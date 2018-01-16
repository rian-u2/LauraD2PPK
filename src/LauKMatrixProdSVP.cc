
/*
Copyright 2008 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauKMatrixProdSVP.cc
    \brief File containing implementation of LauKMatrixProdSVP class.
*/

#include "LauKMatrixProdSVP.hh"
#include "LauKMatrixPropagator.hh"

#include <iostream>

ClassImp(LauKMatrixProdSVP)

LauKMatrixProdSVP::LauKMatrixProdSVP(const TString& SVPName, Int_t channelIndex, Int_t resPairAmpInt,
		                     LauKMatrixPropagator* propagator, const LauDaughters* daughters,
				     Bool_t useProdAdler) : 
	LauAbsResonance(SVPName, resPairAmpInt, daughters),
	thePropagator_(propagator),
        channelIndex_(channelIndex - 1), // channelIndex goes from 1 to nChannels.
        useProdAdler_(useProdAdler)
{
	// Constructor
        if (useProdAdler_) {
	    std::cout<<"Creating K matrix production SVP "<<SVPName<<" with channelIndex = "
		     <<channelIndex<<" with s-dependent production Adler zero term"<<std::endl;
	} else {
	    std::cout<<"Creating K matrix production SVP "<<SVPName<<" with channelIndex = "
		     <<channelIndex<<" with production Adler zero factor = 1"<<std::endl;
	}


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

	// Include Adler zero factor if requested
	Double_t adlerZero(1.0);
	if (useProdAdler_) {adlerZero = thePropagator_->getAdlerZero();}

	amp.rescale(SVPTerm*adlerZero);

	return amp;

}

