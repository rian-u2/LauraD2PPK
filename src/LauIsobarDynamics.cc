
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauIsobarDynamics.cc
    \brief File containing implementation of LauIsobarDynamics class.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
using std::cout;
using std::cerr;
using std::endl;
using std::setprecision;
using std::ifstream;
using std::ofstream;

#include "TFile.h"
#include "TRandom.h"
#include "TSystem.h"

#include "LauAbsResonance.hh"
#include "LauBelleNR.hh"
#include "LauBelleSymNR.hh"
#include "LauConstants.hh"
#include "LauDaughters.hh"
#include "LauEffModel.hh"
#include "LauFitDataTree.hh"
#include "LauGounarisSakuraiRes.hh"
#include "LauIntegrals.hh"
#include "LauIsobarDynamics.hh"
#include "LauKinematics.hh"
#include "LauKMatrixPropagator.hh"
#include "LauKMatrixPropFactory.hh"
#include "LauKMatrixProdPole.hh"
#include "LauKMatrixProdSVP.hh"
#include "LauNRAmplitude.hh"
#include "LauPolNR.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"
#include "LauRelBreitWignerRes.hh"
#include "LauResonanceMaker.hh"

ClassImp(LauIsobarDynamics)


// for Kpipi: only one scfFraction 2D histogram is needed
LauIsobarDynamics::LauIsobarDynamics(LauDaughters* daughters, LauEffModel* effModel, LauEffModel* scfFractionModel) :
	LauAbsDPDynamics(daughters, effModel, scfFractionModel),
	symmetricalDP_(kFALSE),
	integralsDone_(kFALSE),
	intFileName_("integ.dat"),
	m13BinWidth_(0.005),
	m23BinWidth_(0.005),
	m13Sq_(0.0),
	m23Sq_(0.0),
	mPrime_(0.0),
	thPrime_(0.0),
	eff_(0.0),
	scfFraction_(0.0),
	jacobian_(0.0),
	ASq_(0.0),
	evtLike_(0.0),
	iterationsMax_(100000),
	nSigGenLoop_(0),
	aSqMaxSet_(1.25),
	aSqMaxVar_(0.0),
	BelleNRAlpha_(0.0),
	LASSScatteringLength_(0.0),
	LASSEffectiveRange_(0.0),
	LASSResonanceMag_(0.0),
	LASSResonancePhase_(0.0),
	LASSBackgroundMag_(0.0),
	LASSBackgroundPhase_(0.0),
	LASSCutOff_(0.0),
	changeLASSScatteringLength_(kFALSE),
	changeLASSEffectiveRange_(kFALSE),
	changeLASSResonanceMag_(kFALSE),
	changeLASSResonancePhase_(kFALSE),
	changeLASSBackgroundMag_(kFALSE),
	changeLASSBackgroundPhase_(kFALSE),
	changeLASSCutOff_(kFALSE),
	FlatteParameterg1_(0.0),
	FlatteParameterg2_(0.0),
	changeFlatteParameterg1_(kFALSE),
	changeFlatteParameterg2_(kFALSE),
	resBarrierRadius_(4.0),
	parBarrierRadius_(4.0),
	barrierType_( LauAbsResonance::BWPrimeBarrier ),
	flipHelicity_(kTRUE)
{
	// Constructor for the isobar signal model
	if (daughters != 0) {
		symmetricalDP_ = daughters->gotSymmetricalDP();
		typDaug_.push_back(daughters->getTypeDaug1());
		typDaug_.push_back(daughters->getTypeDaug2());
		typDaug_.push_back(daughters->getTypeDaug3());
	}
	sigResonances_.clear();
	kMatrixPropagators_.clear();
	kMatrixPropSet_.clear();
}

// for Kspipi, we need a scfFraction 2D histogram for each tagging category. They are provided by the map.
// Also, we need to know the place that the tagging category of the current event occupies in the data structure inputFitTree
LauIsobarDynamics::LauIsobarDynamics(LauDaughters* daughters, LauEffModel* effModel, LauTagCatScfFractionModelMap scfFractionModel) :
	LauAbsDPDynamics(daughters, effModel, scfFractionModel),
	symmetricalDP_(kFALSE),
	integralsDone_(kFALSE),
	intFileName_("integ.dat"),
	m13BinWidth_(0.005),
	m23BinWidth_(0.005),
	m13Sq_(0.0),
	m23Sq_(0.0),
	mPrime_(0.0),
	thPrime_(0.0),
	eff_(0.0),
	scfFraction_(0.0),
	jacobian_(0.0),
	ASq_(0.0),
	evtLike_(0.0),
	iterationsMax_(100000),
	nSigGenLoop_(0),
	aSqMaxSet_(1.25),
	aSqMaxVar_(0.0),
	BelleNRAlpha_(0.0),
	LASSScatteringLength_(0.0),
	LASSEffectiveRange_(0.0),
	LASSResonanceMag_(0.0),
	LASSResonancePhase_(0.0),
	LASSBackgroundMag_(0.0),
	LASSBackgroundPhase_(0.0),
	LASSCutOff_(0.0),
	changeLASSScatteringLength_(kFALSE),
	changeLASSEffectiveRange_(kFALSE),
	changeLASSResonanceMag_(kFALSE),
	changeLASSResonancePhase_(kFALSE),
	changeLASSBackgroundMag_(kFALSE),
	changeLASSBackgroundPhase_(kFALSE),
	changeLASSCutOff_(kFALSE),
	FlatteParameterg1_(0.0),
	FlatteParameterg2_(0.0),
	changeFlatteParameterg1_(kFALSE),
	changeFlatteParameterg2_(kFALSE),
	resBarrierRadius_(4.0),
	parBarrierRadius_(4.0),
	barrierType_( LauAbsResonance::BWPrimeBarrier ),
	flipHelicity_(kTRUE)
{
	// Constructor for the isobar signal model
	if (daughters != 0) {
		symmetricalDP_ = daughters->gotSymmetricalDP();
		typDaug_.push_back(daughters->getTypeDaug1());
		typDaug_.push_back(daughters->getTypeDaug2());
		typDaug_.push_back(daughters->getTypeDaug3());
	}
	sigResonances_.clear();
	kMatrixPropagators_.clear();
	kMatrixPropSet_.clear();
}

LauIsobarDynamics::~LauIsobarDynamics()
{
}

void LauIsobarDynamics::initialise(const std::vector<LauComplex>& coeffs)
{
	// Check whether we have a valid set of integration constants for
	// the normalisation of the signal likelihood function.
	this->initialiseVectors();

	integralsDone_ = kFALSE;

	// Print summary of what we have so far to screen
	this->initSummary();

	if ( nAmp_ == 0 ) {
		cout << "No contributions to DP model, not performing normalisation integrals." << endl;
	} else {

		// We need to calculate the normalisation constants for the
		// Dalitz plot generation/fitting.
		cout<<"Starting special run to generate the integrals for normalising the PDF..."<<endl;
		this->calcDPNormalisation();

		// Write the integrals to a file (mainly for debugging purposes)
		this->writeIntegralsFile();
	}


	integralsDone_ = kTRUE;

	cout << setprecision(10);

	// Calculate and cache the relative normalisations of each resonance _dynamic_ amplitude
	// (e.g. Breit-Wigner contribution, not from the complex amplitude/phase) w.r.t. the
	// total DP amplitude. These are stored in fNorm_[i].
	// The normalisation uses fSqSum[i], which is calculated within the dynamics() function, 
	// which has already been called by the calcDPNomalisation() function above to create the 
	// normalisation integrals. 
	// fSqSum[i] is the event-by-event running total of the dynamical amplitude 
	// squared for a given resonance, i. We require that:
	// |fNorm_[i]|^2 * |fSqSum[i]|^2 = 1,
	// i.e. fNorm_[i] normalises each resonance contribution to give the same number of
	// events in the DP, accounting for the total DP area and the
	// dynamics of the resonance.

	for (UInt_t i = 0; i < nAmp_; i++) {
		fNorm_[i] = 0.0;
		if (fSqSum_[i] > 0.0) {fNorm_[i] = TMath::Sqrt(1.0/(fSqSum_[i]));}
		cout<<" fNorm["<<i<<"] = "<<fNorm_[i]<<endl;
		cout<<" fSqSum["<<i<<"] = "<<fSqSum_[i]<<endl;
	}

	for (UInt_t i = 0; i < nAmp_; i++) {    
		for (UInt_t j = 0; j < nAmp_; j++) {
			cout<<" fifjEffSum["<<i<<"]["<<j<<"] = "<<fifjEffSum_[i][j];
		}
		cout<<endl;
	}

	for (UInt_t i = 0; i < nAmp_; i++) {    
		for (UInt_t j = 0; j < nAmp_; j++) {
			cout<<" fifjSum["<<i<<"]["<<j<<"] = "<<fifjSum_[i][j];
		}
		cout<<endl;
	}

	// Calculate the initial fit fractions (for later comparison with Toy MC, if required)
	this->updateCoeffs(coeffs);
	this->calcExtraInfo(kTRUE);
	for (UInt_t i = 0; i < nAmp_; i++) {
		for (UInt_t j = i; j < nAmp_; j++) {
			cout<<"Initial fit fraction for amplitude ("<<i<<","<<j<<") = "<<fitFrac_[i][j].genValue()<<endl;
		}
	}

	cout<<"Initial efficiency = "<<meanDPEff_.initValue()<<endl;

	cout<<"Initial DPRate = "<<DPRate_.initValue()<<endl;
}

