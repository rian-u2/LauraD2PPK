
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauParametricStepFuncPdf.cc
    \brief File containing implementation of LauParametricStepFuncPdf class.
*/

/*****************************************************************************
 * Class based on RooFit/RooParametricStepFunction.                          *
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
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

#include "TMath.h"
#include "TSystem.h"

#include "LauConstants.hh"
#include "LauParametricStepFuncPdf.hh"

ClassImp(LauParametricStepFuncPdf)


LauParametricStepFuncPdf::LauParametricStepFuncPdf(const TString& theVarName, const vector<LauAbsRValue*>& params, const vector<Double_t>& limits, NormBin normalisationBin) :
	LauAbsPdf(theVarName, params, limits.front(), limits.back()),
	normBin_(normalisationBin),
	limits_(limits)
{
	// Constructor for the PSF PDF.
	//
	// The parameters in params are the bin contents of all but the
	// normalisation bin, so has N_bins-1 entries.
	// The last argument specifies the limits of the bins and the range
	// as a whole, so has N_bins+1 entries.

	if (this->nParameters() != this->nBins()-1) {
		cerr<<"ERROR in LauParametricStepFuncPdf constructor: LauParametricStepFuncPdf requires N-1 parameters, where N is the number of bins."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor
	this->calcNorm();
}

LauParametricStepFuncPdf::~LauParametricStepFuncPdf() 
{
	// Destructor
}

void LauParametricStepFuncPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the parameters
	const vector<LauAbsRValue*>& pars = this->getParameters();

	// Calculate value
	Double_t value(0.0);
	const UInt_t numBins = this->nBins();

	if ( this->normBin() == Last ) {
		// the last bin is our normalisation bin
		for ( UInt_t i(1); i<=numBins; ++i ) {
			if ( abscissa < limits_[i] ) {
				// in bin i-1 (starting with bin 0)
				if ( i < numBins ) {
					// not in last bin
					value = pars[i-1]->unblindValue();
					break;
				} else {
					// in last bin
					Double_t sum(0.0);
					Double_t binSize(0.0);
					for ( UInt_t j(1); j<numBins; ++j ) {
						binSize = limits_[j] - limits_[j-1];
						sum += ( pars[j-1]->unblindValue() * binSize );
					}
					binSize = limits_[numBins] - limits_[numBins-1];
					value = ( 1.0 - sum ) / binSize;
					break;
				}
			}
		}
	} else {
		// the first bin is our normalisation bin
		for ( UInt_t i(1); i<=numBins; ++i ) {
			if ( abscissa < limits_[i] ) {
				// in bin i-1 (starting with bin 0)
				if ( i > 1 ) {
					// not in first bin
					value = pars[i-2]->unblindValue();
					break;
				} else {
					// in first bin
					Double_t sum(0.0);
					Double_t binSize(0.0);
					for ( UInt_t j(2); j<=numBins; ++j ) {
						binSize = limits_[j] - limits_[j-1];
						sum += ( pars[j-2]->unblindValue() * binSize );
					}
					binSize = limits_[1] - limits_[0];
					value = ( 1.0 - sum ) / binSize;
					break;
				}
			}
		}
	}

	this->setUnNormPDFVal(value);

	// if the parameters are floating then we
	// need to recalculate the normalisation
	if (!this->cachePDF() && !this->withinNormCalc() && !this->withinGeneration()) {
		this->calcNorm();
	}
}

void LauParametricStepFuncPdf::calcNorm() 
{
	this->setNorm(1.0);
}

void LauParametricStepFuncPdf::calcPDFHeight( const LauKinematics* /*kinematics*/ )
{
	if (this->heightUpToDate()) {
		return;
	}

	// Get the parameters
	const vector<LauAbsRValue*>& pars = this->getParameters();

	// Find the PDF height
	Double_t height(0.0);
	Double_t value(0.0);
	const UInt_t numBins = this->nBins();

	if ( this->normBin() == Last ) {
		// the last bin is our normalisation bin

		// Check through all the parameterised bins
		for ( UInt_t i(0); i<numBins-1; ++i ) {
			value = pars[i]->unblindValue();
			if ( height < value ) {
				height = value;
			}
		}

		// Check the last bin
		Double_t sum(0.0);
		Double_t binSize(0.0);
		for ( UInt_t j(1); j<numBins; ++j ) {
			binSize = limits_[j] - limits_[j-1];
			sum += ( pars[j-1]->unblindValue() * binSize );
		}
		binSize = limits_[numBins] - limits_[numBins-1];
		value = ( 1.0 - sum ) / binSize;
		if ( height < value ) {
			height = value;
		}
	} else {
		// the first bin is our normalisation bin

		// Check through all the parameterised bins
		for ( UInt_t i(1); i<numBins; ++i ) {
			value = pars[i-1]->unblindValue();
			if ( height < value ) {
				height = value;
			}
		}

		// Check the first bin
		Double_t sum(0.0);
		Double_t binSize(0.0);
		for ( UInt_t j(2); j<=numBins; ++j ) {
			binSize = limits_[j] - limits_[j-1];
			sum += ( pars[j-2]->unblindValue() * binSize );
		}
		binSize = limits_[1] - limits_[0];
		value = ( 1.0 - sum ) / binSize;
		if ( height < value ) {
			height = value;
		}
	}

	this->setMaxHeight(height);
}

