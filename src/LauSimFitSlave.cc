
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


ClassImp(LauSimFitSlave)


LauSimFitSlave::LauSimFitSlave() :
	sMaster_(0),
	messageFromMaster_(0),
	slaveId_(0),
	nSlaves_(0),
	nParams_(0),
	parValues_(0)
{
}

LauSimFitSlave::~LauSimFitSlave()
{
	delete sMaster_; sMaster_ = 0;
	delete messageFromMaster_; messageFromMaster_ = 0;
	delete[] parValues_; parValues_ = 0;
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

	delete messageFromMaster_;
	messageFromMaster_ = 0;

	std::cout << "INFO in LauSimFitSlave::connectToMaster : Established connection to master on port " << portMaster << std::endl;
	std::cout << "                                        : We are slave " << slaveId_ << " of " << nSlaves_ << std::endl;
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
				nParams_ = array.GetEntries();
				parValues_ = new Double_t[nParams_];

				messageToMaster.Reset( kMESS_OBJECT );
				messageToMaster.WriteObject( &array );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Read Expt" ) {

				// Read the data for this experiment
				UInt_t iExpt(0);
				messageFromMaster_->ReadUInt( iExpt );

				UInt_t nEvents = this->readExperimentData( iExpt );
				if ( nEvents < 1 ) {
					std::cerr << "WARNING in LauSimFitSlave::processMasterRequests : Zero events in experiment " << iExpt << ", the master should skip this experiment..." << std::endl;
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

			Int_t fitStatus(0);
			Double_t NLL(0.0);
			messageFromMaster_->ReadInt( fitStatus );
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
			this->finaliseResults( fitStatus, NLL, objarray, covMat, array );

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

			if ( nPars != nParams_ ) {
				std::cerr << "ERROR in LauSimFitSlave::processMasterRequests : Unexpected number of parameters received from master" << std::endl;
				std::cerr << "                                               : Received " << nPars << " when expecting " << nParams_ << std::endl;
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


