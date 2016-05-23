
// Copyright University of Warwick 2004 - 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRhoOmegaMix.cc
    \brief File containing implementation of LauRhoOmegaMix class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauRhoOmegaMix.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauRhoOmegaMix)


LauRhoOmegaMix::LauRhoOmegaMix(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, 
			       const LauDaughters* daughters) :
    LauAbsResonance(resInfo, resPairAmpInt, daughters),
    q0_(0.0),
    p0_(0.0),
    pstar0_(0.0),
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
    FR0_(1.0),
    FP0_(1.0),
    mOmega_(0),
    wOmega_(0),
    magB_(0),
    phiB_(0),
    delta_(0)
{
    // Initialise various constants

    // Set the omega mass and width
    const Double_t mOmegaVal = 0.78265;
    const Double_t wOmegaVal = 0.00849;

    const TString& parNameBase = this->getSanitisedName();

    TString mOmegaName(parNameBase); mOmegaName += "_mOmega";
    mOmega_ = resInfo->getExtraParameter(mOmegaName);
    if (!mOmega_) {
	mOmega_ = new LauParameter(mOmegaName, mOmegaVal, 0.0, 100.0, kTRUE);
	mOmega_->secondStage(kTRUE);
	resInfo->addExtraParameter(mOmega_);
    }

    TString wOmegaName(parNameBase); wOmegaName += "_wOmega";
    wOmega_ = resInfo->getExtraParameter(wOmegaName);
    if (!wOmega_) {
	wOmega_ = new LauParameter(wOmegaName, wOmegaVal, 0.0, 100.0, kTRUE);
	wOmega_->secondStage(kTRUE);
	resInfo->addExtraParameter(wOmega_);
    }


    // Set the magnitude and phase of the omega amplitude mixing term.
    // These should be fitted
    const Double_t magBVal = 1.0;
    const Double_t phiBVal = 0.0;

    TString magBName(parNameBase); magBName += "_magB";
    magB_ = resInfo->getExtraParameter(magBName);
    if (!magB_) {
	magB_ = new LauParameter(magBName, magBVal, 0.0, 100.0, kTRUE);
	magB_->secondStage(kTRUE);
	resInfo->addExtraParameter(magB_);
    }

    TString phiBName(parNameBase); phiBName += "_phiB";
    phiB_ = resInfo->getExtraParameter(phiBName);
    if (!phiB_) {
	phiB_ = new LauParameter(phiBName, phiBVal, -100.0, 100.0, kTRUE);
	phiB_->secondStage(kTRUE);
	resInfo->addExtraParameter(phiB_);
    }

    // Set the delta parameter for the omega amplitude mixing term. This
    // is usually fixed but should be varied for systematic error checks.
    // In theory, this parameter can be complex, but we only use its magnitude
    // in the mixing amplitude, since its usually very small: (2.15 +- 0.35) MeV/c^2
    const Double_t deltaVal = 2.15e-3;
    
    TString deltaName(parNameBase); deltaName += "_delta";
    delta_ = resInfo->getExtraParameter(deltaName);
    if (!delta_) {
	delta_ = new LauParameter(deltaName, deltaVal, 0.0, 100.0, kTRUE);
	delta_->secondStage(kTRUE);
	resInfo->addExtraParameter(delta_);
    }    

}

LauRhoOmegaMix::~LauRhoOmegaMix()
{
}

