
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixPropagator.cc
    \brief File containing implementation of LauKMatrixPropagator class.
*/

#include "LauKMatrixPropagator.hh"
#include "LauConstants.hh"
#include "LauTextFileParser.hh"

#include "TMath.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cerr;

ClassImp(LauKMatrixPropagator)

LauKMatrixPropagator::LauKMatrixPropagator(const TString& name, const TString& paramFile, 
					   Int_t resPairAmpInt, Int_t nChannels, 
					   Int_t nPoles, Int_t rowIndex) :
	name_(name),
	paramFileName_(paramFile),
	resPairAmpInt_(resPairAmpInt), 
	index_(rowIndex - 1),
	previousS_(0.0),
	scattSVP_(0.0),
	prodSVP_(0.0),
	nChannels_(nChannels),
	nPoles_(nPoles),
	sAConst_(0.0),
	m2piSq_(4.0*LauConstants::mPiSq),
	m2KSq_( 4.0*LauConstants::mKSq),
	m2EtaSq_(4.0*LauConstants::mEtaSq),
	mEtaEtaPSumSq_((LauConstants::mEta + LauConstants::mEtaPrime)*(LauConstants::mEta + LauConstants::mEtaPrime)),
	mEtaEtaPDiffSq_((LauConstants::mEta - LauConstants::mEtaPrime)*(LauConstants::mEta - LauConstants::mEtaPrime)),
	mKpiSumSq_((LauConstants::mK + LauConstants::mPi)*(LauConstants::mK + LauConstants::mPi)),
	mKpiDiffSq_((LauConstants::mK - LauConstants::mPi)*(LauConstants::mK - LauConstants::mPi)),
	mKEtaPSumSq_((LauConstants::mK + LauConstants::mEtaPrime)*(LauConstants::mK + LauConstants::mEtaPrime)),
	mKEtaPDiffSq_((LauConstants::mK - LauConstants::mEtaPrime)*(LauConstants::mK - LauConstants::mEtaPrime)),
	mK3piDiffSq_((LauConstants::mK - 3.0*LauConstants::mPi)*(LauConstants::mK - 3.0*LauConstants::mPi)),
	k3piFactor_(TMath::Power((1.44 - mK3piDiffSq_)/1.44, -2.5)),
	fourPiFactor1_(16.0*LauConstants::mPiSq),
	fourPiFactor2_(TMath::Sqrt(1.0 - fourPiFactor1_)),
	adlerZeroFactor_(0.0),
	parametersSet_(kFALSE),
	verbose_(kFALSE)
{
	// Constructor
	realProp_.Clear(); negImagProp_.Clear();
	this->setParameters(paramFile);
}

LauKMatrixPropagator::~LauKMatrixPropagator() 
{
	// Destructor
	realProp_.Clear(); 
	negImagProp_.Clear();
}

LauComplex LauKMatrixPropagator::getPropTerm(Int_t channel) const
{
	// Get the (i,j) = (index_, channel) term of the propagator
	// matrix. This allows us not to return the full propagator matrix.
	Double_t realTerm = this->getRealPropTerm(channel);
	Double_t imagTerm = this->getImagPropTerm(channel);

	LauComplex propTerm(realTerm, imagTerm);
	return propTerm;

}

Double_t LauKMatrixPropagator::getRealPropTerm(Int_t channel) const
{
	// Get the real part of the (i,j) = (index_, channel) term of the propagator
	// matrix. This allows us not to return the full propagator matrix.
	if (parametersSet_ == kFALSE) {return 0.0;}

	Double_t propTerm = realProp_[index_][channel];
	return propTerm;

}

Double_t LauKMatrixPropagator::getImagPropTerm(Int_t channel) const
{
	// Get the imaginary part of the (i,j) = (index_, channel) term of the propagator
	// matrix. This allows us not to return the full propagator matrix.
	if (parametersSet_ == kFALSE) {return 0.0;}

	Double_t imagTerm = -1.0*negImagProp_[index_][channel];
	return imagTerm;

}

