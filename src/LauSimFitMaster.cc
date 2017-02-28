
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSimFitMaster.cc
    \brief File containing implementation of LauSimFitMaster class.
*/

#include <cstdlib>
#include <iostream>

#include "TMatrixD.h"
#include "TMessage.h"
#include "TMonitor.h"
#include "TObjArray.h"
#include "TObjString.h"
#include "TServerSocket.h"
#include "TSocket.h"
#include "TSystem.h"

#include "LauAbsFitter.hh"
#include "LauFitNtuple.hh"
#include "LauFitter.hh"
#include "LauFormulaPar.hh"
#include "LauParameter.hh"
#include "LauParamFixed.hh"
#include "LauSimFitMaster.hh"


ClassImp(LauSimFitMaster)


LauSimFitMaster::LauSimFitMaster( UInt_t numSlaves, UInt_t port ) :
	nSlaves_(numSlaves),
	reqPort_(port),
	nParams_(0),
	nFreeParams_(0),
	twoStageFit_(kFALSE),
	useAsymmFitErrors_(kFALSE),
	numberOKFits_(0),
	numberBadFits_(0),
	fitStatus_(0),
	iExpt_(0),
	NLL_(0.0),
	socketMonitor_(0),
	messageFromSlave_(0),
	fitNtuple_(0)
{
	messagesToSlaves_.resize( nSlaves_ );
	for ( UInt_t iSlave(0); iSlave < nSlaves_; ++iSlave ) {
		messagesToSlaves_[iSlave] = new TMessage();
	}
}

LauSimFitMaster::~LauSimFitMaster()
{
	delete socketMonitor_; socketMonitor_ = 0;

	// Tell all slaves that they are finished and delete corresponding socket
	TString msgStr("Finish");
	TMessage message( kMESS_STRING );
	message.WriteTString(msgStr);
	for ( std::vector<TSocket*>::iterator iter = sSlaves_.begin(); iter != sSlaves_.end(); ++iter ) {
		(*iter)->Send(message);
		(*iter)->Close();
		delete (*iter);
	}
	sSlaves_.clear();

	// Remove the components created to apply constraints to fit parameters
	for (std::vector<LauAbsRValue*>::iterator iter = conVars_.begin(); iter != conVars_.end(); ++iter){
		if ( !(*iter)->isLValue() ){
			delete (*iter);
			(*iter) = 0;
		}
	}
	conVars_.clear();

	// Remove all fit parameters
	for ( std::vector<LauParameter*>::iterator iter = params_.begin(); iter != params_.end(); ++iter ) {
		delete *iter;
	}
	params_.clear();

	for ( std::vector<Double_t*>::iterator iter = vectorPar_.begin(); iter != vectorPar_.end(); ++iter ) {
		delete[] (*iter);
	}
	vectorPar_.clear();

	delete messageFromSlave_; messageFromSlave_ = 0;

	for ( std::vector<TMessage*>::iterator iter = messagesToSlaves_.begin(); iter != messagesToSlaves_.end(); ++iter ) {
		delete (*iter);
	}
	messagesToSlaves_.clear();

	delete fitNtuple_;
}

void LauSimFitMaster::initSockets()
{
	if ( socketMonitor_ != 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::initSockets : Sockets already initialised." << std::endl;
		return;
	}

	//initialise socket connection, then accept a connection and return a full-duplex communication socket.
	socketMonitor_ = new TMonitor();

	TServerSocket *ss = new TServerSocket( reqPort_, kFALSE );
	UInt_t actual_port = ss->GetLocalPort();

	std::cout << "INFO in LauSimFitMaster::initSockets : Waiting for connection with " << nSlaves_ << " workers on port " << actual_port << std::endl;

	sSlaves_.resize(nSlaves_);
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		sSlaves_[iSlave] = ss->Accept();
		std::cout << "                                     : Added slave " << iSlave << std::endl;
	}

	// tell the clients to start
	std::cout << "INFO in LauSimFitMaster::initSockets : Initialising slaves" << std::endl;
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {

		TMessage message( kMESS_ANY );
		message.WriteUInt(iSlave);
		message.WriteUInt(nSlaves_);
		message.WriteBool(useAsymmFitErrors_);

		sSlaves_[iSlave]->Send(message);

		socketMonitor_->Add(sSlaves_[iSlave]);
	}
	std::cout << "                                     : Now start fit\n" << std::endl;

	ss->Close();
	delete ss;
}

