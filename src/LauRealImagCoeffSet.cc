
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRealImagCoeffSet.cc
    \brief File containing implementation of LauRealImagCoeffSet class.
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
#include "LauRealImagCoeffSet.hh"
#include "LauParameter.hh"
#include "LauPrint.hh"
#include "LauRandom.hh"

ClassImp(LauRealImagCoeffSet)


LauRealImagCoeffSet::LauRealImagCoeffSet(const TString& compName, Double_t x, Double_t y, Bool_t xFixed, Bool_t yFixed) :
	LauAbsCoeffSet(compName),
	minPar_(-10.0),
	maxPar_(+10.0),
	x_(new LauParameter("X",x,minPar_,maxPar_,xFixed)),
	y_(new LauParameter("Y",y,minPar_,maxPar_,yFixed)),
	coeff_(x,y)
{
	// Print message
	cout<<"Set component \""<<this->name()<<"\" to have real part = "<<x_->value()<<" and imaginary part = "<<y_->value()<<"."<<endl;
}

LauRealImagCoeffSet::LauRealImagCoeffSet(const LauRealImagCoeffSet& rhs, Double_t constFactor) : LauAbsCoeffSet(rhs.name())
{
	minPar_ = rhs.minPar_;
	maxPar_ = rhs.maxPar_;
	y_ = rhs.x_->createClone(constFactor);
	y_ = rhs.y_->createClone(constFactor);
	coeff_ = rhs.coeff_;
}

LauRealImagCoeffSet& LauRealImagCoeffSet::operator=(const LauRealImagCoeffSet& rhs)
{
	if (&rhs != this) {
		this->name(rhs.name());
		minPar_ = rhs.minPar_;
		maxPar_ = rhs.maxPar_;
		y_ = rhs.x_->createClone();
		y_ = rhs.y_->createClone();
		coeff_ = rhs.coeff_;
	}
	return *this;
}

std::vector<LauParameter*> LauRealImagCoeffSet::getParameters()
{
	std::vector<LauParameter*> pars;
	pars.push_back(x_);
	pars.push_back(y_);
	return pars;
}

void LauRealImagCoeffSet::printTableHeading(std::ostream& stream)
{
	stream<<"\\begin{tabular}{|l|c|c|}"<<endl;
	stream<<"\\hline"<<endl;
	stream<<"Component & Real Part & Imaginary Part \\\\"<<endl;
	stream<<"\\hline"<<endl;
}

void LauRealImagCoeffSet::printTableRow(std::ostream& stream)
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
	stream<<"$ \\\\"<<endl;
}

void LauRealImagCoeffSet::randomiseInitValues()
{
	if (x_->fixed() == kFALSE) {
		// Choose a value between -10.0 and 10.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*20.0 - 10.0;
		x_->initValue(value); x_->value(value);
	}
	if (y_->fixed() == kFALSE) {
		// Choose a value between -10.0 and 10.0
		Double_t value = LauRandom::zeroSeedRandom()->Rndm()*20.0 - 10.0;
		y_->initValue(value); y_->value(value);
	}
}

void LauRealImagCoeffSet::finaliseValues()
{
	x_->updatePull();
	y_->updatePull();
}

const LauComplex& LauRealImagCoeffSet::particleCoeff()
{
	coeff_.setRealImagPart(x_->value(), y_->value());
	return coeff_;
}

const LauComplex& LauRealImagCoeffSet::antiparticleCoeff()
{
	return this->particleCoeff();
}

void LauRealImagCoeffSet::setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar )
{
	LauComplex average( coeff );
	average += coeffBar;
	average.rescale( 0.5 );

	x_->value( average.re() );
	y_->value( average.im() );
}

LauParameter LauRealImagCoeffSet::acp()
{
	TString parName(this->baseName()); parName += "_ACP";
	return LauParameter(parName,0.0);
}

LauAbsCoeffSet* LauRealImagCoeffSet::createClone(const TString& newName, Double_t constFactor)
{
	LauAbsCoeffSet* clone = new LauRealImagCoeffSet( *this, constFactor );
	clone->name( newName );
	return clone;
}