void LauIsobarDynamics::initSummary()
{

	UInt_t i(0);
	TString nameP = daughters_->getNameParent();
	TString name1 = daughters_->getNameDaug1();
	TString name2 = daughters_->getNameDaug2();
	TString name3 = daughters_->getNameDaug3();

	cout<<"We are going to do a DP with "<<nameP<<" going to "<<name1<<" "<<name2<<" "<<name3<<endl;

	cout<<"For the following resonance combinations:"<<endl;

	cout<<"In tracks 2 and 3:"<<endl;
	for (i = 0; i < nAmp_; i++) {
		if (resPairAmp_[i] == 1) {
			cout<<"  "<<resTypAmp_[i]<<" to " <<name2<<", "<< name3<<endl;
		}
	}

	cout<<endl;

	cout<<"In tracks 1 and 3:"<<endl;
	for (i = 0; i < nAmp_; i++) {
		if (resPairAmp_[i] == 2) {
			cout<<"  "<<resTypAmp_[i]<<" to "<<name1<<", "<< name3<<endl;
		}
	}

	cout<<endl;

	cout<<"In tracks 1 and 2:"<<endl;
	for (i = 0; i < nAmp_; i++) {
		if (resPairAmp_[i] == 3) {
			cout<<"  "<<resTypAmp_[i]<<" to "<<name1<<", "<< name2<<endl;
		}
	}

	cout<<endl;

	for (i = 0; i < nAmp_; i++) {
		if (resPairAmp_[i] == 0) {
			cout<<"and a non-resonant amplitude."<<endl;
		}
	}

	cout<<endl;
}

void LauIsobarDynamics::initialiseVectors()
{
	fSqSum_.clear();     fSqSum_.resize(nAmp_);
	fifjEffSum_.clear(); fifjEffSum_.resize(nAmp_);
	fifjSum_.clear();    fifjSum_.resize(nAmp_);
	ff_.clear();         ff_.resize(nAmp_);
	fNorm_.clear();      fNorm_.resize(nAmp_);
	fitFrac_.clear();    fitFrac_.resize(nAmp_);

	LauComplex null(0.0, 0.0);

	for (UInt_t i = 0; i < nAmp_; i++) {

		fSqSum_[i] = 0.0; fNorm_[i] = 0.0;
		ff_[i] = null;
		fifjEffSum_[i].resize(nAmp_);
		fifjSum_[i].resize(nAmp_);
		fitFrac_[i].resize(nAmp_);

		for (UInt_t j = 0; j < nAmp_; j++) {
			fifjEffSum_[i][j] = null;
			fifjSum_[i][j] = null;
			fitFrac_[i][j].valueAndRange(0.0, -100.0, 100.0);
		}
	}

	UInt_t nKMatrixProps = kMatrixPropagators_.size();
	extraParameters_.clear();
	extraParameters_.resize( nKMatrixProps );

	for ( UInt_t i = 0; i < nKMatrixProps; ++i ) {
		extraParameters_[i].valueAndRange(0.0, -100.0, 100.0);
	}
}


void LauIsobarDynamics::writeIntegralsFile()
{
	// Routine to end integration calculation for loglike normalisation.
	// This writes out the normalisation integral output into the file named
	// outputFileName.
	cout<<"Writing integral output to integrals file "<<intFileName_.Data()<<endl;

	UInt_t i(0), j(0);
	ofstream getChar(intFileName_.Data());

	getChar << setprecision(10);

	// Write out daughter types (pi, pi0, K, K0s?)
	for (i = 0; i < 3; i++) {    
		getChar << typDaug_[i] << " ";
	}

	// Write out number of resonances in the Dalitz plot model
	getChar << nAmp_ << endl;

	// Write out the resonances
	for (i = 0; i < nAmp_; i++) {
		getChar << resTypAmp_[i] << " ";
	}

	getChar << endl;

	// Write out the resonance model types (BW, RelBW etc...)
	for (i = 0; i < nAmp_; i++) {
		LauAbsResonance* theResonance = sigResonances_[i];
		Int_t resModelInt = theResonance->getResonanceModel();
		getChar << resModelInt << " ";
	}

	getChar << endl;

	// Write out the track pairings for each resonance. This is specified
	// by the resPairAmpInt integer in the addResonance function.
	for (i = 0; i < nAmp_; i++) {
		getChar << resPairAmp_[i] << " ";
	}

	getChar << endl;

	// Write out the fSqSum = |ff|^2, where ff = resAmp()
	for (i = 0; i < nAmp_; i++) {
		getChar << fSqSum_[i] << " ";
	}

	getChar << endl;

	// Write out the f_i*f_j_conj*eff values = resAmp_i*resAmp_j_conj*eff.
	// Note that only the top half of the i*j "matrix" is required, as it
	// is symmetric w.r.t i, j.
	for (i = 0; i < nAmp_; i++) {
		for (j = i; j < nAmp_; j++) {
			getChar << fifjEffSum_[i][j] << " ";
		}
	}

	getChar << endl;

	// Similar to fifjEffSum, but without the efficiency term included.
	for (i = 0; i < nAmp_; i++) {
		for (j = i; j < nAmp_; j++) {
			getChar << fifjSum_[i][j] << " ";
		}
	}

	getChar << endl;

}

void LauIsobarDynamics::addResonance(const TString& resName, Int_t resPairAmpInt, const TString& resType, Double_t newMass, Double_t newWidth, Int_t newSpin)
{
	// Function to add a resonance in a Dalitz plot (for signal). To add a resonance
	// in the continuum background, please use addBgResonance().
	// No check is made w.r.t flavour
	// and charge conservation rules, and so the user is responsible for checking the
	// internal consistency of their function statements with these laws. For example,
	// the program will not prevent the user from asking for a rho resonance
	// in a K-pi pair or a K* resonance in a pi-pi pair.
	// However, to assist the user, a summary of the resonant structure requested
	// by the user is printed before the program runs. It is important to check this
	// information when you first define your Dalitz plot model before doing
	// any fitting/generating.
	// Arguments are: resonance name, integer to specify the resonance track pairing
	// (1 => m_23, 2 => m_13, 3 => m_12), i.e. the bachelor track number.
	// Also required are the initial values of the magnitude and phase of the amplitude
	// for this resonance, and whether they are to be fixed in any fit.
	// Supported resonances for the resName (1st) argument are (case-sensitive):
	// Rho, Kst, f0_980, phi1020, f2_1270, Kst1410, Kst1430
	// K2*1430, Rho1450, Kst1680, Chic0, NonReson, f2_1525, f0_1500, 
	// Rho1700, f0_1370, (alternative) NRModel, a2_1320, Rho3_1690, a0_980
	// a0_1450, phi1680, a6_2450, phi3_1850.
	// The final argument resType specifies whether the resonance is a Breit-Wigner (BW)
	// Relativistic Breit-Wigner (RelBW) or Flatte distribution (Flatte), for example.

	LauAbsResonance *theResonance = 
		resonanceMaker_->getResonance(resName, resPairAmpInt, resType);

	if (theResonance == 0) {
		cout<<"Error. Couldn't find the resonance "<<resName<<endl;
		cout<<"Sorry. Resonance type is not recognised. Not added."<<endl;
		return;
	}

	// Change resonance and lineshape parameters as required.
	if (newMass > 0.0 || newWidth > 0.0 || newSpin > -1) {
		theResonance->changeResonance(newMass, newWidth, newSpin);
	}

	// implement the helicity flip here
	if (flipHelicity_ && daughters_->getCharge(resPairAmpInt) == 0) {	  
		if ( daughters_->getChargeParent() == 0 && daughters_->getTypeParent() > 0 ) {
			theResonance->flipHelicity(kTRUE);
		}
	}

	TString resTypeName(resType);

	// Reset the Blatt-Weisskopf barrier factors as appropriate
	if (!resTypeName.CompareTo("RelBW")) {
		LauRelBreitWignerRes* theRBW = dynamic_cast<LauRelBreitWignerRes*>(theResonance);
		theRBW->setBarrierRadii(resBarrierRadius_, parBarrierRadius_, barrierType_);
	} else if (!resTypeName.CompareTo("GS")) {
		LauGounarisSakuraiRes* theGS = dynamic_cast<LauGounarisSakuraiRes*>(theResonance);
		theGS->setBarrierRadii(resBarrierRadius_, parBarrierRadius_, barrierType_);
	}

	if (changeLASSScatteringLength_ == kTRUE && resTypeName.BeginsWith("LASS") ) {
		theResonance->setResonanceParameter(LASSScatteringLength_, "a");
	}
	if (changeLASSEffectiveRange_ == kTRUE && resTypeName.BeginsWith("LASS") ) {
		theResonance->setResonanceParameter(LASSEffectiveRange_, "r");
	}
	if (changeLASSResonanceMag_ == kTRUE && !resTypeName.CompareTo("LASS") ) {
		theResonance->setResonanceParameter(LASSResonanceMag_, "R");
	}
	if (changeLASSResonancePhase_ == kTRUE && !resTypeName.CompareTo("LASS") ) {
		theResonance->setResonanceParameter(LASSResonancePhase_, "phiR");
	}
	if (changeLASSBackgroundMag_ == kTRUE && !resTypeName.CompareTo("LASS") ) {
		theResonance->setResonanceParameter(LASSBackgroundMag_, "B");
	}
	if (changeLASSBackgroundPhase_ == kTRUE && !resTypeName.CompareTo("LASS") ) {
		theResonance->setResonanceParameter(LASSBackgroundPhase_, "phiB");
	}
	if (changeLASSCutOff_ == kTRUE && resTypeName.BeginsWith("LASS") ) {
		theResonance->setResonanceParameter(LASSCutOff_, "cutOff");
	}

	if (changeFlatteParameterg1_ == kTRUE && !resTypeName.CompareTo("Flatte") ) {
		theResonance->setResonanceParameter(FlatteParameterg1_, "g1");
	}
	if (changeFlatteParameterg2_ == kTRUE && !resTypeName.CompareTo("Flatte") ) {
		theResonance->setResonanceParameter(FlatteParameterg2_, "g2");
	}

	TString resonanceName = theResonance->getResonanceName();

	if ( resonanceName.BeginsWith("BelleNR", TString::kExact) ) {
		LauBelleNR* belleNR = dynamic_cast<LauBelleNR*>(theResonance);
		if (belleNR != 0) {
			belleNR->setAlpha(BelleNRAlpha_);
		} else {
			cout<<"Belle non-resonant object is null"<<endl;
		}
	} else if ( resonanceName.BeginsWith("BelleSymNR", TString::kExact) ) {
		LauBelleSymNR* belleNR = dynamic_cast<LauBelleSymNR*>(theResonance);
		if (belleNR != 0) {
			belleNR->initialise(symmetricalDP_, BelleNRAlpha_, resTypeName);
		} else {
			cout<<"Belle non-resonant object is null"<<endl;
		}

	} else if ( resonanceName.BeginsWith("PolNR", TString::kExact) ) {
		LauPolNR* polNR = dynamic_cast<LauPolNR*>(theResonance);
		Double_t omega = 0.5*(daughters_->getMassParent()+(1./3)*(daughters_->getMassDaug1()+daughters_->getMassDaug2()+daughters_->getMassDaug3()));
		if (polNR != 0) {
		  polNR->setOmega(omega);
		} else {
			cout<<"Polynomial non-resonant object is null"<<endl;
		}
	}
	// Initialise the resonance model
	theResonance->initialise();

	// Set the resonance name and what track is the bachelor
	resTypAmp_.push_back(resonanceName);
	resIntAmp_.push_back(resonanceMaker_->resTypeInt(resonanceName));

	// Always force the non-resonant amplitude pair to have resPairAmp = 0
	// in case the user chooses the wrong number.
	if (    (resonanceName.BeginsWith("NonReson",   TString::kExact) == kTRUE) || 
		(resonanceName.BeginsWith("BelleSymNR", TString::kExact) == kTRUE) ||
		(resonanceName.BeginsWith("PolNR",      TString::kExact) == kTRUE) ||
		(resonanceName.BeginsWith("NRModel",    TString::kExact) == kTRUE)) {
	        cout<<"Setting resPairAmp to 0 for "<<resonanceName<<" contribution."<<endl;
		resPairAmp_.push_back(0);
	} else {
		resPairAmp_.push_back(resPairAmpInt);
	}

	// Increment the number of resonance amplitudes we have so far
	nAmp_++;

	// Finally, add the resonance object to the internal array
	sigResonances_.push_back(theResonance);

	cout<<"Successfully added resonance. Total number of resonances so far = "<<nAmp_<<endl;

}

