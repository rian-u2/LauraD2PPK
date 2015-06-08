
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
		//! Constructor
		LauAbsRValue() {}

		//! Destructor
		virtual ~LauAbsRValue() {}

		//! Copy constructor
		LauAbsRValue(const LauAbsRValue& /*rhs*/) {}

		//! Copy assignment operator
		LauAbsRValue& operator=(const LauAbsRValue& /*rhs*/) {return *this;}

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

		//! The unblinded value of the parameter
		/*!
		  \return the unblinded value of the parameter
		*/
		virtual Double_t unblindValue() const =0;

		//! Check whether a Gaussian constraints is applied
		/*!
		  \return the boolean flag true/false whether a Gaussian constraint is applied
		*/
		virtual Bool_t gaussConstraint() const =0;

		//! The mean of the Gaussian constraint
		/*!
		  \return the mean value of the Gaussian constraint
		*/
		virtual Double_t constraintMean() const =0;

		//! The width of the Gaussian constraint
		/*!
		  \return the width of the Gaussian constraint
		*/
		virtual Double_t constraintWidth() const =0;

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

		ClassDef(LauAbsRValue,1) // Abstract base class for R parameters
};

#endif
