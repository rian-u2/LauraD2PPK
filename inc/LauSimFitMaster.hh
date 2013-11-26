
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSimFitMaster.hh
    \brief File containing declaration of LauSimFitMaster class.
*/

/*! \class LauSimFitMaster
    \brief The master process for simultaneous/combined fits

    The interface between the slave processes and the minimiser.
*/

#ifndef LAU_SIM_FIT_MASTER
#define LAU_SIM_FIT_MASTER

#include <map>
#include <vector>

#include "TMatrixDfwd.h"
#include "TMessage.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TVectorDfwd.h"

#include "LauFitObject.hh"

class TMessage;
class TMonitor;
class TSocket;
class LauParameter;

/* NOTES
 *
 * Fit procedure in LauAbsFitModel:
 *
 * Print message about asym errors.
 * How many experiments are we fitting and what is the ID of the first one?
 * Start the cumulative timer.
 * Create the fit ntuple and (optionally) the sPlot ntuple. (I think we let the slaves handle these.)
 * Read in the data. (Tell the slaves to read the data.)
 * Loop through the experiments.
 *   Start the expt timer.
 *   Set the expt number for the data cache. (Tell the slaves to do this. They should report back the number of events they find - abort (or skip expt) on one or more having zero?)
 *   Do the caching. (Tell the slaves to do it.)
 *   Fit the expt.
 *     Set the FCN.
 *     Set the Object.
 *     Clear the fitter.
 *     Update the initial fit parameters (randomise, recalc nSig if not going extended fit).
 *     Give the parameters to the fitter.
 *     Fix parameters if needed.
 *     Count the number of free and fixed parameters.
 *     Set the fitter error definition.
 *     Set the fitter strategy.
 *     Run the minimisation.
 *       Migrad.
 *       Check status.
 *       Hesse.
 *       Check status.
 *       Optionally Minos.
 *       Get final status.
 *       Print results.
 *     If doing a two-stage fit release the 2nd stage parameters and rerun the minimisation.
 *     Get the final parameter values and errors and store in the LauParameters.
 *   Finalise the results and (optionally) write likelihood and sWeight data. (Tell the slaves to do it.)
 *   Optionally create toy MC samples. (Tell the slaves to do it.)
 *   Stop and print the expt timer. (Maybe do this before the previous two items?)
 * Stop and print the cumulative timer.
 * Print information on the number of OK and failed fits.
 * Write out the results (etc.) ntuples. (Tell the slaves to do it.)
 *
 *
 *
 *
 */

class LauSimFitMaster : public LauFitObject {

	public:
		//! Constructor
		explicit LauSimFitMaster( UInt_t numSlaves, UInt_t port = 9090 );

		//! Destructor
		virtual ~LauSimFitMaster();

		//! Run the fit
		void runSimFit( UInt_t nExpt, UInt_t firstExpt = 0, Bool_t twoStageFit = kFALSE );

		//! Mark that the fit is calculating asymmetric errors
		/*!
			This function has to be public since it is called by
			the fitter interface to mark when entering and exiting
			the asymmetric error calculation.
			It should not be called otherwise!

			\param [in] inAsymErrCalc boolean marking that the fit is calculating the asymmetric errors
		*/
		virtual void withinAsymErrorCalc(Bool_t inAsymErrCalc) { withinAsymErrorCalc_ = inAsymErrCalc; }

		//! This function sets the parameter values from Minuit
		/*! 
			This function has to be public since it is called from the global FCN.
			It should not be called otherwise!

			\param [in] par an array storing the various parameter values
			\param [in] npar the number of free parameters
		*/
		virtual void setParsFromMinuit(Double_t* par, Int_t npar);

		//! Calculate the new value of the negative log likelihood
		/*! 
			This function has to be public since it is called from the global FCN.
			It should not be called otherwise!
		*/	
		virtual Double_t getTotNegLogLikelihood();

	protected:
		//! Print information on the parameters
		void printParInfo() const;

		//! Initialise
		void initialise();

		//! Initialise socket connections for the slaves 
		void initSockets();

		//! Determine the parameter names and initial values from all slaves
		void getParametersFromSlaves();

		//! Check for compatibility between two same-named parameters, which should therefore be identical
		void checkParameter( const LauParameter* param, UInt_t index ) const;

		//! Instruct the slaves to read the input data for the given experiment
		/*!
			\param [in] iExpt the number of the experiment to read
			\return success/failure of the reading operations
		*/
		Bool_t readData( UInt_t iExpt );

		//! Instruct the slaves to perform the caching
		/*!
			\return success/failure of the caching operations
		*/
		Bool_t cacheInputData();

		//! Perform the fit for the current experiment
		void fitExpt( Bool_t twoStageFit );

		//! Instruct the slaves to update the initial fit parameter values, if required
		void checkInitFitParams();

		//! Return the final parameters to the slaves and instruct them to perform their finalisation
		Bool_t finalise();

		//! Instruct the slaves to write out the fit results
		Bool_t writeOutResults();


	private:
		//! The number of slaves
		const UInt_t nSlaves_;

		//! The requested port
		const UInt_t reqPort_;

		//! The number of fit parameters
		UInt_t nParams_; 

		//! The number of free fit parameters
		UInt_t nFreeParams_;

		//! Flag to indicate if the asymmetric error calculation (e.g. MINOS) is currently running
		Bool_t withinAsymErrorCalc_;

		//! The number of successful fits
		UInt_t numberOKFits_;

		//! The number of fit failures
		UInt_t numberBadFits_;

		//! The status of the current fit
		Int_t fitStatus_;

		//! The negative log-likelihood
		Double_t NLL_;

		//! The fit covariance matrix
		TMatrixD* covMatrix_;

		//! Parallel setup monitor
		TMonitor* socketMonitor_;

		//! Sockets for each of the slaves
		std::vector<TSocket*> sSlaves_;

		//! Messages to slaves
		std::vector<TMessage*> messagesToSlaves_;

		//! Message from slaves to the master
		TMessage* messageFromSlave_;

		//! Map of parameter names to index in the values vector
		std::map< TString, UInt_t > parIndices_;

		//! Reverse map of index in the values vector to parameter names
		std::map< UInt_t, TString > parNames_;

		//! Parameters
		std::vector<LauParameter*> params_;

		//! Parameter values
		std::vector<Double_t> parValues_;

		//! Lists of indices for each slave
		std::vector< std::vector<UInt_t> > slaveIndices_;

		//! Parameter values to send to the slaves
		std::vector<Double_t*> vectorPar_;

		//! Likelihood values returned from the slaves
		std::vector<Double_t> vectorRes_;

		//! The fit timer 
		TStopwatch timer_; 

		//! The total fit timer
		TStopwatch cumulTimer_;

		ClassDef(LauSimFitMaster,0);
};

#endif

