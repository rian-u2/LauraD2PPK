
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

#include <iostream>

#include "LauFitter.hh"
#include "LauAbsFitter.hh"
#include "LauMinuit.hh"

LauAbsFitter* LauFitter::theInstance_ = 0;
LauFitter::Type LauFitter::fitterType_ = LauFitter::Minuit;

void LauFitter::setFitterType( Type type )
{
	if ( theInstance_ != 0 ) {
		std::cerr << "ERROR in LauFitter::setFitterType : The fitter has already been created, cannot change the type now." << std::endl;
		return;
	}

	fitterType_ = type;
}

LauAbsFitter* LauFitter::fitter()
{
	// Returns a pointer to a singleton LauAbsFitter object.
	// Creates the object the first time it is called.

	if ( theInstance_ == 0 ) {
		if ( fitterType_ == Minuit ) {
			theInstance_ = new LauMinuit();
		}
	}

	return theInstance_;
}

