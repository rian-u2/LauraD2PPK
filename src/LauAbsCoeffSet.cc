
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsCoeffSet.cc
    \brief File containing implementation of LauAbsCoeffSet class.
*/

#include <iostream>

#include "TString.h"

#include "LauAbsCoeffSet.hh"
#include "LauConstants.hh"
#include "LauParameter.hh"

ClassImp(LauAbsCoeffSet);

Double_t LauAbsCoeffSet::minMagnitude_ = -10.0;
Double_t LauAbsCoeffSet::maxMagnitude_ =  10.0;
Double_t LauAbsCoeffSet::minPhase_ = -LauConstants::threePi;
Double_t LauAbsCoeffSet::maxPhase_ =  LauConstants::threePi;
Double_t LauAbsCoeffSet::minRealImagPart_ = -10.0;
Double_t LauAbsCoeffSet::maxRealImagPart_ =  10.0;
Double_t LauAbsCoeffSet::minDelta_ = -2.0;
Double_t LauAbsCoeffSet::maxDelta_ =  2.0;

LauAbsCoeffSet::LauAbsCoeffSet(const TString& theName, const TString& theBaseName) :
	name_(theName),
	basename_(theBaseName),
	index_(0)
{
}

LauAbsCoeffSet::LauAbsCoeffSet(const LauAbsCoeffSet& rhs) :
	name_(rhs.name_),
	basename_(rhs.basename_),
	index_(rhs.index_)
{
}

LauAbsCoeffSet& LauAbsCoeffSet::operator=(const LauAbsCoeffSet& rhs)
{
	if ( &rhs != this ) {
		name_ = rhs.name_;
		basename_ = rhs.basename_;
		index_ = rhs.index_;
	}
	return *this;
}

void LauAbsCoeffSet::index(UInt_t newIndex)
{
	index_ = newIndex;

	TString basename( this->baseName() );
	if ( basename.Length() != 1 ) {
		basename.Remove(1);
	}
	basename += newIndex;
	basename += "_";
	this->baseName(basename);

	std::vector<LauParameter*> pars = this->getParameters();
	for ( std::vector<LauParameter*>::iterator iter = pars.begin(); iter != pars.end(); ++iter ) {
		this->adjustName( *iter );
	}
}

void LauAbsCoeffSet::adjustName(LauParameter* par)
{
	TString theName(par->name());
	theName.Remove(0,theName.Index("_")+1);
	theName.Prepend(this->baseName());
	par->name(theName);
}

void LauAbsCoeffSet::setParameterValue(const TString& parName, Double_t value, Bool_t init)
{
	LauParameter* par = this->findParameter( parName );
	if ( par == 0 ) {
		std::cerr << "ERROR in LauAbsCoeffSet::setParameterValue : Unable to find parameter \"" << parName << "\"" << std::endl;
		return;
	}

	par->value( value );
	if ( init ) {
		par->genValue( value );
		par->initValue( value );
	}
}

void LauAbsCoeffSet::fixParameter(const TString& parName)
{
	LauParameter* par = this->findParameter( parName );
	if ( par == 0 ) {
		std::cerr << "ERROR in LauAbsCoeffSet::fixParameter : Unable to find parameter \"" << parName << "\"" << std::endl;
		return;
	}

	par->fixed( kTRUE );
}

void LauAbsCoeffSet::floatParameter(const TString& parName)
{
	LauParameter* par = this->findParameter( parName );
	if ( par == 0 ) {
		std::cerr << "ERROR in LauAbsCoeffSet::floatParameter : Unable to find parameter \"" << parName << "\"" << std::endl;
		return;
	}

	par->fixed( kFALSE );
}

LauParameter* LauAbsCoeffSet::findParameter(const TString& parName)
{
	std::vector<LauParameter*> pars = this->getParameters();
	for ( std::vector<LauParameter*>::iterator iter = pars.begin(); iter != pars.end(); ++iter ) {

		const TString& iName = (*iter)->name();

		if ( iName.EndsWith( parName ) ) {
			return (*iter);
		}
	}

	return 0;
}

