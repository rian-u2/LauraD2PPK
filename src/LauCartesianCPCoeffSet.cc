
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauCartesianCPCoeffSet.cc
    \brief File containing implementation of LauCartesianCPCoeffSet class.
*/

#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"
#include "TRandom.h"

#include "LauCartesianCPCoeffSet.hh"
#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

ClassImp(LauCartesianCPCoeffSet)


LauCartesianCPCoeffSet::LauCartesianCPCoeffSet(const TString& compName, Double_t x, Double_t y, Double_t deltaX, Double_t deltaY,
		Bool_t xFixed, Bool_t yFixed, Bool_t deltaXFixed, Bool_t deltaYFixed, Bool_t deltaXSecondStage, Bool_t deltaYSecondStage) :
	LauAbsCoeffSet(compName),
	minPar_(-10.0),
	maxPar_(+10.0),
	minDeltaPar_(-2.0),
	maxDeltaPar_(+2.0),
	x_(new LauParameter("X", x, minPar_, maxPar_, xFixed)),
	y_(new LauParameter("Y", y, minPar_, maxPar_, yFixed)),
	deltaX_(new LauParameter("DeltaX", deltaX, minDeltaPar_, maxDeltaPar_, deltaXFixed)),
	deltaY_(new LauParameter("DeltaY", deltaY, minDeltaPar_, maxDeltaPar_, deltaYFixed)),
	particleCoeff_( x+deltaX, y+deltaY ),
	antiparticleCoeff_( x-deltaX, y-deltaY ),
	acp_("ACP", -2.0*(x*deltaX + y*deltaY)/(x*x + deltaX*deltaX + y*y + deltaY*deltaY), -1.0, 1.0, deltaXFixed&&deltaYFixed)
{
	// Print message
	cout<<"Set component \""<<this->name()<<"\" to have x = "<<x_->value()<<",\ty = "<<y_->value()<<",\t";
	cout<<"Delta x = "<<deltaX_->value()<<",\tDelta y = "<<deltaY_->value()<<"."<<endl;

	if (deltaXSecondStage && !deltaXFixed) {
		deltaX_->secondStage(kTRUE);
		deltaX_->initValue(0.0);
	}
	if (deltaYSecondStage && !deltaYFixed) {
		deltaY_->secondStage(kTRUE);
		deltaY_->initValue(0.0);
	}
}

LauCartesianCPCoeffSet::LauCartesianCPCoeffSet(const LauCartesianCPCoeffSet& rhs, Double_t constFactor) : LauAbsCoeffSet(rhs.name())
{
	minPar_ = rhs.minPar_;
	maxPar_ = rhs.maxPar_;
	minDeltaPar_ = rhs.minDeltaPar_;
	maxDeltaPar_ = rhs.maxDeltaPar_;
	x_ = rhs.x_->createClone(constFactor);
	y_ = rhs.y_->createClone(constFactor);
	deltaX_ = rhs.deltaX_->createClone(constFactor);
	deltaY_ = rhs.deltaY_->createClone(constFactor);
	particleCoeff_ = rhs.particleCoeff_;
	antiparticleCoeff_ = rhs.antiparticleCoeff_;
	acp_ = rhs.acp_;
}

LauCartesianCPCoeffSet& LauCartesianCPCoeffSet::operator=(const LauCartesianCPCoeffSet& rhs)
{
	if (&rhs != this) {
		this->name(rhs.name());
		minPar_ = rhs.minPar_;
		maxPar_ = rhs.maxPar_;
		minDeltaPar_ = rhs.minDeltaPar_;
		maxDeltaPar_ = rhs.maxDeltaPar_;
		x_ = rhs.x_->createClone();
		y_ = rhs.y_->createClone();
		deltaX_ = rhs.deltaX_->createClone();
		deltaY_ = rhs.deltaY_->createClone();
		particleCoeff_ = rhs.particleCoeff_;
		antiparticleCoeff_ = rhs.antiparticleCoeff_;
		acp_ = rhs.acp_;
	}
	return *this;
}

