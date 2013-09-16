
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauVetoes.cc
    \brief File containing implementation of LauVetoes class.
*/

#include <iostream>

#include "LauKinematics.hh"
#include "LauVetoes.hh"

ClassImp(LauVetoes)


LauVetoes::LauVetoes() :
	nVetoes_(0)
{
}

LauVetoes::~LauVetoes()
{
}

LauVetoes::LauVetoes(const LauVetoes& other)
{
	nVetoes_ = other.nVetoes_;
	vetoPair_ = other.vetoPair_;
	vetoMinMass_ = other.vetoMinMass_;
	vetoMaxMass_ = other.vetoMaxMass_;
}

LauVetoes& LauVetoes::operator=(const LauVetoes& other)
{
	if ( &other != this ) {
		nVetoes_ = other.nVetoes_;
		vetoPair_ = other.vetoPair_;
		vetoMinMass_ = other.vetoMinMass_;
		vetoMaxMass_ = other.vetoMaxMass_;
	}
	return *this;
}

void LauVetoes::addMassVeto(Int_t resPairAmpInt, Double_t minMass, Double_t maxMass)
{

	Double_t minMassSq = minMass*minMass;
	Double_t maxMassSq = maxMass*maxMass;

	this->addMassSqVeto(resPairAmpInt, minMassSq, maxMassSq);
}

void LauVetoes::addMassSqVeto(Int_t resPairAmpInt, Double_t minMassSq, Double_t maxMassSq) 
{
	// Routine to add a veto in the Dalitz plot. The function takes as input the
	// bachelor track number (1, 2 or 3) and the mass-squared range of the veto.

	if (resPairAmpInt == 1) {

		// The bachelor track is the first track
		std::cout << "INFO in LauVetoes::addMassSqVeto : Adding the veto for resPairAmpInt = 1, with " << minMassSq << " < m^2_23 < " << maxMassSq << std::endl;

	} else if (resPairAmpInt == 2) {

		// The bachelor track is the second track
		std::cout << "INFO in LauVetoes::addMassSqVeto : Adding the veto for resPairAmpInt = 2, with " << minMassSq << " < m^2_13 < " << maxMassSq << std::endl;

	} else if (resPairAmpInt == 3) {

		// The bachelor track is the third track
		std::cout << "INFO in LauVetoes::addMassSqVeto : Adding the veto for resPairAmpInt = 3, with " << minMassSq << " < m^2_12 < " << maxMassSq << std::endl;

	} else {
		std::cerr << "ERROR in LauVetoes::addMassSqVeto : Invalid resPairAmpInt. Please use 1, 2 or 3 to specify bachelor daughter track. Veto is not added." << std::endl;
		return;
	}

	// Set the veto limits
	vetoPair_.push_back(resPairAmpInt);
	vetoMinMass_.push_back(minMassSq);
	vetoMaxMass_.push_back(maxMassSq);

	// Keep track of how many vetoes we have
	++nVetoes_;
}

Bool_t LauVetoes::passVeto(const LauKinematics* kinematics) const
{
	// Routine to ask whether the given Dalitz plot point passes any specified vetoes.
	if (kinematics == 0) {
		std::cerr << "ERROR in LauVetoes::passVeto : LauKinematics object is null." << std::endl;
		return kFALSE;
	}

	Double_t m12Sq = kinematics->getm12Sq();
	Double_t m23Sq = kinematics->getm23Sq();
	Double_t m13Sq = kinematics->getm13Sq();

	return passVeto(m12Sq, m23Sq, m13Sq);
}

Bool_t LauVetoes::passVeto(Double_t& m12Sq, Double_t& m23Sq, Double_t& m13Sq) const 
{
	// Routine to ask whether the given Dalitz plot point passes any specified vetoes.

	// Loop over the number of possible vetoes
	for ( Int_t i(0); i < nVetoes_; ++i) {

		if (vetoPair_[i] == 1) {
			// Veto m23 combination
			if (m23Sq > vetoMinMass_[i] && m23Sq < vetoMaxMass_[i]) {
				return kFALSE;
			}
		} else if (vetoPair_[i] == 2) {
			// Veto m13 combination
			if (m13Sq > vetoMinMass_[i] && m13Sq < vetoMaxMass_[i]) {
				return kFALSE;
			}
		} else if (vetoPair_[i] == 3) {
			// Veto m12 combination
			if (m12Sq > vetoMinMass_[i] && m12Sq < vetoMaxMass_[i]) {
				return kFALSE;
			}
		}
	}

	return kTRUE;
}

