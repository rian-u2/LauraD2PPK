
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsIncohRes.cc
  \brief File containing implementation of LauAbsIncohRes class.
 */

#include "LauAbsIncohRes.hh"
#include "LauDaughters.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauAbsIncohRes)


// Constructor
LauAbsIncohRes::LauAbsIncohRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters)
	{}

// Destructor
LauAbsIncohRes::~LauAbsIncohRes()
{
}

LauComplex LauAbsIncohRes::resAmp(Double_t /*mass*/, Double_t spinTerm)
{
	return LauComplex(spinTerm, 0.0);
}
