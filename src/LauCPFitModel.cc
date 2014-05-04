
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauCPFitModel.cc
  \brief File containing implementation of LauCPFitModel class.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "TVirtualFitter.h"
#include "TSystem.h"
#include "TMinuit.h"
#include "TRandom.h"
#include "TFile.h"
#include "TMath.h"
#include "TH2.h"

#include "LauAbsBkgndDPModel.hh"
#include "LauAbsCoeffSet.hh"
#include "LauAbsDPDynamics.hh"
#include "LauAbsPdf.hh"
#include "LauAsymmCalc.hh"
#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauCPFitModel.hh"
#include "LauDaughters.hh"
#include "LauEffModel.hh"
#include "LauEmbeddedData.hh"
#include "LauFitNtuple.hh"
#include "LauKinematics.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"
#include "LauScfMap.hh"

ClassImp(LauCPFitModel)


LauCPFitModel::LauCPFitModel(LauAbsDPDynamics* negModel, LauAbsDPDynamics* posModel, Bool_t tagged, const TString& tagVarName) : LauAbsFitModel(),
	negSigModel_(negModel), posSigModel_(posModel),
	negKinematics_(negModel ? negModel->getKinematics() : 0),
	posKinematics_(posModel ? posModel->getKinematics() : 0),
	usingBkgnd_(kFALSE),
	nSigComp_(0),
	nSigDPPar_(0),
	nExtraPdfPar_(0),
	nNormPar_(0),
	negMeanEff_("negMeanEff",0.0,0.0,1.0), posMeanEff_("posMeanEff",0.0,0.0,1.0),
	negDPRate_("negDPRate",0.0,0.0,100.0), posDPRate_("posDPRate",0.0,0.0,100.0),
	signalEvents_(0),
	signalAsym_(0),
	forceAsym_(kFALSE),
	tagged_(tagged),
	tagVarName_(tagVarName),
	curEvtCharge_(0),
	useSCF_(kFALSE),
	useSCFHist_(kFALSE),
	scfFrac_("scfFrac",0.0,0.0,1.0),
	scfFracHist_(0),
	scfMap_(0),
	compareFitData_(kFALSE),
	negParent_("B-"), posParent_("B+"),
	negSignalTree_(0), posSignalTree_(0),
	reuseSignal_(kFALSE),
	useNegReweighting_(kFALSE), usePosReweighting_(kFALSE),
	sigDPLike_(0.0),
	scfDPLike_(0.0),
	sigExtraLike_(0.0),
	scfExtraLike_(0.0),
	sigTotalLike_(0.0),
	scfTotalLike_(0.0)
{
	LauDaughters* negDaug = negSigModel_->getDaughters();
	if (negDaug != 0) {negParent_ = negDaug->getNameParent();}
	LauDaughters* posDaug = posSigModel_->getDaughters();
	if (posDaug != 0) {posParent_ = posDaug->getNameParent();}
}

LauCPFitModel::~LauCPFitModel()
{
	delete negSignalTree_;
	delete posSignalTree_;
	for (LauBkgndEmbDataList::iterator iter = negBkgndTree_.begin(); iter != negBkgndTree_.end(); ++iter) {
		delete (*iter);
	}
	for (LauBkgndEmbDataList::iterator iter = posBkgndTree_.begin(); iter != posBkgndTree_.end(); ++iter) {
		delete (*iter);
	}
	delete scfFracHist_;
}

void LauCPFitModel::setupBkgndVectors()
{
	UInt_t nBkgnds = this->nBkgndClasses();
	negBkgndDPModels_.resize( nBkgnds );
	posBkgndDPModels_.resize( nBkgnds );
	negBkgndPdfs_.resize( nBkgnds );
	posBkgndPdfs_.resize( nBkgnds );
	bkgndEvents_.resize( nBkgnds );
	bkgndAsym_.resize( nBkgnds );
	negBkgndTree_.resize( nBkgnds );
	posBkgndTree_.resize( nBkgnds );
	reuseBkgnd_.resize( nBkgnds );
	bkgndDPLike_.resize( nBkgnds );
	bkgndExtraLike_.resize( nBkgnds );
	bkgndTotalLike_.resize( nBkgnds );
}

