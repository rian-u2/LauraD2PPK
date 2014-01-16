
// Copyright University of Warwick 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRealImagCPCoeffSet.cc
    \brief File containing implementation of LauRealImagCPCoeffSet class.
*/

#include <iostream>
#include <fstream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"
#include "TRandom.h"

#include "LauRealImagCPCoeffSet.hh"
#include "LauComplex.hh"
#include "LauConstants.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

ClassImp(LauRealImagCPCoeffSet)


LauRealImagCPCoeffSet::LauRealImagCPCoeffSet(const TString& compName, Double_t x, Double_t y, Double_t xbar, Double_t ybar,
		Bool_t xFixed, Bool_t yFixed, Bool_t xbarFixed, Bool_t ybarFixed) :
	LauAbsCoeffSet(compName),
	minPar_(-10.0),
	maxPar_(+10.0),
	x_(new LauParameter("X", x, minPar_, maxPar_, xFixed)),
	y_(new LauParameter("Y", y, minPar_, maxPar_, yFixed)),
	xbar_(new LauParameter("Xbar", xbar, minPar_, maxPar_, xbarFixed)),
	ybar_(new LauParameter("Ybar", ybar, minPar_, maxPar_, ybarFixed)),
	particleCoeff_(x,y),
	antiparticleCoeff_(xbar,ybar),
	acp_("ACP", 0.0, -1.0, 1.0, kTRUE)
{
	// Print message
	std::cout << "Set component \"" << this->name() << "\" to have x = " << x_->value() << ",\ty = " << y_->value() << ",\t";
	std::cout << "xbar = " << xbar_->value() << ",\tybar = " << ybar_->value() << "." << std::endl;
}

LauRealImagCPCoeffSet::LauRealImagCPCoeffSet(const LauRealImagCPCoeffSet& rhs, Double_t constFactor) : LauAbsCoeffSet(rhs.name())
{
	minPar_ = rhs.minPar_;
	maxPar_ = rhs.maxPar_;
	x_ = rhs.x_->createClone(constFactor);
	y_ = rhs.y_->createClone(constFactor);
	xbar_ = rhs.xbar_->createClone(constFactor);
	ybar_ = rhs.ybar_->createClone(constFactor);
	particleCoeff_ = rhs.particleCoeff_;
	antiparticleCoeff_ = rhs.antiparticleCoeff_;
	acp_ = rhs.acp_;
}

LauRealImagCPCoeffSet& LauRealImagCPCoeffSet::operator=(const LauRealImagCPCoeffSet& rhs)
{
	if (&rhs != this) {
		this->name(rhs.name());
		minPar_ = rhs.minPar_;
		maxPar_ = rhs.maxPar_;
		x_ = rhs.x_->createClone();
		y_ = rhs.y_->createClone();
		xbar_ = rhs.xbar_->createClone();
		ybar_ = rhs.ybar_->createClone();
		particleCoeff_ = rhs.particleCoeff_;
		antiparticleCoeff_ = rhs.antiparticleCoeff_;
		acp_ = rhs.acp_;
	}
	return *this;
}

std::vector<LauParameter*> LauRealImagCPCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(x_);
	pars.push_back(y_);
	pars.push_back(xbar_);
	pars.push_back(ybar_);
	return pars;
}

void LauRealImagCPCoeffSet::printTableHeading(std::ostream& stream)
{
	stream<<"\\begin{tabular}{|l|c|c|c|c|}"<<endl;
	stream<<"\\hline"<<endl;
	stream<<"Component & Particle Real Part & Particle Imaginary Part & Antiparticle Real Part & Antiparticle Imaginary Part \\\\"<<endl;
	stream<<"\\hline"<<endl;
}

void LauRealImagCPCoeffSet::printTableRow(std::ostream& stream)
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
	print.printFormat(stream, xbar_->value());
	stream<<" \\pm ";
	print.printFormat(stream, xbar_->error());
	stream<<"$  &  $";
	print.printFormat(stream, ybar_->value());
	stream<<" \\pm ";
	print.printFormat(stream, ybar_->error());
	stream<<"$ \\\\"<<endl;
}

void LauRealImagCPCoeffSet::randomiseInitValues()
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
	if (xbar_->fixed() == kFALSE && xbar_->secondStage() == kFALSE) {
		// Choose a value for "Delta X" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		xbar_->initValue(value); xbar_->value(value);
	}
	if (ybar_->fixed() == kFALSE && ybar_->secondStage() == kFALSE) {
		// Choose a value for "Delta Y" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		ybar_->initValue(value); ybar_->value(value);
	}
}

void LauRealImagCPCoeffSet::finaliseValues()
{
	// update the pulls
	x_->updatePull();
	y_->updatePull();
	xbar_->updatePull();
	ybar_->updatePull();
}

const LauComplex& LauRealImagCPCoeffSet::particleCoeff()
{
	particleCoeff_.setRealImagPart( x_->value(), y_->value() );
	return particleCoeff_;
}

const LauComplex& LauRealImagCPCoeffSet::antiparticleCoeff()
{
	antiparticleCoeff_.setRealImagPart( xbar_->value(), ybar_->value() );
	return antiparticleCoeff_;
}

void LauRealImagCPCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar )
{
	x_->value( coeff.re() );
	y_->value( coeff.im() );
	xbar_->value( coeffBar.re() );
	ybar_->value( coeffBar.im() );
}

LauParameter LauRealImagCPCoeffSet::acp()
{
	// set the name
	TString parName(this->baseName()); parName += "_ACP";
	acp_.name(parName);

	// work out the ACP value
	Double_t csq = x_->value()*x_->value() + y_->value()*y_->value();
	Double_t cbarsq = xbar_->value()*xbar_->value() + ybar_->value()*ybar_->value();
	Double_t numer = cbarsq - csq;
	Double_t denom = cbarsq + csq;
	Double_t value = numer/denom;

	// is it fixed?
	Bool_t fixed = x_->fixed() && y_->fixed() && xbar_->fixed() && ybar_->fixed();
	acp_.fixed(fixed);

	// we can't work out the error without the covariance matrix
	Double_t error(0.0);

	// set the value and error
	acp_.valueAndErrors(value,error);

	return acp_;
}

LauAbsCoeffSet* LauRealImagCPCoeffSet::createClone(const TString& newName, Double_t constFactor)
{
	LauAbsCoeffSet* clone = new LauRealImagCPCoeffSet( *this, constFactor );
	clone->name( newName );
	return clone;
}

