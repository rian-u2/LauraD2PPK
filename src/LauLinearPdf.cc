
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauLinearPdf.cc
  \brief File containing implementation of LauLinearPdf class.
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
#include "LauLinearPdf.hh"

ClassImp(LauLinearPdf)


	LauLinearPdf::LauLinearPdf(const TString& theVarName, const vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa) :
		LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
		slope_(0),posflag_(kTRUE)
{
	// Constructor for the linear PDF.
	//
	// The parameters in params are the slope and y-intercept of the line.
	// The last two arguments specify the range in which the PDF is defined, and the PDF
	// will be normalised w.r.t. these limits.

	slope_ = this->findParameter("slope");

	if ((this->nParameters() != 1) || (slope_ == 0)) {
		cerr<<"Warning. LauLinearPdf requires 1 parameter: \"slope\"."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor.
	this->calcNorm();
}

LauLinearPdf::~LauLinearPdf() 
{
	// Destructor
}

LauLinearPdf::LauLinearPdf(const LauLinearPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa())
{
	// Copy constructor
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

void LauLinearPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the up to date parameter values
	Double_t slope = slope_->value();

	// Calculate the value of the straight line for the given value of the abscissa.
	Double_t constVal = 1.0/(this->getMaxAbscissa() - this->getMinAbscissa());
	constVal -= slope * (this->getMaxAbscissa() + this->getMinAbscissa()) * 0.5;

	Double_t value = slope*abscissa + constVal;

	// Make sure the PDF doesn't go negative
	if ( value < 0.0 ) {
		if ( posflag_ ) {
			std::cerr << "WARNING in LauLinearPdf::calcLikelihoodInfo : The PDF is negative, setting to zero" << std::endl;
		}
		value = 0.0;
		posflag_= kFALSE;
	}

	this->setUnNormPDFVal(value);
}

void LauLinearPdf::calcNorm() 
{
	// Nothing to calculate here since the PDF is already normalised to 1
	this->setNorm(1.0);
}

void LauLinearPdf::calcPDFHeight( const LauKinematics* /*kinematics*/ )
{
	if (this->heightUpToDate()) {
		return;
	}

	// Get the up to date parameter values
	Double_t slope = slope_->value();

	// Calculate the PDF height for the straight line
	LauAbscissas maxPoint(1);
	if (slope>0.0) {
		maxPoint[0] = this->getMaxAbscissa();
	} else {
		maxPoint[0] = this->getMinAbscissa();
	}
	this->calcLikelihoodInfo(maxPoint);

	Double_t height = this->getUnNormLikelihood();

	this->setMaxHeight(height);
}
