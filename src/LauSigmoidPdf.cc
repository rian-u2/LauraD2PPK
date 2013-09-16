
// Copyright University of Warwick 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSigmoidPdf.cc
    \brief File containing implementation of LauSigmoidPdf class.
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
#include "LauSigmoidPdf.hh"

ClassImp(LauSigmoidPdf)


LauSigmoidPdf::LauSigmoidPdf(const TString& theVarName, const vector<LauParameter*>& params, Double_t minAbscissa, Double_t maxAbscissa) :
	LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
	a_(0),
	b_(0)
{
	// Constructor for the general form of a Sigmoid PDF.
	//
	// The parameters in params "a" and "b" define the steepness of the
	// slope and shift of the distribution (negative parameter "a" flips
	// the distribution around the y-axis). 
	// The last two arguments specify the range in which the PDF is
	// defined, and the PDF will be normalised w.r.t. these limits.

	a_ = this->findParameter("a");
	b_ = this->findParameter("b");

	if ((this->nParameters() != 2) || (a_ == 0) || (b_ == 0)) {
		cerr<<"ERROR in LauSigmoidPdf constructor: LauSigmoidPdf requires 2 parameters: \"a\" and \"b\"."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor
	this->calcNorm();
}

LauSigmoidPdf::~LauSigmoidPdf() 
{
	// Destructor
}

LauSigmoidPdf::LauSigmoidPdf(const LauSigmoidPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa())
{
	// Copy constructor
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

void LauSigmoidPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the up to date parameter values
	Double_t a = a_->value();
	Double_t b = b_->value();

	// Calculate the value of the exponent for the given value of the abscissa.

	Double_t exponent = -a*abscissa + b;

	Double_t value = 1.0/(1.0+ TMath::Exp(exponent));

	this->setUnNormPDFVal(value);

	// if the parameters are floating then we
	// need to recalculate the normalisation
	if (!this->cachePDF() && !this->withinNormCalc() && !this->withinGeneration()) {
		this->calcNorm();
	}

}

void LauSigmoidPdf::calcNorm() 
{
	// Get the up to date parameter values
	Double_t a = a_->value();
	Double_t b = b_->value();

	// Calculate the normalisation of the sigmoid and cache it.
	Double_t norm(0.0);

	if (TMath::Abs(a) > 1e-10) {
		Double_t expb = TMath::Exp(b);

		norm = TMath::Log( TMath::Exp(a * this->getMaxAbscissa()) + expb ) -
		       TMath::Log( TMath::Exp(a * this->getMinAbscissa()) + expb );
		norm /= a;

	}

	this->setNorm(norm);
}


void LauSigmoidPdf::calcPDFHeight(const LauKinematics* /*kinematics*/)
{
	if (this->heightUpToDate()) {
		return;
	}

	// Get the up to date parameter values
	Double_t a = a_->value();

	LauAbscissas maxPoint(1);
	maxPoint[0] = 0;

	// Calculate the PDF height for the Sigmoid function.
	if (a > 0.0) {
		maxPoint[0] = this->getMaxAbscissa();
	} else {
		maxPoint[0] = this->getMinAbscissa();
	}
	this->calcLikelihoodInfo(maxPoint);

	Double_t height = this->getUnNormLikelihood();
	this->setMaxHeight(height);
}


