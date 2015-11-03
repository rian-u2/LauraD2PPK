
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
			\param [in] nExpt the number of experiments to be fitted
			\param [in] firstExpt the ID of the first experiment to be fitted
			\param [in] useAsymmErrors should asymmetric errors be calculated or not
			\param [in] twoStageFit should the fit be performed in two stages or not
		*/
		void runSimFit( const TString& fitNtupleFileName, UInt_t nExpt, UInt_t firstExpt = 0, Bool_t useAsymmErrors = kFALSE, Bool_t twoStageFit = kFALSE );

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

		//! Store constraint information for fit parameters
		/*!
			\param [in] formula the formula to be used in the LauFormulaPar
			\param [in] pars a vector of LauParameter names to be used in the Formula, in the order specified by the formula
			\param [in] mean the value of the mean of the Gaussian constraint 
			\param [in] width the value of the width of the Gaussian constraint 
		*/	
		virtual void addConstraint(const TString& formula, const std::vector<TString>& pars, const Double_t mean, const Double_t width);

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
		void fitExpt( Bool_t useAsymmErrors, Bool_t twoStageFit );

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

		//! Store the constraints for fit parameters until initialisation is complete
		std::vector<StoreConstraints> storeCon_;

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

		//! The experiment number of the current fit
		UInt_t iExpt_;

		//! The negative log-likelihood
		Double_t NLL_;

		//! The fit covariance matrix
		TMatrixD covMatrix_;

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

