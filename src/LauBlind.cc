
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


void LauBlind::calcOffset(const TString blindingString, const Int_t width) {
	//hash the blinding string to obtain a seed
	TRandom3 r(TMath::Hash(blindingString));
	//offsets are Gaussian distributed with defined width
	offset_ = width*r.Gaus();
}
