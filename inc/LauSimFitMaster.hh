
/*
Copyright 2013 University of Warwick

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

/*! \file LauSimFitMaster.hh
    \brief File containing declaration of LauSimFitMaster class.
*/

/*! \class LauSimFitMaster
    \brief The master process for simultaneous/combined fits

    Implementation of the JFit method described in arXiv:1409.5080 [physics.data-an].

    This class acts as the interface between the slave processes and the minimiser.
*/

#ifndef LAU_SIM_FIT_MASTER
#define LAU_SIM_FIT_MASTER

#include <map>
#include <vector>

#include "TMatrixD.h"
#include "TStopwatch.h"
#include "TString.h"

#include "LauFitObject.hh"

class TMessage;
class TMonitor;
class TSocket;
class LauAbsRValue;
class LauParameter;
class LauFitNtuple;


class LauSimFitMaster : public LauFitObject {

	public:
		//! Constructor
		/*! 
			\param [in] numSlaves the number of slaves processes to expect connections from
			\param [in] port the port on which to listen for connections from the slaves
		*/
		LauSimFitMaster( UInt_t numSlaves, UInt_t port = 9090 );

		//! Destructor
		virtual ~LauSimFitMaster();

		//! Run the fit
		/*! 
			\param [in] fitNtupleFileName the file to which the ntuple containing the fit results should be written
			\param [in] nExp the number of experiments to be fitted
			\param [in] firstExp the ID of the first experiment to be fitted
			\param [in] useAsymmErrors should asymmetric errors be calculated or not
			\param [in] doTwoStageFit should the fit be performed in two stages or not
		*/
		void runSimFit( const TString& fitNtupleFileName, const UInt_t nExp, const UInt_t firstExp = 0, const Bool_t useAsymmErrors = kFALSE, const Bool_t doTwoStageFit = kFALSE );

		//! Mark that the fit is calculating asymmetric errors
		/*!
			This function has to be public since it is called by
			the fitter interface to mark when entering and exiting
			the asymmetric error calculation.
			It should not be called otherwise!

			\param [in] inAsymErrCalc boolean marking that the fit is calculating the asymmetric errors
		*/
		virtual void withinAsymErrorCalc(const Bool_t inAsymErrCalc);

		// Need to unshadow the query method defined in the base class
		using LauFitObject::withinAsymErrorCalc;

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

		//! Determine/update the parameter initial values from all slaves
		void getParametersFromSlaves();

		//! Determine the parameter names and initial values from all slaves
		void getParametersFromSlavesFirstTime();

		//! Update and verify the parameter initial values from all slaves
		void updateParametersFromSlaves();

		//! Check for compatibility between two same-named parameters, which should therefore be identical
		void checkParameter( const LauParameter* param, UInt_t index ) const;

		//! Add parameters to the list of Gaussian constrained parameters
		void addConParameters();

		//! Calculate the penalty terms to the log likelihood from Gaussian constraints
		Double_t getLogLikelihoodPenalty();

		//! Instruct the slaves to read the input data for the given experiment
		/*!
			\return success/failure of the reading operations
		*/
		Bool_t readData();

		//! Instruct the slaves to perform the caching
		/*!
			\return success/failure of the caching operations
		*/
		Bool_t cacheInputData();

		//! Perform the fit for the current experiment
		void fitExpt();

		//! Instruct the slaves to update the initial fit parameter values, if required
		void checkInitFitParams();

		//! Return the final parameters to the slaves and instruct them to perform their finalisation
		Bool_t finalise();

		//! Instruct the slaves to write out the fit results
		Bool_t writeOutResults();


	private:
		//! Copy constructor (not implemented)
		LauSimFitMaster(const LauSimFitMaster& rhs);

		//! Copy assignment operator (not implemented)
		LauSimFitMaster& operator=(const LauSimFitMaster& rhs);

		//! Store the constraints for fit parameters until initialisation is complete
		std::vector<StoreConstraints> storeCon_;

		//! The number of slaves
		const UInt_t nSlaves_;

		//! The requested port
		const UInt_t reqPort_;

		//! The covariance sub-matrices for each slave
		std::vector<TMatrixD> covMatrices_;

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

		//! Gaussian constraints
		std::vector<LauAbsRValue*> conVars_;

		//! Parameter values
		std::vector<Double_t> parValues_;

		//! Lists of indices for each slave
		std::vector< std::vector<UInt_t> > slaveIndices_;

		//! Lists of indices of free parameters for each slave
		std::vector< std::vector<UInt_t> > slaveFreeIndices_;

		//! Parameter values to send to the slaves
		std::vector<Double_t*> vectorPar_;

		//! Likelihood values returned from the slaves
		std::vector<Double_t> vectorRes_;

		//! The fit timer 
		TStopwatch timer_; 

		//! The total fit timer
		TStopwatch cumulTimer_;

		//! The fit results ntuple
		LauFitNtuple* fitNtuple_;

		ClassDef(LauSimFitMaster,0);
};

#endif

