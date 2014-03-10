
// Copyright University of Warwick 2008 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixProdSVP.cc
    \brief File containing implementation of LauKMatrixProdSVP class.
*/

#include "LauKMatrixProdSVP.hh"
#include "LauKMatrixPropagator.hh"

#include <iostream>

ClassImp(LauKMatrixProdSVP)

LauKMatrixProdSVP::LauKMatrixProdSVP(const TString& poleName, Int_t channelIndex, Int_t resPairAmpInt,
		                     LauKMatrixPropagator* propagator, const LauDaughters* daughters) : 
	LauAbsResonance(poleName, 0, 0, 0, 0, resPairAmpInt, daughters),
	thePropagator_(propagator),
	channelIndex_(channelIndex - 1) // channelIndex goes from 1 to nChannels.
{
	// Constructor
}

LauKMatrixProdSVP::~LauKMatrixProdSVP() 
{
	// Destructor
}

LauComplex LauKMatrixProdSVP::resAmp(Double_t mass, Double_t spinTerm)
{
	std::cerr << "ERROR in LauKMatrixProdSVP::resAmp : This method shouldn't get called." << std::endl;
	std::cerr << "                                     Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}

LauComplex LauKMatrixProdSVP::amplitude(const LauKinematics* kinematics)
{

	// Calculate the amplitude for the K-matrix production pole.
	// First, make sure the K-matrix propagator is up-to-date for 
	// the given centre-of-mass squared value ("s") from the kinematics.
	LauComplex amp(0.0, 0.0);

	if (thePropagator_ == 0) {
		std::cerr << "ERROR in LauKMatrixProdSVP::amplitude : The propagator is null" << std::endl;
		return amp;
	}

	thePropagator_->updatePropagator(kinematics);

	Double_t SVPTerm = thePropagator_->getProdSVPTerm();

	amp = thePropagator_->getPropTerm(channelIndex_);
	amp.rescale(SVPTerm);

	return amp;

}

