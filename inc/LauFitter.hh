
// Copyright University of Warwick 2005 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitter.hh
    \brief File containing LauFitter class.
*/

/*! \class LauFitter
    \brief Factory class for creating and providing access to the fitter.

    The fitter type can be set before first access to determine which fitter is used.
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

	private:
		//! Constructor
		LauFitter() {}

		//! Destructor
		virtual ~LauFitter() {}

		//! Copy constructor (not implemented)
		LauFitter( const LauFitter& );

		//! Copy assignment operator (not implemented)
		LauFitter& operator=( const LauFitter& );

		//! Pointer to the singleton fitter instance
		static LauAbsFitter* theInstance_;

		//! The fitter type
		static Type fitterType_;

		ClassDef(LauFitter,0);
};

#endif
