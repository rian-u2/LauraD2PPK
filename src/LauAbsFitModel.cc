
// Copyright University of Warwick 2004 - 2013.
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
#include <vector>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#include "TMessage.h"
#include "TMonitor.h"
#include "TServerSocket.h"
#include "TSocket.h"
#include "TSystem.h"
#include "TVectorD.h"
#include "TVirtualFitter.h"

#include "LauAbsFitModel.hh"
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
	useAsymmFitErrors_(kFALSE),
	compareFitData_(kFALSE),
	writeLatexTable_(kFALSE),
	writeSPlotData_(kFALSE),
	storeDPEff_(kFALSE),
	randomFit_(kFALSE),
	emlFit_(kFALSE),
	poissonSmear_(kFALSE),
	enableEmbedding_(kFALSE),
	twoStageFit_(kFALSE),
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
	worstLogLike_(DBL_MAX),
	withinMINOS_(kFALSE),
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
	socketMonitor_(0),
	sMaster_(0),
	vectorPar_(0),
	vectorRes_(0),
	messageFromSlave_(0),
	messageFromMaster_(0),
	slaveId_(-1),
	nSlaves_(0)
{
}


LauAbsFitModel::~LauAbsFitModel()
{
	delete inputFitData_; inputFitData_ = 0;
	delete fitNtuple_; fitNtuple_ = 0;
	delete genNtuple_; genNtuple_ = 0;
	delete sPlotNtuple_; sPlotNtuple_ = 0;
	delete socketMonitor_; socketMonitor_ = 0;
	delete sMaster_; sMaster_ = 0;
	for ( std::vector<TSocket*>::iterator iter = sSlaves_.begin(); iter != sSlaves_.end(); ++iter ) {
		delete (*iter);
	}
	sSlaves_.clear();
	delete vectorPar_; vectorPar_ = 0;
	delete vectorRes_; vectorRes_ = 0;
	delete messageFromSlave_; messageFromSlave_ = 0;
	delete messageFromMaster_; messageFromMaster_ = 0;
}

// It's necessary to define an external function that specifies the address of the function
// that Minuit needs to minimise. Minuit doesn't know about any classes - therefore
// use gMinuit->SetFCN(external_function), gMinuit->SetObjectFit(this).
// Here, we use TVirtualFitter* fitter instead of gMinuit, defined below.
// Then, within the external function, invoke an object from this class (LauAllModel), 
// and use the member functions to access the parameters/variables.
extern void logLikeFun(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);

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

void LauAbsFitModel::runMaster(const TString& applicationCode, const TString& dataFileName, const TString& dataTreeName,
		const TString& histFileName, const TString& tableFileName, const UInt_t nSlaves)
{
	// Chose whether you want to generate or fit events in the Dalitz plot.
	// To generate events choose applicationCode = "gen", to fit events choose
	// applicationCode = "fit".

	if ( nSlaves < 1 ) {
		return this->run( applicationCode, dataFileName, dataTreeName, histFileName, tableFileName );
	}

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

	if (dataFileNameCopy == "") {dataFileNameCopy = "data.root";}
	if (dataTreeNameCopy == "") {dataTreeNameCopy = "genResults";}

	if (runCode.Contains("gen")) {

		if (histFileNameCopy == "") {histFileNameCopy = "parInfo.root";}
		if (tableFileNameCopy == "") {tableFileNameCopy = "genResults";}

		this->setGenValues();
		this->generate(dataFileNameCopy, dataTreeNameCopy, histFileNameCopy, tableFileNameCopy);

	} else if (runCode.Contains("fit")) {

		//initialize connections with slaves
		nSlaves_ = nSlaves;
		this->initSockets();
		vectorPar_ = new TVectorD(200);
		vectorRes_ = new TVectorD(200);
		messageFromSlave_ = new TMessage(kMESS_OBJECT);

		if (histFileNameCopy == "") {histFileNameCopy = "parInfo.root";}
		if (tableFileNameCopy == "") {tableFileNameCopy = "fitResults";}

		this->fitMaster(dataFileNameCopy, dataTreeNameCopy, histFileNameCopy, tableFileNameCopy);

		// Close the socket.
		for ( UInt_t i(0); i<nSlaves_; ++i ) {
			TString msg = "Finish";
			sSlaves_[i]->Send(msg);
			sSlaves_[i]->Close();
		}
	}
}

