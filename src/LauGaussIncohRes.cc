
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGaussIncohRes.cc
    \brief File containing implementation of LauGaussIncohRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauGaussIncohRes.hh"
#include "LauKinematics.hh"

ClassImp(LauGaussIncohRes)

LauGaussIncohRes::LauGaussIncohRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsIncohRes(resInfo, resPairAmpInt, daughters)
{
}

LauGaussIncohRes::~LauGaussIncohRes()
{
}

void LauGaussIncohRes::initialise()
{
}

Double_t LauGaussIncohRes::intensityFactor(const LauKinematics* kinematics)
{
	Int_t pair = this->getPairInt();
	Double_t mass(0.);

	switch(pair) {
		case 1:
			mass = kinematics->getm23();
			break;
		case 2:
			mass = kinematics->getm13();
			break;
		case 3:
			mass = kinematics->getm12();
			break;
		default:
			std::cerr << "ERROR in LauGaussIncohRes::intensityFactor : Incorrect daughter pair defined." << std::endl;
			std::cerr << "                             Returning zero intensity." << std::endl;
			return 0.;
	}

	Double_t m0 = this->getMass();
	Double_t G0 = this->getWidth();

	if(G0==0) {
		std::cerr << "ERROR in LauGaussIncohRes::intensityFactor : Gaussian width cannot be zero." << std::endl;
		std::cerr << "                             Returning zero intensity." << std::endl;
		return 0.;
	}

	Double_t exponent = -0.5 * ( mass - m0 ) * (mass - m0 ) / (G0*G0);
	Double_t intensity = TMath::Exp(exponent);

	return intensity;
}

const std::vector<LauParameter*>& LauGaussIncohRes::getFloatingParameters()
{
	this->clearFloatingParameters();

	if ( ! this->fixMass() ) {
		this->addFloatingParameter( this->getMassPar() );
	}
	if ( ! this->fixWidth() ) {
		this->addFloatingParameter( this->getWidthPar() );
	}

	return this->getParameters();
}

