
// Copyright University of Warwick 2006 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGounarisSakuraiRes.cc
    \brief File containing implementation of LauGounarisSakuraiRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauGounarisSakuraiRes.hh"

ClassImp(LauGounarisSakuraiRes)


LauGounarisSakuraiRes::LauGounarisSakuraiRes(TString resName, LauParameter* resMass, LauParameter* resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	q0_(0.0),
	p0_(0.0),
	pstar0_(0.0),
	resMassSq_(0.0),
	mDaugSum_(0.0),
	mDaugSumSq_(0.0),
	mDaugDiff_(0.0),
	mDaugDiffSq_(0.0),
	mParentSq_(0.0),
	mBachSq_(0.0),
	h0_(0.0),
	dhdm0_(0.0),
	d_(0.0),
	FR0_(1.0),
	FB0_(1.0)
{
}

LauGounarisSakuraiRes::~LauGounarisSakuraiRes()
{
}

void LauGounarisSakuraiRes::initialise()
{
	// Set-up various constants. This must be called again if the mass/width/spin
	// of a resonance changes...  

	Int_t resSpin = this->getSpin();
	resMass_ = this->getMass();
	Double_t massDaug1 = this->getMassDaug1();
	Double_t massDaug2 = this->getMassDaug2();
	Double_t massBachelor = this->getMassBachelor();
	Double_t massParent = this->getMassParent();

	// Check that the spin is 1
	if (resSpin != 1) {
		std::cerr << "WARNING in LauGounarisSakuraiRes::initialise : Resonance spin is != 1. This lineshape is for the rho(770), setting the spin to 1." << std::endl;
		this->changeResonance( -1.0, -1.0, 1 );
		resSpin = this->getSpin();
	}

	// Create the mass squares, sums, differences etc.
	resMassSq_ = resMass_*resMass_;
	mDaugSum_  = massDaug1 + massDaug2;
	mDaugSumSq_ = mDaugSum_*mDaugSum_;
	mDaugDiff_ = massDaug1 - massDaug2;
	mDaugDiffSq_ = mDaugDiff_*mDaugDiff_;
	mParentSq_ = massParent*massParent;
	mBachSq_ = massBachelor*massBachelor;

	// Decay momentum of either daughter in the resonance rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t term1 = resMassSq_ - mDaugSumSq_;
	Double_t term2 = resMassSq_ - mDaugDiffSq_;
	Double_t term12 = term1*term2;
	if (term12 > 0.0) {
		q0_ = TMath::Sqrt(term12)/(2.0*resMass_);
	} else {
		q0_ = 0.0;
	}

	// Momentum of the bachelor particle in the resonance rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t eBach = (mParentSq_ - resMassSq_ - mBachSq_)/(2.0*resMass_);
	Double_t termBach = eBach*eBach - mBachSq_;
	if ( eBach<0.0 || termBach<0.0 ) {
		p0_ = 0.0;
	} else {
		p0_ = TMath::Sqrt( termBach );
	}

	// Momentum of the bachelor particle in the parent rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t eStarBach = (mParentSq_ + mBachSq_ - resMassSq_)/(2.0*massParent);
	Double_t termStarBach = eStarBach*eStarBach - mBachSq_;
	if ( eStarBach<0.0 || termStarBach<0.0 ) {
		pstar0_ = 0.0;
	} else {
		pstar0_ = TMath::Sqrt( termStarBach );
	}

	// Blatt-Weisskopf barrier factor constant: z = q^2*radius^2
	// Calculate the Blatt-Weisskopf form factor for the case when m = m_0
	const Double_t resR = this->getResBWRadius();
	const Double_t parR = this->getParBWRadius();
	const BarrierType barrierType = this->getBarrierType();
	this->setBarrierRadii(resR, parR, barrierType);

	// Calculate the extra things needed by the G-S shape
	h0_ = 2.0*LauConstants::invPi * q0_/resMass_ * TMath::Log((resMass_ + 2.0*q0_)/(2.0*LauConstants::mPi));
	dhdm0_ = h0_ * (1.0/(8.0*q0_*q0_) - 1.0/(2.0*resMassSq_)) + 1.0/(LauConstants::twoPi*resMassSq_);
	d_ = 3.0*LauConstants::invPi * LauConstants::mPi*LauConstants::mPi/(q0_*q0_)
		* TMath::Log((resMass_ + 2.0*q0_)/(2.0*LauConstants::mPi))
		+ resMass_/(LauConstants::twoPi*q0_)
		- LauConstants::mPi*LauConstants::mPi*resMass_/(LauConstants::pi*q0_*q0_*q0_);
}

void LauGounarisSakuraiRes::setBarrierRadii(Double_t resRadius, Double_t parRadius, LauAbsResonance::BarrierType type)
{
	// Reset the Blatt-Weisskopf barrier radius for the resonance and its parent
	this->LauAbsResonance::setBarrierRadii( resRadius, parRadius, type );
	
	// Recalculate the Blatt-Weisskopf form factor for the case when m = m_0
	const Double_t resR = this->getResBWRadius();
	const Double_t parR = this->getParBWRadius();

	std::cout << "INFO in LauGounarisSakuraiRes::setBarrierRadii : Recalculating barrier factor normalisations for new radii: resonance = " << resR << ", parent = " << parR << std::endl;

	Double_t zR0 = q0_*q0_*resR*resR;
	Double_t zB0 = p0_*p0_*parR*parR;
	if ( ( type == LauAbsResonance::BWPrimeBarrier ) || ( type == LauAbsResonance::ExpBarrier ) ) {
		FR0_ = (resR==0.0) ? 1.0 : this->calcFFactor(zR0);
		FB0_ = (parR==0.0) ? 1.0 : this->calcFFactor(zB0);
	}
}

Double_t LauGounarisSakuraiRes::calcFFactor(Double_t z)
{
	// Calculate the requested form factor for the resonance, given the z value
	Double_t fFactor(1.0);
	const BarrierType barrierType = this->getBarrierType();
	if ( barrierType == LauAbsResonance::BWBarrier ) {
		fFactor = TMath::Sqrt(2.0*z/(z + 1.0));
	} else if ( barrierType == LauAbsResonance::BWPrimeBarrier ) {
		fFactor = TMath::Sqrt(1.0/(z + 1.0));
	} else if ( barrierType == LauAbsResonance::ExpBarrier ) {
		fFactor = TMath::Exp( -TMath::Sqrt(z) );
	}
	return fFactor;
}

LauComplex LauGounarisSakuraiRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Breit-Wigner resonance,
	// given the invariant mass and cos(helicity) values.

	LauComplex resAmplitude(0.0, 0.0);

	if (mass < 1e-10) {
		std::cerr << "WARNING in LauGounarisSakuraiRes::amplitude : mass < 1e-10." << std::endl;
		return LauComplex(0.0, 0.0);
	} else if (q0_ < 1e-30) {
		return LauComplex(0.0, 0.0);
	}

	// Calculate the width of the resonance (as a function of mass)
	// First, calculate the various form factors.
	// NB
	// q is the momentum of either daughter in the resonance rest-frame,
	// p is the momentum of the bachelor in the resonance rest-frame,
	// pstar is the momentum of the bachelor in the parent rest-frame.
	// These quantities have been calculate in LauAbsResonance::amplitude(...)

	Double_t resMass = this->getMass();
	Double_t resWidth = this->getWidth();

	// If the mass is floating and their value have changed
	// we need to recalculate everything that assumes this value
	if ( (!this->fixMass()) && resMass != resMass_ ) {
		this->initialise();
	}

	Double_t q = this->getQ();
	Double_t p = this->getP();
	//Double_t pstar = this->getPstar();

	const Double_t resR = this->getResBWRadius();
	const Double_t parR = this->getParBWRadius();
	Double_t zR = q*q*resR*resR;
	Double_t zB = p*p*parR*parR;
	Double_t fFactorR = (resR==0.0) ? 1.0 : this->calcFFactor(zR);
	Double_t fFactorB = (parR==0.0) ? 1.0 : this->calcFFactor(zB);
	Double_t fFactorRRatio = fFactorR/FR0_;
	Double_t fFactorBRatio = fFactorB/FB0_;

	Double_t qRatio = q/q0_;
	Double_t qTerm = qRatio*qRatio*qRatio;

	Double_t totWidth = resWidth*qTerm*(resMass/mass)*fFactorRRatio*fFactorRRatio;

	Double_t massSq = mass*mass;
	Double_t massSqTerm = resMassSq_ - massSq;

	Double_t h = 2.0*LauConstants::invPi * q/mass * TMath::Log((mass + 2.0*q)/(2.0*LauConstants::mPi));
	Double_t f = totWidth * resMassSq_/(q0_*q0_*q0_) * (q*q * (h - h0_) + massSqTerm * q0_*q0_ * dhdm0_);

	// Compute the complex amplitude
	resAmplitude = LauComplex(massSqTerm + f, resMass*totWidth);

	// Scale by the denominator factor, as well as the spin term and Blatt-Weisskopf factors
	Double_t numerFactor = fFactorRRatio*fFactorBRatio*spinTerm*(1 + d_ * resWidth/resMass);
	Double_t denomFactor = (massSqTerm + f)*(massSqTerm + f) + resMassSq_*totWidth*totWidth;
	resAmplitude.rescale(numerFactor/denomFactor);

	return resAmplitude;
}

