
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

#include "TString.h"

#include "LauAbsCoeffSet.hh"
#include "LauParameter.hh"

ClassImp(LauAbsCoeffSet)


LauAbsCoeffSet::LauAbsCoeffSet(const TString& theName) :
	name_(theName),
	basename_("A"),
	index_(0)
{
}

void LauAbsCoeffSet::index(UInt_t newIndex)
{
	index_ = newIndex;
	TString basename("A");
	basename += newIndex;
	basename += "_";
	this->baseName(basename);

	std::vector<LauParameter*> pars = this->getParameters();
	for ( std::vector<LauParameter*>::iterator iter = pars.begin(); iter != pars.end(); ++iter ) {
		this->adjustName( *iter );
	}
}

void LauAbsCoeffSet::adjustName(LauParameter& par)
{
	TString theName(par.name());
	theName.Remove(0,theName.Index("_")+1);
	theName.Prepend(this->baseName());
	par.name(theName);
}

void LauAbsCoeffSet::adjustName(LauParameter* par)
{
	TString theName(par->name());
	theName.Remove(0,theName.Index("_")+1);
	theName.Prepend(this->baseName());
	par->name(theName);
}

