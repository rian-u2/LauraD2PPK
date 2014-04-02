
// Copyright University of Warwick 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFormulaPar.cc
  \brief File containing implementation of LauFormulaPar class.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>

#include "TRandom.h"
#include "TMessage.h"
#include "TSystem.h"

#include "LauFormulaPar.hh"
#include "LauParameter.hh"
#include "LauRandom.hh"

ClassImp(LauFormulaPar)


	LauFormulaPar::LauFormulaPar(const TString& forName, const TString& formula, const std::vector<LauParameter*>& params) :
		name_(forName),
		formula_(forName,formula),
		paramVec_(params),
		dummy_(0),
		paramArray_(0),
		gaussConstraint_(kFALSE),
		constraintMean_(0.0),
		constraintWidth_(0.0)
{
	// Dummy array for TFormula
	dummy_ = new Double_t[1];

	// Array of input parameters
	Int_t nPars = paramVec_.size();

	// Check length of vector matches number of parameter in the formula
	if (formula_.GetNpar() != nPars){
		std::cerr<<"ERROR in LauFormulaPar::evaluate : Number of parameters in the formula is : "<<formula_.GetNpar()<< " and the number of LauParameters is : "<<nPars<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	paramArray_ = new Double_t[nPars];

	if (formula_.GetNdim() != 1){
		std::cerr<<"ERROR in LauFormulaPar::evaluate : Given formula of dimension: "<<formula_.GetNdim()<<" and not 1"<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
}

LauFormulaPar::~LauFormulaPar()
{
	delete[] dummy_;
	delete[] paramArray_;
}

Double_t LauFormulaPar::value() const
{

	//Assign vector values to array
	Int_t nPars = paramVec_.size();

	for(Int_t i=0; i<nPars; ++i){
		paramArray_[i] = paramVec_[i]->value();
	}

	return formula_.EvalPar(dummy_,paramArray_);
}

Bool_t LauFormulaPar::fixed() const
{
	for ( std::vector<LauParameter*>::const_iterator iter = paramVec_.begin(); iter != paramVec_.end(); ++iter ) {
		if ( !(*iter)->fixed() ) { return kFALSE; }
	}
	return kTRUE;
}

void LauFormulaPar::addGaussianConstraint(Double_t newGaussMean, Double_t newGaussWidth)
{
	gaussConstraint_ = kTRUE;
	constraintMean_ = newGaussMean;
	constraintWidth_ = newGaussWidth;
}

void LauFormulaPar::removeGaussianConstraint()
{
	gaussConstraint_ = kFALSE;
}

