
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWaveSymRealImag.cc
    \brief File containing implementation of LauModIndPartWaveSymRealImag class.
*/

#include <cstdlib>
#include <iostream>

#include "TSpline.h"

#include "LauConstants.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"
#include "LauModIndPartWaveSymRealImag.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauModIndPartWaveSymRealImag)


LauModIndPartWaveSymRealImag::LauModIndPartWaveSymRealImag(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauModIndPartWaveRealImag(resInfo, resPairAmpInt, daughters),
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
		std::cerr << "ERROR in LauModIndPartWaveSymRealImag constructor : Invalid daughters pointer" << std::endl;
	}
}

LauModIndPartWaveSymRealImag::~LauModIndPartWaveSymRealImag()
{
}

LauComplex LauModIndPartWaveSymRealImag::amplitude(const LauKinematics* kinematics)
{
	if ( kinematics_ == 0 ) {
		return this->LauAbsResonance::amplitude(kinematics_);
	}

	const Double_t m13Sq = kinematics->getm13Sq();
	const Double_t m23Sq = kinematics->getm23Sq();

	if ( m13Sq > m23Sq ) {
		kinematics_->updateKinematics( m23Sq, m13Sq );
	} else {
		kinematics_->updateKinematics( m13Sq, m23Sq );
	}

	return this->LauAbsResonance::amplitude(kinematics_);
}