void LauAbsFitModel::runSlave(const TString& applicationCode, const TString& dataFileName, const TString& dataTreeName,
		const TString& histFileName, const TString& tableFileName, const TString& addressMaster)
{
	// Chose whether you want to generate or fit events in the Dalitz plot.
	// To generate events choose applicationCode = "gen", to fit events choose
	// applicationCode = "fit".

	TString runCode(applicationCode);
	runCode.ToLower();

	if ( runCode != "fit" ) {
		std::cerr << "Not doing a fit - nothing for me to do!" << std::endl;
		return;
	}

	TString histFileNameCopy(histFileName);
	TString tableFileNameCopy(tableFileName);
	TString dataFileNameCopy(dataFileName);
	TString dataTreeNameCopy(dataTreeName);

	// Open connection to server
	char str[64];
	sMaster_ = new TSocket(addressMaster, 9090);
	sMaster_->Recv(str, 32);
	TString msg( str );
	std::cout << "Socket received message: " << msg << std::endl;
	msg.Remove(0, 6);
	TString slaveID = msg(0,msg.Index("/"));
	TString nSlaves = msg(msg.Index("/")+1,msg.Length()-1);
	slaveId_ = atoi( slaveID ); 
	nSlaves_ = atoi( nSlaves ); 


	// Initialise the fit par vectors. Each class that inherits from this one
	// must implement this sensibly for all vectors specified in clearFitParVectors,
	// i.e. specify parameter names, initial, min, max and fixed values
	this->initialise();

	if (dataFileNameCopy == "")  {dataFileNameCopy = "data.root";}
	if (dataTreeNameCopy == "")  {dataTreeNameCopy = "genResults";}

	if (histFileNameCopy == "")  {histFileNameCopy = "parInfo.root";}
	if (tableFileNameCopy == "") {tableFileNameCopy = "fitResults";}

	this->fitSlave(dataFileNameCopy, dataTreeNameCopy);

	cout << "Fit slave " << slaveId_ << " has finished successfully" << std::endl;
}

void LauAbsFitModel::initSockets()
{
	cout << "\n\nWaiting for connection with " << nSlaves_ << " workers...\n\n" << std::endl;

	//initialize socket connection, then accept a connection and return a full-duplex communication socket.
	socketMonitor_ = new TMonitor();

	TServerSocket *ss = new TServerSocket(9090, kTRUE);
	sSlaves_.resize(nSlaves_);
	for ( UInt_t i(0); i<nSlaves_; ++i ) {
		sSlaves_[i] = ss->Accept();
	}

	// tell the clients to start
	for ( UInt_t i(0); i<nSlaves_; ++i ) {
		TString msg = "Slave ";
		msg += i;
		msg += "/";
		msg += nSlaves_;
		sSlaves_[i]->Send(msg);
		socketMonitor_->Add(sSlaves_[i]);
		cout << "Added slave " << i<<endl;
	}

	cout << "Now start" << endl;

	ss->Close();
	delete ss;
}

void LauAbsFitModel::doSFit( const TString& sWeightBranchName, Double_t scaleFactor )
{
	if ( sWeightBranchName == "" ) {
		cerr << "WARNING in LauAbsFitModel::doSFit : sWeight branch name is empty string, not setting-up sFit." << endl;
		return;
	}

	doSFit_ = kTRUE;
	sWeightBranchName_ = sWeightBranchName;
	sWeightScaleFactor_ = scaleFactor;
}

void LauAbsFitModel::setBkgndClassNames( const std::vector<TString>& names )
{
	if ( !bkgndClassNames_.empty() ) {
		cerr << "WARNING in LauAbsFitModel::setBkgndClassNames : Names already stored, not changing them." << endl;
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
		cerr << "ERROR in LauAbsFitModel::bkgndClassID : Request for ID for invalid background class \"" << className << "\"." << endl;
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
		cerr << "ERROR in LauAbsFitModel::bkgndClassName : Request for name of invalid background class ID " << classID << "." << endl;
		return nullString_;
	}

	return iter->second;
}

void LauAbsFitModel::clearFitParVectors()
{
	cout << "Clearing fit vectors" << endl;
	fitVars_.clear();
}