void LauCPFitModel::setNSigEvents(LauParameter* nSigEvents)
{
	if ( nSigEvents == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : The LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	if ( signalEvents_ != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : You are trying to overwrite the signal yield." << std::endl;
		return;
	}
	if ( signalAsym_ != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : You are trying to overwrite the signal asymmetry." << std::endl;
		return;
	}

	signalEvents_ = nSigEvents;
	TString name = signalEvents_->name();
	if ( ! name.Contains("signalEvents") && !( name.BeginsWith("signal") && name.EndsWith("Events") ) ) {
		signalEvents_->name("signalEvents");
	}
	Double_t value = nSigEvents->value();
	signalEvents_->range(-2.0*(TMath::Abs(value)+1.0), 2.0*(TMath::Abs(value)+1.0));

	signalAsym_ = new LauParameter("signalAsym",0.0,-1.0,1.0,kTRUE);
}

void LauCPFitModel::setNSigEvents( LauParameter* nSigEvents, LauParameter* sigAsym, Bool_t forceAsym )
{
	if ( nSigEvents == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : The event LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	if ( sigAsym == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : The asym LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if ( signalEvents_ != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : You are trying to overwrite the signal yield." << std::endl;
		return;
	}
	if ( signalAsym_ != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNSigEvents : You are trying to overwrite the signal asymmetry." << std::endl;
		return;
	}

	signalEvents_ = nSigEvents;
	signalEvents_->name("signalEvents");
	Double_t value = nSigEvents->value();
	signalEvents_->range(-2.0*(TMath::Abs(value)+1.0), 2.0*(TMath::Abs(value)+1.0));

	signalAsym_ = sigAsym;
	signalAsym_->name("signalAsym");
	signalAsym_->range(-1.0,1.0);

	forceAsym_ = forceAsym;
}

void LauCPFitModel::setNBkgndEvents( LauParameter* nBkgndEvents )
{
	if ( nBkgndEvents == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBgkndEvents : The background yield LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	} 

	if ( ! this->validBkgndClass( nBkgndEvents->name() ) ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : Invalid background class \"" << nBkgndEvents->name() << "\"." << std::endl;
		std::cerr << "                                        : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	UInt_t bkgndID = this->bkgndClassID( nBkgndEvents->name() );

	if ( bkgndEvents_[bkgndID] != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : You are trying to overwrite the background yield." << std::endl;
		return;
	}

	if ( bkgndAsym_[bkgndID] != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : You are trying to overwrite the background asymmetry." << std::endl;
		return;
	}

	bkgndEvents_[bkgndID] = nBkgndEvents;
	bkgndEvents_[bkgndID]->name( nBkgndEvents->name()+"Events" );
	Double_t value = nBkgndEvents->value();
	bkgndEvents_[bkgndID]->range(-2.0*(TMath::Abs(value)+1.0), 2.0*(TMath::Abs(value)+1.0));

	bkgndAsym_[bkgndID] = new LauParameter(nBkgndEvents->name()+"Asym",0.0,-1.0,1.0,kTRUE);
}

void LauCPFitModel::setNBkgndEvents(LauParameter* nBkgndEvents, LauParameter* bkgndAsym)
{
	if ( nBkgndEvents == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : The background yield LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if ( bkgndAsym == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : The background asym LauParameter pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if ( ! this->validBkgndClass( nBkgndEvents->name() ) ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : Invalid background class \"" << nBkgndEvents->name() << "\"." << std::endl;
		std::cerr << "                                        : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	UInt_t bkgndID = this->bkgndClassID( nBkgndEvents->name() );

	if ( bkgndEvents_[bkgndID] != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : You are trying to overwrite the background yield." << std::endl;
		return;
	}

	if ( bkgndAsym_[bkgndID] != 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setNBkgndEvents : You are trying to overwrite the background asymmetry." << std::endl;
		return;
	}

	bkgndEvents_[bkgndID] = nBkgndEvents;
	bkgndEvents_[bkgndID]->name( nBkgndEvents->name()+"Events" );
	Double_t value = nBkgndEvents->value();
	bkgndEvents_[bkgndID]->range(-2.0*(TMath::Abs(value)+1.0), 2.0*(TMath::Abs(value)+1.0));

	bkgndAsym_[bkgndID] = bkgndAsym;
	bkgndAsym_[bkgndID]->name( nBkgndEvents->name()+"Asym" );
	bkgndAsym_[bkgndID]->range(-1.0,1.0);
}

void LauCPFitModel::splitSignalComponent( const TH2* dpHisto, const Bool_t upperHalf, const Bool_t fluctuateBins, LauScfMap* scfMap )
{
	if ( useSCF_ == kTRUE ) {
		std::cerr << "ERROR in LauCPFitModel::splitSignalComponent : Have already setup SCF." << std::endl;
		return;
	}

	if ( dpHisto == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::splitSignalComponent : The histogram pointer is null." << std::endl;
		return;
	}

	LauDaughters* daughters = negSigModel_->getDaughters();
	scfFracHist_ = new LauEffModel( daughters, 0 );
	scfFracHist_->setEffHisto( dpHisto, kTRUE, fluctuateBins, 0.0, 0.0, upperHalf, daughters->squareDP() );

	scfMap_ = scfMap;

	useSCF_ = kTRUE;
	useSCFHist_ = kTRUE;
}

void LauCPFitModel::splitSignalComponent( const Double_t scfFrac, const Bool_t fixed )
{
	if ( useSCF_ == kTRUE ) {
		std::cerr << "ERROR in LauCPFitModel::splitSignalComponent : Have already setup SCF." << std::endl;
		return;
	}

	scfFrac_.range( 0.0, 1.0 );
	scfFrac_.value( scfFrac ); scfFrac_.initValue( scfFrac ); scfFrac_.genValue( scfFrac );
	scfFrac_.fixed( fixed );

	useSCF_ = kTRUE;
	useSCFHist_ = kFALSE;
}

void LauCPFitModel::setBkgndDPModels(const TString& bkgndClass, LauAbsBkgndDPModel* negModel, LauAbsBkgndDPModel* posModel)
{
	if ((negModel==0) || (posModel==0)) {
		std::cerr << "ERROR in LauCPFitModel::setBkgndDPModels : One or both of the model pointers is null." << std::endl;
		return;
	}

	// check that this background name is valid
	if ( ! this->validBkgndClass( bkgndClass) ) {
		std::cerr << "ERROR in LauCPFitModel::setBkgndDPModel : Invalid background class \"" << bkgndClass << "\"." << std::endl;
		std::cerr << "                                        : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		return;
	}

	UInt_t bkgndID = this->bkgndClassID( bkgndClass );
	negBkgndDPModels_[bkgndID] = negModel;
	posBkgndDPModels_[bkgndID] = posModel;

	usingBkgnd_ = kTRUE;
}

void LauCPFitModel::setSignalPdfs(LauAbsPdf* negPdf, LauAbsPdf* posPdf)
{
	if ( tagged_ ) {
		if (negPdf==0 || posPdf==0) {
			std::cerr << "ERROR in LauCPFitModel::setSignalPdfs : One or both of the PDF pointers is null." << std::endl;
			return;
		}
	} else {
		// if we're doing an untagged analysis we will only use the negative PDFs
		if ( negPdf==0 ) {
			std::cerr << "ERROR in LauCPFitModel::setSignalPdfs : The negative PDF pointer is null." << std::endl;
			return;
		}
		if ( posPdf!=0 ) {
			std::cerr << "WARNING in LauCPFitModel::setSignalPdfs : Doing an untagged fit so will not use the positive PDF." << std::endl;
		}
	}
	negSignalPdfs_.push_back(negPdf);
	posSignalPdfs_.push_back(posPdf);
}

void LauCPFitModel::setSCFPdfs(LauAbsPdf* negPdf, LauAbsPdf* posPdf)
{
	if ( tagged_ ) {
		if (negPdf==0 || posPdf==0) {
			std::cerr << "ERROR in LauCPFitModel::setSCFPdfs : One or both of the PDF pointers is null." << std::endl;
			return;
		}
	} else {
		// if we're doing an untagged analysis we will only use the negative PDFs
		if ( negPdf==0 ) {
			std::cerr << "ERROR in LauCPFitModel::setSCFPdfs : The negative PDF pointer is null." << std::endl;
			return;
		}
		if ( posPdf!=0 ) {
			std::cerr << "WARNING in LauCPFitModel::setSCFPdfs : Doing an untagged fit so will not use the positive PDF." << std::endl;
		}
	}
	negScfPdfs_.push_back(negPdf);
	posScfPdfs_.push_back(posPdf);
}

void LauCPFitModel::setBkgndPdfs(const TString& bkgndClass, LauAbsPdf* negPdf, LauAbsPdf* posPdf)
{
	if ( tagged_ ) {
		if (negPdf==0 || posPdf==0) {
			std::cerr << "ERROR in LauCPFitModel::setBkgndPdfs : One or both of the PDF pointers is null." << std::endl;
			return;
		}
	} else {
		// if we're doing an untagged analysis we will only use the negative PDFs
		if ( negPdf==0 ) {
			std::cerr << "ERROR in LauCPFitModel::setBkgndPdfs : The negative PDF pointer is null." << std::endl;
			return;
		}
		if ( posPdf!=0 ) {
			std::cerr << "WARNING in LauCPFitModel::setBkgndPdfs : Doing an untagged fit so will not use the positive PDF." << std::endl;
		}
	}

	// check that this background name is valid
	if ( ! this->validBkgndClass( bkgndClass ) ) {
		std::cerr << "ERROR in LauCPFitModel::setBkgndPdfs : Invalid background class \"" << bkgndClass << "\"." << std::endl;
		std::cerr << "                                     : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		return;
	}

	UInt_t bkgndID = this->bkgndClassID( bkgndClass );
	negBkgndPdfs_[bkgndID].push_back(negPdf);
	posBkgndPdfs_[bkgndID].push_back(posPdf);

	usingBkgnd_ = kTRUE;
}

void LauCPFitModel::setAmpCoeffSet(LauAbsCoeffSet* coeffSet)
{
	// Is there a component called compName in the signal model?
	TString compName(coeffSet->name());
	Bool_t negOK = negSigModel_->hasResonance(compName);
	TString conjName = negSigModel_->getConjResName(compName);
	Bool_t posOK = posSigModel_->hasResonance(conjName);
	if (!negOK) {
		std::cerr << "ERROR in LauCPFitModel::setMagPhase : " << negParent_ << " signal DP model doesn't contain component \"" << compName << "\"." << std::endl;
		return;
	}
	if (!posOK) {
		std::cerr << "ERROR in LauCPFitModel::setMagPhase : " << posParent_ << " signal DP model doesn't contain component \"" << conjName << "\"." << std::endl;
		return;
	}

	// Do we already have it in our list of names?
	for (std::vector<LauAbsCoeffSet*>::const_iterator iter=coeffPars_.begin(); iter!=coeffPars_.end(); ++iter) {
		if ((*iter)->name() == compName) {
			std::cerr << "ERROR in LauCPFitModel::setAmpCoeffSet : Have already set coefficients for \"" << compName << "\"." << std::endl;
			return;
		}
	}

	coeffSet->index(nSigComp_);
	coeffPars_.push_back(coeffSet);

	TString parName = coeffSet->baseName(); parName += "FitFracAsym";
	fitFracAsymm_.push_back(LauParameter(parName, 0.0, -1.0, 1.0));

	acp_.push_back(coeffSet->acp());

	++nSigComp_;

	std::cout << "INFO in LauCPFitModel::setAmpCoeffSet : Added coefficients for component \"" << compName << "\" to the fit model." << std::endl;
	coeffSet->printParValues();
}

void LauCPFitModel::initialise()
{
	// First of all check that, if a given component is being used,
	// we've got the PDFs for all the variables involved
	if ( this->useDP() ) {
		if ((negSigModel_ == 0) || (posSigModel_ == 0)) {
			std::cerr << "ERROR in LauCPFitModel::initialise : the pointer to one (neg or pos) of the signal DP models is null.\n";
			std::cerr << "                                   : Removing the Dalitz Plot from the model." << std::endl;
			this->useDP(kFALSE);
		}
		if ( usingBkgnd_ ) {
			if ( negBkgndDPModels_.empty() || posBkgndDPModels_.empty() ) {
				std::cerr << "ERROR in LauCPFitModel::initialise : No background DP models found.\n";
				std::cerr << "                                   : Removing the Dalitz plot from the model." << std::endl;
				this->useDP(kFALSE);
			}
			for (LauBkgndDPModelList::const_iterator dpmodel_iter = negBkgndDPModels_.begin(); dpmodel_iter != negBkgndDPModels_.end(); ++dpmodel_iter ) {
				if ( (*dpmodel_iter) == 0 ) {
					std::cerr << "ERROR in LauCPFitModel::initialise : The pointer to one of the background DP models is null.\n";
					std::cerr << "                                   : Removing the Dalitz Plot from the model." << std::endl;
					this->useDP(kFALSE);
					break;
				}
			}
			for (LauBkgndDPModelList::const_iterator dpmodel_iter = posBkgndDPModels_.begin(); dpmodel_iter != posBkgndDPModels_.end(); ++dpmodel_iter ) {
				if ( (*dpmodel_iter) == 0 ) {
					std::cerr << "ERROR in LauCPFitModel::initialise : The pointer to one of the background DP models is null.\n";
					std::cerr << "                                   : Removing the Dalitz Plot from the model." << std::endl;
					this->useDP(kFALSE);
					break;
				}
			}
		}
	}

	// Next check that, if a given component is being used we've got the
	// right number of PDFs for all the variables involved
	// TODO - should probably check variable names and so on as well

	UInt_t nsigpdfvars(0);
	for ( LauPdfList::const_iterator pdf_iter = negSignalPdfs_.begin(); pdf_iter != negSignalPdfs_.end(); ++pdf_iter ) {
		std::vector<TString> varNames = (*pdf_iter)->varNames();
		for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
			if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
				++nsigpdfvars;
			}
		}
	}
	if (useSCF_) {
		UInt_t nscfpdfvars(0);
		for ( LauPdfList::const_iterator pdf_iter = negScfPdfs_.begin(); pdf_iter != negScfPdfs_.end(); ++pdf_iter ) {
			std::vector<TString> varNames = (*pdf_iter)->varNames();
			for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
				if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
					++nscfpdfvars;
				}
			}
		}
		if (nscfpdfvars != nsigpdfvars) {
			std::cerr << "ERROR in LauCPFitModel::initialise : There are " << nsigpdfvars << " TM signal PDF variables but " << nscfpdfvars << " SCF signal PDF variables." << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}
	if (usingBkgnd_) {
		for (LauBkgndPdfsList::const_iterator bgclass_iter = negBkgndPdfs_.begin(); bgclass_iter != negBkgndPdfs_.end(); ++bgclass_iter) {
			UInt_t nbkgndpdfvars(0);
			const LauPdfList& pdfList = (*bgclass_iter);
			for ( LauPdfList::const_iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter ) {
				std::vector<TString> varNames = (*pdf_iter)->varNames();
				for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
					if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
						++nbkgndpdfvars;
					}
				}
			}
			if (nbkgndpdfvars != nsigpdfvars) {
				std::cerr << "ERROR in LauCPFitModel::initialise : There are " << nsigpdfvars << " signal PDF variables but " << nbkgndpdfvars << " bkgnd PDF variables." << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
		}
	}

	// Clear the vectors of parameter information so we can start from scratch
	this->clearFitParVectors();

	// Set the fit parameters for signal and background models
	this->setSignalDPParameters();

	// Set the fit parameters for the various extra PDFs
	this->setExtraPdfParameters();

	// Set the initial bg and signal events
	this->setFitNEvents();

	// Check that we have the expected number of fit variables
	const LauParameterPList& fitVars = this->fitPars();
	if (fitVars.size() != (nSigDPPar_ + nExtraPdfPar_ + nNormPar_)) {
		std::cerr << "ERROR in LauCPFitModel::initialise : Number of fit parameters not of expected size. Exiting" << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// From the initial parameter values calculate the coefficients
	// so they can be passed to the signal model
	this->updateCoeffs();

	// Initialisation
	if (this->useDP() == kTRUE) {
		this->initialiseDPModels();
	}

	if (!this->useDP() && negSignalPdfs_.empty()) {
		std::cerr << "ERROR in LauCPFitModel::initialise : Signal model doesn't exist for any variable." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	this->setExtraNtupleVars();
}

void LauCPFitModel::initialiseDPModels()
{
	std::cout << "INFO in LauCPFitModel::initialiseDPModels : Initialising signal DP model" << std::endl;
	negSigModel_->initialise(negCoeffs_);
	posSigModel_->initialise(posCoeffs_);

	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndDPModelList::iterator iter = negBkgndDPModels_.begin(); iter != negBkgndDPModels_.end(); ++iter) {
			(*iter)->initialise();
		}
		for (LauBkgndDPModelList::iterator iter = posBkgndDPModels_.begin(); iter != posBkgndDPModels_.end(); ++iter) {
			(*iter)->initialise();
		}
	}
}

void LauCPFitModel::setSignalDPParameters()
{
	// Set the fit parameters for the signal model.

	nSigDPPar_ = 0;
	if ( ! this->useDP() ) {
		return;
	}

	std::cout << "INFO in LauCPFitModel::setSignalDPParameters : Setting the initial fit parameters for the signal DP model." << std::endl;

	// Need to check that the number of components we have and that the dynamics has matches up
	UInt_t nNegAmp = negSigModel_->getnAmp();
	UInt_t nPosAmp = posSigModel_->getnAmp();
	if ( nNegAmp != nPosAmp ) {
		std::cerr << "ERROR in LauCPFitModel::setSignalDPParameters : Unequal number of signal DP components in the negative and positive models: " << nNegAmp << " != " << nPosAmp << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	if ( nNegAmp != nSigComp_ ) {
		std::cerr << "ERROR in LauCPFitModel::setSignalDPParameters : Number of signal DP components in the model (" << nNegAmp << ") not equal to number of coefficients supplied (" << nSigComp_ << ")." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}


	// Place signal model parameters in vector of fit variables
	LauParameterPList& fitVars = this->fitPars();
	for (UInt_t i = 0; i < nSigComp_; i++) {
		LauParameterPList pars = coeffPars_[i]->getParameters();
		for (LauParameterPList::iterator iter = pars.begin(); iter != pars.end(); ++iter) {
			if ( !(*iter)->clone() ) {
				fitVars.push_back(*iter);
				++nSigDPPar_;
			}
		}
	}
}

void LauCPFitModel::setExtraPdfParameters()
{
	// Include all the parameters of the PDF in the fit
	// NB all of them are passed to the fit, even though some have been fixed through parameter.fixed(kTRUE)
	// With the new "cloned parameter" scheme only "original" parameters are passed to the fit.
	// Their clones are updated automatically when the originals are updated.

	nExtraPdfPar_ = 0;

	nExtraPdfPar_ += this->addFitParameters(negSignalPdfs_);
	if ( tagged_ ) {
		nExtraPdfPar_ += this->addFitParameters(posSignalPdfs_);
	}

	if (useSCF_ == kTRUE) {
		nExtraPdfPar_ += this->addFitParameters(negScfPdfs_);
		if ( tagged_ ) {
			nExtraPdfPar_ += this->addFitParameters(posScfPdfs_);
		}
	}

	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndPdfsList::iterator iter = negBkgndPdfs_.begin(); iter != negBkgndPdfs_.end(); ++iter) {
			nExtraPdfPar_ += this->addFitParameters(*iter);
		}
		if ( tagged_ ) {
			for (LauBkgndPdfsList::iterator iter = posBkgndPdfs_.begin(); iter != posBkgndPdfs_.end(); ++iter) {
				nExtraPdfPar_ += this->addFitParameters(*iter);
			}
		}
	}
}

void LauCPFitModel::setFitNEvents()
{
	if ( signalEvents_ == 0 ) {
		std::cerr << "ERROR in LauCPFitModel::setFitNEvents : Signal yield not defined." << std::endl;
		return;
	}
	nNormPar_ = 0;

	// initialise the total number of events to be the sum of all the hypotheses
	Double_t nTotEvts = signalEvents_->value();
	for (LauBkgndYieldList::const_iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
		nTotEvts += (*iter)->value();
		if ( (*iter) == 0 ) {
			std::cerr << "ERROR in LauCPFitModel::setFitNEvents : Background yield not defined." << std::endl;
			return;
		}
	}
	this->eventsPerExpt(TMath::FloorNint(nTotEvts));

	LauParameterPList& fitVars = this->fitPars();

	// if doing an extended ML fit add the number of signal events into the fit parameters
	if (this->doEMLFit()) {
		std::cout << "INFO in LauCPFitModel::setFitNEvents : Initialising number of events for signal and background components..." << std::endl;
		// add the signal fraction to the list of fit parameters
		fitVars.push_back(signalEvents_);
		++nNormPar_;
	} else {
		std::cout << "INFO in LauCPFitModel::setFitNEvents : Initialising number of events for background components (and hence signal)..." << std::endl;
	}

	// if not using the DP in the model we need an explicit signal asymmetry parameter
	if (this->useDP() == kFALSE) {
		fitVars.push_back(signalAsym_);
		++nNormPar_;
	}

	if (useSCF_ && !useSCFHist_) {
		fitVars.push_back(&scfFrac_);
		++nNormPar_;
	}

	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndYieldList::iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
			LauParameter* parameter = (*iter);
			fitVars.push_back(parameter);
			++nNormPar_;
		}
		for (LauBkgndYieldList::iterator iter = bkgndAsym_.begin(); iter != bkgndAsym_.end(); ++iter) {
			LauParameter* parameter = (*iter);
			fitVars.push_back(parameter);
			++nNormPar_;
		}
	}
}

