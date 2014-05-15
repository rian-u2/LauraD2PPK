
// Copyright University of Warwick 2008 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauLASSBWRes.cc
    \brief File containing implementation of LauLASSBWRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauLASSBWRes.hh"

ClassImp(LauLASSBWRes)


LauLASSBWRes::LauLASSBWRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
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

LauLASSBWRes::~LauLASSBWRes()
{
}

void LauLASSBWRes::initialise()
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

	resMass_ = this->getMass();
	resMassSq_ = resMass_*resMass_;

	q0_ = TMath::Sqrt((resMassSq_ - mDaugSumSq_)*(resMassSq_ - mDaugDiffSq_))/(2.0*resMass_);

	Int_t resSpin = this->getSpin();
	if (resSpin != 0) {
		std::cerr << "WARNING in LauLASSBWRes::amplitude : Resonance spin is " << resSpin << "." << std::endl;
		std::cerr << "                                   : LASS amplitude is only for scalers, resetting spin to 0." << std::endl;
		this->changeResonance( -1.0, -1.0, 0 );
	}
}

LauComplex LauLASSBWRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Breit-Wigner resonance,
	// given the invariant mass and cos(helicity) values.

	LauComplex resAmplitude(0.0, 0.0);

	if (mass < 1e-10) {
		std::cerr << "WARNING in LauLASSBWRes::amplitude : mass < 1e-10." << std::endl;
		return LauComplex(0.0, 0.0);
	}

	// Calculate the width of the resonance (as a function of mass)
	// q is the momentum of either daughter in the resonance rest-frame
	Double_t q = this->getQ();
	Double_t resMass = this->getMass();
	Double_t resWidth = this->getWidth();

	// If the mass is floating and their value have changed
	// we need to recalculate everything that assumes this value
	if ( (!this->fixMass()) && resMass != resMass_ ) {
		this->initialise();
	}

	Double_t qRatio = q/q0_;
	Double_t totWidth = resWidth*qRatio*(resMass/mass);

	Double_t massSq = mass*mass;
	Double_t massSqTerm = resMassSq_ - massSq;

	// Compute the complex amplitude
	resAmplitude = LauComplex(massSqTerm, resMass*totWidth);

	// Scale by the denominator factor
	resAmplitude.rescale(spinTerm*(resMassSq_*resWidth/q0_)/(massSqTerm*massSqTerm + resMassSq_*totWidth*totWidth));

	// Calculate the phase shift term
	Double_t deltaB = TMath::ATan((2.0*a_*q)/(2.0 + a_*r_*q*q));
	Double_t cos2PhaseShift = TMath::Cos(2.0*(deltaB + phiB_));
	Double_t sin2PhaseShift = TMath::Sin(2.0*(deltaB + phiB_));
	LauComplex phaseShift(cos2PhaseShift, sin2PhaseShift);

	// Add in the R e^{i phiR} term
	Double_t reR = R_ * TMath::Cos(phiR_);
	Double_t imR = R_ * TMath::Sin(phiR_);
	LauComplex R(reR, imR);

	// Multiply by the phase shift and R e^{i phiR}
	resAmplitude = resAmplitude * phaseShift * R;

	// There is no spin term for the LASS shape 
	// Just set it 1.0 in case anyone decides to use it at a later date.
	spinTerm = 1.0;

	return resAmplitude;

}

void LauLASSBWRes::setResonanceParameter(const TString& name, const Double_t value) 
{
	// Set various parameters for the LASS lineshape dynamics
	if (name == "a") {
		this->setScatteringLength(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Scattering Length = " << this->getScatteringLength() << std::endl;
	}
	else if (name == "r") {
		this->setEffectiveRange(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Effective Range = " << this->getEffectiveRange() << std::endl;
	}
	else if (name == "R") {
		this->setResonanceMag(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Resonance Magnitude = " << this->getResonanceMag() << std::endl;
	}
	else if (name == "B") {
		this->setBackgroundMag(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Background Magnitude = " << this->getBackgroundMag() << std::endl;
	}
	else if (name == "phiR") {
		this->setResonancePhase(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Resonance Phase = " << this->getResonancePhase() << std::endl;
	}
	else if (name == "phiB") {
		this->setBackgroundPhase(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Background Phase = " << this->getBackgroundPhase() << std::endl;
	}
	else if (name == "cutOff") {
		this->setCutOff(value);
		std::cout << "INFO in LauLASSBWRes::setResonanceParameter : Setting LASS Cut Off = " << this->getCutOff() << std::endl;
	}
	else {
		std::cerr << "WARNING in LauLASSBWRes::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

