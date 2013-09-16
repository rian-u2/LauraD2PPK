
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitter.cc
    \brief File containing implementation of LauFitter methods.
*/


#include "LauFitter.hh"

#include "TVirtualFitter.h"

TVirtualFitter* LauFitter::fitter( const TString& fitterString, Int_t maxPar )
{
	// Returns a pointer to a singleton TVirtualFitter object.
	// Creates the object the first time it is called.

	static TVirtualFitter* theFitter = 0;
	if ( theFitter == 0 ) {
		TVirtualFitter::SetDefaultFitter( fitterString );
		theFitter = TVirtualFitter::Fitter( 0, maxPar );
	}
	return theFitter;
}

