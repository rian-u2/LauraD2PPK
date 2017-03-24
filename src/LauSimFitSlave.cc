
// Copyright University of Warwick 2013 - 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSimFitSlave.cc
    \brief File containing implementation of LauSimFitSlave class.
*/

#include <cstdlib>
#include <iostream>

#include "TMatrixD.h"
#include "TMessage.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TSocket.h"
#include "TSystem.h"

#include "LauSimFitSlave.hh"
#include "LauFitNtuple.hh"


ClassImp(LauSimFitSlave)


LauSimFitSlave::LauSimFitSlave() :
	sMaster_(0),
	messageFromMaster_(0),
	slaveId_(0),
	nSlaves_(0),
	parValues_(0),
	fitNtuple_(0)
{
}

LauSimFitSlave::~LauSimFitSlave()
{
	delete sMaster_;
	delete messageFromMaster_;
	delete[] parValues_;
	delete fitNtuple_;
}

void LauSimFitSlave::runSlave(const TString& dataFileName, const TString& dataTreeName,
			      const TString& histFileName, const TString& tableFileName,
			      const TString& addressMaster, const UInt_t portMaster)
{
	// Establish the connection to the master process
	this->connectToMaster( addressMaster, portMaster );

	// Initialise the fit model
	this->initialise();

	// NB call to addConParameters() is intentionally not included here cf.
	// LauAbsFitModel::run() since this has to be dealt with by the master
	// to avoid multiple inclusions of each penalty term
	// Print a warning if constraints on combinations of parameters have been specified
	const std::vector<StoreConstraints>& storeCon = this->constraintsStore();
	if ( ! storeCon.empty() ) {
		std::cerr << "WARNING in LauSimFitSlave::runSlave : Constraints have been added but these will be ignored - they should have been added to the master process" << std::endl;
	}

	// Setup saving of fit results to ntuple/LaTeX table etc.
	this->setupResultsOutputs( histFileName, tableFileName );

	// This reads in the given dataFile and creates an input
	// fit data tree that stores them for all events and experiments.
	Bool_t dataOK = this->cacheFitData(dataFileName,dataTreeName);
	if (!dataOK) {
		std::cerr << "ERROR in LauSimFitSlave::runSlave : Problem caching the fit data." << std::endl;
		return;
	}

	// Now process the various requests from the master
	this->processMasterRequests();

	std::cout << "INFO in LauSimFitSlave::runSlave : Fit slave " << this->slaveId() << " has finished successfully" << std::endl;
}

void LauSimFitSlave::setupResultsOutputs( const TString& histFileName, const TString& /*tableFileName*/ )
{
	// Create and setup the fit results ntuple
	std::cout << "INFO in LauSimFitSlave::setupResultsOutputs : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName, this->useAsymmFitErrors());
}

void LauSimFitSlave::connectToMaster( const TString& addressMaster, const UInt_t portMaster )
{
	if ( sMaster_ != 0 ) {
		std::cerr << "ERROR in LauSimFitSlave::connectToMaster : master socket already present" << std::endl;
		return;
	}

	// Open connection to master
	sMaster_ = new TSocket(addressMaster, portMaster);
	sMaster_->Recv( messageFromMaster_ );

	messageFromMaster_->ReadUInt( slaveId_ );
	messageFromMaster_->ReadUInt( nSlaves_ );

	Bool_t useAsymErrs(kFALSE);
	messageFromMaster_->ReadBool( useAsymErrs );
	this->useAsymmFitErrors(useAsymErrs);

	delete messageFromMaster_;
	messageFromMaster_ = 0;

	std::cout << "INFO in LauSimFitSlave::connectToMaster : Established connection to master on port " << portMaster << std::endl;
	std::cout << "                                        : We are slave " << slaveId_ << " of " << nSlaves_ << std::endl;
	if ( useAsymErrs ) {
		std::cout << "                                        : The fit will determine asymmetric errors" << std::endl;
	}
}

