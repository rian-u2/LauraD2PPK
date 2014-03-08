
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauParameter.cc
    \brief File containing implementation of LauParameter class.
*/

#include <iostream>
#include <map>
using std::cout;
using std::cerr;
using std::endl;
using std::map;

#include "TRandom.h"

#include "LauParameter.hh"
#include "LauRandom.hh"

ClassImp(LauParameter)


LauParameter::LauParameter() :
	name_(""),
	value_(0.0),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(0.0),
	initValue_(0.0),
	minValue_(0.0),
	maxValue_(0.0),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
}

LauParameter::LauParameter(const TString& parName) :
	name_(parName),
	value_(0.0),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(0.0),
	initValue_(0.0),
	minValue_(0.0),
	maxValue_(0.0),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
}

LauParameter::LauParameter(Double_t parValue) :
	name_(""),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(parValue-1e-6),
	maxValue_(parValue+1e-6),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
}

LauParameter::LauParameter(const TString& parName, Double_t parValue) :
	name_(parName),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(parValue-1e-6),
	maxValue_(parValue+1e-6),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
}

LauParameter::LauParameter(Double_t parValue, Double_t min, Double_t max) :
	name_(""),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(Double_t parValue, Double_t parError, Double_t min, Double_t max) :
	name_(""),
	value_(parValue),
	error_(parError),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(Double_t parValue, Double_t min, Double_t max, Bool_t parFixed) :
	name_(""),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(parFixed),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(const TString& parName, Double_t parValue, Double_t min, Double_t max) :
	name_(parName),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(const TString& parName, Double_t parValue, Double_t min, Double_t max, Bool_t parFixed) :
	name_(parName),
	value_(parValue),
	error_(0.0),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(parFixed),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(const TString& parName, Double_t parValue, Double_t parError, Double_t min, Double_t max) :
	name_(parName),
	value_(parValue),
	error_(parError),
	negError_(0.0),
	posError_(0.0),
	genValue_(parValue),
	initValue_(parValue),
	minValue_(min),
	maxValue_(max),
	fixed_(kTRUE),
	firstStage_(kFALSE),
	secondStage_(kFALSE),
	gaussConstraint_(kFALSE),
	constraintMean_(0.0),
	constraintWidth_(0.0),
	gcc_(0.0),
	bias_(0.0),
	pull_(0.0),
	clone_(kFALSE),
	parent_(0)
{
	this->checkRange();
}

LauParameter::LauParameter(const LauParameter& rhs) : TObject(rhs)
{
	this->name(rhs.name());
	this->valueAndRange(rhs.value(), rhs.minValue(), rhs.maxValue());
	this->genValue(rhs.genValue());
	this->initValue(rhs.initValue());
	this->fixed(rhs.fixed());
	this->firstStage(rhs.firstStage());
	this->secondStage(rhs.secondStage());
	if ( rhs.gaussConstraint() ) {
		this->addGaussianConstraint( rhs.constraintMean(), rhs.constraintWidth() );
	} else {
		this->removeGaussianConstraint();
	}
	this->errors(rhs.error(), rhs.negError(), rhs.posError());
	this->globalCorrelationCoeff( rhs.globalCorrelationCoeff() );
	this->clone(rhs.parent());
	clones_ = rhs.clones_;
	this->updatePull();
}

LauParameter& LauParameter::operator=(const LauParameter& rhs)
{
	if (&rhs != this) {
		TObject::operator=(rhs);
		this->name(rhs.name());
		this->valueAndRange(rhs.value(), rhs.minValue(), rhs.maxValue());
		this->genValue(rhs.genValue());
		this->initValue(rhs.initValue());
		this->fixed(rhs.fixed());
		this->firstStage(rhs.firstStage());
		this->secondStage(rhs.secondStage());
		if ( rhs.gaussConstraint() ) {
			this->addGaussianConstraint( rhs.constraintMean(), rhs.constraintWidth() );
		} else {
			this->removeGaussianConstraint();
		}
		this->errors(rhs.error(), rhs.negError(), rhs.posError());
		this->globalCorrelationCoeff( rhs.globalCorrelationCoeff() );
		this->clone(rhs.parent());
		clones_ = rhs.clones_;
		this->updatePull();
	}
	return *this;
}

