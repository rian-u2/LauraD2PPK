
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitter.hh
    \brief File containing LauFitter namespace.
*/

/*! \namespace LauFitter
    \brief Namespace for holding the fitter

    Namespace that holds the fitter returning a pointer to a TVirtualFitter object.
*/

#ifndef LAU_FITTER
#define LAU_FITTER

#include "Rtypes.h"
#include "TString.h"

class TVirtualFitter;

namespace LauFitter {

	//! Method that provides a pointer to a TVirtualFitter object
	/*!
	    Arguments are ignored except for very first call
	    \param [in] fitterString the name of the default fitter (default set to Minuit)
	    \param [in] maxPar the maximum number of fit parameters for current fitter (default set to 100)
	    \return a pointer to a singleton TVirtualFitter object 
	*/
	TVirtualFitter* fitter( const TString& fitterString = "Minuit", Int_t maxPar = 100 );

};

#endif