void LauSimFitSlave::processMasterRequests()
{
	// Listen for requests from the master and act accordingly

	TMessage messageToMaster(kMESS_ANY);

	while ( kTRUE ) {

		sMaster_->Recv( messageFromMaster_ );

		if ( messageFromMaster_->What() == kMESS_STRING ) {

			TString msgStr;
			messageFromMaster_->ReadTString( msgStr );

			std::cout << "INFO in LauSimFitSlave::processMasterRequests : Received message from master: " << msgStr << std::endl;

			if ( msgStr == "Send Parameters" ) {

				// Send the fit parameters

				TObjArray array;
				this->prepareInitialParArray( array );

				// Create array to efficiently exchange parameter values with master
				if ( parValues_ != 0 ) {
					delete[] parValues_;
					parValues_ = 0;
				}
				UInt_t nPar = array.GetEntries();
				parValues_ = new Double_t[nPar];

				messageToMaster.Reset( kMESS_OBJECT );
				messageToMaster.WriteObject( &array );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Read Expt" ) {

				// Read the data for this experiment
				UInt_t iExp(0);
				messageFromMaster_->ReadUInt( iExp );

				this->setCurrentExperiment( iExp );

				UInt_t nEvents = this->readExperimentData();
				if ( nEvents < 1 ) {
					std::cerr << "WARNING in LauSimFitSlave::processMasterRequests : Zero events in experiment " << iExp << ", the master should skip this experiment..." << std::endl;
				}

				messageToMaster.Reset( kMESS_ANY );
				messageToMaster.WriteUInt( slaveId_ );
				messageToMaster.WriteUInt( nEvents );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Cache" ) {

				// Perform the caching

				this->cacheInputFitVars();

				messageToMaster.Reset( kMESS_ANY );
				messageToMaster.WriteUInt( slaveId_ );
				messageToMaster.WriteBool( kTRUE );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Asym Error Calc" ) {

				Bool_t asymErrorCalc(kFALSE);
				messageFromMaster_->ReadBool( asymErrorCalc );
				this->withinAsymErrorCalc( asymErrorCalc );

				messageToMaster.Reset( kMESS_ANY );
				messageToMaster.WriteUInt( slaveId_ );
				messageToMaster.WriteBool( asymErrorCalc );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Write Results" ) {

				this->writeOutAllFitResults();

				messageToMaster.Reset( kMESS_ANY );
				messageToMaster.WriteUInt( slaveId_ );
				messageToMaster.WriteBool( kTRUE );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Finish" ) {

				std::cout << "INFO in LauSimFitSlave::processMasterRequests : Message from master to finish" << std::endl;
				break;

			} else {

				std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Unexpected message from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );

			}

		} else if ( messageFromMaster_->What() == kMESS_OBJECT ) {

			std::cout << "INFO in LauSimFitSlave::processMasterRequests : Received message from master: Finalise" << std::endl;

			Int_t status(0);
			Double_t NLL(0.0);
			messageFromMaster_->ReadInt( status );
			messageFromMaster_->ReadDouble( NLL );

			TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromMaster_->ReadObject( messageFromMaster_->GetClass() ) );
			if ( ! objarray ) {
				std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Error reading parameters from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			TMatrixD * covMat = dynamic_cast<TMatrixD*>( messageFromMaster_->ReadObject( messageFromMaster_->GetClass() ) );
			if ( ! covMat ) {
				std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Error reading covariance matrix from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			TObjArray array;
			this->finaliseExperiment( status, NLL, objarray, covMat, array );

			delete objarray; objarray = 0;
			delete covMat; covMat = 0;

			// Send the finalised parameters back to the master
			messageToMaster.Reset( kMESS_ANY );
			messageToMaster.WriteUInt( slaveId_ );
			messageToMaster.WriteBool( kTRUE );
			messageToMaster.WriteObject( &array );
			sMaster_->Send( messageToMaster );

		} else if ( messageFromMaster_->What() == kMESS_ANY ) {

			UInt_t nPars(0);
			UInt_t nFreePars(0);
			messageFromMaster_->ReadUInt( nPars );
			messageFromMaster_->ReadUInt( nFreePars );

			if ( nPars != this->nTotParams() ) {
				std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Unexpected number of parameters received from master" << std::endl;
				std::cerr << "                                               : Received " << nPars << " when expecting " << this->nTotParams() << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			messageFromMaster_->ReadFastArray( parValues_, nPars );

			this->setParsFromMinuit( parValues_, nFreePars );

			Double_t negLogLike = this->getTotNegLogLikelihood();

			messageToMaster.Reset( kMESS_ANY );
			messageToMaster.WriteDouble( negLogLike );   
			sMaster_->Send( messageToMaster );         

		} else {
			std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Unexpected message type" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		delete messageFromMaster_;
		messageFromMaster_ = 0;
	}
}

void LauSimFitSlave::writeOutAllFitResults()
{
	// Write out histograms at end
	if (fitNtuple_ != 0) {
		fitNtuple_->writeOutFitResults();
	}
}

