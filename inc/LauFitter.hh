
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

class LauAbsFitter;

class LauFitter {

	public:
		//! The types of fitter available
		enum Type {
			Minuit	/*!< the Minuit fitter */
		};

		//! Set the type of the fitter
		/*!
		  \param [in] type the type of the fitter (default set to Minuit)
		*/
		static void setFitterType( Type type );

		//! Method that provides access to the singleton fitter
		/*!
		    \return a pointer to a singleton LauAbsFitter object 
		*/
		static LauAbsFitter* fitter();

		virtual ~LauFitter();

	private:
		//! Pointer to the singleton instance
		static LauAbsFitter* theInstance_;

		//! The fitter type
		static Type fitterType_;

		ClassDef(LauFitter,0);
};

#endif
