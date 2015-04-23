
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWaveSymMagPhase.cc
    \brief File containing implementation of LauModIndPartWaveSymMagPhase class.
*/

#include <cstdlib>
#include <iostream>

#include "LauConstants.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"
#include "LauModIndPartWaveSymMagPhase.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauModIndPartWaveSymMagPhase)


LauModIndPartWaveSymMagPhase::LauModIndPartWaveSymMagPhase(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauModIndPartWaveMagPhase(resInfo, resPairAmpInt, daughters),
	kinematics_(0)
{
	if ( daughters != 0 ) {
		kinematics_ = new LauKinematics(
				daughters->getMassDaug1(),
				daughters->getMassDaug2(),
				daughters->getMassDaug3(),
				daughters->getMassParent(),
				daughters->squareDP()
				);
	} else {
		std::cerr << "ERROR in LauModIndPartWaveSymMagPhase constructor : Invalid daughters pointer" << std::endl;
	}
}

LauModIndPartWaveSymMagPhase::~LauModIndPartWaveSymMagPhase()
{
}

std::set<Double_t> LauModIndPartWaveSymMagPhase::checkKnots(const std::set<Double_t>& masses)
{
	if ( kinematics_ == 0 ) {
		return this->LauAbsModIndPartWave::checkKnots(masses);
	}

	std::set<Double_t> knots = masses;

	const std::set<Double_t>::const_iterator first = knots.begin();
	const std::set<Double_t>::const_reverse_iterator last = knots.rbegin();

	const Double_t lower_limit = this->getMassDaug1() + this->getMassDaug2();
	kinematics_->updateSqDPKinematics(1.0,0.5);
	const Double_t upper_limit = kinematics_->getm13();

	// check whether we have been given knots at unphysical masses
	if ( *first < lower_limit ) {
		std::cerr << "WARNING in LauModIndPartWaveSymMagPhase::checkKnots : Knot found at mass " << *first << " is below the lower kinematic limit." << std::endl;
		std::cerr << "                                                    : Lower kinematic limit is at mass " << lower_limit << std::endl;
		std::cerr << "                                                    : Aborting definition of knot positions." << std::endl;
		knots.clear();
		return knots;
	}
	if ( *last > upper_limit ) {
		std::cerr << "WARNING in LauModIndPartWaveSymMagPhase::checkKnots : Knot found at mass " << *last << " is above the upper kinematic limit." << std::endl;
		std::cerr << "                                                    : Upper kinematic limit is at mass " << upper_limit << std::endl;
		std::cerr << "                                                    : Aborting definition of knot positions." << std::endl;
		knots.clear();
		return knots;
	}

	// check if we have knots at each extreme - if not, add them in
	if ( (*first) != lower_limit ) {
		knots.insert( lower_limit );
	}
	if ( (*last)  != upper_limit ) {
		knots.insert( upper_limit );
	}

	return knots;
}

LauComplex LauModIndPartWaveSymMagPhase::amplitude(const LauKinematics* kine)
{
	if ( kinematics_ == 0 ) {
		return this->LauAbsResonance::amplitude(kine);
	}

	const Double_t m13Sq = kine->getm13Sq();
	const Double_t m23Sq = kine->getm23Sq();

	if ( m13Sq > m23Sq ) {
		kinematics_->updateKinematics( m23Sq, m13Sq );
	} else {
		kinematics_->updateKinematics( m13Sq, m23Sq );
	}

	return this->LauAbsResonance::amplitude(kinematics_);
}