void LauCPFitModel::setExtraNtupleVars()
{
	// Set-up other parameters derived from the fit results, e.g. fit fractions.

	if (this->useDP() != kTRUE) {
		return;
	}

	// First clear the vectors so we start from scratch
	this->clearExtraVarVectors();

	LauParameterList& extraVars = this->extraPars();

	// Add the positive and negative fit fractions for each signal component
	negFitFrac_ = negSigModel_->getFitFractions();
	if (negFitFrac_.size() != nSigComp_) {
		std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << negFitFrac_.size() << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	for (UInt_t i(0); i<nSigComp_; ++i) {
		if (negFitFrac_[i].size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << negFitFrac_[i].size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	posFitFrac_ = posSigModel_->getFitFractions();
	if (posFitFrac_.size() != nSigComp_) {
		std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << posFitFrac_.size() << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	for (UInt_t i(0); i<nSigComp_; ++i) {
		if (posFitFrac_[i].size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << posFitFrac_[i].size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Add the positive and negative fit fractions that have not been corrected for the efficiency for each signal component
	negFitFracEffUnCorr_ = negSigModel_->getFitFractionsEfficiencyUncorrected();
	if (negFitFracEffUnCorr_.size() != nSigComp_) {
		std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << negFitFracEffUnCorr_.size() << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	for (UInt_t i(0); i<nSigComp_; ++i) {
		if (negFitFracEffUnCorr_[i].size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << negFitFracEffUnCorr_[i].size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	posFitFracEffUnCorr_ = posSigModel_->getFitFractionsEfficiencyUncorrected();
	if (posFitFracEffUnCorr_.size() != nSigComp_) {
		std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << posFitFracEffUnCorr_.size() << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	for (UInt_t i(0); i<nSigComp_; ++i) {
		if (posFitFracEffUnCorr_[i].size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::setExtraNtupleVars : Initial Fit Fraction array of unexpected dimension: " << posFitFracEffUnCorr_[i].size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	for (UInt_t i(0); i<nSigComp_; ++i) {
		for (UInt_t j(i); j<nSigComp_; ++j) {
			TString name = negFitFrac_[i][j].name();
			name.Insert( name.Index("FitFrac"), "Neg" );
			negFitFrac_[i][j].name(name);
			extraVars.push_back(negFitFrac_[i][j]);

			name = posFitFrac_[i][j].name();
			name.Insert( name.Index("FitFrac"), "Pos" );
			posFitFrac_[i][j].name(name);
			extraVars.push_back(posFitFrac_[i][j]);

			name = negFitFracEffUnCorr_[i][j].name();
			name.Insert( name.Index("FitFrac"), "Neg" );
			negFitFracEffUnCorr_[i][j].name(name);
			extraVars.push_back(negFitFracEffUnCorr_[i][j]);

			name = posFitFracEffUnCorr_[i][j].name();
			name.Insert( name.Index("FitFrac"), "Pos" );
			posFitFracEffUnCorr_[i][j].name(name);
			extraVars.push_back(posFitFracEffUnCorr_[i][j]);
		}
	}

	// Store any extra parameters/quantities from the DP model (e.g. K-matrix total fit fractions)
	std::vector<LauParameter> negExtraPars = negSigModel_->getExtraParameters();
	std::vector<LauParameter>::iterator negExtraIter;
	for (negExtraIter = negExtraPars.begin(); negExtraIter != negExtraPars.end(); ++negExtraIter) {
		LauParameter negExtraParameter = (*negExtraIter);
		extraVars.push_back(negExtraParameter);
	}

	std::vector<LauParameter> posExtraPars = posSigModel_->getExtraParameters();
	std::vector<LauParameter>::iterator posExtraIter;
	for (posExtraIter = posExtraPars.begin(); posExtraIter != posExtraPars.end(); ++posExtraIter) {
		LauParameter posExtraParameter = (*posExtraIter);
		extraVars.push_back(posExtraParameter);
	}

	// Now add in the DP efficiency value
	Double_t initMeanEff = negSigModel_->getMeanEff().initValue();
	negMeanEff_.value(initMeanEff);
	negMeanEff_.genValue(initMeanEff);
	negMeanEff_.initValue(initMeanEff);
	extraVars.push_back(negMeanEff_);

	initMeanEff = posSigModel_->getMeanEff().initValue();
	posMeanEff_.value(initMeanEff);
	posMeanEff_.genValue(initMeanEff);
	posMeanEff_.initValue(initMeanEff);
	extraVars.push_back(posMeanEff_);

	// Also add in the DP rates
	Double_t initDPRate = negSigModel_->getDPRate().initValue();
	negDPRate_.value(initDPRate);
	negDPRate_.genValue(initDPRate);
	negDPRate_.initValue(initDPRate);
	extraVars.push_back(negDPRate_);

	initDPRate = posSigModel_->getDPRate().initValue();
	posDPRate_.value(initDPRate);
	posDPRate_.genValue(initDPRate);
	posDPRate_.initValue(initDPRate);
	extraVars.push_back(posDPRate_);

	// Calculate the CPC and CPV Fit Fractions, ACPs and FitFrac asymmetries
	this->calcExtraFractions(kTRUE);
	this->calcAsymmetries(kTRUE);

	// Add the CP violating and CP conserving fit fractions for each signal component
	for (UInt_t i = 0; i < nSigComp_; i++) {
		for (UInt_t j = i; j < nSigComp_; j++) {
			extraVars.push_back(CPVFitFrac_[i][j]);
		}
	}
	for (UInt_t i = 0; i < nSigComp_; i++) {
		for (UInt_t j = i; j < nSigComp_; j++) {
			extraVars.push_back(CPCFitFrac_[i][j]);
		}
	}

	// Add the Fit Fraction asymmetry for each signal component
	for (UInt_t i = 0; i < nSigComp_; i++) {
		extraVars.push_back(fitFracAsymm_[i]);
	}

	// Add the calculated CP asymmetry for each signal component
	for (UInt_t i = 0; i < nSigComp_; i++) {
		extraVars.push_back(acp_[i]);
	}
}

void LauCPFitModel::calcExtraFractions(Bool_t initValues)
{
	// Calculate the CP-conserving and CP-violating fit fractions

	if (initValues) {
		// create the structure
		CPCFitFrac_.clear();
		CPVFitFrac_.clear();
		CPCFitFrac_.resize(nSigComp_);
		CPVFitFrac_.resize(nSigComp_);
		for (UInt_t i(0); i<nSigComp_; ++i) {
			CPCFitFrac_[i].resize(nSigComp_);
			CPVFitFrac_[i].resize(nSigComp_);

			for (UInt_t j(i); j<nSigComp_; ++j) {
				TString name = negFitFrac_[i][j].name();
				name.Replace( name.Index("Neg"), 3, "CPC" );
				CPCFitFrac_[i][j].name( name );
				CPCFitFrac_[i][j].valueAndRange( 0.0, -100.0, 100.0 );

				name = negFitFrac_[i][j].name();
				name.Replace( name.Index("Neg"), 3, "CPV" );
				CPVFitFrac_[i][j].name( name );
				CPVFitFrac_[i][j].valueAndRange( 0.0, -100.0, 100.0 );
			}
		}
	}

	Double_t denom = negDPRate_ + posDPRate_;

	for (UInt_t i(0); i<nSigComp_; ++i) {
		for (UInt_t j(i); j<nSigComp_; ++j) {

			Double_t negTerm = negFitFrac_[i][j]*negDPRate_;
			Double_t posTerm = posFitFrac_[i][j]*posDPRate_;

			Double_t cpcFitFrac = (negTerm + posTerm)/denom;
			Double_t cpvFitFrac = (negTerm - posTerm)/denom;

			CPCFitFrac_[i][j] = cpcFitFrac;
			CPVFitFrac_[i][j] = cpvFitFrac;

			if (initValues) {
				CPCFitFrac_[i][j].genValue(cpcFitFrac);
				CPCFitFrac_[i][j].initValue(cpcFitFrac);

				CPVFitFrac_[i][j].genValue(cpvFitFrac);
				CPVFitFrac_[i][j].initValue(cpvFitFrac);
			}
		}
	}
}

void LauCPFitModel::calcAsymmetries(Bool_t initValues)
{
	// Calculate the CP asymmetries
	// Also calculate the fit fraction asymmetries

	for (UInt_t i = 0; i < nSigComp_; i++) {

		acp_[i] = coeffPars_[i]->acp();

		LauAsymmCalc asymmCalc(negFitFrac_[i][i].value(), posFitFrac_[i][i].value());
		Double_t asym = asymmCalc.getAsymmetry();
		fitFracAsymm_[i] = asym;
		if (initValues) {
			fitFracAsymm_[i].genValue(asym);
			fitFracAsymm_[i].initValue(asym);
		}
	}
}

void LauCPFitModel::finaliseFitResults(const TString& tablePrefixName)
{
	// Retrieve parameters from the fit results for calculations and toy generation
	// and eventually store these in output root ntuples/text files

	// Now take the fit parameters and update them as necessary
	// i.e. to make mag > 0.0, phase in the right range.
	// This function will also calculate any other values, such as the
	// fit fractions, using any errors provided by fitParErrors as appropriate.
	// Also obtain the pull values: (measured - generated)/(average error)

	if (this->useDP() == kTRUE) {
		for (UInt_t i = 0; i < nSigComp_; ++i) {
			// Check whether we have "a/b > 0.0", and phases in the right range
			coeffPars_[i]->finaliseValues();
		}
	}

	// update the pulls on the event fractions and asymmetries
	if (this->doEMLFit()) {
		signalEvents_->updatePull();
	}
	if (this->useDP() == kFALSE) {
		signalAsym_->updatePull();
	}
	if (useSCF_ && !useSCFHist_) {
		scfFrac_.updatePull();
	}
	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndYieldList::iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
			(*iter)->updatePull();
		}
		for (LauBkgndYieldList::iterator iter = bkgndAsym_.begin(); iter != bkgndAsym_.end(); ++iter) {
			(*iter)->updatePull();
		}
	}

	// Update the pulls on all the extra PDFs' parameters
	this->updateFitParameters(negSignalPdfs_);
	this->updateFitParameters(posSignalPdfs_);
	if (useSCF_ == kTRUE) {
		this->updateFitParameters(negScfPdfs_);
		this->updateFitParameters(posScfPdfs_);
	}
	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndPdfsList::iterator iter = negBkgndPdfs_.begin(); iter != negBkgndPdfs_.end(); ++iter) {
			this->updateFitParameters(*iter);
		}
		for (LauBkgndPdfsList::iterator iter = posBkgndPdfs_.begin(); iter != posBkgndPdfs_.end(); ++iter) {
			this->updateFitParameters(*iter);
		}
	}

	// Fill the fit results to the ntuple

	// update the coefficients and then calculate the fit fractions and ACP's
	if (this->useDP() == kTRUE) {
		this->updateCoeffs();
		negSigModel_->updateCoeffs(negCoeffs_);  negSigModel_->calcExtraInfo();
		posSigModel_->updateCoeffs(posCoeffs_);  posSigModel_->calcExtraInfo();

		LauParArray negFitFrac = negSigModel_->getFitFractions();
		if (negFitFrac.size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << negFitFrac.size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			if (negFitFrac[i].size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << negFitFrac[i].size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
		}

		LauParArray posFitFrac = posSigModel_->getFitFractions();
		if (posFitFrac.size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << posFitFrac.size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			if (posFitFrac[i].size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << posFitFrac[i].size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
		}

		LauParArray negFitFracEffUnCorr = negSigModel_->getFitFractionsEfficiencyUncorrected();
		if (negFitFracEffUnCorr.size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << negFitFracEffUnCorr.size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			if (negFitFracEffUnCorr[i].size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << negFitFracEffUnCorr[i].size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
		}

		LauParArray posFitFracEffUnCorr = posSigModel_->getFitFractionsEfficiencyUncorrected();
		if (posFitFracEffUnCorr.size() != nSigComp_) {
			std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << posFitFracEffUnCorr.size() << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			if (posFitFracEffUnCorr[i].size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::finaliseFitResults : Fit Fraction array of unexpected dimension: " << posFitFracEffUnCorr[i].size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
		}

		for (UInt_t i(0); i<nSigComp_; ++i) {
			for (UInt_t j(i); j<nSigComp_; ++j) {
				negFitFrac_[i][j].value(negFitFrac[i][j].value());
				posFitFrac_[i][j].value(posFitFrac[i][j].value());
				negFitFracEffUnCorr_[i][j].value(negFitFracEffUnCorr[i][j].value());
				posFitFracEffUnCorr_[i][j].value(posFitFracEffUnCorr[i][j].value());
			}
		}

		negMeanEff_.value(negSigModel_->getMeanEff().value());
		posMeanEff_.value(posSigModel_->getMeanEff().value());
		negDPRate_.value(negSigModel_->getDPRate().value());
		posDPRate_.value(posSigModel_->getDPRate().value());

		this->calcExtraFractions();
		this->calcAsymmetries();

		// Then store the final fit parameters, and any extra parameters for
		// the signal model (e.g. fit fractions, FF asymmetries, ACPs, mean efficiency and DP rate)

		this->clearExtraVarVectors();
		LauParameterList& extraVars = this->extraPars();

		// Add the positive and negative fit fractions for each signal component
		for (UInt_t i(0); i<nSigComp_; ++i) {
			for (UInt_t j(i); j<nSigComp_; ++j) {
				extraVars.push_back(negFitFrac_[i][j]);
				extraVars.push_back(posFitFrac_[i][j]);
				extraVars.push_back(negFitFracEffUnCorr_[i][j]);
				extraVars.push_back(posFitFracEffUnCorr_[i][j]);
			}
		}

		// Store any extra parameters/quantities from the DP model (e.g. K-matrix total fit fractions)
		std::vector<LauParameter> negExtraPars = negSigModel_->getExtraParameters();
		std::vector<LauParameter>::iterator negExtraIter;
		for (negExtraIter = negExtraPars.begin(); negExtraIter != negExtraPars.end(); ++negExtraIter) {
			LauParameter negExtraParameter = (*negExtraIter);
			extraVars.push_back(negExtraParameter);
		}

		std::vector<LauParameter> posExtraPars = posSigModel_->getExtraParameters();
		std::vector<LauParameter>::iterator posExtraIter;
		for (posExtraIter = posExtraPars.begin(); posExtraIter != posExtraPars.end(); ++posExtraIter) {
			LauParameter posExtraParameter = (*posExtraIter);
			extraVars.push_back(posExtraParameter);
		}

		extraVars.push_back(negMeanEff_);
		extraVars.push_back(posMeanEff_);
		extraVars.push_back(negDPRate_);
		extraVars.push_back(posDPRate_);

		for (UInt_t i = 0; i < nSigComp_; i++) {
			for (UInt_t j(i); j<nSigComp_; ++j) {
				extraVars.push_back(CPVFitFrac_[i][j]);
			}
		}
		for (UInt_t i = 0; i < nSigComp_; i++) {
			for (UInt_t j(i); j<nSigComp_; ++j) {
				extraVars.push_back(CPCFitFrac_[i][j]);
			}
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			extraVars.push_back(fitFracAsymm_[i]);
		}
		for (UInt_t i(0); i<nSigComp_; ++i) {
			extraVars.push_back(acp_[i]);
		}

		this->printFitFractions(std::cout);
		this->printAsymmetries(std::cout);
	}

	const LauParameterPList& fitVars = this->fitPars();
	const LauParameterList& extraVars = this->extraPars();
	LauFitNtuple* ntuple = this->fitNtuple();
	ntuple->storeParsAndErrors(fitVars, extraVars);

	// find out the correlation matrix for the parameters
	ntuple->storeCorrMatrix(this->iExpt(), this->nll(), this->fitStatus(), this->covarianceMatrix());

	// Fill the data into ntuple
	ntuple->updateFitNtuple();

	// Print out the partial fit fractions, phases and the 
	// averaged efficiency, reweighted by the dynamics (and anything else)
	if (this->writeLatexTable()) {
		TString sigOutFileName(tablePrefixName);
		sigOutFileName += "_"; sigOutFileName += this->iExpt(); sigOutFileName += "Expt.tex";
		this->writeOutTable(sigOutFileName);
	}
}

void LauCPFitModel::printFitFractions(std::ostream& output)
{
	// Print out Fit Fractions, total DP rate and mean efficiency
	// First for the B- events
	for (UInt_t i = 0; i < nSigComp_; i++) {
		const TString compName(coeffPars_[i]->name());
		output << negParent_ << " FitFraction for component " << i << " (" << compName << ") = " << negFitFrac_[i][i] << std::endl;
	}
	output << negParent_ << " overall DP rate (integral of matrix element squared) = " << negDPRate_ << std::endl;
	output << negParent_ << " average efficiency weighted by whole DP dynamics = " << negMeanEff_ << std::endl;

	// Then for the positive sample
	for (UInt_t i = 0; i < nSigComp_; i++) {
		const TString compName(coeffPars_[i]->name());
		const TString conjName(negSigModel_->getConjResName(compName));
		output << posParent_ << " FitFraction for component " << i << " (" << conjName << ") = " << posFitFrac_[i][i] << std::endl;
	}
	output << posParent_ << " overall DP rate (integral of matrix element squared) = " << posDPRate_ << std::endl;
	output << posParent_ << " average efficiency weighted by whole DP dynamics = " << posMeanEff_ << std::endl;
}

void LauCPFitModel::printAsymmetries(std::ostream& output)
{
	for (UInt_t i = 0; i < nSigComp_; i++) {
		const TString compName(coeffPars_[i]->name());
		output << "Fit Fraction asymmetry for component " << i << " (" << compName << ") = " << fitFracAsymm_[i] << std::endl;
	}
	for (UInt_t i = 0; i < nSigComp_; i++) {
		const TString compName(coeffPars_[i]->name());
		output << "ACP for component " << i << " (" << compName << ") = " << acp_[i] << std::endl;
	}
}

void LauCPFitModel::writeOutTable(const TString& outputFile)
{
	// Write out the results of the fit to a tex-readable table
	// TODO - need to include the yields in this table
	std::ofstream fout(outputFile);
	LauPrint print;

	std::cout << "INFO in LauCPFitModel::writeOutTable : Writing out results of the fit to the tex file " << outputFile << std::endl;

	if (this->useDP() == kTRUE) {
		// print the fit coefficients in one table
		coeffPars_.front()->printTableHeading(fout);
		for (UInt_t i = 0; i < nSigComp_; i++) {
			coeffPars_[i]->printTableRow(fout);
		}
		fout << "\\hline" << std::endl;
		fout << "\\end{tabular}" << std::endl << std::endl;

		// print the fit fractions and asymmetries in another
		fout << "\\begin{tabular}{|l|c|c|c|c|}" << std::endl;
		fout << "\\hline" << std::endl;
		fout << "Component & " << negParent_ << " Fit Fraction & " << posParent_ << " Fit Fraction & Fit Fraction Asymmetry & ACP \\\\" << std::endl;
		fout << "\\hline" << std::endl;

		Double_t negFitFracSum(0.0);
		Double_t posFitFracSum(0.0);

		for (UInt_t i = 0; i < nSigComp_; i++) {
			TString resName = coeffPars_[i]->name();
			resName = resName.ReplaceAll("_", "\\_");

			Double_t negFitFrac = negFitFrac_[i][i].value();
			Double_t posFitFrac = posFitFrac_[i][i].value();
			negFitFracSum += negFitFrac;
			posFitFracSum += posFitFrac;

			Double_t fitFracAsymm = fitFracAsymm_[i].value();

			Double_t acp = acp_[i].value();
			Double_t acpErr = acp_[i].error();

			fout << resName << "  &  $";

			print.printFormat(fout, negFitFrac);
			fout << "$  &  $";
			print.printFormat(fout, posFitFrac);
			fout << "$  &  $";

			print.printFormat(fout, fitFracAsymm);
			fout << "$  &  $";

			print.printFormat(fout, acp);
			fout << " \\pm ";
			print.printFormat(fout, acpErr);
			fout << "$ \\\\" << std::endl;
		}
		fout << "\\hline" << std::endl;

		// Also print out sum of fit fractions
		fout << "Fit Fraction Sum  &  $";
		print.printFormat(fout, negFitFracSum);
		fout << "$  &  $";
		print.printFormat(fout, posFitFracSum);
		fout << "$  &   &   \\\\" << std::endl;
		fout << "\\hline" << std::endl;

		fout << "DP rate  &  $";
		print.printFormat(fout, negDPRate_.value());
		fout << "$  &  $";
		print.printFormat(fout, posDPRate_.value());
		fout << "$  &   &   \\\\" << std::endl;

		fout << "$< \\varepsilon > $ &  $";
		print.printFormat(fout, negMeanEff_.value());
		fout << "$  &  $";
		print.printFormat(fout, posMeanEff_.value());
		fout << "$  &   &   \\\\" << std::endl;
		fout << "\\hline" << std::endl;
		fout << "\\end{tabular}" << std::endl << std::endl;
	}

	if (!negSignalPdfs_.empty()) {
		fout << "\\begin{tabular}{|l|c|}" << std::endl;
		fout << "\\hline" << std::endl;
		if (useSCF_ == kTRUE) {
			fout << "\\Extra TM Signal PDFs' Parameters: & \\\\" << std::endl;
		} else {
			fout << "\\Extra Signal PDFs' Parameters: & \\\\" << std::endl;
		}
		this->printFitParameters(negSignalPdfs_, fout);
		if ( tagged_ ) {
			this->printFitParameters(posSignalPdfs_, fout);
		}
		if (useSCF_ == kTRUE && !negScfPdfs_.empty()) {
			fout << "\\hline" << std::endl;
			fout << "\\Extra SCF Signal PDFs' Parameters: & \\\\" << std::endl;
			this->printFitParameters(negScfPdfs_, fout);
			if ( tagged_ ) {
				this->printFitParameters(posScfPdfs_, fout);
			}
		}
		if (usingBkgnd_ == kTRUE && !negBkgndPdfs_.empty()) {
			fout << "\\hline" << std::endl;
			fout << "\\Extra Background PDFs' Parameters: & \\\\" << std::endl;
			for (LauBkgndPdfsList::const_iterator iter = negBkgndPdfs_.begin(); iter != negBkgndPdfs_.end(); ++iter) {
				this->printFitParameters(*iter, fout);
			}
			if ( tagged_ ) {
				for (LauBkgndPdfsList::const_iterator iter = posBkgndPdfs_.begin(); iter != posBkgndPdfs_.end(); ++iter) {
					this->printFitParameters(*iter, fout);
				}
			}
		}
		fout << "\\hline \n\\end{tabular}" << std::endl << std::endl;
	}
}

void LauCPFitModel::checkInitFitParams()
{
	// Update the number of signal events to be total-sum(background events)
	this->updateSigEvents();

	// Check whether we want to have randomised initial fit parameters for the signal model
	if (this->useRandomInitFitPars() == kTRUE) {
		std::cout << "INFO in LauCPFitModel::checkInitFitParams : Setting random parameters for the signal model" << std::endl;
		this->randomiseInitFitPars();
	}
}

void LauCPFitModel::randomiseInitFitPars()
{
	// Only randomise those parameters that are not fixed!
	std::cout << "INFO in LauCPFitModel::randomiseInitFitPars : Randomising the initial fit magnitudes and phases of the components..." << std::endl;

	for (UInt_t i = 0; i < nSigComp_; i++) {
		coeffPars_[i]->randomiseInitValues();
	}
}

LauCPFitModel::LauGenInfo LauCPFitModel::eventsToGenerate()
{
	// Determine the number of events to generate for each hypothesis
	// If we're smearing then smear each one individually

	LauGenInfo nEvtsGen;

	// Signal
	Double_t evtWeight(1.0);
	Double_t nEvts = signalEvents_->genValue();
	if ( nEvts < 0.0 ) {
		evtWeight = -1.0;
		nEvts = TMath::Abs( nEvts );
	}
	Double_t asym(0.0);
	Double_t sigAsym(0.0);
	// need to include this as an alternative in case the DP isn't in the model
	if ( !this->useDP() || forceAsym_ ) {
		sigAsym = signalAsym_->genValue();
	} else {
		Double_t negRate = negSigModel_->getDPNorm();
		Double_t posRate = posSigModel_->getDPNorm();
		if (negRate+posRate>1e-30) {
			sigAsym = (negRate-posRate)/(negRate+posRate);
		}
	}
	asym = sigAsym;
	Int_t nPosEvts = static_cast<Int_t>((nEvts/2.0 * (1.0 - asym)) + 0.5);
	Int_t nNegEvts = static_cast<Int_t>((nEvts/2.0 * (1.0 + asym)) + 0.5);
	if (this->doPoissonSmearing()) {
		nNegEvts = LauRandom::randomFun()->Poisson(nNegEvts);
		nPosEvts = LauRandom::randomFun()->Poisson(nPosEvts);
	}
	nEvtsGen[std::make_pair("signal",-1)] = std::make_pair(nNegEvts,evtWeight);
	nEvtsGen[std::make_pair("signal",+1)] = std::make_pair(nPosEvts,evtWeight);

	// backgrounds
	const UInt_t nBkgnds = this->nBkgndClasses();
	for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
		const TString& bkgndClass = this->bkgndClassName(bkgndID);
		const LauParameter* evtsPar = bkgndEvents_[bkgndID];
		const LauParameter* asymPar = bkgndAsym_[bkgndID];
		evtWeight = 1.0;
		nEvts = TMath::FloorNint( evtsPar->genValue() );
		if ( nEvts < 0 ) {
			evtWeight = -1.0;
			nEvts = TMath::Abs( nEvts );
		}
		asym = asymPar->genValue();
		nPosEvts = static_cast<Int_t>((nEvts/2.0 * (1.0 - asym)) + 0.5);
		nNegEvts = static_cast<Int_t>((nEvts/2.0 * (1.0 + asym)) + 0.5);
		if (this->doPoissonSmearing()) {
			nNegEvts = LauRandom::randomFun()->Poisson(nNegEvts);
			nPosEvts = LauRandom::randomFun()->Poisson(nPosEvts);
		}
		nEvtsGen[std::make_pair(bkgndClass,-1)] = std::make_pair(nNegEvts,evtWeight);
		nEvtsGen[std::make_pair(bkgndClass,+1)] = std::make_pair(nPosEvts,evtWeight);
	}

	std::cout << "INFO in LauCPFitModel::eventsToGenerate : Generating toy MC with:" << std::endl;
	std::cout << "                                        : Signal asymmetry  = " << sigAsym << " and number of signal events = " << signalEvents_->genValue() << std::endl;
	for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
		const TString& bkgndClass = this->bkgndClassName(bkgndID);
		const LauParameter* evtsPar = bkgndEvents_[bkgndID];
		const LauParameter* asymPar = bkgndAsym_[bkgndID];
		std::cout << "                                        : " << bkgndClass << " asymmetry  = " << asymPar->genValue() << " and number of " << bkgndClass << " events = " << evtsPar->genValue() << std::endl;
	}

	return nEvtsGen;
}

Bool_t LauCPFitModel::genExpt()
{
	// Routine to generate toy Monte Carlo events according to the various models we have defined.

	// Determine the number of events to generate for each hypothesis
	LauGenInfo nEvts = this->eventsToGenerate();

	Bool_t genOK(kTRUE);
	Int_t evtNum(0);

	const UInt_t nBkgnds = this->nBkgndClasses();
	std::vector<TString> bkgndClassNames(nBkgnds);
	std::vector<TString> bkgndClassNamesGen(nBkgnds);
	for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
		TString name( this->bkgndClassName(iBkgnd) );
		bkgndClassNames[iBkgnd] = name;
		bkgndClassNamesGen[iBkgnd] = "gen"+name;
	}

	const Bool_t storeSCFTruthInfo = ( useSCF_ || ( this->enableEmbedding() &&
				negSignalTree_ != 0 && negSignalTree_->haveBranch("mcMatch") &&
				posSignalTree_ != 0 && posSignalTree_->haveBranch("mcMatch") ) );

	// Loop over the hypotheses and generate the requested number of events for each one
	for (LauGenInfo::const_iterator iter = nEvts.begin(); iter != nEvts.end(); ++iter) {

		const TString& type(iter->first.first);
		curEvtCharge_ = iter->first.second;
		Double_t evtWeight( iter->second.second );
		Int_t nEvtsGen( iter->second.first );

		for (Int_t iEvt(0); iEvt<nEvtsGen; ++iEvt) {

			this->setGenNtupleDoubleBranchValue( "evtWeight", evtWeight );
			this->setGenNtupleDoubleBranchValue( "efficiency", 1.0 );

			if (type == "signal") {
				this->setGenNtupleIntegerBranchValue("genSig",1);
				for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
					this->setGenNtupleIntegerBranchValue( bkgndClassNamesGen[iBkgnd], 0 );
				}
				genOK = this->generateSignalEvent();
				if ( curEvtCharge_ > 0 ){ 
					this->setGenNtupleDoubleBranchValue( "efficiency", posSigModel_->getEvtEff() );
				} else {
					this->setGenNtupleDoubleBranchValue( "efficiency", negSigModel_->getEvtEff() );
				}

			} else {
				this->setGenNtupleIntegerBranchValue("genSig",0);
				if ( storeSCFTruthInfo ) {
					this->setGenNtupleIntegerBranchValue("genTMSig",0);
					this->setGenNtupleIntegerBranchValue("genSCFSig",0);
				}
				UInt_t bkgndID(0);
				for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
					Int_t gen(0);
					if ( bkgndClassNames[iBkgnd] == type ) {
						gen = 1;
						bkgndID = iBkgnd;
					}
					this->setGenNtupleIntegerBranchValue( bkgndClassNamesGen[iBkgnd], gen );
				}
				genOK = this->generateBkgndEvent(bkgndID);
			}
			if (!genOK) {
				// If there was a problem with the generation then break out and return.
				// The problem model will have adjusted itself so that all should be OK next time.
				break;
			}
			if (this->useDP() == kTRUE) {
				this->setDPBranchValues();
			}

			// Store the event charge
			this->setGenNtupleIntegerBranchValue(tagVarName_,curEvtCharge_);

			// Store the event number (within this experiment)
			// and then increment it
			this->setGenNtupleIntegerBranchValue("iEvtWithinExpt",evtNum);
			++evtNum;

			this->fillGenNtupleBranches();
			if (iEvt%500 == 0) {std::cout << "INFO in LauCPFitModel::genExpt : Generated event number " << iEvt << " out of " << nEvtsGen << " " << type << " events." << std::endl;}
		}

		if (!genOK) {
			break;
		}
	}

	if (this->useDP() && genOK) {

		negSigModel_->checkToyMC(kTRUE,kTRUE);
		posSigModel_->checkToyMC(kTRUE,kTRUE);

		// Get the fit fractions if they're to be written into the latex table
		if (this->writeLatexTable()) {
			LauParArray negFitFrac = negSigModel_->getFitFractions();
			if (negFitFrac.size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::genExpt : Fit Fraction array of unexpected dimension: " << negFitFrac.size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
			for (UInt_t i(0); i<nSigComp_; ++i) {
				if (negFitFrac[i].size() != nSigComp_) {
					std::cerr << "ERROR in LauCPFitModel::genExpt : Fit Fraction array of unexpected dimension: " << negFitFrac[i].size() << std::endl;
					gSystem->Exit(EXIT_FAILURE);
				}
			}
			LauParArray posFitFrac = posSigModel_->getFitFractions();
			if (posFitFrac.size() != nSigComp_) {
				std::cerr << "ERROR in LauCPFitModel::genExpt : Fit Fraction array of unexpected dimension: " << posFitFrac.size() << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
			for (UInt_t i(0); i<nSigComp_; ++i) {
				if (posFitFrac[i].size() != nSigComp_) {
					std::cerr << "ERROR in LauCPFitModel::genExpt : Fit Fraction array of unexpected dimension: " << posFitFrac[i].size() << std::endl;
					gSystem->Exit(EXIT_FAILURE);
				}
			}

			for (UInt_t i(0); i<nSigComp_; ++i) {
				for (UInt_t j(i); j<nSigComp_; ++j) {
					negFitFrac_[i][j].value(negFitFrac[i][j].value());
					posFitFrac_[i][j].value(posFitFrac[i][j].value());
				}
			}
			negMeanEff_.value(negSigModel_->getMeanEff().value());
			posMeanEff_.value(posSigModel_->getMeanEff().value());
			negDPRate_.value(negSigModel_->getDPRate().value());
			posDPRate_.value(posSigModel_->getDPRate().value());
		}
	}

	// If we're reusing embedded events or if the generation is being
	// reset then clear the lists of used events
	if (reuseSignal_ || !genOK) {
		if (negSignalTree_) {
			negSignalTree_->clearUsedList();
		}
		if (posSignalTree_) {
			posSignalTree_->clearUsedList();
		}
	}
	for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
		LauEmbeddedData* data = negBkgndTree_[bkgndID];
		if (reuseBkgnd_[bkgndID] || !genOK) {
			if (data) {
				data->clearUsedList();
			}
		}
	}
	for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
		LauEmbeddedData* data = posBkgndTree_[bkgndID];
		if (reuseBkgnd_[bkgndID] || !genOK) {
			if (data) {
				data->clearUsedList();
			}
		}
	}

	return genOK;
}

Bool_t LauCPFitModel::generateSignalEvent()
{
	// Generate signal event
	Bool_t genOK(kTRUE);
	Bool_t genSCF(kFALSE);

	LauAbsDPDynamics* model(0);
	LauKinematics* kinematics(0);
	LauEmbeddedData* embeddedData(0);
	LauPdfList* sigPdfs(0);
	LauPdfList* scfPdfs(0);

	Bool_t doReweighting(kFALSE);

	if (curEvtCharge_<0) {
		model = negSigModel_;
		kinematics = negKinematics_;
		sigPdfs = &negSignalPdfs_;
		scfPdfs = &negScfPdfs_;
		if (this->enableEmbedding()) {
			embeddedData = negSignalTree_;
			doReweighting = useNegReweighting_;
		}
	} else {
		model = posSigModel_;
		kinematics = posKinematics_;
		if ( tagged_ ) {
			sigPdfs = &posSignalPdfs_;
			scfPdfs = &posScfPdfs_;
		} else {
			sigPdfs = &negSignalPdfs_;
			scfPdfs = &negScfPdfs_;
		}
		if (this->enableEmbedding()) {
			embeddedData = posSignalTree_;
			doReweighting = usePosReweighting_;
		}
	}

	if (this->useDP()) {
		if (embeddedData) {
			if (doReweighting) {
				// Select a (random) event from the generated data. Then store the
				// reconstructed DP co-ords, together with other pdf information,
				// as the embedded data.
				genOK = embeddedData->getReweightedEvent(model);
			} else {
				// Just get the information of a (randomly) selected event in the 
				// embedded data
				embeddedData->getEmbeddedEvent(kinematics);
			}
			genSCF = this->storeSignalMCMatch( embeddedData );
		} else {
			genOK = model->generate();
			if ( genOK && useSCF_ ) {
				Double_t frac(0.0);
				if ( useSCFHist_ ) {
					frac = scfFracHist_->calcEfficiency( kinematics );
				} else {
					frac = scfFrac_.genValue();
				}
				if ( frac < LauRandom::randomFun()->Rndm() ) {
					this->setGenNtupleIntegerBranchValue("genTMSig",1);
					this->setGenNtupleIntegerBranchValue("genSCFSig",0);
					genSCF = kFALSE;
				} else {
					this->setGenNtupleIntegerBranchValue("genTMSig",0);
					this->setGenNtupleIntegerBranchValue("genSCFSig",1);
					genSCF = kTRUE;

					// Optionally smear the DP position
					// of the SCF event
					if ( scfMap_ != 0 ) {
						Double_t xCoord(0.0), yCoord(0.0);
						if ( kinematics->squareDP() ) {
							xCoord = kinematics->getmPrime();
							yCoord = kinematics->getThetaPrime();
						} else {
							xCoord = kinematics->getm13Sq();
							yCoord = kinematics->getm23Sq();
						}

						// Find the bin number where this event is generated
						Int_t binNo = scfMap_->binNumber( xCoord, yCoord );

						// Retrieve the migration histogram
						TH2* histo = scfMap_->trueHist( binNo );

						LauAbsEffModel * effModel = model->getEffModel();
						do {
							// Get a random point from the histogram
							histo->GetRandom2( xCoord, yCoord );

							// Update the kinematics
							if ( kinematics->squareDP() ) {
								kinematics->updateSqDPKinematics( xCoord, yCoord );
							} else {
								kinematics->updateKinematics( xCoord, yCoord );
							}
						} while ( ! effModel->passVeto( kinematics ) );
					}
				}
			}
		}
	} else {
		if (embeddedData) {
			embeddedData->getEmbeddedEvent(0);
			genSCF = this->storeSignalMCMatch( embeddedData );
		} else if ( useSCF_ ) {
			Double_t frac = scfFrac_.genValue();
			if ( frac < LauRandom::randomFun()->Rndm() ) {
				this->setGenNtupleIntegerBranchValue("genTMSig",1);
				this->setGenNtupleIntegerBranchValue("genSCFSig",0);
				genSCF = kFALSE;
			} else {
				this->setGenNtupleIntegerBranchValue("genTMSig",0);
				this->setGenNtupleIntegerBranchValue("genSCFSig",1);
				genSCF = kTRUE;
			}
		}
	}
	if (genOK) {
		if ( useSCF_ ) {
			if ( genSCF ) {
				this->generateExtraPdfValues(scfPdfs, embeddedData);
			} else {
				this->generateExtraPdfValues(sigPdfs, embeddedData);
			}
		} else {
			this->generateExtraPdfValues(sigPdfs, embeddedData);
		}
	}
	// Check for problems with the embedding
	if (embeddedData && (embeddedData->nEvents() == embeddedData->nUsedEvents())) {
		std::cerr << "WARNING in LauCPFitModel::generateSignalEvent : Source of embedded signal events used up, clearing the list of used events." << std::endl;
		embeddedData->clearUsedList();
	}

	return genOK;
}

Bool_t LauCPFitModel::generateBkgndEvent(UInt_t bkgndID)
{
	// Generate Bkgnd event
	Bool_t genOK(kTRUE);

	LauAbsBkgndDPModel* model(0);
	LauEmbeddedData* embeddedData(0);
	LauPdfList* extraPdfs(0);
	LauKinematics* kinematics(0);

	if (curEvtCharge_<0) {
		model = negBkgndDPModels_[bkgndID];
		if (this->enableEmbedding()) {
			embeddedData = negBkgndTree_[bkgndID];
		}
		extraPdfs = &negBkgndPdfs_[bkgndID];
		kinematics = negKinematics_;
	} else {
		model = posBkgndDPModels_[bkgndID];
		if (this->enableEmbedding()) {
			embeddedData = posBkgndTree_[bkgndID];
		}
		if ( tagged_ ) {
			extraPdfs = &posBkgndPdfs_[bkgndID];
		} else {
			extraPdfs = &negBkgndPdfs_[bkgndID];
		}
		kinematics = posKinematics_;
	}

	if (this->useDP()) {
		if (embeddedData) {
			embeddedData->getEmbeddedEvent(kinematics);
		} else {
			if (model == 0) {
				const TString& bkgndClass = this->bkgndClassName(bkgndID);
				std::cerr << "ERROR in LauCPFitModel::generateBkgndEvent : Can't find the DP model for background class \"" << bkgndClass << "\"." << std::endl;
				gSystem->Exit(EXIT_FAILURE);
			}
			genOK = model->generate();
		}
	} else {
		if (embeddedData) {
			embeddedData->getEmbeddedEvent(0);
		}
	}
	if (genOK) {
		this->generateExtraPdfValues(extraPdfs, embeddedData);
	}

	// Check for problems with the embedding
	if (embeddedData && (embeddedData->nEvents() == embeddedData->nUsedEvents())) {
		const TString& bkgndClass = this->bkgndClassName(bkgndID);
		std::cerr << "WARNING in LauCPFitModel::generateBkgndEvent : Source of embedded " << bkgndClass << " events used up, clearing the list of used events." << std::endl;
		embeddedData->clearUsedList();
	}

	return genOK;
}

void LauCPFitModel::setupGenNtupleBranches()
{
	// Setup the required ntuple branches
	this->addGenNtupleDoubleBranch("evtWeight");
	this->addGenNtupleIntegerBranch("genSig");
	this->addGenNtupleDoubleBranch("efficiency");
	if ( useSCF_ || ( this->enableEmbedding() &&
				negSignalTree_ != 0 && negSignalTree_->haveBranch("mcMatch") &&
				posSignalTree_ != 0 && posSignalTree_->haveBranch("mcMatch") ) ) {
		this->addGenNtupleIntegerBranch("genTMSig");
		this->addGenNtupleIntegerBranch("genSCFSig");
	}
	const UInt_t nBkgnds = this->nBkgndClasses();
	for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
		TString name( this->bkgndClassName(iBkgnd) );
		name.Prepend("gen");
		this->addGenNtupleIntegerBranch(name);
	}
	this->addGenNtupleIntegerBranch("charge");
	if (this->useDP() == kTRUE) {
		this->addGenNtupleDoubleBranch("m12");
		this->addGenNtupleDoubleBranch("m23");
		this->addGenNtupleDoubleBranch("m13");
		this->addGenNtupleDoubleBranch("m12Sq");
		this->addGenNtupleDoubleBranch("m23Sq");
		this->addGenNtupleDoubleBranch("m13Sq");
		this->addGenNtupleDoubleBranch("cosHel12");
		this->addGenNtupleDoubleBranch("cosHel23");
		this->addGenNtupleDoubleBranch("cosHel13");
		if (negKinematics_->squareDP() && posKinematics_->squareDP()) {
			this->addGenNtupleDoubleBranch("mPrime");
			this->addGenNtupleDoubleBranch("thPrime");
		}
	}
	for (LauPdfList::const_iterator pdf_iter = negSignalPdfs_.begin(); pdf_iter != negSignalPdfs_.end(); ++pdf_iter) {
		std::vector<TString> varNames = (*pdf_iter)->varNames();
		for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
			if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
				this->addGenNtupleDoubleBranch( (*var_iter) );
			}
		}
	}
}

void LauCPFitModel::setDPBranchValues()
{
	LauKinematics* kinematics(0);
	if (curEvtCharge_<0) {
		kinematics = negKinematics_;
	} else {
		kinematics = posKinematics_;
	}

	// Store all the DP information
	this->setGenNtupleDoubleBranchValue("m12", kinematics->getm12());
	this->setGenNtupleDoubleBranchValue("m23", kinematics->getm23());
	this->setGenNtupleDoubleBranchValue("m13", kinematics->getm13());
	this->setGenNtupleDoubleBranchValue("m12Sq", kinematics->getm12Sq());
	this->setGenNtupleDoubleBranchValue("m23Sq", kinematics->getm23Sq());
	this->setGenNtupleDoubleBranchValue("m13Sq", kinematics->getm13Sq());
	this->setGenNtupleDoubleBranchValue("cosHel12", kinematics->getc12());
	this->setGenNtupleDoubleBranchValue("cosHel23", kinematics->getc23());
	this->setGenNtupleDoubleBranchValue("cosHel13", kinematics->getc13());
	if (kinematics->squareDP()) {
		this->setGenNtupleDoubleBranchValue("mPrime", kinematics->getmPrime());
		this->setGenNtupleDoubleBranchValue("thPrime", kinematics->getThetaPrime());
	}
}

void LauCPFitModel::generateExtraPdfValues(LauPdfList* extraPdfs, LauEmbeddedData* embeddedData)
{
	LauKinematics* kinematics(0);
	if (curEvtCharge_<0) {
		kinematics = negKinematics_;
	} else {
		kinematics = posKinematics_;
	}

	if (!extraPdfs) {
		std::cerr << "ERROR in LauCPFitModel::generateExtraPdfValues : Null pointer to PDF list." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if (extraPdfs->empty()) {
		//std::cerr << "WARNING in LauCPFitModel::generateExtraPdfValues : PDF list is empty." << std::endl;
		return;
	}

	// Generate from the extra PDFs
	for (LauPdfList::iterator pdf_iter = extraPdfs->begin(); pdf_iter != extraPdfs->end(); ++pdf_iter) {
		LauFitData genValues;
		if (embeddedData) {
			genValues = embeddedData->getValues( (*pdf_iter)->varNames() );
		} else {
			genValues = (*pdf_iter)->generate(kinematics);
		}
		for ( LauFitData::const_iterator var_iter = genValues.begin(); var_iter != genValues.end(); ++var_iter ) {
			TString varName = var_iter->first;
			if ( varName != "m13Sq" && varName != "m23Sq" ) {
				Double_t value = var_iter->second;
				this->setGenNtupleDoubleBranchValue(varName,value);
			}
		}
	}
}

Bool_t LauCPFitModel::storeSignalMCMatch(LauEmbeddedData* embeddedData)
{
	// Default to TM
	Bool_t genSCF(kFALSE);
	Int_t match(1);

	// Check that we have a valid pointer and that embedded data has
	// the mcMatch branch.  If so then get the match value.
	if ( embeddedData && embeddedData->haveBranch("mcMatch") ) {
		match = TMath::Nint( embeddedData->getValue("mcMatch") );
	}

	// Set the variables accordingly.
	if (match) {
		this->setGenNtupleIntegerBranchValue("genTMSig",1);
		this->setGenNtupleIntegerBranchValue("genSCFSig",0);
		genSCF = kFALSE;
	} else {
		this->setGenNtupleIntegerBranchValue("genTMSig",0);
		this->setGenNtupleIntegerBranchValue("genSCFSig",1);
		genSCF = kTRUE;
	}

	return genSCF;
}

void LauCPFitModel::propagateParUpdates()
{
	// Update the signal parameters and then the total normalisation for the signal likelihood
	if (this->useDP() == kTRUE) {
		this->updateCoeffs();
		negSigModel_->updateCoeffs(negCoeffs_);
		posSigModel_->updateCoeffs(posCoeffs_);
	}

	// Update the signal fraction from the background fractions if not doing an extended fit
	if ( !this->doEMLFit() && !signalEvents_->fixed() ) {
		this->updateSigEvents();
	}
}

void LauCPFitModel::updateSigEvents()
{
	// The background parameters will have been set from Minuit.
	// We need to update the signal events using these.
	Double_t nTotEvts = this->eventsPerExpt();

	signalEvents_->range(-2.0*nTotEvts,2.0*nTotEvts);
	for (LauBkgndYieldList::iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
		(*iter)->range(-2.0*nTotEvts,2.0*nTotEvts);
	}

	if (signalEvents_->fixed()) {
		return;
	}

	// Subtract background events (if any) from signal.
	Double_t signalEvents = nTotEvts;
	if (usingBkgnd_ == kTRUE) {
		for (LauBkgndYieldList::const_iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
			signalEvents -= (*iter)->value();
		}
	}
	signalEvents_->value(signalEvents);
}

void LauCPFitModel::cacheInputFitVars()
{
	// Fill the internal data trees of the signal and background models.
	// Note that we store the events of both charges in both the
	// negative and the positive models. It's only later, at the stage
	// when the likelihood is being calculated, that we separate them.

	LauFitDataTree* inputFitData = this->fitData();

	// First the Dalitz plot variables (m_ij^2)
	if (this->useDP() == kTRUE) {

		// need to append SCF smearing bins before caching DP amplitudes
		if ( scfMap_ != 0 ) {
			this->appendBinCentres( inputFitData );
		}

		negSigModel_->fillDataTree(*inputFitData);
		posSigModel_->fillDataTree(*inputFitData);

		if (usingBkgnd_ == kTRUE) {
			for (LauBkgndDPModelList::iterator iter = negBkgndDPModels_.begin(); iter != negBkgndDPModels_.end(); ++iter) {
				(*iter)->fillDataTree(*inputFitData);
			}
			for (LauBkgndDPModelList::iterator iter = posBkgndDPModels_.begin(); iter != posBkgndDPModels_.end(); ++iter) {
				(*iter)->fillDataTree(*inputFitData);
			}
		}
	}

	// ...and then the extra PDFs
	this->cacheInfo(negSignalPdfs_, *inputFitData);
	this->cacheInfo(negScfPdfs_, *inputFitData);
	for (LauBkgndPdfsList::iterator iter = negBkgndPdfs_.begin(); iter != negBkgndPdfs_.end(); ++iter) {
		this->cacheInfo((*iter), *inputFitData);
	}
	if ( tagged_ ) {
		this->cacheInfo(posSignalPdfs_, *inputFitData);
		this->cacheInfo(posScfPdfs_, *inputFitData);
		for (LauBkgndPdfsList::iterator iter = posBkgndPdfs_.begin(); iter != posBkgndPdfs_.end(); ++iter) {
			this->cacheInfo((*iter), *inputFitData);
		}
	}

	// the SCF fractions and jacobians
	if ( useSCF_ && useSCFHist_ ) {
		if ( !inputFitData->haveBranch( "m13Sq" )  || !inputFitData->haveBranch( "m23Sq" ) ) {
			std::cerr << "ERROR in LauCPFitModel::cacheInputFitVars : Input data does not contain DP branches and so can't cache the SCF fraction." << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}

		UInt_t nEvents = inputFitData->nEvents();
		recoSCFFracs_.clear();
		recoSCFFracs_.reserve( nEvents );
		if ( negKinematics_->squareDP() ) {
			recoJacobians_.clear();
			recoJacobians_.reserve( nEvents );
		}
		for (UInt_t iEvt = 0; iEvt < nEvents; iEvt++) {
			const LauFitData& dataValues = inputFitData->getData(iEvt);
			LauFitData::const_iterator m13_iter = dataValues.find("m13Sq");
			LauFitData::const_iterator m23_iter = dataValues.find("m23Sq");
			negKinematics_->updateKinematics( m13_iter->second, m23_iter->second );
			Double_t scfFrac = scfFracHist_->calcEfficiency( negKinematics_ );
			recoSCFFracs_.push_back( scfFrac );
			if ( negKinematics_->squareDP() ) {
				recoJacobians_.push_back( negKinematics_->calcSqDPJacobian() );
			}
		}
	}

	// finally cache the event charge
	evtCharges_.clear();
	if ( tagged_ ) {
		if ( !inputFitData->haveBranch( tagVarName_ ) ) {
			std::cerr << "ERROR in LauCPFitModel::cacheInputFitVars : Input data does not contain branch \"" << tagVarName_ << "\"." << std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
		UInt_t nEvents = inputFitData->nEvents();
		evtCharges_.reserve( nEvents );
		for (UInt_t iEvt = 0; iEvt < nEvents; iEvt++) {
			const LauFitData& dataValues = inputFitData->getData(iEvt);
			LauFitData::const_iterator iter = dataValues.find( tagVarName_ );
			curEvtCharge_ = static_cast<Int_t>( iter->second );
			evtCharges_.push_back( curEvtCharge_ );
		}
	}
}

void LauCPFitModel::appendBinCentres( LauFitDataTree* inputData )
{
	// We'll be caching the DP amplitudes and efficiencies of the centres of the true bins.
	// To do so, we attach some fake points at the end of inputData, the number of the entry
	// minus the total number of events corresponding to the number of the histogram for that
	// given true bin in the LauScfMap object. (What this means is that when Laura is provided with
	// the LauScfMap object by the user, it's the latter who has to make sure that it contains the
	// right number of histograms and in exactly the right order!) 

	// Get the x and y co-ordinates of the bin centres
	std::vector<Double_t> binCentresXCoords;
	std::vector<Double_t> binCentresYCoords;
	scfMap_->listBinCentres(binCentresXCoords, binCentresYCoords);

	// The SCF histograms could be in square Dalitz plot histograms.
	// The dynamics takes normal Dalitz plot coords, so we might have to convert them back.
	Bool_t sqDP = negKinematics_->squareDP();
	UInt_t nBins = binCentresXCoords.size();
	fakeSCFFracs_.clear();
	fakeSCFFracs_.reserve( nBins );
	if ( sqDP ) {
		fakeJacobians_.clear();
		fakeJacobians_.reserve( nBins );
	}

	for (UInt_t iBin = 0; iBin < nBins; ++iBin) {

		if ( sqDP ) {
			negKinematics_->updateSqDPKinematics(binCentresXCoords[iBin],binCentresYCoords[iBin]);
			binCentresXCoords[iBin] = negKinematics_->getm13Sq();
			binCentresYCoords[iBin] = negKinematics_->getm23Sq();
			fakeJacobians_.push_back( negKinematics_->calcSqDPJacobian() );
		} else {
			negKinematics_->updateKinematics(binCentresXCoords[iBin],binCentresYCoords[iBin]);
		}

		fakeSCFFracs_.push_back( scfFracHist_->calcEfficiency( negKinematics_ ) );
	}

	// Set up inputFitVars_ object to hold the fake events
	inputData->appendFakePoints(binCentresXCoords,binCentresYCoords);
}

Double_t LauCPFitModel::getTotEvtLikelihood(UInt_t iEvt)
{
	// Find out whether we have B- or B+
	if ( tagged_ ) {
		curEvtCharge_ = evtCharges_[iEvt];

		// check that the charge is either +1 or -1
		if (TMath::Abs(curEvtCharge_)!=1) {
			std::cerr << "ERROR in LauCPFitModel::getTotEvtLikelihood : Charge/tag not accepted value: " << curEvtCharge_ << std::endl;
			if (curEvtCharge_>0) {
				curEvtCharge_ = +1;
			} else {
				curEvtCharge_ = -1;
			}
			std::cerr << "                                            : Making it: " << curEvtCharge_ << "." << std::endl;
		}
	}

	// Get the DP likelihood for signal and backgrounds
	this->getEvtDPLikelihood(iEvt);

	// Get the combined extra PDFs likelihood for signal and backgrounds
	this->getEvtExtraLikelihoods(iEvt);

	// If appropriate, combine the TM and SCF likelihoods
	Double_t sigLike = sigDPLike_ * sigExtraLike_;
	if ( useSCF_ ) {
		Double_t scfFrac(0.0);
		if (useSCFHist_) {
			scfFrac = recoSCFFracs_[iEvt];
		} else {
			scfFrac = scfFrac_.value();
		}
		sigLike *= (1.0 - scfFrac);
		if ( (scfMap_ != 0) && (this->useDP() == kTRUE) ) {
			// if we're smearing the SCF DP PDF then the SCF frac
			// is already included in the SCF DP likelihood
			sigLike += (scfDPLike_ * scfExtraLike_);
		} else {
			sigLike += (scfFrac * scfDPLike_ * scfExtraLike_);
		}
	}

	// Get the correct event fractions depending on the charge
	// Signal asymmetry is built into the DP model... but when the DP
	// isn't in the fit we need an explicit parameter
	Double_t signalEvents = signalEvents_->value() * 0.5;
	if (this->useDP() == kFALSE) {
		signalEvents *= (1.0 - curEvtCharge_ * signalAsym_->value());
	}

	// Construct the total event likelihood
	Double_t likelihood(0.0);
	if (usingBkgnd_) {
		likelihood = sigLike*signalEvents;
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
			Double_t bkgndEvents  = bkgndEvents_[bkgndID]->value() * 0.5 * (1.0 - curEvtCharge_ * bkgndAsym_[bkgndID]->value());
			likelihood += bkgndEvents*bkgndDPLike_[bkgndID]*bkgndExtraLike_[bkgndID];
		}
	} else {
		likelihood = sigLike*0.5;
	}
	return likelihood;
}

Double_t LauCPFitModel::getEventSum() const
{
	Double_t eventSum(0.0);
	eventSum += signalEvents_->value();
	if (usingBkgnd_) {
		for (LauBkgndYieldList::const_iterator iter = bkgndEvents_.begin(); iter != bkgndEvents_.end(); ++iter) {
			eventSum += (*iter)->value();
		}
	}
	return eventSum;
}

void LauCPFitModel::getEvtDPLikelihood(UInt_t iEvt)
{
	// Function to return the signal and background likelihoods for the
	// Dalitz plot for the given event evtNo.

	if ( ! this->useDP() ) {
		// There's always going to be a term in the likelihood for the
		// signal, so we'd better not zero it.
		sigDPLike_ = 1.0;
		scfDPLike_ = 1.0;

		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
			if (usingBkgnd_ == kTRUE) {
				bkgndDPLike_[bkgndID] = 1.0;
			} else {
				bkgndDPLike_[bkgndID] = 0.0;
			}
		}

		return;
	}

	const UInt_t nBkgnds = this->nBkgndClasses();
	if ( tagged_ ) {
		if (curEvtCharge_==+1) {
			posSigModel_->calcLikelihoodInfo(iEvt);
			sigDPLike_ = posSigModel_->getEvtDPAmp().abs2();
			sigDPLike_ *= posSigModel_->getEvtEff();

			for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
				if (usingBkgnd_ == kTRUE) {
					bkgndDPLike_[bkgndID] = posBkgndDPModels_[bkgndID]->getLikelihood(iEvt);
				} else {
					bkgndDPLike_[bkgndID] = 0.0;
				}
			}
		} else {
			negSigModel_->calcLikelihoodInfo(iEvt);
			sigDPLike_ = negSigModel_->getEvtDPAmp().abs2();
			sigDPLike_ *= negSigModel_->getEvtEff();

			for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
				if (usingBkgnd_ == kTRUE) {
					bkgndDPLike_[bkgndID] = negBkgndDPModels_[bkgndID]->getLikelihood(iEvt);
				} else {
					bkgndDPLike_[bkgndID] = 0.0;
				}
			}
		}
	} else {
		posSigModel_->calcLikelihoodInfo(iEvt);
		negSigModel_->calcLikelihoodInfo(iEvt);

		sigDPLike_ = 0.5 * ( posSigModel_->getEvtDPAmp().abs2() * posSigModel_->getEvtEff() +
				negSigModel_->getEvtDPAmp().abs2() * negSigModel_->getEvtEff() );

		for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
			if (usingBkgnd_ == kTRUE) {
				bkgndDPLike_[bkgndID] = 0.5 * ( posBkgndDPModels_[bkgndID]->getLikelihood(iEvt) +
						negBkgndDPModels_[bkgndID]->getLikelihood(iEvt) );
			} else {
				bkgndDPLike_[bkgndID] = 0.0;
			}
		}
	}

	if ( useSCF_ == kTRUE ) {
		if ( scfMap_ == 0 ) {
			// we're not smearing the SCF DP position
			// so the likelihood is the same as the TM
			scfDPLike_ = sigDPLike_;
		} else {
			// calculate the smeared SCF DP likelihood
			scfDPLike_ = this->getEvtSCFDPLikelihood(iEvt);
		}
	}

	// Calculate the signal normalisation
	// NB the 2.0 is there so that the 0.5 factor is applied to
	// signal and background in the same place otherwise you get
	// normalisation problems when you switch off the DP in the fit
	Double_t norm = negSigModel_->getDPNorm() + posSigModel_->getDPNorm();
	sigDPLike_ *= 2.0/norm;
	scfDPLike_ *= 2.0/norm;
}