void LauRhoOmegaMix::initialise()
{

    // Set-up various constants

    // Rho mass and width: take them as potential fit parameters
    resMass_   = this->getMass();
    resWidth_  = this->getWidth();
    resRadius_ = this->getResRadius();
    parRadius_ = this->getParRadius();

    Double_t massDaug1 = this->getMassDaug1();
    Double_t massDaug2 = this->getMassDaug2();
    Double_t massBachelor = this->getMassBachelor();
    Double_t massParent = this->getMassParent();

    // Create the mass squares, sums, differences etc.
    resMassSq_ = resMass_*resMass_;
    mDaugSum_  = massDaug1 + massDaug2;
    mDaugSumSq_ = mDaugSum_*mDaugSum_;
    mDaugDiff_ = massDaug1 - massDaug2;
    mDaugDiffSq_ = mDaugDiff_*mDaugDiff_;
    mParentSq_ = massParent*massParent;
    mBachSq_ = massBachelor*massBachelor;
    
    // Create an effective resonance pole mass to protect against resonances
    // that are below threshold
    Double_t effResMass = resMass_;
    Double_t effResMassSq = resMassSq_;
    if (resMassSq_ - mDaugSumSq_ < 0.0  || resMass_ > massParent - massBachelor){
	Double_t minMass = mDaugSum_;
	Double_t maxMass = massParent - massBachelor;
	Double_t tanhTerm = std::tanh( (resMass_ - ((minMass + maxMass)/2))/(maxMass-minMass));
	effResMass = minMass + (maxMass-minMass)*(1+tanhTerm)/2;
	effResMassSq = effResMass*effResMass;
    }
    
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
    if ( eBach < 0.0 || termBach < 0.0 ) {
	p0_ = 0.0;
    } else {
	p0_ = TMath::Sqrt( termBach );
    }
    
    // Momentum of the bachelor particle in the parent rest frame
    // when resonance mass = rest-mass value, m_0 (PDG value)
    Double_t eStarBach = (mParentSq_ + mBachSq_ - effResMassSq)/(2.0*massParent);
    Double_t termStarBach = eStarBach*eStarBach - mBachSq_;
    if ( eStarBach < 0.0 || termStarBach < 0.0 ) {
	pstar0_ = 0.0;
    } else {
	pstar0_ = TMath::Sqrt( termStarBach );
    }
    
    // Calculate the Blatt-Weisskopf form factor for the case when m = m_0
    const LauBlattWeisskopfFactor* resBWFactor = this->getResBWFactor();
    const LauBlattWeisskopfFactor* parBWFactor = this->getParBWFactor();
    FR0_ = (resBWFactor!=0) ? resBWFactor->calcFormFactor(q0_) : 1.0;
    FP0_ = (parBWFactor!=0) ? parBWFactor->calcFormFactor(p0_) : 1.0;
    
}

