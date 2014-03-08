
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFormulaPar.hh
    \brief File containing declaration of LauFormulaPar class.
*/

/*! \class LauFormulaPar
    \brief Class for defining combinations of fit parameter objects.

    Allows for combinations of LauParameters to be passed to the fit models.
    Equations of the form [0]*2 + 3*[1] are accepted, with a vector of LauParameters to define
    inputs [0] and [1]. The parameter for [0] must be stored first in the vector, and so on.
*/

#ifndef LAU_FORMULAPAR
#define LAU_FORMULAPAR

#include <map>
#include <vector>

#include "TString.h"
#include "TFormula.h"
#include "LauParameter.hh"


class LauFormulaPar {

	public:
		//! Constructor double limit parameter
		/*!
		    \param [in] forName the name of the formula
		    \param [in] formula the desired expression, using TFormula syntax
		    \param [in] params a vector of LauParameters used in the formula
		*/
		LauFormulaPar(const TString& forName, const TString& formula, const std::vector<LauParameter*>& params);

		// Destructor
		virtual ~LauFormulaPar();

		// Return the value of the LauFormalaPar
		/*!
	 	    \return the value of the formula
		*/
		Double_t value() const;
		
		//! The parameter name
		/*!
		    \return the name of the parameter
		*/
		inline const TString& name() const {return name_;}

	protected:

	private:
		//! The parameter name
		TString name_;

		//! The parameter name
		mutable TFormula formula_;

		//! Vector of LauParameters in the formula
		std::vector<LauParameter*> paramVec_;

		//! Array 
		Double_t* dummy_;

		//! Array 
		Double_t* paramArray_;

		ClassDef(LauFormulaPar, 0)

};

#endif
