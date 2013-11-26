
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauMinuit.hh
    \brief File containing declaration of LauMinuit class.
*/

/*! \class LauMinuit
    \brief The interface to the Minuit fitter.

    The singleton interface to the Minuit fitter.
*/

#ifndef LAU_MINUIT
#define LAU_MINUIT

#include <utility>
#include <vector>

#include "Rtypes.h"
#include "TMatrixDfwd.h"

#include "LauAbsFitter.hh"

class LauParameter;
class TVirtualFitter;


class LauMinuit : public LauAbsFitter {

	public:
		//! Destructor
		virtual ~LauMinuit();

		//! Initialise the fitter, setting the information on the parameters
		/*!
		    \param [in] parameters the list of parameters of the fit
		*/
		virtual void initialise( LauFitObject* fitObj, const std::vector<LauParameter*>& parameters );

		//! Get the object that controls the calculation of the likelihood
		virtual LauFitObject* getFitObject();

		//! Get the total number of fit parameters
		virtual UInt_t nParameters() const { return nParams_; }

		//! Get the number of floating fit parameters
		virtual UInt_t nFreeParameters() const { return nFreeParams_; }

		//! Determine whether the two-stage fit is enabled
		virtual Bool_t twoStageFit() const {return twoStageFit_;}

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
		virtual void twoStageFit(Bool_t doTwoStageFit) {twoStageFit_ = doTwoStageFit;}

		//! Determine whether calculation of asymmetric errors is enabled
		virtual Bool_t useAsymmFitErrors() const {return useAsymmFitErrors_;}

		//! Turn on or off the computation of asymmetric errors (i.e. the MINOS routine)
		/*!
			\param [in] useAsymmErrors boolean specifying whether or not the computation of asymmetric errors is enabled
		*/	
		virtual void useAsymmFitErrors(Bool_t useAsymmErrors) {useAsymmFitErrors_ = useAsymmErrors;}

		//! Perform the minimisation of the fit function
		/*!
		    \return the status code of the fit and the minimised value
		*/
		virtual std::pair<Int_t,Double_t> minimise();

		//! Fix parameters marked as "first stage"
		virtual void fixFirstStageParameters();

		//! Release parameters marked as "first stage"
		virtual void releaseFirstStageParameters();

		//! Fix parameters marked as "second stage"
		virtual void fixSecondStageParameters();

		//! Release parameters marked as "second stage"
		virtual void releaseSecondStageParameters();

		//! Update the values and errors of the parameters based on the fit minimum
		virtual void updateParameters();

		//! Retrieve the fit covariance matrix
		virtual const TMatrixD* covarianceMatrix() const { return covMatrix_; }


	private:
		//! Allow the factory class to access private methods
		friend class LauFitter;

		//! Constructor
		explicit LauMinuit( Int_t maxPar = 100 );

		//! Copy constructor - private and not implemented
		LauMinuit( const LauMinuit& );

		//! Copy assignment operator - private and not implemented
		LauMinuit& operator=( const LauMinuit& rhs );

		//! The interface to Minuit
		TVirtualFitter* minuit_;

		//! The maximum number of parameters
		const UInt_t maxPar_;

		//! The fit parameters
		std::vector<LauParameter*> params_;

		//! The total number of parameters
		UInt_t nParams_;

		//! The number of free parameters
		UInt_t nFreeParams_;

		//! Option to perform a two stage fit
		Bool_t twoStageFit_; 

		//! Option to use asymmetric errors
		Bool_t useAsymmFitErrors_; 

		//! The status of the fit 
		Int_t fitStatus_;

		//! The negative log-likelihood
		Double_t NLL_;

		//! The covariance matrix
		TMatrixD* covMatrix_;

		ClassDef(LauMinuit,0);
};

#endif

