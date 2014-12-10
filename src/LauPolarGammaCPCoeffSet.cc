
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPolarGammaCPCoeffSet.cc
    \brief File containing implementation of LauPolarGammaCPCoeffSet class.
*/

#include <iostream>
#include <fstream>
#include <vector>

#include "TMath.h"
#include "TRandom.h"

#include "LauPolarGammaCPCoeffSet.hh"
#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

LauParameter* LauPolarGammaCPCoeffSet::gammaGlobal_ = 0;

ClassImp(LauPolarGammaCPCoeffSet)


LauPolarGammaCPCoeffSet::LauPolarGammaCPCoeffSet(const TString& compName, const Double_t x, const Double_t y, const Double_t r, const Double_t delta, const Double_t gamma,
		const Bool_t xFixed, const Bool_t yFixed, const Bool_t rFixed, const Bool_t deltaFixed, const Bool_t gammaFixed, 
		const Bool_t rSecondStage, const Bool_t deltaSecondStage, const Bool_t gammaSecondStage, const Bool_t useGlobalGamma) :
	LauAbsCoeffSet(compName),
	x_(new LauParameter("X", x, minRealImagPart_, maxRealImagPart_, xFixed)),
	y_(new LauParameter("Y", y, minRealImagPart_, maxRealImagPart_, yFixed)),
	r_(new LauParameter("r", r, minMagnitude_, maxMagnitude_, rFixed)),
	delta_(new LauParameter("delta", delta, minPhase_, maxPhase_, deltaFixed)),
	gamma_(useGlobalGamma?0:(new LauParameter("gamma", gamma, minPhase_, maxPhase_, gammaFixed))),
	useGlobalGamma_(useGlobalGamma),
	nonCPPart_( x, y),
	cpPart_( 1+ r*TMath::Cos(delta+gamma), TMath::Sin(delta+gamma)),
	cpAntiPart_( 1+ r*TMath::Cos(delta-gamma), TMath::Sin(delta-gamma)),
	particleCoeff_( nonCPPart_ * cpPart_ ),
	antiparticleCoeff_( nonCPPart_ * cpAntiPart_ ),
	acp_("ACP", (antiparticleCoeff_.abs2()-particleCoeff_.abs2())/(antiparticleCoeff_.abs2()+particleCoeff_.abs2()), -1.0, 1.0, rFixed&&deltaFixed&&gammaFixed)
{
	if (rSecondStage && !rFixed) {
		r_->secondStage(kTRUE);
		r_->initValue(0.0);
	}
	if (deltaSecondStage && !deltaFixed) {
		delta_->secondStage(kTRUE);
		delta_->initValue(0.0);
	}
	if (!useGlobalGamma_ && gammaSecondStage && !gammaFixed) {
		gamma_->secondStage(kTRUE);
		gamma_->initValue(0.0);
	}

	//if we're using a global gamma, create it if it doesn't already exist then set gamma_ to point to it
	if(useGlobalGamma_) {
		if(!gammaGlobal_) {
			gammaGlobal_ = new LauParameter("gamma", gamma, minPhase_, maxPhase_, gammaFixed);
			gamma_ = gammaGlobal_;
			if(gammaSecondStage && !gammaFixed) {
				gamma_->secondStage(kTRUE);
				gamma_->initValue(0.0);
			}
		} else {
			gamma_ = gammaGlobal_->createClone();
		}
	}
}

LauPolarGammaCPCoeffSet::LauPolarGammaCPCoeffSet(const LauPolarGammaCPCoeffSet& rhs, CloneOption cloneOption, Double_t constFactor) : LauAbsCoeffSet(rhs.name()),
	x_(0),
	y_(0),
	r_(0),
	delta_(0),
	gamma_(0),
	useGlobalGamma_( rhs.useGlobalGamma_ ),
	nonCPPart_( rhs.nonCPPart_ ),
	cpPart_( rhs.cpPart_ ),
	cpAntiPart_( rhs.cpAntiPart_ ),
	particleCoeff_( rhs.particleCoeff_ ),
	antiparticleCoeff_( rhs.antiparticleCoeff_ ),
	acp_( rhs.acp_ )
{
	if ( cloneOption == All || cloneOption == TieRealPart ) {
		x_ = rhs.x_->createClone(constFactor);
	} else {
		x_ = new LauParameter("X", rhs.x_->value(), minRealImagPart_, maxRealImagPart_, rhs.x_->fixed());
	}

	if ( cloneOption == All || cloneOption == TieImagPart ) {
		y_ = rhs.y_->createClone(constFactor);
	} else {
		y_ = new LauParameter("Y", rhs.y_->value(), minRealImagPart_, maxRealImagPart_, rhs.y_->fixed());
	}

	if ( cloneOption == All || cloneOption == TieCPPars ) {
		r_ = rhs.r_->createClone(constFactor);
		delta_ = rhs.delta_->createClone(constFactor);
		gamma_ = rhs.gamma_->createClone(constFactor);
	} else {
		r_ = new LauParameter("r", rhs.r_->value(), minMagnitude_, maxMagnitude_, rhs.r_->fixed());
		delta_ = new LauParameter("delta", rhs.delta_->value(), minPhase_, maxPhase_, rhs.delta_->fixed());
		if(useGlobalGamma_) gamma_ = gammaGlobal_->createClone();
		else gamma_ = new LauParameter("gamma", rhs.gamma_->value(), minPhase_, maxPhase_, rhs.gamma_->fixed());
		if ( rhs.r_->secondStage() && !rhs.r_->fixed() ) {
			r_->secondStage(kTRUE);
			r_->initValue(0.0);
		}
		if ( rhs.delta_->secondStage() && !rhs.delta_->fixed() ) {
			delta_->secondStage(kTRUE);
			delta_->initValue(0.0);
		}
		if ( !useGlobalGamma_ && rhs.gamma_->secondStage() && !rhs.gamma_->fixed() ) {
			gamma_->secondStage(kTRUE);
			gamma_->initValue(0.0);
		}
	}
}