void LauKMatrixPropagator::updatePropagator(const LauKinematics* kinematics)
{

	// Calculate the K-matrix propagator for the given s value.  
	// The K-matrix amplitude is given by
	// T_i = sum_{ij} (I - iK*rho)^-1 * P_j, where P is the production K-matrix.
	// i = index for the state (e.g. S-wave index = 0).
	// Here, we only find the (I - iK*rho)^-1 matrix part.

	// Get the invariant mass squared (s) from the kinematics object. 
	// Use the resPairAmpInt to find which mass-squared combination to use.
	Double_t s(0.0);
	if (resPairAmpInt_ == 1) {
		s = kinematics->getm23Sq();
	} else if (resPairAmpInt_ == 2) {
		s = kinematics->getm13Sq();
	} else if (resPairAmpInt_ == 3) {
		s = kinematics->getm12Sq();
	}

	this->updatePropagator(s);

}

void LauKMatrixPropagator::updatePropagator(Double_t s)
{
	// Calculate the K-matrix propagator for the given s value.  
	// The K-matrix amplitude is given by
	// T_i = sum_{ij} (I - iK*rho)^-1 * P_j, where P is the production K-matrix.
	// i = index for the state (e.g. S-wave index = 0).
	// Here, we only find the (I - iK*rho)^-1 matrix part.

	// Check if we have almost the same s value as before. If so, don't re-calculate
	// the propagator nor any of the pole mass summation terms.
	if (TMath::Abs(s - previousS_) < 1e-6) {
		//cout<<"Already got propagator for s = "<<s<<endl;
		return;
	}

	if (parametersSet_ == kFALSE) {
		//cerr<<"ERROR in LauKMatrixPropagator::updatePropagator. Parameters have not been set."<<endl;
		return;
	}

	// Calculate the denominator pole mass terms and Adler zero factor
	this->calcPoleDenomVect(s);
	this->updateAdlerZeroFactor(s);

	// Calculate the scattering K-matrix (real and symmetric)
	this->calcScattKMatrix(s);
	// Calculate the phase space density matrix, which is diagonal, but can be complex 
	// if the quantity s is below various threshold values (analytic continuation).
	this->calcRhoMatrix(s);

	// Calculate K*rho (real and imaginary parts, since rho can be complex)
	TMatrixD K_realRho(ScattKMatrix_);
	K_realRho *= ReRhoMatrix_;
	TMatrixD K_imagRho(ScattKMatrix_);
	K_imagRho *= ImRhoMatrix_;

	// A = I + K*Imag(rho), B = -K*Real(Rho)
	// Calculate C and D matrices such that (A + iB)*(C + iD) = I,
	// ie. C + iD = (I - i K*rho)^-1, separated into real and imaginary parts.
	TMatrixD A(IMatrix_);
	A += K_imagRho;
	TMatrixD B(zeroMatrix_);
	B -= K_realRho;

	TMatrixD invA(TMatrixD::kInverted, A);
	TMatrixD invA_B(invA);
	invA_B *= B;
	TMatrixD B_invA_B(B);
	B_invA_B *= invA_B;

	TMatrixD invC(A);
	invC += B_invA_B;

	// Set the real part of the propagator matrix ("C")
	realProp_ = TMatrixD(TMatrixD::kInverted, invC);

	// Set the (negative) imaginary part of the propagator matrix ("-D")
	TMatrixD BC(B);
	BC *= realProp_;
	negImagProp_ = TMatrixD(invA);
	negImagProp_ *= BC;

	// Also calculate the production SVP term, since this uses Adler-zero parameters
	// defined in the parameter file.
	this->updateProdSVPTerm(s);

	// Finally, keep track of the value of s we just used.
	previousS_ = s;

}

