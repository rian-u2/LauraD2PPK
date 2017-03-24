
// Copyright University of Warwick 2013 - 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSimFitSlave.hh
    \brief File containing declaration of LauSimFitSlave class.
*/

/*! \class LauSimFitSlave
    \brief The base class for any slave process for simultaneous/combined fits

    Implementation of the JFit method described in arXiv:1409.5080 [physics.data-an].

    This class acts as the base class from which slaves should inherit.
    This allows any fitting framework to plug in to the JFit method.
*/

#ifndef LAU_SIM_FIT_SLAVE
#define LAU_SIM_FIT_SLAVE

#include "TMatrixDfwd.h"

#include "LauFitObject.hh"

class TMessage;
class TSocket;
class TString;
class LauFitNtuple;


class LauSimFitSlave : public LauFitObject {

	public:
		//! Constructor
		LauSimFitSlave();

		//! Destructor
		virtual ~LauSimFitSlave();

		//! Obtain the number of slaves
		UInt_t nSlaves() const {return nSlaves_;}

		//! Obtain the ID number of this slave
		UInt_t slaveId() const {return slaveId_;}

		//! Start the slave process for simultaneous fitting
		/*!
			\param [in] dataFileName the name of the input data file
			\param [in] dataTreeName the name of the tree containing the data
			\param [in] histFileName the file name for the output histograms
			\param [in] tableFileName the file name for the latex output file
			\param [in] addressMaster the hostname of the machine running the master process
			\param [in] portMaster the port number on which the master process is listening
		*/	
		virtual void runSlave(const TString& dataFileName, const TString& dataTreeName,
			              const TString& histFileName, const TString& tableFileName = "",
			              const TString& addressMaster = "localhost", const UInt_t portMaster = 9090);

		//! Initialise the fit model
		/*!
			Each class that inherits from this one must implement
			this to do what is appropriate
		*/
		virtual void initialise() = 0;

		//! This function sets the parameter values from Minuit
		/*! 
			\param [in] par an array storing the various parameter values
			\param [in] npar the number of free parameters
		*/
		virtual void setParsFromMinuit(Double_t* par, Int_t npar) = 0;

		//! Calculates the total negative log-likelihood
		virtual Double_t getTotNegLogLikelihood() = 0;

	protected:
		//! Const access to the fit ntuple
		const LauFitNtuple* fitNtuple() const {return fitNtuple_;}

		//! Access to the fit ntuple
		LauFitNtuple* fitNtuple() {return fitNtuple_;}

		//! Establish the connection to the master process
		/*!
			\param [in] addressMaster the hostname of the machine running the master process
			\param [in] portMaster the port number on which the master process is listening
		*/	
		void connectToMaster( const TString& addressMaster, const UInt_t portMaster );

		//! Listen for requests from the master and act accordingly
		void processMasterRequests();

		//! Setup saving of fit results to ntuple/LaTeX table etc.
		/*!
		  	Provide here a default implementation that produces an ntuple only.
			Derived classes can override as they wish.

			\param [in] histFileName the file name for the output histograms
			\param [in] tableFileName the file name for the latex output file
		*/	
		virtual void setupResultsOutputs( const TString& histFileName, const TString& tableFileName );

		//! Package the initial fit parameters for transmission to the master
		/*!
			\param [out] array the array to be filled with the LauParameter objects
		*/	
		virtual void prepareInitialParArray( TObjArray& array ) = 0;

		//! Perform all finalisation actions
		/*!
			- Receive the results of the fit from the master
			- Perform any finalisation routines
		  	- Package the finalised fit parameters for transmission back to the master

			\param [in] fitStat the convergence/error matrix status of the fit
			\param [in] NLL the minimised negative log likelihood
			\param [in] parsFromMaster the parameters at the fit minimum
			\param [in] covMat the fit covariance matrix
			\param [out] parsToMaster the array to be filled with the finalised LauParameter objects
		*/	
		virtual void finaliseExperiment( const Int_t fitStat, const Double_t NLL, const TObjArray* parsFromMaster, const TMatrixD* covMat, TObjArray& parsToMaster ) = 0;

		//! Store variables from the input file into the internal data storage
		/*!
			\param [in] dataFileName the name of the input file
			\param [in] dataTreeName the name of the input tree
		*/	
		virtual Bool_t cacheFitData(const TString& dataFileName, const TString& dataTreeName) = 0;

		//! Read in the data for the current experiment
		/*!
			\return the number of events read in
		*/	
		virtual UInt_t readExperimentData() = 0;

		//! Cache the input data values to calculate the likelihood during the fit
		virtual void cacheInputFitVars() = 0;

		//! Write out any fit results
		virtual void writeOutAllFitResults();

	private:
		//! Copy constructor (not implemented)
		LauSimFitSlave(const LauSimFitSlave& rhs);

		//! Copy assignment operator (not implemented)
		LauSimFitSlave& operator=(const LauSimFitSlave& rhs);

		//! A socket to enable parallel setup 
		TSocket* sMaster_;

		//! Message from master to the slaves
		TMessage* messageFromMaster_;

		//! Slave id number
		UInt_t slaveId_;

		//! The total number of slaves
		UInt_t nSlaves_;

		//! Parameter values array (for reading from the master)
		Double_t* parValues_;

		//! The fit ntuple
		LauFitNtuple* fitNtuple_;

		ClassDef(LauSimFitSlave,0);
};

#endif

