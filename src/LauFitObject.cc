
/*
Copyright 2017 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauFitObject.cc
    \brief File containing implementation of LauFitObject class.
*/


#include "LauFitObject.hh"

ClassImp(LauFitObject)

LauFitObject::LauFitObject() : TObject(),
	storeCon_(),
	twoStageFit_(kFALSE),
	useAsymmFitErrors_(kFALSE),
	nParams_(0),
	nFreeParams_(0),
	withinAsymErrorCalc_(kFALSE),
	firstExpt_(0),
	nExpt_(0),
	iExpt_(0),
	evtsPerExpt_(0),
	fitStatus_({-1,0.0,0.0}),
	worstLogLike_(std::numeric_limits<Double_t>::max()),
	covMatrix_(),
	numberOKFits_(0),
	numberBadFits_(0)
{
}

void LauFitObject::resetFitCounters()
{
	numberOKFits_ = 0;
	numberBadFits_ = 0;
	fitStatus_ = { -1, 0.0, 0.0 };
}

void LauFitObject::startNewFit( const UInt_t nPars, const UInt_t nFreePars )
{
	// Reset the worst likelihood found to its catch-all value
	worstLogLike_ = std::numeric_limits<Double_t>::max();

	// Store the number of fit parameters (total and floating)
	nParams_ = nPars;
	nFreeParams_ = nFreePars;
}

void LauFitObject::storeFitStatus( const LauAbsFitter::FitStatus& status, const TMatrixD& covMatrix )
{
	fitStatus_ = status;

	covMatrix_.Clear();
	covMatrix_.ResizeTo( covMatrix.GetNrows(), covMatrix.GetNcols() );
	covMatrix_.SetMatrixArray( covMatrix.GetMatrixArray() );

	// Keep track of how many fits worked or failed
	// NB values of fitStatus_ indicate the status of the error matrix:
	// 0= not calculated at all
	// 1= approximation only, not accurate
	// 2= full matrix, but forced positive-definite
	// 3= full accurate covariance matrix
	if (fitStatus_.status == 3) {
		++numberOKFits_;
	} else {
		++numberBadFits_;
	}
}

void LauFitObject::addConstraint(const TString& formula, const std::vector<TString>& pars, const Double_t mean, const Double_t width)
{
	StoreConstraints newCon;
	newCon.formula_ = formula;
	newCon.conPars_ = pars;
	newCon.mean_ = mean;
	newCon.width_ = width;

	storeCon_.push_back(newCon);
}

