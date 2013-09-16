
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSigmaRes.cc
    \brief File containing implementation of LauSigmaRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauSigmaRes.hh"

ClassImp(LauSigmaRes)


LauSigmaRes::LauSigmaRes(TString resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	mPiSq4_(0.0),
	sAdler_(0.0),
	b1_(0.0),
	b2_(0.0),
	A_(0.0),
	m0_(0.0),
	m0Sq_(0.0),
	denom_(0.0)
{
	// Initialise various constants
	mPiSq4_ = 4.0*LauConstants::mPiSq;
	sAdler_ = LauConstants::mPiSq*0.5; // Adler zero at 0.5*(mpi)^2

	// constant factors from BES data
	Double_t b1 = 0.5843;
	Double_t b2 = 1.6663;
	Double_t A = 1.082;
	Double_t m0 = 0.9264;

	this->setConstants(b1, b2, A, m0);
}

LauSigmaRes::~LauSigmaRes()
{
}

void LauSigmaRes::initialise()
{
	this->checkDaughterTypes();

	Double_t resSpin = this->getSpin();
	if (resSpin != 0) {
		std::cerr << "ERROR in LauSigmaRes : spin = " << resSpin << " is not zero!" << std::endl;
	}
}

void LauSigmaRes::setConstants(Double_t b1, Double_t b2, Double_t A, Double_t m0) {
	b1_ = b1;
	b2_ = b2;
	A_ = A;
	m0_ = m0;
	m0Sq_ = m0_*m0_;
	denom_ = m0Sq_ - sAdler_;
}

void LauSigmaRes::checkDaughterTypes() const
{
	// Check that the daughter tracks are the same type. Otherwise issue a warning
	// and set the type to be pion for the Sigma distribution.
	Int_t resPairAmpInt = this->getPairInt();
	if (resPairAmpInt < 1 || resPairAmpInt > 3) {
		std::cerr << "WARNING in LauSigmaRes::checkDaughterTypes : resPairAmpInt = " << resPairAmpInt << " is out of the range [1,2,3]." << std::endl;
		return;
	}

	const TString& nameDaug1 = this->getNameDaug1();
	const TString& nameDaug2 = this->getNameDaug2();
	if (!nameDaug1.CompareTo(nameDaug2, TString::kExact)) {
		// Daughter types agree. Find out if we have pion or kaon system
		if (!nameDaug1.Contains("pi")) {
			std::cerr << "ERROR in LauSigmaRes::checkDaughterTypes : Sigma model is using daughters \""<<nameDaug1<<"\" and \""<<nameDaug2<<"\", which are not pions." << std::endl;
		}
	}
}

LauComplex LauSigmaRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Sigma distribution
	// given the invariant mass and cos(helicity) values.

	// First check that the appropriate daughters are either pi+pi- or K+K-
	// Check that the daughter tracks are the same type. Otherwise issue a warning
	// and set the type to be pion for the Sigma distribution. Returns the
	// integer defined by the enum LauSigmaRes::SigmaPartType.

	Double_t s = mass*mass; // Invariant mass squared combination for the system
	Double_t rho(0.0); // Phase-space factor
	if (s > mPiSq4_) {rho = TMath::Sqrt(1.0 - mPiSq4_/s);}

	Double_t f = b2_*s + b1_; // f(s) function
	Double_t numerator = s - sAdler_;
	Double_t gamma(0.0);
	if (TMath::Abs(denom_) > 1e-10 && TMath::Abs(A_) > 1e-10) {   
		// Decay width of the system
		gamma = rho*(numerator/denom_)*f*TMath::Exp(-(s - m0Sq_)/A_);
	}

	// Now form the complex amplitude - use relativistic BW form (without barrier factors)    
	// Note that the M factor in the denominator is not the "pole" at ~500 MeV, but is 
	// m0_ = 0.9264, the mass when the phase shift goes through 90 degrees.

	Double_t dMSq = m0Sq_ - s;
	Double_t widthTerm = gamma*m0_;
	LauComplex resAmplitude(dMSq, widthTerm);

	Double_t denomFactor = dMSq*dMSq + widthTerm*widthTerm;

	Double_t invDenomFactor = 0.0;
	if (denomFactor > 1e-10) {invDenomFactor = 1.0/denomFactor;}

	resAmplitude.rescale(spinTerm*invDenomFactor);

	return resAmplitude;

}

