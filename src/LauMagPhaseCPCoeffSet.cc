
// Copyright University of Warwick 2011 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauMagPhaseCPCoeffSet.cc
    \brief File containing implementation of LauMagPhaseCPCoeffSet class.
*/

#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"
#include "TRandom.h"

#include "LauMagPhaseCPCoeffSet.hh"
#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

ClassImp(LauMagPhaseCPCoeffSet)


LauMagPhaseCPCoeffSet::LauMagPhaseCPCoeffSet(const TString& compName, Double_t mag, Double_t phase, Double_t magBar, Double_t phaseBar,
		Bool_t magFixed, Bool_t phaseFixed,Bool_t magBarFixed, Bool_t phaseBarFixed) :
	LauAbsCoeffSet(compName),
	minMag_(-40.0),
	maxMag_(+40.0),
	minPhase_(-LauConstants::threePi),
	maxPhase_(+LauConstants::threePi),
	mag_(new LauParameter("Mag", mag, minMag_, maxMag_, magFixed)),
	phase_(new LauParameter("Phase", phase, minPhase_, maxPhase_, phaseFixed)),
	magBar_(new LauParameter("MagBar", magBar, minMag_, maxMag_, magBarFixed)),
	phaseBar_(new LauParameter("PhaseBar", phaseBar, minPhase_, maxPhase_, phaseBarFixed)),
	acp_("ACP", (magBar*magBar - mag*mag)/(magBar*magBar + mag*mag), -1.0, 1.0)
{
	// Print message
	cout<<"Set component \""<<this->name()<<"\" to have mag = "<<mag_->value()<<",\tphase = "<<phase_->value()<<",\t";
	cout<<"magBar = "<<magBar_->value()<<",\tphaseBar = "<<phaseBar_->value()<<"."<<endl;

}

LauMagPhaseCPCoeffSet::LauMagPhaseCPCoeffSet(const LauMagPhaseCPCoeffSet& rhs, Double_t constFactor) : LauAbsCoeffSet(rhs.name())
{
	minMag_ = rhs.minMag_;
	maxMag_ = rhs.maxMag_;
	minPhase_ = rhs.minPhase_;
	maxPhase_ = rhs.maxPhase_;
	mag_ = rhs.mag_->createClone(constFactor);
	phase_ = rhs.phase_->createClone(constFactor);
	magBar_ = rhs.magBar_->createClone(constFactor);
	phaseBar_ = rhs.phaseBar_->createClone(constFactor);
	acp_ = rhs.acp_;
}

LauMagPhaseCPCoeffSet& LauMagPhaseCPCoeffSet::operator=(const LauMagPhaseCPCoeffSet& rhs)
{
	if (&rhs == this) {
		return *this;
	}
	this->name(rhs.name());
	minMag_ = rhs.minMag_;
	maxMag_ = rhs.maxMag_;
	minPhase_ = rhs.minPhase_;
	maxPhase_ = rhs.maxPhase_;
	mag_ = rhs.mag_->createClone();
	phase_ = rhs.phase_->createClone();
	magBar_ = rhs.magBar_->createClone();
	phaseBar_ = rhs.phaseBar_->createClone();
	acp_ = rhs.acp_;
	return *this;
}

std::vector<LauParameter*> LauMagPhaseCPCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(mag_);
	pars.push_back(phase_);
	pars.push_back(magBar_);
	pars.push_back(phaseBar_);
	return pars;
}

void LauMagPhaseCPCoeffSet::printTableHeading(std::ostream& stream)
{
	stream<<"\\begin{tabular}{|l|c|c|c|c|}"<<endl;
	stream<<"\\hline"<<endl;
	stream<<"Component & Magnitude & Phase & Magnitude_bar & Phase_bar \\\\"<<endl;
	stream<<"\\hline"<<endl;
}

void LauMagPhaseCPCoeffSet::printTableRow(std::ostream& stream)
{
	LauPrint print;
	TString resName = this->name();
	resName = resName.ReplaceAll("_", "\\_");
	stream<<resName<<"  &  $";
	print.printFormat(stream, mag_->value());
	stream<<" \\pm ";
	print.printFormat(stream, mag_->error());
	stream<<"$  &  $";
	print.printFormat(stream, phase_->value());
	stream<<" \\pm ";
	print.printFormat(stream, phase_->error());
	stream<<"$  &  $";
	print.printFormat(stream, magBar_->value());
	stream<<" \\pm ";
	print.printFormat(stream, magBar_->error());
	stream<<"$  &  $";
	print.printFormat(stream, phaseBar_->value());
	stream<<" \\pm ";
	print.printFormat(stream, phaseBar_->error());
	stream<<"$ \\\\"<<endl;
}

