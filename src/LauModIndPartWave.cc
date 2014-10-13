
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWave.cc
    \brief File containing implementation of LauModIndPartWave class.
*/

//****************************************************************************
// Class for defining the model independent partial wave model
//****************************************************************************

// --CLASS DESCRIPTION [MODEL] --
// Class for defining the model independent partial wave model

#include <cstdlib>
#include <iostream>

#include "TSpline.h"

#include "LauConstants.hh"
#include "LauKinematics.hh"
#include "LauModIndPartWave.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauModIndPartWave)


LauModIndPartWave::LauModIndPartWave(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
  nKnots_(0),
  initialised_(kFALSE),
  upperThresholdMag_(0.01),
  upperThresholdPhase_(0.),
  fixUpperThresholdMag_(kFALSE),
  fixUpperThresholdPhase_(kFALSE)
{
  this->addKnot(this->getMassDaug1() + this->getMassDaug2(),0.01,0.0);
}

LauModIndPartWave::~LauModIndPartWave()
{
  if(magSpline_) delete magSpline_;
  if(phaseSpline_) delete phaseSpline_;

  std::vector<LauParameter*>::iterator it = magnitudePars_.begin();
  std::vector<LauParameter*>::iterator end = magnitudePars_.end();

  for( ; it!=end; ++it) {
    if(*it) delete *it;
  }

  it = phasePars_.begin();
  end = phasePars_.end();

  for( ; it!=end; ++it) {
    if(*it) delete *it;
  }
}

void LauModIndPartWave::initialise()
{
  if(!initialised_) {
    //Use values for upper threshold knot that were set using setKnotAmp
    this->addKnot(this->getMassParent() - this->getMassBachelor(),upperThresholdMag_,upperThresholdPhase_, fixUpperThresholdMag_, fixUpperThresholdPhase_);
    initialised_ = kTRUE;
  }
  if(magSpline_!=0) {
    delete magSpline_;
    magSpline_=0;
  }
  if(phaseSpline_!=0) {
    delete phaseSpline_;
    phaseSpline_=0;
	}

  for(Int_t i=0; i<nKnots_; ++i) {
    magnitudes_[i] = magnitudePars_[i]->value();
    phases_[i] = phasePars_[i]->value();
  }

  Double_t* massVals  = &masses_[0];
  Double_t* magVals   = &magnitudes_[0];
  Double_t* phaseVals = &phases_[0];

  magSpline_   = new TSpline3("", massVals, magVals,   nKnots_);
  phaseSpline_ = new TSpline3("", massVals, phaseVals, nKnots_);
}

void LauModIndPartWave::addKnot(Double_t mass, Double_t magVal, Double_t phaseVal, Bool_t fixMag, Bool_t fixPhase) {
  const TString & parNameBase = this->getSanitisedName();

  if(mass < this->getMassDaug1() + this->getMassDaug2()) {
    std::cerr << "WARNING in LauModIndPartWave::addKnot : Knot at mass " << mass << " is below the lower kinematic limit and will not be added." << std::endl;
    std::cerr << "                                        Lower kinematic limit is at mass " << this->getMassDaug1() + this->getMassDaug2() << std::endl;
    return;
  }

  if(mass > this->getMassParent() - this->getMassBachelor()) {
    std::cerr << "WARNING in LauModIndPartWave::addKnot : Knot at mass " << mass << " is above the upper kinematic limit and will not be added." << std::endl;
    std::cerr << "                                        Upper kinematic limit is at mass " << this->getMassParent() - this->getMassBachelor() << std::endl;
    return;
  }

  if(!masses_.empty() && masses_[nKnots_-1] >= mass) {
    std::cerr << "WARNING in LauModIndPartWave::addKnot : Knots must be added in ascending order. Knot at mass " << mass << " has not been added." << std::endl;
    std::cerr << "                                        Highest existing knot has mass " << masses_[nKnots_-1] << std::endl;
    return;
  }

  masses_.push_back(mass);
  magnitudes_.push_back(magVal);
  phases_.push_back(phaseVal);

  TString magName(parNameBase);
  magName+="_A";
  magName+=nKnots_;

  magnitudePars_.push_back(this->getResInfo()->getExtraParameter( magName ));
  if( magnitudePars_[nKnots_] == 0) {
    magnitudePars_[nKnots_] = new LauParameter( magName, magVal, 0.0, 10.0, fixMag);
    magnitudePars_[nKnots_]->secondStage(kTRUE);
    this->getResInfo()->addExtraParameter(magnitudePars_[nKnots_]);
  }

  TString phaseName(parNameBase);
  phaseName+="_d";
  phaseName+=nKnots_;

  phasePars_.push_back(this->getResInfo()->getExtraParameter( phaseName ));
  if( phasePars_[nKnots_] == 0) {
    phasePars_[nKnots_] = new LauParameter( phaseName, phaseVal, -6.0*LauConstants::pi, 6.0*LauConstants::pi, fixPhase);
    phasePars_[nKnots_]->secondStage(kTRUE);
    this->getResInfo()->addExtraParameter(phasePars_[nKnots_]);
  }

  std::cout << "INFO in LauModIndPartWave::addKnot : Knot added to resonance " << this->getResonanceName() << " at mass " << mass << std::endl;
  if(fixMag) std::cout << "                                     Magnitude fixed to " << magVal << std::endl;
  else std::cout << "                                     Magnitude set to " << magVal << std::endl;
  if(fixPhase) std::cout << "                                     Phase fixed to " << phaseVal << std::endl;
  else std::cout << "                                     Phase set to " << phaseVal << std::endl;

  ++nKnots_;
}

void LauModIndPartWave::setKnotAmp(Int_t knot, Double_t magVal, Double_t phaseVal, Bool_t fixMag, Bool_t fixPhase) {

  //Out of range
  if(knot > nKnots_ || knot < -1) {
    std::cerr << "WARNING in LauModIndPartWave::setKnotAmp : Index " << knot << " does not correspond to an existing knot in resonance " << this->getResonanceName() << std::endl;
    std::cerr << "                                           Index must be in range -1 to " << nKnots_-1 << std::endl;
    return;
  }

  //Special value to access upper threshold knot (only added during initialisation)
  if(knot == -1) {
    upperThresholdMag_ = magVal;
    upperThresholdPhase_ = phaseVal;
    fixUpperThresholdMag_ = fixMag;
    fixUpperThresholdPhase_ = fixPhase;

    std::cout << "INFO in LauModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at upper kinematic threshold" << std::endl;
    if(fixMag) std::cout << "                                        Magnitude fixed to " << magVal << std::endl;
    else std::cout << "                                        Magnitude set to " << magVal << std::endl;
    if(fixPhase) std::cout << "                                        Phase fixed to " << phaseVal << std::endl;
    else std::cout << "                                        Phase set to " << phaseVal << std::endl;
  }

  //Otherwise edit the values directly
  else {
    magnitudes_[knot] = magVal;
    magnitudePars_[knot]->value(magVal);
    magnitudePars_[knot]->genValue(magVal);
    magnitudePars_[knot]->initValue(magVal);
    magnitudePars_[knot]->fixed(fixMag);
    phases_[knot] = phaseVal;
    phasePars_[knot]->value(phaseVal);
    phasePars_[knot]->genValue(phaseVal);
    phasePars_[knot]->initValue(phaseVal);
    phasePars_[knot]->fixed(fixPhase);

    if(knot == 0) std::cout << "INFO in LauModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at lower kinematic threshold" << std::endl;
    else std::cout << "INFO in LauModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at mass " << masses_[knot] << std::endl;
    if(fixMag) std::cout << "                                        Magnitude fixed to " << magVal << std::endl;
    else std::cout << "                                        Magnitude set to " << magVal << std::endl;
    if(fixPhase) std::cout << "                                        Phase fixed to " << phaseVal << std::endl;
    else std::cout << "                                        Phase set to " << phaseVal << std::endl;
  }
}

LauComplex LauModIndPartWave::resAmp(Double_t mass, Double_t spinTerm)
{
  LauComplex amp(0.0, 0.0);

  Bool_t paramChanged(kFALSE);

  for(Int_t i=0; i<nKnots_; ++i) {
    if(!magnitudePars_[i]->fixed() && magnitudePars_[i]->value() != magnitudes_[i]) {
      paramChanged = kTRUE;
      break;
    }
    if(!phasePars_[i]->fixed() && phasePars_[i]->value() != phases_[i]) {
      paramChanged = kTRUE;
      break;
    }
  }

  if(paramChanged) this->initialise();

  if (magSpline_ == 0 || phaseSpline_ == 0) {
    std::cerr << "ERROR in LauModIndPartWave::amplitude : One of the splines is null" << std::endl;
    return amp;
  }

  Double_t mag = magSpline_->Eval(mass);
  Double_t phase = phaseSpline_->Eval(mass);
  LauComplex ff(mag*TMath::Cos(phase), mag*TMath::Sin(phase));

  amp = LauComplex(spinTerm,0.)*ff;

  return amp;

}

const std::vector<LauParameter*>& LauModIndPartWave::getFloatingParameters() {
  this->clearFloatingParameters();

  for(Int_t i=0; i<nKnots_; ++i) {
    if(!magnitudePars_[i]->fixed()) {
      this->addFloatingParameter( magnitudePars_[i] );
    }
    if(!phasePars_[i]->fixed()) {
      this->addFloatingParameter( phasePars_[i] );
    }
  }

  return this->getParameters();
}