void LauIsobarDynamics::defineKMatrixPropagator(const TString& propName, const TString& paramFileName, Int_t resPairAmpInt, 
						Int_t nChannels, Int_t nPoles, Int_t rowIndex)
{
  // Define the K-matrix propagator. The resPairAmpInt integer specifies which mass combination should be used
  // for the invariant mass-squared variable "s". The pole masses and coupling constants are defined in the
  // paramFileName parameter file. The number of channels and poles are defined by the nChannels and nPoles integers, respectively.
  // The integer rowIndex specifies which row of the propagator should be used when 
  // summing over all amplitude channels: S-wave will be the first row, so rowIndex = 1.

  if (rowIndex < 1) {
    cerr<<"Error in defineKMatrixPropagator: rowIndex must be > 0 but is equal to "<<rowIndex<<endl;
    return;
  }

  TString propagatorName(propName), parameterFile(paramFileName);

  LauKMatrixPropagator* thePropagator = LauKMatrixPropFactory::getInstance()->getPropagator(propagatorName, parameterFile,
											    resPairAmpInt, nChannels,
											    nPoles, rowIndex);
  kMatrixPropagators_[propagatorName] = thePropagator;

}

void LauIsobarDynamics::addKMatrixProdPole(const TString& poleName, const TString& propName, Int_t poleIndex)
{

  // Add a K-matrix production pole term, using the K-matrix propagator given by the propName.
  // Here, poleIndex is the integer specifying the pole number.

  // First, find the K-matrix propagator.
  KMPropMap::iterator mapIter = kMatrixPropagators_.find(propName);
  if (mapIter != kMatrixPropagators_.end()) {

    LauKMatrixPropagator* thePropagator = mapIter->second;

    // Make sure the pole index is valid
    Int_t nPoles = thePropagator->getNPoles();
    if (poleIndex < 1 || poleIndex > nPoles) {
      cerr<<"Error in LauIsobarDynamics::addKMatrixProdPole. The pole index "<<poleIndex
	  <<" is not between 1 and "<<nPoles<<". Not adding production pole "<<poleName
	  <<" for K-matrix propagator "<<propName<<endl;
      return;
    }

    // Now add the K-matrix production pole amplitude to the vector of LauAbsResonance pointers.
    Int_t resPairAmpInt = thePropagator->getResPairAmpInt();
    LauAbsResonance* prodPole = new LauKMatrixProdPole(poleName, poleIndex, resPairAmpInt, thePropagator, daughters_);

    resTypAmp_.push_back(poleName);
    resIntAmp_.push_back(0);
    resPairAmp_.push_back(resPairAmpInt);

    nAmp_++;
    sigResonances_.push_back(prodPole);

    // Also store the propName-poleName pair for calculating total fit fractions later on 
    // (avoiding the need to use dynamic casts to check which resonances are of the K-matrix type)
    kMatrixPropSet_[poleName] = propName;

    cout<<"Successfully added K-matrix production pole term. Total number of resonances so far = "<<nAmp_<<endl;

  } else {

    cerr<<"Error in LauIsobarDynamics::addKMatrixProdPole. The propagator of the name "<<propName
	<<" could not be found for the production pole "<<poleName<<endl;

  }

}


void LauIsobarDynamics::addKMatrixProdSVP(const TString& SVPName, const TString& propName, Int_t channelIndex)
{

  // Add a K-matrix production "slowly-varying part" (SVP) term, using the K-matrix propagator 
  // given by the propName. Here, channelIndex is the integer specifying the channel number.

  // First, find the K-matrix propagator.
  KMPropMap::iterator mapIter = kMatrixPropagators_.find(propName);
  if (mapIter != kMatrixPropagators_.end()) {

    LauKMatrixPropagator* thePropagator = mapIter->second;

    // Make sure the channel index is valid
    Int_t nChannels = thePropagator->getNChannels();
    if (channelIndex < 1 || channelIndex > nChannels) {
      cerr<<"Error in LauIsobarDynamics::addKMatrixProdSVP. The channel index "<<channelIndex
	  <<" is not between 1 and "<<nChannels<<". Not adding production slowly-varying part "<<SVPName
	  <<" for K-matrix propagator "<<propName<<endl;
      return;
    }

    // Now add the K-matrix production SVP amplitude to the vector of LauAbsResonance pointers.
    Int_t resPairAmpInt = thePropagator->getResPairAmpInt();
    LauAbsResonance* prodSVP = new LauKMatrixProdSVP(SVPName, channelIndex, resPairAmpInt, thePropagator, daughters_);

    resTypAmp_.push_back(SVPName);
    resIntAmp_.push_back(0);
    resPairAmp_.push_back(resPairAmpInt);

    nAmp_++;
    sigResonances_.push_back(prodSVP);

    // Also store the SVPName-propName pair for calculating total fit fractions later on 
    // (avoiding the need to use dynamic casts to check which resonances are of the K-matrix type)
    kMatrixPropSet_[SVPName] = propName;

    cout<<"Successfully added K-matrix production slowly-varying (SVP) term. Total number of resonances so far = "
	<<nAmp_<<endl;    

  } else {

    cerr<<"Error in LauIsobarDynamics::addKMatrixProdSVP. The propagator of the name "<<propName
	<<" could not be found for the production slowly-varying part "<<SVPName<<endl;

  }

}

LauAbsResonance* LauIsobarDynamics::findResonance(const TString& name)
{
	TString testName(name);
	testName.ToLower();
	LauAbsResonance* theResonance(0);

	for (std::vector<LauAbsResonance*>::iterator iter=sigResonances_.begin(); iter!=sigResonances_.end(); ++iter) {
		theResonance = (*iter);
		if (theResonance != 0) {
			TString resString = theResonance->getResonanceName();
			resString.ToLower();
			if (resString.BeginsWith(testName, TString::kExact)) {
				return theResonance;
			}
		}
	}

	cout<<"ERROR in LauIsobarDynamics::findResonance : Couldn't find resonance \""<<name<<"\" in the model."<<endl;
	return 0;
}

const LauAbsResonance* LauIsobarDynamics::findResonance(const TString& name) const
{
	TString testName(name);
	testName.ToLower();
	const LauAbsResonance* theResonance(0);

	for (std::vector<LauAbsResonance*>::const_iterator iter=sigResonances_.begin(); iter!=sigResonances_.end(); ++iter) {
		theResonance = (*iter);
		if (theResonance != 0) {
			TString resString = theResonance->getResonanceName();
			resString.ToLower();
			if (resString.BeginsWith(testName, TString::kExact)) {
				return theResonance;
			}
		}
	}

	cout<<"ERROR in LauIsobarDynamics::findResonance : Couldn't find resonance \""<<name<<"\" in the model."<<endl;
	return 0;
}

void LauIsobarDynamics::removeCharge(TString& string) const
{
	Ssiz_t index = string.Index("+");
	if (index != -1) {
		string.Remove(index,1);
	}
	index = string.Index("-");
	if (index != -1) {
		string.Remove(index,1);
	}
}

void LauIsobarDynamics::changeResonance(const TString& resName, Double_t newMass, Double_t newWidth, Int_t newSpin)
{
	// Change the mass, width or spin of a resonance.

	if (newMass > 0.0 || newWidth > 0.0 || newSpin > -1) {
		cout<<"ERROR in LauIsobarDynamics::changeResonance : mass, width and spin parameters all out of range."<<endl;
		return;
	}

	LauAbsResonance* theRes = this->findResonance(resName);
	if (theRes != 0) {
		theRes->changeResonance(newMass, newWidth, newSpin);
	}

}

