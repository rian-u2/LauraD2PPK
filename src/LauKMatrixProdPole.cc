
// Copyright University of Warwick 2008 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixProdPole.cc
    \brief File containing implementation of LauKMatrixProdPole class.
*/

#include "LauKMatrixProdPole.hh"
#include "LauKMatrixPropagator.hh"

#include <iostream>

ClassImp(LauKMatrixProdPole)

LauKMatrixProdPole::LauKMatrixProdPole(const TString& poleName, Int_t poleIndex, Int_t resPairAmpInt,
				       LauKMatrixPropagator* propagator, const LauDaughters* daughters) : 
	LauAbsResonance(poleName, 0, 0, 0, 0, resPairAmpInt, daughters),
	thePropagator_(propagator),
	poleIndex_(poleIndex - 1) // poleIndex goes from 1 to nPoles
{
}

LauKMatrixProdPole::~LauKMatrixProdPole() 
{
}

LauComplex LauKMatrixProdPole::resAmp(Double_t mass, Double_t spinTerm)
{
	std::cerr << "ERROR in LauKMatrixProdPole::resAmp : This method shouldn't get called." << std::endl;
	std::cerr << "                                      Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}

LauComplex LauKMatrixProdPole::amplitude(const LauKinematics* kinematics)
{

	// Calculate the amplitude for the K-matrix production pole.
	// First, make sure the K-matrix propagator is up-to-date for 
	// the given centre-of-mass squared value ("s") from the kinematics.
	LauComplex amp(0.0, 0.0);

	if (thePropagator_ == 0) {
		std::cerr << "ERROR in LauKMatrixProdPole::amplitude : The propagator is null" << std::endl;
		return amp;
	}

	thePropagator_->updatePropagator(kinematics);

	// Sum the pole denominator terms over all channels j, multiplying by
	// the propagator terms. Note that we do not sum over poles, since we
	// only want one of the production pole terms.
	Int_t nChannels = thePropagator_->getNChannels();
	Int_t jChannel;

	for (jChannel = 0; jChannel < nChannels; jChannel++) {

		Double_t gj = thePropagator_->getCouplingConstant(poleIndex_, jChannel);
		LauComplex prodTerm = thePropagator_->getPropTerm(jChannel);

		prodTerm.rescale(gj);

		amp += prodTerm;

	}

	Double_t poleDenom = thePropagator_->getPoleDenomTerm(poleIndex_);
	amp.rescale(poleDenom);

	return amp;

}
