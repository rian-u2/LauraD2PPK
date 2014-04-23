
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRelBreitWignerRes.cc
    \brief File containing implementation of LauRelBreitWignerRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauRelBreitWignerRes.hh"

ClassImp(LauRelBreitWignerRes)


LauRelBreitWignerRes::LauRelBreitWignerRes(TString resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
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
	FR0_(1.0),
	FB0_(1.0)
{
}

LauRelBreitWignerRes::~LauRelBreitWignerRes()
{
}

void LauRelBreitWignerRes::initialise()
{
	// Set-up various constants. This must be called again if the mass/width/spin
	// of a resonance changes...  

	Int_t resSpin = this->getSpin();
	Double_t resMass = this->getMass();
	Double_t massDaug1 = this->getMassDaug1();
	Double_t massDaug2 = this->getMassDaug2();
	Double_t massBachelor = this->getMassBachelor();
	Double_t massParent = this->getMassParent();

	// Create the mass squares, sums, differences etc.
	resMassSq_ = resMass*resMass;
	mDaugSum_  = massDaug1 + massDaug2;
	mDaugSumSq_ = mDaugSum_*mDaugSum_;
	mDaugDiff_ = massDaug1 - massDaug2;
	mDaugDiffSq_ = mDaugDiff_*mDaugDiff_;
	mParentSq_ = massParent*massParent;
	mBachSq_ = massBachelor*massBachelor;

	// Create an effective resonance pole mass to protect against resonances
	// that are below threshold
	Double_t effResMass = resMass;
	if (resMassSq_ - mDaugSumSq_ < 0.0 ){
		Double_t minMass = mDaugSum_;
		Double_t maxMass = massParent - massBachelor;
		Double_t tanhTerm = std::tanh( (resMass - ((minMass + maxMass)/2))/(maxMass-minMass));
		effResMass = minMass + (maxMass-minMass)*(1+tanhTerm)/2;
	}
	Double_t effResMassSq = effResMass*effResMass;

	// Decay momentum of either daughter in the resonance rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t term1 = effResMassSq - mDaugSumSq_;
	Double_t term2 = effResMassSq - mDaugDiffSq_;
	Double_t term12 = term1*term2;
	if (term12 > 0.0) {
		q0_ = TMath::Sqrt(term12)/(2.0*effResMass);
	} else {
		q0_ = 0.0;
	}

	// Momentum of the bachelor particle in the resonance rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t eBach = (mParentSq_ - effResMassSq - mBachSq_)/(2.0*effResMass);
	Double_t termBach = eBach*eBach - mBachSq_;
	if ( eBach<0.0 || termBach<0.0 ) {
		p0_ = 0.0;
	} else {
		p0_ = TMath::Sqrt( termBach );
	}

	// Momentum of the bachelor particle in the parent rest frame
	// when resonance mass = rest-mass value, m_0 (PDG value)
	Double_t eStarBach = (mParentSq_ + mBachSq_ - effResMassSq)/(2.0*massParent);
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

	if (resSpin > 5) {
		std::cerr << "WARNING in LauRelBreitWignerRes::initialise : Resonances spin is > 5.  Blatt-Weisskopf form factors will be set to 1.0" << std::endl;
	}
}

void LauRelBreitWignerRes::setBarrierRadii(const Double_t resRadius, const Double_t parRadius, const BarrierType type)
{
	// Reset the Blatt-Weisskopf barrier radius for the resonance and its parent
	this->LauAbsResonance::setBarrierRadii( resRadius, parRadius, type );

	// Recalculate the Blatt-Weisskopf form factor for the case when m = m_0
	const Double_t resR = this->getResBWRadius();
	const Double_t parR = this->getParBWRadius();

	std::cout << "INFO in LauRelBreitWignerRes::setBarrierRadii : Recalculating barrier factor normalisations for new radii: resonance = " << resR << ", parent = " << parR << std::endl;

	Double_t zR0 = q0_*q0_*resR*resR;
	Double_t zB0 = p0_*p0_*parR*parR;
	if ( ( type == LauAbsResonance::BWPrimeBarrier ) || ( type == LauAbsResonance::ExpBarrier ) ) {
		FR0_ = (resR==0.0) ? 1.0 : this->calcFFactor(zR0);
		FB0_ = (parR==0.0) ? 1.0 : this->calcFFactor(zB0);
	}
}

Double_t LauRelBreitWignerRes::calcFFactor(Double_t z)
{
	// Calculate the requested form factor for the resonance, given the z value
	Double_t fFactor(1.0);

	// For scalars the form factor is always unity
	// TODO: and we currently don't have formulae for spin > 5
	Int_t resSpin = this->getSpin();
	if ( (resSpin == 0) || (resSpin>5) ) {
		return fFactor;
	}

	const BarrierType barrierType = this->getBarrierType();
	if ( barrierType == LauAbsResonance::BWBarrier ) {
		if (resSpin == 1) {
			fFactor = TMath::Sqrt(2.0*z/(z + 1.0));
		} else if (resSpin == 2) {
			fFactor = TMath::Sqrt(13.0*z*z/(z*z + 3.0*z + 9.0));
		} else if (resSpin == 3) {
			fFactor = TMath::Sqrt(277.0*z*z*z/(z*z*z + 6.0*z*z + 45.0*z + 225.0));
		} else if (resSpin == 4) {
			fFactor = TMath::Sqrt(12746.0*z*z*z*z/(z*z*z*z + 10.0*z*z*z + 135.0*z*z + 1575.0*z + 11025.0));
		} else if (resSpin == 5) {
			fFactor = TMath::Sqrt(998881.0*z*z*z*z*z/(z*z*z*z*z + 15.0*z*z*z*z + 315.0*z*z*z + 6300.0*z*z + 99225.0*z + 893025.0));
		}
	} else if ( barrierType == LauAbsResonance::BWPrimeBarrier ) {
		if (resSpin == 1) {
			fFactor = TMath::Sqrt(1.0/(z + 1.0));
		} else if (resSpin == 2) {
			fFactor = TMath::Sqrt(1.0/(z*z + 3.0*z + 9.0));
		} else if (resSpin == 3) {
			fFactor = TMath::Sqrt(1.0/(z*z*z + 6.0*z*z + 45.0*z + 225.0));
		} else if (resSpin == 4) {
			fFactor = TMath::Sqrt(1.0/(z*z*z*z + 10.0*z*z*z + 135.0*z*z + 1575.0*z + 11025.0));
		} else if (resSpin == 5) {
			fFactor = TMath::Sqrt(1.0/(z*z*z*z*z + 15.0*z*z*z*z + 315.0*z*z*z + 6300.0*z*z + 99225.0*z + 893025.0));
		}
	} else if ( barrierType == LauAbsResonance::ExpBarrier ) {
		if (resSpin == 1) {
			fFactor = TMath::Exp( -TMath::Sqrt(z) );
		} else if (resSpin == 2) {
			fFactor = TMath::Exp( -z );
		} else if (resSpin == 3) {
			fFactor = TMath::Exp( -TMath::Sqrt(z*z*z) );
		} else if (resSpin == 4) {
			fFactor = TMath::Exp( -z*z );
		} else if (resSpin == 5) {
			fFactor = TMath::Exp( -TMath::Sqrt(z*z*z*z*z) );
		}
	}

	return fFactor;

}

LauComplex LauRelBreitWignerRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Breit-Wigner resonance,
	// given the invariant mass and cos(helicity) values.

	LauComplex resAmplitude(0.0, 0.0);

	if (mass < 1e-10) {
		std::cerr << "WARNING in LauRelBreitWignerRes::amplitude : mass < 1e-10." << std::endl;
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

	Int_t resSpin = this->getSpin();
	Double_t resMass = this->getMass();
	Double_t resWidth = this->getWidth();
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
	Double_t qTerm(0.0);
	if (resSpin == 0) {
		qTerm = qRatio;
	} else if (resSpin == 1) {
		qTerm = qRatio*qRatio*qRatio;
	} else if (resSpin == 2) {
		qTerm = TMath::Power(qRatio, 5.0);
	} else {
		qTerm = TMath::Power(qRatio, 2*resSpin + 1);  
	}

	Double_t totWidth = resWidth*qTerm*(resMass/mass)*fFactorRRatio*fFactorRRatio;

	Double_t massSq = mass*mass;
	Double_t massSqTerm = resMassSq_ - massSq;

	// Compute the complex amplitude
	resAmplitude = LauComplex(massSqTerm, resMass*totWidth);

	// Scale by the denominator factor, as well as the spin term and Blatt-Weisskopf factors
	resAmplitude.rescale((fFactorRRatio*fFactorBRatio*spinTerm)/(massSqTerm*massSqTerm + resMassSq_*totWidth*totWidth));

	return resAmplitude;
}

