
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauNRAmplitude.cc
    \brief File containing implementation of LauNRAmplitude class.
*/

#include <iostream>

#include "LauKinematics.hh"
#include "LauNRAmplitude.hh"

ClassImp(LauNRAmplitude)

LauNRAmplitude::LauNRAmplitude(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
	d_(1.3232e-3),
	c1_(0.65),
	c2_(0.55),
	p1_(18.0),
	p2_(15.0)
{
}

LauNRAmplitude::~LauNRAmplitude()
{
}

void LauNRAmplitude::initialise()
{
}

LauComplex LauNRAmplitude::amplitude(const LauKinematics* kinematics)
{
	// Get the information from the kinematics object
	Double_t m13Sq = kinematics->getm13Sq();
	Double_t m23Sq = kinematics->getm23Sq();
	Double_t m13 = kinematics->getm13();
	Double_t m23 = kinematics->getm23();

	// Calculate the magnitude
	Double_t magnitude = TMath::Sqrt( m13 * m23 *
			                  this->f(m23Sq, c1_, p1_) * 
					  this->f(m13Sq, c2_, p2_) * 
					  TMath::Exp( -1.0 * d_ * m13Sq*m13Sq * m23Sq*m23Sq )
				        );

	// return the amplitude
	LauComplex resAmplitude(magnitude, 0.0);
	return resAmplitude;
}

LauComplex LauNRAmplitude::resAmp(Double_t mass, Double_t spinTerm)
{
	std::cerr << "ERROR in LauNRAmplitude::resAmp : This method shouldn't get called." << std::endl;
	std::cerr << "                                  Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}

Double_t LauNRAmplitude::f(Double_t s, Double_t c, Double_t p) const
{
	return 1.0 / (1.0 + TMath::Exp( c * (s-p) ));
}