Double_t LauCPFitModel::getEvtSCFDPLikelihood(UInt_t iEvt)
{
	Double_t scfDPLike(0.0);

	Double_t recoJacobian(1.0);
	Double_t xCoord(0.0);
	Double_t yCoord(0.0);

	Bool_t squareDP = negKinematics_->squareDP();
	if ( squareDP ) {
		xCoord = negSigModel_->getEvtmPrime();
		yCoord = negSigModel_->getEvtthPrime();
		recoJacobian = recoJacobians_[iEvt];
	} else {
		xCoord = negSigModel_->getEvtm13Sq();
		yCoord = negSigModel_->getEvtm23Sq();
	}

	// Find the bin that our reco event falls in
	Int_t recoBin = scfMap_->binNumber( xCoord, yCoord );

	// Find out which true Bins contribute to the given reco bin
	const std::vector<Int_t>* trueBins = scfMap_->trueBins(recoBin);

	const Int_t nDataEvents = this->eventsPerExpt();

	// Loop over the true bins
	for (std::vector<Int_t>::const_iterator iter = trueBins->begin(); iter != trueBins->end(); ++iter)
	{
		Int_t trueBin = (*iter);

		// prob of a true event in the given true bin migrating to the reco bin
		Double_t pRecoGivenTrue =  scfMap_->prob( recoBin, trueBin );
		Double_t pTrue(0.0);

		// We've cached the DP amplitudes and the efficiency for the
		// true bin centres, just after the data points
		if ( tagged_ ) {
			LauAbsDPDynamics* sigModel(0);
			if (curEvtCharge_<0) {
				sigModel = negSigModel_;
			} else {
				sigModel = posSigModel_;
			}

			sigModel->calcLikelihoodInfo( nDataEvents + trueBin );

			pTrue = sigModel->getEvtDPAmp().abs2() * sigModel->getEvtEff();
		} else {
			posSigModel_->calcLikelihoodInfo( nDataEvents + trueBin );
			negSigModel_->calcLikelihoodInfo( nDataEvents + trueBin );

			pTrue = 0.5 * ( posSigModel_->getEvtDPAmp().abs2() * posSigModel_->getEvtEff() +
					negSigModel_->getEvtDPAmp().abs2() * negSigModel_->getEvtEff() );
		}

		// Get the cached SCF fraction (and jacobian if we're using the square DP)
		Double_t scfFraction = fakeSCFFracs_[ trueBin ];
		Double_t jacobian(1.0);
		if ( squareDP ) {
			jacobian = fakeJacobians_[ trueBin ];
		}

		scfDPLike += pTrue * jacobian * scfFraction * pRecoGivenTrue;
	}

	// Divide by the reco jacobian
	scfDPLike /= recoJacobian;

	return scfDPLike;
}