void LauIsobarDynamics::calcDPNormalisation()
{
	// Use Gauss-Legendre quadrature integration

	// Get the rectangle that encloses the DP
	Double_t minm13 = kinematics_->getm13Min();
	Double_t maxm13 = kinematics_->getm13Max();
	Double_t minm23 = kinematics_->getm23Min();
	Double_t maxm23 = kinematics_->getm23Max();
	Double_t minm12 = kinematics_->getm12Min();
	Double_t maxm12 = kinematics_->getm12Max();

	// Find out whether we have narrow resonances in the DP (defined here as width < 20 MeV).
	std::multimap<Double_t,Double_t> m13NarrowRes;
	std::multimap<Double_t,Double_t> m23NarrowRes;
	std::multimap<Double_t,Double_t> m12NarrowRes;
	for ( std::vector<LauAbsResonance*>::const_iterator iter = sigResonances_.begin(); iter != sigResonances_.end(); ++iter ) {
		Double_t width = (*iter)->getWidth();
		if ( width > 0.020 || width == 0.0 ) { continue; }
		Double_t mass = (*iter)->getMass();
		Int_t pair = (*iter)->getPairInt();
		TString name = (*iter)->getResonanceName();
		cout<<"Found narrow resonance: "<<name<<", mass = "<<mass<<", width = "<<width<<", pair int = "<<pair<<endl;
		if ( pair == 1 ) {
			if ( mass < minm23 || mass > maxm23 ){ continue; }
			m23NarrowRes.insert( std::make_pair(width,mass) );
		} else if ( pair == 2 ) {
			if ( mass < minm13 || mass > maxm13 ){ continue; }
			m13NarrowRes.insert( std::make_pair(width,mass) );
		} else if ( pair == 3 ) {
			if ( mass < minm12 || mass > maxm12 ){ continue; }
			m12NarrowRes.insert( std::make_pair(width,mass) );
		} else {
			cerr<<"WARNING in LauIsobarDynamics::calcDPNormalisation : strange pair integer, "<<pair<<", for resonance \""<<(*iter)->getResonanceName()<<endl;
		}
	}

	// Find the narrowest resonance in each mass pairing
	const Bool_t e12 = m12NarrowRes.empty();
	const Bool_t e13 = m13NarrowRes.empty();
	const Bool_t e23 = m23NarrowRes.empty();
	//const UInt_t s12 = e12 ? 0 : m12NarrowRes.size();
	const UInt_t s13 = e13 ? 0 : m13NarrowRes.size();
	const UInt_t s23 = e23 ? 0 : m23NarrowRes.size();
	const Double_t w12 = e12 ? DBL_MAX : m12NarrowRes.begin()->first / 100.0;
	const Double_t w13 = e13 ? DBL_MAX : m13NarrowRes.begin()->first / 100.0;
	const Double_t w23 = e23 ? DBL_MAX : m23NarrowRes.begin()->first / 100.0;

	// Start off with default bin width (5 MeV)
	Double_t m13BinWidth = m13BinWidth_;
	Double_t m23BinWidth = m23BinWidth_;

	// Depending on how many narrow resonances we have and where they
	// are we adopt different approaches
	if ( e12 && e13 && e23 ) {
		// If we have no narrow resonances just integrate the whole
		// DP with the standard bin widths
		cout<<"No narrow resonances found, integrating over whole Dalitz plot..."<<endl;
		this->calcDPPartialIntegral(minm13, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
	} else if ( ! e12 ) {
		// If we have a narrow resonance on the diagonal then we'll have to
		// just use a narrow bin width over the whole DP (1/10 of the width
		// of the narrowest resonance in any mass pair)
		m13BinWidth = m23BinWidth = 10.0*TMath::Min( w12, TMath::Min( w13, w23 ) );
		cout<<"One or more narrow resonances found in m12, integrating over whole Dalitz plot with bin width of "<<m13BinWidth<<" GeV/c2..."<<endl;
		this->calcDPPartialIntegral(minm13, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
	} else if ( s13==1 && e23 ) {
		// We have a single narrow resonance in m13
		// Divide the plot into 3 regions: the resonance band and
		// the two areas either side.
		Double_t mass = m13NarrowRes.begin()->second;
		Double_t width = m13NarrowRes.begin()->first;
		Double_t resMin = mass - 5.0*width;
		Double_t resMax = mass + 5.0*width;
		// if the resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( resMin < (minm13+50.0*m13BinWidth_) ) {
			cout<<"One narrow resonance found in m13, close to threshold, dividing Dalitz plot into two regions..."<<endl;
			this->calcDPPartialIntegral(resMax, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			this->calcDPPartialIntegral(minm13, resMax, minm23, maxm23, m13BinWidth, m23BinWidth);
		} else {
			cout<<"One narrow resonance found in m13, dividing Dalitz plot into three regions..."<<endl;
			this->calcDPPartialIntegral(minm13, resMin, minm23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			this->calcDPPartialIntegral(resMin, resMax, minm23, maxm23, m13BinWidth, m23BinWidth);
		}
	} else if ( s13==2 && e23 ) {
		// We have a two narrow resonances in m13
		// Divide the plot into 5 regions: the resonance bands,
		// the two areas either side and the area in between.
		std::multimap<Double_t,Double_t> massordered;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m13NarrowRes.begin(); iter != m13NarrowRes.end(); ++iter ) {
			massordered.insert( std::make_pair( iter->second, iter->first ) );
		}
		Double_t res1Mass = massordered.begin()->first;
		Double_t res1Width = massordered.begin()->second;
		Double_t res1Min = res1Mass - 5.0*res1Width;
		Double_t res1Max = res1Mass + 5.0*res1Width;
		Double_t res2Mass = (++(massordered.begin()))->first;
		Double_t res2Width = (++(massordered.begin()))->second;
		Double_t res2Min = res2Mass - 5.0*res2Width;
		Double_t res2Max = res2Mass + 5.0*res2Width;
		// if the resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( res1Min < (minm13+50.0*m13BinWidth_) ) {
			cout<<"Two narrow resonances found in m13, one close to threshold, dividing Dalitz plot into four regions..."<<endl;
			this->calcDPPartialIntegral(res1Max, res2Min, minm23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(res2Max, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = res1Width/100.0;
			this->calcDPPartialIntegral(minm13, res1Max, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = res2Width/100.0;
			this->calcDPPartialIntegral(res2Min, res2Max, minm23, maxm23, m13BinWidth, m23BinWidth);
		} else {
			cout<<"Two narrow resonances found in m13, dividing Dalitz plot into five regions..."<<endl;
			this->calcDPPartialIntegral(minm13, res1Min, minm23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(res1Max, res2Min, minm23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(res2Max, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = res1Width/100.0;
			this->calcDPPartialIntegral(res1Min, res1Max, minm23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = res2Width/100.0;
			this->calcDPPartialIntegral(res2Min, res2Max, minm23, maxm23, m13BinWidth, m23BinWidth);
		}
	} else if ( s23==1 && e13 ) {
		// We have a single narrow resonance in m23
		// Divide the plot into 3 regions: the resonance band and
		// the two areas either side.
		Double_t mass = m23NarrowRes.begin()->second;
		Double_t width = m23NarrowRes.begin()->first;
		Double_t resMin = mass - 5.0*width;
		Double_t resMax = mass + 5.0*width;
		// if the resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( resMin < (minm23+50.0*m23BinWidth_) ) {
			cout<<"One narrow resonance found in m23, close to threshold, dividing Dalitz plot into two regions..."<<endl;
			this->calcDPPartialIntegral(minm13, maxm13, resMax, maxm23, m13BinWidth, m23BinWidth);
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, maxm13, minm23, resMax, m13BinWidth, m23BinWidth);
		} else {
			cout<<"One narrow resonance found in m23, dividing Dalitz plot into three regions..."<<endl;
			this->calcDPPartialIntegral(minm13, maxm13, minm23, resMin, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, maxm13, resMax, maxm23, m13BinWidth, m23BinWidth);
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, maxm13, resMin, resMax, m13BinWidth, m23BinWidth);
		}
	} else if ( s23==2 && e13 ) {
		// We have a two narrow resonances in m23
		// Divide the plot into 5 regions: the resonance bands,
		// the two areas either side and the area in between.
		std::multimap<Double_t,Double_t> massordered;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m23NarrowRes.begin(); iter != m23NarrowRes.end(); ++iter ) {
			massordered.insert( std::make_pair( iter->second, iter->first ) );
		}
		Double_t res1Mass = massordered.begin()->first;
		Double_t res1Width = massordered.begin()->second;
		Double_t res1Min = res1Mass - 5.0*res1Width;
		Double_t res1Max = res1Mass + 5.0*res1Width;
		Double_t res2Mass = (++(massordered.begin()))->first;
		Double_t res2Width = (++(massordered.begin()))->second;
		Double_t res2Min = res2Mass - 5.0*res2Width;
		Double_t res2Max = res2Mass + 5.0*res2Width;
		// if the resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( res1Min < (minm23+50.0*m23BinWidth_) ) {
			cout<<"Two narrow resonances found in m23, one close to threshold, dividing Dalitz plot into four regions..."<<endl;
			this->calcDPPartialIntegral(minm13, maxm13, res1Max, res2Min, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, maxm13, res2Max, maxm23, m13BinWidth, m23BinWidth);
			m23BinWidth = res1Width/100.0;
			this->calcDPPartialIntegral(minm13, maxm13, minm23, res1Max, m13BinWidth, m23BinWidth);
			m23BinWidth = res2Width/100.0;
			this->calcDPPartialIntegral(minm13, maxm13, res2Min, res2Max, m13BinWidth, m23BinWidth);
		} else {
			cout<<"Two narrow resonances found in m23, dividing Dalitz plot into five regions..."<<endl;
			this->calcDPPartialIntegral(minm13, maxm13, minm23, res1Min, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, maxm13, res1Max, res2Min, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, maxm13, res2Max, maxm23, m13BinWidth, m23BinWidth);
			m23BinWidth = res1Width/100.0;
			this->calcDPPartialIntegral(minm13, maxm13, res1Min, res1Max, m13BinWidth, m23BinWidth);
			m23BinWidth = res2Width/100.0;
			this->calcDPPartialIntegral(minm13, maxm13, res2Min, res2Max, m13BinWidth, m23BinWidth);
		}
	} else if ( s13==1 && s23==1 ) {
		// We have a single narrow resonance in both m13 and m23
		// Divide the plot into 9 regions: the point where the
		// resonance bands cross, the four other parts of the bands
		// and the four remaining areas of the DP.
		Double_t mass23 = m23NarrowRes.begin()->second;
		Double_t width23 = m23NarrowRes.begin()->first;
		Double_t resMin23 = mass23 - 5.0*width23;
		Double_t resMax23 = mass23 + 5.0*width23;
		Double_t mass13 = m13NarrowRes.begin()->second;
		Double_t width13 = m13NarrowRes.begin()->first;
		Double_t resMin13 = mass13 - 5.0*width13;
		Double_t resMax13 = mass13 + 5.0*width13;
		// if either resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( resMin13 < (minm13+50.0*m13BinWidth_) && resMin23 < (minm23+50.0*m23BinWidth_) ) {
			cout<<"One narrow resonance found in m13 and one in m23, both close to threshold, dividing Dalitz plot into four regions..."<<endl;
			m13BinWidth = m13BinWidth_;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
		} else if ( resMin13 < (minm13+50.0*m13BinWidth_) ) {
			cout<<"One narrow resonance found in m13, close to threshold, and one in m23, not close to threshold, dividing Dalitz plot into six regions..."<<endl;
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMax13, maxm13, resMin23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMax13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMax13, resMin23, resMax23, m13BinWidth, m23BinWidth);
		} else if ( resMin23 < (minm23+50.0*m23BinWidth_) ) {
			cout<<"One narrow resonance found in m23, close to threshold, and one in m13, not close to threshold, dividing Dalitz plot into six regions..."<<endl;
			this->calcDPPartialIntegral(minm13, resMin13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMin13, minm23, resMax23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMin13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMin13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
		} else {
			cout<<"One narrow resonance found in both m13 and m23, neither close to threshold, dividing Dalitz plot into nine regions..."<<endl;
			this->calcDPPartialIntegral(minm13, resMin13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, resMin13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMin13, resMin23, resMax23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMin23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMin13, resMax13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMin13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMin13, resMax13, resMin23, resMax23, m13BinWidth, m23BinWidth);
		}
	} else if ( e23 && s13>1 ) {
		// We have multiple narrow resonances in m13 only.
		// Divide the plot into 2 regions: threshold to the most
		// massive of the narrow resonances, and the rest
		cout<<"Multiple narrow resonances found in m13, dividing Dalitz plot into two regions..."<<endl;
		Double_t mass = 0.0;
		Double_t width = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m13NarrowRes.begin(); iter != m13NarrowRes.end(); ++iter ) {
			if ( mass < iter->second ) {
				mass = iter->second;
				width = iter->first;
			}
		}
		Double_t resMax = mass + 5.0*width;
		this->calcDPPartialIntegral(resMax, maxm13, minm23, maxm23, m13BinWidth, m23BinWidth);
		m13BinWidth = w13;
		this->calcDPPartialIntegral(minm13, resMax, minm23, maxm23, m13BinWidth, m23BinWidth);
	} else if ( e13 && s23>1 ) {
		// We have multiple narrow resonances in m23 only.
		// Divide the plot into 2 regions: threshold to the most
		// massive of the narrow resonances, and the rest
		cout<<"Multiple narrow resonances found in m23, dividing Dalitz plot into two regions..."<<endl;
		Double_t mass = 0.0;
		Double_t width = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m23NarrowRes.begin(); iter != m23NarrowRes.end(); ++iter ) {
			if ( mass < iter->second ) {
				mass = iter->second;
				width = iter->first;
			}
		}
		Double_t resMax = mass + 5.0*width;
		this->calcDPPartialIntegral(minm13, maxm13, resMax, maxm23, m13BinWidth, m23BinWidth);
		m23BinWidth = w23;
		this->calcDPPartialIntegral(minm13, maxm13, minm23, resMax, m13BinWidth, m23BinWidth);
	} else if ( s13==1 && s23>1 ) {
		// We've got a single narrow resonance in m13 and multiple
		// narrow resonances in m23.  Divide the plot into 6 regions.
		Double_t mass23 = 0.0;
		Double_t width23 = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m23NarrowRes.begin(); iter != m23NarrowRes.end(); ++iter ) {
			if ( mass23 < iter->second ) {
				mass23 = iter->second;
				width23 = iter->first;
			}
		}
		Double_t resMax23 = mass23 + 5.0*width23;
		Double_t mass13 = m13NarrowRes.begin()->second;
		Double_t width13 = m13NarrowRes.begin()->first;
		Double_t resMin13 = mass13 - 5.0*width13;
		Double_t resMax13 = mass13 + 5.0*width13;
		// if the m13 resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( resMin13 < (minm13+50.0*m13BinWidth_) ) {
			cout<<"Multiple narrow resonances found in m23 and one in m13, close to threshold, dividing Dalitz plot into four regions..."<<endl;
			m13BinWidth = m13BinWidth_;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
		} else {
			cout<<"Multiple narrow resonances found in m23 and one in m13, not close to threshold, dividing Dalitz plot into six regions..."<<endl;
			m13BinWidth = m13BinWidth_;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMin13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMin13, minm23, resMax23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMin13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMin13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
		}
	} else if ( s13>1 && s23==1 ) {
		// We've got a single narrow resonance in m23 and multiple
		// narrow resonances in m13.  Divide the plot into 6 regions.
		Double_t mass13 = 0.0;
		Double_t width13 = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m13NarrowRes.begin(); iter != m13NarrowRes.end(); ++iter ) {
			if ( mass13 < iter->second ) {
				mass13 = iter->second;
				width13 = iter->first;
			}
		}
		Double_t resMax13 = mass13 + 5.0*width13;
		Double_t mass23 = m23NarrowRes.begin()->second;
		Double_t width23 = m23NarrowRes.begin()->first;
		Double_t resMin23 = mass23 - 5.0*width23;
		Double_t resMax23 = mass23 + 5.0*width23;
		// if the m23 resonance is close to threshold just go from
		// threshold to resMax, otherwise treat threshold to resMin
		// as a separate region
		if ( resMin23 < (minm23+50.0*m23BinWidth_) ) {
			cout<<"Multiple narrow resonances found in m13 and one in m23, close to threshold, dividing Dalitz plot into four regions..."<<endl;
			m13BinWidth = m13BinWidth_;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
		} else {
			cout<<"Multiple narrow resonances found in m13 and one in m23, not close to threshold, dividing Dalitz plot into six regions..."<<endl;
			this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = m13BinWidth_;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(resMax13, maxm13, resMin23, resMax23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = m23BinWidth_;
			this->calcDPPartialIntegral(minm13, resMax13, minm23, resMin23, m13BinWidth, m23BinWidth);
			this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
			m13BinWidth = w13;
			m23BinWidth = w23;
			this->calcDPPartialIntegral(minm13, resMax13, resMin23, resMax23, m13BinWidth, m23BinWidth);
		}
	} else {
		// We've got multiple narrow resonances in both m13 and m23.
		// Divide the plot into 4 regions.
		cout<<"Multiple narrow resonances found in both m13 and m23, dividing Dalitz plot into four regions..."<<endl;
		Double_t mass13 = 0.0;
		Double_t width13 = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m13NarrowRes.begin(); iter != m13NarrowRes.end(); ++iter ) {
			if ( mass13 < iter->second ) {
				mass13 = iter->second;
				width13 = iter->first;
			}
		}
		Double_t resMax13 = mass13 + 5.0*width13;

		Double_t mass23 = 0.0;
		Double_t width23 = 0.0;
		for ( std::map<Double_t,Double_t>::const_iterator iter = m23NarrowRes.begin(); iter != m23NarrowRes.end(); ++iter ) {
			if ( mass23 < iter->second ) {
				mass23 = iter->second;
				width23 = iter->first;
			}
		}
		Double_t resMax23 = mass23 + 5.0*width23;

		m13BinWidth = m13BinWidth_;
		m23BinWidth = m23BinWidth_;
		this->calcDPPartialIntegral(resMax13, maxm13, resMax23, maxm23, m13BinWidth, m23BinWidth);
		m13BinWidth = m13BinWidth_;
		m23BinWidth = w23;
		this->calcDPPartialIntegral(resMax13, maxm13, minm23, resMax23, m13BinWidth, m23BinWidth);
		m13BinWidth = w13;
		m23BinWidth = m23BinWidth_;
		this->calcDPPartialIntegral(minm13, resMax13, resMax23, maxm23, m13BinWidth, m23BinWidth);
		m13BinWidth = w13;
		m23BinWidth = w23;
		this->calcDPPartialIntegral(minm13, resMax13, minm23, resMax23, m13BinWidth, m23BinWidth);
	}
}

