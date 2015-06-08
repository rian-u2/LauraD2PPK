
// Copyright University of Warwick 2006 - 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBlind.cc
    \brief File containing implementation of LauBlind class.
*/

#include "LauBlind.hh"

#include "TMath.h"
#include "TRandom3.h"

ClassImp(LauBlind)


LauBlind::LauBlind() :
	blindingString_(""),
	blindingWidth_(0.0),
	offset_(0.0)
{
}

LauBlind::LauBlind(const TString& blindingString, const Double_t width) :
	blindingString_(blindingString),
	blindingWidth_(width),
	offset_(0.0)
{
	this->calcOffset();
}

LauBlind::LauBlind(const LauBlind& rhs) :
	blindingString_(rhs.blindingString_),
	blindingWidth_(rhs.blindingWidth_),
	offset_(rhs.offset_)
{
}

LauBlind::~LauBlind()
{
}

void LauBlind::calcOffset()
{
	//hash the blinding string to obtain a seed
	TRandom3 r(TMath::Hash(blindingString_));

	//offsets are Gaussian distributed with defined width
	offset_ = blindingWidth_ * r.Gaus();
}

