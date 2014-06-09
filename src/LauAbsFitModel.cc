
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsFitModel.cc
  \brief File containing implementation of LauAbsFitModel class.
 */

#include <iostream>
#include <limits>
#include <vector>

#include "TMessage.h"
#include "TMonitor.h"
#include "TServerSocket.h"
#include "TSocket.h"
#include "TSystem.h"
#include "TVectorD.h"
#include "TVirtualFitter.h"

#include "LauAbsFitModel.hh"
#include "LauAbsFitter.hh"
#include "LauAbsPdf.hh"
#include "LauComplex.hh"
#include "LauFitter.hh"
#include "LauFitDataTree.hh"
#include "LauFitNtuple.hh"
#include "LauGenNtuple.hh"
#include "LauParameter.hh"
#include "LauParamFixed.hh"
#include "LauPrint.hh"
#include "LauSPlot.hh"

ClassImp(LauAbsFitModel)


LauAbsFitModel::LauAbsFitModel() :
	storeCon_(0),
	twoStageFit_(kFALSE),
	useAsymmFitErrors_(kFALSE),
	compareFitData_(kFALSE),
	writeLatexTable_(kFALSE),
	writeSPlotData_(kFALSE),
	storeDPEff_(kFALSE),
	randomFit_(kFALSE),
	emlFit_(kFALSE),
	poissonSmear_(kFALSE),
	enableEmbedding_(kFALSE),
	usingDP_(kTRUE),
	pdfsDependOnDP_(kFALSE),
	firstExpt_(0),
	nExpt_(0),
	evtsPerExpt_(0),
	iExpt_(0),
	inputFitData_(0),
	fitNtuple_(0),
	genNtuple_(0),
	sPlotNtuple_(0),
	fitStatus_(0),
	NLL_(0),
	numberOKFits_(0),
	numberBadFits_(0),
	nParams_(0),
	nFreeParams_(0),
	worstLogLike_(std::numeric_limits<Double_t>::max()),
	withinAsymErrorCalc_(kFALSE),
	nullString_(""),
	doSFit_(kFALSE),
	sWeightBranchName_(""),
	sWeightScaleFactor_(1.0),
	fitToyMCFileName_("fitToyMC.root"),
	fitToyMCTableName_("fitToyMCTable"),
	fitToyMCScale_(10),
	fitToyMCPoissonSmear_(kFALSE),
	sPlotFileName_(""),
	sPlotTreeName_(""),
	sPlotVerbosity_(""),
	sMaster_(0),
	messageFromMaster_(0),
	slaveId_(-1),
	nSlaves_(0),
	parValues_(0)
{
}


LauAbsFitModel::~LauAbsFitModel()
{
	delete inputFitData_; inputFitData_ = 0;
	delete fitNtuple_; fitNtuple_ = 0;
	delete genNtuple_; genNtuple_ = 0;
	delete sPlotNtuple_; sPlotNtuple_ = 0;
	delete sMaster_; sMaster_ = 0;
	delete[] parValues_; parValues_ = 0;

	// Remove the components created to apply constraints to fit parameters
	for (std::vector<LauAbsRValue*>::iterator iter = conVars_.begin(); iter != conVars_.end(); ++iter){
		if ( !(*iter)->isLValue() ){
			delete (*iter);
			(*iter) = 0;
		}
	}
}

void LauAbsFitModel::run(const TString& applicationCode, const TString& dataFileName, const TString& dataTreeName,
		const TString& histFileName, const TString& tableFileName)
{
	// Chose whether you want to generate or fit events in the Dalitz plot.
	// To generate events choose applicationCode = "gen", to fit events choose
	// applicationCode = "fit".

	TString runCode(applicationCode);
	runCode.ToLower();

	TString histFileNameCopy(histFileName);
	TString tableFileNameCopy(tableFileName);
	TString dataFileNameCopy(dataFileName);
	TString dataTreeNameCopy(dataTreeName);

	// Initialise the fit par vectors. Each class that inherits from this one
	// must implement this sensibly for all vectors specified in clearFitParVectors,
	// i.e. specify parameter names, initial, min, max and fixed values
	this->initialise();

	// Add variables to Gaussian constrain to a list
	this->addConParameters();

	if (dataFileNameCopy == "") {dataFileNameCopy = "data.root";}
	if (dataTreeNameCopy == "") {dataTreeNameCopy = "genResults";}

	if (runCode.Contains("gen")) {

		if (histFileNameCopy == "") {histFileNameCopy = "parInfo.root";}
		if (tableFileNameCopy == "") {tableFileNameCopy = "genResults";}

		this->setGenValues();
		this->generate(dataFileNameCopy, dataTreeNameCopy, histFileNameCopy, tableFileNameCopy);

	} else if (runCode.Contains("fit")) {

		if (histFileNameCopy == "") {histFileNameCopy = "parInfo.root";}
		if (tableFileNameCopy == "") {tableFileNameCopy = "fitResults";}

		this->fit(dataFileNameCopy, dataTreeNameCopy, histFileNameCopy, tableFileNameCopy);

	} else if (runCode.Contains("reweight")) {

		this->weightEvents(dataFileNameCopy, dataTreeNameCopy);
	}
}

