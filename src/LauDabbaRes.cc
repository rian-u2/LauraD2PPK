
// Copyright University of Warwick 2010 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDabbaRes.cc
    \brief File containing implementation of LauDabbaRes class.
    Formulae and data values from arXiv:0901.2217 - author D.V.Bugg
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauDabbaRes.hh"

ClassImp(LauDabbaRes)


LauDabbaRes::LauDabbaRes(TString resName, LauParameter* resMass, LauParameter* resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	mSumSq_(0.0),
	sAdler_(0.0),
	b_(24.49),
	alpha_(0.1),
	beta_(0.1)
{
}

LauDabbaRes::~LauDabbaRes()
{
}

void LauDabbaRes::initialise()
{
	// check that we have a D and a pi
	this->checkDaughterTypes();

	// Initialise various constants
	Double_t massDaug1 = this->getMassDaug1();
	Double_t massDaug2 = this->getMassDaug2();

	Double_t mSum = massDaug1 + massDaug2;
	mSumSq_ = mSum*mSum;

	Double_t massDaug1Sq = massDaug1*massDaug1;
	Double_t massDaug2Sq = massDaug2*massDaug2;
	sAdler_ = TMath::Max(massDaug1Sq,massDaug2Sq) - 0.5*TMath::Min(massDaug1Sq,massDaug2Sq); // Adler zero at (mD)^2 - 0.5*(mpi)^2

	Int_t resSpin = this->getSpin();
	if (resSpin != 0) {
		std::cerr << "WARNING in LauDabbaRes::initialise : Spin = " << resSpin << " is not zero!  It will be ignored anyway!" << std::endl;
	}
}

void LauDabbaRes::setConstants(Double_t b, Double_t alpha, Double_t beta) {
	b_ = b;
	alpha_ = alpha;
	beta_ = beta;
}

void LauDabbaRes::checkDaughterTypes() const
{
	// Check that the daughter tracks are D and pi. Otherwise issue a warning.
	Int_t resPairAmpInt = this->getPairInt();
	if (resPairAmpInt < 1 || resPairAmpInt > 3) {
		std::cerr << "WARNING in LauDabbaRes::checkDaughterTypes : resPairAmpInt = " << resPairAmpInt << " is out of the range [1,2,3]." << std::endl;
		return;
	}

	// Check that daughter types agree
	const TString& nameDaug1 = this->getNameDaug1();
	const TString& nameDaug2 = this->getNameDaug2();
	if ( !( nameDaug1.Contains("pi", TString::kIgnoreCase) && nameDaug2.Contains("d", TString::kIgnoreCase) ) ) {
		if ( !( nameDaug2.Contains("pi", TString::kIgnoreCase) && nameDaug1.Contains("d", TString::kIgnoreCase) ) ) {
			std::cerr << "ERROR in LauDabbaRes::checkDaughterTypes : Dabba model is using daughters \"" << nameDaug1 << "\" and \"" << nameDaug2 << "\" that are not a D meson and a pion." << std::endl;
		}
	}
}

LauComplex LauDabbaRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Dabba distribution
	// given the invariant mass and cos(helicity) values.

	// Invariant mass squared combination for the system
	Double_t s = mass*mass;

	// Dabba is spin zero - so there are no helicity factors.
	// Just set it to 1.0 in case anyone decides to use it at a later date.
	spinTerm = 1.0;

	// Phase-space factor
	Double_t rho(0.0);
	Double_t sDiff = s - mSumSq_;
	if ( sDiff > 0.0 ) {
		rho = TMath::Sqrt(1.0 - mSumSq_/s);
	}

	Double_t realPart = 1.0 - beta_ * sDiff;

	Double_t imagPart = b_ * TMath::Exp( - alpha_ * sDiff ) * ( s - sAdler_ ) * rho;

	LauComplex resAmplitude( realPart, imagPart );

	Double_t denomFactor = realPart*realPart + imagPart*imagPart;

	Double_t invDenomFactor = 0.0;
	if (denomFactor > 1e-10) {invDenomFactor = 1.0/denomFactor;}

	resAmplitude.rescale(spinTerm*invDenomFactor);

	return resAmplitude;
}

