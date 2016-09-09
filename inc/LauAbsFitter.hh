
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsFitter.hh
    \brief File containing declaration of LauAbsFitter class.
*/

/*! \class LauAbsFitter
    \brief The abstract interface to the fitter.

    The abstract interface to the fitter.
    Concrete implementations provide the singleton interface with a particular fitter, e.g. Minuit.
*/

#ifndef LAU_ABS_FITTER
#define LAU_ABS_FITTER

#include <utility>
#include <vector>

#include "Rtypes.h"
#include "TMatrixDfwd.h"

class LauFitObject;
class LauParameter;


class LauAbsFitter {

	public:
		//! Destructor
		virtual ~LauAbsFitter() {}

		//! Initialise the fitter, setting the information on the parameters
		/*!
		    \param [in] fitObj the object that controls the likelihood calculation
		    \param [in] parameters the list of parameters of the fit
		*/
		virtual void initialise( LauFitObject* fitObj, const std::vector<LauParameter*>& parameters ) = 0;

		//! Get the object that controls the calculation of the likelihood
		virtual LauFitObject* getFitObject() =0;

		//! Get the total number of fit parameters
		virtual UInt_t nParameters() const = 0;

		//! Get the number of floating fit parameters
		virtual UInt_t nFreeParameters() const = 0;

		//! Determine whether the two-stage fit is enabled
		virtual Bool_t twoStageFit() const = 0;

		//! Turn on or off the two stage fit
		/*!
			The two-stage fit allows certain parameters to be fixed
			in one stage and floated in another stage of the fit.
			Can be used, for example, in a CP fit where the
			CP-parameters are fixed to zero in the first stage
			(while the CP-average parameters are determined), then
			floated in the second.

			\param [in] doTwoStageFit boolean specifying whether or not the two-stage fit should be enabled
		*/	
		virtual void twoStageFit(Bool_t doTwoStageFit) = 0;

		//! Determine whether calculation of asymmetric errors is enabled
		virtual Bool_t useAsymmFitErrors() const = 0;

		//! Turn on or off the computation of asymmetric errors (e.g. MINOS routine in Minuit)
		/*!
			\param [in] useAsymmErrors boolean specifying whether or not the computation of asymmetric errors is enabled
		*/	
		virtual void useAsymmFitErrors(Bool_t useAsymmErrors) = 0;

		//! Perform the minimisation of the fit function
		/*!
		    \return the status code of the fit and the minimised value
		*/
		virtual std::pair<Int_t,Double_t> minimise() = 0;

		//! Fix parameters marked as "second stage"
		virtual void fixSecondStageParameters() = 0;

		//! Release parameters marked as "second stage"
		virtual void releaseSecondStageParameters() = 0;

		//! Update the values and errors of the parameters based on the fit minimum
		virtual void updateParameters() = 0;

		//! Retrieve the fit covariance matrix
		virtual const TMatrixD& covarianceMatrix() const = 0;

	protected:
		//! Constructor
		LauAbsFitter() {}

	private:
		//! Copy constructor - private and not implemented
		LauAbsFitter( const LauAbsFitter& );

		//! Copy assignment operator - private and not implemented
		LauAbsFitter& operator=( const LauAbsFitter& rhs );

		ClassDef(LauAbsFitter,0);
};

#endif

