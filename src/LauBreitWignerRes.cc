
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBreitWignerRes.cc
    \brief File containing implementation of LauBreitWignerRes class.
*/

#include "LauBreitWignerRes.hh"

ClassImp(LauBreitWignerRes)


LauBreitWignerRes::LauBreitWignerRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters)
{
}

LauBreitWignerRes::~LauBreitWignerRes()
{
}

void LauBreitWignerRes::initialise()
{
}

LauComplex LauBreitWignerRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Breit-Wigner resonance,
	// given the invariant mass and cos(helicity) values.

	Double_t resMass = this->getMass();
	Double_t deltaM = mass - resMass;

	Double_t resWidthO2 = 0.5 * this->getWidth();
	Double_t resWidthO2Sq = resWidthO2*resWidthO2;

	LauComplex resAmplitude(deltaM, resWidthO2);

	resAmplitude.rescale(spinTerm/(deltaM*deltaM + resWidthO2Sq));

	return resAmplitude;
}

