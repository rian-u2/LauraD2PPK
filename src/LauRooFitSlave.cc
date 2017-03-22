
// Copyright University of Warwick 2016 - 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRooFitSlave.cc
  \brief File containing implementation of LauRooFitSlave class.
 */

// TODO - can some of this implementation go into the base class?

#include <iostream>
#include <vector>

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"

#include "LauParameter.hh"
#include "LauSimFitSlave.hh"
#include "LauRooFitSlave.hh"

ClassImp(LauRooFitSlave)


LauRooFitSlave::LauRooFitSlave( RooAbsPdf& model, const Bool_t extended, const RooArgSet& vars, const TString& weightVarName ) :
	LauSimFitSlave(),
	model_(model),
	dataVars_(vars),
	weightVarName_(weightVarName),
	dataFile_(0),
	dataTree_(0),
	exptData_(0),
	extended_(extended),
	iExpt_(0),
	iExptCat_("iExpt","Expt Number"),
	nEvent_(0),
	nllVar_(0),
	fitNtuple_(0),
	nFreeParams_(0),
	fitStatus_(0),
	NLL_(0.0)
{
	if ( weightVarName_ != "" ) {
		Bool_t weightVarFound = kFALSE;
		RooFIter argset_iter = dataVars_.fwdIterator();
		RooAbsArg* param(0);
		while ( (param = argset_iter.next()) ) {
			TString name = param->GetName();
			if ( name == weightVarName_ ) {
				weightVarFound = kTRUE;
				break;
			}
		}
		if ( ! weightVarFound ) {
			std::cerr << "ERROR in LauRooFitSlave::LauRooFitSlave : The set of data variables does not contain the weighting variable \"" << weightVarName_ << std::endl;
			std::cerr << "                                        : Weighting will be disabled." << std::endl;
			weightVarName_ = "";
		}
	}

}

LauRooFitSlave::~LauRooFitSlave()
{
	delete nllVar_; nllVar_ = 0;
	delete fitNtuple_; fitNtuple_ = 0;
	this->cleanData();
}

void LauRooFitSlave::cleanData()
{
	if ( dataFile_ != 0 ) {
		dataFile_->Close();
		delete dataFile_;
		dataTree_ = 0;
		dataFile_ = 0;
	}
	delete exptData_;
	exptData_ = 0;
}

Bool_t LauRooFitSlave::cacheFitData(const TString& dataFileName, const TString& dataTreeName)
{
	// Clean-up from any previous runs
	if ( dataFile_ != 0 ) {
		this->cleanData();
	}

	// Open the data file
	dataFile_ = TFile::Open( dataFileName );
	if ( ! dataFile_ ) {
		std::cerr << "ERROR in LauRooFitSlave::cacheFitData : Problem opening data file \"" << dataFileName << "\"" << std::endl;
		return kFALSE;
	}

	// Retrieve the tree
	dataTree_ = dynamic_cast<TTree*>( dataFile_->Get( dataTreeName ) );
	if ( ! dataTree_ ) {
		std::cerr << "ERROR in LauRooFitSlave::cacheFitData : Problem retrieving tree \"" << dataTreeName << "\" from data file \"" << dataFileName << "\"" << std::endl;
		dataFile_->Close();
		delete dataFile_;
		dataFile_ = 0;
		return kFALSE;
	}

	// Check that the tree contains branches for all the fit variables
	RooFIter argset_iter = dataVars_.fwdIterator();
	RooAbsArg* param(0);
	while ( (param = argset_iter.next()) ) {
		TString name = param->GetName();
		TBranch* branch = dataTree_->GetBranch( name );
		if ( branch == 0 ) {
			std::cerr << "ERROR in LauRooFitSlave::cacheFitData : The data tree does not contain a branch for fit variable \"" << name << std::endl;
			return kFALSE;
		}
	}

	// Check whether the tree has the branch iExpt
	TBranch* branch = dataTree_->GetBranch("iExpt");
	if ( branch == 0 ) {
		std::cout << "WARNING in LauRooFitSlave::cacheFitData : Cannot find branch \"iExpt\" in the tree, will treat all data as being from a single experiment" << std::endl;
	} else {
		// Define the valid values for the iExpt RooCategory
		iExptCat_.clearTypes();
		const UInt_t firstExpt = dataTree_->GetMinimum("iExpt");
		const UInt_t lastExpt  = dataTree_->GetMaximum("iExpt");
		for ( UInt_t iExpt = firstExpt; iExpt <= lastExpt; ++iExpt ) {
			iExptCat_.defineType( TString::Format("expt%d",iExpt), iExpt );
		}
	}

	return kTRUE;
}

