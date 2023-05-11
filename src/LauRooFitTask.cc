
/*
Copyright 2017 University of Warwick

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

/*! \file LauRooFitTask.cc
  \brief File containing implementation of LauRooFitTask class.
 */

#include <iostream>
#include <vector>

#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "TFile.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"

#include "LauFitNtuple.hh"
#include "LauParameter.hh"
#include "LauSimFitTask.hh"
#include "LauRooFitTask.hh"



LauRooFitTask::LauRooFitTask( RooAbsPdf& model, const Bool_t extended, const RooArgSet& vars, const TString& weightVarName ) :
	LauSimFitTask(),
	model_(model),
	dataVars_(vars),
	weightVarName_(weightVarName),
	dataFile_(0),
	dataTree_(0),
	exptData_(0),
	extended_(extended),
	iExptSet_(),
	nllVar_(0)
{
}

LauRooFitTask::~LauRooFitTask()
{
	delete nllVar_; nllVar_ = 0;
	this->cleanData();
}

void LauRooFitTask::cleanData()
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

void LauRooFitTask::initialise()
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
			std::cerr << "ERROR in LauRooFitTask::initialise : The set of data variables does not contain the weighting variable \"" << weightVarName_ << std::endl;
			std::cerr << "                                    : Weighting will be disabled." << std::endl;
			weightVarName_ = "";
		}
	}
}

Bool_t LauRooFitTask::verifyFitData(const TString& dataFileName, const TString& dataTreeName)
{
	// Clean-up from any previous runs
	if ( dataFile_ != 0 ) {
		this->cleanData();
	}

	// Open the data file
	dataFile_ = TFile::Open( dataFileName );
	if ( ! dataFile_ ) {
		std::cerr << "ERROR in LauRooFitTask::verifyFitData : Problem opening data file \"" << dataFileName << "\"" << std::endl;
		return kFALSE;
	}

	// Retrieve the tree
	dataTree_ = dynamic_cast<TTree*>( dataFile_->Get( dataTreeName ) );
	if ( ! dataTree_ ) {
		std::cerr << "ERROR in LauRooFitTask::verifyFitData : Problem retrieving tree \"" << dataTreeName << "\" from data file \"" << dataFileName << "\"" << std::endl;
		dataFile_->Close();
		delete dataFile_;
		dataFile_ = 0;
		return kFALSE;
	}

	// Check that the tree contains branches for all the fit variables
	RooFIter argset_iter = dataVars_.fwdIterator();
	RooAbsArg* param(0);
	Bool_t allOK(kTRUE);
	while ( (param = argset_iter.next()) ) {
		TString name = param->GetName();
		TBranch* branch = dataTree_->GetBranch( name );
		if ( branch == 0 ) {
			std::cerr << "ERROR in LauRooFitTask::verifyFitData : The data tree does not contain a branch for fit variable \"" << name << std::endl;
			allOK = kFALSE;
		}
	}
	if ( ! allOK ) {
		return kFALSE;
	}

	// Check whether the tree has the branch iExpt
	TBranch* branch = dataTree_->GetBranch("iExpt");
	if ( branch == 0 ) {
		std::cout << "WARNING in LauRooFitTask::verifyFitData : Cannot find branch \"iExpt\" in the tree, will treat all data as being from a single experiment" << std::endl;
	} else {
		// Define the valid values for iExpt
		iExptSet_.clear();
		const UInt_t firstExp = dataTree_->GetMinimum("iExpt");
		const UInt_t lastExp  = dataTree_->GetMaximum("iExpt");
		for ( UInt_t iExp = firstExp; iExp <= lastExp; ++iExp ) {
			iExptSet_.insert( iExp );
		}
	}

	return kTRUE;
}

void LauRooFitTask::prepareInitialParArray( TObjArray& array )
{
	// Check that the NLL variable has been initialised
	if ( ! nllVar_ ) {
		std::cerr << "ERROR in LauRooFitTask::prepareInitialParArray : NLL var not initialised" << std::endl;
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
	UInt_t nFreePars(0);

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
				++nFreePars;
				// Do the conversion and add it to the array
				LauParameter* lpar = this->convertToLauParameter( rrvar );
				fitVars_.push_back( rrvar );
				fitPars_.push_back( lpar );
				array.Add( lpar );
			} else {
				RooFormulaVar* rfvar = dynamic_cast<RooFormulaVar*>( param );
				if ( rfvar == 0 ) {
					std::cerr << "ERROR in LauRooFitTask::prepareInitialParArray : The parameter is neither a RooRealVar nor a RooFormulaVar, don't know what to do" << std::endl;
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
					++nFreePars;
					// Add the parameter to the array
					fitVars_.push_back( rrvar );
					fitPars_.push_back( lpar );
					array.Add( lpar );
				}
			}
		}
	}
	delete varSet;

	this->startNewFit( nFreePars, nFreePars );
}

LauParameter* LauRooFitTask::convertToLauParameter( const RooRealVar* rooParameter ) const
{
	return new LauParameter( rooParameter->GetName(), rooParameter->getVal(), rooParameter->getMin(), rooParameter->getMax(), rooParameter->isConstant() );
}

std::vector< std::pair<RooRealVar*,LauParameter*> > LauRooFitTask::convertToLauParameters( const RooFormulaVar* rooFormula ) const
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
		std::cerr << "ERROR in LauRooFitTask::convertToLauParameters : One of the parameters is not a RooRealVar nor a RooFormulaVar, it is a: " << rabsarg->ClassName() << std::endl;
		std::cerr << "                                                : Do not know how to process that - it will be skipped." << std::endl;
	}

	return lauParameters;
}

