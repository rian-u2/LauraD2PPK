
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
	x_(new LauParameter("X", x, minRealImagPart_, maxRealImagPart_, xFixed)),
	y_(new LauParameter("Y", y, minRealImagPart_, maxRealImagPart_, yFixed)),
	xbar_(new LauParameter("Xbar", xbar, minRealImagPart_, maxRealImagPart_, xbarFixed)),
	ybar_(new LauParameter("Ybar", ybar, minRealImagPart_, maxRealImagPart_, ybarFixed)),
	particleCoeff_(x,y),
	antiparticleCoeff_(xbar,ybar),
	acp_("ACP", 0.0, -1.0, 1.0, kTRUE)
{
}

LauRealImagCPCoeffSet::LauRealImagCPCoeffSet(const LauRealImagCPCoeffSet& rhs, CloneOption cloneOption, Double_t constFactor) : LauAbsCoeffSet(rhs.name()),
	x_(0),
	y_(0),
	xbar_(0),
	ybar_(0),
	particleCoeff_( rhs.particleCoeff_ ),
	antiparticleCoeff_( rhs.antiparticleCoeff_ ),
	acp_( rhs.acp_ )
{
	if ( cloneOption == All || cloneOption == TieRealPart ) {
		x_ = rhs.x_->createClone(constFactor);
		xbar_ = rhs.xbar_->createClone(constFactor);
	} else {
		x_ = new LauParameter("X", rhs.x_->value(), minRealImagPart_, maxRealImagPart_, rhs.x_->fixed());
		xbar_ = new LauParameter("Xbar", rhs.xbar_->value(), minRealImagPart_, maxRealImagPart_, rhs.xbar_->fixed());
	}

	if ( cloneOption == All || cloneOption == TieImagPart ) {
		y_ = rhs.y_->createClone(constFactor);
		ybar_ = rhs.ybar_->createClone(constFactor);
	} else {
		y_ = new LauParameter("Y", rhs.y_->value(), minRealImagPart_, maxRealImagPart_, rhs.y_->fixed());
		ybar_ = new LauParameter("Ybar", rhs.ybar_->value(), minRealImagPart_, maxRealImagPart_, rhs.ybar_->fixed());
	}
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

void LauRealImagCPCoeffSet::printParValues() const
{
	std::cout << "INFO in LauRealImagCPCoeffSet::printParValues : Component \"" << this->name() << "\" has ";
	std::cout << "x = " << x_->value() << ",\t";
	std::cout << "y = " << y_->value() << ",\t";
	std::cout << "xbar = " << xbar_->value() << ",\t";
	std::cout << "ybar = " << ybar_->value() << "." << std::endl;
}

void LauRealImagCPCoeffSet::printTableHeading(std::ostream& stream) const
{
	stream<<"\\begin{tabular}{|l|c|c|c|c|}"<<std::endl;
	stream<<"\\hline"<<std::endl;
	stream<<"Component & Particle Real Part & Particle Imaginary Part & Antiparticle Real Part & Antiparticle Imaginary Part \\\\"<<std::endl;
	stream<<"\\hline"<<std::endl;
}

void LauRealImagCPCoeffSet::printTableRow(std::ostream& stream) const
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
	stream<<"$ \\\\"<<std::endl;
}

void LauRealImagCPCoeffSet::randomiseInitValues()
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
	if (xbar_->fixed() == kFALSE) {
		// Choose a value for "Xbar" between -3.0 and 3.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*6.0 - 3.0;
		xbar_->initValue(value); xbar_->value(value);
	}
	if (ybar_->fixed() == kFALSE) {
		// Choose a value for "Ybar" between -3.0 and 3.0
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

void LauRealImagCPCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar, Bool_t init )
{
	Double_t xVal( coeff.re() );
	Double_t yVal( coeff.im() );
	Double_t xBarVal( coeffBar.re() );
	Double_t yBarVal( coeffBar.im() );

	x_->value( xVal );
	y_->value( yVal );
	xbar_->value( xBarVal );
	ybar_->value( yBarVal );

	if ( init ) {
		x_->genValue( xVal );
		y_->genValue( yVal );
		xbar_->genValue( xBarVal );
		ybar_->genValue( yBarVal );

		x_->initValue( xVal );
		y_->initValue( yVal );
		xbar_->initValue( xBarVal );
		ybar_->initValue( yBarVal );
	}
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

LauAbsCoeffSet* LauRealImagCPCoeffSet::createClone(const TString& newName, CloneOption cloneOption, Double_t constFactor)
{
	LauAbsCoeffSet* clone(0);
	if ( cloneOption == All || cloneOption == TieRealPart || cloneOption == TieImagPart ) {
		clone = new LauRealImagCPCoeffSet( *this, cloneOption, constFactor );
		clone->name( newName );
	} else {
		std::cerr << "ERROR in LauRealImagCPCoeffSet::createClone : Invalid clone option" << std::endl;
	}
	return clone;
}