void LauCPFitModel::getEvtExtraLikelihoods(UInt_t iEvt)
{
	// Function to return the signal and background likelihoods for the
	// extra variables for the given event evtNo.

	sigExtraLike_ = 1.0;

	const UInt_t nBkgnds = this->nBkgndClasses();

	if ( ! tagged_  || curEvtCharge_ < 0 ) {
		sigExtraLike_ = this->prodPdfValue( negSignalPdfs_, iEvt );

		if (useSCF_) {
			scfExtraLike_ = this->prodPdfValue( negScfPdfs_, iEvt );
		}

		for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
			if (usingBkgnd_) {
				bkgndExtraLike_[bkgndID] = this->prodPdfValue( negBkgndPdfs_[bkgndID], iEvt );
			} else {
				bkgndExtraLike_[bkgndID] = 0.0;
			}
		}
	} else {
		sigExtraLike_ = this->prodPdfValue( posSignalPdfs_, iEvt );

		if (useSCF_) {
			scfExtraLike_ = this->prodPdfValue( posScfPdfs_, iEvt );
		}

		for ( UInt_t bkgndID(0); bkgndID < nBkgnds; ++bkgndID ) {
			if (usingBkgnd_) {
				bkgndExtraLike_[bkgndID] = this->prodPdfValue( posBkgndPdfs_[bkgndID], iEvt );
			} else {
				bkgndExtraLike_[bkgndID] = 0.0;
			}
		}
	}
}

