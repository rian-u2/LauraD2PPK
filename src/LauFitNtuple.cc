
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFitNtuple.cc
    \brief File containing implementation of LauFitNtuple class.
*/

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TTree.h"
#include "TVirtualFitter.h"

#include "LauFitNtuple.hh"
#include "LauFitter.hh"
#include "LauParamFixed.hh"

ClassImp(LauFitNtuple)


LauFitNtuple::LauFitNtuple(const TString& fileName) :
	rootFileName_(fileName),
	rootFile_(0),
	fitResults_(0),
	definedFitTree_(kFALSE),
	fitStatus_(0),
	nFitPars_(0),
	nFreePars_(0),
	nExtraPars_(0),
	NLL_(0.0),
	iExpt_(0)
{
	rootFile_ = TFile::Open(rootFileName_, "recreate");
	rootFile_->cd();
	fitResults_ = new TTree("fitResults", "fitResults");
	fitResults_->SetDirectory(rootFile_);

	fitVars_.clear(); extraVars_.clear();
}

LauFitNtuple::~LauFitNtuple()
{
	if (rootFile_ && rootFile_->IsOpen()) {
		delete fitResults_; fitResults_ = 0;
	}
	delete rootFile_; rootFile_ = 0;
}

void LauFitNtuple::storeCorrMatrix(UInt_t iExpt, Double_t NLL, Int_t fitStatus)
{
	// store the minimised NLL value, correlation matrix status and experiment number
	iExpt_ = iExpt;
	NLL_ = NLL;
	fitStatus_ = fitStatus;

	// get a pointer to the fitter
	TVirtualFitter* fitter = LauFitter::fitter();

	// make a few checks on the number of parameters
	Int_t nFitPars = fitter->GetNumberTotalParameters();
	Int_t nFreePars = fitter->GetNumberFreeParameters();
	if (nFitPars != nFitPars_) {
		cerr << "WARNING in LauFitNtuple::storeCorrMatrix : total number of parameters from fitter (" << nFitPars
			 << ") not the same as the number held here (" << nFitPars_ << ")." << endl;
	}
	if (nFreePars != nFreePars_) {
		cerr << "WARNING in LauFitNtuple::storeCorrMatrix : number of free parameters from fitter (" << nFreePars
			 << ") not the same as the number held here (" << nFreePars_ << ")." << endl;
	}

	// make the two correlation matrices the correct dimensions
	if (definedFitTree_ == kFALSE) {
		globalCC_.clear();
		globalCC_.resize(nFitPars_);

		corrMatrix_.clear();
		corrMatrix_.resize(nFitPars_);
		for (Int_t i = 0; i < nFitPars_; ++i) {corrMatrix_[i].resize(nFitPars_);}
	}

	// get correlation matrix information from the fitter
	Double_t error(0.0);
	Double_t negError(0.0);
	Double_t posError(0.0);
	Double_t globalcc(0.0);
	Bool_t iFixed(kFALSE);
	Bool_t jFixed(kFALSE);
	Int_t iFree(0);
	Int_t jFree(0);

	for (Int_t i = 0; i < nFitPars_; i++) {      

		iFixed = fitVars_[i]->fixed();

		// get the global correlation factor for each parameter
		if (iFixed) {
			globalcc = 0.0;
		} else {
			fitter->GetErrors(i, posError, negError, error, globalcc);
		}
		globalCC_[i] = globalcc;

		// reset the "j" free parameter counter
		jFree = 0;

		// the GetCovarianceMatrixElement method returns elements of the external error matrix,
		// which is of dimension nFreePars_ x nFreePars_
		for (Int_t j = 0; j < nFitPars_; j++) {

			jFixed = fitVars_[j]->fixed();

			if (i == j) {
				corrMatrix_[i][j] = 1.0;
			} else if (iFixed == kTRUE || jFixed == kTRUE) {
				corrMatrix_[i][j] = 0.0;
			} else {
				Double_t r_ij = fitter->GetCovarianceMatrixElement(iFree,jFree);
				Double_t r_ii = fitter->GetCovarianceMatrixElement(iFree,iFree);
				Double_t r_jj = fitter->GetCovarianceMatrixElement(jFree,jFree);
				Double_t denom = r_ii * r_jj;
				if (denom < 0.0) {
					r_ij = 0.0;
					denom = 1.0;
				}
				denom = TMath::Sqrt(denom);
				if (denom < 1e-30) {
					r_ij = 0.0;
					denom = 1.0;
				}
				corrMatrix_[i][j] = r_ij / denom;
			}

			if (!jFixed) {
				++jFree;
			}
		}

		if (!iFixed) {
			++iFree;
		}
	}
}

