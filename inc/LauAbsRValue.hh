
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsRValue.hh
    \brief File containing declaration of LauAbsRValue class.
*/

/*! \class LauAbsRValue
    \brief Pure abstract base class for defining a parameter containing an R value

    Pure abstract base class for defining a parameter containing an R value, 
    either a LauParameter or a LauFormulaPar
*/

#ifndef LAU_ABSRVALUE
#define LAU_ABSRVALUE

#include <vector>

class LauParameter;

class LauAbsRValue {

	public:
		//!Constructor
		LauAbsRValue() {}

		//! Destructor
		virtual ~LauAbsRValue() {}

		//! Return the name of the parameter
		/*!
		    \return the name of the parameter
		*/
		virtual const TString& name() const =0;

		//! Return the value of the parameter
		/*!
		    \return the value of the parameter
		*/    
		virtual Double_t value() const =0;

		//! Return the list of LauParameters on which the LauAbsRValue depends
		/*!
		    \return the list of LauParameters
		*/    
		virtual std::vector<LauParameter*> getPars() =0;

		//! Is the parameter also an L value or not
		/*!
		    \return whether the parameter is also an L value
		*/    
		virtual Bool_t isLValue() const =0;

		//! Check is the parameter is fixed or floated
		/*!
		    \return the boolean flag whether the parameter is fixed
		*/    
		virtual Bool_t fixed() const =0;


	private:

		ClassDef(LauAbsRValue,0) // Abstract base class for R parameters
};

#endif
