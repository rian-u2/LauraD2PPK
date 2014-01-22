
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauEffModel.cc
    \brief File containing implementation of LauEffModel class.
*/

#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TSystem.h"
#include "Lau2DHistDP.hh"
#include "Lau2DSplineDP.hh"
#include "LauDaughters.hh"
#include "LauEffModel.hh"
#include "LauKinematics.hh"
#include "LauVetoes.hh"

ClassImp(LauEffModel)


LauEffModel::LauEffModel(const LauDaughters* daughters, const LauVetoes* vetoes) :
	daughters_( daughters ),
	vetoes_( vetoes ),
	effHisto_( 0 ),
	squareDP_( kFALSE ),
	fluctuateEffHisto_( kFALSE )
{
	if ( daughters_ == 0 ) {
		cerr << "ERROR in LauEffModel Constructor : invalid pointer to daughters object supplied." << endl;
		gSystem->Exit(EXIT_FAILURE);
	}
}

/*LauEffModel::LauEffModel( const LauEffModel& rhs ) :
	daughters_( rhs.daughters_ ),
	vetoes_( rhs.vetoes_ ),
	effHisto_( rhs.effHisto_ ? new Lau2DHistDP( *rhs.effHisto_ ) : 0 ),
	squareDP_( rhs.squareDP_ ),
	fluctuateEffHisto_( rhs.fluctuateEffHisto_ )
{
}*/

LauEffModel::~LauEffModel()
{
	if (effHisto_ != 0) {
		delete effHisto_; effHisto_ = 0;
	}
}

void LauEffModel::setEffHisto(const TH2* effHisto, Bool_t useInterpolation,
		Bool_t fluctuateBins, Double_t avEff, Double_t absError,
		Bool_t useUpperHalfOnly, Bool_t squareDP)
{
	// Set the efficiency across the Dalitz plot using a predetermined 2D histogram
	// with x = m_13^2, y = m_23^2.
	Bool_t upperHalf( kFALSE );
	if ( daughters_->gotSymmetricalDP() && useUpperHalfOnly == kTRUE) {upperHalf = kTRUE;}
	cout<<"Efficiency histogram has upperHalf = "<<static_cast<Int_t>(upperHalf)<<endl;

	squareDP_ = squareDP;

	if(effHisto_) {
		delete effHisto_;
		effHisto_=0;
	}

	// Copy the histogram.
	effHisto_ = new Lau2DHistDP(effHisto, daughters_,
			useInterpolation, fluctuateBins,
			avEff, absError, upperHalf, squareDP);
	fluctuateEffHisto_ = fluctuateBins;

	if (avEff > 0.0 && absError > 0.0) {
		fluctuateEffHisto_ = kTRUE;
	}
}

void LauEffModel::setEffSpline(const TH2* effHisto,
		Bool_t fluctuateBins, Double_t avEff, Double_t absError,
		Bool_t useUpperHalfOnly, Bool_t squareDP)
{
	// Set the efficiency across the Dalitz plot using a predetermined 2D histogram
	// with x = m_13^2, y = m_23^2.
	Bool_t upperHalf( kFALSE );
	if ( daughters_->gotSymmetricalDP() && useUpperHalfOnly == kTRUE) {upperHalf = kTRUE;}
	cout<<"Efficiency histogram has upperHalf = "<<static_cast<Int_t>(upperHalf)<<endl;

	squareDP_ = squareDP;

	if(effHisto_) {
		delete effHisto_;
		effHisto_=0;
	}

	// Copy the histogram.
	effHisto_ = new Lau2DSplineDP(effHisto, daughters_,
			fluctuateBins, avEff, absError, upperHalf, squareDP);
	fluctuateEffHisto_ = fluctuateBins;

	if (avEff > 0.0 && absError > 0.0) {
		fluctuateEffHisto_ = kTRUE;
	}
}

Double_t LauEffModel::getEffHistValue(Double_t xVal, Double_t yVal) const
{
	// Get the efficiency from the 2D histo.
	Double_t eff(1.0);

	if (effHisto_ != 0) {
		eff = effHisto_->interpolateXY(xVal, yVal);
	}

	return eff;
}

Double_t LauEffModel::calcEfficiency( const LauKinematics* kinematics ) const
{
	// Routine to calculate the efficiency for the given event/point in
	// the Dalitz plot. This routine uses the 2D histogram set by the
	// setEffHisto() funciton.
	Double_t eff(1.0);

	// Check for vetoes
	Bool_t vetoOK(kTRUE);
	if ( vetoes_ != 0 ) {
		vetoOK = vetoes_->passVeto(kinematics);
	}

	if (vetoOK == kFALSE) {    
		// We failed the veto. 
		eff = 0.0;
	} else {
		// We are using a 2D histogram representation of the efficiency across the Dalitz plot.
		// First find out which bin we are in given the x and y Dalitz plot mass values
		// Here, x = m13^2, y = m23^2 or if using square DP x = m', y = theta'.
		if (squareDP_ == kTRUE) {
			eff = this->getEffHistValue(kinematics->getmPrime(), kinematics->getThetaPrime());
		} else {
			eff = this->getEffHistValue(kinematics->getm13Sq(), kinematics->getm23Sq());
		}
	}

	// Check that the efficiency is in the allowed range (0-1)
	if ( eff < 0.0 ) {
		std::cerr << "WARNING in LauEffModel::calcEfficiency : Efficiency is less than 0 - setting to 0.  You may want to check your histogram!" << std::endl;
		eff = 0.0;
	} else if ( eff > 1.0 ) {
		std::cerr << "WARNING in LauEffModel::calcEfficiency : Efficiency is greater than 1 - setting to 1.  You may want to check your histogram!" << std::endl;
		eff = 1.0;
	}

	return eff;
}

Bool_t LauEffModel::passVeto( const LauKinematics* kinematics ) const
{
	Bool_t pass = kTRUE;
	if ( vetoes_ != 0 ) {
		pass = vetoes_->passVeto( kinematics );
	}
	return pass;
}

