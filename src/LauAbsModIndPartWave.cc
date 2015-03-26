
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsModIndPartWave.cc
    \brief File containing implementation of LauAbsModIndPartWave class.
*/

#include <cstdlib>
#include <iostream>

#include "TSpline.h"

#include "LauConstants.hh"
#include "LauKinematics.hh"
#include "LauAbsModIndPartWave.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauAbsModIndPartWave)


LauAbsModIndPartWave::LauAbsModIndPartWave(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
	nKnots_(0),
	spline1_(0),
	spline2_(0),
	secondStage_(kFALSE)
{
}

LauAbsModIndPartWave::~LauAbsModIndPartWave()
{
	delete spline1_;
	delete spline2_;
}

void LauAbsModIndPartWave::floatKnotsSecondStage(const Bool_t secondStage)
{
	secondStage_ = secondStage;

	// if the parameters have not yet been created we can now just return
	if ( amp1Pars_.size() != nKnots_ ) {
		return;
	}

	// otherwise we need to toggle their second-stage parameter
	for ( UInt_t i(0); i < nKnots_; ++i ) {
		amp1Pars_[i]->secondStage(secondStage_);
		amp2Pars_[i]->secondStage(secondStage_);
	}
}

void LauAbsModIndPartWave::defineKnots(const std::set<Double_t>& masses)
{
	if ( ! masses_.empty() ) {
		std::cerr << "WARNING in LauAbsModIndPartWave::defineKnots : Knot positions have already been defined, not making any changes." << std::endl;
		return;
	}

	const std::set<Double_t>::const_iterator first = masses.begin();
	const std::set<Double_t>::const_reverse_iterator last = masses.rbegin();

	const Double_t lower_limit = this->getMassDaug1() + this->getMassDaug2();
	const Double_t upper_limit = this->getMassParent() - this->getMassBachelor();

	if ( *first < lower_limit ) {
		std::cerr << "WARNING in LauAbsModIndPartWave::defineKnots : Knot found at mass " << *first << " is below the lower kinematic limit." << std::endl;
		std::cerr << "                                             : Lower kinematic limit is at mass " << lower_limit << std::endl;
		std::cerr << "                                             : Aborting definition of knot positions." << std::endl;
		return;
	}

	if ( *last > upper_limit ) {
		std::cerr << "WARNING in LauAbsModIndPartWave::defineKnots : Knot found at mass " << *last << " is above the upper kinematic limit." << std::endl;
		std::cerr << "                                             : Upper kinematic limit is at mass " << upper_limit << std::endl;
		std::cerr << "                                             : Aborting definition of knot positions." << std::endl;
		return;
	}

	Bool_t needLowerLimitKnot = (*first) != lower_limit;
	Bool_t needUpperLimitKnot = (*last)  != upper_limit;

	nKnots_ = masses.size();
	if ( needLowerLimitKnot ) {
		++nKnots_;
	}
	if ( needUpperLimitKnot ) {
		++nKnots_;
	}

	masses_.reserve(nKnots_);
	amp1Vals_.reserve(nKnots_);
	amp2Vals_.reserve(nKnots_);
	amp1Pars_.reserve(nKnots_);
	amp2Pars_.reserve(nKnots_);

	UInt_t counter(0);
	if ( needLowerLimitKnot ) {
		masses_.push_back( lower_limit );
		amp1Vals_.push_back(1.0);
		amp2Vals_.push_back(1.0);
		this->createAmpParameters(counter);
		++counter;
	}

	for ( std::set<Double_t>::const_iterator iter = masses.begin(); iter != masses.end(); ++iter ) {
		masses_.push_back( *iter );
		amp1Vals_.push_back(1.0);
		amp2Vals_.push_back(1.0);
		this->createAmpParameters(counter);
		++counter;
	}

	if ( needUpperLimitKnot ) {
		masses_.push_back( upper_limit );
		amp1Vals_.push_back(1.0);
		amp2Vals_.push_back(1.0);
		this->createAmpParameters(counter);
		++counter;
	}

	for ( std::vector<Double_t>::const_iterator iter = masses_.begin(); iter != masses_.end(); ++iter ) {
		std::cout << "INFO in LauAbsModIndPartWave::defineKnots : Knot added to resonance " << this->getResonanceName() << " at mass " << *iter << std::endl;
	}
}

void LauAbsModIndPartWave::initialise()
{
	if ( spline1_ != 0 ) {
		delete spline1_;
		spline1_ = 0;
	}
	if ( spline2_ != 0 ) {
		delete spline2_;
		spline2_ = 0;
	}

	for ( UInt_t i(0); i < nKnots_; ++i ) {
		amp1Vals_[i] = amp1Pars_[i]->value();
		amp2Vals_[i] = amp2Pars_[i]->value();
	}

	// TODO need to check that this is guaranteed to work by the standard
	Double_t* massVals = &masses_[0];
	Double_t* amp1Vals = &amp1Vals_[0];
	Double_t* amp2Vals = &amp2Vals_[0];

	spline1_ = new TSpline3("", massVals, amp1Vals, nKnots_);
	spline2_ = new TSpline3("", massVals, amp2Vals, nKnots_);
}

/*
void LauAbsModIndPartWave::addKnot(Double_t mass, Double_t magVal, Double_t phaseVal, Bool_t fixMag, Bool_t fixPhase)
{
	const TString & parNameBase = this->getSanitisedName();

	if(mass < this->getMassDaug1() + this->getMassDaug2()) {
		std::cerr << "WARNING in LauAbsModIndPartWave::addKnot : Knot at mass " << mass << " is below the lower kinematic limit and will not be added." << std::endl;
		std::cerr << "                                        Lower kinematic limit is at mass " << this->getMassDaug1() + this->getMassDaug2() << std::endl;
		return;
	}

	if(mass > this->getMassParent() - this->getMassBachelor()) {
		std::cerr << "WARNING in LauAbsModIndPartWave::addKnot : Knot at mass " << mass << " is above the upper kinematic limit and will not be added." << std::endl;
		std::cerr << "                                        Upper kinematic limit is at mass " << this->getMassParent() - this->getMassBachelor() << std::endl;
		return;
	}

	if(!masses_.empty() && masses_[nKnots_-1] >= mass) {
		std::cerr << "WARNING in LauAbsModIndPartWave::addKnot : Knots must be added in ascending order. Knot at mass " << mass << " has not been added." << std::endl;
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

	std::cout << "INFO in LauAbsModIndPartWave::addKnot : Knot added to resonance " << this->getResonanceName() << " at mass " << mass << std::endl;
	if(fixMag) std::cout << "                                     Magnitude fixed to " << magVal << std::endl;
	else std::cout << "                                     Magnitude set to " << magVal << std::endl;
	if(fixPhase) std::cout << "                                     Phase fixed to " << phaseVal << std::endl;
	else std::cout << "                                     Phase set to " << phaseVal << std::endl;

	++nKnots_;
}

void LauAbsModIndPartWave::setKnotAmp(Int_t knot, Double_t magVal, Double_t phaseVal, Bool_t fixMag, Bool_t fixPhase)
{

	//Out of range
	if(knot > nKnots_ || knot < -1) {
		std::cerr << "WARNING in LauAbsModIndPartWave::setKnotAmp : Index " << knot << " does not correspond to an existing knot in resonance " << this->getResonanceName() << std::endl;
		std::cerr << "                                           Index must be in range -1 to " << nKnots_-1 << std::endl;
		return;
	}

	//Special value to access upper threshold knot (only added during initialisation)
	if(knot == -1) {
		upperThresholdMag_ = magVal;
		upperThresholdPhase_ = phaseVal;
		fixUpperThresholdMag_ = fixMag;
		fixUpperThresholdPhase_ = fixPhase;

		std::cout << "INFO in LauAbsModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at upper kinematic threshold" << std::endl;
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

		if(knot == 0) std::cout << "INFO in LauAbsModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at lower kinematic threshold" << std::endl;
		else std::cout << "INFO in LauAbsModIndPartWave::setKnotAmp : Knot updated in resonance " << this->getResonanceName() << " at mass " << masses_[knot] << std::endl;
		if(fixMag) std::cout << "                                        Magnitude fixed to " << magVal << std::endl;
		else std::cout << "                                        Magnitude set to " << magVal << std::endl;
		if(fixPhase) std::cout << "                                        Phase fixed to " << phaseVal << std::endl;
		else std::cout << "                                        Phase set to " << phaseVal << std::endl;
	}
}
*/

LauComplex LauAbsModIndPartWave::resAmp(Double_t mass, Double_t spinTerm)
{
	amp_.zero();

	Bool_t paramChanged(kFALSE);

	for ( UInt_t i(0); i < nKnots_; ++i ) {
		if ( !amp1Pars_[i]->fixed() && amp1Pars_[i]->value() != amp1Vals_[i] ) {
			paramChanged = kTRUE;
			break;
		}
		if ( !amp2Pars_[i]->fixed() && amp2Pars_[i]->value() != amp2Vals_[i] ) {
			paramChanged = kTRUE;
			break;
		}
	}

	if ( paramChanged ) {
		this->initialise();
	}

	if ( spline1_ == 0 ||  spline2_ == 0) {
		std::cerr << "ERROR in LauAbsModIndPartWave::resAmp : One of the splines is null" << std::endl;
		return amp_;
	}

	this->evaluateAmplitude( mass );

	amp_.rescale( spinTerm );

	return amp_;
}

const std::vector<LauParameter*>& LauAbsModIndPartWave::getFloatingParameters()
{
	this->clearFloatingParameters();

	for ( UInt_t i(0); i < nKnots_; ++i ) {
		if ( !amp1Pars_[i]->fixed() ) {
			this->addFloatingParameter( amp1Pars_[i] );
		}
		if ( !amp2Pars_[i]->fixed() ) {
			this->addFloatingParameter( amp2Pars_[i] );
		}
	}

	return this->getParameters();
}

