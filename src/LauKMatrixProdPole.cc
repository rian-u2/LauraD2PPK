
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
				       LauKMatrixPropagator* propagator, const LauDaughters* daughters, 
				       Bool_t useProdAdler) : 
	LauAbsResonance(poleName, resPairAmpInt, daughters),
	thePropagator_(propagator),
        poleIndex_(poleIndex - 1), // poleIndex goes from 1 to nPoles
        useProdAdler_(useProdAdler)
{

        if (useProdAdler_) {
	    std::cout<<"Creating K matrix production pole "<<poleName<<" with poleIndex = "
		     <<poleIndex<<" with s-dependent production Adler zero term"<<std::endl;
	} else {
	    std::cout<<"Creating K matrix production pole "<<poleName<<" with poleIndex = "
		     <<poleIndex<<" with production Adler zero factor = 1"<<std::endl;
	}

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

	// Include Adler zero factor if requested
	Double_t adlerZero(1.0);
	if (useProdAdler_) {adlerZero = thePropagator_->getAdlerZero();}

	amp.rescale(poleDenom*adlerZero);

	return amp;

}
