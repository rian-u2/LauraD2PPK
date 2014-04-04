
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsResonance.cc
  \brief File containing implementation of LauAbsResonance class.
 */

//****************************************************************************
// Abstract class for defining resonance models (Breit-Wigner, Flatte etc.)
//****************************************************************************

// --CLASS DESCRIPTION [MODEL] --
// Abstract class for defining resonance models (Breit-Wigner, Flatte etc.)

#include <iostream>

#include "TSystem.h"

#include "LauAbsResonance.hh"
#include "LauConstants.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"

ClassImp(LauAbsResonance)


// Constructor
LauAbsResonance::LauAbsResonance(const TString& resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		                 Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	daughters_(daughters),
	nameParent_(""), nameDaug1_(""), nameDaug2_(""), nameBachelor_(""),
	chargeParent_(0), chargeDaug1_(0), chargeDaug2_(0), chargeBachelor_(0),
	massParent_(0.0), massDaug1_(0.0), massDaug2_(0.0), massBachelor_(0.0),
	resName_(resName),
	resMass_(resMass),
	resWidth_(resWidth),
	resSpin_(resSpin),
	resCharge_(resCharge),
	resPairAmpInt_(resPairAmpInt),
	flipHelicity_(kFALSE),
	ignoreMomenta_(kFALSE),
	q_(0.0),
	p_(0.0),
	pstar_(0.0)
{
	if (daughters_) {
		nameParent_ = this->getNameParent();
		nameDaug1_ = this->getNameDaug1();
		nameDaug2_ = this->getNameDaug2();
		nameBachelor_ = this->getNameBachelor();
		massParent_ = this->getMassParent();
		massDaug1_ = this->getMassDaug1();
		massDaug2_ = this->getMassDaug2();
		massBachelor_ = this->getMassBachelor();
		chargeParent_ = this->getChargeParent();
		chargeDaug1_ = this->getChargeDaug1();
		chargeDaug2_ = this->getChargeDaug2();
		chargeBachelor_ = this->getChargeBachelor();
	} else {
		std::cerr<<"ERROR in LauAbsResonance : daughters_ pointer is NULL."<<std::endl;
	}

	// check that the total charge adds up to that of the resonance
	Int_t totalCharge = chargeDaug1_ + chargeDaug2_;
	if ( (totalCharge != resCharge_) && (resName != "NonReson") && (!resName.BeginsWith("BelleNR")) ) {
		std::cerr<<"ERROR in LauAbsResonance : "<<"Total charge of daughters = "<<totalCharge<<". Resonance charge = "<<resCharge_<<"."<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
}

// Destructor
LauAbsResonance::~LauAbsResonance()
{
}

LauComplex LauAbsResonance::amplitude(const LauKinematics* kinematics)
{
	// Use LauKinematics interface for amplitude
	Double_t mass(0.0), cosHel(0.0);
	// For resonance made from tracks i, j, we need the momenta
	// of tracks i and k in the i-j rest frame for spin helicity calculations
	// in the Zemach tensor formalism.
	// Also need the momentum of track k in the parent rest-frame for
	// calculation of the Blatt-Weisskopf factors.
	q_ = 0.0;  p_ = 0.0;  pstar_ = 0.0;

	if (resPairAmpInt_ == 1) {

		mass   = kinematics->getm23();
		cosHel = kinematics->getc23();
		q_ = kinematics->getp2_23();
		p_ = kinematics->getp1_23();
		pstar_ = kinematics->getp1_Parent();

	} else if (resPairAmpInt_ == 2) {

		mass   = kinematics->getm13();
		cosHel = kinematics->getc13();
		q_ = kinematics->getp1_13();
		p_ = kinematics->getp2_13();
		pstar_ = kinematics->getp2_Parent();

	} else if (resPairAmpInt_ == 3) {

		mass   = kinematics->getm12();
		cosHel = kinematics->getc12();
		q_ = kinematics->getp1_12();
		p_ = kinematics->getp3_12();
		pstar_ = kinematics->getp3_Parent();

	} else {
		std::cerr<<"WARNING in LauAbsResonance::amplitude : Nonsense setup of resPairAmp array."<<std::endl;
	}

	if (this->flipHelicity()) {
		cosHel *= -1.0;
	}

	if (this->ignoreMomenta()) {
	  q_ = 1;
	  p_ = 1;
	}

	Double_t spinTerm(1.0);
	if (resSpin_ == 1) {
		// Calculate vector resonance Zemach helicity factor
		spinTerm = -2.0*q_*p_*cosHel;
	} else if (resSpin_ == 2) {
		// Calculate tensor resonance Zemach helicity factor
		Double_t pProd = q_*p_;
		spinTerm = 4.0*(pProd*pProd)*(3.0*cosHel*cosHel - 1.0)/3.0;
	} else if (resSpin_ == 3) {
		// Calculate spin 3 resonance Zemach helicity factor
		Double_t pProd = q_*p_;
		spinTerm = -8.0*3.0*(pProd*pProd*pProd)*(5.0*cosHel*cosHel*cosHel - 3.0*cosHel)/15.0;
	}

	LauComplex resAmplitude = this->resAmp(mass, spinTerm);

	return resAmplitude;
}

void LauAbsResonance::changeResonance(Double_t newMass, Double_t newWidth, Int_t newSpin)
{
	if (newMass > 0.0) {
		resMass_ = newMass;
		std::cout << "INFO in LauAbsResonance::changeResonance : Setting mass to " << resMass_ << std::endl;
	}
	if (newWidth > 0.0) {
		resWidth_ = newWidth;
		std::cout << "INFO in LauAbsResonance::changeResonance : Setting width to " << resWidth_ << std::endl;
	}
	if (newSpin > -1) {
		resSpin_ = newSpin;
		std::cout << "INFO in LauAbsResonance::changeResonance : Setting spin to " << resSpin_ << std::endl;
	}
	this->initialise();
}

void LauAbsResonance::setResonanceParameter(Double_t value, const TString& name)
{
	//This function should always be overwritten if needed in classes inheriting from LauAbsResonance.
	std::cerr << "WARNING in LauAbsResonance::setResonanceParameter : Unable to set parameter \"" << name << "\" to value: " << value << "." << std::endl;
}

Double_t LauAbsResonance::getMassParent() const
{
	// Get the parent mass
	Double_t mass(LauConstants::mB);

	if (daughters_) {
		mass = daughters_->getMassParent();
	}

	return mass;
}

Double_t LauAbsResonance::getMassDaug1() const
{
	// Get the daughter mass
	Double_t mass(LauConstants::mPi);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			mass = daughters_->getMassDaug2();
		} else if (resPairAmpInt_ == 2) {
			mass = daughters_->getMassDaug1();
		} else if (resPairAmpInt_ == 3) {
			mass = daughters_->getMassDaug1();
		}
	}

	return mass;
}