/*
 * OLD VERSION THAT JUST GETS THE NAMES - COULD HAVE A SERIES OF EXCHANGES TO GET THE NAMES, INIT VALUES, RANGES, ETC. INSTEAD OF PASSING PARAMETERS
 * THIS INCREASES THE GENERALITY OF THE CODE, I.E. THERE IS NO NEED FOR THE SLAVES TO KNOW ANY LAURA++ CLASS BUT THIS ONE, BUT MAKES IT RATHER MORE DENSE
 * FOR THE MOMENT I WILL STICK WITH THE METHOD OF PASSING LAUPARAMETER OBJECTS AROUND AND CONSIDER GOING BACK TO THIS GENERAL METHOD ONCE EVERYTHING IS WORKING
 *
void LauSimFitMaster::getParametersFromSlavesFirstTime()
{
	slaveIndices_.resize( nSlaves_ );

	TSocket* sActive(0);
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		// Send a message to the slave, requesting the list of parameter names
		TString msgStr = "Parameter Names";
		TMessage message( kMESS_STRING );
		message.WriteTString( msgStr );
		sSlaves_[iSlave]->Send(message);

		// Wait to receive the response and check that it has come from the slave we just requested from
		sActive = socketMonitor_->Select();
		if ( sActive != sSlaves_[iSlave] ) {
			std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Received message from a different slave than expected!" << std::endl;
			gSystem->Exit(1);
		}

		// Read the object and extract the parameter names
		sSlaves_[iSlave]->Recv( messageFromSlave_ );
		TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromSlave_->ReadObject( messageFromSlave_->GetClass() ) );
		if ( ! objarray ) {
			std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Error reading parameter names from slave" << std::endl;
			gSystem->Exit(1);
		}

		Int_t nPars = objarray->GetEntries();
		for ( Int_t iPar(0); iPar < nPars; ++iPar ) {
			TObjString* objstring = dynamic_cast<TObjString*>( (*objarray)[iPar] );
			if ( ! objstring ) {
				std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Error reading parameter names from slave" << std::endl;
				gSystem->Exit(1);
			}
			TString parname = objstring->GetString();

			std::map< TString, UInt_t >::iterator iter = parIndices_.find( parname );
			if ( iter != parIndices_.end() ) {
				UInt_t index = iter->second;
				slaveIndices_[iSlave].push_back( index );
			} else {
				UInt_t index = parIndices_.size();
				parIndices_.insert( std::make_pair( parname, index ) );
				parNames_.insert( std::make_pair( index, parname ) );
				slaveIndices_[iSlave].push_back( index );
			}
		}

		delete objarray; objarray = 0;
		delete messageFromSlave_; messageFromSlave_ = 0;
	}

	UInt_t nPars = parNames_.size();
	parValues_.resize( nPars );
}
*/

void LauSimFitMaster::getParametersFromSlaves()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlaves : Sockets not initialised." << std::endl;
		return;
	}

	if ( params_.empty() ) {
		this->getParametersFromSlavesFirstTime();

		// Add variables to Gaussian constrain to a list
		this->addConParameters();
	} else {
		this->updateParametersFromSlaves();
	}
}

void LauSimFitMaster::updateParametersFromSlaves()
{
	TSocket* sActive(0);

	// Construct a message, requesting the list of parameter names
	TString msgStr = "Send Parameters";
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );

	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		// Send the message to the slave
		sSlaves_[iSlave]->Send(message);

		// Wait to receive the response and check that it has come from the slave we just requested from
		sActive = socketMonitor_->Select();
		if ( sActive != sSlaves_[iSlave] ) {
			std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Received message from a different slave than expected!" << std::endl;
			gSystem->Exit(1);
		}

		// Read the object and extract the parameter names
		sSlaves_[iSlave]->Recv( messageFromSlave_ );
		TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromSlave_->ReadObject( messageFromSlave_->GetClass() ) );
		if ( ! objarray ) {
			std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Error reading parameter names from slave" << std::endl;
			gSystem->Exit(1);
		}

		// We want to auto-delete the supplied parameters since we only copy their values in this case
		objarray->SetOwner(kTRUE);

		const UInt_t nPars = objarray->GetEntries();
		if ( nPars != slaveIndices_[iSlave].size() ) {
			std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Unexpected number of parameters received from slave" << std::endl;
			gSystem->Exit(1);
		}

		for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
			LauParameter* parameter = dynamic_cast<LauParameter*>( (*objarray)[iPar] );
			if ( ! parameter ) {
				std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Error reading parameter from slave" << std::endl;
				gSystem->Exit(1);
			}

			TString parname = parameter->name();
			Double_t parvalue = parameter->initValue();

			std::map< TString, UInt_t >::iterator iter = parIndices_.find( parname );
			if ( iter == parIndices_.end() ) {
				std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Unexpected parameter name received from slave" << std::endl;
				gSystem->Exit(1);
			}

			const UInt_t index = iter->second;
			if ( slaveIndices_[iSlave][iPar] != index ) {
				std::cerr << "ERROR in LauSimFitMaster::updateParametersFromSlaves : Unexpected parameter received from slave" << std::endl;
				gSystem->Exit(1);
			}

			params_[index]->initValue( parvalue );
			parValues_[index] = parvalue;
			vectorPar_[iSlave][iPar] = parvalue;
			this->checkParameter( parameter, index );
		}

		delete objarray; objarray = 0;
		delete messageFromSlave_; messageFromSlave_ = 0;
	}
}

