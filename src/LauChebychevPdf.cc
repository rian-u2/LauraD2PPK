
// Copyright University of Warwick 2009 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauChebychevPdf.cc
    \brief File containing implementation of LauChebychevPdf class.
*/

/*****************************************************************************
 * Class based on RooFit/RooChebychev.                                       *
 * Original copyright given below.                                           *
 *****************************************************************************
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

#include <iostream>
#include <vector>

#include "TMath.h"
#include "TSystem.h"

#include "LauChebychevPdf.hh"

ClassImp(LauChebychevPdf)

LauChebychevPdf::LauChebychevPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa) :
	LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
	coeffs_(params.size(),0)
{
	// Constructor for the Chebychev Polynomial PDF.
	//
	// The parameters in params are the coefficients of the polynomial
	// (polynomial can be anything from 0 to 7 orders).
	// The last two arguments specify the range in which the PDF is defined, and the PDF
	// will be normalised w.r.t. these limits.

	if ( (this->nParameters() > 7) ) {
		std::cerr << "ERROR in LauChebychevPdf constructor: Too many coeffs - can only cope with order <=7 polynomial." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	for ( UInt_t i(0); i < this->nParameters(); ++i ) {
		TString name = "c";
		name += i+1;
		coeffs_[i] = this->findParameter( name );
	}

	// Cache the normalisation factor
	this->calcNorm();
}

LauChebychevPdf::~LauChebychevPdf() 
{
	// Destructor
}

LauChebychevPdf::LauChebychevPdf(const LauChebychevPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa())
{
	// Copy constructor
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

//inline static double p0(double ,double a) {  return a; }
inline static double p1(double t,double a,double b) {  return a*t+b; }
inline static double p2(double t,double a,double b,double c) {  return p1(t,p1(t,a,b),c); }
inline static double p3(double t,double a,double b,double c,double d) {  return p2(t,p1(t,a,b),c,d); }
//inline static double p4(double t,double a,double b,double c,double d,double e) {  return p3(t,p1(t,a,b),c,d,e); }

void LauChebychevPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	Double_t xmin = this->getMinAbscissa();
	Double_t xmax = this->getMaxAbscissa();
	Double_t x(-1.0+2.0*(abscissa-xmin)/(xmax-xmin));
	Double_t x2(x*x);
	Double_t sum(0) ;
	switch ( coeffs_.size() ) {
		case  7: sum += coeffs_[6]->value()*x*p3(x2,64,-112,56,-7);
		case  6: sum += coeffs_[5]->value()*p3(x2,32,-48,18,-1);
		case  5: sum += coeffs_[4]->value()*x*p2(x2,16,-20,5);
		case  4: sum += coeffs_[3]->value()*p2(x2,8,-8,1);
		case  3: sum += coeffs_[2]->value()*x*p1(x2,4,-3);
		case  2: sum += coeffs_[1]->value()*p1(x2,2,-1);
		case  1: sum += coeffs_[0]->value()*x;
		case  0: sum +=1;
	}

	this->setUnNormPDFVal( sum );

	// if the parameters are floating then we
	// need to recalculate the normalisation
	if (!this->cachePDF() && !this->withinNormCalc() && !this->withinGeneration()) {
		this->calcNorm();
	}
}

void LauChebychevPdf::calcNorm()
{
	Double_t xmin = this->getMinAbscissa();
	Double_t xmax = this->getMaxAbscissa();

	Double_t norm(0) ;
	switch( coeffs_.size() ) {
		case  7: case  6: norm += coeffs_[5]->value()*(-1 + 18./3. - 48./5. + 32./7.);
		case  5: case  4: norm += coeffs_[3]->value()*( 1 -  8./3. +  8./5.);
		case  3: case  2: norm += coeffs_[1]->value()*(-1 +  2./3.);
		case  1: case  0: norm += 1;
	}
	norm *= xmax-xmin;

	this->setNorm(norm);
}

void LauChebychevPdf::calcPDFHeight(const LauKinematics* /*kinematics*/)
{
	// TODO - this method can hopefully be improved
	// At present it scans through the range and then increases by a 20% safety factor
	// Maybe there's a better way?

	if (this->heightUpToDate()) {
		return;
	}

	// Calculate the PDF height
	LauAbscissas maxPoint(1);

	Double_t minAbs = this->getMinAbscissa();
	Double_t maxAbs = this->getMaxAbscissa();
	Double_t range = maxAbs - minAbs;
	Double_t maxHeight(0.0);

	// Just scan through the range
	for ( Double_t point = minAbs; point <= maxAbs; point += range/1000.0 ) {
		maxPoint[0] = point;
		this->calcLikelihoodInfo(maxPoint);
		Double_t heightAtPoint = this->getUnNormLikelihood();
		if ( heightAtPoint > maxHeight ) {
			maxHeight = heightAtPoint;
		}
	}


	// Mutliply by 120% to be on the safe side
	maxHeight *= 1.2;

	this->setMaxHeight(maxHeight);
}