void LauCPFitModel::updateCoeffs() 
{
	negCoeffs_.clear(); posCoeffs_.clear();
	negCoeffs_.reserve(nSigComp_); posCoeffs_.reserve(nSigComp_);
	for (UInt_t i = 0; i < nSigComp_; i++) {
		negCoeffs_.push_back(coeffPars_[i]->antiparticleCoeff());
		posCoeffs_.push_back(coeffPars_[i]->particleCoeff());
	}
}

void LauCPFitModel::setupSPlotNtupleBranches()
{
	// add branches for storing the experiment number and the number of
	// the event within the current experiment
	this->addSPlotNtupleIntegerBranch("iExpt");
	this->addSPlotNtupleIntegerBranch("iEvtWithinExpt");

	// Store the efficiency of the event (for inclusive BF calculations).
	if (this->storeDPEff()) {
		this->addSPlotNtupleDoubleBranch("efficiency");
		if ( negSigModel_->usingScfModel() && posSigModel_->usingScfModel() ) {
			this->addSPlotNtupleDoubleBranch("scffraction");
		}
	}

	// Store the total event likelihood for each species.
	if (useSCF_) {
		this->addSPlotNtupleDoubleBranch("sigTMTotalLike");
		this->addSPlotNtupleDoubleBranch("sigSCFTotalLike");
		this->addSPlotNtupleDoubleBranch("sigSCFFrac");
	} else {
		this->addSPlotNtupleDoubleBranch("sigTotalLike");
	}
	if (usingBkgnd_) {
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
			TString name( this->bkgndClassName(iBkgnd) );
			name += "TotalLike";
			this->addSPlotNtupleDoubleBranch(name);
		}
	}

	// Store the DP likelihoods
	if (this->useDP()) {
		if (useSCF_) {
			this->addSPlotNtupleDoubleBranch("sigTMDPLike");
			this->addSPlotNtupleDoubleBranch("sigSCFDPLike");
		} else {
			this->addSPlotNtupleDoubleBranch("sigDPLike");
		}
		if (usingBkgnd_) {
			const UInt_t nBkgnds = this->nBkgndClasses();
			for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
				TString name( this->bkgndClassName(iBkgnd) );
				name += "DPLike";
				this->addSPlotNtupleDoubleBranch(name);
			}
		}
	}

	// Store the likelihoods for each extra PDF
	if (useSCF_) {
		this->addSPlotNtupleBranches(&negSignalPdfs_, "sigTM");
		this->addSPlotNtupleBranches(&negScfPdfs_, "sigSCF");
	} else {
		this->addSPlotNtupleBranches(&negSignalPdfs_, "sig");
	}
	if (usingBkgnd_) {
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
			const TString& bkgndClass = this->bkgndClassName(iBkgnd);
			const LauPdfList* pdfList = &(negBkgndPdfs_[iBkgnd]);
			this->addSPlotNtupleBranches(pdfList, bkgndClass);
		}
	}
}