void LauKMatrixPropagator::setParameters(const TString& inputFile)
{

	// Read an input file that specifies the values of the coupling constants g_i for
	// the given number of poles and their (bare) masses. Also provided are the f_{ab} 
	// slow-varying constants. The input file should also provide the Adler zero 
	// constants s_0, s_A and s_A0.

	// Format of input file:
	// Indices (nChannels) of phase space channel types (defined in KMatrixChannels enum)
	// Then the bare pole mass and coupling constants over all channels for each pole:
	// m_{alpha} g_1^{alpha} g_2^{alpha} ... g_n^{alpha}   where n = nChannels
	// Repeat for N poles. Then define the f_{ab} scattering coefficients
	// f_{11} f_{12} ... f_{1n}
	// f_{21} f_{22} ... f_{2n} etc.. where n = nChannels
	// Note that the K-matrix will be symmetrised (by definition), so it is sufficient 
	// to only have the upper half filled with sensible values.
	// Then define the Adler-zero and slowly-varying part (SVP) constants
	// m0^2 s0Scatt s0Prod sA sA0
	// where m0^2 = mass-squared constant for scattering production f_{ab} numerator
	parametersSet_ = kFALSE;

	cout<<"Initialising K-matrix propagator "<<name_<<" parameters from "<<inputFile.Data()<<endl;

	cout<<"nChannels = "<<nChannels_<<", nPoles = "<<nPoles_<<endl;

	LauTextFileParser readFile(inputFile);
	readFile.processFile();

	// Get the first (non-comment) line
	std::vector<std::string> channelTypeLine = readFile.getNextLine();
	Int_t nTypes = static_cast<Int_t>(channelTypeLine.size());
	if (nTypes != nChannels_) {
		cerr<<"Error in LauKMatrixPropagator::setParameters. Input file "<<inputFile
			<<" defines "<<nTypes<<" channels when "<<nChannels_<<" are expected"<<endl;
		return;
	}

	// Get the list of channel indices to specify what phase space factors should be used
	// e.g. pipi, Kpi, eta eta', 4pi etc..
	Int_t iChannel(0);
	phaseSpaceTypes_.clear();
	for (iChannel = 0; iChannel < nChannels_; iChannel++) {

		Int_t phaseSpaceInt = atoi(channelTypeLine[iChannel].c_str());
		Bool_t checkChannel = this->checkPhaseSpaceType(phaseSpaceInt);

		if (checkChannel == kTRUE) {
			cout<<"Adding phase space channel index "<<phaseSpaceInt
				<<" to K-matrix propagator "<<name_<<endl;
			phaseSpaceTypes_.push_back(phaseSpaceInt);
		} else {
			cerr<<"Phase space channel index "<<phaseSpaceInt
				<<" should be between 1 and "<<LauKMatrixPropagator::TotChannels-1<<endl;
			cerr<<"Stopping initialisation of the K-matrix propagator "<<name_<<endl;
			cerr<<"Please correct the channel index on the first line of "<<inputFile<<endl;
			return;
		}

	}

	// Clear vector of pole masses^2 as well as the map of the coupling constant vectors.
	mSqPoles_.clear(); gCouplings_.clear();

	Double_t poleMass(0.0), poleMassSq(0.0), couplingConst(0.0);
	Int_t iPole(0);
	Int_t nPoleNumbers(nChannels_+1);

	for (iPole = 0; iPole < nPoles_; iPole++) {

		// Read the next line of bare pole mass and its coupling constants 
		// over all channels (nChannels_)
		std::vector<std::string> poleLine = readFile.getNextLine();
		Int_t nPoleValues = static_cast<Int_t>(poleLine.size());
		if (nPoleValues != nPoleNumbers) {
			cerr<<"Error in LauKMatrixPropagator::setParameters. Expecting "
				<<nPoleNumbers<<" numbers for the bare pole "<<iPole<<" line (mass and "
				<<nChannels_<<" coupling constants). Found "<<nPoleValues<<" values instead."
				<<endl;
			return;
		}

		poleMass = atof(poleLine[0].c_str());
		poleMassSq = poleMass*poleMass;
		LauParameter mPoleParam(poleMassSq);
		mSqPoles_.push_back(mPoleParam);

		std::vector<LauParameter> couplingVector;

		cout<<"Added bare pole mass "<<poleMass<<" GeV for pole number "<<iPole+1<<endl;

		for (iChannel = 0; iChannel < nChannels_; iChannel++) {

			couplingConst = atof(poleLine[iChannel+1].c_str());
			LauParameter couplingParam(couplingConst);
			couplingVector.push_back(couplingParam);

			cout<<"Added coupling parameter g^"<<iPole+1<<"_"<<iChannel+1<<" = "<<couplingConst<<endl;

		}

		gCouplings_[iPole] = couplingVector;    

	}

	// Scattering (slowly-varying part, or SVP) values

	fScattering_.clear();
	Int_t jChannel(0);

	std::vector<std::string> scatteringLine = readFile.getNextLine();
	Int_t nScatteringValues = static_cast<Int_t>(scatteringLine.size());
	if (nScatteringValues != nChannels_) {
		cerr<<"Error in LauKMatrixPropagator::setParameters. Expecting "
			<<nChannels_<<" scattering SVP f constants instead of "<<nScatteringValues
			<<" for the K-matrix row index "<<index_<<endl;
		return;
	}

	std::vector<LauParameter> scatteringVect;
	for (jChannel = 0; jChannel < nChannels_; jChannel++) {

		Double_t fScattValue = atof(scatteringLine[jChannel].c_str());
		LauParameter scatteringParam(fScattValue);
		scatteringVect.push_back(scatteringParam);

		cout<<"Added scattering SVP f("<<index_+1<<","<<jChannel+1<<") = "<<fScattValue<<endl;

	}

	fScattering_[index_] = scatteringVect;

	// Now extract the constants for the "Adler-zero" terms
	std::vector<std::string> constLine = readFile.getNextLine();
	Int_t nConstValues = static_cast<Int_t>(constLine.size());
	if (nConstValues != 5) {
		cerr<<"Error in LauKMatrixPropagator::setParameters. Expecting 5 values for the Adler-zero constants:"
			<<" m0^2 s0Scatt s0Prod sA sA0"<<endl;
		return;
	}

	Double_t mSq0Value = atof(constLine[0].c_str());
	Double_t s0ScattValue = atof(constLine[1].c_str());
	Double_t s0ProdValue = atof(constLine[2].c_str());
	Double_t sAValue = atof(constLine[3].c_str());
	Double_t sA0Value = atof(constLine[4].c_str());

	cout<<"Adler zero constants:"<<endl;
	cout<<"m0Sq = "<<mSq0Value<<", s0Scattering = "<<s0ScattValue<<", s0Production = "
		<<s0ProdValue<<", sA = "<<sAValue<<" and sA0 = "<<sA0Value<<endl;

	mSq0_ = LauParameter("mSq0", mSq0Value);
	s0Scatt_ = LauParameter("s0Scatt", s0ScattValue);
	s0Prod_ = LauParameter("s0Prod", s0ProdValue);
	sA_ = LauParameter("sA", sAValue);
	sA0_ = LauParameter("sA0", sA0Value);
	sAConst_ = 0.5*sAValue*LauConstants::mPiSq;

	// Identity and null matrices
	IMatrix_.Clear();
	IMatrix_.ResizeTo(nChannels_, nChannels_);
	for (iChannel = 0; iChannel < nChannels_; iChannel++) {
		IMatrix_[iChannel][iChannel] = 1.0;
	}

	zeroMatrix_.Clear();
	zeroMatrix_.ResizeTo(nChannels_, nChannels_);

	realProp_.Clear(); negImagProp_.Clear();
	realProp_.ResizeTo(nChannels_, nChannels_);
	negImagProp_.ResizeTo(nChannels_, nChannels_);

	// All required parameters have been set
	parametersSet_ = kTRUE;

	cout<<"Finished initialising K-matrix propagator "<<name_<<endl;

}