void LauSimFitMaster::getParametersFromSlavesFirstTime()
{
	slaveIndices_.resize( nSlaves_ );
	slaveFreeIndices_.resize( nSlaves_ );
	vectorPar_.resize( nSlaves_ );
	vectorRes_.resize( nSlaves_ );

	TSocket* sActive(0);

	// Construct a message, requesting the list of parameter names
	TString msgStr = "Send Parameters";
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );

	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		// Send the message to the slave
		sSlaves_[iSlave]->Send(message);

		// Wait to receive the response and check that it has come from the slave we just requested from
		sActive = socketMonitor_->Select();
		if ( sActive != sSlaves_[iSlave] ) {
			std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Received message from a different slave than expected!" << std::endl;
			gSystem->Exit(1);
		}

		// Read the object and extract the parameter names
		sSlaves_[iSlave]->Recv( messageFromSlave_ );
		TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromSlave_->ReadObject( messageFromSlave_->GetClass() ) );
		if ( ! objarray ) {
			std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Error reading parameters from slave" << std::endl;
			gSystem->Exit(1);
		}

		const UInt_t nPars = objarray->GetEntries();

		vectorPar_[iSlave] = new Double_t[nPars];

		for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
			LauParameter* parameter = dynamic_cast<LauParameter*>( (*objarray)[iPar] );
			if ( ! parameter ) {
				std::cerr << "ERROR in LauSimFitMaster::getParametersFromSlavesFirstTime : Error reading parameter from slave" << std::endl;
				gSystem->Exit(1);
			}

			TString parname = parameter->name();
			Double_t parvalue = parameter->initValue();
			Bool_t parfixed = parameter->fixed();

			std::map< TString, UInt_t >::iterator iter = parIndices_.find( parname );
			if ( iter != parIndices_.end() ) {
				UInt_t index = iter->second;
				slaveIndices_[iSlave].push_back( index );
				if ( ! parfixed ) {
					slaveFreeIndices_[iSlave].push_back( index );
				}
				this->checkParameter( parameter, index );
			} else {
				UInt_t index = parIndices_.size();
				parIndices_.insert( std::make_pair( parname, index ) );
				parNames_.insert( std::make_pair( index, parname ) );
				slaveIndices_[iSlave].push_back( index );
				if ( ! parfixed ) {
					slaveFreeIndices_[iSlave].push_back( index );
				}
				params_.push_back( parameter );
				parValues_.push_back( parvalue );
			}
			vectorPar_[iSlave][iPar] = parvalue;
		}

		delete objarray; objarray = 0;
		delete messageFromSlave_; messageFromSlave_ = 0;
	}

	nParams_ = params_.size();
}

void LauSimFitMaster::printParInfo() const
{
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		const std::vector<UInt_t>& indices = slaveIndices_[iSlave];

		std::cout << "INFO in LauSimFitMaster::printParInfo : Slave " << iSlave << " has the following parameters:\n";
		for ( std::vector<UInt_t>::const_iterator iter = indices.begin(); iter != indices.end(); ++iter ) {
			const TString& parName = parNames_.find(*iter)->second;
			Double_t parValue = parValues_[*iter];
			const LauParameter* par = params_[*iter];
			if ( par->name() != parName || par->initValue() != parValue ) {
				std::cerr << "ERROR in LauSimFitMaster::printParInfo : Discrepancy in parameter name and value records, this is very strange!!" << std::endl;
			}

			std::cout << "                                      : " << parName << " = " << parValue << " and has index " << *iter << "\n";
		}

		std::cout << std::endl;
	}

	std::cout << "INFO in LauSimFitMaster::printParInfo : " << "There are " << nParams_ << " parameters in total" << std::endl;
}

