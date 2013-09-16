
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPrint.cc
    \brief File containing implementation of LauPrint class.
*/

#include <iostream>

#include "TMath.h"

#include "LauPrint.hh"

ClassImp(LauPrint)


LauPrint::LauPrint()
{
}

LauPrint::~LauPrint()
{
}

void LauPrint::printFormat(std::ostream& stream, Double_t value) const
{
	// Print double value to a specified level of precision
	char* string = new char[100];

	if (TMath::Abs(value) < 1e-30) {
		sprintf(string, "%5.3f", 0.0);
	} else if (TMath::Abs(value) < 0.01) {
		sprintf(string, "%5.3e", value);
	} else if (TMath::Abs(value) < 0.1) {
		sprintf(string, "%5.3f", value);
	} else {
		sprintf(string, "%5.3f", value);
	}

	stream<<string;

	delete[] string; string = 0;
}

