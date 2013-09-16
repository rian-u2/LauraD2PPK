
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauArgusPdf.cc
    \brief File containing implementation of LauArgusPdf class.
*/

#include <iostream>
#include <vector>

#include "TMath.h"
#include "TSystem.h"

#include "LauArgusPdf.hh"
#include "LauConstants.hh"

ClassImp(LauArgusPdf)


LauArgusPdf::LauArgusPdf(const TString& theVarName, const std::vector<LauParameter*>& params, Double_t minAbscissa, Double_t maxAbscissa) :
	LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
	xi_(0),
	m0_(0)
{
	// Constructor for the ARGUS PDF.
	//
	// The parameters in params are the shape, xi, and the end-point of the curve.
	// The last two arguments specify the range in which the PDF is defined, and the PDF
	// will be normalised w.r.t. these limits.

	xi_ = this->findParameter("xi");
	m0_ = this->findParameter("m0");

	if ((this->nParameters() != 2) || (xi_ == 0) || (m0_ == 0)) {
		std::cerr << "ERROR in LauArgusPdf constructor: LauArgusPdf requires 2 parameters: argus shape parameter, \"xi\", and end-point, \"m0\"." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor.
	this->calcNorm();
}

LauArgusPdf::~LauArgusPdf() 
{
	// Destructor
}

LauArgusPdf::LauArgusPdf(const LauArgusPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa())
{
	// Copy constructor
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

void LauArgusPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the up to date parameter values
	Double_t xi = xi_->value();
	Double_t m0 = m0_->value();

	// Calculate the value of the ARGUS function for the given value of the abscissa.
	Double_t x = abscissa/m0;

	Double_t term = 1.0 - x*x;
	if (term < 0.0) {term = 0.0;} // In case |x| > 1.0 (which should happen rarely).

	Double_t value = abscissa*TMath::Sqrt(term)*TMath::Exp(-xi*term);
	this->setUnNormPDFVal(value);

	// if the parameters are floating then we
	// need to recalculate the normalisation
	if (!this->cachePDF() && !this->withinNormCalc() && !this->withinGeneration()) {
		this->calcNorm();
	}
}

void LauArgusPdf::calcNorm() 
{
	// Calculate the PDF normalisation and cache it

	// Get the up to date parameter values
	Double_t xi = xi_->value();
	Double_t m0 = m0_->value();

	// Since the PDF is 0 above m0 by definition need to check whether m0 is within the range, above it or below it
	Double_t min = (this->getMinAbscissa() < m0) ? this->getMinAbscissa() : m0;
	Double_t max = (this->getMaxAbscissa() < m0) ? this->getMaxAbscissa() : m0;

	// Define variables equivalent to "term" in calcLikelihoodInfo above but at the min and max points
	Double_t termMin = 1.0 - (min/m0)*(min/m0);
	Double_t termMax = 1.0 - (max/m0)*(max/m0);

	// Calculate the various terms in the integrals
	Double_t norm1 = TMath::Sqrt(termMax)*TMath::Exp(-xi*termMax) - TMath::Sqrt(termMin)*TMath::Exp(-xi*termMin);
	Double_t norm2 = LauConstants::rootPi/(2.0*TMath::Sqrt(xi)) * ( TMath::Erf(TMath::Sqrt(xi*termMax)) - TMath::Erf(TMath::Sqrt(xi*termMin)) );

	// Combine them and set the normalisation
	Double_t norm = m0*m0*(norm1 - norm2)/(2.0*xi);

	this->setNorm(norm);
}

void LauArgusPdf::calcPDFHeight( const LauKinematics* /*kinematics*/ )
{
	if (this->heightUpToDate()) {
		return;
	}

	// Calculate the PDF height of the ARGUS function.
	// Get the up to date parameter values
	Double_t xi = xi_->value();
	Double_t m0 = m0_->value();

	// First make sure that the limits are not larger than the end-point.
	// (Btw, use the logarithmic derivative to derive this formula) 
	Double_t term = xi*xi + 1.0;
	Double_t x = TMath::Sqrt((TMath::Sqrt(term) - 1.0 + xi)/(2.0*xi));
	x = (x*m0 >= this->getMinAbscissa()) ? x*m0 : this->getMinAbscissa();

	LauAbscissas abscissa(1);
	abscissa[0] = x;
	this->calcLikelihoodInfo(abscissa);

	Double_t height = this->getUnNormLikelihood();
	this->setMaxHeight(height);
}