Double_t LauAbsResonance::getMassDaug2() const
{
	// Get the daughter mass
	Double_t mass(LauConstants::mPi);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			mass = daughters_->getMassDaug3();
		} else if (resPairAmpInt_ == 2) {
			mass = daughters_->getMassDaug3();
		} else if (resPairAmpInt_ == 3) {
			mass = daughters_->getMassDaug2();
		}
	}

	return mass;
}

Double_t LauAbsResonance::getMassBachelor() const
{
	// Get the bachelor mass
	Double_t mass(LauConstants::mPi);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			mass = daughters_->getMassDaug1();
		} else if (resPairAmpInt_ == 2) {
			mass = daughters_->getMassDaug2();
		} else if (resPairAmpInt_ == 3) {
			mass = daughters_->getMassDaug3();
		}
	}

	return mass;
}

Int_t LauAbsResonance::getChargeParent() const
{
	// Get the parent charge
	Int_t charge(0);

	if (daughters_) {
		charge = daughters_->getChargeParent();
	}

	return charge;
}

Int_t LauAbsResonance::getChargeDaug1() const
{
	// Get the daughter charge
	Int_t charge(0);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			charge = daughters_->getChargeDaug2();
		} else if (resPairAmpInt_ == 2) {
			charge = daughters_->getChargeDaug1();
		} else if (resPairAmpInt_ == 3) {
			charge = daughters_->getChargeDaug1();
		}
	}

	return charge;
}

Int_t LauAbsResonance::getChargeDaug2() const
{
	// Get the daughter charge
	Int_t charge(0);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			charge = daughters_->getChargeDaug3();
		} else if (resPairAmpInt_ == 2) {
			charge = daughters_->getChargeDaug3();
		} else if (resPairAmpInt_ == 3) {
			charge = daughters_->getChargeDaug2();
		}
	}

	return charge;
}

Int_t LauAbsResonance::getChargeBachelor() const
{
	// Get the bachelor charge
	Int_t charge(0);

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			charge = daughters_->getChargeDaug1();
		} else if (resPairAmpInt_ == 2) {
			charge = daughters_->getChargeDaug2();
		} else if (resPairAmpInt_ == 3) {
			charge = daughters_->getChargeDaug3();
		}
	}

	return charge;
}

TString LauAbsResonance::getNameParent() const
{
	// Get the parent name
	TString name("");

	if (daughters_) {
		name = daughters_->getNameParent();
	}

	return name;
}

TString LauAbsResonance::getNameDaug1() const
{
	// Get the daughter name
	TString name("");

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			name = daughters_->getNameDaug2();
		} else if (resPairAmpInt_ == 2) {
			name = daughters_->getNameDaug1();
		} else if (resPairAmpInt_ == 3) {
			name = daughters_->getNameDaug1();
		}
	}

	return name;
}

TString LauAbsResonance::getNameDaug2() const
{
	// Get the daughter name
	TString name("");

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			name = daughters_->getNameDaug3();
		} else if (resPairAmpInt_ == 2) {
			name = daughters_->getNameDaug3();
		} else if (resPairAmpInt_ == 3) {
			name = daughters_->getNameDaug2();
		}
	}

	return name;
}

TString LauAbsResonance::getNameBachelor() const
{
	// Get the bachelor name
	TString name("");

	if (daughters_) {
		if (resPairAmpInt_ == 1) {
			name = daughters_->getNameDaug1();
		} else if (resPairAmpInt_ == 2) {
			name = daughters_->getNameDaug2();
		} else if (resPairAmpInt_ == 3) {
			name = daughters_->getNameDaug3();
		}
	}

	return name;
}