void LauPolarGammaCPCoeffSet::adjustName(LauParameter* par)
{
	if(!useGlobalGamma_ || par!=gamma_) LauAbsCoeffSet::adjustName(par);
}

std::vector<LauParameter*> LauPolarGammaCPCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(x_);
	pars.push_back(y_);
	if(!r_->fixed()) pars.push_back(r_);
	if(!delta_->fixed()) pars.push_back(delta_);
	if(!gamma_->fixed()) pars.push_back(gamma_);
	return pars;
}

void LauPolarGammaCPCoeffSet::printParValues() const
{
	std::cout<<"INFO in LauPolarGammaCPCoeffSet::printParValues : Component \""<<this->name()<<"\" has ";
	std::cout<<"x = "<<x_->value()<<",\t";
	std::cout<<"y = "<<y_->value()<<",\t";
	std::cout<<"r = "<<r_->value()<<",\t";
	std::cout<<"delta = "<<delta_->value()<<",\t";
	std::cout<<"gamma = "<<gamma_->value()<<"."<<std::endl;
}

void LauPolarGammaCPCoeffSet::printTableHeading(std::ostream& stream) const
{
	stream<<"\\begin{tabular}{|l|c|c|c|c|c|}"<<std::endl;
	stream<<"\\hline"<<std::endl;
	stream<<"Component & Real Part & Imaginary Part & r & $\\delta$ & $\\gamma$ \\\\"<<std::endl;
	stream<<"\\hline"<<std::endl;
}

void LauPolarGammaCPCoeffSet::printTableRow(std::ostream& stream) const
{
	LauPrint print;
	TString resName = this->name();
	resName = resName.ReplaceAll("_", "\\_");
	stream<<resName<<"  &  $";
	print.printFormat(stream, x_->value());
	stream<<" \\pm ";
	print.printFormat(stream, x_->error());
	stream<<"$  &  $";
	print.printFormat(stream, y_->value());
	stream<<" \\pm ";
	print.printFormat(stream, y_->error());
	stream<<"$  &  $";
	print.printFormat(stream, r_->value());
	stream<<" \\pm ";
	print.printFormat(stream, r_->error());
	stream<<"$  &  $";
	print.printFormat(stream, delta_->value());
	stream<<" \\pm ";
	print.printFormat(stream, delta_->error());
	stream<<"$  &  $";
	print.printFormat(stream, gamma_->value());
	stream<<" \\pm ";
	print.printFormat(stream, gamma_->error());
	stream<<"$ \\\\"<<std::endl;
}

void LauPolarGammaCPCoeffSet::randomiseInitValues()
{
	if (x_->fixed() == kFALSE) {
		// Choose a value for "X" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		x_->initValue(value); x_->value(value);
	}
	if (y_->fixed() == kFALSE) {
		// Choose a value for "Y" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		y_->initValue(value);  y_->value(value);
	}
	if (r_->fixed() == kFALSE && r_->secondStage() == kFALSE) {
		// Choose a value for "r" between 0.0 and 2.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*2.0;
		r_->initValue(value); r_->value(value);
	}
	if (delta_->fixed() == kFALSE && delta_->secondStage() == kFALSE) {
		// Choose a value for "delta" between +- pi
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*LauConstants::twoPi - LauConstants::pi;
		delta_->initValue(value); delta_->value(value);
	}
	if (gamma_->fixed() == kFALSE && gamma_->secondStage() == kFALSE) {
		// Choose a value for "gamma" between +-pi
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*LauConstants::twoPi - LauConstants::pi;
		gamma_->initValue(value); gamma_->value(value);
	}
}

