
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAsymmCalc.cc
    \brief File containing implementation of LauAsymmCalc class.
*/

#include "TMath.h"

#include "LauAsymmCalc.hh"

ClassImp(LauAsymmCalc)


LauAsymmCalc::LauAsymmCalc(Double_t negValue, Double_t posValue) :
	negValue_(negValue),
	posValue_(posValue),
	asymm_(0.0)
{
	asymm_ = calcAsymmetry();
}

LauAsymmCalc::~LauAsymmCalc()
{
}

Double_t LauAsymmCalc::calcAsymmetry()
{
	Double_t num = negValue_ - posValue_;
	Double_t denom = negValue_ + posValue_;
	Double_t asymm(0.0);
	if (TMath::Abs(denom) > 1e-10) {
		asymm = num/denom;
	}

	return asymm;
}

