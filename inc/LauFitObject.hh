
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitObject.hh
    \brief File containing declaration of LauFitObject class.
*/

/*! \class LauFitObject
    \brief The abstract interface for the objects that control the calculation of the likelihood.
*/

#ifndef LAU_FIT_OBJECT
#define LAU_FIT_OBJECT

#include "TObject.h"
#include "TVirtualFitter.h"


class LauFitObject : public TObject {

	public:
		//! Destructor
		virtual ~LauFitObject() {}

		//! Mark that the fit is calculating asymmetric errors
		/*!
			This is called by the fitter interface to mark when
			entering and exiting the asymmetric error calculation

			\param [in] inAsymErrCalc boolean marking that the fit is calculating the asymmetric errors
		*/
		virtual void withinAsymErrorCalc(Bool_t inAsymErrCalc) = 0;

		//! This function sets the parameter values from Minuit
		/*! 
			This function has to be public since it is called from the global FCN.
			It should not be called otherwise!

			\param [in] par an array storing the various parameter values
			\param [in] npar the number of free parameters
		*/
		virtual void setParsFromMinuit(Double_t* par, Int_t npar) = 0;

		//! Calculate the new value of the negative log likelihood
		/*! 
			This function has to be public since it is called from the global FCN.
			It should not be called otherwise!
		*/	
		virtual Double_t getTotNegLogLikelihood() = 0;

		//! Store constraint information for fit parameters
		/*!
			\param [in] formula the formula to be used in the LauFormulaPar
			\param [in] pars a vector of LauParameter names to be used in the Formula, in the order specified by the formula
			\param [in] mean the value of the mean of the Gaussian constraint 
			\param [in] width the value of the width of the Gaussian constraint 
		*/	
		virtual void addConstraint(const TString& formula, const std::vector<TString>& pars, const Double_t mean, const Double_t width) = 0;

	protected:
		//! Constructor
		LauFitObject() : TObject() {}

		// Setup a struct to store information on constrained fit parameters
		/*!
		  \struct StoreConstraints
		  \brief Struct to store constraint information until the fit is run
		*/ 
		struct StoreConstraints {
		  	//! The formula to be used in the LauFormulaPar
			TString formula_;
		  	//! The list of LauParameter names to be used in the LauFormulaPar
			std::vector<TString> conPars_;
		  	//! The mean value of the Gaussian constraint to be applied
			Double_t mean_;
		  	//! The width of the Gaussian constraint to be applied
			Double_t width_;
		};

	private:
		//! Copy constructor (not implemented)
		LauFitObject(const LauFitObject& rhs);

		//! Copy assignment operator (not implemented)
		LauFitObject& operator=(const LauFitObject& rhs);

		ClassDef(LauFitObject,0)
};

#endif

