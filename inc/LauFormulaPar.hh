
// Copyright University of Warwick 2013 - 2014.
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
#include "LauAbsRValue.hh"
#include "LauParameter.hh"


class LauFormulaPar : public LauAbsRValue {

	public:
		//! Constructor
		/*!
		  \param [in] forName the name of the formula
		  \param [in] formula the desired expression, using TFormula syntax
		  \param [in] params a vector of LauParameters used in the formula
		*/
		LauFormulaPar(const TString& forName, const TString& formula, const std::vector<LauParameter*>& params);

		// Destructor
		virtual ~LauFormulaPar();

		//! Copy constructor
		LauFormulaPar(const LauFormulaPar& rhs);

		//! Copy assignment operator
		LauFormulaPar& operator=(const LauFormulaPar& rhs);

		//! Return the value of the LauFormalaPar
		/*!
		  \return the value of the formula
		*/
		Double_t value() const;

		//! The parameter name
		/*!
		  \return the name of the parameter
		*/
		inline const TString& name() const {return name_;}

		//! Get the LauParameters used in LauFormulaPar
		/*!
		  \return the list of LauParameters
		*/
		std::vector<LauParameter*> getPars() {return paramVec_;}

		//! Boolean to say it is not an L value
		/*!
		  \return kFALSE, LauFormulaPars are not L values
		*/
		inline Bool_t isLValue() const {return kFALSE;}

		//! Boolean to say if the LauFormulaPar is fixed
		/*!
		  \return kFALSE unless all LauParameters in the formula are fixed
		*/
		Bool_t fixed() const;

		//! Check whether a Gaussian constraints is applied
		/*!
		  \return the boolean flag true/false whether a Gaussian constraint is applied
		*/
		inline Bool_t gaussConstraint() const {return gaussConstraint_;}

		//! The mean of the Gaussian constraint
		/*!
		  \return the mean value of the Gaussian constraint
		*/
		inline Double_t constraintMean() const {return constraintMean_;}

		//! The width of the Gaussian constraint
		/*!
		  \return the width of the Gaussian constraint
		*/
		inline Double_t constraintWidth() const {return constraintWidth_;}

		//! Add a Gaussian constraint (or modify an existing one)
		/*!
		  \param [in] newGaussMean the new value of the Gaussian constraint mean
		  \param [in] newGaussWidth the new value of the Gaussian constraint width
		*/
		void addGaussianConstraint(Double_t newGaussMean, Double_t newGaussWidth);

		//! Remove the Gaussian constraint
		void removeGaussianConstraint();

	protected:

	private:
		//! The parameter name
		TString name_;

		//! The formula
		mutable TFormula formula_;

		//! Vector of LauParameters in the formula
		std::vector<LauParameter*> paramVec_;

		//! Array 
		Double_t* dummy_;
		//! Array 
		Double_t* paramArray_;

		//! Choice to use Gaussian constraint
		Bool_t gaussConstraint_;
		//! Mean value of the Gaussian constraint
		Double_t constraintMean_;
		//! Width of the Gaussian constraint
		Double_t constraintWidth_;

		ClassDef(LauFormulaPar, 0)

};

#endif