void LauSimFitMaster::checkParameter( const LauParameter* param, UInt_t index ) const
{
	const LauParameter* storedPar = params_[index];

	TString parName = storedPar->name();
	if ( param->name() != parName ) {
		std::cerr << "ERROR in LauSimFitMaster::checkParameter : Parameter name is different!!  This shouldn't happen!!" << std::endl;
	}
	if ( param->initValue() != storedPar->initValue() ) {
		std::cerr << "WARNING in LauSimFitMaster::checkParameter : Initial value for parameter " << parName << " is different, will use the value first set: " << storedPar->initValue() << std::endl;
	}
	if ( param->minValue() != storedPar->minValue() ) {
		std::cerr << "WARNING in LauSimFitMaster::checkParameter : Minimum allowed value for parameter " << parName << " is different, will use the value first set: " << storedPar->minValue() << std::endl;
	}
	if ( param->maxValue() != storedPar->maxValue() ) {
		std::cerr << "WARNING in LauSimFitMaster::checkParameter : Maximum allowed value for parameter " << parName << " is different, will use the value first set: " << storedPar->maxValue() << std::endl;
	}
	if ( param->fixed() != storedPar->fixed() ) {
		std::cerr << "WARNING in LauSimFitMaster::checkParameter : Fixed/floating property of parameter " << parName << " is different, will use the value first set: " << (storedPar->fixed() ? "fixed" : "floating") << std::endl;
	}
	if ( param->secondStage() != storedPar->secondStage() ) {
		std::cerr << "WARNING in LauSimFitMaster::checkParameter : Second stage property of parameter " << parName << " is different, will use the value first set: " << (storedPar->secondStage() ? "true" : "false") << std::endl;
	}
}

void LauSimFitMaster::initialise()
{
	this->initSockets();
}

void LauSimFitMaster::runSimFit( const TString& fitNtupleFileName, UInt_t nExpt, UInt_t firstExpt, Bool_t useAsymmErrors, Bool_t twoStageFit )
{
	// Routine to perform the total fit.
	useAsymmFitErrors_ = useAsymmErrors;
	twoStageFit_ = twoStageFit;

	// First, initialise
	this->initialise();

	std::cout << "INFO in LauSimFitMaster::runSimFit : First experiment = " << firstExpt << std::endl;
	std::cout << "INFO in LauSimFitMaster::runSimFit : Number of experiments = " << nExpt << std::endl;

	// Start the cumulative timer
	cumulTimer_.Start();

	numberOKFits_ = 0, numberBadFits_ = 0;
	fitStatus_ = -1;

	// Create and setup the fit results ntuple
	std::cout << "INFO in LauSimFitMaster::runSimFit : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(fitNtupleFileName, useAsymmFitErrors_);

	// Loop over the number of experiments
	for (iExpt_ = firstExpt; iExpt_ < (firstExpt+nExpt); ++iExpt_) {

		// Start the timer to see how long each fit takes
		timer_.Start();

		// Instruct the slaves to read the data for this experiment
		Bool_t readOK = this->readData();
		if ( ! readOK ) {
			std::cerr << "ERROR in LauSimFitMaster::runSimFit : One or more slaves reported problems with reading data for experiment " << iExpt_ << ", skipping..." << std::endl;
			timer_.Stop();
			continue;
		}

		// Instruct the slaves to perform the caching
		this->cacheInputData();

		// Do the fit
		this->fitExpt();

		// Stop the timer and see how long the program took so far
		timer_.Stop();
		timer_.Print();

		// Instruct the slaves to finalise the results
		this->finalise();

		// Keep track of how many fits succeeded or failed
		if (fitStatus_ == 3) {
			++numberOKFits_;
		} else {
			++numberBadFits_;
		}
	}

	// Print out total timing info.
	std::cout << "INFO in LauSimFitMaster::runSimFit : Cumulative timing:" << std::endl;
	cumulTimer_.Stop();
	cumulTimer_.Print();

	// Print out stats on OK fits.
	std::cout << "INFO in LauSimFitMaster::runSimFit : Number of OK Fits = " << numberOKFits_ << std::endl;
	std::cout << "INFO in LauSimFitMaster::runSimFit : Number of Failed Fits = " << numberBadFits_ << std::endl;
	Double_t fitEff(0.0);
	if (nExpt != 0) {fitEff = numberOKFits_/(1.0*nExpt);}
	std::cout << "INFO in LauSimFitMaster::runSimFit : Fit efficiency = " << fitEff*100.0 << "%." << std::endl;

	// Instruct the slaves to write out any fit results (ntuples etc...).
	this->writeOutResults();
}

