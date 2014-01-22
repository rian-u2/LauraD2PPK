
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DSplineDP.cc
    \brief File containing implementation of Lau2DSplineDP class.
*/

#include <iostream>

#include "TAxis.h"
#include "TH2.h"
#include "TRandom.h"
#include "TSystem.h"

#include "Lau2DSplineDP.hh"
#include "Lau2DCubicSpline.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"
#include "LauRandom.hh"

ClassImp(Lau2DSplineDP)


Lau2DSplineDP::Lau2DSplineDP(const TH2* hist, const LauDaughters* daughters,
		Bool_t fluctuateBins, Double_t avEff, Double_t avEffError, 
		Bool_t useUpperHalfOnly, Bool_t squareDP) :
	Lau2DAbsHistDP(daughters,useUpperHalfOnly,squareDP),
	spline_(0)
{
	//We may need to modify the histogram so clone it
	TH2* tempHist(hist ? dynamic_cast<TH2*>(hist->Clone()) : 0);

	if ( ! tempHist ) {
		std::cerr << "ERROR in Lau2DSplineDP constructor : the histogram pointer is null." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if (fluctuateBins) {
		this->doBinFluctuation(tempHist);
	}
	if (avEff > 0.0 && avEffError > 0.0) {
		this->raiseOrLowerBins(tempHist,avEff,avEffError);
	}

	spline_ = new Lau2DCubicSpline(*tempHist);

	delete tempHist;
}

Lau2DSplineDP::~Lau2DSplineDP()
{
	delete spline_;
	spline_ = 0;
}

Double_t Lau2DSplineDP::interpolateXY(Double_t x, Double_t y) const
{
	// This function returns the interpolated value of the histogram function
	// for the given values of x and y by finding the adjacent bins and extrapolating
	// using weights based on the inverse distance of the point from the adajcent
	// bin centres.
	// Here, x = m13^2, y = m23^2, or m', theta' for square DP co-ordinates

	// If we're only using one half then flip co-ordinates
	// appropriately for conventional or square DP
	getUpperHalf(x,y);

	// First ask whether the point is inside the kinematic region.
	if (withinDPBoundaries(x,y) == kFALSE) {
		std::cerr << "WARNING in Lau2DSplineDP::interpolateXY : Given position is outside the DP boundary, returning 0.0." << std::endl;
		return 0.0;
	}

	return spline_->evaluate(x,y);

}