LauComplex LauRhoOmegaMix::resAmp(Double_t mass, Double_t /*spinTerm*/) {

    // This function returns the complex dynamical amplitude for a rho-omega mass
    // mixing amplitude given the invariant mass and cos(helicity) values
    
    // Sanity checks
    if (mass < 1e-10) {
	std::cerr << "WARNING in LauRelBreitWignerRes::amplitude : mass < 1e-10." << std::endl;
	return LauComplex(0.0, 0.0);
    } else if (q0_ < 1e-30) {
	return LauComplex(0.0, 0.0);
    }

    // Calculate the width of the rho resonance as a function of mass.
    // q is the momentum of either daughter in the resonance rest-frame,
    // p is the momentum of the bachelor in the resonance rest-frame,

    const Double_t resMass = this->getMass();
    const Double_t resWidth = this->getWidth();
    const Double_t resRadius = this->getResRadius();
    const Double_t parRadius = this->getParRadius();
    const Double_t q = this->getQ();
    const Double_t p = this->getP();

    // If the mass is floating and its value has changed we need to
    // recalculate everything that assumes that value.
    // Similarly for the BW radii
    if ( ( (!this->fixMass()) && resMass != resMass_ ) ||
	 ( (!this->fixResRadius()) && resRadius != resRadius_ ) ||
	 ( (!this->fixParRadius()) && parRadius != parRadius_ ) ) {
	this->initialise();
    }

    const LauBlattWeisskopfFactor* resBWFactor = this->getResBWFactor();
    const LauBlattWeisskopfFactor* parBWFactor = this->getParBWFactor();
    const Double_t fFactorR = (resBWFactor!=0) ? resBWFactor->calcFormFactor(q) : 1.0;
    const Double_t fFactorB = (parBWFactor!=0) ? parBWFactor->calcFormFactor(p) : 1.0;
    const Double_t fFactorRRatio = fFactorR/FR0_;
    const Double_t fFactorBRatio = fFactorB/FP0_;

    const Double_t qRatio = q/q0_;
    const Double_t qTerm = qRatio*qRatio*qRatio;

    // The mass-dependent width of the rho resonance component
    const Double_t rhoWidth = resWidth*qTerm*(resMass/mass)*fFactorRRatio*fFactorRRatio;

    // The rho propagator term
    const Double_t massSq = mass*mass;
    const LauComplex rhoProp = LauComplex(resMassSq_ - massSq, -resMass_*rhoWidth);

    // The rho amplitude part
    const LauComplex rhoAmp = LauComplex(p*qRatio*fFactorRRatio, 0.0)/rhoProp;

    // The omega propagator term. Assume the omega width does not depend on the running mass
    const Double_t massOmega = this->getmOmegaValue();
    const Double_t widthOmega = this->getwOmegaValue();
    const LauComplex omegaProp = LauComplex(massOmega*massOmega - massSq, -massOmega*widthOmega);

    // The Delta parameter, which we assume is purely real. Theoretically, delta can
    // be complex, but we only use its (small) magnitude here
    const Double_t Delta = (resMass + massOmega)*this->getdeltaValue();

    // The B amplitude term
    const Double_t magBVal = this->getmagBValue()*Delta;
    const Double_t phiBVal = this->getphiBValue();
    const LauComplex BTerm = LauComplex(magBVal*cos(phiBVal), magBVal*sin(phiBVal));

    // The omega amplitude
    const LauComplex unity(1.0, 0.0);
    const LauComplex omegaAmp = (BTerm/omegaProp) + unity;
    
    // The mixing correction denominator term.
    // First, the product of the two propagators
    const LauComplex prodProp = rhoProp*omegaProp;
    const LauComplex DeltaSqTerm = LauComplex(Delta*Delta, 0.0)/prodProp;
    const LauComplex mixingDenom = unity/(unity - DeltaSqTerm);
    
    // Now form the full amplitude
    LauComplex resAmplitude = rhoAmp*omegaAmp/mixingDenom;

    // Multiply by the parent barrier term
    resAmplitude.rescale(fFactorBRatio);

    return resAmplitude;

}

const std::vector<LauParameter*>& LauRhoOmegaMix::getFloatingParameters() {

    this->clearFloatingParameters();
    
    if ( ! this->fixmOmegaValue() ) {
	this->addFloatingParameter( mOmega_ );
    }

    if ( ! this->fixwOmegaValue() ) {
	this->addFloatingParameter( wOmega_ );
    }

    if ( ! this->fixmagBValue() ) {
	this->addFloatingParameter( magB_ );
    }

    if ( ! this->fixphiBValue() ) {
	this->addFloatingParameter( phiB_ );
    }

    if ( ! this->fixdeltaValue() ) {
	this->addFloatingParameter( delta_ );
    }
    
    return this->getParameters();
}

void LauRhoOmegaMix::setResonanceParameter(const TString& name, const Double_t value) {

    // Set various parameters for the lineshape
    if (name == "mOmega") {
	this->setmOmegaValue(value);
	std::cout << "INFO in LauRhoOmegaMix::setResonanceParameter : Setting parameter mOmega = " << this->getmOmegaValue() << std::endl;
    } else if (name == "wOmega") {
	this->setwOmegaValue(value);
	std::cout << "INFO in LauRhoOmegaMix::setResonanceParameter : Setting parameter wOmega = " << this->getwOmegaValue() << std::endl;
    } else if (name == "magB") {
	this->setmagBValue(value);
	std::cout << "INFO in LauRhoOmegaMix::setResonanceParameter : Setting parameter magB = " << this->getmagBValue() << std::endl;
    } else if (name == "phiB") {
	this->setphiBValue(value);
	std::cout << "INFO in LauRhoOmegaMix::setResonanceParameter : Setting parameter phiB = " << this->getphiBValue() << std::endl;
    } else if (name == "delta") {
	this->setdeltaValue(value);
	std::cout << "INFO in LauRhoOmegaMix::setResonanceParameter : Setting parameter delta = " << this->getdeltaValue() << std::endl;
    } else {
	std::cerr << "WARNING in LauSigmaRes::setResonanceParameter: Parameter name "<<name<<" not recognised.  No parameter changes made." << std::endl;
    }

}