void LauSimFitMaster::withinAsymErrorCalc(const Bool_t inAsymErrCalc)
{
	this->LauFitObject::withinAsymErrorCalc(inAsymErrCalc);

	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::withinAsymErrorCalc : Sockets not initialised." << std::endl;
		return;
	}

	// Construct a message, informing the slaves whether or not we are now within the asymmetric error calculation
	TString msgStr("Asym Error Calc");
	const Bool_t asymErrorCalc( this->withinAsymErrorCalc() );
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );
	message.WriteBool( asymErrorCalc );

	// Send the message to the slaves
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		sSlaves_[iSlave]->Send(message);
	}

	TSocket* sActive(0);
	UInt_t responsesReceived(0);
	while ( responsesReceived != nSlaves_ ) {

		// Get the next queued response
		sActive = socketMonitor_->Select();

		// Extract from the message the ID of the slave and the number of events read
		Bool_t response(kTRUE);
		UInt_t iSlave(0);
		sActive->Recv( messageFromSlave_ );
		messageFromSlave_->ReadUInt( iSlave );
		messageFromSlave_->ReadBool( response );

		if ( response != asymErrorCalc ) {
			std::cerr << "WARNING in LauSimFitMaster::withinAsymErrorCalc : Problem informing slave " << iSlave << std::endl;
		}

		++responsesReceived;
	}

}

Bool_t LauSimFitMaster::readData()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::readData : Sockets not initialised." << std::endl;
		return kFALSE;
	}

	// Construct a message, requesting to read the data for the given experiment
	TString msgStr("Read Expt");
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );
	message.WriteUInt( iExpt_ );

	// Send the message to the slaves
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		sSlaves_[iSlave]->Send(message);
	}

	TSocket* sActive(0);
	UInt_t responsesReceived(0);
	Bool_t ok(kTRUE);
	while ( responsesReceived != nSlaves_ ) {

		// Get the next queued response
		sActive = socketMonitor_->Select();

		// Extract from the message the ID of the slave and the number of events read
		sActive->Recv( messageFromSlave_ );
		UInt_t iSlave(0);
		UInt_t nEvents(0);
		messageFromSlave_->ReadUInt( iSlave );
		messageFromSlave_->ReadUInt( nEvents );

		if ( nEvents <= 0 ) {
			std::cerr << "ERROR in LauSimFitMaster::readData : Slave " << iSlave << " reports no events found for experiment " << iExpt_ << std::endl;
			ok = kFALSE;
		} else {
			std::cerr << "INFO in LauSimFitMaster::readData : Slave " << iSlave << " reports " << nEvents << " events found for experiment " << iExpt_ << std::endl;
		}

		++responsesReceived;
	}

	return ok;
}

Bool_t LauSimFitMaster::cacheInputData()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::cacheInputData : Sockets not initialised." << std::endl;
		return kFALSE;
	}

	// Construct a message, requesting it to read the data for the given experiment
	TString msgStr("Cache");
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );

	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		// Send the message to the slave
		sSlaves_[iSlave]->Send(message);
	}

	TSocket* sActive(0);
	UInt_t responsesReceived(0);
	Bool_t allOK(kTRUE);
	while ( responsesReceived != nSlaves_ ) {

		// Get the next queued response
		sActive = socketMonitor_->Select();

		// Extract from the message the ID of the slave and the success/failure flag
		sActive->Recv( messageFromSlave_ );
		UInt_t iSlave(0);
		Bool_t ok(kTRUE);
		messageFromSlave_->ReadUInt( iSlave );
		messageFromSlave_->ReadBool( ok );

		if ( ! ok ) {
			std::cerr << "ERROR in LauSimFitMaster::cacheInputData : Slave " << iSlave << " reports an error performing caching" << std::endl;
			allOK = kFALSE;
		}

		++responsesReceived;
	}

	return allOK;
}

void LauSimFitMaster::checkInitFitParams()
{
	this->getParametersFromSlaves();
	this->printParInfo();
}

