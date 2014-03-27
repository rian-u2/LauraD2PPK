
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DAbsHistDP.cc
    \brief File containing implementation of Lau2DAbsHistDP class.
*/

#include <iostream>

#include "TAxis.h"
#include "TH2.h"
#include "TRandom.h"
#include "TSystem.h"

#include "Lau2DAbsHistDP.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"
#include "LauRandom.hh"

ClassImp(Lau2DAbsHistDP)


Lau2DAbsHistDP::Lau2DAbsHistDP(const LauDaughters* daughters, Bool_t useUpperHalfOnly, Bool_t squareDP) :
	kinematics_( (daughters!=0) ? daughters->getKinematics() : 0 ),
	upperHalf_(useUpperHalfOnly),
	squareDP_(squareDP)
{
}

Lau2DAbsHistDP::~Lau2DAbsHistDP()
{
}

void Lau2DAbsHistDP::doBinFluctuation(TH2* hist)
{
	TRandom* random = LauRandom::randomFun();

	Int_t nBinsX = static_cast<Int_t>(hist->GetNbinsX());
	Int_t nBinsY = static_cast<Int_t>(hist->GetNbinsY());

	for (Int_t i(0); i<nBinsX; ++i) {
		for (Int_t j(0); j<nBinsY; ++j) {
			Double_t currentContent = hist->GetBinContent(i+1,j+1);
			Double_t currentError   = hist->GetBinError(i+1,j+1);
			Double_t newContent = random->Gaus(currentContent,currentError);
			if (newContent<0.0) {
				hist->SetBinContent(i+1,j+1,0.0);
			} else {
				hist->SetBinContent(i+1,j+1,newContent);
			}
		}
	}
}

void Lau2DAbsHistDP::raiseOrLowerBins(TH2* hist, Double_t avEff, Double_t avEffError)
{
	TRandom* random = LauRandom::randomFun();

	Double_t curAvg = this->computeAverageContents(hist);
	Double_t newAvg = random->Gaus(avEff,avEffError);

	hist->Scale( newAvg / curAvg );
}

Double_t Lau2DAbsHistDP::computeAverageContents(TH2 const * const hist) const
{
	Double_t totalContent(0.0);
	Int_t binsWithinDPBoundary(0);

	Int_t nBinsX = static_cast<Int_t>(hist->GetNbinsX());
	Int_t nBinsY = static_cast<Int_t>(hist->GetNbinsY());

	// Loop through the bins and include any that have their centre or any
	// of the four corners within the kinematic boundary
	for ( Int_t i(0); i<nBinsX; ++i ) {
		Double_t binXCentre = hist->GetXaxis()->GetBinCenter(i+1);
		Double_t binXLowerEdge = hist->GetXaxis()->GetBinLowEdge(i+1);
		Double_t binXUpperEdge = hist->GetXaxis()->GetBinUpEdge(i+1);

		for ( Int_t j(0); j<nBinsY; ++j ) {
			Double_t binYCentre = hist->GetYaxis()->GetBinCenter(i+1);
			Double_t binYLowerEdge = hist->GetYaxis()->GetBinLowEdge(i+1);
			Double_t binYUpperEdge = hist->GetYaxis()->GetBinUpEdge(i+1);

			if ( withinDPBoundaries( binXCentre, binYCentre ) ||
			     withinDPBoundaries( binXLowerEdge, binYLowerEdge ) ||
			     withinDPBoundaries( binXUpperEdge, binYUpperEdge ) ||
			     withinDPBoundaries( binXLowerEdge, binYUpperEdge ) ||
			     withinDPBoundaries( binXUpperEdge, binYLowerEdge ) ) {

				totalContent += hist->GetBinContent(i+1, j+1);
				++binsWithinDPBoundary;
			}
		}
	}

	return totalContent/binsWithinDPBoundary;
}

Bool_t Lau2DAbsHistDP::withinDPBoundaries(Double_t x, Double_t y) const
{
	return squareDP_ ? kinematics_->withinSqDPLimits(x,y) : kinematics_->withinDPLimits(x,y);
}

void Lau2DAbsHistDP::getUpperHalf(Double_t& x, Double_t& y) const
{
	if ( upperHalf_ == kTRUE ) {
		if ( squareDP_ == kFALSE && x > y ) {
			Double_t temp = y;
			y = x;
			x = temp;
		} else if ( squareDP_ == kTRUE && y > 0.5 ) {
			y = 1.0 - y;
		}
	}
}