void LauIsobarDynamics::setIntegralBinWidths(Double_t m13BinWidth, Double_t m23BinWidth)
{
	// Specify whether we're going to use Gauss-Legendre integration to calculate the normalisation
	// integrals, and the bin widths we require for the m13 and m23 axes. Note that the integration
	// is done over m13, m23 space, with the appropriate Jacobian applied, and not m13^2, m23^2 space.
	// The default bin widths in m13 and m23 space are 5 MeV.

	m13BinWidth_ = m13BinWidth;
	m23BinWidth_ = m23BinWidth;
}

void LauIsobarDynamics::calcDPPartialIntegral(Double_t minm13, Double_t maxm13, Double_t minm23, Double_t maxm23, 
		Double_t m13BinWidth, Double_t m23BinWidth)
{
	// Calculate the total DP area, as well as finding the normalisation terms for
	// the signal resonances

	Int_t i(0), j(0);
	Double_t precision(1e-6);

	Double_t meanm13 = 0.5*(minm13 + maxm13);
	Double_t rangem13 = maxm13 - minm13;
	Double_t halfRangem13 = 0.5*rangem13;

	Double_t meanm23 = 0.5*(minm23 + maxm23);
	Double_t rangem23 = maxm23 - minm23;
	Double_t halfRangem23 = 0.5*rangem23;

	Double_t intFactor = halfRangem13*halfRangem23;

	// Choose smallest of mass ranges to set number of bins, given specified bin width
	Int_t nm13Points = static_cast<Int_t>((rangem13/m13BinWidth));
	Int_t nm23Points = static_cast<Int_t>((rangem23/m23BinWidth));

	// Avoid integral if we have no points in either x or y space
	if (nm13Points == 0 || nm23Points == 0) {return;}

	cout<<"nm13Points = "<<nm13Points<<", nm23Points = "<<nm23Points<<endl;
	cout<<"m13BinWidth = "<<m13BinWidth<<", m23BinWidth = "<<m23BinWidth<<endl;
	cout<<"Integrating over m13 = "<<minm13<<" to "<<maxm13<<", m23 = "<<minm23<<" to "<<maxm23<<endl;

	LauIntegrals DPIntegrals(precision);
	std::vector<Double_t> m13Weights, m23Weights;
	std::vector<Double_t> m13Abscissas, m23Abscissas;

	DPIntegrals.calcGaussLegendreWeights(nm13Points, m13Abscissas, m13Weights);
	DPIntegrals.calcGaussLegendreWeights(nm23Points, m23Abscissas, m23Weights);

	Int_t nm13Weights = static_cast<Int_t>(m13Weights.size());
	Int_t nm23Weights = static_cast<Int_t>(m23Weights.size());

	//cout<<"nm13Weights = "<<nm13Weights<<", nm23Weights = "<<nm23Weights<<endl;
	// Print out abscissas and weights for the integration
	Double_t totm13Weight(0.0), totm23Weight(0.0);
	for (i = 0; i < nm13Weights; i++) {
		totm13Weight += m13Weights[i];
	}
	for (i = 0; i < nm23Weights; i++) {
		totm23Weight += m23Weights[i];
	}
	cout<<"totm13Weight = "<<totm13Weight<<", totm23Weight = "<<totm23Weight<<endl;

	std::vector<Double_t> m13(nm13Weights), m23(nm23Weights);
	std::vector<Double_t> m13Sq(nm13Weights), m23Sq(nm23Weights);

	// Use same number of abscissas for x and y co-ordinates
	Int_t m = (nm13Weights + 1)/2;
	for (i = 0; i < m; i++) {

		Int_t ii = nm13Weights - 1 - i; // symmetric i index

		Double_t dm13 = halfRangem13*m13Abscissas[i];
		Double_t m13Val = meanm13 - dm13;
		m13[i] = m13Val;
		m13Sq[i] = m13Val*m13Val;

		m13Val = meanm13 + dm13;
		m13[ii] = m13Val;
		m13Sq[ii] = m13Val*m13Val;

	}

	m = (nm23Weights +1)/2;
	for (i = 0; i < m; i++) {

		Int_t ii = nm23Weights - 1 - i; // symmetric i index

		Double_t dm23 = halfRangem23*m23Abscissas[i];
		Double_t m23Val = meanm23 - dm23;
		m23[i] = m23Val;
		m23Sq[i] = m23Val*m23Val;
		m23Val = meanm23 + dm23;
		m23[ii] = m23Val;
		m23Sq[ii] = m23Val*m23Val;
	}

	// Now compute the integral
	Double_t dpArea(0.0);
	for (i = 0; i < nm13Weights; i++) {

		for (j = 0; j < nm23Weights; j++) {

			Double_t weight = m13Weights[i]*m23Weights[j];
			Double_t Jacobian = 4.0*m13[i]*m23[j];
			weight *= (Jacobian*intFactor);

			// Calculate the integral contributions for each resonance.
			// Only resonances within the DP area contribute.
			// This also calculates the total DP area as a check.
			Bool_t withinDP = kinematics_->withinDPLimits(m13Sq[i], m23Sq[j]);
			if (withinDP == kTRUE) {

				kinematics_->updateKinematics(m13Sq[i], m23Sq[j]);
				this->dynamics(kFALSE, weight);
				// Increment total DP area
				dpArea += weight;

			}

		} // j weights loop
	} // i weights loop

	// Print out DP area to check whether we have a sensible output
	cout<<"dpArea = "<<dpArea<<endl;

}

