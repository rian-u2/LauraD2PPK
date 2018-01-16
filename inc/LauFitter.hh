
/*
Copyright 2005 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauFitter.hh
    \brief File containing declaration of LauFitter class.
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