void LauMagPhaseCPCoeffSet::randomiseInitValues()
{
	if (mag_->fixed() == kFALSE) {
		// Choose a value for "magnitude" between 0.0 and 2.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*2.0;
		mag_->initValue(value); mag_->value(value);
	}
	if (phase_->fixed() == kFALSE) {
		// Choose a phase between +- pi
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*LauConstants::twoPi - LauConstants::pi;
		phase_->initValue(value); phase_->value(value);
	}
	if (magBar_->fixed() == kFALSE) {
		// Choose a value for "magnitude" between 0.0 and 2.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*2.0;
		magBar_->initValue(value); magBar_->value(value);
	}
	if (phaseBar_->fixed() == kFALSE) {
		// Choose a phase between +- pi
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*LauConstants::twoPi - LauConstants::pi;
		phaseBar_->initValue(value); phaseBar_->value(value);
	}
}

void LauMagPhaseCPCoeffSet::finaliseValues()
{
	// retrieve the current values from the parameters
	Double_t mVal= mag_->value();
	Double_t pVal= phase_->value();
	Double_t mBarVal= magBar_->value();
	Double_t pBarVal= phaseBar_->value();
	Double_t genPhase = phase_->genValue();
	Double_t genPhaseBar   = phaseBar_->genValue();
	
	// Check whether we have a negative magnitude.
	// If so make it positive and add pi to the  phase.
	if (mVal < 0.0) {
		mVal *= -1.0;
		pVal += LauConstants::pi;
	}
	if (mBarVal < 0.0) {
		mBarVal *= -1.0;
		pBarVal += LauConstants::pi;
	}

	// Check now whether the phases lies in the right range (-pi to pi).
	Bool_t pWithinRange(kFALSE);
	Bool_t pBarWithinRange(kFALSE);
	while (pWithinRange == kFALSE && pBarWithinRange == kFALSE) {
		if (pVal > -LauConstants::pi && pVal < LauConstants::pi) {
			pWithinRange = kTRUE;
		} else {
			// Not within the specified range
			if (pVal > LauConstants::pi) {
				pVal -= LauConstants::twoPi;
			} else if (pVal < -LauConstants::pi) {
				pVal += LauConstants::twoPi;
			}
		}

		if (pBarVal > -LauConstants::pi && pBarVal < LauConstants::pi) {
			pBarWithinRange = kTRUE;
		} else {
			// Not within the specified range
			if (pBarVal > LauConstants::pi) {
				pBarVal -= LauConstants::twoPi;
			} else if (pBarVal < -LauConstants::pi) {
				pBarVal += LauConstants::twoPi;
			}
		}
	}

	// A further problem can occur when the generated phase is close to -pi or pi.
	// The phase can wrap over to the other end of the scale -
	// this leads to artificially large pulls so we wrap it back.
	Double_t diff = pVal - genPhase;
	if (diff > LauConstants::pi) {
		pVal -= LauConstants::twoPi;
	} else if (diff < -LauConstants::pi) {
		pVal += LauConstants::twoPi;
	}

	diff = pBarVal - genPhaseBar;
	if (diff > LauConstants::pi) {
		pBarVal -= LauConstants::twoPi;
	} else if (diff < -LauConstants::pi) {
		pBarVal += LauConstants::twoPi;
	}

	// finally store the new values in the parameters
	// and update the pulls
	mag_->value(mVal);          	mag_->updatePull();
	phase_->value(pVal);          	phase_->updatePull();
	magBar_->value(mBarVal);  	magBar_->updatePull();
	phaseBar_->value(pBarVal);      phaseBar_->updatePull();


}

LauComplex LauMagPhaseCPCoeffSet::particleCoeff()
{
	return LauComplex( mag_->value()*TMath::Cos(phase_->value()), mag_->value()*TMath::Sin(phase_->value()) );
}

LauComplex LauMagPhaseCPCoeffSet::antiparticleCoeff()
{
	return LauComplex( magBar_->value()*TMath::Cos(phaseBar_->value()), magBar_->value()*TMath::Sin(phaseBar_->value()) );
}

void LauMagPhaseCPCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar )
{
	mag_->value( coeff.abs() );
	phase_->value( coeff.arg() );

	magBar_->value( coeffBar.abs() );
	phaseBar_->value( coeffBar.arg() );
}

LauParameter LauMagPhaseCPCoeffSet::acp()
{
	// set the name
	TString parName(this->baseName()); parName += "_ACP";
	acp_.name(parName);

	// work out the ACP value

	Double_t value(-99.0);
	value = (magBar_->value()*magBar_->value() - mag_->value()*mag_->value())/(magBar_->value()*magBar_->value() + mag_->value()*mag_->value()); 

	// is it fixed?
	Bool_t fixed = magBar_->fixed() && mag_->fixed();
	acp_.fixed(fixed);

	// we can't work out the error without the covariance matrix
	Double_t error(0.0);

	// set the value and error
	acp_.valueAndErrors(value,error);

	return acp_;
}

LauAbsCoeffSet* LauMagPhaseCPCoeffSet::createClone(const TString& newName, Double_t constFactor)
{
	LauAbsCoeffSet* clone = new LauMagPhaseCPCoeffSet( *this, constFactor );
	clone->name( newName );
	return clone;
}