void LauRhoOmegaMix::floatResonanceParameter(const TString& name) {

    if (name == "mOmega") {
	if ( mOmega_->fixed() ) {
	    mOmega_->fixed( kFALSE );
	    this->addFloatingParameter( mOmega_ );
	} else {
	    std::cerr << "WARNING in LauRhoOmegaMix::floatResonanceParameter: Parameter "<<name<<" already floating.  No parameter changes made." << std::endl;
	}
    } else if (name == "wOmega") {
	if ( wOmega_->fixed() ) {
	    wOmega_->fixed( kFALSE );
	    this->addFloatingParameter( wOmega_ );
	} else {
	    std::cerr << "WARNING in LauRhoOmegaMix::floatResonanceParameter: Parameter "<<name<<" already floating.  No parameter changes made." << std::endl;
	}
    } else if (name == "magB") {
	if ( magB_->fixed() ) {
	    magB_->fixed( kFALSE );
	    this->addFloatingParameter( magB_ );
	} else {
	    std::cerr << "WARNING in LauRhoOmegaMix::floatResonanceParameter: Parameter "<<name<<" already floating.  No parameter changes made." << std::endl;
	}
    } else if (name == "phiB") {
	if ( phiB_->fixed() ) {
	    phiB_->fixed( kFALSE );
	    this->addFloatingParameter( phiB_ );
	} else {
	    std::cerr << "WARNING in LauRhoOmegaMix::floatResonanceParameter: Parameter "<<name<<" already floating.  No parameter changes made." << std::endl;
	}
    } else if (name == "delta") {
	if ( delta_->fixed() ) {
	    delta_->fixed( kFALSE );
	    this->addFloatingParameter( delta_ );
	} else {
	    std::cerr << "WARNING in LauRhoOmegaMix::floatResonanceParameter: Parameter "<<name<<" already floating.  No parameter changes made." << std::endl;
	}
    }

}

LauParameter* LauRhoOmegaMix::getResonanceParameter(const TString& name) {

    if (name == "mOmega") {
	return mOmega_;
    } else if (name == "wOmega") {
	return wOmega_;
    } else if (name == "magB") {
	return magB_;
    } else if (name == "phiB") {
	return phiB_;
    } else if (name == "delta") {
	return delta_;
    } else {
	std::cerr << "WARNING in LauRhoOmegaMix::getResonanceParameter: Parameter name "<<name<<" not reconised." << std::endl;
	return 0;
    }
}

void LauRhoOmegaMix::setmOmegaValue(const Double_t mOmega) {
    mOmega_->value( mOmega );
    mOmega_->genValue( mOmega );
    mOmega_->initValue( mOmega );
}

void LauRhoOmegaMix::setwOmegaValue(const Double_t wOmega) {
    wOmega_->value( wOmega );
    wOmega_->genValue( wOmega );
    wOmega_->initValue( wOmega );
}

void LauRhoOmegaMix::setmagBValue(const Double_t magB) {
    magB_->value( magB );
    magB_->genValue( magB );
    magB_->initValue( magB );
}

void LauRhoOmegaMix::setphiBValue(const Double_t phiB) {
    phiB_->value( phiB );
    phiB_->genValue( phiB );
    phiB_->initValue( phiB );
}

void LauRhoOmegaMix::setdeltaValue(const Double_t delta) {
    delta_->value( delta );
    delta_->genValue( delta );
    delta_->initValue( delta );
}