void LauPolarGammaCPCoeffSet::finaliseValues()
{
	// retrieve the current values from the parameters
	Double_t rVal     = r_->value();
	Double_t deltaVal = delta_->value();
	Double_t gammaVal = gamma_->value();
	Double_t genDelta = delta_->genValue();
	
	// Check whether we have a negative magnitude.
	// If so make it positive and add pi to the phases.
	if (rVal < 0.0) {
		rVal *= -1.0;
		deltaVal += LauConstants::pi;
	}

	// Check now whether the phases lie in the right range (-pi to pi).
	Bool_t deltaWithinRange(kFALSE);
	Bool_t gammaWithinRange(kFALSE);
	while (deltaWithinRange == kFALSE && gammaWithinRange == kFALSE) {
		if (deltaVal > -LauConstants::pi && deltaVal <= LauConstants::pi) {
			deltaWithinRange = kTRUE;
		} else {
			// Not within the specified range
			if (deltaVal > LauConstants::pi) {
				deltaVal -= LauConstants::twoPi;
			} else if (deltaVal <= -LauConstants::pi) {
				deltaVal += LauConstants::twoPi;
			}
		}

		if (gammaVal > -LauConstants::pi && gammaVal <= LauConstants::pi) {
			gammaWithinRange = kTRUE;
		} else {
			// Not within the specified range
			if (gammaVal > LauConstants::pi) {
				gammaVal -= LauConstants::twoPi;
			} else if (gammaVal <= -LauConstants::pi) {
				gammaVal += LauConstants::twoPi;
			}
		}
	}

	// To resolve the two-fold ambiguity in gamma and delta we require gamma to be in the range 0-pi
	if(gammaVal < 0) {
		if(deltaVal <= 0) {
			gammaVal += LauConstants::pi;
			deltaVal += LauConstants::pi;
		} else {
			gammaVal += LauConstants::pi;
			deltaVal -= LauConstants::pi;
		}
	}

	// A further problem can occur when the generated phase is close to -pi or pi.
	// The phase can wrap over to the other end of the scale -
	// this leads to artificially large pulls so we wrap it back.
	Double_t diff = deltaVal - genDelta;
	if (diff > LauConstants::pi) {
		deltaVal -= LauConstants::twoPi;
	} else if (diff < -LauConstants::pi) {
		deltaVal += LauConstants::twoPi;
	}

	// finally store the new values in the parameters
	// and update the pulls
	r_->value(rVal);             r_->updatePull();
	delta_->value(deltaVal);     delta_->updatePull();
	gamma_->value(gammaVal);      gamma_->updatePull();
}

const LauComplex& LauPolarGammaCPCoeffSet::particleCoeff()
{
	nonCPPart_.setRealImagPart( x_->value(), y_->value() );
	cpPart_.setRealImagPart( 1 + r_->value()*TMath::Cos(delta_->value()+gamma_->value()), r_->value()*TMath::Sin(delta_->value()+gamma_->value()) );
	particleCoeff_ = nonCPPart_ * cpPart_;
	return particleCoeff_;
}

const LauComplex& LauPolarGammaCPCoeffSet::antiparticleCoeff()
{
	nonCPPart_.setRealImagPart( x_->value(), y_->value() );
	cpAntiPart_.setRealImagPart( 1 + r_->value()*TMath::Cos(delta_->value()-gamma_->value()), r_->value()*TMath::Sin(delta_->value()-gamma_->value()) );
	antiparticleCoeff_ = nonCPPart_ * cpAntiPart_;
	return antiparticleCoeff_;
}

void LauPolarGammaCPCoeffSet::setCoeffValues( const LauComplex&, const LauComplex&, Bool_t )
{
	std::cerr << "ERROR in LauPolarGammaCPCoeffSet::setCoeffValues : Method not supported by this class - too many parameters" << std::endl;
}

LauParameter LauPolarGammaCPCoeffSet::acp()
{
	// set the name
	TString parName(this->baseName()); parName += "_ACP";
	acp_.name(parName);

	// work out the ACP value
	// particle and antiparticle coeffs will have already been calculated by calls to particleCoeff() and antiparticleCoeff()
	Double_t numer = antiparticleCoeff_.abs2()-particleCoeff_.abs2();
	Double_t denom = antiparticleCoeff_.abs2()+particleCoeff_.abs2();
	Double_t value = numer/denom;

	// is it fixed?
	Bool_t fixed = r_->fixed() && delta_->fixed() && gamma_->fixed();
	acp_.fixed(fixed);

	// we can't work out the error without the covariance matrix
	Double_t error(0.0);

	// set the value and error
	acp_.valueAndErrors(value,error);

	return acp_;
}

LauAbsCoeffSet* LauPolarGammaCPCoeffSet::createClone(const TString& newName, CloneOption cloneOption, Double_t constFactor)
{
	LauAbsCoeffSet* clone(0);
	if ( cloneOption == All || cloneOption == TieRealPart || cloneOption == TieImagPart || cloneOption == TieCPPars ) {
		clone = new LauPolarGammaCPCoeffSet( *this, cloneOption, constFactor );
		clone->name( newName );
	} else {
		std::cerr << "ERROR in LauPolarGammaCPCoeffSet::createClone : Invalid clone option" << std::endl;
	}
	return clone;
}