void LauSimFitMaster::fitExpt()
{
	// Routine to perform the actual fit for the given experiment

	// Instruct the salves to update initial fit parameters if required (e.g. if using random numbers).
	this->checkInitFitParams();

	// Initialise the fitter
	LauFitter::fitter()->useAsymmFitErrors( useAsymmFitErrors_ );
	LauFitter::fitter()->twoStageFit( twoStageFit_ );
	LauFitter::fitter()->initialise( this, params_ );

	nParams_ = LauFitter::fitter()->nParameters();
	nFreeParams_ = LauFitter::fitter()->nFreeParameters();

	// Now ready for minimisation step
	std::cout << "\nINFO in LauSimFitMaster::fitExpt : Start minimisation...\n";
	std::pair<Int_t,Double_t> fitResult = LauFitter::fitter()->minimise();

	fitStatus_ = fitResult.first;
	NLL_       = fitResult.second;

	// If we're doing a two stage fit we can now release (i.e. float)
	// the 2nd stage parameters and re-fit
	if ( twoStageFit_ ) {

		if ( fitStatus_ != 3 ) {
			std::cerr << "ERROR in LauSimFitMaster:fitExpt : Not running second stage fit since first stage failed." << std::endl;
			LauFitter::fitter()->releaseSecondStageParameters();
		} else {
			LauFitter::fitter()->releaseSecondStageParameters();
			nParams_ = LauFitter::fitter()->nParameters();
			nFreeParams_ = LauFitter::fitter()->nFreeParameters();
			fitResult = LauFitter::fitter()->minimise();
		}
	}

	fitStatus_ = fitResult.first;
	NLL_       = fitResult.second;
	const TMatrixD& covMat = LauFitter::fitter()->covarianceMatrix();
	covMatrix_.Clear();
	covMatrix_.ResizeTo( covMat.GetNrows(), covMat.GetNcols() );
	covMatrix_.SetMatrixArray( covMat.GetMatrixArray() );

	// Store the final fit results and errors into protected internal vectors that
	// all sub-classes can use within their own finalFitResults implementation
	// used below (e.g. putting them into an ntuple in a root file)
	LauFitter::fitter()->updateParameters();
}

void LauSimFitMaster::setParsFromMinuit(Double_t* par, Int_t npar)
{
	// This function sets the internal parameters based on the values
	// that Minuit is using when trying to minimise the total likelihood function.

	// MINOS reports different numbers of free parameters depending on the
	// situation, so disable this check
	if ( ! this->withinAsymErrorCalc() ) {
		if (static_cast<UInt_t>(npar) != nFreeParams_) {
			std::cerr << "ERROR in LauSimFitMaster::setParsFromMinuit : Unexpected number of free parameters: " << npar << ".\n";
			std::cerr << "                                              Expected: " << nFreeParams_ << ".\n" << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Despite npar being the number of free parameters
	// the par array actually contains all the parameters,
	// free and floating...
	// Update all the parameters with their new values.
	// Change the value in the array to be sent out to the slaves and the
	// parameters themselves (so that constraints are correctly calculated)
	for (UInt_t i(0); i<nParams_; ++i) {
		if (!params_[i]->fixed()) {
			parValues_[i] = par[i];
			params_[i]->value(par[i]);
		}
	}
}

Double_t LauSimFitMaster::getTotNegLogLikelihood()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::getTotNegLogLikelihood : Sockets not initialised." << std::endl;
		return 0.0;
	}

	// Send current values of the parameters to the slaves.
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {

		std::vector<UInt_t>& indices = slaveIndices_[iSlave];
		std::vector<UInt_t>& freeIndices = slaveFreeIndices_[iSlave];
		UInt_t nPars = indices.size();
		UInt_t nFreePars = freeIndices.size();
		for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
			vectorPar_[iSlave][iPar] = parValues_[ indices[iPar] ];
		}

		TMessage* message = messagesToSlaves_[iSlave];
		message->Reset( kMESS_ANY );
		message->WriteUInt( nPars );
		message->WriteUInt( nFreePars );
		message->WriteFastArray( vectorPar_[iSlave], nPars );

		sSlaves_[iSlave]->Send(*message);
	}

	Double_t negLogLike(0.0);
	TSocket  *sActive(0);
	UInt_t responsesReceived(0);
	while ( responsesReceived != nSlaves_ ) {

		sActive = socketMonitor_->Select();
		sActive->Recv(messageFromSlave_);	    

		messageFromSlave_->ReadDouble( vectorRes_[responsesReceived] );

		negLogLike += vectorRes_[responsesReceived];

		++responsesReceived;
	} 

	// Calculate any penalty terms from Gaussian constrained variables
	if ( ! conVars_.empty() ){
		negLogLike += this->getLogLikelihoodPenalty();
	}

	return negLogLike;
}

Double_t LauSimFitMaster::getLogLikelihoodPenalty()
{
	Double_t penalty(0.0);

	for ( std::vector<LauAbsRValue*>::const_iterator iter = conVars_.begin(); iter != conVars_.end(); ++iter ) {
		Double_t val = (*iter)->unblindValue();
		Double_t mean = (*iter)->constraintMean();
		Double_t width = (*iter)->constraintWidth();

		Double_t term = ( val - mean )*( val - mean );
		penalty += term/( 2*width*width );
	}

	return penalty;
}

void LauSimFitMaster::addConstraint(const TString& formula, const std::vector<TString>& pars, const Double_t mean, const Double_t width)
{
	StoreConstraints newCon;
	newCon.formula_ = formula;
	newCon.conPars_ = pars;
	newCon.mean_ = mean;
	newCon.width_ = width;
	storeCon_.push_back(newCon);
}

