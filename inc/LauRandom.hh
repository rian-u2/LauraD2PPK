
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRandom.hh
    \brief File containing LauRandom namespace.
*/

/*! \namespace LauRandom
    \brief Namespace for holding the random number generator functions.

    Holds one generator with a given (changable) seed and one where the seed is taken from the machine clock.
*/

#ifndef LAU_RANDOM
#define LAU_RANDOM

#include "Rtypes.h"

class TRandom;

namespace LauRandom {

	//! Access the singleton random number generator with a particular seed
	/*!
	    The seed value can be set using LauRandom::setSeed

	    \return pointer to the singleton random number generator
	*/
	TRandom* randomFun();

	//! Access the singleton random number generator with seed set from machine clock time (within +-1 sec).
	/*!
	    \return pointer to the singleton random number generator
	*/
	TRandom* zeroSeedRandom();

	//! Set seed of random-number generator to a given value
	/*!
	    \param [in] seed the seed to be used in the generation
	*/
	void setSeed(UInt_t seed);

}

#endif