void LauKMatrixPropagator::calcScattKMatrix(Double_t s) 
{

	// Calculate the scattering K-matrix for the given value of s.
	// We need to obtain the complete matrix (not just one row/column) 
	// to get the correct inverted (I - i K rho) terms for the propagator.

	if (verbose_) {cout<<"Within calcScattKMatrix for s = "<<s<<endl;}

	// Clear the internal matrix and resize.
	ScattKMatrix_.Clear();
	ScattKMatrix_.ResizeTo(nChannels_, nChannels_);

	Int_t iChannel(0), jChannel(0), iPole(0);

	// The pole denominator 1/(m^2 - s) terms should already be calculated
	// by the calcPoleDenomVect() function. These same terms are also
	// used for calculating the production K-matrix elements.

	// Calculate the "slowly-varying part" (SVP), e.g. (1 GeV - s0)/(s - s0)
	this->updateScattSVPTerm(s);

	// Now loop over iChannel, jChannel to calculate Kij = Kji.
	for (iChannel = 0; iChannel < nChannels_; iChannel++) {

		std::vector<LauParameter> SVPVect(0);   

		KMatrixParamMap::iterator SVPIter = fScattering_.find(iChannel);
		if (SVPIter != fScattering_.end()) {SVPVect = SVPIter->second;}

		Int_t SVPVectSize = static_cast<Int_t>(SVPVect.size());

		// Scattering matrix is real and symmetric. Start j loop from i.
		for (jChannel = iChannel; jChannel < nChannels_; jChannel++) {

			Double_t Kij(0.0);

			// Calculate pole mass summation term
			for (iPole = 0; iPole < nPoles_; iPole++) {

				KMatrixParamMap::iterator couplingIter = gCouplings_.find(iPole);

				std::vector<LauParameter> couplingVect = couplingIter->second;

				Double_t g_i = couplingVect[iChannel].value();
				Double_t g_j = couplingVect[jChannel].value();

				Kij += poleDenomVect_[iPole]*g_i*g_j;
				if (verbose_) {cout<<"1: Kij for i = "<<iChannel<<", j = "<<jChannel<<" = "<<Kij<<endl;}

			}

			if (SVPVectSize != 0 && jChannel < SVPVectSize) {
				Double_t fij = SVPVect[jChannel].value();
				Kij += fij*scattSVP_;
			}

			Kij *= adlerZeroFactor_;
			if (verbose_) {cout<<"2: Kij for i = "<<iChannel<<", j = "<<jChannel<<" = "<<Kij<<endl;}

			// Assign the TMatrix (i,j) element to the variable Kij and Kji (symmetry)
			ScattKMatrix_(iChannel, jChannel) = Kij;
			ScattKMatrix_(jChannel, iChannel) = Kij;

		} // j loop

	} // i loop

}