void LauIsobarDynamics::dynamics(Bool_t cacheResData, Double_t weight, Bool_t useEff)
{
	// Routine that calculates the Dalitz plot amplitude, incorporating
	// resonance dynamics (using resAmp()) and any interference between them.
	// Used by the fit() and sigGen() functions.

	UInt_t i(0), j(0);

	// Reset the total amplitude to zero
	totAmp_.zero();

	// Loop over the number of resonance amplitudes defined in the model
	// Have we already calculated this for this event (during fit?)
	// Or do we have a resonance that has varying pole mass/width/other factors?
	if (cacheResData == kFALSE) {

		for (i = 0; i < nAmp_; i++) {

			// Calculate the dynamics for this resonance, using the resAmp function.
			ff_[i] = resAmp(i);

			//cout<<"ff_["<<i<<"] = "<<ff_[i]<<endl;

			// If we have a symmetrical Dalitz plot, flip the m_13^2 and m_23^2
			// variables, recalculate the dynamics, and average both contributions.
			// Although, the factor of 0.5 cancels out with the fact that
			// the resonance appears on both sides of the Dalitz plot.
			if (symmetricalDP_ == kTRUE) { // was tieSg_ == 12
				kinematics_->flipAndUpdateKinematics();
				ff_[i] += resAmp(i);
				// Flip the m_13^2 and m_23^2 variables back to their original values
				kinematics_->flipAndUpdateKinematics();
			}

		} // Loop over amplitudes

		// If we haven't cached the data, then we need to find out the efficiency.
		eff_ = this->retrieveEfficiency();

	} // Already cached data?

	if (integralsDone_ == kTRUE) {

		// Loop over all signal amplitudes
		LauComplex ATerm;
		for (i = 0; i < nAmp_; i++) {  

			// Get the partial complex amplitude - (mag, phase)*(resonance dynamics)
			ATerm = Amp_[i]*ff_[i];
			// Scale this contribution by its relative normalisation w.r.t. the whole dynamics
			ATerm.rescale(fNorm_[i]);

			// Add this partial amplitude to the sum
			//cout<<"For i = "<<i<<", ATerm = "<<ATerm<<", Amp = "<<Amp_[i]<<", ff = "<<ff_[i]<<endl;
			totAmp_ += ATerm;

		} // Loop over amplitudes

		// |Sum of partial amplitudes|^2
		ASq_ = totAmp_.abs2();

		// Apply the efficiency correction for this event.
		// Multiply the amplitude squared sum by the DP efficiency
		if ( useEff ) {
			ASq_ *= eff_;
		}

	} else {  // integrals not done

		// Find the efficiency correction to be applied for this event.
		eff_ = this->retrieveEfficiency();

		Double_t effWeight = eff_*weight;

		// Need this for integrals for normalisation of likelihood function.
		LauComplex fifjEffSumTerm;
		LauComplex fifjSumTerm;
		for (i = 0; i < nAmp_; i++) {

			// Add the dynamical amplitude squared for this resonance.
			Double_t fSqVal = ff_[i].abs2();
			fSqSum_[i] += fSqVal*weight;

			for (j = i; j < nAmp_; j++) {

				fifjEffSumTerm = fifjSumTerm = ff_[i]*ff_[j].conj();

				fifjEffSumTerm.rescale(effWeight);
				fifjEffSum_[i][j] += fifjEffSumTerm;

				fifjSumTerm.rescale(weight);
				fifjSum_[i][j] += fifjSumTerm;
			}
		}
	}
}

LauComplex LauIsobarDynamics::resAmp(Int_t index) 
{  
	// Routine to calculate the resonance dynamics (amplitude) 
	// using the appropriate Breit-Wigner/Form Factors. 
	// Called by the dynamics() function.

	// Get the signal resonance from the stored vector
	LauAbsResonance* sigResonance = sigResonances_[index];

	if (sigResonance == 0) {
		cout<<"Error in resAmp. Couldn't retrieve resonance with index = "<<index<<endl;
		return LauComplex(0.0, 0.0);
	}

	// Get the integer index of the resonance.
	Int_t resInt = resIntAmp_[index];  

	LauComplex resAmplitude(0.0, 0.0);

	// Fortran code has this set to 0 -> set NR index to -1
	if (resInt == -1) {

		// Non-resonant
		resAmplitude = LauComplex(0.3, 0.0);

	} else if (resInt < -1 || resInt >= static_cast<Int_t>(this->getnDefinedResonances())) {

		cout<<"Error in resAmp. Probably bad resonance name."<<endl;
		resAmplitude = LauComplex(0.0, 0.0);

	} else {

		resAmplitude = sigResonance->amplitude(kinematics_);

	}

	return resAmplitude;
}

