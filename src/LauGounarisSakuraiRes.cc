
/*
Copyright 2006 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauGounarisSakuraiRes.cc
    \brief File containing implementation of LauGounarisSakuraiRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauGounarisSakuraiRes.hh"

ClassImp(LauGounarisSakuraiRes)


LauGounarisSakuraiRes::LauGounarisSakuraiRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
	q0_(0.0),
	p0_(0.0),
	pstar0_(0.0),
	erm0_(0.0),
	resMass_(0.0),
	resMassSq_(0.0),
	resWidth_(0.0),
	resRadius_(0.0),
	parRadius_(0.0),
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
	FP0_(1.0)
{
}

LauGounarisSakuraiRes::~LauGounarisSakuraiRes()
{
}

void LauGounarisSakuraiRes::initialise()
{
	// Set-up various constants. This must be called again if the mass/width/spin
	// of a resonance changes...  

	resMass_ = this->getMass();
	resWidth_ = this->getWidth();
	resRadius_ = this->getResRadius();
	parRadius_ = this->getParRadius();

	Double_t massDaug1 = this->getMassDaug1();
	Double_t massDaug2 = this->getMassDaug2();
	Double_t massBachelor = this->getMassBachelor();
	Double_t massParent = this->getMassParent();

	// Check that the spin is 1
	Int_t resSpin = this->getSpin();
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

	// Covariant factor when resonance mass = rest-mass value, m_0 (PDF value)
	erm0_ = (mParentSq_ + resMassSq_ - mBachSq_)/(2.0*massParent*resMass_);
	this->calcCovFactor( erm0_ );

	// Calculate the Blatt-Weisskopf form factor for the case when m = m_0
	FR0_ = 1.0;
	FP0_ = 1.0;
	if ( resSpin > 0 ) {
		const LauBlattWeisskopfFactor* resBWFactor = this->getResBWFactor();
		const LauBlattWeisskopfFactor* parBWFactor = this->getParBWFactor();
		FR0_ = (resBWFactor!=0) ? resBWFactor->calcFormFactor(q0_) : 1.0;
		switch ( parBWFactor->getRestFrame() ) {
			case LauBlattWeisskopfFactor::ResonanceFrame:
				FP0_ = (parBWFactor!=0) ? parBWFactor->calcFormFactor(p0_) : 1.0;
				break;
			case LauBlattWeisskopfFactor::ParentFrame:
				FP0_ = (parBWFactor!=0) ? parBWFactor->calcFormFactor(pstar0_) : 1.0;
				break;
			case LauBlattWeisskopfFactor::Covariant:
				{
				Double_t covFactor = this->getCovFactor();
				if ( resSpin > 2 ) {
					covFactor = TMath::Power( covFactor, 1.0/resSpin );
				} else if ( resSpin == 2 ) {
					covFactor = TMath::Sqrt( covFactor );
				}
				FP0_ = (parBWFactor!=0) ? parBWFactor->calcFormFactor(pstar0_*covFactor) : 1.0;
				break;
				}
		}
	}

	// Calculate the extra things needed by the G-S shape
	h0_ = 2.0*LauConstants::invPi * q0_/resMass_ * TMath::Log((resMass_ + 2.0*q0_)/(2.0*LauConstants::mPi));
	dhdm0_ = h0_ * (1.0/(8.0*q0_*q0_) - 1.0/(2.0*resMassSq_)) + 1.0/(LauConstants::twoPi*resMassSq_);
	d_ = 3.0*LauConstants::invPi * LauConstants::mPi*LauConstants::mPi/(q0_*q0_)
		* TMath::Log((resMass_ + 2.0*q0_)/(2.0*LauConstants::mPi))
		+ resMass_/(LauConstants::twoPi*q0_)
		- LauConstants::mPi*LauConstants::mPi*resMass_/(LauConstants::pi*q0_*q0_*q0_);
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

	const Double_t resMass = this->getMass();
	const Double_t resWidth = this->getWidth();
	const Double_t resRadius = this->getResRadius();
	const Double_t parRadius = this->getParRadius();

	// If the mass is floating and its value has changed we need to
	// recalculate everything that assumes that value
	// Similarly for the BW radii
	if ( ( (!this->fixMass()) && resMass != resMass_ ) ||
	     ( (!this->fixResRadius()) && resRadius != resRadius_ ) ||
	     ( (!this->fixParRadius()) && parRadius != parRadius_ ) ) {
		this->initialise();
	}

	const Int_t resSpin = this->getSpin();
	const Double_t q = this->getQ();
	const Double_t p = this->getP();
	const Double_t pstar = this->getPstar();

	Double_t fFactorR(1.0);
	Double_t fFactorB(1.0);
	if ( resSpin > 0 ) {
		const LauBlattWeisskopfFactor* resBWFactor = this->getResBWFactor();
		const LauBlattWeisskopfFactor* parBWFactor = this->getParBWFactor();
		fFactorR = (resBWFactor!=0) ? resBWFactor->calcFormFactor(q) : 1.0;
		switch ( parBWFactor->getRestFrame() ) {
			case LauBlattWeisskopfFactor::ResonanceFrame:
				fFactorB = (parBWFactor!=0) ? parBWFactor->calcFormFactor(p) : 1.0;
				break;
			case LauBlattWeisskopfFactor::ParentFrame:
				fFactorB = (parBWFactor!=0) ? parBWFactor->calcFormFactor(pstar) : 1.0;
				break;
			case LauBlattWeisskopfFactor::Covariant:
				{
				Double_t covFactor = this->getCovFactor();
				if ( resSpin > 2 ) {
					covFactor = TMath::Power( covFactor, 1.0/resSpin );
				} else if ( resSpin == 2 ) {
					covFactor = TMath::Sqrt( covFactor );
				}
				fFactorB = (parBWFactor!=0) ? parBWFactor->calcFormFactor(pstar*covFactor) : 1.0;
				break;
				}
		}
	}
	const Double_t fFactorRRatio = fFactorR/FR0_;
	const Double_t fFactorBRatio = fFactorB/FP0_;

	const Double_t qRatio = q/q0_;
	const Double_t qTerm = qRatio*qRatio*qRatio;

	const Double_t totWidth = resWidth*qTerm*(resMass/mass)*fFactorRRatio*fFactorRRatio;

	const Double_t massSq = mass*mass;
	const Double_t massSqTerm = resMassSq_ - massSq;

	const Double_t h = 2.0*LauConstants::invPi * q/mass * TMath::Log((mass + 2.0*q)/(2.0*LauConstants::mPi));
	const Double_t f = resWidth * resMassSq_/(q0_*q0_*q0_) * (q*q * (h - h0_) + massSqTerm * q0_*q0_ * dhdm0_);

	// Compute the complex amplitude
	resAmplitude = LauComplex(massSqTerm + f, resMass*totWidth);

	// Scale by the denominator factor, as well as the spin term and Blatt-Weisskopf factors
	Double_t numerFactor = spinTerm*(1.0 + d_ * resWidth/resMass);
	if (!this->ignoreBarrierScaling()) {
   	        numerFactor *= fFactorRRatio*fFactorBRatio;
	}
	const Double_t denomFactor = (massSqTerm + f)*(massSqTerm + f) + resMassSq_*totWidth*totWidth;
	resAmplitude.rescale(numerFactor/denomFactor);

	return resAmplitude;
}

const std::vector<LauParameter*>& LauGounarisSakuraiRes::getFloatingParameters()
{
	this->clearFloatingParameters();

	if ( ! this->fixMass() ) {
		this->addFloatingParameter( this->getMassPar() );
	}
	if ( ! this->fixWidth() ) {
		this->addFloatingParameter( this->getWidthPar() );
	}
	if ( ! this->fixResRadius() ) {
		this->addFloatingParameter( this->getResBWFactor()->getRadiusParameter() );
	}
	if ( ! this->fixParRadius() ) {
		this->addFloatingParameter( this->getParBWFactor()->getRadiusParameter() );
	}

	return this->getParameters();
}