void LauCPFitModel::addSPlotNtupleBranches(const LauPdfList* extraPdfs, const TString& prefix)
{
	if (extraPdfs) {
		// Loop through each of the PDFs
		for (LauPdfList::const_iterator pdf_iter = extraPdfs->begin(); pdf_iter != extraPdfs->end(); ++pdf_iter) {

			// Count the number of input variables that are not
			// DP variables (used in the case where there is DP
			// dependence for e.g. MVA)
			UInt_t nVars(0);
			std::vector<TString> varNames = (*pdf_iter)->varNames();
			for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
				if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
					++nVars;
				}
			}

			if ( nVars == 1 ) {
				// If the PDF only has one variable then
				// simply add one branch for that variable
				TString varName = (*pdf_iter)->varName();
				TString name(prefix);
				name += varName;
				name += "Like";
				this->addSPlotNtupleDoubleBranch(name);
			} else if ( nVars == 2 ) {
				// If the PDF has two variables then we
				// need a branch for them both together and
				// branches for each
				TString allVars("");
				for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
					allVars += (*var_iter);
					TString name(prefix);
					name += (*var_iter);
					name += "Like";
					this->addSPlotNtupleDoubleBranch(name);
				}
				TString name(prefix);
				name += allVars;
				name += "Like";
				this->addSPlotNtupleDoubleBranch(name);
			} else {
				std::cerr << "WARNING in LauCPFitModel::addSPlotNtupleBranches : Can't yet deal with 3D PDFs." << std::endl;
			}
		}
	}
}

Double_t LauCPFitModel::setSPlotNtupleBranchValues(LauPdfList* extraPdfs, const TString& prefix, UInt_t iEvt)
{
	// Store the PDF value for each variable in the list
	Double_t totalLike(1.0);
	Double_t extraLike(0.0);
	if (extraPdfs) {
		for (LauPdfList::iterator pdf_iter = extraPdfs->begin(); pdf_iter != extraPdfs->end(); ++pdf_iter) {

			// calculate the likelihood for this event
			(*pdf_iter)->calcLikelihoodInfo(iEvt);
			extraLike = (*pdf_iter)->getLikelihood();
			totalLike *= extraLike;

			// Count the number of input variables that are not
			// DP variables (used in the case where there is DP
			// dependence for e.g. MVA)
			UInt_t nVars(0);
			std::vector<TString> varNames = (*pdf_iter)->varNames();
			for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
				if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
					++nVars;
				}
			}

			if ( nVars == 1 ) {
				// If the PDF only has one variable then
				// simply store the value for that variable
				TString varName = (*pdf_iter)->varName();
				TString name(prefix);
				name += varName;
				name += "Like";
				this->setSPlotNtupleDoubleBranchValue(name, extraLike);
			} else if ( nVars == 2 ) {
				// If the PDF has two variables then we
				// store the value for them both together
				// and for each on their own
				TString allVars("");
				for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
					allVars += (*var_iter);
					TString name(prefix);
					name += (*var_iter);
					name += "Like";
					Double_t indivLike = (*pdf_iter)->getLikelihood( (*var_iter) );
					this->setSPlotNtupleDoubleBranchValue(name, indivLike);
				}
				TString name(prefix);
				name += allVars;
				name += "Like";
				this->setSPlotNtupleDoubleBranchValue(name, extraLike);
			} else {
				std::cerr << "WARNING in LauCPFitModel::setSPlotNtupleBranchValues : Can't yet deal with 3D PDFs." << std::endl;
			}
		}
	}
	return totalLike;
}

LauSPlot::NameSet LauCPFitModel::variableNames() const
{
	LauSPlot::NameSet nameSet;
	if (this->useDP()) {
		nameSet.insert("DP");
	}
	// Loop through all the signal PDFs
	for (LauPdfList::const_iterator pdf_iter = negSignalPdfs_.begin(); pdf_iter != negSignalPdfs_.end(); ++pdf_iter) {
		// Loop over the variables involved in each PDF
		std::vector<TString> varNames = (*pdf_iter)->varNames();
		for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
			// If they are not DP coordinates then add them
			if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
				nameSet.insert( (*var_iter) );
			}
		}
	}
	return nameSet;
}

LauSPlot::NumbMap LauCPFitModel::freeSpeciesNames() const
{
	LauSPlot::NumbMap numbMap;
	if (!signalEvents_->fixed() && this->doEMLFit()) {
		numbMap["sig"] = signalEvents_->genValue();
	}
	if ( usingBkgnd_ ) {
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
			const TString& bkgndClass = this->bkgndClassName(iBkgnd);
			const LauParameter* par = bkgndEvents_[iBkgnd];
			if (!par->fixed()) {
				numbMap[bkgndClass] = par->genValue();
			}
		}
	}
	return numbMap;
}

LauSPlot::NumbMap LauCPFitModel::fixdSpeciesNames() const
{
	LauSPlot::NumbMap numbMap;
	if (signalEvents_->fixed() && this->doEMLFit()) {
		numbMap["sig"] = signalEvents_->genValue();
	}
	if ( usingBkgnd_ ) {
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
			const TString& bkgndClass = this->bkgndClassName(iBkgnd);
			const LauParameter* par = bkgndEvents_[iBkgnd];
			if (par->fixed()) {
				numbMap[bkgndClass] = par->genValue();
			}
		}
	}
	return numbMap;
}