void LauKMatrixPropagator::calcPoleDenomVect(Double_t s)
{
	// Calculate the 1/(m_pole^2 - s) terms for the scattering 
	// and production K-matrix formulae.
	poleDenomVect_.clear();
	Int_t iPole(0);
	for (iPole = 0; iPole < nPoles_; iPole++) {

		Double_t poleTerm = mSqPoles_[iPole] - s;
		Double_t invPoleTerm(0.0);
		if (TMath::Abs(poleTerm) > 1.0e-6) {invPoleTerm = 1.0/poleTerm;}

		poleDenomVect_.push_back(invPoleTerm);

	}

}

Double_t LauKMatrixPropagator::getPoleDenomTerm(Int_t poleIndex) const
{

	if (parametersSet_ == kFALSE) {return 0.0;}

	Double_t poleDenom(0.0);
	poleDenom = poleDenomVect_[poleIndex];
	return poleDenom;

}

Double_t LauKMatrixPropagator::getCouplingConstant(Int_t poleIndex, Int_t channelIndex) const
{

	if (parametersSet_ == kFALSE) {return 0.0;}

	Double_t couplingConst(0.0);
	KMatrixParamMap::const_iterator couplingIter = gCouplings_.find(poleIndex);
	std::vector<LauParameter> couplingVect = couplingIter->second;
	couplingConst = couplingVect[channelIndex].value();

	return couplingConst;

}

Double_t LauKMatrixPropagator::calcSVPTerm(Double_t s, Double_t s0) const
{

	if (parametersSet_ == kFALSE) {return 0.0;}

	// Calculate the "slowly-varying part" (SVP)
	Double_t result(0.0);
	Double_t deltaS = s - s0;
	if (TMath::Abs(deltaS) > 1.0e-6) {
		result = (mSq0_.value() - s0)/deltaS;
	}  

	return result;

}

void LauKMatrixPropagator::updateScattSVPTerm(Double_t s)
{
	// Update the scattering "slowly-varying part" (SVP)
	Double_t s0Scatt = s0Scatt_.value();
	scattSVP_ = this->calcSVPTerm(s, s0Scatt);
}