void LauRooFitSlave::runSlave(const TString& dataFileName, const TString& dataTreeName,
			      const TString& histFileName, const TString& /*tableFileName*/,
			      const TString& addressMaster, const UInt_t portMaster)
{
	// Load the data
	Bool_t dataOK = this->cacheFitData(dataFileName, dataTreeName);
	if ( ! dataOK ) {
		std::cerr << "ERROR in LauRooFitSlave::runSlave : Problem reading the data, aborting fit" << std::endl;
		return;
	}

	// Establish the connection to the master process
	this->connectToMaster( addressMaster, portMaster );

	// Create the ntuple in which to store the fit results
	std::cout << "INFO in LauRooFitSlave::runSlave : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName, this->useAsymmFitErrors());

	// Now process the various requests from the master
	this->processMasterRequests();
}

void LauRooFitSlave::prepareInitialParArray( TObjArray& array )
{
	// Check that the NLL variable has been initialised
	if ( ! nllVar_ ) {
		std::cerr << "ERROR in LauRooFitSlave::prepareInitialParArray : NLL var not initialised" << std::endl;
		return;
	}

	// If we already prepared the entries in the fitPars_ vector then we only need to add the contents to the array
	if ( ! fitPars_.empty() ) {
		for ( std::vector<LauParameter*>::iterator iter = fitPars_.begin(); iter != fitPars_.end(); ++iter ) {
			array.Add(*iter);
		}
		return;
	}

	// Store the set of parameters and the total number of parameters
	RooArgSet* varSet = nllVar_->getParameters( exptData_ );
	nFreeParams_ = 0;

	// Loop through the fit parameters
	RooFIter argset_iter = varSet->fwdIterator();
	RooAbsArg* param(0);
	while ( (param = argset_iter.next()) ) {
		// Only consider the free parameters
		if ( ! param->isConstant() ) {
			// Add the parameter
			RooRealVar* rrvar = dynamic_cast<RooRealVar*>( param );
			if ( rrvar != 0 ) {
				// Count the number of free parameters
				++nFreeParams_;
				// Do the conversion and add it to the array
				LauParameter* lpar = this->convertToLauParameter( rrvar );
				fitVars_.push_back( rrvar );
				fitPars_.push_back( lpar );
				array.Add( lpar );
			} else {
				RooFormulaVar* rfvar = dynamic_cast<RooFormulaVar*>( param );
				if ( rfvar == 0 ) {
					std::cerr << "ERROR in LauRooFitSlave::prepareInitialParArray : The parameter is neither a RooRealVar nor a RooFormulaVar, don't know what to do" << std::endl;
					continue;
				}
				std::vector< std::pair<RooRealVar*,LauParameter*> > lpars = this->convertToLauParameters( rfvar );
				for ( std::vector< std::pair<RooRealVar*,LauParameter*> >::iterator iter = lpars.begin(); iter != lpars.end(); ++iter ) {
					RooRealVar* rrv = iter->first;
					LauParameter* lpar = iter->second;
					if ( ! rrv->isConstant() ) {
						continue;
					}

					// Count the number of free parameters
					++nFreeParams_;
					// Add the parameter to the array
					fitVars_.push_back( rrvar );
					fitPars_.push_back( lpar );
					array.Add( lpar );
				}
			}
		}
	}
	delete varSet;
}

