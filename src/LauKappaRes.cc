
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKappaRes.cc
    \brief File containing implementation of LauKappaRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauKappaRes.hh"

ClassImp(LauKappaRes)


LauKappaRes::LauKappaRes(TString resName, LauParameter* resMass, LauParameter* resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	mSum_(0.0),
	mSumSq_(0.0),
	sAdler_(0.0),
	b1_(0.0),
	b2_(0.0),
	A_(0.0),
	m0_(0.0),
	m0Sq_(0.0),
	denom_(0.0)
{
	// Initialise various constants
	mSum_ = LauConstants::mPi + LauConstants::mK;
	mSumSq_ = mSum_*mSum_;
	sAdler_ = LauConstants::mKSq - LauConstants::mPiSq*0.5; // Adler zero at (mK)^2 - 0.5*(mpi)^2

	// Default constant factors from BES data
	Double_t b1 = 24.49;
	Double_t b2 = 0.0;
	Double_t A = 2.5;
	Double_t m0 = 3.3;
	this->setConstants( b1, b2, A, m0 );
}

LauKappaRes::~LauKappaRes()
{
}

void LauKappaRes::initialise()
{
	this->checkDaughterTypes();

	Double_t resSpin = this->getSpin();
	if (resSpin != 0) {
		std::cerr << "ERROR in LauKappaRes : spin = " << resSpin << " is not zero!" << std::endl;
	}
}

void LauKappaRes::setConstants(const Double_t b1, const Double_t b2, const Double_t A, const Double_t m0)
{
	b1_ = b1;
	b2_ = b2;
	A_ = A;
	m0_ = m0;
	m0Sq_ = m0_*m0_;
	denom_ = m0Sq_ - sAdler_;
}

void LauKappaRes::checkDaughterTypes() const
{
	// Check that the daughter tracks are K and pi. Otherwise issue a warning.
	Int_t resPairAmpInt = this->getPairInt();
	if (resPairAmpInt < 1 || resPairAmpInt > 3) {
		std::cerr << "WARNING in LauKappaRes::checkDaughterTypes : resPairAmpInt = " << resPairAmpInt << " is out of the range [1,2,3]." << std::endl;
		return;
	}

	// Check that daughter types agree
	const TString& nameDaug1 = this->getNameDaug1();
	const TString& nameDaug2 = this->getNameDaug2();
	if ( !( nameDaug1.Contains("pi", TString::kIgnoreCase) && nameDaug2.Contains("k", TString::kIgnoreCase) ) ) {
		if ( !( nameDaug2.Contains("pi", TString::kIgnoreCase) && nameDaug1.Contains("k", TString::kIgnoreCase) ) ) {
			std::cerr << "ERROR in LauKappaRes::checkDaughterTypes : Kappa model is using daughters \"" << nameDaug1 << "\" and \"" << nameDaug2 << "\" that are not a kaon and a pion." << std::endl;
		}
	}
}

LauComplex LauKappaRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Kappa distribution
	// given the invariant mass and cos(helicity) values.

	// First check that the appropriate daughters are either pi+pi- or K+K-
	// Check that the daughter tracks are the same type. Otherwise issue a warning
	// and set the type to be pion for the Kappa distribution. Returns the
	// integer defined by the enum LauKappaRes::KappaPartType.

	Double_t s = mass*mass; // Invariant mass squared combination for the system
	Double_t rho(0.0); // Phase-space factor
	if (s > mSumSq_) {rho = TMath::Sqrt(1.0 - mSumSq_/s);}

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

void LauKappaRes::setResonanceParameter(const TString& name, const Double_t value) 
{
	// Set various parameters for the lineshape
	if (name == "b1") {
		this->setB1Value(value);
		std::cout << "INFO in LauKappaRes::setResonanceParameter : Setting parameter b1 = " << this->getB1Value() << std::endl;
	}
	else if (name == "b2") {
		this->setB2Value(value);
		std::cout << "INFO in LauKappaRes::setResonanceParameter : Setting parameter b2 = " << this->getB2Value() << std::endl;
	}
	else if (name == "A") {
		this->setAValue(value);
		std::cout << "INFO in LauKappaRes::setResonanceParameter : Setting parameter A = " << this->getAValue() << std::endl;
	}
	else if (name == "m0") {
		this->setM0Value(value);
		std::cout << "INFO in LauKappaRes::setResonanceParameter : Setting parameter m0 = " << this->getM0Value() << std::endl;
	}
	else {
		std::cerr << "WARNING in LauKappaRes::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

