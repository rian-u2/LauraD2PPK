
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGaussPdf.cc
    \brief File containing implementation of LauGaussPdf class.
*/

#include <iostream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#include "TMath.h"
#include "TSystem.h"

#include "LauConstants.hh"
#include "LauGaussPdf.hh"

ClassImp(LauGaussPdf)


LauGaussPdf::LauGaussPdf(const TString& theVarName, const vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa) :
	LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
	mean_(0),
	sigma_(0)
{
	// Constructor for the Gaussian PDF.
	//
	// The parameters in params are the mean and the sigma (half the width) of the gaussian.
	// The last two arguments specify the range in which the PDF is defined, and the PDF
	// will be normalised w.r.t. these limits.

	mean_ = this->findParameter("mean");
	sigma_ = this->findParameter("sigma");

	if ((this->nParameters() != 2) || (mean_ == 0) || (sigma_ == 0)) {
		cerr<<"ERROR in LauGaussPdf constructor: LauGaussPdf requires 2 parameters: \"mean\" and \"sigma\"."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor
	this->calcNorm();
}

LauGaussPdf::~LauGaussPdf() 
{
	// Destructor
}

LauGaussPdf::LauGaussPdf(const LauGaussPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa())
{
	// Copy constructor
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

void LauGaussPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the up to date parameter values
	Double_t mean = mean_->value();
	Double_t sigma = sigma_->value();

	// Calculate the value of the Gaussian for the given value of the abscissa.
	Double_t arg = abscissa - mean;

	Double_t exponent(0.0);
	if (TMath::Abs(sigma) > 1e-10) {
		exponent = -0.5*arg*arg/(sigma*sigma);
	}

	Double_t value = TMath::Exp(exponent);
	this->setUnNormPDFVal(value);

	// if the parameters are floating then we
	// need to recalculate the normalisation
	if (!this->cachePDF() && !this->withinNormCalc() && !this->withinGeneration()) {
		this->calcNorm();
	}

}

void LauGaussPdf::calcNorm() 
{
	// Get the up to date parameter values
	Double_t mean = mean_->value();
	Double_t sigma = sigma_->value();

	// Calculate the normalisation of the gaussian and cache it.
	Double_t scale = LauConstants::root2*sigma;
	Double_t norm(0.0);

	if (TMath::Abs(sigma) > 1e-10) {
		norm = LauConstants::rootPiBy2*sigma*(TMath::Erf((this->getMaxAbscissa() - mean)/scale) - TMath::Erf((this->getMinAbscissa() - mean)/scale));
	}

	this->setNorm(norm);
}

void LauGaussPdf::calcPDFHeight(const LauKinematics* /*kinematics*/)
{
	if (this->heightUpToDate()) {
		return;
	}

	// Get the up to date parameter values
	Double_t mean = mean_->value();

	LauAbscissas maxPoint(1);
	maxPoint[0] = mean;

	// Calculate the PDF height for the Gaussian function.
	if (mean>this->getMaxAbscissa()) {
		maxPoint[0] = this->getMaxAbscissa();
	} else if (mean<this->getMinAbscissa()) {
		maxPoint[0] = this->getMinAbscissa();
	}
	this->calcLikelihoodInfo(maxPoint);

	Double_t height = this->getUnNormLikelihood();
	this->setMaxHeight(height);
}

