
// Copyright University of Warwick 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauMinuit.cc
    \brief File containing implementation of LauMinuit methods.
*/

#include <iostream>
#include <algorithm>

#include "TMatrixD.h"
#include "TVirtualFitter.h"

#include "LauFitObject.hh"
#include "LauFitter.hh"
#include "LauMinuit.hh"
#include "LauParameter.hh"
#include "LauParamFixed.hh"

// It's necessary to define an external function that specifies the address of the function
// that Minuit needs to minimise. Minuit doesn't know about any classes - therefore
// use gMinuit->SetFCN(external_function), gMinuit->SetObjectFit(this).
// Here, we use TVirtualFitter* fitter instead of gMinuit, defined below.
// Then, within the external function, invoke an object from this class (LauAllModel), 
// and use the member functions to access the parameters/variables.
extern void logLikeFun(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag);


LauMinuit::LauMinuit( Int_t maxPar ) : LauAbsFitter(),
	minuit_(0),
	maxPar_(maxPar),
	nParams_(0),
	nFreeParams_(0),
	twoStageFit_(kFALSE),
	useAsymmFitErrors_(kFALSE),
	fitStatus_(0),
	NLL_(0.0)
{
	TVirtualFitter::SetDefaultFitter( "Minuit" );
	minuit_ = TVirtualFitter::Fitter( 0, maxPar_ );
}

LauMinuit::~LauMinuit()
{
}

void LauMinuit::initialise( LauFitObject* fitObj, const std::vector<LauParameter*>& parameters )
{
	// Check whether we're going to use asymmetric errors
	if (useAsymmFitErrors_ == kTRUE) {
		std::cout << "INFO in LauMinuit::fit : We are going to calculate the asymmetric fit errors." << std::endl;
		std::cout << "                       : This will, in general, significantly increase the CPU time required for fitting." << std::endl;
	} else {
		std::cout << "INFO in LauMinuit::fit : Only parabolic errors will be calculated." << std::endl;
	}

	// Store the parameters
	params_ = parameters;

	// Hook the external likelihood function to this LauFitter::fitter() and this class.
	minuit_->SetFCN( logLikeFun );
	minuit_->SetObjectFit( fitObj );

	// Clear any stored parameters etc... before using
	minuit_->Clear();

	nParams_ = params_.size();
	std::cout << "INFO in LauMinuit::initialise : Setting fit parameters" << std::endl;
	std::cout << "                              : Total number of parameters = " << nParams_ << std::endl;

	// Define the default relative error
	const Double_t defaultError(0.01);

	// Set-up the parameters
	for (UInt_t i = 0; i < nParams_; ++i) {
		TString name = params_[i]->name();
		Double_t initVal = params_[i]->initValue();
		Double_t initErr = params_[i]->error();
		// If we do not have a supplied estimate of the error, we should make a reasonable guess
		if ( initErr == 0.0 ) {
			if ( initVal == 0.0 ) {
				initErr = defaultError;
			} else if ( TMath::Abs(initErr/initVal) < 1e-6 ) {
				initErr = TMath::Abs(defaultError * initVal);
			}
		}
		Double_t minVal = params_[i]->minValue();
		Double_t maxVal = params_[i]->maxValue();
		Bool_t secondStage = params_[i]->secondStage();
		if (this->twoStageFit() && secondStage == kTRUE) {
			params_[i]->fixed(kTRUE);
		}
		Bool_t fixVar = params_[i]->fixed();

		std::cout << "                              : Setting parameter " << i << " called " << name << " to have initial value " << initVal << ", error " << initErr << " and range " << minVal << " to " << maxVal << std::endl;
		minuit_->SetParameter(i, name, initVal, initErr, minVal, maxVal);

		// Fix parameter if required
		if (fixVar == kTRUE) {
			std::cout << "                              : Fixing parameter " << i << std::endl;
			minuit_->FixParameter(i);
		} 
	}

	LauParamFixed pred;
	nFreeParams_ = nParams_ - std::count_if(params_.begin(),params_.end(),pred);

	// Need to set the "SET ERR" command to +0.5 for +/-1 sigma errors
	// for maximum likelihood fit. Very important command, otherwise all
	// extracted errors will be too big, and pull distributions will be too narrow!
	// TODO - The alternative to this is to make FCN = -2log(L) rather than -log(L)
	Double_t argL[2];
	argL[0] = 0.5;
	fitStatus_ = minuit_->ExecuteCommand("SET ERR", argL, 1);

	//argL[0] = 0;
	//fitStatus_ = minuit_->ExecuteCommand("SET STRATEGY", argL, 1);
}

LauFitObject* LauMinuit::getFitObject()
{
	return (minuit_!=0) ? dynamic_cast<LauFitObject*>( minuit_->GetObjectFit() ) : 0;
}