void LauKMatrixPropagator::updateProdSVPTerm(Double_t s)
{
	// Update the production "slowly-varying part" (SVP)
	Double_t s0Prod = s0Prod_.value();
	prodSVP_ = this->calcSVPTerm(s, s0Prod);
}

void LauKMatrixPropagator::updateAdlerZeroFactor(Double_t s)
{

	// Calculate the multiplicative factor containing various Adler zero
	// constants.
	adlerZeroFactor_ = 0.0;

	Double_t sA0Val = sA0_.value();
	Double_t deltaS = s - sA0Val;
	if (TMath::Abs(deltaS) > 1e-6) {
		adlerZeroFactor_ = (s - sAConst_)*(1.0 - sA0Val)/deltaS;
	}  

}

void LauKMatrixPropagator::calcRhoMatrix(Double_t s)
{

	// Calculate the real and imaginary part of the phase space density
	// diagonal matrix for the given invariant mass squared quantity, s.
	// The matrix can be complex if s is below threshold (so that
	// the amplitude continues analytically).
	ReRhoMatrix_.Clear(); ImRhoMatrix_.Clear();
	ReRhoMatrix_.ResizeTo(nChannels_, nChannels_);
	ImRhoMatrix_.ResizeTo(nChannels_, nChannels_);

	LauComplex rho(0.0, 0.0);
	Int_t phaseSpaceIndex(0);

	for (Int_t iChannel (0); iChannel < nChannels_; ++iChannel) {

		phaseSpaceIndex = phaseSpaceTypes_[iChannel];

		if (phaseSpaceIndex == LauKMatrixPropagator::PiPi) {
			rho = this->calcPiPiRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::KK) {
			rho = this->calcKKRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::FourPi) {
			rho = this->calcFourPiRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::EtaEta) {
			rho = this->calcEtaEtaRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::EtaEtaP) {
			rho = this->calcEtaEtaPRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::KPi) {
			rho = this->calcKPiRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::KEtaP) {
			rho = this->calcKEtaPRho(s);
		} else if (phaseSpaceIndex == LauKMatrixPropagator::KThreePi) {
			rho = this->calcKThreePiRho(s);
		}

		if (verbose_) {
			cout<<"ReRhoMatrix("<<iChannel<<", "<<iChannel<<") = "<<rho.re()<<endl;
			cout<<"ImRhoMatrix("<<iChannel<<", "<<iChannel<<") = "<<rho.im()<<endl;
		}

		ReRhoMatrix_(iChannel, iChannel) = rho.re();
		ImRhoMatrix_(iChannel, iChannel) = rho.im();    

	}

}

