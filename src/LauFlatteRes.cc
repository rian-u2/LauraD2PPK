
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFlatteRes.cc
    \brief File containing implementation of LauFlatteRes class.
*/

#include <iostream>

#include "LauConstants.hh"
#include "LauFlatteRes.hh"

ClassImp(LauFlatteRes)


LauFlatteRes::LauFlatteRes(TString resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
	resMassSq_(0.0),
	g1_(0.0),
	g2_(0.0),
	mSumSq0_(0.0),
	mSumSq1_(0.0),
	mSumSq2_(0.0),
	mSumSq3_(0.0)
{
	// constant factors from BES data
	// resMass_ should be 0.965 +/- 0.008 +/- 0.006 GeV/c^2
	g1_ = 0.165;     // +/- 0.010 +/- 0.015 GeV/c^2
	g2_ = g1_*4.21;  // +/- 0.25 +/- 0.21

	// or from E791
	//g1_ = 0.09;
	//g2_ = 0.02;

	// or from CERN/WA76
	//g1_ = 0.28;
	//g2_ = 0.56;
}

LauFlatteRes::~LauFlatteRes()
{
}

void LauFlatteRes::initialise()
{
	Double_t resMass = this->getMass();
	resMassSq_ = resMass*resMass;

	const TString& resName = this->getResonanceName();
	if (resName != "f_0(980)") {
		std::cerr << "WARNING in LauFlatteRes::initialise : Unexpected resonance name \"" << resName << "\" for Flatte shape." << std::endl;
		std::cerr << "                                    : Setting parameters to \"f0_980\" values." << std::endl;
	}

	mSumSq0_ = (LauConstants::mPi0 + LauConstants::mPi0) * (LauConstants::mPi0 + LauConstants::mPi0);
	mSumSq1_ = (LauConstants::mPi + LauConstants::mPi) * (LauConstants::mPi + LauConstants::mPi);
	mSumSq2_ = (LauConstants::mK + LauConstants::mK) * (LauConstants::mK + LauConstants::mK);
	mSumSq3_ = (LauConstants::mK0 + LauConstants::mK0) * (LauConstants::mK0 + LauConstants::mK0);
}

void LauFlatteRes::setGFactors(Double_t g1, Double_t g2)
{
	this->setg1Parameter(g1);
	this->setg2Parameter(g2);
}

void LauFlatteRes::setResonanceParameter(const TString& name, const Double_t value) 
{
	if (name == "g1") {
		this->setg1Parameter(value);
		TString g1name = "gPiPi";
		std::cout << "INFO in LauFlatteRes::setResonanceParameter : Setting " << g1name <<" Parameter to " << this->getg1Parameter() << std::endl;
	} else if (name == "g2") {
		this->setg2Parameter(value);
		TString g2name = "gKK";
		std::cout << "INFO in LauFlatteRes::setResonanceParameter : Setting " << g2name << " Parameter to " << this->getg2Parameter() << std::endl;  
	} else {
		std::cerr << "WARNING in LauFlatteRes::setResonanceParameter : Parameter name \"" << name << "\" not recognised." << std::endl;
	}
}  

LauComplex LauFlatteRes::resAmp(Double_t mass, Double_t spinTerm)
{
	// This function returns the complex dynamical amplitude for a Flatte distribution
	// given the invariant mass and cos(helicity) values.

	Double_t resMass = this->getMass();
	Double_t s = mass*mass; // Invariant mass squared combination for the system
	Double_t dMSq = resMassSq_ - s;

	Double_t rho1(0.0), rho2(0.0);
	if (s > mSumSq0_) {
		rho1 = TMath::Sqrt(1.0 - mSumSq0_/s)/3.0;
		if (s > mSumSq1_) {
			rho1 += 2.0*TMath::Sqrt(1.0 - mSumSq1_/s)/3.0;
			if (s > mSumSq2_) {
				rho2 = 0.5*TMath::Sqrt(1.0 - mSumSq2_/s);
				if (s > mSumSq3_) {
					rho2 += 0.5*TMath::Sqrt(1.0 - mSumSq3_/s);
				} else {
					// Continue analytically below higher channel thresholds
					// This contributes to the real part of the amplitude denominator
					dMSq += g2_*resMass*0.5*TMath::Sqrt(mSumSq3_/s - 1.0);
				}
			} else {
				// Continue analytically below higher channel thresholds
				// This contributes to the real part of the amplitude denominator
				rho2 = 0.0;
				dMSq += g2_*resMass*(0.5*TMath::Sqrt(mSumSq2_/s - 1.0) + 0.5*TMath::Sqrt(mSumSq3_/s - 1.0));
			}
		} else {
			// Continue analytically below higher channel thresholds
			// This contributes to the real part of the amplitude denominator
			dMSq += g1_*resMass*2.0*TMath::Sqrt(mSumSq1_/s - 1.0)/3.0;
		}
	}

	Double_t width1 = g1_*rho1*resMass;
	Double_t width2 = g2_*rho2*resMass;
	Double_t widthTerm = width1 + width2;

	LauComplex resAmplitude(dMSq, widthTerm);

	Double_t denomFactor = dMSq*dMSq + widthTerm*widthTerm;

	Double_t invDenomFactor = 0.0;
	if (denomFactor > 1e-10) {invDenomFactor = 1.0/denomFactor;}

	resAmplitude.rescale(spinTerm*invDenomFactor);

	return resAmplitude;
}