std::pair<Int_t,Double_t> LauMinuit::minimise()
{
	Double_t arglist[2];
	arglist[0] = 1000*nParams_; // maximum iterations
	arglist[1] = 0.05; // tolerance -> min EDM = 0.001*tolerance (0.05)
	fitStatus_ = minuit_->ExecuteCommand("MIGRAD", arglist, 2);

	// Dummy variables - need to feed them to the function
	// used for getting NLL and error matrix status
	Double_t edm, errdef;
	Int_t nvpar, nparx;

	if (fitStatus_ != 0) {

		std::cerr << "ERROR in LauMinuit::minimise : Error in minimising loglike." << std::endl;

	} else {

		// Check that the error matrix is ok
		NLL_ = 0.0;
		fitStatus_ = minuit_->GetStats(NLL_, edm, errdef, nvpar, nparx);
		std::cout << "INFO in LauMinuit::minimise : Error matrix status after MIGRAD is: " << fitStatus_ << std::endl;
		// 0= not calculated at all
		// 1= approximation only, not accurate
		// 2= full matrix, but forced positive-definite
		// 3= full accurate covariance matrix

		// Fit result was OK. Now get the more precise errors.
		fitStatus_ = minuit_->ExecuteCommand("HESSE", arglist, 1);

		if (fitStatus_ != 0) {

			std::cerr << "ERROR in LauMinuit::minimise : Error in HESSE routine." << std::endl;

		} else {

			// Check that the error matrix is ok
			NLL_ = 0.0;
			fitStatus_ = minuit_->GetStats(NLL_, edm, errdef, nvpar, nparx);
			std::cout << "INFO in LauMinuit::minimise : Error matrix status after HESSE is: " << fitStatus_ << std::endl;
			// 0= not calculated at all
			// 1= approximation only, not accurate
			// 2= full matrix, but forced positive-definite
			// 3= full accurate covariance matrix

			// Symmetric errors and eror matrix were OK. 
			// Get asymmetric errors if asked for.
			if (useAsymmFitErrors_ == kTRUE) {
				LauFitObject* fitObj = this->getFitObject();
				fitObj->withinAsymErrorCalc( kTRUE );
				fitStatus_ = minuit_->ExecuteCommand("MINOS", arglist, 1); 
				fitObj->withinAsymErrorCalc( kFALSE );
				if (fitStatus_ != 0) {
					std::cerr << "ERROR in LauMinuit::minimise : Error in MINOS routine." << std::endl;
				}
			}
		}
	}

	// Print results
	NLL_ = 0.0;
	fitStatus_ = minuit_->GetStats(NLL_, edm, errdef, nvpar, nparx);
	std::cout << "INFO in LauMinuit::minimise : Final error matrix status is: " << fitStatus_ << std::endl;
	// 0= not calculated at all
	// 1= approximation only, not accurate
	// 2= full matrix, but forced positive-definite
	// 3= full accurate covariance matrix

	minuit_->PrintResults(3, NLL_);

	// Retrieve the covariance matrix from the fitter
	// For some reason the array returned is as if the matrix is of dimension nParams_ x nParams_
	// but only the elements within the sub-matrix nFreeParams_ x nFreeParams_ have values,
	// the "trailing" elements are zero, so we trim them off.
	Double_t* covMatrix = minuit_->GetCovarianceMatrix();
	covMatrix_.Clear();
	covMatrix_.ResizeTo( nParams_, nParams_ );
	covMatrix_.SetMatrixArray( covMatrix );
	covMatrix_.ResizeTo( nFreeParams_, nFreeParams_ );

	return std::make_pair( fitStatus_, NLL_ );
}

void LauMinuit::fixSecondStageParameters()
{
	for (UInt_t i = 0; i < nParams_; ++i) {
		Bool_t secondStage = params_[i]->secondStage();
		if (secondStage == kTRUE) {
			params_[i]->fixed(kTRUE);
			minuit_->FixParameter(i);
		}
	}
	LauParamFixed pred;
	nFreeParams_ = nParams_ - std::count_if(params_.begin(),params_.end(),pred);
}

void LauMinuit::releaseSecondStageParameters()
{
	for (UInt_t i = 0; i < nParams_; ++i) {
		Bool_t secondStage = params_[i]->secondStage();
		if (secondStage == kTRUE) {
			params_[i]->fixed(kFALSE);
			minuit_->ReleaseParameter(i);
		}
	}
	LauParamFixed pred;
	nFreeParams_ = nParams_ - std::count_if(params_.begin(),params_.end(),pred);
}

void LauMinuit::updateParameters()
{
	for (UInt_t i = 0; i < nParams_; ++i) {
		// Get the value and errors from MINUIT
		Double_t value = minuit_->GetParameter(i);
		Double_t error(0.0);
		Double_t negError(0.0);
		Double_t posError(0.0);
		Double_t globalcc(0.0);
		minuit_->GetErrors(i, posError, negError, error, globalcc);
		params_[i]->valueAndErrors(value, error, negError, posError);
		params_[i]->globalCorrelationCoeff(globalcc);
	}
}

// Definition of the fitting function for Minuit
void logLikeFun(Int_t& npar, Double_t* /*first_derivatives*/, Double_t& f, Double_t* par, Int_t /*iflag*/)
{
	// Routine that specifies the negative log-likelihood function for the fit.
	// Used by the MINUIT minimising code.

	LauFitObject* theModel = LauFitter::fitter()->getFitObject();

	// Set the internal parameters for this model using parameters from Minuit (pars):
	theModel->setParsFromMinuit( par, npar );

	// Set the value of f to be the total negative log-likelihood for the data sample.
	f = theModel->getTotNegLogLikelihood();
}