LauSPlot::TwoDMap LauCPFitModel::twodimPDFs() const
{
	// This makes the assumption that the form of the positive and
	// negative PDFs are the same, which seems reasonable to me

	LauSPlot::TwoDMap twodimMap;

	for (LauPdfList::const_iterator pdf_iter = negSignalPdfs_.begin(); pdf_iter != negSignalPdfs_.end(); ++pdf_iter) {
		// Count the number of input variables that are not DP variables
		UInt_t nVars(0);
		std::vector<TString> varNames = (*pdf_iter)->varNames();
		for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
			if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
				++nVars;
			}
		}
		if ( nVars == 2 ) {
			if (useSCF_) {
				twodimMap.insert( std::make_pair( "sigTM", std::make_pair( varNames[0], varNames[1] ) ) );
			} else {
				twodimMap.insert( std::make_pair( "sig", std::make_pair( varNames[0], varNames[1] ) ) );
			}
		}
	}

	if ( useSCF_ ) {
		for (LauPdfList::const_iterator pdf_iter = negScfPdfs_.begin(); pdf_iter != negScfPdfs_.end(); ++pdf_iter) {
			// Count the number of input variables that are not DP variables
			UInt_t nVars(0);
			std::vector<TString> varNames = (*pdf_iter)->varNames();
			for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
				if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
					++nVars;
				}
			}
			if ( nVars == 2 ) {
				twodimMap.insert( std::make_pair( "sigSCF", std::make_pair( varNames[0], varNames[1] ) ) );
			}
		}
	}

	if (usingBkgnd_) {
		const UInt_t nBkgnds = this->nBkgndClasses();
		for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
			const TString& bkgndClass = this->bkgndClassName(iBkgnd);
			const LauPdfList& pdfList = negBkgndPdfs_[iBkgnd];
			for (LauPdfList::const_iterator pdf_iter = pdfList.begin(); pdf_iter != pdfList.end(); ++pdf_iter) {
				// Count the number of input variables that are not DP variables
				UInt_t nVars(0);
				std::vector<TString> varNames = (*pdf_iter)->varNames();
				for ( std::vector<TString>::const_iterator var_iter = varNames.begin(); var_iter != varNames.end(); ++var_iter ) {
					if ( (*var_iter) != "m13Sq" && (*var_iter) != "m23Sq" ) {
						++nVars;
					}
				}
				if ( nVars == 2 ) {
					twodimMap.insert( std::make_pair( bkgndClass, std::make_pair( varNames[0], varNames[1] ) ) );
				}
			}
		}
	}

	return twodimMap;
}

void LauCPFitModel::storePerEvtLlhds()
{
	std::cout << "INFO in LauCPFitModel::storePerEvtLlhds : Storing per-event likelihood values..." << std::endl;

	// if we've not been using the DP model then we need to cache all
	// the info here so that we can get the efficiency from it

	LauFitDataTree* inputFitData = this->fitData();

	if (!this->useDP() && this->storeDPEff()) {
		negSigModel_->initialise(negCoeffs_);
		posSigModel_->initialise(posCoeffs_);
		negSigModel_->fillDataTree(*inputFitData);
		posSigModel_->fillDataTree(*inputFitData);
	}

	UInt_t evtsPerExpt(this->eventsPerExpt());

	LauAbsDPDynamics* sigModel(0);
	LauPdfList* sigPdfs(0);
	LauPdfList* scfPdfs(0);
	LauBkgndPdfsList* bkgndPdfs(0);

	for (UInt_t iEvt = 0; iEvt < evtsPerExpt; ++iEvt) {

		this->setSPlotNtupleIntegerBranchValue("iExpt",this->iExpt());
		this->setSPlotNtupleIntegerBranchValue("iEvtWithinExpt",iEvt);

		// Find out whether we have B- or B+
		if ( tagged_ ) {
			const LauFitData& dataValues = inputFitData->getData(iEvt);
			LauFitData::const_iterator iter = dataValues.find("charge");
			curEvtCharge_ = static_cast<Int_t>(iter->second);

			if (curEvtCharge_==+1) {
				sigModel = posSigModel_;
				sigPdfs = &posSignalPdfs_;
				scfPdfs = &posScfPdfs_;
				bkgndPdfs = &posBkgndPdfs_;
			} else {
				sigModel = negSigModel_;
				sigPdfs = &negSignalPdfs_;
				scfPdfs = &negScfPdfs_;
				bkgndPdfs = &negBkgndPdfs_;
			}
		} else {
			sigPdfs = &negSignalPdfs_;
			scfPdfs = &negScfPdfs_;
			bkgndPdfs = &negBkgndPdfs_;
		}

		// the DP information
		this->getEvtDPLikelihood(iEvt);
		if (this->storeDPEff()) {
			if (!this->useDP()) {
				posSigModel_->calcLikelihoodInfo(iEvt);
				negSigModel_->calcLikelihoodInfo(iEvt);
			}
			if ( tagged_ ) {
				this->setSPlotNtupleDoubleBranchValue("efficiency",sigModel->getEvtEff());
				if ( negSigModel_->usingScfModel() && posSigModel_->usingScfModel() ) {
					this->setSPlotNtupleDoubleBranchValue("scffraction",sigModel->getEvtScfFraction());
				}
			} else {
				this->setSPlotNtupleDoubleBranchValue("efficiency",0.5*(posSigModel_->getEvtEff() + negSigModel_->getEvtEff()) );
				if ( negSigModel_->usingScfModel() && posSigModel_->usingScfModel() ) {
					this->setSPlotNtupleDoubleBranchValue("scffraction",0.5*(posSigModel_->getEvtScfFraction() + negSigModel_->getEvtScfFraction()));
				}
			}
		}
		if (this->useDP()) {
			sigTotalLike_ = sigDPLike_;
			if (useSCF_) {
				scfTotalLike_ = scfDPLike_;
				this->setSPlotNtupleDoubleBranchValue("sigTMDPLike",sigDPLike_);
				this->setSPlotNtupleDoubleBranchValue("sigSCFDPLike",scfDPLike_);
			} else {
				this->setSPlotNtupleDoubleBranchValue("sigDPLike",sigDPLike_);
			}
			if (usingBkgnd_) {
				const UInt_t nBkgnds = this->nBkgndClasses();
				for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
					TString name = this->bkgndClassName(iBkgnd);
					name += "DPLike";
					this->setSPlotNtupleDoubleBranchValue(name,bkgndDPLike_[iBkgnd]);
				}
			}
		} else {
			sigTotalLike_ = 1.0;
			if (useSCF_) {
				scfTotalLike_ = 1.0;
			}
			if (usingBkgnd_) {
				const UInt_t nBkgnds = this->nBkgndClasses();
				for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
					bkgndTotalLike_[iBkgnd] = 1.0;
				}
			}
		}

		// the signal PDF values
		if ( useSCF_ ) {
			sigTotalLike_ *= this->setSPlotNtupleBranchValues(sigPdfs, "sigTM", iEvt);
			scfTotalLike_ *= this->setSPlotNtupleBranchValues(scfPdfs, "sigSCF", iEvt);
		} else {
			sigTotalLike_ *= this->setSPlotNtupleBranchValues(sigPdfs, "sig", iEvt);
		}

		// the background PDF values
		if (usingBkgnd_) {
			const UInt_t nBkgnds = this->nBkgndClasses();
			for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
				const TString& bkgndClass = this->bkgndClassName(iBkgnd);
				LauPdfList& pdfs = (*bkgndPdfs)[iBkgnd];
				bkgndTotalLike_[iBkgnd] *= this->setSPlotNtupleBranchValues(&(pdfs), bkgndClass, iEvt);
			}
		}

		// the total likelihoods
		if (useSCF_) {
			Double_t scfFrac(0.0);
			if ( useSCFHist_ ) {
				scfFrac = recoSCFFracs_[iEvt];
			} else {
				scfFrac = scfFrac_.value();
			}
			this->setSPlotNtupleDoubleBranchValue("sigSCFFrac",scfFrac);
			sigTotalLike_ *= ( 1.0 - scfFrac );
			if ( scfMap_ == 0 ) {
				scfTotalLike_ *= scfFrac;
			}
			this->setSPlotNtupleDoubleBranchValue("sigTMTotalLike",sigTotalLike_);
			this->setSPlotNtupleDoubleBranchValue("sigSCFTotalLike",scfTotalLike_);
		} else {
			this->setSPlotNtupleDoubleBranchValue("sigTotalLike",sigTotalLike_);
		}
		if (usingBkgnd_) {
			const UInt_t nBkgnds = this->nBkgndClasses();
			for ( UInt_t iBkgnd(0); iBkgnd < nBkgnds; ++iBkgnd ) {
				TString name = this->bkgndClassName(iBkgnd);
				name += "TotalLike";
				this->setSPlotNtupleDoubleBranchValue(name,bkgndTotalLike_[iBkgnd]);
			}
		}
		// fill the tree
		this->fillSPlotNtupleBranches();
	}
	std::cout << "INFO in LauCPFitModel::storePerEvtLlhds : Finished storing per-event likelihood values." << std::endl;
}

void LauCPFitModel::embedNegSignal(const TString& fileName, const TString& treeName,
		Bool_t reuseEventsWithinEnsemble, Bool_t reuseEventsWithinExperiment, 
		Bool_t useReweighting)
{
	if (negSignalTree_) {
		std::cerr << "ERROR in LauCPFitModel::embedNegSignal : Already embedding signal from a file." << std::endl;
		return;
	}

	if (!reuseEventsWithinEnsemble && reuseEventsWithinExperiment) {
		std::cerr << "WARNING in LauCPFitModel::embedNegSignal : Conflicting options provided, will not reuse events at all." << std::endl;
		reuseEventsWithinExperiment = kFALSE;
	}

	negSignalTree_ = new LauEmbeddedData(fileName,treeName,reuseEventsWithinExperiment);
	Bool_t dataOK = negSignalTree_->findBranches();
	if (!dataOK) {
		delete negSignalTree_; negSignalTree_ = 0;
		std::cerr << "ERROR in LauCPFitModel::embedNegSignal : Problem creating data tree for embedding." << std::endl;
		return;
	}
	reuseSignal_ = reuseEventsWithinEnsemble;
	useNegReweighting_ = useReweighting;
	if (this->enableEmbedding() == kFALSE) {this->enableEmbedding(kTRUE);}
}

void LauCPFitModel::embedNegBkgnd(const TString& bkgndClass, const TString& fileName, const TString& treeName,
		Bool_t reuseEventsWithinEnsemble, Bool_t reuseEventsWithinExperiment)
{
	if ( ! this->validBkgndClass( bkgndClass ) ) {
		std::cerr << "ERROR in LauCPFitModel::embedBkgnd : Invalid background class \"" << bkgndClass << "\"." << std::endl;
		std::cerr << "                                   : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		return;
	}

	UInt_t bkgndID = this->bkgndClassID( bkgndClass );

	if (negBkgndTree_[bkgndID]) {
		std::cerr << "ERROR in LauCPFitModel::embedNegBkgnd : Already embedding background from a file." << std::endl;
		return;
	}

	if (!reuseEventsWithinEnsemble && reuseEventsWithinExperiment) {
		std::cerr << "WARNING in LauCPFitModel::embedNegBkgnd : Conflicting options provided, will not reuse events at all." << std::endl;
		reuseEventsWithinExperiment = kFALSE;
	}

	negBkgndTree_[bkgndID] = new LauEmbeddedData(fileName,treeName,reuseEventsWithinExperiment);
	Bool_t dataOK = negBkgndTree_[bkgndID]->findBranches();
	if (!dataOK) {
		delete negBkgndTree_[bkgndID]; negBkgndTree_[bkgndID] = 0;
		std::cerr << "ERROR in LauCPFitModel::embedNegBkgnd : Problem creating data tree for embedding." << std::endl;
		return;
	}
	reuseBkgnd_[bkgndID] = reuseEventsWithinEnsemble;
	if (this->enableEmbedding() == kFALSE) {this->enableEmbedding(kTRUE);}
}

void LauCPFitModel::embedPosSignal(const TString& fileName, const TString& treeName,
		Bool_t reuseEventsWithinEnsemble, Bool_t reuseEventsWithinExperiment,
		Bool_t useReweighting)
{
	if (posSignalTree_) {
		std::cerr << "ERROR in LauCPFitModel::embedPosSignal : Already embedding signal from a file." << std::endl;
		return;
	}

	if (!reuseEventsWithinEnsemble && reuseEventsWithinExperiment) {
		std::cerr << "WARNING in LauCPFitModel::embedPosSignal : Conflicting options provided, will not reuse events at all." << std::endl;
		reuseEventsWithinExperiment = kFALSE;
	}

	posSignalTree_ = new LauEmbeddedData(fileName,treeName,reuseEventsWithinExperiment);
	Bool_t dataOK = posSignalTree_->findBranches();
	if (!dataOK) {
		delete posSignalTree_; posSignalTree_ = 0;
		std::cerr << "ERROR in LauCPFitModel::embedPosSignal : Problem creating data tree for embedding." << std::endl;
		return;
	}
	reuseSignal_ = reuseEventsWithinEnsemble;
	usePosReweighting_ = useReweighting;
	if (this->enableEmbedding() == kFALSE) {this->enableEmbedding(kTRUE);}
}

void LauCPFitModel::embedPosBkgnd(const TString& bkgndClass, const TString& fileName, const TString& treeName,
		Bool_t reuseEventsWithinEnsemble, Bool_t reuseEventsWithinExperiment)
{
	if ( ! this->validBkgndClass( bkgndClass ) ) {
		std::cerr << "ERROR in LauCPFitModel::embedBkgnd : Invalid background class \"" << bkgndClass << "\"." << std::endl;
		std::cerr << "                                   : Background class names must be provided in \"setBkgndClassNames\" before any other background-related actions can be performed." << std::endl;
		return;
	}

	UInt_t bkgndID = this->bkgndClassID( bkgndClass );

	if (posBkgndTree_[bkgndID]) {
		std::cerr << "ERROR in LauCPFitModel::embedPosBkgnd : Already embedding background from a file." << std::endl;
		return;
	}

	if (!reuseEventsWithinEnsemble && reuseEventsWithinExperiment) {
		std::cerr << "WARNING in LauCPFitModel::embedPosBkgnd : Conflicting options provided, will not reuse events at all." << std::endl;
		reuseEventsWithinExperiment = kFALSE;
	}

	posBkgndTree_[bkgndID] = new LauEmbeddedData(fileName,treeName,reuseEventsWithinExperiment);
	Bool_t dataOK = posBkgndTree_[bkgndID]->findBranches();
	if (!dataOK) {
		delete posBkgndTree_[bkgndID]; posBkgndTree_[bkgndID] = 0;
		std::cerr << "ERROR in LauCPFitModel::embedPosBkgnd : Problem creating data tree for embedding." << std::endl;
		return;
	}
	reuseBkgnd_[bkgndID] = reuseEventsWithinEnsemble;
	if (this->enableEmbedding() == kFALSE) {this->enableEmbedding(kTRUE);}
}

void LauCPFitModel::weightEvents( const TString& /*dataFileName*/, const TString& /*dataTreeName*/ )
{
	std::cerr << "ERROR in LauCPFitModel::weightEvents : Method not available for this fit model." << std::endl;
	return;
}

