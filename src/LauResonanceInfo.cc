
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauResonanceInfo.cc
    \brief File containing implementation of LauResonanceInfo class.
*/

#include "LauResonanceInfo.hh"

ClassImp(LauResonanceInfo)


LauResonanceInfo::LauResonanceInfo(const TString& name, Double_t mass, Double_t width, Int_t spin, Int_t charge, Double_t range) :
	name_(name),
	mass_(mass),
	width_(width),
	spin_(spin),
	charge_(charge),
	range_(range)
{
}