void LauSimFitMaster::addConParameters()
{
	// Add penalties from the constraints to fit parameters

	// First, constraints on the fit parameters themselves
	for ( std::vector<LauParameter*>::const_iterator iter = params_.begin(); iter != params_.end(); ++iter ) {
		if ( (*iter)->gaussConstraint() ) {
			conVars_.push_back( *iter );
			std::cout << "INFO in LauSimFitMaster::addConParameters : Added Gaussian constraint to parameter "<< (*iter)->name() << std::endl;
		}
	}

	// Second, constraints on arbitrary combinations
	for ( std::vector<StoreConstraints>::iterator iter = storeCon_.begin(); iter != storeCon_.end(); ++iter ) {
		std::vector<TString> names = (*iter).conPars_;
		std::vector<LauParameter*> params;
		for ( std::vector<TString>::iterator iternames = names.begin(); iternames != names.end(); ++iternames ) { 
			for ( std::vector<LauParameter*>::const_iterator iterfit = params_.begin(); iterfit != params_.end(); ++iterfit ) {
				if ( (*iternames) == (*iterfit)->name() ){
					params.push_back(*iterfit);
				}
			}
		}

		// If the parameters are not found, skip it
		if ( params.size() != (*iter).conPars_.size() ) {
			std::cerr << "WARNING in LauSimFitMaster::addConParameters: Could not find parameters to constrain in the formula... skipping" << std::endl;
			continue;
		}

		LauFormulaPar* formPar = new LauFormulaPar( (*iter).formula_, (*iter).formula_, params );
		formPar->addGaussianConstraint( (*iter).mean_, (*iter).width_ );
		conVars_.push_back(formPar);

		std::cout << "INFO in LauSimFitMaster::addConParameters : Added Gaussian constraint to formula\n";
		std::cout << "                                          : Formula: " << (*iter).formula_ << std::endl;
		for ( std::vector<LauParameter*>::iterator iterparam = params.begin(); iterparam != params.end(); ++iterparam ) {
			std::cout << "                                          : Parameter: " << (*iterparam)->name() << std::endl;
		}
	}
	
}

