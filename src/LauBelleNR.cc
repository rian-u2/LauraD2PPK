
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleNR.cc
    \brief File containing implementation of LauBelleNR class.
*/

#include <iostream>

#include "TMath.h"

#include "LauBelleNR.hh"
#include "LauDaughters.hh"

ClassImp(LauBelleNR)


LauBelleNR::LauBelleNR(const TString& resName, const LauAbsResonance::LauResonanceModel resType,
		       LauParameter* resMass, LauParameter* resWidth,
		       const Int_t resSpin, const Int_t resCharge, const Int_t resPairAmpInt,
		       const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	alpha_(0.0),
	model_(resType)
{
}

LauBelleNR::~LauBelleNR()
{
}

void LauBelleNR::initialise()
{
	const LauDaughters* daughters = this->getDaughters();
	Int_t resPairAmpInt = this->getPairInt();
	if ( daughters->gotSymmetricalDP() && resPairAmpInt != 3 ) {
		std::cerr << "WARNING in LauBelleNR::initialise : Dalitz plot is symmetric - this lineshape is not appropriate." << std::endl;
	}

	if ( model_ != LauAbsResonance::BelleNR && model_ != LauAbsResonance::PowerLawNR ) {
		std::cerr << "WARNING in LauBelleNR::initialise : Unknown model requested, defaulting to exponential." << std::endl;
		model_ = LauAbsResonance::BelleNR;
	}

	// TODO - should the BelleNR ignore the momenta in the spin term?
}

LauComplex LauBelleNR::resAmp(Double_t mass, Double_t spinTerm)
{
	Double_t magnitude(1.0);

	if ( model_ == LauAbsResonance::BelleNR ) {
		magnitude = spinTerm * TMath::Exp(-alpha_*mass*mass);
	} else if ( model_ == LauAbsResonance::PowerLawNR ) {
		magnitude = spinTerm * TMath::Power(mass*mass, -alpha_);
	}

	LauComplex resAmplitude(magnitude, 0.0);

	return resAmplitude;
}

void LauBelleNR::setResonanceParameter(const TString& name, const Double_t value) 
{
	// Set various parameters for the lineshape
	if (name == "alpha") {
		this->setAlpha(value);
		std::cout << "INFO in LauBelleNR::setResonanceParameter : Setting parameter alpha = " << this->getAlpha() << std::endl;
	} else {
		std::cerr << "WARNING in LauBelleNR::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

