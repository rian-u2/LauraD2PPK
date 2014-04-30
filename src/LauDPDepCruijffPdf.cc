
// Copyright University of Warwick 2009 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDPDepCruijffPdf.cc
    \brief File containing implementation of LauDPDepCruijffPdf class.
*/

#include <iostream>
#include <vector>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"
#include "TSystem.h"

#include "LauConstants.hh"
#include "LauDaughters.hh"
#include "LauDPDepCruijffPdf.hh"
#include "LauKinematics.hh"

ClassImp(LauDPDepCruijffPdf)


LauDPDepCruijffPdf::LauDPDepCruijffPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params,
		Double_t minAbscissa, Double_t maxAbscissa,
		const LauDaughters* daughters,
		const std::vector<Double_t>& meanCoeffs,
		const std::vector<Double_t>& sigmaLCoeffs,
		const std::vector<Double_t>& sigmaRCoeffs,
		const std::vector<Double_t>& alphaLCoeffs,
		const std::vector<Double_t>& alphaRCoeffs,
		DPAxis dpAxis) :
	LauAbsPdf(theVarName, params, minAbscissa, maxAbscissa),
	kinematics_(daughters ? daughters->getKinematics() : 0),
	mean_(0),
	sigmaL_(0),
	sigmaR_(0),
	alphaL_(0),
	alphaR_(0),
	meanVal_(0.0),
	sigmaLVal_(0.0),
	sigmaRVal_(0.0),
	alphaLVal_(0.0),
	alphaRVal_(0.0),
	meanCoeffs_(meanCoeffs),
	sigmaLCoeffs_(sigmaLCoeffs),
	sigmaRCoeffs_(sigmaRCoeffs),
	alphaLCoeffs_(alphaLCoeffs),
	alphaRCoeffs_(alphaRCoeffs),
	dpAxis_(dpAxis)
{
	// Constructor for the Dalitz-plot dependent Cruijff PDF.

	// Check we have a valid kinematics object
	if ( ! kinematics_ ) {
		cerr<<"ERROR in LauDPDepCruijffPdf::LauDPDepCruijffPdf : Have not been provided with a valid DP kinematics object."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// The parameters in params are the mean, sigmaR, sigmaL, alphaR and alphaL.
	// The last two arguments specify the range in which the PDF is defined, and the PDF
	// will be normalised w.r.t. these limits.

	mean_ = this->findParameter("mean");
	sigmaR_ = this->findParameter("sigmaR");
	sigmaL_ = this->findParameter("sigmaL");
	alphaR_ = this->findParameter("alphaR");
	alphaL_ = this->findParameter("alphaL");

	if ((this->nParameters() != 5) || (mean_ == 0) || (sigmaR_ == 0) || (sigmaL_ == 0) || (alphaL_ == 0) || (alphaR_ == 0)) {
		cerr<<"ERROR in LauDPDepCruijffPdf constructor: LauDPDepCruijffPdf requires 5 parameters: \"mean\", \"sigmaL\", \"sigmaR\", \"alphaR\" and \"alphaL\"."<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Cache the normalisation factor
	this->calcNorm();
}

LauDPDepCruijffPdf::~LauDPDepCruijffPdf() 
{
	// Destructor
}

LauDPDepCruijffPdf::LauDPDepCruijffPdf(const LauDPDepCruijffPdf& other) : LauAbsPdf(other.varName(), other.getParameters(), other.getMinAbscissa(), other.getMaxAbscissa()),
	kinematics_( other.kinematics_ ),
	mean_(0),
	sigmaL_(0),
	sigmaR_(0),
	alphaL_(0),
	alphaR_(0),
	meanVal_(0.0),
	sigmaLVal_(0.0),
	sigmaRVal_(0.0),
	alphaLVal_(0.0),
	alphaRVal_(0.0),
	meanCoeffs_( other.meanCoeffs_ ),
	sigmaLCoeffs_( other.sigmaLCoeffs_ ),
	sigmaRCoeffs_( other.sigmaRCoeffs_ ),
	alphaLCoeffs_( other.alphaLCoeffs_ ),
	alphaRCoeffs_( other.alphaRCoeffs_ ),
	dpAxis_( other.dpAxis_ )
{
	// Copy constructor
	mean_ = this->findParameter("mean");
	sigmaR_ = this->findParameter("sigmaR");
	sigmaL_ = this->findParameter("sigmaL");
	alphaR_ = this->findParameter("alphaR");
	alphaL_ = this->findParameter("alphaL");
	this->setRandomFun(other.getRandomFun());
	this->calcNorm();
}

void LauDPDepCruijffPdf::calcNorm() 
{
	this->setNorm(1.0);
}

void LauDPDepCruijffPdf::calcLikelihoodInfo(const LauAbscissas& abscissas)
{
	// Check that the given abscissa is within the allowed range
	if (!this->checkRange(abscissas)) {
		gSystem->Exit(EXIT_FAILURE);
	}

	// Get our abscissa
	Double_t abscissa = abscissas[0];

	// Get the up to date parameter values
	meanVal_ = mean_->value();
	sigmaLVal_ = sigmaL_->value();
	sigmaRVal_ = sigmaR_->value();
	alphaLVal_ = alphaL_->value();
	alphaRVal_ = alphaR_->value();

	// Find out the DP position
	Double_t dpPos(0.0);
	UInt_t nVars = this->nInputVars();
	if ( abscissas.size() == nVars+2 ) {
		Double_t m13Sq = abscissas[nVars];
		Double_t m23Sq = abscissas[nVars+1];

		if ( dpAxis_ == M12 ) {
			dpPos = kinematics_->calcThirdMassSq(m13Sq,m23Sq);
		} else if ( dpAxis_ == M13 ) {
			dpPos = m13Sq;
		} else if ( dpAxis_ == M23 ) {
			dpPos = m23Sq;
		} else if ( dpAxis_ == MMIN ) {
			dpPos = TMath::Min( m13Sq, m23Sq );
		} else if ( dpAxis_ == MMAX ) {
			dpPos = TMath::Max( m13Sq, m23Sq );
		} else {
			dpPos = kinematics_->distanceFromDPCentre(m13Sq,m23Sq);
		}
	}

	// Scale the parameters according to the DP position
	this->scalePars( dpPos );

	// Calculate the PDF value
	Double_t value = this->currentPDFValue( abscissa );

	// Calculate the normalisation
	IntMethod sumMethod = this->integMethod();
	Double_t normFac = (sumMethod == GaussLegendre) ? this->integrGaussLegendre() : this->integTrapezoid();

	value /= normFac;

	this->setUnNormPDFVal(value);
}

Double_t LauDPDepCruijffPdf::currentPDFValue(Double_t abscissa) const
{
	Double_t arg = abscissa - meanVal_;
	Double_t coef(0.0);
	if (arg < 0.0){
		if (TMath::Abs(sigmaLVal_) > 1e-30) {
			coef = -1.0/(2.0*sigmaLVal_*sigmaLVal_ + alphaLVal_*arg*arg);
		}
	} else {
		if (TMath::Abs(sigmaRVal_) > 1e-30) {
			coef = -1.0/(2.0*sigmaRVal_*sigmaRVal_ + alphaRVal_*arg*arg);
		}
	}
	return TMath::Exp(coef*arg*arg);
}

Double_t LauDPDepCruijffPdf::integrGaussLegendre()
{
	if (!this->normWeightsDone()) {
		this->getNormWeights();
	}

	const std::vector<LauAbscissas>& norm_abscissas = this->normAbscissas();
	const std::vector<Double_t>& norm_weights = this->normWeights();

	// Now compute the integral
	Double_t norm(0.0);
	for (UInt_t i = 0; i < norm_weights.size(); i++) {
		Double_t fun = this->currentPDFValue( norm_abscissas[i][0] );
		Double_t intFactor = 0.5 * this->getRange();
		norm += norm_weights[i]*intFactor*fun;
	} 
	
	return norm;
}

Double_t LauDPDepCruijffPdf::integTrapezoid()
{
	static Double_t norm(0.0);
	Double_t range = this->getRange();

	if (this->nNormPoints()==1){

		Double_t abscissa = this->getMinAbscissa();
		Double_t funAbsMin = this->currentPDFValue(abscissa);

		abscissa = this->getMaxAbscissa();
		Double_t funAbsMax = this->currentPDFValue(abscissa);

		norm = 0.5*range*(funAbsMin+funAbsMax);
		return norm;

	} else {

		Double_t abscVal(0.0), tnm(0.0), sum(0.0), del(0.0);
		Int_t it(0), j(0);

		for (it=1, j=1; j< this->nNormPoints()-1; j++) {it<<=1;}
		tnm=it;
		del=range/tnm;
		abscVal= this->getMinAbscissa()+ 0.5*del;

		for (sum = 0.0, j=1; j<it; j++, abscVal+=del) {

			Double_t funVal = this->currentPDFValue(abscVal);
			sum+=funVal;
		}

		norm = 0.5*(norm + sum*range/tnm);
		return norm;
	}
}

void LauDPDepCruijffPdf::scalePars(Double_t dpPos)
{
	Int_t power = 1;
	for (std::vector<Double_t>::const_iterator iter = meanCoeffs_.begin(); iter != meanCoeffs_.end(); ++iter) {
		Double_t coeff = (*iter);
		meanVal_ += coeff * TMath::Power(dpPos,power);
		++power;
	}

	power = 1;
	for (std::vector<Double_t>::const_iterator iter = sigmaLCoeffs_.begin(); iter != sigmaLCoeffs_.end(); ++iter) {
		Double_t coeff = (*iter);
		sigmaLVal_ += coeff * TMath::Power(dpPos,power);
		++power;
	}

	power = 1;
	for (std::vector<Double_t>::const_iterator iter = sigmaRCoeffs_.begin(); iter != sigmaRCoeffs_.end(); ++iter) {
		Double_t coeff = (*iter);
		sigmaRVal_ += coeff * TMath::Power(dpPos,power);
		++power;
	}

	power = 1;
	for (std::vector<Double_t>::const_iterator iter = alphaLCoeffs_.begin(); iter != alphaLCoeffs_.end(); ++iter) {
		Double_t coeff = (*iter);
		alphaLVal_ += coeff * TMath::Power(dpPos,power);
		++power;
	}

	power = 1;
	for (std::vector<Double_t>::const_iterator iter = alphaRCoeffs_.begin(); iter != alphaRCoeffs_.end(); ++iter) {
		Double_t coeff = (*iter);
		alphaRVal_ += coeff * TMath::Power(dpPos,power);
		++power;
	}
}

void LauDPDepCruijffPdf::calcPDFHeight( const LauKinematics* kinematics )
{
	// Get the up to date parameter values
	meanVal_ = mean_->value();
	sigmaLVal_ = sigmaL_->value();
	sigmaRVal_ = sigmaR_->value();
	alphaLVal_ = alphaL_->value();
	alphaRVal_ = alphaR_->value();

	// Find out the DP position
	Double_t dpPos(0.0);
	if ( dpAxis_ == M12 ) {
		dpPos = kinematics->getm12Sq();
	} else if ( dpAxis_ == M13 ) {
		dpPos = kinematics->getm13Sq();
	} else if ( dpAxis_ == M23 ) {
		dpPos = kinematics->getm23Sq();
	} else {
		dpPos = kinematics->distanceFromDPCentre();
	}

	// Scale the parameters according to the DP position
	this->scalePars( dpPos );

	// Calculate the PDF height
	
	LauAbscissas maxPoint(3);
	maxPoint[0] = meanVal_;
	maxPoint[1] = kinematics->getm13Sq();
	maxPoint[2] = kinematics->getm23Sq();

	if (meanVal_ < this->getMinAbscissa()) {
		maxPoint[0] = this->getMinAbscissa();
	} else  if (meanVal_ > this->getMaxAbscissa()) {
		maxPoint[0] = this->getMaxAbscissa();
	}

	this->calcLikelihoodInfo(maxPoint);
	Double_t height = this->getUnNormLikelihood();

	// Multiply by a small factor to avoid problems from rounding errors
	height *= 1.01;

	this->setMaxHeight(height);
}

