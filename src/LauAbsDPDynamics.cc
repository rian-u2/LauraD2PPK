
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsDPDynamics.cc
    \brief File containing implementation of LauAbsDPDynamics class.
*/

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TSystem.h"

#include "LauAbsDPDynamics.hh"
#include "LauComplex.hh"
#include "LauDaughters.hh"
#include "LauAbsEffModel.hh"
#include "LauKinematics.hh"
#include "LauResonanceMaker.hh"

ClassImp(LauAbsDPDynamics)


LauAbsDPDynamics::LauAbsDPDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, LauAbsEffModel* scfFractionModel) :
	daughters_(daughters),
	resonanceMaker_(new LauResonanceMaker(daughters)),
	kinematics_(daughters_ ? daughters_->getKinematics() : 0),
	effModel_(effModel),
	nAmp_(0),
	nResDefMax_(resonanceMaker_ ? resonanceMaker_->getNResDefMax() : 0),
	DPNorm_(0.0),
	DPRate_("DPRate", 0.0, 0.0, 1000.0),
	meanDPEff_("meanDPEff", 0.0, 0.0, 1.0),
	currentEvent_(0)
{
	if (scfFractionModel != 0) {
		scfFractionModel_[0] = scfFractionModel;
	}
	extraParameters_.clear();
}

LauAbsDPDynamics::LauAbsDPDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, const LauTagCatScfFractionModelMap& scfFractionModel) :
	daughters_(daughters),
	resonanceMaker_(new LauResonanceMaker(daughters)),
	kinematics_(daughters_ ? daughters_->getKinematics() : 0),
	effModel_(effModel),
	scfFractionModel_(scfFractionModel),
	nAmp_(0),
	nResDefMax_(resonanceMaker_ ? resonanceMaker_->getNResDefMax() : 0),
	DPNorm_(0.0),
	DPRate_("DPRate", 0.0, 0.0, 1000.0),
	meanDPEff_("meanDPEff", 0.0, 0.0, 1.0),
	currentEvent_(0)
{
	extraParameters_.clear();
}

LauAbsDPDynamics::~LauAbsDPDynamics()
{
	if (resonanceMaker_ != 0) {
		delete resonanceMaker_; resonanceMaker_ = 0;
	}
	extraParameters_.clear();

	for ( std::vector<LauCacheData*>::iterator iter = data_.begin(); iter != data_.end(); ++iter ) {
		delete (*iter);
	}
}

void LauAbsDPDynamics::setDataEventNo(UInt_t iEvt)
{
	// Retrieve the data for event iEvt
	if (data_.size() > iEvt) {
		currentEvent_ = data_[iEvt];
	} else {
		cerr<<"ERROR in LauAbsDPDynamics::setDataEventNo : Event index too large: "<<iEvt<<" >= "<<data_.size()<<"."<<endl;
	}
}

void LauAbsDPDynamics::updateCoeffs(const std::vector<LauComplex>& coeffs)
{
	// Check that the number of coeffs is correct
	if (coeffs.size() != this->getnAmp()) {
		cerr << "ERROR in LauAbsDPDynamics::updateCoeffs : Expected " << this->getnAmp() << " but got " << coeffs.size() << endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Now check if the coeffs have changed
	Bool_t changed = (Amp_ != coeffs);
	if (changed) {
		// Copy the coeffs
		Amp_ = coeffs;

		// Update the total normalisation for the signal likelihood
		this->calcSigDPNorm();
	}
}

Bool_t LauAbsDPDynamics::hasResonance(const TString& resName) const
{
	const LauAbsResonance* theRes = this->findResonance(resName);
	if (theRes != 0) {
		return kTRUE;
	} else {
		return kFALSE;
	}
}

TString LauAbsDPDynamics::getConjResName(const TString& resName) const
{
       // Get the name of the charge conjugate resonance
       TString conjName(resName);

       Ssiz_t index1 = resName.Index("+");
       Ssiz_t index2 = resName.Index("-");
       if (index1 != -1) {
                conjName.Replace(index1, 1, "-");
       } else if (index2 != -1) {
                conjName.Replace(index2, 1, "+");
       }

       return conjName;

}

Double_t LauAbsDPDynamics::retrieveEfficiency()
{
	Double_t eff(1.0);
	if (effModel_ != 0) {
		eff = effModel_->calcEfficiency(kinematics_);
	}
	return eff;
}

Double_t LauAbsDPDynamics::retrieveScfFraction(Int_t tagCat)
{
	Double_t scfFraction(0.0);

	// scf model and eff model are exactly the same, functionally
	// so we use an instance of LauAbsEffModel, and the method
	// calcEfficiency actually calculates the scf fraction
	if (tagCat == -1) {
		if (!scfFractionModel_.empty()) {
			scfFraction = scfFractionModel_[0]->calcEfficiency(kinematics_);
		}
	} else {
		scfFraction = scfFractionModel_[tagCat]->calcEfficiency(kinematics_);
	}
	return scfFraction;
}