std::vector<LauParameter*> LauCartesianCPCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(x_);
	pars.push_back(y_);
	pars.push_back(deltaX_);
	pars.push_back(deltaY_);
	return pars;
}

void LauCartesianCPCoeffSet::printTableHeading(std::ostream& stream)
{
	stream<<"\\begin{tabular}{|l|c|c|c|c|}"<<endl;
	stream<<"\\hline"<<endl;
	stream<<"Component & Real Part & Imaginary Part & $\\Delta$ Real Part & $\\Delta$ Imaginary Part \\\\"<<endl;
	stream<<"\\hline"<<endl;
}

void LauCartesianCPCoeffSet::printTableRow(std::ostream& stream)
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
	print.printFormat(stream, deltaX_->value());
	stream<<" \\pm ";
	print.printFormat(stream, deltaX_->error());
	stream<<"$  &  $";
	print.printFormat(stream, deltaY_->value());
	stream<<" \\pm ";
	print.printFormat(stream, deltaY_->error());
	stream<<"$ \\\\"<<endl;
}

void LauCartesianCPCoeffSet::randomiseInitValues()
{
	if (x_->fixed() == kFALSE && x_->secondStage() == kFALSE) {
		// Choose a value for "X" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		x_->initValue(value); x_->value(value);
	}
	if (y_->fixed() == kFALSE && y_->secondStage() == kFALSE) {
		// Choose a value for "Y" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		y_->initValue(value);  y_->value(value);
	}
	if (deltaX_->fixed() == kFALSE && deltaX_->secondStage() == kFALSE) {
		// Choose a value for "Delta X" between -0.5 and 0.5
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*1.0 - 0.5;
		deltaX_->initValue(value); deltaX_->value(value);
	}
	if (deltaY_->fixed() == kFALSE && deltaY_->secondStage() == kFALSE) {
		// Choose a value for "Delta Y" between -0.5 and 0.5
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*1.0 - 0.5;
		deltaY_->initValue(value); deltaY_->value(value);
	}
}

void LauCartesianCPCoeffSet::finaliseValues()
{
	// update the pulls
	x_->updatePull();
	y_->updatePull();
	deltaX_->updatePull();
	deltaY_->updatePull();
}

const LauComplex& LauCartesianCPCoeffSet::particleCoeff()
{
	particleCoeff_.setRealImagPart( x_->value()+deltaX_->value(), y_->value()+deltaY_->value() );
	return particleCoeff_;
}

const LauComplex& LauCartesianCPCoeffSet::antiparticleCoeff()
{
	antiparticleCoeff_.setRealImagPart( x_->value()-deltaX_->value(), y_->value()-deltaY_->value() );
	return antiparticleCoeff_;
}

void LauCartesianCPCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar )
{
	LauComplex average( coeff );
	average += coeffBar;
	average.rescale( 0.5 );

	x_->value( average.re() );
	y_->value( average.im() );
	deltaX_->value( coeff.re() - average.re() );
	deltaY_->value( coeff.im() - average.im() );
}

LauParameter LauCartesianCPCoeffSet::acp()
{
	// set the name
	TString parName(this->baseName()); parName += "_ACP";
	acp_.name(parName);

	// work out the ACP value
	Double_t numer = x_->value()*deltaX_->value() + y_->value()*deltaY_->value();
	Double_t denom = x_->value()*x_->value() + deltaX_->value()*deltaX_->value() + y_->value()*y_->value() + deltaY_->value()*deltaY_->value();
	Double_t value = -2.0*numer/denom;

	// is it fixed?
	Bool_t fixed = deltaX_->fixed() && deltaY_->fixed();
	acp_.fixed(fixed);

	// we can't work out the error without the covariance matrix
	Double_t error(0.0);

	// set the value and error
	acp_.valueAndErrors(value,error);

	return acp_;
}

LauAbsCoeffSet* LauCartesianCPCoeffSet::createClone(const TString& newName, Double_t constFactor)
{
	LauAbsCoeffSet* clone = new LauCartesianCPCoeffSet( *this, constFactor );
	clone->name( newName );
	return clone;
}

