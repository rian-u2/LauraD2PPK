
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauMagPhaseCoeffSet.cc
    \brief File containing implementation of LauMagPhaseCoeffSet class.
*/

#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"
#include "TRandom.h"

#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauMagPhaseCoeffSet.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

ClassImp(LauMagPhaseCoeffSet)


LauMagPhaseCoeffSet::LauMagPhaseCoeffSet(const TString& compName, Double_t magnitude, Double_t phase, Bool_t magFixed, Bool_t phaseFixed) :
	LauAbsCoeffSet(compName),
	minMag_(-10.0),
	maxMag_(+10.0),
	minPhase_(-LauConstants::threePi),
	maxPhase_(+LauConstants::threePi),
	magnitude_(new LauParameter("A",magnitude,minMag_,maxMag_,magFixed)),
	phase_(new LauParameter("Delta",phase,minPhase_,maxPhase_,phaseFixed))
{
	// Print message
	cout<<"Set component \""<<this->name()<<"\" to have magnitude = "<<magnitude_->value()<<" and phase = "<<phase_->value()<<"."<<endl;
}

LauMagPhaseCoeffSet::LauMagPhaseCoeffSet(const LauMagPhaseCoeffSet& rhs, Double_t constFactor) : LauAbsCoeffSet(rhs.name())
{
	minMag_ = rhs.minMag_;
	maxMag_ = rhs.maxMag_;
	minPhase_ = rhs.minPhase_;
	maxPhase_ = rhs.maxPhase_;
	magnitude_ = rhs.magnitude_->createClone(constFactor);
	phase_ = rhs.phase_->createClone(constFactor);
}

LauMagPhaseCoeffSet& LauMagPhaseCoeffSet::operator=(const LauMagPhaseCoeffSet& rhs)
{
	if (&rhs == this) {
		return *this;
	}
	this->name(rhs.name());
	minMag_ = rhs.minMag_;
	maxMag_ = rhs.maxMag_;
	minPhase_ = rhs.minPhase_;
	maxPhase_ = rhs.maxPhase_;
	magnitude_ = rhs.magnitude_->createClone();
	phase_ = rhs.phase_->createClone();
	return *this;
}

std::vector<LauParameter*> LauMagPhaseCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(magnitude_);
	pars.push_back(phase_);
	return pars;
}

void LauMagPhaseCoeffSet::printTableHeading(std::ostream& stream)
{
	stream<<"\\begin{tabular}{|l|c|c|}"<<endl;
	stream<<"\\hline"<<endl;
	stream<<"Component & Magnitude & Phase \\\\"<<endl;
	stream<<"\\hline"<<endl;
}

void LauMagPhaseCoeffSet::printTableRow(std::ostream& stream)
{
	LauPrint print;
	TString resName = this->name();
	resName = resName.ReplaceAll("_", "\\_");
	stream<<resName<<"  &  $";
	print.printFormat(stream, magnitude_->value());
	stream<<" \\pm ";
	print.printFormat(stream, magnitude_->error());
	stream<<"$  &  $";
	print.printFormat(stream, phase_->value());
	stream<<" \\pm ";
	print.printFormat(stream, phase_->error());
	stream<<"$ \\\\"<<endl;
}

void LauMagPhaseCoeffSet::randomiseInitValues()
{
	if (magnitude_->fixed() == kFALSE) {
		// Choose a magnitude between 0.0 and 2.0
		Double_t mag = LauRandom::zeroSeedRandom()->Rndm()*2.0;
		magnitude_->initValue(mag); magnitude_->value(mag);
	}
	if (phase_->fixed() == kFALSE) {
		// Choose a phase between +- pi
		Double_t phase = LauRandom::zeroSeedRandom()->Rndm()*LauConstants::twoPi - LauConstants::pi;
		phase_->initValue(phase); phase_->value(phase);
	}
}

void LauMagPhaseCoeffSet::finaliseValues()
{
	// retrieve the current values from the parameters
	Double_t mag      = magnitude_->value();
	Double_t phase    = phase_->value();
	Double_t genPhase = phase_->genValue();

	// Check whether we have a negative magnitude.
	// If so make it positive and add pi to the phase.
	if (mag < 0.0) {
		mag *= -1.0;
		phase += LauConstants::pi;
	}

	// Check now whether the phase lies in the right range (-pi to pi).
	Bool_t withinRange(kFALSE);
	while (withinRange == kFALSE) {
		if (phase > -LauConstants::pi && phase < LauConstants::pi) {
			withinRange = kTRUE;
		} else {
			// Not within the specified range
			if (phase > LauConstants::pi) {
				phase -= LauConstants::twoPi;
			} else if (phase < -LauConstants::pi) {
				phase += LauConstants::twoPi;
			}
		}
	}

	// A further problem can occur when the generated phase is close to -pi or pi.
	// The phase can wrap over to the other end of the scale -
	// this leads to artificially large pulls so we wrap it back.
	Double_t diff = phase - genPhase;
	if (diff > LauConstants::pi) {
		phase -= LauConstants::twoPi;
	} else if (diff < -LauConstants::pi) {
		phase += LauConstants::twoPi;
	}

	// finally store the new values in the parameters
	// and update the pulls
	magnitude_->value(mag);  magnitude_->updatePull();
	phase_->value(phase);  phase_->updatePull();
}

LauComplex LauMagPhaseCoeffSet::particleCoeff()
{
	LauComplex coeff(magnitude_->value()*TMath::Cos(phase_->value()), magnitude_->value()*TMath::Sin(phase_->value()));
	return coeff;
}

LauComplex LauMagPhaseCoeffSet::antiparticleCoeff()
{
	return this->particleCoeff();
}

void LauMagPhaseCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar )
{
	LauComplex average( coeff );
	average += coeffBar;
	average.rescale( 0.5 );

	magnitude_->value( average.abs() );
	phase_->value( average.arg() );
}

LauParameter LauMagPhaseCoeffSet::acp()
{
	TString parName(this->baseName()); parName += "_ACP";
	return LauParameter(parName,0.0);
}

LauAbsCoeffSet* LauMagPhaseCoeffSet::createClone(const TString& newName, Double_t constFactor)
{
	LauAbsCoeffSet* clone = new LauMagPhaseCoeffSet( *this, constFactor );
	clone->name( newName );
	return clone;
}