LauParameter* LauRooFitSlave::convertToLauParameter( const RooRealVar* rooParameter ) const
{
	return new LauParameter( rooParameter->GetName(), rooParameter->getVal(), rooParameter->getMin(), rooParameter->getMax(), rooParameter->isConstant() );
}

std::vector< std::pair<RooRealVar*,LauParameter*> > LauRooFitSlave::convertToLauParameters( const RooFormulaVar* rooFormula ) const
{
	// Create the empty vector
	std::vector< std::pair<RooRealVar*,LauParameter*> > lauParameters;

	Int_t parIndex(0);
	RooAbsArg* rabsarg(0);
	RooRealVar* rrvar(0);
	RooFormulaVar* rfvar(0);
	// Loop through all the parameters of the formula
	while ( (rabsarg = rooFormula->getParameter(parIndex)) ) {
		// First try converting to a RooRealVar
		rrvar = dynamic_cast<RooRealVar*>( rabsarg );
		if ( rrvar ) {
			// Do the conversion and add it to the array
			LauParameter* lpar = this->convertToLauParameter( rrvar );
			lauParameters.push_back( std::make_pair(rrvar,lpar) );
			continue;
		}

		// If that didn't work, try converting to a RooFormulaVar
		rfvar = dynamic_cast<RooFormulaVar*>( rabsarg );
		if ( rfvar ) {
			// Do the conversion and add these to the array
			std::vector< std::pair<RooRealVar*,LauParameter*> > lpars = this->convertToLauParameters( rfvar );
			for ( std::vector< std::pair<RooRealVar*,LauParameter*> >::iterator iter = lpars.begin(); iter != lpars.end(); ++iter ) {
				lauParameters.push_back( *iter );
			}
			continue;
		}

		// If neither of those worked we don't know what to do, so print an error message and continue
		std::cerr << "ERROR in LauRooFitSlave::convertToLauParameters : One of the parameters is not a RooRealVar nor a RooFormulaVar, it is a: " << rabsarg->ClassName() << std::endl;
		std::cerr << "                                                : Do not know how to process that - it will be skipped." << std::endl;
	}

	return lauParameters;
}

Double_t LauRooFitSlave::getTotNegLogLikelihood()
{
	Double_t nll = (nllVar_ != 0) ? nllVar_->getVal() : 0.0;
	return nll;
}

