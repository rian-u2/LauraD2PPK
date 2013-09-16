
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleNR.cc
    \brief File containing implementation of LauBelleNR class.
*/

//****************************************************************************
// Class for defining the Belle Non-Resonant model
//****************************************************************************

// --CLASS DESCRIPTION [MODEL] --
// Class for defining the  Belle Non-Resonant model.

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"

#include "LauBelleNR.hh"
#include "LauDaughters.hh"

ClassImp(LauBelleNR)


LauBelleNR::LauBelleNR(const TString& resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	alpha_(0.0)
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
		cerr << "WARNING in LauBelleNR::initialise : Dalitz plot is symmetric - this lineshape is not appropriate." << endl;
	}
}

LauComplex LauBelleNR::resAmp(Double_t mass, Double_t spinTerm)
{
	Double_t magnitude = spinTerm * TMath::Exp(-alpha_*mass*mass);

	LauComplex resAmplitude(magnitude, 0.0);

	return resAmplitude;
}