Double_t LauRooFitTask::getTotNegLogLikelihood()
{
	Double_t nLL = (nllVar_ != 0) ? nllVar_->getVal() : 0.0;
	return nLL;
}

void LauRooFitTask::setParsFromMinuit(Double_t* par, Int_t npar)
{
	// This function sets the internal parameters based on the values
	// that Minuit is using when trying to minimise the total likelihood function.

	// MINOS reports different numbers of free parameters depending on the
	// situation, so disable this check
	const UInt_t nFreePars = this->nFreeParams();
	if ( ! this->withinAsymErrorCalc() ) {
		if (static_cast<UInt_t>(npar) != nFreePars) {
			std::cerr << "ERROR in LauRooFitTask::setParsFromMinuit : Unexpected number of free parameters: " << npar << ".\n";
			std::cerr << "                                             Expected: " << nFreePars << ".\n" << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Despite npar being the number of free parameters
	// the par array actually contains all the parameters,
	// free and floating...

	// Update all the floating ones with their new values
	for (UInt_t i(0); i<nFreePars; ++i) {
		if (!fitPars_[i]->fixed()) {
			// Set both the RooRealVars and the LauParameters
			fitPars_[i]->value(par[i]);
			fitVars_[i]->setVal(par[i]);
		}
	}
}

UInt_t LauRooFitTask::readExperimentData()
{
	// check that we're being asked to read a valid index
	const UInt_t exptIndex = this->iExpt();
	if ( iExptSet_.empty() && exptIndex != 0 ) {
		std::cerr << "ERROR in LauRooFitTask::readExperimentData : Invalid experiment number " << exptIndex << ", data contains only one experiment" << std::endl;
		return 0;
	} else if ( iExptSet_.find( exptIndex ) == iExptSet_.end() ) {
		std::cerr << "ERROR in LauRooFitTask::readExperimentData : Invalid experiment number " << exptIndex << std::endl;
		return 0;
	}

	// cleanup the data from any previous experiment
	delete exptData_;

	// retrieve the data and find out how many events have been read
	if ( iExptSet_.empty() ) {
		exptData_ = new RooDataSet( TString::Format("expt%dData",exptIndex), "", dataTree_, dataVars_, "", (weightVarName_ != "") ? weightVarName_.Data() : 0 );
	} else {
		const TString selectionString = TString::Format("iExpt==%d",exptIndex);
		TTree* exptTree = dataTree_->CopyTree(selectionString);
		exptData_ = new RooDataSet( TString::Format("expt%dData",exptIndex), "", exptTree, dataVars_, "", (weightVarName_ != "") ? weightVarName_.Data() : 0 );
		delete exptTree;
	}

	const UInt_t nEvent = exptData_->numEntries();
	this->eventsPerExpt( nEvent );
	return nEvent;
}

void LauRooFitTask::cacheInputFitVars()
{
	// cleanup the old NLL info
	delete nllVar_;

	// construct the new NLL variable for this dataset
	nllVar_ = new RooNLLVar("nllVar", "", model_, *exptData_, extended_);
}

void LauRooFitTask::finaliseExperiment( const LauAbsFitter::FitStatus& fitStat, const TObjArray* parsFromCoordinator, const TMatrixD* covMat, TObjArray& parsToCoordinator )
{
	// Copy the fit status information
	this->storeFitStatus( fitStat, *covMat );

	// Now process the parameters
	const UInt_t nFreePars = this->nFreeParams();
	UInt_t nPars = parsFromCoordinator->GetEntries();
	if ( nPars != nFreePars ) {
		std::cerr << "ERROR in LauRooFitTask::finaliseExperiment : Unexpected number of parameters received from coordinator" << std::endl;
		std::cerr << "                                            : Received " << nPars << " when expecting " << nFreePars << std::endl;
		gSystem->Exit( EXIT_FAILURE );
	}

	for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
		LauParameter* parameter = dynamic_cast<LauParameter*>( (*parsFromCoordinator)[iPar] );
		if ( ! parameter ) {
			std::cerr << "ERROR in LauRooFitTask::finaliseExperiment : Error reading parameter from coordinator" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		if ( parameter->name() != fitPars_[iPar]->name() ) {
			std::cerr << "ERROR in LauRooFitTask::finaliseExperiment : Error reading parameter from coordinator" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		*(fitPars_[iPar]) = *parameter;

		RooRealVar* rrv = fitVars_[iPar];
		rrv->setVal( parameter->value() );
		rrv->setError( parameter->error() );
		rrv->setAsymError( parameter->negError(), parameter->posError() );
	}

	// Update the pulls and add each finalised fit parameter to the list to
	// send back to the coordinator
	for ( std::vector<LauParameter*>::iterator iter = fitPars_.begin(); iter != fitPars_.end(); ++iter ) {
		(*iter)->updatePull();
		parsToCoordinator.Add( *iter );
	}

	// Write the results into the ntuple
	std::vector<LauParameter> extraVars;
	LauFitNtuple* ntuple = this->fitNtuple();
	ntuple->storeParsAndErrors(fitPars_, extraVars);

	// find out the correlation matrix for the parameters
	ntuple->storeCorrMatrix(this->iExpt(), this->fitStatus(), this->covarianceMatrix());

	// Fill the data into ntuple
	ntuple->updateFitNtuple();
}