Bool_t LauSimFitMaster::finalise()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::finalise : Sockets not initialised." << std::endl;
		return kFALSE;
	}

	// Prepare the covariance matrices
	covMatrices_.resize( nSlaves_ );

	LauParamFixed pred;

	std::map<UInt_t,UInt_t> freeParIndices;

	UInt_t counter(0);
	for ( UInt_t iPar(0); iPar < nParams_; ++iPar ) {
		const LauParameter* par = params_[iPar];
		if ( ! pred(par) ) {
			freeParIndices.insert( std::make_pair(iPar,counter) );
			++counter;
		}
	}

	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		const UInt_t nPar = slaveIndices_[iSlave].size();

		std::vector<UInt_t> freeIndices;
		freeIndices.reserve( nPar );

		for ( UInt_t iPar(0); iPar < nPar; ++iPar ) {
			UInt_t index = slaveIndices_[iSlave][iPar];
			std::map<UInt_t,UInt_t>::iterator freeIter = freeParIndices.find(index);
			if ( freeIter == freeParIndices.end() ) {
				continue;
			}
			UInt_t freeIndex = freeIter->second;
			freeIndices.push_back( freeIndex );
		}

		const UInt_t nFreePars = freeIndices.size();
		TMatrixD& covMat = covMatrices_[iSlave];
		covMat.ResizeTo( nFreePars, nFreePars );

		for ( UInt_t iPar(0); iPar < nFreePars; ++iPar ) {
			for ( UInt_t jPar(0); jPar < nFreePars; ++jPar ) {
				UInt_t i = freeIndices[iPar];
				UInt_t j = freeIndices[jPar];
				covMat( iPar, jPar ) = covMatrix_( i, j );
			}
		}
	}

	// The array to hold the parameters
	TObjArray array;

	// Send messages to all slaves containing the final parameters and fit status, NLL
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {

		array.Clear();

		std::vector<UInt_t>& indices = slaveIndices_[iSlave];
		UInt_t nPars = indices.size();
		for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
			array.Add( params_[ indices[iPar] ] );
		}

		TMatrixD& covMat = covMatrices_[iSlave];

		TMessage* message = messagesToSlaves_[iSlave];
		message->Reset( kMESS_OBJECT );
		message->WriteInt( fitStatus_ );
		message->WriteDouble( NLL_ );
		message->WriteObject( &array );
		message->WriteObject( &covMat );

		sSlaves_[iSlave]->Send(*message);
	}

	TSocket  *sActive(0);
	UInt_t responsesReceived(0);
	Bool_t allOK(kTRUE);
	while ( responsesReceived != nSlaves_ ) {

		// Get the next queued response
		sActive = socketMonitor_->Select();

		// Extract from the message the ID of the slave and the number of events read
		sActive->Recv( messageFromSlave_ );
		UInt_t iSlave(0);
		Bool_t ok(kTRUE);
		messageFromSlave_->ReadUInt( iSlave );
		messageFromSlave_->ReadBool( ok );

		if ( ok ) {
			TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromSlave_->ReadObject( messageFromSlave_->GetClass() ) );
			if ( ! objarray ) {
				std::cerr << "ERROR in LauSimFitMaster::finalise : Error reading finalised parameters from slave" << std::endl;
				allOK = kFALSE;
			} else {
				// We want to auto-delete the supplied parameters since we only copy their values in this case
				objarray->SetOwner(kTRUE);

				const UInt_t nPars = objarray->GetEntries();
				if ( nPars != slaveIndices_[iSlave].size() ) {
					std::cerr << "ERROR in LauSimFitMaster::finalise : Unexpected number of finalised parameters received from slave" << std::endl;
					allOK = kFALSE;
				} else {
					for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
						LauParameter* parameter = dynamic_cast<LauParameter*>( (*objarray)[iPar] );
						if ( ! parameter ) {
							std::cerr << "ERROR in LauSimFitMaster::finalise : Error reading parameter from slave" << std::endl;
							allOK = kFALSE;
							continue;
						}

						TString parname = parameter->name();

						std::map< TString, UInt_t >::iterator iter = parIndices_.find( parname );
						if ( iter == parIndices_.end() ) {
							std::cerr << "ERROR in LauSimFitMaster::finalise : Unexpected parameter name received from slave" << std::endl;
							allOK = kFALSE;
							continue;
						}

						const UInt_t index = iter->second;
						if ( slaveIndices_[iSlave][iPar] != index ) {
							std::cerr << "ERROR in LauSimFitMaster::finalise : Unexpected parameter received from slave" << std::endl;
							allOK = kFALSE;
							continue;
						}

						Double_t parvalue = parameter->value();
						params_[index]->value( parvalue );
						parValues_[index] = parvalue;
						vectorPar_[iSlave][iPar] = parvalue;
					}
				}
				delete objarray;
			}
		} else {
			std::cerr << "ERROR in LauSimFitMaster::finalise : Slave " << iSlave << " reports an error performing finalisation" << std::endl;
			allOK = kFALSE;
		}

		++responsesReceived;
	}

	// Fill our ntuple as well
	if ( fitNtuple_ != 0 ) {
		for ( std::vector<LauParameter*>::iterator iter = params_.begin(); iter != params_.end(); ++iter ) {
			if (!(*iter)->fixed()) {
				(*iter)->updatePull();
			}
		}
		std::vector<LauParameter> extraVars;
		fitNtuple_->storeParsAndErrors( params_, extraVars );
		fitNtuple_->storeCorrMatrix( iExpt_, NLL_, fitStatus_, covMatrix_ );
		fitNtuple_->updateFitNtuple();
	}

	return allOK;
}

Bool_t LauSimFitMaster::writeOutResults()
{
	if ( socketMonitor_ == 0 ) {
		std::cerr << "ERROR in LauSimFitMaster::writeOutResults : Sockets not initialised." << std::endl;
		return kFALSE;
	}

	// Construct a message, requesting to write out the fit results
	TString msgStr("Write Results");
	TMessage message( kMESS_STRING );
	message.WriteTString( msgStr );

	// Send the message to the slaves
	for ( UInt_t iSlave(0); iSlave<nSlaves_; ++iSlave ) {
		sSlaves_[iSlave]->Send(message);
	}

	TSocket  *sActive(0);
	UInt_t responsesReceived(0);
	Bool_t allOK(kTRUE);
	while ( responsesReceived != nSlaves_ ) {

		// Get the next queued response
		sActive = socketMonitor_->Select();

		// Extract from the message the ID of the slave and the number of events read
		sActive->Recv( messageFromSlave_ );
		UInt_t iSlave(0);
		Bool_t ok(kTRUE);
		messageFromSlave_->ReadUInt( iSlave );
		messageFromSlave_->ReadBool( ok );

		if ( ! ok ) {
			std::cerr << "ERROR in LauSimFitMaster::writeOutResults : Slave " << iSlave << " reports an error performing finalisation" << std::endl;
			allOK = kFALSE;
		}

		++responsesReceived;
	}

	// Write out our ntuple as well
	if (fitNtuple_ != 0) {
		fitNtuple_->writeOutFitResults();
	}

	return allOK;
}

