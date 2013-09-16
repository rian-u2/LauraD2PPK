
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauLASSNRRes.cc
    \brief File containing implementation of LauLASSNRRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauLASSNRRes.hh"

ClassImp(LauLASSNRRes)


LauLASSNRRes::LauLASSNRRes(TString resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	q0_(0.0),
	mDaugSum_(0.0),
	mDaugSumSq_(0.0),
	mDaugDiff_(0.0),
	mDaugDiffSq_(0.0),
	resMassSq_(0.0),
	r_(0.0),
	a_(0.0),
	B_(0.0),
	R_(0.0),
	phiB_(0.0),
	phiR_(0.0),
	cutOff_(0.0)
{
	// Default values for LASS parameters
	r_ = 3.32;
	a_ = 2.07;
	R_ = 1.0;
	B_ = 1.0;
	phiR_ = 0.0;
	phiB_ = 0.0;
	cutOff_ = 1.8;
}

LauLASSNRRes::~LauLASSNRRes()
{
}

void LauLASSNRRes::initialise()
{
	// Create the mass sums and differences
	Double_t massDaug1 = this->getMassDaug1();
	Double_t massDaug2 = this->getMassDaug2();

	mDaugSum_  = massDaug1 + massDaug2;
	mDaugSumSq_ = mDaugSum_*mDaugSum_;

	mDaugDiff_ = massDaug1 - massDaug2;
	mDaugDiffSq_ = mDaugDiff_*mDaugDiff_;

	// Decay momentum of either daughter in the resonance rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)

	Double_t resMass = this->getMass();
	resMassSq_ = resMass*resMass;

	q0_ = TMath::Sqrt((resMassSq_ - mDaugSumSq_)*(resMassSq_ - mDaugDiffSq_))/(2.0*resMass);

	Int_t resSpin = this->getSpin();
	if (resSpin != 0) {
		std::cerr << "WARNING in LauLASSNRRes::amplitude : Resonance spin is " << resSpin << "." << std::endl;
		std::cerr << "                                   : LASS amplitude is only for scalers, resetting spin to 0." << std::endl;
		this->changeResonance( -1.0, -1.0, 0 );
	}
}

LauComplex LauLASSNRRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Breit-Wigner resonance,
	// given the invariant mass and cos(helicity) values.

	LauComplex totAmplitude(0.0, 0.0);
	LauComplex bkgAmplitude(0.0, 0.0);

	if (mass < 1e-10) {
		std::cerr << "WARNING in LauLASSNRRes::amplitude : mass < 1e-10." << std::endl;
		return LauComplex(0.0, 0.0);
	}

	// q is the momentum of either daughter in the resonance rest-frame
	Double_t q = this->getQ();

	// Calculate the phase shift term
	Double_t deltaB = TMath::ATan((2.0*a_*q)/(2.0 + a_*r_*q*q));

	// Form the real and imaginary parts
	Double_t realTerm = q/TMath::Tan(deltaB + phiB_);
	Double_t imagTerm = q;

	// Compute the complex amplitude
	bkgAmplitude = LauComplex(realTerm, imagTerm);

	// Scale by the numerator and denominator factors
	bkgAmplitude.rescale(spinTerm*mass*B_/(realTerm*realTerm + imagTerm*imagTerm));

	if (mass < cutOff_) {
		totAmplitude = bkgAmplitude;
	}

	// There is no spin term for the LASS shape 
	// Just set it 1.0 in case anyone decides to use it at a later date.
	spinTerm = 1.0;

	return totAmplitude;

}

void LauLASSNRRes::setResonanceParameter(Double_t value, const TString& name) 
{
	// Set various parameters for the LASS lineshape dynamics
	if (name == "a") {
		this->setScatteringLength(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Scattering Length = " << this->getScatteringLength() << std::endl;
	}
	else if (name == "r") {
		this->setEffectiveRange(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Effective Range = " << this->getEffectiveRange() << std::endl;
	}
	else if (name == "R") {
		this->setResonanceMag(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Resonance Magnitude = " << this->getResonanceMag() << std::endl;
	}
	else if (name == "B") {
		this->setBackgroundMag(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Background Magnitude = " << this->getBackgroundMag() << std::endl;
	}
	else if (name == "phiR") {
		this->setResonancePhase(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Resonance Phase = " << this->getResonancePhase() << std::endl;
	}
	else if (name == "phiB") {
		this->setBackgroundPhase(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Background Phase = " << this->getBackgroundPhase() << std::endl;
	}
	else if (name == "cutOff") {
		this->setCutOff(value);
		std::cout << "INFO in LauLASSNRRes::setResonanceParameter : Setting LASS Cut Off = " << this->getCutOff() << std::endl;
	}
	else {
		std::cerr << "WARNING in LauLASSNRRes::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

