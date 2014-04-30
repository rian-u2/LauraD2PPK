
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPolNR.cc
    \brief File containing implementation of LauPolNR class.
*/

#include <iostream>

#include "TMath.h"

#include "LauPolNR.hh"
#include "LauDaughters.hh"

ClassImp(LauPolNR)


LauPolNR::LauPolNR(const TString& resName, LauParameter* resMass, LauParameter* resWidth, Int_t resSpin,
		   Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	omega_(0.0),
	order_(0)
{
}

LauPolNR::~LauPolNR()
{
}

void LauPolNR::initialise()
{
	const LauDaughters* daughters = this->getDaughters();
	Int_t resPairAmpInt = this->getPairInt();
	if ( daughters->gotSymmetricalDP() && resPairAmpInt != 3 ) {
		std::cerr << "WARNING in LauPolNR::initialise : Dalitz plot is symmetric - this lineshape is not appropriate." << std::endl;
	}

	this->ignoreMomenta(kTRUE);

	Double_t omega = 0.5*(daughters->getMassParent()+(1.0/3.0)*(daughters->getMassDaug1()+daughters->getMassDaug2()+daughters->getMassDaug3()));
	this->setOmega( omega );

	TString name = this->getResonanceName();
	if (name.EndsWith("0",TString::kExact)){
		order_ = 0;
	}
	else if (name.EndsWith("1",TString::kExact)){
		order_ = 1;
	}
	else if (name.EndsWith("2",TString::kExact)){
		order_ = 2;
	}
	else if (name.EndsWith("3",TString::kExact)){
		order_ = 3;
	}
	else{
		std::cerr << "ERROR in LauPolNR::initialise : Resonance order unknown (known orders : 0, 1, 2 and 3)" << std::endl;
		std::cerr << "                              : Defaulting to 0." << std::endl;
	}
}

LauComplex LauPolNR::resAmp(Double_t mass, Double_t spinTerm)
{
	Double_t magnitude( spinTerm );

	Double_t massDiff = mass - omega_;
	for ( UInt_t i(0); i < order_; ++i ) {
		magnitude *= massDiff;
	}

	LauComplex resAmplitude(magnitude, 0.0);

	return resAmplitude;
}

