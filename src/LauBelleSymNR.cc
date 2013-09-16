
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleSymNR.cc
    \brief File containing implementation of LauBelleSymNR class.
*/

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"

#include "LauBelleSymNR.hh"
#include "LauKinematics.hh"

ClassImp(LauBelleSymNR)


LauBelleSymNR::LauBelleSymNR(const TString& resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	alpha_(0.0),
	initialised_(kFALSE),
	shapeNo_(0)
{
}

LauBelleSymNR::~LauBelleSymNR()
{
	// Destructor
}

void LauBelleSymNR::initialise(Bool_t symmetricalDP, Double_t alpha, const TString& shape)
{
	alpha_ = alpha;  
	shapeNo_ = 0;

	if (symmetricalDP == kFALSE) {
		cerr << "ERROR in LauBelleSymNR::initialise : Dalitz plot is not symmetric - this lineshape is not appropriate." << endl;
		return;
	}

	if (shape == "BelleSymNR") {
		cout << "Initialising the Belle non-resonant model with alpha = " << alpha << endl;
		shapeNo_ = 1; 
	} else if (shape == "NRTaylor") {
		cout << "Initialising the Taylor expansion non-resonant model with alpha = " << alpha << endl; 
		shapeNo_ = 2;
	} else {
		cerr << "ERROR in LauBelleSymNR::initialise : Non-resonant parameterisation not recognised." << endl;
		return;
	}

	initialised_ = kTRUE;
}

LauComplex LauBelleSymNR::amplitude(const LauKinematics* kinematics)
{
	if (initialised_ == kFALSE) {
		cerr<<"ERROR in LauBelleSymNR::amplitude : LauBelleSymNR is not initialised. Returning zero amplitude."<<endl;
		return LauComplex(0.0, 0.0);
	}

	// This function returns the complex dynamical amplitude for a Belle Non-Resonant distribution

	// Calculate for symmetric DPs, e.g. 3pi or 3K, by using shapeNo = 1 or 2
	// Have s<->t symmetry already done in Dynamics flip function.
	// For Kpipi or similar plots, one can use the separate exponentials
	// and consider them as two separate components with their own mag and phase.
	// For this shapeNo = 3 and shapeNo = 4 need to be used to create the two
	// individual amplitudes (with the same value of alpha).

	// Calculate Mandelstam variables.
	// s = m_13^2, t = m_23^2, u = m_12^2. 
	Double_t s = kinematics->getm13Sq();
	Double_t t = kinematics->getm23Sq();
	//Double_t u = kinematics->getm12Sq();

	Double_t magnitude(1.0);

	if (shapeNo_ == 1) {
		magnitude = TMath::Exp(-alpha_*s) + TMath::Exp(-alpha_*t);
	} else if (shapeNo_ == 2) {
		Double_t mParentSq = kinematics->getmParentSq();
		magnitude = alpha_*(s + t)/mParentSq + 1.0;
	}

	LauComplex resAmplitude(magnitude, 0.0);

	return resAmplitude;

}

LauComplex LauBelleSymNR::resAmp(Double_t mass, Double_t spinTerm)
{
	cerr << "ERROR in LauBelleSymNR : This method should never be called." << endl;
	cerr << "                       : Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << endl;
	return LauComplex(0.0, 0.0);
}