void LauFitNtuple::storeParsAndErrors(const std::vector<LauParameter*>& fitVars, const std::vector<LauParameter>& extraVars)
{
	fitVars_ = fitVars; 
	Int_t nFitPars = fitVars_.size();
	// the number of parameters being given to us should be the same as the number from the last fit
	// OR it's the first time so the "last" number is zero
	if (nFitPars_ != 0 && nFitPars_ != nFitPars) {
		cerr << "ERROR in LauFitNtuple::storeParsAndErrors : expected total number of parameters (" << nFitPars_
			 << ") not the same as the number provided (" << nFitPars << ")." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	LauParamFixed pred;
	Int_t nFreePars = nFitPars - std::count_if(fitVars_.begin(),fitVars_.end(),pred);
	// the number of free parameters being given to us should be the same as the number from the last fit
	// OR it's the first time so the "last" number is zero
	// (NB we check whether nFitPars_ is zero for this since it is possible to have zero free parameters, albeit rather daft)
	if (nFitPars_ != 0 && nFreePars_ != nFreePars) {
		cerr << "ERROR in LauFitNtuple::storeParsAndErrors : expected number of free parameters (" << nFreePars_
			 << ") not the same as the number provided (" << nFreePars << ")." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	nFitPars_ = nFitPars;
	nFreePars_ = nFreePars;

	extraVars_ = extraVars;
	nExtraPars_ = extraVars_.size();
}

void LauFitNtuple::updateFitNtuple()
{
	// Now create and fill the stored fit results into an ntuple (TTree)
	if (definedFitTree_ == kFALSE) {

		cout << "INFO in LauFitNtuple::updateFitNtuple : totNoPars = " << nFitPars_ << endl;

		// Add experiment number as a branch
		fitResults_->Branch("iExpt", &iExpt_, "iExpt/I");
		fitResults_->Branch("fitStatus", &fitStatus_, "fitStatus/I");

		// Add NLL (negative log-likelihood) value from fit
		fitResults_->Branch("NLL", &NLL_, "NLL/D");

		for (Int_t i = 0; i < nFitPars_; i++) {

			TString parName = fitVars_[i]->name();
			TString parNameD(parName); parNameD += "/D";
			fitResults_->Branch(parName.Data(), &fitVars_[i]->value_, parNameD.Data());

			TString parInitName(parName); parInitName += "_True";
			TString parInitNameD(parInitName); parInitNameD += "/D";
			fitResults_->Branch(parInitName.Data(), &fitVars_[i]->genValue_, parInitNameD.Data());

			if (!fitVars_[i]->fixed()) {
				TString parErrName(parName); parErrName += "_Error";
				TString parErrNameD(parErrName); parErrNameD += "/D";
				fitResults_->Branch(parErrName.Data(), &fitVars_[i]->error_, parErrNameD.Data());

				TString parPullName(parName); parPullName += "_Pull";
				TString parPullNameD(parPullName); parPullNameD += "/D";
				fitResults_->Branch(parPullName.Data(), &fitVars_[i]->pull_, parPullNameD.Data());
			}

			// Now add in the correlation matrix values (only for floating parameters)
			if (!fitVars_[i]->fixed()) {
				// First the global correlation coeffs
				TString parGCCName(parName); parGCCName += "_GCC";
				TString parGCCNameD(parGCCName); parGCCNameD += "/D";
				fitResults_->Branch(parGCCName.Data(), &globalCC_[i], parGCCNameD.Data());

				// Then the rest
				for (Int_t j = 0; j < nFitPars_; j++) {
					if (!fitVars_[j]->fixed() && i!=j) {
						TString parName2 = fitVars_[j]->name();
						TString corrName("corr__");
						corrName += parName; corrName += "__"; corrName += parName2;

						TString corrNameD(corrName); corrNameD += "/D";	
						fitResults_->Branch(corrName.Data(), &corrMatrix_[i][j], corrNameD.Data());
					}
				}
			}
		}

		// Update extra parameter values...
		for (Int_t i = 0; i < nExtraPars_; i++) {

			TString parName = extraVars_[i].name();
			TString parNameD(parName); parNameD += "/D";
			fitResults_->Branch(parName.Data(), &extraVars_[i].value_, parNameD.Data());

			TString parInitName(parName); parInitName += "_True";
			TString parInitNameD(parInitName); parInitNameD += "/D";
			fitResults_->Branch(parInitName.Data(), &extraVars_[i].genValue_, parInitNameD.Data());

			//TString parErrName(parName); parErrName += "_Error";
			//TString parErrNameD(parErrName); parErrNameD += "/D";
			//fitResults_->Branch(parErrName.Data(), &extraVars_[i].error_, parErrNameD.Data());

			// Also find the fit fraction pull and store it
			//TString pullName(parName); pullName += "_Pull";
			//TString pullNameD(pullName); pullNameD += "/D";
			//fitResults_->Branch(pullName.Data(), &extraVars_[i].pull_, pullNameD.Data());

		}

		definedFitTree_ = kTRUE;

	}

	cout << "NLL = " << NLL_ << endl;

	fitResults_->Fill();
}  

void LauFitNtuple::writeOutFitResults()
{
	// Write out the fit ntuple to the appropriate root file
	rootFile_->cd();
	rootFile_->Write();
	rootFile_->Close();
	delete rootFile_; rootFile_ = 0;
}