void LauAbsFitModel::runSlave(const TString& dataFileName, const TString& dataTreeName,
		const TString& histFileName, const TString& tableFileName,
		const TString& addressMaster, const UInt_t portMaster)
{
	if ( sMaster_ != 0 ) {
		std::cerr << "ERROR in LauAbsFitModel::runSlave : master socket already present" << std::endl;
		return;
	}

	// Open connection to master
	sMaster_ = new TSocket(addressMaster, portMaster);
	sMaster_->Recv( messageFromMaster_ );
	messageFromMaster_->ReadUInt( slaveId_ );
	messageFromMaster_->ReadUInt( nSlaves_ );

	delete messageFromMaster_;
	messageFromMaster_ = 0;

	std::cout << "INFO in LauAbsFitModel::runSlave : Established connection to master on port " << portMaster << std::endl;
	std::cout << "                                 : We are slave " << slaveId_ << " of " << nSlaves_ << std::endl;

	// Initialise the fit par vectors. Each class that inherits from this one
	// must implement this sensibly for all vectors specified in clearFitParVectors,
	// i.e. specify parameter names, initial, min, max and fixed values
	this->initialise();

	// NB call to addConParameters() is intentionally not included here cf.
	// run() since this has to be dealt with by the master to avoid
	// multiple inclusions of each penalty term

	// Create array to efficiently exchange parameter values with master
	nParams_ = fitVars_.size();
	parValues_ = new Double_t[nParams_];
	for ( UInt_t iPar(0); iPar < nParams_; ++iPar ) {
		parValues_[iPar] = fitVars_[iPar]->initValue();
	}

	TString dataFileNameCopy(dataFileName);
	TString dataTreeNameCopy(dataTreeName);
	TString histFileNameCopy(histFileName);
	TString tableFileNameCopy(tableFileName);

	if (dataFileNameCopy == "")  {dataFileNameCopy = "data.root";}
	if (dataTreeNameCopy == "")  {dataTreeNameCopy = "genResults";}
	if (histFileNameCopy == "")  {histFileNameCopy = "parInfo.root";}
	if (tableFileNameCopy == "") {tableFileNameCopy = "fitResults";}

	this->fitSlave(dataFileNameCopy, dataTreeNameCopy, histFileNameCopy, tableFileNameCopy);

	std::cout << "INFO in LauAbsFitModel::runSlave : Fit slave " << slaveId_ << " has finished successfully" << std::endl;
}

void LauAbsFitModel::doSFit( const TString& sWeightBranchName, Double_t scaleFactor )
{
	if ( sWeightBranchName == "" ) {
		std::cerr << "WARNING in LauAbsFitModel::doSFit : sWeight branch name is empty string, not setting-up sFit." << std::endl;
		return;
	}

	doSFit_ = kTRUE;
	sWeightBranchName_ = sWeightBranchName;
	sWeightScaleFactor_ = scaleFactor;
}

void LauAbsFitModel::setBkgndClassNames( const std::vector<TString>& names )
{
	if ( !bkgndClassNames_.empty() ) {
		std::cerr << "WARNING in LauAbsFitModel::setBkgndClassNames : Names already stored, not changing them." << std::endl;
		return;
	}

	UInt_t nBkgnds = names.size();
	for ( UInt_t i(0); i < nBkgnds; ++i ) {
		bkgndClassNames_.insert( std::make_pair( i, names[i] ) );
	}

	this->setupBkgndVectors();
}

Bool_t LauAbsFitModel::validBkgndClass( const TString& className ) const
{
	if ( bkgndClassNames_.empty() ) {
		return kFALSE;
	}

	Bool_t found(kFALSE);
	for ( LauBkgndClassMap::const_iterator iter = bkgndClassNames_.begin(); iter != bkgndClassNames_.end(); ++iter ) {
		if ( iter->second == className ) {
			found = kTRUE;
			break;
		}
	}

	return found;
}

UInt_t LauAbsFitModel::bkgndClassID( const TString& className ) const
{
	if ( ! this->validBkgndClass( className ) ) {
		std::cerr << "ERROR in LauAbsFitModel::bkgndClassID : Request for ID for invalid background class \"" << className << "\"." << std::endl;
		return (bkgndClassNames_.size() + 1);
	}

	UInt_t bgID(0);
	for ( LauBkgndClassMap::const_iterator iter = bkgndClassNames_.begin(); iter != bkgndClassNames_.end(); ++iter ) {
		if ( iter->second == className ) {
			bgID = iter->first;
			break;
		}
	}

	return bgID;
}

const TString& LauAbsFitModel::bkgndClassName( UInt_t classID ) const
{
	LauBkgndClassMap::const_iterator iter = bkgndClassNames_.find( classID );

	if ( iter == bkgndClassNames_.end() ) {
		std::cerr << "ERROR in LauAbsFitModel::bkgndClassName : Request for name of invalid background class ID " << classID << "." << std::endl;
		return nullString_;
	}

	return iter->second;
}

void LauAbsFitModel::clearFitParVectors()
{
	std::cout << "INFO in LauAbsFitModel::clearFitParVectors : Clearing fit variable vectors" << std::endl;

	// Remove the components created to apply constraints to fit parameters
	for (std::vector<LauAbsRValue*>::iterator iter = conVars_.begin(); iter != conVars_.end(); ++iter){
		if ( !(*iter)->isLValue() ){
			delete (*iter);
			(*iter) = 0;
		}
	}
	conVars_.clear();
	fitVars_.clear();
}

void LauAbsFitModel::clearExtraVarVectors()
{
	std::cout << "INFO in LauAbsFitModel::clearExtraVarVectors : Clearing extra ntuple variable vectors" << std::endl;
	extraVars_.clear();
}

void LauAbsFitModel::setGenValues()
{
	// makes sure each parameter holds its genValue as its current value
	for (LauParameterPList::iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter) {
		(*iter)->value((*iter)->genValue());
	}
	this->propagateParUpdates();
}

void LauAbsFitModel::writeSPlotData(const TString& fileName, const TString& treeName, Bool_t storeDPEfficiency, const TString& verbosity)
{
	if (this->writeSPlotData()) {
		std::cerr << "ERROR in LauAbsFitModel::writeSPlotData : Already have an sPlot ntuple setup, not doing it again." << std::endl;
		return;
	}
	writeSPlotData_ = kTRUE;
	sPlotFileName_ = fileName;
	sPlotTreeName_ = treeName;
	sPlotVerbosity_ = verbosity;
	storeDPEff_ = storeDPEfficiency;
}

