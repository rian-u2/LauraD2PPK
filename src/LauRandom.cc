
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRandom.cc
    \brief File containing implementation of LauRandom methods.
*/


#include "LauRandom.hh"

#include "TRandom3.h"

TRandom* LauRandom::randomFun()
{
	// Returns a pointer to a singleton random-number generator implementation.
	// Creates the object the first time it is called.

	static TRandom* theGenerator = 0;
	if (theGenerator == 0) {theGenerator = new TRandom3(65539);}
	return theGenerator;
}

TRandom* LauRandom::zeroSeedRandom()
{
	// Returns a pointer to a singleton random-number generator implementation.
	// Creates the object the first time it is called.

	static TRandom* theGenerator = 0;
	if (theGenerator == 0) {theGenerator = new TRandom3(0);}
	// Use TRandom3(0) to set seed from machine clock time (within +-1 sec).
	return theGenerator;
}

void LauRandom::setSeed(UInt_t seed)
{
	TRandom* theGenerator = randomFun();
	theGenerator->SetSeed(seed);
}