LauComplex LauKMatrixPropagator::calcPiPiRho(Double_t s) const
{
	// Calculate the pipi phase space factor
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm = (-m2piSq_/s) + 1.0;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcKKRho(Double_t s) const
{
	// Calculate the KK phase space factor
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm = (-m2KSq_/s) + 1.0;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcFourPiRho(Double_t s) const
{
	// Calculate the 4pi phase space factor. This uses a 6th-order polynomial 
        // parameterisation that approximates the multi-body phase space double integral
        // defined in Eq 4 of the A&S paper hep-ph/0204328. This form agrees with the 
        // BaBar model (another 6th order polynomial from s^4 down to 1/s^2), but avoids the
        // exponential increase at small values of s (~< 0.1) arising from 1/s and 1/s^2.
        // Eq 4 is evaluated for each value of s by assuming incremental steps of 1e-3 GeV^2 
        // for s1 and s2, the invariant energy squared of each of the di-pion states,
        // with the integration limits of s1 = (2*mpi)^2 to (sqrt(s) - 2*mpi)^2 and
        // s2 = (2*mpi)^2 to (sqrt(s) - sqrt(s1))^2. The mass M of the rho is taken to be
        // 0.775 GeV and the energy-dependent width of the 4pi system 
        // Gamma(s) = gamma_0*rho1^3(s), where rho1 = sqrt(1.0 - 4*mpiSq/s) and gamma_0 is 
        // the "width" of the 4pi state at s = 1, which is taken to be 0.3 GeV 
        // (~75% of the total width from PDG estimates of the f0(1370) -> 4pi state).
        // The normalisation term rho_0 is found by ensuring that the phase space integral
        // at s = 1 is equal to sqrt(1.0 - 16*mpiSq/s). Note that the exponent for this 
        // factor in hep-ph/0204328 is wrong; it should be 0.5, i.e. sqrt, not n = 1 to 5.
        // Plotting the value of this double integral as a function of s can then be fitted
        // to a 6th-order polynomial (for s < 1), which is the result used below

	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	if (s <= 1.0) {
	        Double_t rhoTerm = ((1.07885*s + 0.13655)*s - 0.29744)*s - 0.20840;
	        rhoTerm = ((rhoTerm*s + 0.13851)*s - 0.01933)*s + 0.00051;
		// For some values of s (below 2*mpi), this term is a very small 
		// negative number. Check for this and set the rho term to zero.
		if (rhoTerm < 0.0) {rhoTerm = 0.0;}
		rho.setRealPart( rhoTerm );
	} else {
		rho.setRealPart( TMath::Sqrt(1.0 - (fourPiFactor1_/s)) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcEtaEtaRho(Double_t s) const
{
	// Calculate the eta-eta phase space factor
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm = (-m2EtaSq_/s) + 1.0;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcEtaEtaPRho(Double_t s) const
{
	// Calculate the eta-eta' phase space factor. Note that the
        // mass difference term m_eta - m_eta' is not included,
        // since this corresponds to a "t or u-channel crossing",
        // which means that we cannot simply analytically continue 
        // this part of the phase space factor below threshold, which
        // we can do for s-channel contributions. This is actually an 
        // unsolved problem, e.g. see Guo et al 1409.8652, and 
        // Danilkin et al 1409.7708. Anisovich and Sarantsev in 
        // hep-ph/0204328 "solve" this issue by setting the mass 
        // difference term to unity, which is what we do here...

	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm = (-mEtaEtaPSumSq_/s) + 1.0;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}


LauComplex LauKMatrixPropagator::calcKPiRho(Double_t s) const
{
	// Calculate the K-pi phase space factor
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm1 = (-mKpiSumSq_/s) + 1.0;
	Double_t sqrtTerm2 = (-mKpiDiffSq_/s) + 1.0;
	Double_t sqrtTerm = sqrtTerm1*sqrtTerm2;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcKEtaPRho(Double_t s) const
{
	// Calculate the K-eta' phase space factor
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	Double_t sqrtTerm1 = (-mKEtaPSumSq_/s) + 1.0;
	Double_t sqrtTerm2 = (-mKEtaPDiffSq_/s) + 1.0;
	Double_t sqrtTerm = sqrtTerm1*sqrtTerm2;
	if (sqrtTerm < 0.0) {
		rho.setImagPart( TMath::Sqrt(-sqrtTerm) );
	} else {
		rho.setRealPart( TMath::Sqrt(sqrtTerm) );
	}

	return rho;
}

LauComplex LauKMatrixPropagator::calcKThreePiRho(Double_t s) const
{
	// Calculate the Kpipipi + multimeson phase space factor. 
	// Use the simplest definition in hep-ph/9705401 (Eq 14), which is the form 
	// used for the rest of that paper (thankfully, the amplitude does not depend
	// significantly on the form used for the K3pi phase space factor).
	LauComplex rho(0.0, 0.0);
	if (TMath::Abs(s) < 1e-10) {return rho;}

	if (s < 1.44) {

		Double_t powerTerm = (-mK3piDiffSq_/s) + 1.0;
		if (powerTerm < 0.0) {
			rho.setImagPart( k3piFactor_*TMath::Power(-powerTerm, 2.5) );
		} else {
			rho.setRealPart( k3piFactor_*TMath::Power(powerTerm, 2.5) );
		}

	} else {
		rho.setRealPart( 1.0 );
	}

	return rho;
}

Bool_t LauKMatrixPropagator::checkPhaseSpaceType(Int_t phaseSpaceInt) const
{
	Bool_t passed(kFALSE);

	if (phaseSpaceInt >= 1 && phaseSpaceInt < LauKMatrixPropagator::TotChannels) {
		passed = kTRUE;
	}

	return passed;
}
