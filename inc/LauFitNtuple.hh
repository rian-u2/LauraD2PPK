
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitNtuple.hh
    \brief File containing declaration of LauFitNtuple class.
*/

/*! \class LauFitNtuple
    \brief Class to store the results from the fit into an ntuple

    Class to store the results from the fit into an ntuple.
    The fitted values and their errors are stored.  In the case of toy MC, the true values are also stored, along with the pulls.
    Derived quantities can also be stored, such as the fit fractions.  What precisely is stored depends on the fit model.
*/

//****************************************************************************
// Class to store the results from the fit/toy MC into an ntuple
// -- CLASS DESCRIPTION [MISC] --
/// Class to store the results from the fit/toy MC into an ntuple

#ifndef LAU_FIT_NTUPLE
#define LAU_FIT_NTUPLE

#include <vector>

#include "TMatrixDfwd.h"
#include "TString.h"

class TFile;
class TTree;

class LauParameter;


class LauFitNtuple {

	public:
		//! Constructor
		/*!
		    \param [in] fileName the name for the ntuple
		*/
		LauFitNtuple(const TString& fileName);
		
		//! Destructor
		virtual ~LauFitNtuple();

		//! Store the correlation matrix and other fit information
		/*!
		    \param [in] iExpt the experiment number
		    \param [in] NLL the minimised negative log likelihood
		    \param [in] fitStatus the status of the fit
		    \param [in] covMatrix the fit covariance matrix
		*/
		void storeCorrMatrix(UInt_t iExpt, Double_t NLL, Int_t fitStatus, const TMatrixD& covMatrix);

		//! Store parameters and their errors
		/*!
		    \param [in] fitVars the fit parameters
		    \param [in] extraVars variables in addition to the fit parameters, e.g. derived quantities such as fit fractions
		*/
		void storeParsAndErrors(const std::vector<LauParameter*>& fitVars, const std::vector<LauParameter>& extraVars);

		//! Update the fit ntuple
		void updateFitNtuple();

		//! Write out fit results
		void writeOutFitResults();

	private:
		//! Name of root file
		TString rootFileName_;
		//! Root file
		TFile* rootFile_;
		//! Fit results
		TTree* fitResults_;

		//! Fit variables
		std::vector<LauParameter*> fitVars_;
		//! Extra variables
		std::vector<LauParameter> extraVars_;

		//! Correlation matrix
		std::vector< std::vector<Double_t> > corrMatrix_;

		//! Flags whether the fit tree has been defined
		Bool_t definedFitTree_;
		//! Status of fit
		Int_t fitStatus_;
		//! Number of fit parameters
		UInt_t nFitPars_;
		//! Number of free parameters
		UInt_t nFreePars_;
		//! Number of extra parameters
		UInt_t nExtraPars_;
		//! Minimised negative log likelihood
		Double_t NLL_;
		//! Experiment number
		Int_t iExpt_;

		ClassDef(LauFitNtuple,0) // Fit/toyMC results ntuple

};

#endif
