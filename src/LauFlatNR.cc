
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFlatNR.cc
    \brief File containing implementation of LauFlatNR class.
*/

#include <iostream>

#include "LauKinematics.hh"
#include "LauFlatNR.hh"

ClassImp(LauFlatNR)

LauFlatNR::LauFlatNR(TString resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters)
{
}

LauFlatNR::~LauFlatNR()
{
}

void LauFlatNR::initialise()
{
}

LauComplex LauFlatNR::amplitude(const LauKinematics* /*kinematics*/)
{
	// return the uniform amplitude
	return LauComplex(1.0, 0.0);
}

LauComplex LauFlatNR::resAmp(Double_t mass, Double_t spinTerm)
{
	std::cerr << "ERROR in LauFlatNR::resAmp : This method shouldn't get called." << std::endl;
	std::cerr << "                             Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}

