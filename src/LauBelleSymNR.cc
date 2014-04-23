
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

#include "TMath.h"

#include "LauBelleSymNR.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"

ClassImp(LauBelleSymNR)


LauBelleSymNR::LauBelleSymNR(const TString& resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	alpha_(0.0),
	initialised_(kFALSE),
	shapeNo_(0)
{
	if ( !resName.CompareTo("BelleSymNR" ) ) {
		shapeNo_ = 1;
	} else if ( !resName.CompareTo("NRTaylor") ) {
		shapeNo_ = 2;
	}
}

LauBelleSymNR::~LauBelleSymNR()
{
}

void LauBelleSymNR::initialise()
{
	const LauDaughters* daughters = this->getDaughters();
	Int_t resPairAmpInt = this->getPairInt();
	if ( ! daughters->gotSymmetricalDP() ) {
		std::cerr << "WARNING in LauBelleSymNR::initialise : Dalitz plot is symmetric - this lineshape is not appropriate." << std::endl;
	}
	if ( resPairAmpInt == 3 ) {
		std::cerr << "WARNING in LauBelleSymNR::initialise : This lineshape is intended to be on the symmetrised axes of the DP." << std::endl;
	}

	if ( shapeNo_ == 0 ) {
		std::cerr << "ERROR in LauBelleSymNR::initialise : Non-resonant parameterisation not recognised." << std::endl;
	}

	initialised_ = kTRUE;
}

LauComplex LauBelleSymNR::amplitude(const LauKinematics* kinematics)
{
	if (initialised_ == kFALSE) {
		std::cerr<<"ERROR in LauBelleSymNR::amplitude : LauBelleSymNR is not initialised. Returning zero amplitude."<<std::endl;
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
	std::cerr << "ERROR in LauBelleSymNR : This method should never be called." << std::endl;
	std::cerr << "                       : Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}

void LauBelleSymNR::setResonanceParameter(const TString& name, const Double_t value) 
{
	// Set various parameters for the lineshape
	if (name == "alpha") {
		this->setAlpha(value);
		std::cout << "INFO in LauBelleSymNR::setResonanceParameter : Setting parameter alpha = " << this->getAlpha() << std::endl;
	}
	else {
		std::cerr << "WARNING in LauBelleSymNR::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

