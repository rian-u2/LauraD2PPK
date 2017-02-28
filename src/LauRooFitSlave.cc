
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
#include "TString.h"
#include "TSystem.h"

#include "LauParameter.hh"
#include "LauSimFitSlave.hh"
#include "LauRooFitSlave.hh"

ClassImp(LauRooFitSlave)


LauRooFitSlave::LauRooFitSlave( RooAbsPdf& model, std::vector<RooAbsData*>& data, const Bool_t extended ) :
	LauSimFitSlave(),
	model_(model),
	data_(data),
	exptData_(0),
	extended_(extended),
	iExpt_(0),
	nEvent_(0),
	nllVar_(0),
	fitNtuple_(0),
	nFreeParams_(0),
	fitStatus_(0),
	NLL_(0.0)
{
}

LauRooFitSlave::~LauRooFitSlave()
{
	delete nllVar_; nllVar_ = 0;
	delete fitNtuple_; fitNtuple_ = 0;
}

void LauRooFitSlave::runSlave(const TString& /*dataFileName*/, const TString& /*dataTreeName*/,
			      const TString& histFileName, const TString& /*tableFileName*/,
			      const TString& addressMaster, const UInt_t portMaster)
{
	// TODO - should we actually use the dataFileName and dataTreeName to open a ROOT file and create the RooDataSet objects?
	//      - if so we will need to modify the constructor accordingly

	// Establish the connection to the master process
	this->connectToMaster( addressMaster, portMaster );

	// Create the ntuple in which to store the fit results
	std::cout << "INFO in LauRooFitSlave::fitSlave : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName, this->useAsymmFitErrors());

	// Now process the various requests from the master
	this->processMasterRequests();
}

void LauRooFitSlave::prepareInitialParArray( TObjArray& array )
{
	// Check that we've not already done this
	if ( ! fitVars_.empty() ) {
		std::cerr << "ERROR in LauRooFitSlave::prepareInitialParArray : have already processed fit variables, not doing so again" << std::endl;
		return;
	}

	// Check that the NLL variable has been initialised
	if ( ! nllVar_ ) {
		std::cerr << "ERROR in LauRooFitSlave::prepareInitialParArray : NLL var not initialised" << std::endl;
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
	return (nllVar_ != 0) ? nllVar_->getVal() : 0.0;
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
	if ( exptIndex >= data_.size() ) {
		std::cerr << "ERROR in LauRooFitSlave::readExperimentData : Invalid experiment number " << exptIndex << ", data contains " << data_.size() << " experiments" << std::endl;
		return 0;
	}

	// set our record of which experiment we're examining
	iExpt_ = exptIndex;

	// retrieve the data and find out how many events have been read
	exptData_ = data_[ iExpt_ ];
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