void LauIsobarDynamics::setFFTerm(UInt_t index, Double_t realPart, Double_t imagPart) 
{  
	// Function to set the internal ff = resAmp() term.  
	if ( index >= nAmp_ ) {
		cout<<"Warning in setFFTerm. index = "<<index<<" is not within the range 0 and "
			<<nAmp_-1<<". Bailing out."<<endl;
		return;
	}

	ff_[index].setRealImagPart( realPart, imagPart );

}

void LauIsobarDynamics::calcExtraInfo(Bool_t init)
{
	// This method calculates the fit fractions, mean efficiency and total DP rate

	Double_t fifjEffTot(0.0), fifjTot(0.0);
	UInt_t i, j;
	for (i = 0; i < nAmp_; i++) {

		// Calculate the diagonal terms
		TString name = "A"; name += i; name += "Sq_FitFrac";
		fitFrac_[i][i].name(name);

		Double_t fifjSumReal = fifjSum_[i][i].re();
		Double_t sumTerm = Amp_[i].abs2()*fifjSumReal*fNorm_[i]*fNorm_[i];
		fifjTot += sumTerm;

		Double_t fifjEffSumReal = fifjEffSum_[i][i].re();
		Double_t sumEffTerm = Amp_[i].abs2()*fifjEffSumReal*fNorm_[i]*fNorm_[i];
		fifjEffTot += sumEffTerm;

		fitFrac_[i][i] = sumTerm;
	}

	for (i = 0; i < nAmp_; i++) {
		for (j = i+1; j < nAmp_; j++) {
			// Calculate the cross-terms
			TString name = "A"; name += i; name += "A"; name += j; name += "_FitFrac";
			fitFrac_[i][j].name(name);

			LauComplex AmpjConj = Amp_[j].conj();
			LauComplex AmpTerm = Amp_[i]*AmpjConj;

			Double_t crossTerm = 2.0*(AmpTerm*fifjSum_[i][j]).re()*fNorm_[i]*fNorm_[j];
			fifjTot += crossTerm;

			Double_t crossEffTerm = 2.0*(AmpTerm*fifjEffSum_[i][j]).re()*fNorm_[i]*fNorm_[j];
			fifjEffTot += crossEffTerm;

			fitFrac_[i][j] = crossTerm;
		}
	}

	if (TMath::Abs(fifjTot) > 1e-10) {
		meanDPEff_ = fifjEffTot/fifjTot;
		if (init) {
			meanDPEff_.genValue( meanDPEff_.value() );
			meanDPEff_.initValue( meanDPEff_.value() );
		}
	}
	DPRate_ = fifjTot;
	if (init) {
		DPRate_.genValue( DPRate_.value() );
		DPRate_.initValue( DPRate_.value() );
	}

	// Now divide the fitFraction sums by the overall integral
	for (i = 0; i < nAmp_; i++) {
		for (j = i; j < nAmp_; j++) {
			// Get the actual fractions by dividing by the total DP rate
			fitFrac_[i][j] /= fifjTot;
			if (init) {
				fitFrac_[i][j].genValue( fitFrac_[i][j].value() );
				fitFrac_[i][j].initValue( fitFrac_[i][j].value() );
			}
		}
	}

	// Work out total fit fraction over all K-matrix components (for each propagator)
	KMPropMap::iterator mapIter;
	Int_t propInt(0);

	for (mapIter = kMatrixPropagators_.begin(); mapIter != kMatrixPropagators_.end(); ++mapIter) {

	        LauKMatrixPropagator* thePropagator = mapIter->second;

		TString propName = thePropagator->getName();

		// Now loop over all resonances and find those which are K-matrix components for this propagator
		Double_t kMatrixTotFitFrac(0.0);

		for (i = 0; i < nAmp_; i++) {
	    
		        Bool_t gotKMRes1 = this->gotKMatrixMatch(i, propName);
			if (gotKMRes1 == kFALSE) {continue;}

			Double_t fifjSumReal = fifjSum_[i][i].re();
			Double_t sumTerm = Amp_[i].abs2()*fifjSumReal*fNorm_[i]*fNorm_[i];

			//Double_t fifjEffSumReal = fifjEffSum_[i][i].re();
			//Double_t sumEffTerm = Amp_[i].abs2()*fifjEffSumReal*fNorm_[i]*fNorm_[i];

			kMatrixTotFitFrac += sumTerm;
			
			for (j = i+1; j < nAmp_; j++) {

			        Bool_t gotKMRes2 = this->gotKMatrixMatch(j, propName);
				if (gotKMRes2 == kFALSE) {continue;}

				LauComplex AmpjConj = Amp_[j].conj();
				LauComplex AmpTerm = Amp_[i]*AmpjConj;

				Double_t crossTerm = 2.0*(AmpTerm*fifjSum_[i][j]).re()*fNorm_[i]*fNorm_[j];
				//Double_t crossEffTerm = 2.0*(AmpTerm*fifjEffSum_[i][j]).re()*fNorm_[i]*fNorm_[j];

				kMatrixTotFitFrac += crossTerm;	      
				
			}
			
		}
	  
		kMatrixTotFitFrac /= fifjTot;

		TString parName("KMatrixTotFF_"); parName += propInt;
		extraParameters_[propInt].name( parName );
		extraParameters_[propInt] =  kMatrixTotFitFrac;
		if (init) {
		        extraParameters_[propInt].genValue(kMatrixTotFitFrac);
		        extraParameters_[propInt].initValue(kMatrixTotFitFrac);
		}

		cout<<"Total K-matrix fit fraction for propagator "<<propName<<" is "<<kMatrixTotFitFrac<<endl;
		
		++propInt;

	}
	

}

Bool_t LauIsobarDynamics::gotKMatrixMatch(UInt_t resAmpInt, const TString& propName) const
{

        Bool_t gotMatch(kFALSE);
  	    
	if (resAmpInt >= nAmp_) {return kFALSE;}

	const LauAbsResonance* theResonance = sigResonances_[resAmpInt];
	    
	if (theResonance == 0) {return kFALSE;}

	Int_t resModelInt = theResonance->getResonanceModel();

	if (resModelInt == LauAbsResonance::KMatrix) {
    
                TString resName = theResonance->getResonanceName();
    
		KMStringMap::const_iterator kMPropSetIter = kMatrixPropSet_.find(resName);

		if (kMPropSetIter != kMatrixPropSet_.end()) {
                        TString kmPropString = kMPropSetIter->second;
			if (kmPropString == propName) {gotMatch = kTRUE;}
		}
		
	}

	return gotMatch;

}

Double_t LauIsobarDynamics::calcSigDPNorm()
{
	// Calculate the normalisation for the log-likelihood function.
	DPNorm_ = 0.0;

	for (UInt_t i = 0; i < nAmp_; i++) {
		// fifjEffSum is the contribution from the term involving the resonance
		// dynamics (f_i for resonance i) and the efficiency term.
		Double_t fifjEffSumReal = fifjEffSum_[i][i].re();
		// We need to normalise this contribution w.r.t. the complete dynamics in the DP.
		// Hence we scale by the fNorm_i factor (squared), which is calculated by the
		// initialise() function, when the normalisation integrals are calculated and cached. 
		// We also include the complex amplitude squared to get the total normalisation
		// contribution from this resonance.
		DPNorm_ += Amp_[i].abs2()*fifjEffSumReal*fNorm_[i]*fNorm_[i];
	}

	// We now come to the cross-terms (between resonances i and j) in the normalisation.
	for (UInt_t i = 0; i < nAmp_; i++) {
		for (UInt_t j = i+1; j < nAmp_; j++) {
			LauComplex AmpjConj = Amp_[j].conj();
			LauComplex AmpTerm = Amp_[i]*AmpjConj;
			// Again, fifjEffSum is the contribution from the term involving the resonance
			// dynamics (f_i*f_j_conjugate) and the efficiency cross term.
			// Also include the relative normalisation between these two resonances w.r.t. the
			// total DP dynamical structure (fNorm_i and fNorm_j) and the complex
			// amplitude squared (mag,phase) part.
			DPNorm_ += 2.0*(AmpTerm*fifjEffSum_[i][j]).re()*fNorm_[i]*fNorm_[j];
		}
	}

	return DPNorm_;
}

Bool_t LauIsobarDynamics::generate()
{
	// Routine to generate a signal event according to the Dalitz plot
	// model we have defined.

	nSigGenLoop_ = 0;
	Bool_t generatedSig(kFALSE);

	while (generatedSig == kFALSE && nSigGenLoop_ < iterationsMax_) {

		// Generates uniform DP phase-space distribution
		Double_t m13Sq(0.0), m23Sq(0.0);
		kinematics_->genFlatPhaseSpace(m13Sq, m23Sq);	

		// If we're in a symmetrical DP then we should only generate events in one half
		if ( symmetricalDP_ && m13Sq > m23Sq ) {
			Double_t tmpSq = m13Sq;
			m13Sq = m23Sq;
			m23Sq = tmpSq;
		}

		// calculates the amplitudes and total amplitude for the given DP point
		this->calcLikelihoodInfo(m13Sq, m23Sq);

		if (integralsDone_ == kTRUE) {

			// No need for efficiency correction here. It is already done in 
			// the dynamics() function (unlike the Fortran version).

			// Very important line to avoid bias in MC generation for the accept/reject method.
			// Make sure that the total amplitude squared is below some number, given
			// by aSqMaxSet_. If it is, then the event is valid.
			// Otherwise, go through another toy MC loop until we can generate the event
			// OK, or until we reach the maximum iteration limit.

			Double_t randNo = LauRandom::randomFun()->Rndm();

			if (randNo > ASq_/aSqMaxSet_) {
				nSigGenLoop_++;
			} else {
				generatedSig = kTRUE;
				nSigGenLoop_ = 0;
				if (ASq_ > aSqMaxVar_) {aSqMaxVar_ = ASq_;}
			}

		} else {
			// For toy MC numerical integration only
			generatedSig = kTRUE;
		}
	} // while loop

	Bool_t sigGenOK(kTRUE);
	if (GenOK != this->checkToyMC(kFALSE,kFALSE)) {
		sigGenOK = kFALSE;
	}

	return sigGenOK;
}