void LauAbsFitModel::clearExtraVarVectors()
{
	cout << "Clearing extra ntuple variable vectors" << endl;
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
		cerr << "ERROR in LauAbsFitModel::writeSPlotData : Already have an sPlot ntuple setup, not doing it again." << endl;
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
	cout << "Creating generation ntuple." << endl;
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
			cout << "Generating experiment number " << iExpt_ << endl;
			genOK = this->genExpt();

			// Stop the timer and see how long the program took so far
			timer_.Stop();
			timer_.Print();

			if (!genOK) {
				// delete and recreate an empty tree
				genNtuple_->deleteAndRecreateTree();

				// then break out of the experiment loop
				cerr << "ERROR in LauAbsFitModel::generate : Problem in toy MC generation.  Starting again with updated parameters..." << endl;
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
	cout << "Finished generating all experiments." << endl;
	cout << "Cumulative timing:" << endl;
	cumulTimer_.Print();

	// Build the event index
	cout << "Building experiment:event index." << endl;
	// TODO - can test this return value?
	//Int_t nIndexEntries =
	genNtuple_->buildIndex("iExpt","iEvtWithinExpt");

	// Write out toy MC ntuple
	cout << "Writing data to file " << dataFileName << "." << endl;
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

	// Check whether we're going to use asymmetric errors
	// This boolean can be changed with the useAsymmFitErrors(Bool_t) function
	if (useAsymmFitErrors_ == kTRUE) {
		cout << "We are going to use MINOS to calculate the asymmetric fit errors." << endl;
		cout << "This will in general significantly increase the CPU time required for fitting." << endl;
		cout << "Use setCalcAsymmFitErrors(kFALSE) if you want disable this feature." << endl;
	}

	cout << "First experiment = " << firstExpt_ << endl;
	cout << "Number of experiments = " << nExpt_ << endl;

	// Start the cumulative timer
	cumulTimer_.Start();

	numberOKFits_ = 0, numberBadFits_ = 0;
	fitStatus_ = -1;

	// Create and setup the fit results ntuple
	cout << "Creating fit ntuple." << endl;
	if (fitNtuple_ != 0) {delete fitNtuple_; fitNtuple_ = 0;}
	fitNtuple_ = new LauFitNtuple(histFileName);

	// Create and setup the sPlot ntuple
	if (this->writeSPlotData()) {
		cout << "Creating sPlot ntuple." << endl;
		if (sPlotNtuple_ != 0) {delete sPlotNtuple_; sPlotNtuple_ = 0;}
		sPlotNtuple_ = new LauGenNtuple(sPlotFileName_,sPlotTreeName_);
		this->setupSPlotNtupleBranches();
	}

	// This reads in the given dataFile and creates an input
	// fit data tree that stores them for all events and experiments.
	Bool_t dataOK = this->cacheFitData(dataFileName,dataTreeName);
	if (!dataOK) {
		cerr << "ERROR in LauAbsFitModel::fit : Problem caching the fit data." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Loop over the number of experiments
	for (iExpt_ = firstExpt_; iExpt_ < (firstExpt_+nExpt_); ++iExpt_) {

		// Start the timer to see how long each fit takes
		timer_.Start();

		inputFitData_->readExperimentData(iExpt_);
		this->eventsPerExpt(inputFitData_->nEvents());

		if (this->eventsPerExpt() < 1) {
			cerr << "ERROR in LauAbsFitModel::fit : Zero events in experiment " << iExpt_ << ", skipping..." << endl;
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

		// Store the per-event likelihood values
		if ( this->writeSPlotData() ) {
			this->storePerEvtLlhds();
		}

		// Create a toy MC sample for the 1st successful experiment
		// using the fitted parameters so that the user can compare
		// the fit to the actual data. The toy MC stats are a
		// factor of 10 higher than the number of events specified
		// via setNEvGen. This is to reduce the statistical
		// fluctuations for the toy MC data.
		if (compareFitData_ == kTRUE && fitStatus_ == 3) {
			this->createFitToyMC(fitToyMCFileName_, fitToyMCTableName_);
			compareFitData_ = kFALSE; // only do this for the first successful experiment
		}

		// Stop the timer and see how long the program took so far
		timer_.Stop();
		timer_.Print();

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
	cout << " Cumulative timing:" << endl;
	cumulTimer_.Print();

	// Print out stats on OK fits.
	cout << "Number of OK Fits = " << numberOKFits_ << endl;
	cout << "Number of Failed Fits = " << numberBadFits_ << endl;
	Double_t fitEff(0.0);
	if (nExpt_ != 0) {fitEff = numberOKFits_/(1.0*nExpt_);}
	cout << "Fit efficiency = " << fitEff*100.0 << "%." << endl;

	// Write out any fit results (ntuples etc...).
	this->writeOutAllFitResults();
	if ( this->writeSPlotData() ) {
		this->calculateSPlotData();
	}
}

void LauAbsFitModel::fitMaster(const TString& dataFileName, const TString& dataTreeName, const TString& histFileName, const TString& tableFileNameBase)
{
	this->fit( dataFileName, dataTreeName, histFileName, tableFileNameBase );
}

void LauAbsFitModel::fitSlave(const TString& dataFileName, const TString& dataTreeName)
{

	// This reads in the given dataFile and creates an input
	// fit data tree that stores them for all events and experiments.
	Bool_t dataOK = this->cacheFitData(dataFileName,dataTreeName);
	if (!dataOK) {
		cerr << "ERROR in LauAbsFitModel::fit : Problem caching the fit data." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	inputFitData_->readExperimentData(0);
	this->eventsPerExpt(inputFitData_->nEvents());

	if (this->eventsPerExpt() < 1) {
		cerr << "ERROR in LauAbsFitModel::fit : Zero events in experiment " << firstExpt_ << ", aborting..." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	this->cacheInputFitVars();
	if ( this->doSFit() ) {
		this->cacheInputSWeights();
	}
	std::cout << "\nSlave " << slaveId_ << " ready...\n" << std::endl;


	// infinite loop waiting messages from server with new parameters
	TMessage messageToMaster_(kMESS_OBJECT);
	char str[128];

	while (1) {
		sMaster_->Recv(messageFromMaster_);
		if (!messageFromMaster_) break;

		if (messageFromMaster_->What() == kMESS_STRING) {
			messageFromMaster_->ReadString(str, 128);
			TString msg( str );
			std::cout << "Message from master: " << msg << std::endl;
			if (msg == "Finish") {
				break;
			}
		} else if (messageFromMaster_->What() == kMESS_OBJECT) {
			TVectorD *vecPars_ = dynamic_cast<TVectorD*>( messageFromMaster_->ReadObject( messageFromMaster_->GetClass() ) );
			if (vecPars_) {
				Double_t * params = vecPars_->GetMatrixArray();
				UInt_t npar  = static_cast<UInt_t>( params[0] );
				//Int_t iflag = (Int_t)params[1];

				// We split the data among the slaves.
				UInt_t nEventsPerSlave = this->eventsPerExpt() / nSlaves_;
				UInt_t start( nEventsPerSlave*slaveId_ );
				UInt_t end( nEventsPerSlave*(slaveId_+1) );
				if ( slaveId_ == (nSlaves_-1) ) {
					end = this->eventsPerExpt();
				}

				for (UInt_t i=2;i<npar+2;i++) {
					if (!fitVars_[i-2]->fixed()) {
						fitVars_[i-2]->value(params[i]);
					}
				}
				this->propagateParUpdates();

				Double_t func = this->getLogLikelihood(start,end);

				// send the function in the same vector
				vecPars_[0] = func;
				messageToMaster_.Reset();
				messageToMaster_.WriteObject(vecPars_);   
				sMaster_->Send(messageToMaster_);         
				delete vecPars_;
			}
		} else {
			std::cerr << "ERROR in LauAbsFitModel::fitSlave : *** Unexpected type of message from master ***" << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}

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
	// Routine to perform the actual fit for the given experiment, and store
	// the results in the histograms if required (doHist == kTRUE).

	// Reset the worst likelihood found to its catch-all value
	worstLogLike_ = DBL_MAX;

	// Hook the external likelihood function to this LauFitter::fitter() and this class.
	LauFitter::fitter()->SetFCN(logLikeFun);
	LauFitter::fitter()->SetObjectFit(this);

	// Clear any stored parameters etc... before using
	LauFitter::fitter()->Clear();

	// Define the default relative error
	const Double_t defaultError(0.01);

	// Update initial fit parameters if required (e.g. if using random numbers).
	this->checkInitFitParams();

	nParams_ = fitVars_.size();
	cout << "Total number of parameters = " << nParams_ << endl;
	cout << "Setting fit parameters" << endl;

	// Set-up the parameters to be fit
	for (UInt_t i = 0; i < nParams_; i++) {
		TString name = fitVars_[i]->name();
		Double_t initVal = fitVars_[i]->initValue();
		Double_t initErr = fitVars_[i]->error();
		if ( initVal == 0.0 ) {
			initErr = defaultError;
		} else if ( TMath::Abs(initErr/initVal) < 1e-6 ) {
			initErr = TMath::Abs(defaultError * initVal);
		}
		Double_t minVal = fitVars_[i]->minValue();
		Double_t maxVal = fitVars_[i]->maxValue();
		Bool_t secondStage = fitVars_[i]->secondStage();
		if (this->twoStageFit() && secondStage == kTRUE) {
			fitVars_[i]->fixed(kTRUE);
		}
		Bool_t fixVar = fitVars_[i]->fixed();

		cout << "Setting parameter " << i << " called " << name << " to have initial value " << initVal << ", error " << initErr << " and range " << minVal << " to " << maxVal << endl;
		LauFitter::fitter()->SetParameter(i, name, initVal, initErr, minVal, maxVal);

		// Fix parameter if required
		if (fixVar == kTRUE) {
			cout << "Fixing parameter " << i << std::endl;
			LauFitter::fitter()->FixParameter(i);
		} 
	}

	LauParamFixed pred;
	nFreeParams_ = nParams_ - std::count_if(fitVars_.begin(),fitVars_.end(),pred);

	// Need to set the "SET ERR" command to +0.5 for +/-1 sigma errors
	// for maximum likelihood fit. Very important command, otherwise all
	// extracted errors will be too big, and pull distributions will be too narrow!
	// TODO - The alternative to this is to make FCN = -2log(L) rather than -log(L)
	Double_t argL[2];
	argL[0] = 0.5;
	fitStatus_ = LauFitter::fitter()->ExecuteCommand("SET ERR", argL, 1);

	//argL[0] = 0;
	//fitStatus_ = LauFitter::fitter()->ExecuteCommand("SET STRATEGY", argL, 1);

	// Now ready for minimization step
	cout << "\n...Start minimization...\n";
	Bool_t ok = this->runMinimisation();

	// If we're doing a two stage fit we can now release (i.e. float)
	// the 2nd stage parameters and re-fit
	if (this->twoStageFit()) {

		if (!ok) {
			cerr << "ERROR in LauAbsFitModel:fitExpt : Not running second stage fit since first stage failed." << endl;
			// Need to mark the second stage parameters as free
			// now so that the fit ntuple doesn't get confused
			for (UInt_t i = 0; i < nParams_; i++) {
				Bool_t secondStage = fitVars_[i]->secondStage();
				if (secondStage == kTRUE) {
					fitVars_[i]->fixed(kFALSE);
				}
			}
		} else {
			for (UInt_t i = 0; i < nParams_; i++) {
				// Release "secondStage" parameters
				Bool_t secondStage = fitVars_[i]->secondStage();
				if (secondStage == kTRUE) {
					fitVars_[i]->fixed(kFALSE);
					LauFitter::fitter()->ReleaseParameter(i);
				} 
				// Fix "firstStage" parameters
				Bool_t firstStage = fitVars_[i]->firstStage();
				if (firstStage == kTRUE) {
					fitVars_[i]->fixed(kTRUE);
					LauFitter::fitter()->FixParameter(i);
				} 
			}
			nFreeParams_ = nParams_ - std::count_if(fitVars_.begin(),fitVars_.end(),pred);
			this->runMinimisation();
		}
	}

	// Store the final fit results and errors into protected internal vectors that
	// all sub-classes can use within their own finalFitResults implementation
	// used below (e.g. putting them into an ntuple in a root file)
	for (UInt_t i = 0; i < nParams_; i++) {
		// Get the value and errors from MINUIT
		Double_t value = LauFitter::fitter()->GetParameter(i);
		Double_t error(0.0);
		Double_t negError(0.0);
		Double_t posError(0.0);
		Double_t globalcc(0.0);
		if (useAsymmFitErrors_) {
			LauFitter::fitter()->GetErrors(i, posError, negError, error, globalcc);
		} else {
			error = LauFitter::fitter()->GetParError(i);
		}
		fitVars_[i]->valueAndErrors(value, error, negError, posError);

		// release "firstStage" parameters so fit results are stored
		Bool_t firstStage = fitVars_[i]->firstStage();
		if (firstStage == kTRUE) {
			fitVars_[i]->fixed(kFALSE);
		} 
	}
}

Bool_t LauAbsFitModel::runMinimisation()
{
	Double_t arglist[2];
	arglist[0] = 1000*nParams_; // maximum iterations
	arglist[1] = 0.05; // tolerance -> min EDM = 0.001*tolerance (0.05)
	fitStatus_ = LauFitter::fitter()->ExecuteCommand("MIGRAD", arglist, 2);

	// Dummy variables - need to feed them to the function
	// used for getting NLL and error matrix status
	Double_t edm, errdef;
	Int_t nvpar, nparx;

	if (fitStatus_ != 0) {

		cerr << "Error in minimising loglike." << endl;

	} else {

		// Check that the error matrix is ok
		NLL_ = 0.0;
		fitStatus_ = LauFitter::fitter()->GetStats(NLL_, edm, errdef, nvpar, nparx);
		cout << "Error matrix status after MIGRAD is: " << fitStatus_ << endl;
		// 0= not calculated at all
		// 1= approximation only, not accurate
		// 2= full matrix, but forced positive-definite
		// 3= full accurate covariance matrix

		// Fit result was OK. Now get the more precise errors.
		fitStatus_ = LauFitter::fitter()->ExecuteCommand("HESSE", arglist, 1);

		if (fitStatus_ != 0) {

			cerr << "Error in Hesse routine." << endl;

		} else {

			// Check that the error matrix is ok
			NLL_ = 0.0;
			fitStatus_ = LauFitter::fitter()->GetStats(NLL_, edm, errdef, nvpar, nparx);
			cout << "Error matrix status after HESSE is: " << fitStatus_ << endl;
			// 0= not calculated at all
			// 1= approximation only, not accurate
			// 2= full matrix, but forced positive-definite
			// 3= full accurate covariance matrix

			// Symmetric errors and eror matrix were OK. 
			// Get asymmetric errors if asked for.
			if (useAsymmFitErrors_ == kTRUE) {
				withinMINOS_ = kTRUE;
				fitStatus_ = LauFitter::fitter()->ExecuteCommand("MINOS", arglist, 1); 
				withinMINOS_ = kFALSE;
				if (fitStatus_ != 0) {
					cerr << "Error in Minos routine." << endl;
				}
			}
		}
	}

	// Print results
	NLL_ = 0.0;
	fitStatus_ = LauFitter::fitter()->GetStats(NLL_, edm, errdef, nvpar, nparx);
	// If the error matrix is not accurate, fail the fit
	cout << "Final error matrix status is: " << fitStatus_ << endl;
	// 0= not calculated at all
	// 1= approximation only, not accurate
	// 2= full matrix, but forced positive-definite
	// 3= full accurate covariance matrix

	LauFitter::fitter()->PrintResults(3, NLL_);

	return (fitStatus_ == 3);
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
	// Create a toy MC sample so that the user can eventually 
	// compare the "fitted" result with the data
	// Generate more toy MC to reduce statistical fluctuations. Use the
	// rescaling value fitToyMCScale_.

	// Store the info on the number of experiments, first expt and current expt
	UInt_t oldNExpt(this->nExpt());
	UInt_t oldFirstExpt(this->firstExpt());
	UInt_t oldIExpt(iExpt_);

	// Turn off Poisson smearing if required
	Bool_t poissonSmearing(this->doPoissonSmearing());
	this->doPoissonSmearing(fitToyMCPoissonSmear_);

	// Turn off embedding, since we need toy MC, not reco'ed events
	Bool_t enableEmbeddingOrig(this->enableEmbedding());
	this->enableEmbedding(kFALSE);

	// Need to make sure that the generation of the DP co-ordinates is
	// switched on if any of our PDFs depend on it
	Bool_t origUseDP = this->useDP();
	if ( this->pdfsDependOnDP() && !origUseDP ) {
		this->useDP( kTRUE );
		this->initialiseDPModels();
	}

	// Generate the toy MC
	cout << "Generating toy MC in " << mcFileName << " to compare fit with data..." << endl;
	cout << "Number of experiments to generate = " << this->nExpt() << ", which is a factor of "
		<<fitToyMCScale_ << " higher than that originally specified. "
		<<"This is to allow the toy MC to be made with reduced statistical "
		<<"fluctuations." << endl;

	// Set the genValue of each parameter to its current (fitted) value
	// but first store the original genValues for restoring later
	vector<Double_t> origGenValues;  origGenValues.reserve(nParams_);
	for (LauParameterPList::iterator iter = fitVars_.begin(); iter != fitVars_.end(); ++iter) {
		origGenValues.push_back((*iter)->genValue());
		(*iter)->genValue((*iter)->value());
	}

	// If we're asked to generate more than 100 experiments then split it
	// up into multiple files since otherwise can run into memory issues
	// when building the index

	UInt_t totalExpts = oldNExpt * fitToyMCScale_;
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
			TString filename(mcFileName);
			filename.Insert( filename.Index("."), extraname );
			this->generate(filename, "genResults", "dummy.root", tableFileName);
		}
	} else {
		// Set number of experiments to new value
		this->setNExpts(oldNExpt*fitToyMCScale_, 0);
		// Generate the toy
		this->generate(mcFileName, "genResults", "dummy.root", tableFileName);
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

	cout << "Finished in createFitToyMC." << endl;
}

Double_t LauAbsFitModel::getTotNegLogLikelihood()
{
	// Calculate the total negative log-likelihood over all events.
	// This function assumes that the fit parameters and data tree have
	// already been set-up correctly.

	// Loop over the data points to calculate the log likelihood
	Double_t logLike(0.0);

	// Loop over the number of events in this experiment
	Bool_t ok(kTRUE);
	for (UInt_t iEvt = 0; iEvt < this->eventsPerExpt(); ++iEvt) {

		Double_t likelihood = this->getTotEvtLikelihood(iEvt);

		if (likelihood > DBL_MIN) {	// Is the likelihood zero?
			Double_t evtLogLike = TMath::Log(likelihood);
			if ( doSFit_ ) {
				evtLogLike *= sWeights_[iEvt];
			}
			logLike += evtLogLike;
		} else {
			ok = kFALSE;
			cerr << "WARNING in LauAbsFitModel::getTotNegLogLikelihood : Strange likelihood value for event " << iEvt << ": " << likelihood << "\n";
			this->printEventInfo(iEvt);
			this->printVarsInfo();	//Write the values of the floated variables for which the likelihood is zero
			break;
		}	
	}

	// Include the Poisson term in the extended likelihood if required
	if (this->doEMLFit()) {
		logLike -= this->getEventSum();
	}

	if (!ok) {
		cerr << "                                                  : Returning worst NLL found so far to force MINUIT out of this region." << endl;
		logLike = worstLogLike_;
	} else if (logLike < worstLogLike_) {
		worstLogLike_ = logLike;
	}

	Double_t totNegLogLike = -logLike;
	return totNegLogLike;
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
			cerr << "WARNING in LauAbsFitModel::getLogLikelihood : Strange likelihood value for event " << iEvt << ": " << likelihood << "\n";
			this->printEventInfo(iEvt);
			this->printVarsInfo();	//Write the values of the floated variables for which the likelihood is zero
			break;
		}	
	}

	if (!ok) {
		cerr << "                                                  : Returning worst NLL found so far to force MINUIT out of this region." << endl;
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

	// MINOS reports one fewer free parameter than there actually is,
	// so increment npar so the following check doesn't fail
	if ( withinMINOS_ ) {
		++npar;
	}

	if (static_cast<UInt_t>(npar) != nFreeParams_) {
		cerr << "ERROR in LauAbsFitModel::setParsFromMinuit : Unexpected number of free parameters: " << npar << ".\n";
		cerr << "                                             Expected: " << nFreeParams_ << ".\n" << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Despite npar being the number of free parameters
	// the par array actually contains all the parameters,
	// free and floating...
	// Update all the floating ones with their new values.
	for (UInt_t i(0); i<nParams_; ++i) {
		if (!fitVars_[i]->fixed()) {
			fitVars_[i]->value(par[i]);
		}
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
		LauParameterPList& pars = pdf->getParameters();
		for (LauParameterPList::iterator pars_iter = pars.begin(); pars_iter != pars.end(); ++pars_iter) {
			if ( !(*pars_iter)->clone() && 	( !(*pars_iter)->fixed() ||
						(this->twoStageFit() && ( (*pars_iter)->secondStage() || (*pars_iter)->firstStage())) ) ) {
				fitVars_.push_back(*pars_iter);
				++nParsAdded;
			}
		}
	}
	return nParsAdded;
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
		const LauParameterPList& pars = (*pdf_iter)->getParameters();
		for (LauParameterPList::const_iterator pars_iter = pars.begin(); pars_iter != pars.end(); ++pars_iter) {
			if (!(*pars_iter)->clone()) {
				fout << (*pars_iter)->name() << "  &  $";
				print.printFormat(fout, (*pars_iter)->value());
				if ((*pars_iter)->fixed() == kTRUE) {
					fout << "$ (fixed) \\\\";
				} else {
					fout << " \\pm ";
					print.printFormat(fout, (*pars_iter)->error());
					fout << "$ \\\\" << endl;
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
	cerr << "                                                  : Input data values for this event:" << endl;
	for (LauFitData::const_iterator iter = data.begin(); iter != data.end(); ++iter) {
		cerr << " " << iter->first << " = " << iter->second << endl;
	}
}

void LauAbsFitModel::printVarsInfo() const
{
	cerr << "                                                  : Current values of fit parameters:" << endl;
	for (UInt_t i(0); i<nParams_; ++i) {
		cerr << " " << (fitVars_[i]->name()).Data() << " = " << fitVars_[i]->value() << endl;
	}
}

Double_t LauAbsFitModel::calculateLogLike(Int_t npar, Double_t* par, Int_t iflag)
{
	// check if we're running a parallel setup or not
	if ( socketMonitor_ == 0 ) {
		// we're not, so just do things normally
		return this->getTotNegLogLikelihood();
	}

	TMessage messageToSlave(kMESS_OBJECT);
	TSocket  *sActual(0);

	//send current parameters to the clients. Must send all the par vector
	//In fact, the number npar = number of free parameters, while par has all parameters
	if ((UInt_t)npar > nParams_){
		std::cerr << "ERROR in LauAbsFitModel::calculateLogLike : Oops, too many parameters, abort" << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	(*vectorPar_)[0] = nParams_;
	(*vectorPar_)[1] = iflag;
	for (UInt_t i(0);i<nParams_;i++) (*vectorPar_)[i+2] = par[i];

	messageToSlave.WriteObject(vectorPar_);   //write vector of parameters in message buffer
	for ( UInt_t i(0); i<nSlaves_; ++i ) {
		sSlaves_[i]->Send(messageToSlave);
	}

	Double_t func(0.0);
	UInt_t msgsReceived(0);
	while (1) {
		sActual = socketMonitor_->Select();
		sActual->Recv(messageFromSlave_);	    

		vectorRes_ = dynamic_cast<TVectorD*>( messageFromSlave_->ReadObject( messageFromSlave_->GetClass() ) );
		if (!vectorRes_) { 
			std::cerr << "ERROR in LauAbsFitModel::calculateLogLike : vector parameter is NULL !" << std::endl;
			return 0.0;
		}

		func += (*vectorRes_)[0];
		++msgsReceived;

		if (msgsReceived == nSlaves_) {
			break;
		}
	} 

	// Include the Poisson term in the extended likelihood if required
	if (this->doEMLFit()) {
		func -= this->getEventSum();
	}

	Double_t negLogLike = -func;
	return negLogLike;
}

// Definition of the fitting function for Minuit
void logLikeFun(Int_t& npar, Double_t* /*first-derivatives*/, Double_t& f, Double_t* par, Int_t iflag)
{
	// Routine that specifies the negative log-likelihood function for the fit.
	// Used by the MINUIT minimising code.

	LauAbsFitModel* theModel = dynamic_cast<LauAbsFitModel*>(LauFitter::fitter()->GetObjectFit());

	// Set the internal parameters for this model using parameters from Minuit (pars):
	theModel->setParsFromMinuit( par, npar );

	// Set the value of f to be the total negative log-likelihood for the data sample.
	f = theModel->calculateLogLike( npar, par, iflag );
}