// TODO : histFileName isn't used here at the moment but could be used for
//        storing the values of the parameters used in the generation.
//        These could then be read and used for setting the "true" values
//        in a subsequent fit.
void LauAbsFitModel::generate(const TString& dataFileName, const TString& dataTreeName, const TString& /*histFileName*/, const TString& tableFileNameBase)
{
	// Create the ntuple for storing the results
	std::cout << "INFO in LauAbsFitModel::generate : Creating generation ntuple." << std::endl;
	if (genNtuple_ != 0) {delete genNtuple_; genNtuple_ = 0;}
	genNtuple_ = new LauGenNtuple(dataFileName,dataTreeName);

	// add branches for storing the experiment number and the number of
	// the event within the current experiment
	this->addGenNtupleIntegerBranch("iExpt");
	this->addGenNtupleIntegerBranch("iEvtWithinExpt");
	this->setupGenNtupleBranches();

	// Start the cumulative timer
	cumulTimer_.Start();

	Bool_t genOK(kTRUE);
	do {
		// Loop over the number of experiments
		for (iExpt_ = firstExpt_; iExpt_ < (firstExpt_+nExpt_); ++iExpt_) {

			// Start the timer to see how long each experiment takes to generate
			timer_.Start();

			// Store the experiment number in the ntuple
			this->setGenNtupleIntegerBranchValue("iExpt",iExpt_);

			// Do the generation for this experiment
			std::cout << "INFO in LauAbsFitModel::generate : Generating experiment number " << iExpt_ << std::endl;
			genOK = this->genExpt();

			// Stop the timer and see how long the program took so far
			timer_.Stop();
			timer_.Print();

			if (!genOK) {
				// delete and recreate an empty tree
				genNtuple_->deleteAndRecreateTree();

				// then break out of the experiment loop
				std::cerr << "WARNING in LauAbsFitModel::generate : Problem in toy MC generation.  Starting again with updated parameters..." << std::endl;
				break;
			}

			if (this->writeLatexTable()) {
				TString tableFileName(tableFileNameBase);
				tableFileName += "_";
				tableFileName += iExpt_;
				tableFileName += ".tex";
				this->writeOutTable(tableFileName);
			}

		} // Loop over number of experiments
	} while (!genOK);

	// Print out total timing info.
	cumulTimer_.Stop();
	std::cout << "INFO in LauAbsFitModel::generate : Finished generating all experiments." << std::endl;
	std::cout << "INFO in LauAbsFitModel::generate : Cumulative timing:" << std::endl;
	cumulTimer_.Print();

	// Build the event index
	std::cout << "INFO in LauAbsFitModel::generate : Building experiment:event index." << std::endl;
	// TODO - can test this return value?
	//Int_t nIndexEntries =
	genNtuple_->buildIndex("iExpt","iEvtWithinExpt");

	// Write out toy MC ntuple
	std::cout << "INFO in LauAbsFitModel::generate : Writing data to file " << dataFileName << "." << std::endl;
	genNtuple_->writeOutGenResults();
}

void LauAbsFitModel::addGenNtupleIntegerBranch(const TString& name)
{
	genNtuple_->addIntegerBranch(name);
}

void LauAbsFitModel::addGenNtupleDoubleBranch(const TString& name)
{
	genNtuple_->addDoubleBranch(name);
}

void LauAbsFitModel::setGenNtupleIntegerBranchValue(const TString& name, Int_t value)
{
	genNtuple_->setIntegerBranchValue(name,value);
}

void LauAbsFitModel::setGenNtupleDoubleBranchValue(const TString& name, Double_t value)
{
	genNtuple_->setDoubleBranchValue(name,value);
}

Int_t LauAbsFitModel::getGenNtupleIntegerBranchValue(const TString& name) const
{
	return genNtuple_->getIntegerBranchValue(name);
}

Double_t LauAbsFitModel::getGenNtupleDoubleBranchValue(const TString& name) const
{
	return genNtuple_->getDoubleBranchValue(name);
}

void LauAbsFitModel::fillGenNtupleBranches()
{
	genNtuple_->fillBranches();
}

void LauAbsFitModel::addSPlotNtupleIntegerBranch(const TString& name)
{
	sPlotNtuple_->addIntegerBranch(name);
}

void LauAbsFitModel::addSPlotNtupleDoubleBranch(const TString& name)
{
	sPlotNtuple_->addDoubleBranch(name);
}

void LauAbsFitModel::setSPlotNtupleIntegerBranchValue(const TString& name, Int_t value)
{
	sPlotNtuple_->setIntegerBranchValue(name,value);
}

void LauAbsFitModel::setSPlotNtupleDoubleBranchValue(const TString& name, Double_t value)
{
	sPlotNtuple_->setDoubleBranchValue(name,value);
}

void LauAbsFitModel::fillSPlotNtupleBranches()
{
	sPlotNtuple_->fillBranches();
}