LauAbsDPDynamics::ToyMCStatus LauIsobarDynamics::checkToyMC(Bool_t printErrorMessages, Bool_t printInfoMessages)
{
	// Check whether we have generated the toy MC OK.
	ToyMCStatus ok(GenOK);

	if (nSigGenLoop_ >= iterationsMax_) {
		if (printErrorMessages) {
			cerr<<"Error in sigGen. More than "<<iterationsMax_<<" iterations required."<<endl;
			cerr<<"Try to decrease the maximum allowed value of the total amplitude squared using the "
				<<"LauIsobarDynamics::setASqMaxValue(Double_t) function and re-run."<<endl;
			cerr<<"This needs to be, perhaps significantly, less than "<<aSqMaxSet_<<endl;
			cerr<<"Maximum value of ASq so far = "<<aSqMaxVar_<<endl;
		}
		aSqMaxSet_ = 1.01 * aSqMaxVar_;
                cout<<"|A|^2 max reset to "<<aSqMaxSet_<<endl;
		ok = MaxIterError;
	} else if (aSqMaxVar_ > aSqMaxSet_) {
		if (printErrorMessages) {
			cerr<<"Warning in LauIsobarDynamics::checkToyMC : aSqMaxSet_ was set to "<<aSqMaxSet_<<" but actual aSqMax was "<<aSqMaxVar_<<endl;
			cerr<<"Run was invalid, as any generated MC will be biased, according to the accept/reject method!"<<endl;
			cerr<<"Please set aSqMaxSet >= "<<aSqMaxVar_<<" using the LauIsobarDynamics::setASqMaxValue(Double_t) function and re-run."<<endl;
		}
		aSqMaxSet_ = 1.01 * aSqMaxVar_;
                cout<<"|A|^2 max reset to "<<aSqMaxSet_<<endl;
		ok = ASqMaxError;
	} else if (printInfoMessages) {
		cout<<"aSqMaxSet = "<<aSqMaxSet_<<" and aSqMaxVar = "<<aSqMaxVar_<<endl;
	}

	return ok;
}

void LauIsobarDynamics::setDataEventNo(UInt_t iEvt)
{
	this->LauAbsDPDynamics::setDataEventNo(iEvt);
	m13Sq_ = currentEvent_->retrievem13Sq();
	m23Sq_ = currentEvent_->retrievem23Sq();
	mPrime_ = currentEvent_->retrievemPrime();
	thPrime_ = currentEvent_->retrievethPrime();
	eff_ = currentEvent_->retrieveEff();
	scfFraction_ = currentEvent_->retrieveScfFraction();	// These two are necessary, even though the dynamics don't actually use scfFraction_ or jacobian_,
	jacobian_ = currentEvent_->retrieveJacobian();		// since this is at the heart of the caching mechanism.
}

void LauIsobarDynamics::calcLikelihoodInfo(UInt_t iEvt)
{
	// Calculate the likelihood and associated info
	// for the given event using cached information
	evtLike_ = 0.0;

	// retrieve the cached dynamics from the tree:
	// realAmp, imagAmp for each resonance plus efficiency, scf fraction and jacobian
	this->setDataEventNo(iEvt);

	// use realAmp and imagAmp to create the resonance amplitudes
	for (UInt_t i = 0; i < nAmp_; i++) {
		this->setFFTerm(i, currentEvent_->retrieveRealAmp()[i], currentEvent_->retrieveImagAmp()[i]);
	}

	// Update the dynamics - calculates totAmp_ and then ASq_ = totAmp_.abs2() * eff_
	// All calculated using cached information on the individual amplitudes and efficiency.
	this->dynamics(kTRUE, 1.0);  

	// Calculate the normalised matrix element squared value
	if (DPNorm_ > 1e-10) {
		evtLike_ = ASq_/DPNorm_;
	}
}

void LauIsobarDynamics::calcLikelihoodInfo(Double_t m13Sq, Double_t m23Sq)
{
	this->calcLikelihoodInfo(m13Sq, m23Sq, -1);
}

void LauIsobarDynamics::calcLikelihoodInfo(Double_t m13Sq, Double_t m23Sq, Int_t tagCat)
{
	// Calculate the likelihood and associated info
	// for the given point in the Dalitz plot
	// Also retrieves the SCF fraction in the bin where the event lies (done
	// here to cache it along with the the rest of the DP quantities, like eff)
	// The jacobian for the square DP is calculated here for the same reason.
	evtLike_ = 0.0;

	// update the kinematics for the specified DP point
	kinematics_->updateKinematics(m13Sq, m23Sq);

	// calculate the jacobian and the scfFraction to cache them later
	scfFraction_ = this->retrieveScfFraction(tagCat);
	if (kinematics_->squareDP() == kTRUE) {
		// If cacheResData == kFALSE, updateKinematics has been called before dynamics(). Then get Jacobian.
		jacobian_ = kinematics_->calcSqDPJacobian();
	}

	// calculates the ff_ terms and retrieves eff_ from the efficiency model
	// then calculates totAmp_ and finally ASq_ = totAmp_.abs2() * eff_
	this->dynamics(kFALSE, 1.0);

	// Calculate the normalised matrix element squared value
	if (DPNorm_ > 1e-10) {
		evtLike_ = ASq_/DPNorm_;
	}
}

void LauIsobarDynamics::fillDataTree(const LauFitDataTree& inputFitTree) 
{
	// In LauFitDataTree, the first two variables should always be m13^2 and m23^2.
	// Other variables follow thus: charge/flavour tag prob, etc.

	UInt_t nBranches = inputFitTree.nBranches();

	if (nBranches < 2) {
		cout<<"Error in LauIsobarDynamics::fillDataTree. Expecting at least 2 variables "
			<<"in input data tree, but there are "<<nBranches<<"! Make sure you have "
			<<"the right number of variables in your input data file!"<<endl;
		gSystem->Exit(-1);
	}

	// Data structure that will cache the variables required to 
	// calculate the signal likelihood for this experiment
	for ( std::vector<LauCacheData*>::iterator iter = data_.begin(); iter != data_.end(); ++iter ) {
		delete (*iter);
	}
	data_.clear();

	Double_t m13Sq(0.0), m23Sq(0.0);
	Double_t mPrime(0.0), thPrime(0.0);
	Int_t tagCat(-1);
	std::vector<Double_t> realAmp(nAmp_), imagAmp(nAmp_);
	Double_t eff(0.0), scfFraction(0.0), jacobian(0.0);

	UInt_t nEvents = inputFitTree.nEvents() + inputFitTree.nFakeEvents();

	data_.reserve(nEvents);

	for (UInt_t iEvt = 0; iEvt < nEvents; iEvt++) {

		const LauFitData& dataValues = inputFitTree.getData(iEvt);
		LauFitData::const_iterator iter = dataValues.find("m13Sq");
		m13Sq = iter->second;
		iter = dataValues.find("m23Sq");
		m23Sq = iter->second;

		// is there more than one tagging category?
		// if so then we need to know the category from the data
		if (scfFractionModel_.size()>1) {
			iter = dataValues.find("tagCat");
			tagCat = static_cast<Int_t>(iter->second);
		}

		// calculates the amplitudes and total amplitude for the given DP point
		// tagging category not needed by dynamics, but to find out the scfFraction
		this->calcLikelihoodInfo(m13Sq, m23Sq, tagCat);

		// extract the real and imaginary parts of the ff_ terms for storage
		for (UInt_t i = 0; i < nAmp_; i++) {
			realAmp[i] = ff_[i].re();
			imagAmp[i] = ff_[i].im();
		}

		if ( kinematics_->squareDP() ) {
			mPrime = kinematics_->getmPrime();
			thPrime = kinematics_->getThetaPrime();
		}

		eff = this->getEvtEff();
		scfFraction = this->getEvtScfFraction();
		jacobian = this->getEvtJacobian();

		// store the data for each event in the list
		data_.push_back( new LauCacheData() );
		data_[iEvt]->storem13Sq(m13Sq);
		data_[iEvt]->storem23Sq(m23Sq);
		data_[iEvt]->storemPrime(mPrime);
		data_[iEvt]->storethPrime(thPrime);
		data_[iEvt]->storeEff(eff);
		data_[iEvt]->storeScfFraction(scfFraction);
		data_[iEvt]->storeJacobian(jacobian);
		data_[iEvt]->storeRealAmp(realAmp);
		data_[iEvt]->storeImagAmp(imagAmp);
	}
}

Bool_t LauIsobarDynamics::gotReweightedEvent()
{
        // Select the event (kinematics_) using an accept/reject method based on the
        // ratio of the current value of ASq to the maximal value.
        Bool_t accepted(kFALSE);

	this->dynamics(kFALSE, 1.0, kFALSE);

	// Compare the ASq value with the maximal value (set by the user)
	if (LauRandom::randomFun()->Rndm() < ASq_/aSqMaxSet_) {
	        accepted = kTRUE;
	}

	if (ASq_ > aSqMaxVar_) {aSqMaxVar_ = ASq_;}

	return accepted;
}

Double_t LauIsobarDynamics::getEventWeight()
{
	// calculate the dynamics from the current kinematics
	this->dynamics(kFALSE, 1.0, kFALSE);

	if (ASq_ > aSqMaxVar_) {aSqMaxVar_ = ASq_;}

	// return the event weight = the value of the squared amplitude divided
	// by the user-defined ceiling
	return ASq_ / aSqMaxSet_;
}