void LauParameter::value(Double_t newValue)
{
	this->checkRange(newValue,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
}

void LauParameter::error(Double_t newError)
{
	error_ = TMath::Abs(newError);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::negError(Double_t newNegError)
{
	negError_ = TMath::Abs(newNegError);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::posError(Double_t newPosError)
{
	posError_ = TMath::Abs(newPosError);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::errors(Double_t newError, Double_t newNegError, Double_t newPosError)
{
	error_ = TMath::Abs(newError);
	negError_ = TMath::Abs(newNegError);
	posError_ = TMath::Abs(newPosError);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::valueAndErrors(Double_t newValue, Double_t newError, Double_t newNegError, Double_t newPosError)
{
	this->checkRange(newValue,this->minValue(),this->maxValue());
	error_ = TMath::Abs(newError);
	negError_ = TMath::Abs(newNegError);
	posError_ = TMath::Abs(newPosError);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::globalCorrelationCoeff(Double_t newGCCValue)
{
	gcc_ = newGCCValue;
}

void LauParameter::genValue(Double_t newGenValue)
{
	genValue_ = newGenValue;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::initValue(Double_t newInitValue)
{
	initValue_ = newInitValue;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::minValue(Double_t newMinValue)
{
	this->checkRange(this->value(),newMinValue,this->maxValue());
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::maxValue(Double_t newMaxValue)
{
	this->checkRange(this->value(),this->minValue(),newMaxValue);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::range(Double_t newMinValue, Double_t newMaxValue)
{
	this->checkRange(this->value(),newMinValue,newMaxValue);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::valueAndRange(Double_t newValue, Double_t newMinValue, Double_t newMaxValue)
{
	this->checkRange(newValue,newMinValue,newMaxValue);
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::name(const TString& newName)
{
	// no need to update clones here
	// clones are allowed to have different names
	name_ = newName;
}

void LauParameter::fixed(Bool_t parFixed)
{
	fixed_ = parFixed;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::firstStage(Bool_t firstStagePar)
{
	firstStage_ = firstStagePar;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::secondStage(Bool_t secondStagePar)
{
	secondStage_ = secondStagePar;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::addGaussianConstraint(Double_t newGaussMean, Double_t newGaussWidth)
{
	gaussConstraint_ = kTRUE;
	constraintMean_ = newGaussMean;
	constraintWidth_ = newGaussWidth;
	if (!this->clone()) {
		this->updateClones();
	}
}

void LauParameter::removeGaussianConstraint()
{
	gaussConstraint_ = kFALSE;
	if (!this->clone()) {
		this->updateClones();
	}
}

LauParameter& LauParameter::operator = (Double_t val)
{
	this->checkRange(val,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
	return *this;
}

LauParameter& LauParameter::operator += (Double_t val)
{
	this->checkRange(this->value()+val,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
	return *this;
}

LauParameter& LauParameter::operator -= (Double_t val)
{
	this->checkRange(this->value()-val,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
	return *this;
}

LauParameter& LauParameter::operator *= (Double_t val)
{
	this->checkRange(this->value()*val,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
	return *this;
}

LauParameter& LauParameter::operator /= (Double_t val)
{
	this->checkRange(this->value()/val,this->minValue(),this->maxValue());
	if (!this->clone()) {
		this->updateClones(kTRUE);
	}
	return *this;
}

void LauParameter::updatePull()
{
	// calculate the bias
	bias_ = value_ - genValue_;

	// if we have errors calculated then calculate
	// the pull using the best error available
	if ((bias_ > 0.0) && (negError_ > 1e-10)) {
		pull_ = bias_ / negError_;
	} else if ((bias_ < 0.0) && (posError_ > 1e-10)) {
		pull_ = bias_ / posError_;
	} else if (error_ > 1e-10) {
		pull_ = bias_ / error_;
	} else {
		pull_ = 0.0;
	}
}

void LauParameter::checkRange(Double_t val, Double_t minVal, Double_t maxVal)
{
	// first check that min is less than max (or they are the same - this is allowed)
	if (minVal > maxVal) {
		cerr<<"ERROR in LauParameter::checkRange : minValue: "<<minVal<<" greater than maxValue: "<<maxVal<<endl;
		if (minValue_ > maxValue_) {
			minValue_ = maxValue_;
			cerr<<"                                  : Setting both to "<<maxValue_<<"."<<endl;
		} else {
			cerr<<"                                  : Not changing anything."<<endl;
		}
		return;
	}

	minValue_ = minVal;
	maxValue_ = maxVal;

	// now check that the value is still within the range
	if ((val < minVal) || (val > maxVal)) {
		if (name_ != "") {
			cerr<<"ERROR in LauParameter::checkRange : value: "<<val<<" not in allowed range ["<<minVal<<" , "<<maxVal<<"] for parameter \""<<name_<<"\"."<<endl;
		} else {
			cerr<<"ERROR in LauParameter::checkRange : value: "<<val<<" not in allowed range ["<<minVal<<" , "<<maxVal<<"]."<<endl;
		}
		if (val < minVal) {
			cerr<<"                                  : Setting value to minValue: "<<minVal<<endl;
			val = minVal;
		} else {
			cerr<<"                                  : Setting value to maxValue: "<<maxVal<<endl;
			val = maxVal;
		}
	}
	value_ = val;
}

LauParameter* LauParameter::createClone(Double_t constFactor)
{
	// if we're a clone we mustn't be cloned ourselves
	// but instead return another clone of our parent
	// (this is so that the parent knows of all its clones)
	if (this->clone()) {
		LauParameter* clonePar = parent_->createClone(constFactor);
		clonePar->name(this->name());
		return clonePar;
	}

	// clone ourselves using the copy-constructor
	LauParameter* clonePar = new LauParameter(*this);
	(*clonePar) *= constFactor;
	clonePar->wipeClones();
	clonePar->clone(this);
	clones_.insert( std::make_pair( clonePar, constFactor ) );
	return clonePar;
}

LauParameter* LauParameter::createClone(const TString& newName, Double_t constFactor)
{
	// self message to create the clone
	LauParameter* clonePar = this->createClone(constFactor);
	// set the new name
	clonePar->name(newName);
	// and return
	return clonePar;
}

void LauParameter::updateClones(Bool_t justValue)
{
	if (justValue) {
		for (map<LauParameter*,Double_t>::iterator iter = clones_.begin(); iter != clones_.end(); ++iter) {
			LauParameter* clonePar = iter->first;
			Double_t constFactor = iter->second;
			clonePar->value(constFactor*this->value());
		}
	} else {
		for (map<LauParameter*,Double_t>::iterator iter = clones_.begin(); iter != clones_.end(); ++iter) {
			LauParameter* clonePar = iter->first;
			Double_t constFactor = iter->second;
			clonePar->valueAndRange(constFactor*this->value(),constFactor*this->minValue(),constFactor*this->maxValue());
			clonePar->errors(constFactor*this->error(),constFactor*this->negError(),constFactor*this->posError());
			clonePar->genValue(constFactor*this->genValue());
			clonePar->initValue(constFactor*this->initValue());
			clonePar->fixed(this->fixed());
			clonePar->firstStage(this->firstStage());
			clonePar->secondStage(this->secondStage());
			if ( this->gaussConstraint() ) {
				clonePar->addGaussianConstraint( this->constraintMean(), this->constraintWidth() );
			} else {
				clonePar->removeGaussianConstraint();
			}
		}
	}
}

void LauParameter::randomiseValue()
{
	this->randomiseValue(this->minValue(), this->maxValue());
}

void LauParameter::randomiseValue(Double_t minVal, Double_t maxVal)
{
	// if we're fixed then do nothing
	if (this->fixed()) {
		return;
	}
	// check supplied values are sensible
	if (maxVal < minVal) {
		cerr<<"ERROR in LauParameter::randomiseValue : Supplied maximum value smaller than minimum value."<<endl;
		return;
	}
	if (maxVal > this->maxValue()) {
		maxVal = this->maxValue();
	}
	if (minVal < this->minValue()) {
		minVal = this->minValue();
	}

	Double_t randNo = LauRandom::zeroSeedRandom()->Rndm();
	Double_t val = randNo*(maxVal - minVal) + minVal;
	this->initValue(val);
}

// various mathematical operators (non-member functions)
Double_t operator + (const LauParameter& lhs, Double_t rhs)
{
	return (lhs.value() + rhs);
}
Double_t operator + (Double_t lhs, const LauParameter& rhs)
{
	return (lhs + rhs.value());
}
Double_t operator + (const LauParameter& lhs, const LauParameter& rhs)
{
	return (lhs.value() + rhs.value());
}
Double_t operator - (const LauParameter& lhs, Double_t rhs)
{
	return (lhs.value() - rhs);
}
Double_t operator - (Double_t lhs, const LauParameter& rhs)
{
	return (lhs - rhs.value());
}
Double_t operator - (const LauParameter& lhs, const LauParameter& rhs)
{
	return (lhs.value() - rhs.value());
}
Double_t operator * (const LauParameter& lhs, Double_t rhs)
{
	return (lhs.value() * rhs);
}
Double_t operator * (Double_t lhs, const LauParameter& rhs)
{
	return (lhs * rhs.value());
}
Double_t operator * (const LauParameter& lhs, const LauParameter& rhs)
{
	return (lhs.value() * rhs.value());
}
Double_t operator / (const LauParameter& lhs, Double_t rhs)
{
	return (lhs.value() / rhs);
}
Double_t operator / (Double_t lhs, const LauParameter& rhs)
{
	return (lhs / rhs.value());
}
Double_t operator / (const LauParameter& lhs, const LauParameter& rhs)
{
	return (lhs.value() / rhs.value());
}
Double_t operator += (Double_t& lhs, const LauParameter& rhs)
{
	lhs += rhs.value();
	return lhs;
}
Double_t operator -= (Double_t& lhs, const LauParameter& rhs)
{
	lhs -= rhs.value();
	return lhs;
}
Double_t operator *= (Double_t& lhs, const LauParameter& rhs)
{
	lhs *= rhs.value();
	return lhs;
}
Double_t operator /= (Double_t& lhs, const LauParameter& rhs)
{
	lhs /= rhs.value();
	return lhs;
}

// ostream operator
ostream& operator << (ostream& stream, const LauParameter& par)
{
	stream << par.value();
	return stream;
}

