
// Copyright University of Warwick 2016 - 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRooFitSlave.hh
    \brief File containing declaration of LauRooFitSlave class.
*/

/*! \class LauRooFitSlave
    \brief A class for creating a RooFit-based slave process for simultaneous/combined fits

    Implementation of the JFit method described in arXiv:1409.5080 [physics.data-an].
*/

#ifndef LAU_ROO_FIT_SLAVE
#define LAU_ROO_FIT_SLAVE

#include "RooAbsPdf.h"
#include "RooAbsData.h"
#include "RooCategory.h"
#include "RooNLLVar.h"
//#include "TMatrixDfwd.h"
#include "TMatrixD.h"

#include "LauFitNtuple.hh"
#include "LauSimFitSlave.hh"

class TString;


class LauRooFitSlave : public LauSimFitSlave {

	public:
		//! Constructor
		LauRooFitSlave( RooAbsPdf& model, const Bool_t extended, const RooArgSet& vars, const TString& weightVarName = "" );

		//! Destructor
		virtual ~LauRooFitSlave();

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


		//! This function sets the parameter values from Minuit
		/*! 
			\param [in] par an array storing the various parameter values
			\param [in] npar the number of free parameters
		*/
		virtual void setParsFromMinuit(Double_t* par, Int_t npar);

		//! Calculates the total negative log-likelihood
		virtual Double_t getTotNegLogLikelihood();

	protected:

		//! Package the initial fit parameters for transmission to the master
		/*!
		    \param [out] array the array to be filled with the LauParameter objects
		*/	
		virtual void prepareInitialParArray( TObjArray& array );

		//! Convert a RooRealVar into a LauParameter
		/*!
		    \param [in] rooParameter the RooRealVar to be converted
		    \return the newly created LauParameter
		*/
		LauParameter* convertToLauParameter( const RooRealVar* rooParameter ) const;

		//! Convert a RooFormulaVar into LauParameters
		/*!
		    \param [in] rooFormula the RooFormulaVar to be converted
		    \return the vector of pointers to the RooRealVars and newly created LauParameters
		*/
		std::vector< std::pair<RooRealVar*,LauParameter*> > convertToLauParameters( const RooFormulaVar* rooFormula ) const;

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
		virtual void finaliseResults( const Int_t fitStat, const Double_t NLL, const TObjArray* parsFromMaster, const TMatrixD* covMat, TObjArray& parsToMaster );

		//! Store variables from the input file into the internal data storage
		/*!
			\param [in] dataFileName the name of the input file
			\param [in] dataTreeName the name of the input tree
		*/	
		virtual Bool_t cacheFitData(const TString& dataFileName, const TString& dataTreeName);

		//! Read in the data for the specified experiment
		/*!
			\param [in] exptIndex the experiment number to be read
			\return the number of events read in
		*/	
		virtual UInt_t readExperimentData( const UInt_t exptIndex );

		//! Cache the input data values to calculate the likelihood during the fit
		virtual void cacheInputFitVars();

		//! Write out any fit results
		virtual void writeOutAllFitResults();

	private:
		//! Cleanup the data
		void cleanData();

		//! Copy constructor (not implemented)
		LauRooFitSlave(const LauRooFitSlave& rhs);

		//! Copy assignment operator (not implemented)
		LauRooFitSlave& operator=(const LauRooFitSlave& rhs);

		//! The model
		RooAbsPdf& model_;

		//! The dataset variables
		RooArgSet dataVars_;

		//! The name of the (optional) weight variable in the dataset
		TString weightVarName_;

		//! The data file
		TFile* dataFile_;

		//! The data tree
		TTree* dataTree_;

		//! The data for the current experiment
		RooAbsData* exptData_;

		//! Is the PDF extended?
		const Bool_t extended_;

		//! The current experiment
		UInt_t iExpt_;

		//! The experiment category variable
		RooCategory iExptCat_;

		//! The number of events in the current experiment
		UInt_t nEvent_;

		//! The NLL variable
		RooNLLVar* nllVar_;

		//! The fit ntuple
		LauFitNtuple* fitNtuple_;

		//! The fit parameters (as RooRealVar's)
		std::vector<RooRealVar*> fitVars_;

		//! The fit parameters (as LauParameter's)
		std::vector<LauParameter*> fitPars_;

		//! The number of free fit parameters
		UInt_t nFreeParams_;

		//! The fit status of the current experiment
		Int_t fitStatus_;

		//! The NLL value for the current experiment
		Double_t NLL_;

		//! The fit covariance matrix
		TMatrixD covMatrix_;

		ClassDef(LauRooFitSlave,0);
};

#endif