void LauAbsFitModel::fit(const TString& dataFileName, const TString& dataTreeName, const TString& histFileName, const TString& tableFileNameBase)
{
	// Routine to perform the total fit.

	std::cout << "INFO in LauAbsFitModel::fit : First experiment = " << firstExpt_ << std::endl;
	std::cout << "INFO in LauAbsFitModel::fit : Number of experiments = " << nExpt_ << std::endl;

	// Start the cumulative timer
	cumulTimer_.Start();

	numberOKFits_ = 0, numberBadFits_ = 0;
	fitStatus_ = -1;

	// Create and setup the fit results ntuple
	std::cout << "INFO in LauAbsFitModel::fit : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName, this->useAsymmFitErrors());

	// Create and setup the sPlot ntuple
	if (this->writeSPlotData()) {
		std::cout << "INFO in LauAbsFitModel::fit : Creating sPlot ntuple." << std::endl;
		if (sPlotNtuple_ != 0) {delete sPlotNtuple_; sPlotNtuple_ = 0;}
		sPlotNtuple_ = new LauGenNtuple(sPlotFileName_,sPlotTreeName_);
		this->setupSPlotNtupleBranches();
	}

	// This reads in the given dataFile and creates an input
	// fit data tree that stores them for all events and experiments.
	Bool_t dataOK = this->cacheFitData(dataFileName,dataTreeName);
	if (!dataOK) {
		std::cerr << "ERROR in LauAbsFitModel::fit : Problem caching the fit data." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Loop over the number of experiments
	for (iExpt_ = firstExpt_; iExpt_ < (firstExpt_+nExpt_); ++iExpt_) {

		// Start the timer to see how long each fit takes
		timer_.Start();

		inputFitData_->readExperimentData(iExpt_);
		this->eventsPerExpt(inputFitData_->nEvents());

		if (this->eventsPerExpt() < 1) {
			std::cerr << "WARNING in LauAbsFitModel::fit : Zero events in experiment " << iExpt_ << ", skipping..." << std::endl;
			timer_.Stop();
			continue;
		}

		// Now the sub-classes must implement whatever they need to do
		// to cache any more input fit data they need in order to
		// calculate the likelihoods during the fit. 
		// They need to use the inputFitData_ tree as input. For example, 
		// inputFitData_ contains m13Sq and m23Sq. The appropriate fit model
		// then caches the resonance dynamics for the signal model, as
		// well as the background likelihood values in the Dalitz plot
		this->cacheInputFitVars();
		if ( this->doSFit() ) {
			this->cacheInputSWeights();
		}

		// Do the fit for this experiment
		this->fitExpt();

		// Write the results into the ntuple
		this->finaliseFitResults(tableFileNameBase);

		// Stop the timer and see how long the program took so far
		timer_.Stop();
		timer_.Print();

		// Store the per-event likelihood values
		if ( this->writeSPlotData() ) {
			this->storePerEvtLlhds();
		}

		// Create a toy MC sample using the fitted parameters so that
		// the user can compare the fit to the data.
		if (compareFitData_ == kTRUE && fitStatus_ == 3) {
			this->createFitToyMC(fitToyMCFileName_, fitToyMCTableName_);
		}

		// Keep track of how many fits worked or failed
		// NB values of fitStatus_ now indicate the status of the error matrix:
		// 0= not calculated at all
		// 1= approximation only, not accurate
		// 2= full matrix, but forced positive-definite
		// 3= full accurate covariance matrix
		if (fitStatus_ == 3) {
			numberOKFits_++;
		} else {
			numberBadFits_++;
		}

	} // Loop over number of experiments

	// Print out total timing info.
	cumulTimer_.Stop();
	std::cout << "INFO in LauAbsFitModel::fit : Cumulative timing:" << std::endl;
	cumulTimer_.Print();

	// Print out stats on OK fits.
	std::cout << "INFO in LauAbsFitModel::fit : Number of OK Fits = " << numberOKFits_ << std::endl;
	std::cout << "INFO in LauAbsFitModel::fit : Number of Failed Fits = " << numberBadFits_ << std::endl;
	Double_t fitEff(0.0);
	if (nExpt_ != 0) {fitEff = numberOKFits_/(1.0*nExpt_);}
	std::cout << "INFO in LauAbsFitModel::fit : Fit efficiency = " << fitEff*100.0 << "%." << std::endl;

	// Write out any fit results (ntuples etc...).
	this->writeOutAllFitResults();
	if ( this->writeSPlotData() ) {
		this->calculateSPlotData();
	}
}

void LauAbsFitModel::fitSlave(const TString& dataFileName, const TString& dataTreeName, const TString& histFileName, const TString& tableFileNameBase)
{
	// Create and setup the fit results ntuple
	std::cout << "INFO in LauAbsFitModel::fitSlave : Creating fit ntuple." << std::endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName, this->useAsymmFitErrors());

	// This reads in the given dataFile and creates an input
	// fit data tree that stores them for all events and experiments.
	Bool_t dataOK = this->cacheFitData(dataFileName,dataTreeName);
	if (!dataOK) {
		std::cerr << "ERROR in LauAbsFitModel::fitSlave : Problem caching the fit data." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Now process the various requests from the master

	TMessage messageToMaster(kMESS_ANY);

	while ( kTRUE ) {

		sMaster_->Recv( messageFromMaster_ );

		if ( messageFromMaster_->What() == kMESS_STRING ) {

			TString msgStr;
			messageFromMaster_->ReadTString( msgStr );

			std::cout << "INFO in LauAbsFitModel::fitSlave : Received message from master: " << msgStr << std::endl;

			if ( msgStr == "Send Parameters" ) {

				// Update initial fit parameters if required (e.g. if using random numbers).
				this->checkInitFitParams();

				// Send the fit parameters
				TObjArray array;
				for ( LauParameterPList::iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter ) {
					array.Add( *iter );
				}

				messageToMaster.Reset( kMESS_OBJECT );
				messageToMaster.WriteObject( &array );
				sMaster_->Send( messageToMaster );

			} else if ( msgStr == "Read Expt" ) {

				// Read the data for this experiment
				messageFromMaster_->ReadUInt( iExpt_ );

				inputFitData_->readExperimentData( iExpt_ );
				UInt_t nEvent = inputFitData_->nEvents();
				this->eventsPerExpt( nEvent );

				if ( nEvent < 1 ) {
					std::cerr << "WARNING in LauAbsFitModel::fitSlave : Zero events in experiment " << firstExpt_ << ", the master should skip this experiment..." << std::endl;
				}

				messageToMaster.Reset( kMESS_ANY );
				messageToMaster.WriteUInt( slaveId_ );
				messageToMaster.WriteUInt( nEvent );
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

				std::cout << "INFO in LauAbsFitModel::fitSlave : Message from master to finish" << std::endl;
				break;
			} else {
				std::cerr << "ERROR in LauAbsFitModel::fitSlave : Unexpected message from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

		} else if ( messageFromMaster_->What() == kMESS_OBJECT ) {

			std::cout << "INFO in LauAbsFitModel::fitSlave : Received message from master: Finalise" << std::endl;

			messageFromMaster_->ReadInt( fitStatus_ );
			messageFromMaster_->ReadDouble( NLL_ );

			TObjArray * objarray = dynamic_cast<TObjArray*>( messageFromMaster_->ReadObject( messageFromMaster_->GetClass() ) );
			if ( ! objarray ) {
				std::cerr << "ERROR in LauAbsFitModel::fitSlave : Error reading parameters from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			TMatrixD * covMat = dynamic_cast<TMatrixD*>( messageFromMaster_->ReadObject( messageFromMaster_->GetClass() ) );
			if ( ! covMat ) {
				std::cerr << "ERROR in LauAbsFitModel::fitSlave : Error reading covariance matrix from master" << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}
			covMatrix_.Clear();
			covMatrix_.ResizeTo( covMat->GetNrows(), covMat->GetNcols() );
			covMatrix_.SetMatrixArray( covMat->GetMatrixArray() );
			delete covMat; covMat = 0;


			UInt_t nPars = objarray->GetEntries();

			if ( nPars != nParams_ ) {
				std::cerr << "ERROR in LauAbsFitModel::fitSlave : Unexpected number of parameters received from master" << std::endl;
				std::cerr << "                       ::fitSlave : Received " << nPars << " when expecting " << nParams_ << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
				LauParameter* parameter = dynamic_cast<LauParameter*>( (*objarray)[iPar] );
				if ( ! parameter ) {
					std::cerr << "ERROR in LauAbsFitModel::fitSlave : Error reading parameter from master" << std::endl;
					gSystem->Exit( EXIT_FAILURE );
				}

				if ( parameter->name() != fitVars_[iPar]->name() ) {
					std::cerr << "ERROR in LauAbsFitModel::fitSlave : Error reading parameter from master" << std::endl;
					gSystem->Exit( EXIT_FAILURE );
				}

				*(fitVars_[iPar]) = *parameter;
			}

			// Write the results into the ntuple
			this->finaliseFitResults( tableFileNameBase );

			// Store the per-event likelihood values
			if ( this->writeSPlotData() ) {
			  this->storePerEvtLlhds();
			}

			// Create a toy MC sample using the fitted parameters so that
			// the user can compare the fit to the data.
			if (compareFitData_ == kTRUE && fitStatus_ == 3) {
			  this->createFitToyMC(fitToyMCFileName_, fitToyMCTableName_);
			}

			// Send the finalised parameters
			TObjArray array;
			for ( LauParameterPList::iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter ) {
				array.Add( *iter );
			}

			messageToMaster.Reset( kMESS_ANY );
			messageToMaster.WriteUInt( slaveId_ );
			messageToMaster.WriteBool( kTRUE );
			messageToMaster.WriteObject( &array );
			sMaster_->Send( messageToMaster );

		} else if ( messageFromMaster_->What() == kMESS_ANY ) {

			UInt_t nPars(0);
			messageFromMaster_->ReadUInt( nPars );

			if ( nPars != nParams_ ) {
				std::cerr << "ERROR in LauAbsFitModel::fitSlave : Unexpected number of parameters received from master" << std::endl;
				std::cerr << "                       ::fitSlave : Received " << nPars << " when expecting " << nParams_ << std::endl;
				gSystem->Exit( EXIT_FAILURE );
			}

			messageFromMaster_->ReadFastArray( parValues_, nPars );

			for ( UInt_t iPar(0); iPar < nPars; ++iPar ) {
				if ( ! fitVars_[iPar]->fixed() ) {
					fitVars_[iPar]->value( parValues_[iPar] );
				}
			}
			this->propagateParUpdates();

			Double_t negLogLike = this->getTotNegLogLikelihood();

			messageToMaster.Reset( kMESS_ANY );
			messageToMaster.WriteDouble( negLogLike );   
			sMaster_->Send( messageToMaster );         

		} else {
			std::cerr << "ERROR in LauAbsFitModel::fitSlave : Unexpected message type" << std::endl;
			gSystem->Exit( EXIT_FAILURE );
		}

		delete messageFromMaster_;
		messageFromMaster_ = 0;
	}
}

Bool_t LauAbsFitModel::cacheFitData(const TString& dataFileName, const TString& dataTreeName)
{
	// From the input data stream, store the variables into the
	// internal tree inputFitData_ that can be used by the sub-classes
	// in calculating their likelihood functions for the fit
	delete inputFitData_;
	inputFitData_ = new LauFitDataTree(dataFileName,dataTreeName);
	Bool_t dataOK = inputFitData_->findBranches();

	if (!dataOK) {
		delete inputFitData_; inputFitData_ = 0;
	}

	return dataOK;
}

void LauAbsFitModel::cacheInputSWeights()
{
	Bool_t hasBranch = inputFitData_->haveBranch( sWeightBranchName_ );
	if ( ! hasBranch ) {
		std::cerr << "ERROR in LauAbsFitModel::cacheInputSWeights : Input data does not contain variable \"" << sWeightBranchName_ << "\".\n";
		std::cerr << "                                            : Turning off sFit!" << std::endl;
		doSFit_ = kFALSE;
		return;
	}

	UInt_t nEvents = this->eventsPerExpt();
	sWeights_.clear();
	sWeights_.reserve( nEvents );

	for (UInt_t iEvt = 0; iEvt < nEvents; ++iEvt) {

		const LauFitData& dataValues = inputFitData_->getData(iEvt);

		LauFitData::const_iterator iter = dataValues.find( sWeightBranchName_ );

		sWeights_.push_back( iter->second * sWeightScaleFactor_ );
	}
}

void LauAbsFitModel::fitExpt()
{
	// Routine to perform the actual fit for the given experiment

	// Reset the worst likelihood found to its catch-all value
	worstLogLike_ = std::numeric_limits<Double_t>::max();

	// Update initial fit parameters if required (e.g. if using random numbers).
	this->checkInitFitParams();

	// Initialise the fitter
	LauFitter::fitter()->useAsymmFitErrors( this->useAsymmFitErrors() );
	LauFitter::fitter()->twoStageFit( this->twoStageFit() );
	LauFitter::fitter()->initialise( this, fitVars_ );

	nParams_ = LauFitter::fitter()->nParameters();
	nFreeParams_ = LauFitter::fitter()->nFreeParameters();

	// Now ready for minimisation step
	std::cout << "\nINFO in LauAbsFitModel::fitExpt : Start minimisation...\n";
	std::pair<Int_t,Double_t> fitResult = LauFitter::fitter()->minimise();

	fitStatus_ = fitResult.first;
	NLL_       = fitResult.second;

	// If we're doing a two stage fit we can now release (i.e. float)
	// the 2nd stage parameters and re-fit
	if (this->twoStageFit()) {

		if ( fitStatus_ != 3 ) {
			std::cerr << "WARNING in LauAbsFitModel:fitExpt : Not running second stage fit since first stage failed." << std::endl;
			LauFitter::fitter()->releaseSecondStageParameters();
		} else {
			LauFitter::fitter()->fixFirstStageParameters();
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
	LauFitter::fitter()->releaseFirstStageParameters();
}

void LauAbsFitModel::writeOutAllFitResults()
{
	// Write out histograms at end
	if (fitNtuple_ != 0) {
		fitNtuple_->writeOutFitResults();
	}
}

void LauAbsFitModel::calculateSPlotData()
{
	if (sPlotNtuple_ != 0) {
		sPlotNtuple_->addFriendTree(inputFitData_->fileName(), inputFitData_->treeName());
		sPlotNtuple_->writeOutGenResults();
		LauSPlot splot(sPlotNtuple_->fileName(), sPlotNtuple_->treeName(), this->firstExpt(), this->nExpt(),
				this->variableNames(), this->freeSpeciesNames(), this->fixdSpeciesNames(), this->twodimPDFs(),
				this->splitSignal(), this->scfDPSmear());
		splot.runCalculations(sPlotVerbosity_);
		splot.writeOutResults();
	}
}

void LauAbsFitModel::compareFitData(UInt_t toyMCScale, const TString& mcFileName, const TString& tableFileName, Bool_t poissonSmearing) 
{
	compareFitData_ = kTRUE;
	fitToyMCScale_ = toyMCScale;
	fitToyMCFileName_ = mcFileName;
	fitToyMCTableName_ = tableFileName;
	fitToyMCPoissonSmear_ = poissonSmearing;
}

void LauAbsFitModel::createFitToyMC(const TString& mcFileName, const TString& tableFileName)
{
	// Create a toy MC sample so that the user can compare the fitted
	// result with the data.
	// Generate more toy MC to reduce statistical fluctuations:
	// - use the rescaling value fitToyMCScale_

	// Store the info on the number of experiments, first expt and current expt
	const UInt_t oldNExpt(this->nExpt());
	const UInt_t oldFirstExpt(this->firstExpt());
	const UInt_t oldIExpt(iExpt_);

	// Turn off Poisson smearing if required
	const Bool_t poissonSmearing(this->doPoissonSmearing());
	this->doPoissonSmearing(fitToyMCPoissonSmear_);

	// Turn off embedding, since we need toy MC, not reco'ed events
	const Bool_t enableEmbeddingOrig(this->enableEmbedding());
	this->enableEmbedding(kFALSE);

	// Need to make sure that the generation of the DP co-ordinates is
	// switched on if any of our PDFs depend on it
	const Bool_t origUseDP = this->useDP();
	if ( !origUseDP && this->pdfsDependOnDP() ) {
		this->useDP( kTRUE );
		this->initialiseDPModels();
	}

	// Construct a unique filename for this experiment
	TString exptString("_expt");
	exptString += oldIExpt;
	TString fileName( mcFileName );
	fileName.Insert( fileName.Last('.'), exptString );

	// Generate the toy MC
	std::cout << "INFO in LauAbsFitModel::createFitToyMC : Generating toy MC in " << fileName << " to compare fit with data..." << std::endl;
	std::cout << "                                       : Number of experiments to generate = " << fitToyMCScale_ << "." << std::endl;
	std::cout << "                                       : This is to allow the toy MC to be made with reduced statistical fluctuations." << std::endl;

	// Set the genValue of each parameter to its current (fitted) value
	// but first store the original genValues for restoring later
	std::vector<Double_t> origGenValues;  origGenValues.reserve(nParams_);
	for (LauParameterPList::iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter) {
		origGenValues.push_back((*iter)->genValue());
		(*iter)->genValue((*iter)->value());
	}

	// If we're asked to generate more than 100 experiments then split it
	// up into multiple files since otherwise can run into memory issues
	// when building the index

	UInt_t totalExpts = fitToyMCScale_;
	if ( totalExpts > 100 ) {
		UInt_t nFiles = totalExpts/100;
		if ( totalExpts%100 ) {
			nFiles += 1;
		}
		for ( UInt_t iFile(0); iFile < nFiles; ++iFile ) {

			UInt_t firstExp( iFile*100 );

			// Set number of experiments and first experiment to generate
			UInt_t nExp = ((firstExp + 100)>totalExpts) ? totalExpts-firstExp : 100;
			this->setNExpts(nExp, firstExp);

			// Create a unique filename and generate the events
			TString extraname = "_file";
			extraname += iFile;
			fileName.Insert( fileName.Last('.'), extraname );
			this->generate(fileName, "genResults", "dummy.root", tableFileName);
		}
	} else {
		// Set number of experiments to new value
		this->setNExpts(fitToyMCScale_, 0);
		// Generate the toy
		this->generate(fileName, "genResults", "dummy.root", tableFileName);
	}

	// Reset number of experiments to original value
	iExpt_ = oldIExpt;
	this->setNExpts(oldNExpt, oldFirstExpt);

	// Restore the Poisson smearing to its former value
	this->doPoissonSmearing(poissonSmearing);

	// Restore the embedding status
	this->enableEmbedding(enableEmbeddingOrig);

	// Restore "useDP" to its former status
	this->useDP( origUseDP );

	// Restore the original genValue to each parameter
	for (UInt_t i(0); i<nParams_; ++i) {
		fitVars_[i]->genValue(origGenValues[i]);
	}

	std::cout << "INFO in LauAbsFitModel::createFitToyMC : Finished in createFitToyMC." << std::endl;
}

Double_t LauAbsFitModel::getTotNegLogLikelihood()
{
	// Calculate the total negative log-likelihood over all events.
	// This function assumes that the fit parameters and data tree have
	// already been set-up correctly.

	// Loop over the data points to calculate the log likelihood
	Double_t logLike = this->getLogLikelihood( 0, this->eventsPerExpt() );

	// Include the Poisson term in the extended likelihood if required
	if (this->doEMLFit()) {
		logLike -= this->getEventSum();
	}

	// Calculate any penalty terms from Gaussian constrained variables
	if ( ! conVars_.empty() ){
		logLike -= this->getLogLikelihoodPenalty();
	}

	Double_t totNegLogLike = -logLike;
	return totNegLogLike;
}

Double_t LauAbsFitModel::getLogLikelihoodPenalty()
{
	Double_t penalty(0.0);

	for ( LauAbsRValuePList::const_iterator iter = conVars_.begin(); iter != conVars_.end(); ++iter ) {
		Double_t val = (*iter)->value();
		Double_t mean = (*iter)->constraintMean();
		Double_t width = (*iter)->constraintWidth();

		Double_t term = ( val - mean )*( val - mean );
		penalty += term/( 2*width*width );
	}

	return penalty;
}

Double_t LauAbsFitModel::getLogLikelihood( UInt_t iStart, UInt_t iEnd )
{
	// Calculate the total negative log-likelihood over all events.
	// This function assumes that the fit parameters and data tree have
	// already been set-up correctly.

	// Loop over the data points to calculate the log likelihood
	Double_t logLike(0.0);

	// Loop over the number of events in this experiment
	Bool_t ok(kTRUE);
	for (UInt_t iEvt = iStart; iEvt < iEnd; ++iEvt) {

		Double_t likelihood = this->getTotEvtLikelihood(iEvt);

		if (likelihood > DBL_MIN) {	// Is the likelihood zero?
			Double_t evtLogLike = TMath::Log(likelihood);
			if ( doSFit_ ) {
				evtLogLike *= sWeights_[iEvt];
			}
			logLike += evtLogLike;
		} else {
			ok = kFALSE;
			std::cerr << "WARNING in LauAbsFitModel::getLogLikelihood : Strange likelihood value for event " << iEvt << ": " << likelihood << "\n";
			this->printEventInfo(iEvt);
			this->printVarsInfo();	//Write the values of the floated variables for which the likelihood is zero
			break;
		}	
	}

	if (!ok) {
		std::cerr << "                                                  : Returning worst NLL found so far to force MINUIT out of this region." << std::endl;
		logLike = worstLogLike_;
	} else if (logLike < worstLogLike_) {
		worstLogLike_ = logLike;
	}

	return logLike;
}

void LauAbsFitModel::setParsFromMinuit(Double_t* par, Int_t npar)
{
	// This function sets the internal parameters based on the values
	// that Minuit is using when trying to minimise the total likelihood function.

	// MINOS reports different numbers of free parameters depending on the
	// situation, so disable this check
	if ( ! withinAsymErrorCalc_ ) {
		if (static_cast<UInt_t>(npar) != nFreeParams_) {
			std::cerr << "ERROR in LauAbsFitModel::setParsFromMinuit : Unexpected number of free parameters: " << npar << ".\n";
			std::cerr << "                                             Expected: " << nFreeParams_ << ".\n" << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Despite npar being the number of free parameters
	// the par array actually contains all the parameters,
	// free and floating...

	// Update all the floating ones with their new values
	// Also check if we have any parameters on which the DP integrals depend
	Bool_t recalcNorm(kFALSE);
	const LauParameterPSet::const_iterator resVarsEnd = resVars_.end();
	for (UInt_t i(0); i<nParams_; ++i) {
		if (!fitVars_[i]->fixed()) {
			if ( resVars_.find( fitVars_[i] ) != resVarsEnd ) {
				if ( fitVars_[i]->value() != par[i] ) {
					recalcNorm = kTRUE;
				}
			}
			fitVars_[i]->value(par[i]);
		}
	}

	// If so, then recalculate the normalisation
	if (recalcNorm) {
		this->recalculateNormalisation();
	}

	this->propagateParUpdates();
}

UInt_t LauAbsFitModel::addFitParameters(LauPdfList& pdfList)
{
	UInt_t nParsAdded(0);
	for (LauPdfList::iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
		LauAbsPdf* pdf = (*pdf_iter);
		if ( pdf->isDPDependent() ) {
			this->pdfsDependOnDP( kTRUE );
		}
		LauAbsRValuePList& pars = pdf->getParameters();
		for (LauAbsRValuePList::iterator pars_iter = pars.begin(); pars_iter != pars.end(); ++pars_iter) {
			LauParameterPList params = (*pars_iter)->getPars();
			for (LauParameterPList::iterator params_iter = params.begin(); params_iter != params.end(); ++params_iter) {
				if ( !(*params_iter)->clone() && ( !(*params_iter)->fixed() ||
							(this->twoStageFit() && ( (*params_iter)->secondStage() || (*params_iter)->firstStage())) ) ) {
					fitVars_.push_back(*params_iter);
					++nParsAdded;
				}
			}
		}
	}
	return nParsAdded;
}

void LauAbsFitModel::addConstraint(const TString& formula, const std::vector<TString>& pars, const Double_t mean, const Double_t width)
{
	StoreConstraints newCon;
	newCon.formula_ = formula;
	newCon.conPars_ = pars;
	newCon.mean_ = mean;
	newCon.width_ = width;
	storeCon_.push_back(newCon);
}

void LauAbsFitModel::addConParameters()
{
	for ( LauParameterPList::const_iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter ) {
		if ( (*iter)->gaussConstraint() ) {
			conVars_.push_back( *iter );
			std::cout << "INFO in LauAbsFitModel::addConParameters : Added Gaussian constraint to parameter "<< (*iter)->name() << std::endl;
		}
	}

	// Add penalties from the constraints to fit parameters
	for ( std::vector<StoreConstraints>::iterator iter = storeCon_.begin(); iter != storeCon_.end(); ++iter ) {
		std::vector<TString> names = (*iter).conPars_;
		std::vector<LauParameter*> params;
		for ( std::vector<TString>::iterator iternames = names.begin(); iternames != names.end(); ++iternames ) { 
			for ( LauParameterPList::const_iterator iterfit = fitVars_.begin(); iterfit != fitVars_.end(); ++iterfit ) {
				if ( (*iternames) == (*iterfit)->name() ){
					params.push_back(*iterfit);
				}
			}
		}

		// If the parameters are not found, skip it
		if ( params.size() != (*iter).conPars_.size() ) {
			std::cerr << "WARNING in LauAbsFitModel::addConParameters: Could not find parameters to constrain in the formula... skipping" << std::endl;
			continue;
		}

		LauFormulaPar* formPar = new LauFormulaPar( (*iter).formula_, (*iter).formula_, params );
		formPar->addGaussianConstraint( (*iter).mean_, (*iter).width_ );
		conVars_.push_back(formPar);

		std::cout << "INFO in LauAbsFitModel::addConParameters : Added Gaussian constraint to formula\n";
		std::cout << "                                         : Formula: " << (*iter).formula_ << std::endl;
		for ( std::vector<LauParameter*>::iterator iterparam = params.begin(); iterparam != params.end(); ++iterparam ) {
			std::cout << "                                         : Parameter: " << (*iterparam)->name() << std::endl;
		}
	}
	
}

void LauAbsFitModel::updateFitParameters(LauPdfList& pdfList)
{
	for (LauPdfList::iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
		(*pdf_iter)->updatePulls();
	}
}

void LauAbsFitModel::printFitParameters(const LauPdfList& pdfList, std::ostream& fout) const
{
	LauPrint print;
	for (LauPdfList::const_iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
		const LauAbsRValuePList& pars = (*pdf_iter)->getParameters();
		for (LauAbsRValuePList::const_iterator pars_iter = pars.begin(); pars_iter != pars.end(); ++pars_iter) {
			LauParameterPList params = (*pars_iter)->getPars();
			for (LauParameterPList::iterator params_iter = params.begin(); params_iter != params.end(); ++params_iter) {
				if (!(*params_iter)->clone()) {
					fout << (*params_iter)->name() << "  &  $";
					print.printFormat(fout, (*params_iter)->value());
					if ((*params_iter)->fixed() == kTRUE) {
						fout << "$ (fixed) \\\\";
					} else {
						fout << " \\pm ";
						print.printFormat(fout, (*params_iter)->error());
						fout << "$ \\\\" << std::endl;
					}
				}
			}
		}
	}
}

void LauAbsFitModel::cacheInfo(LauPdfList& pdfList, const LauFitDataTree& theData)
{
	for (LauPdfList::iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
		(*pdf_iter)->cacheInfo(theData);
	}
}

Double_t LauAbsFitModel::prodPdfValue(LauPdfList& pdfList, UInt_t iEvt)
{
	Double_t pdfVal = 1.0;
	for (LauPdfList::iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
		(*pdf_iter)->calcLikelihoodInfo(iEvt);
		pdfVal *= (*pdf_iter)->getLikelihood();
	}
	return pdfVal;
}

void LauAbsFitModel::printEventInfo(UInt_t iEvt) const
{
	const LauFitData& data = inputFitData_->getData(iEvt);
	std::cerr << "                                                  : Input data values for this event:" << std::endl;
	for (LauFitData::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		std::cerr << " " << iter->first << " = " << iter->second << std::endl;
	}
}

void LauAbsFitModel::printVarsInfo() const
{
	std::cerr << "                                                  : Current values of fit parameters:" << std::endl;
	for (UInt_t i(0); i<nParams_; ++i) {
		std::cerr << " " << (fitVars_[i]->name()).Data() << " = " << fitVars_[i]->value() << std::endl;
	}
}