void LauRooFitSlave::setParsFromMinuit(Double_t* par, Int_t npar)
{
	// This function sets the internal parameters based on the values
	// that Minuit is using when trying to minimise the total likelihood function.

	// MINOS reports different numbers of free parameters depending on the
	// situation, so disable this check
	if ( ! this->withinAsymErrorCalc() ) {
		if (static_cast<UInt_t>(npar) != nFreeParams_) {
			std::cerr << "ERROR in LauRooFitSlave::setParsFromMinuit : Unexpected number of free parameters: " << npar << ".\n";
			std::cerr << "                                             Expected: " << nFreeParams_ << ".\n" << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Despite npar being the number of free parameters
	// the par array actually contains all the parameters,
	// free and floating...

	// Update all the floating ones with their new values
	for (UInt_t i(0); i<nFreeParams_; ++i) {
		if (!fitPars_[i]->fixed()) {
			// Set both the RooRealVars and the LauParameters
			fitPars_[i]->value(par[i]);
			fitVars_[i]->setVal(par[i]);
		}
	}
}

UInt_t LauRooFitSlave::readExperimentData( const UInt_t exptIndex )
{
	// check that we're being asked to read a valid index
	if ( iExptCat_.numTypes() == 0 && exptIndex != 0 ) {
		std::cerr << "ERROR in LauRooFitSlave::readExperimentData : Invalid experiment number " << exptIndex << ", data contains only one experiment" << std::endl;
		return 0;
	} else if ( ! iExptCat_.isValidIndex( exptIndex ) ) {
		std::cerr << "ERROR in LauRooFitSlave::readExperimentData : Invalid experiment number " << exptIndex << std::endl;
		return 0;
	}

	// set our record of which experiment we're examining
	iExpt_ = exptIndex;

	// retrieve the data and find out how many events have been read
	RooArgSet dataVars(dataVars_);
	if ( iExptCat_.numTypes() == 0 ) {
		exptData_ = new RooDataSet( TString::Format("expt%dData",iExpt_), "", dataTree_, dataVars_, "", (weightVarName_ != "") ? weightVarName_.Data() : 0 );
	} else {
		const TString selectionString = TString::Format("iExpt==%d",iExpt_);
		TTree* exptTree = dataTree_->CopyTree(selectionString);
		exptData_ = new RooDataSet( TString::Format("expt%dData",iExpt_), "", exptTree, dataVars_, "", (weightVarName_ != "") ? weightVarName_.Data() : 0 );
		delete exptTree;
	}
	nEvent_ = exptData_->numEntries();

	return nEvent_;
}

void LauRooFitSlave::cacheInputFitVars()
{
	// cleanup the old NLL info
	delete nllVar_;

	// construct the new NLL variable for this dataset
	nllVar_ = new RooNLLVar("nllVar", "", model_, *exptData_, extended_);
}

void LauRooFitSlave::finaliseResults( const Int_t fitStat, const Double_t NLL, const TObjArray* parsFromMaster, const TMatrixD* covMat, TObjArray& parsToMaster )
{
	// Copy the fit status information
	fitStatus_ = fitStat;
	NLL_ = NLL;

	// Copy the contents of the covariance matrix
	covMatrix_.Clear();
	covMatrix_.ResizeTo( covMat->GetNrows(), covMat->GetNcols() );
	covMatrix_.SetMatrixArray( covMat->GetMatrixArray() );

	// Now process the parameters
	UInt_t nPars = parsFromMaster->GetEntries();
	if ( nPars != nFreeParams_ ) {
		std::cerr << "ERROR in LauRooFitSlave::finaliseResults : Unexpected number of parameters received from master" << std::endl;
		std::cerr << "                                         : Received " << nPars << " when expecting " << nFreeParams_ << std::endl;
		gSystem->Exit( EXIT_FAILURE );
	}

	for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
		LauParameter* parameter = dynamic_cast<LauParameter*>( (*parsFromMaster)[iPar] );
		if ( ! parameter ) {
			std::cerr << "ERROR in LauRooFitSlave::finaliseResults : Error reading parameter from master" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		if ( parameter->name() != fitPars_[iPar]->name() ) {
			std::cerr << "ERROR in LauAbsFitModel::finaliseResults : Error reading parameter from master" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		*(fitPars_[iPar]) = *parameter;

		RooRealVar* rrv = fitVars_[iPar];
		rrv->setVal( parameter->value() );
		rrv->setError( parameter->error() );
		rrv->setAsymError( parameter->negError(), parameter->posError() );
	}

	// Update the pulls and add each finalised fit parameter to the list to
	// send back to the master
	for ( std::vector<LauParameter*>::iterator iter = fitPars_.begin(); iter != fitPars_.end(); ++iter ) {
		(*iter)->updatePull();
		parsToMaster.Add( *iter );
	}

	// Write the results into the ntuple
	std::vector<LauParameter> extraVars;
	fitNtuple_->storeParsAndErrors(fitPars_, extraVars);

	// find out the correlation matrix for the parameters
	fitNtuple_->storeCorrMatrix(iExpt_, NLL_, fitStatus_, covMatrix_);

	// Fill the data into ntuple
	fitNtuple_->updateFitNtuple();
}

void LauRooFitSlave::writeOutAllFitResults()
{
	// Write out histograms at end
	if (fitNtuple_ != 0) {
		fitNtuple_->writeOutFitResults();
	}
}

