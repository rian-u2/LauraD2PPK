
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBkgndDPModel.cc
    \brief File containing implementation of LauBkgndDPModel class.
*/

#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TRandom.h"
#include "TSystem.h"

#include "Lau2DHistDPPdf.hh"
#include "Lau2DSplineDPPdf.hh"
#include "LauBkgndDPModel.hh"
#include "LauDaughters.hh"
#include "LauFitDataTree.hh"
#include "LauKinematics.hh"
#include "LauRandom.hh"
#include "LauVetoes.hh"

ClassImp(LauBkgndDPModel)


LauBkgndDPModel::LauBkgndDPModel(LauDaughters* daughters, LauVetoes* vetoes) :
	LauAbsBkgndDPModel(daughters, vetoes),
	symmetricalDP_(kFALSE),
	squareDP_(kFALSE),
	bgHistDPPdf_(0),
	curEvtHistVal_(0.0),
	maxPdfHeight_(1.0),
	pdfNorm_(1.0),
	doneGenWarning_(kFALSE)
{
	if (daughters != 0) {
		symmetricalDP_ = daughters->gotSymmetricalDP();
	}
}

LauBkgndDPModel::~LauBkgndDPModel()
{
	if (bgHistDPPdf_ != 0) {
		delete bgHistDPPdf_; bgHistDPPdf_ = 0;
	}
}

void LauBkgndDPModel::setBkgndHisto(const TH2* histo, Bool_t useInterpolation, Bool_t fluctuateBins, Bool_t useUpperHalfOnly, Bool_t squareDP)
{
	Bool_t upperHalf = kFALSE;
	if (symmetricalDP_ == kTRUE && useUpperHalfOnly == kTRUE) {upperHalf = kTRUE;}
	cout<<"Bg histogram has upperHalf = "<<static_cast<Int_t>(upperHalf)<<endl;

	squareDP_ = squareDP;

	LauKinematics* kinematics = this->getKinematics();
	const LauVetoes* vetoes = this->getVetoes();
	bgHistDPPdf_ = new Lau2DHistDPPdf(histo, kinematics, vetoes, useInterpolation, fluctuateBins, upperHalf, squareDP);

	maxPdfHeight_ = bgHistDPPdf_->getMaxHeight();
	pdfNorm_ = bgHistDPPdf_->getHistNorm();
}

void LauBkgndDPModel::setBkgndSpline(const TH2* histo, Bool_t fluctuateBins, Bool_t useUpperHalfOnly, Bool_t squareDP)
{
	Bool_t upperHalf = kFALSE;
	if (symmetricalDP_ == kTRUE && useUpperHalfOnly == kTRUE) {upperHalf = kTRUE;}
	cout<<"Bg histogram has upperHalf = "<<static_cast<Int_t>(upperHalf)<<endl;

	squareDP_ = squareDP;

	LauKinematics* kinematics = this->getKinematics();
	const LauVetoes* vetoes = this->getVetoes();
	bgHistDPPdf_ = new Lau2DSplineDPPdf(histo, kinematics, vetoes, fluctuateBins, upperHalf, squareDP);

	maxPdfHeight_ = bgHistDPPdf_->getMaxHeight();
	pdfNorm_ = bgHistDPPdf_->getHistNorm();
}

Double_t LauBkgndDPModel::calcHistValue(Double_t xVal, Double_t yVal)
{
	// Get the likelihood value of the background in the Dalitz plot. 

	// Check that we have a valid histogram PDF
	if (bgHistDPPdf_ == 0) {
		cerr << "WARNING in LauBkgndDPModel::calcHistValue : We don't have a histogram so assuming the likelihood is flat in the Dalitz plot." << endl;
		this->setBkgndHisto( 0, kFALSE, kFALSE, kFALSE, kFALSE );
	}

	// Find out the un-normalised PDF value
	Double_t value = bgHistDPPdf_->interpolateXY(xVal, yVal);

	LauKinematics* kinematics = this->getKinematics();

	// For square DP co-ordinates, need to divide by Jacobian
	if (squareDP_ == kTRUE) {
		// Make sure that square DP kinematics are correct, then get Jacobian
		kinematics->updateSqDPKinematics(xVal, yVal);
		Double_t jacobian = kinematics->calcSqDPJacobian();
		value /= jacobian;
	}

	return value;
}

void LauBkgndDPModel::initialise() 
{
}

Bool_t LauBkgndDPModel::generate()
{
	// Routine to generate the background, using data provided by an
	// already defined histogram.

	LauKinematics* kinematics = this->getKinematics();

	Bool_t gotBG(kFALSE);

	while (gotBG == kFALSE) {

		if (squareDP_ == kTRUE) {
			// Generate a point in m', theta' space. By construction, this point
			// is already within the DP region.
			Double_t mPrime(0.0), thetaPrime(0.0);
			kinematics->genFlatSqDP(mPrime, thetaPrime);

			// If we're in a symmetrical DP then we should only generate events in one half
			if ( symmetricalDP_ && thetaPrime > 0.5 ) {
				thetaPrime = 1.0 - thetaPrime;
			}

			// Calculate histogram height for DP point and
			// compare with the maximum height
			if ( bgHistDPPdf_ != 0 ) {
				Double_t bgContDP = bgHistDPPdf_->interpolateXY(mPrime, thetaPrime)/maxPdfHeight_;
				if (LauRandom::randomFun()->Rndm() < bgContDP) {
					kinematics->updateSqDPKinematics(mPrime, thetaPrime);
					gotBG = kTRUE;
				}
			} else {
				if ( !doneGenWarning_ ) {
					cerr << "WARNING in LauBkgndDPModel::generate : We don't have a histogram so generating flat in the square DP, which won't be flat in the conventional DP!" << endl;
					cerr << "WARNING in LauBkgndDPModel::generate : This should never happen!! What have you done?!" << endl;
					doneGenWarning_ = kTRUE;
				}
				kinematics->updateSqDPKinematics(mPrime, thetaPrime);
				gotBG = kTRUE;
			}
		} else {
			// Generate a point in the Dalitz plot (phase-space).
			Double_t m13Sq(0.0), m23Sq(0.0);
			kinematics->genFlatPhaseSpace(m13Sq, m23Sq);

			// If we're in a symmetrical DP then we should only generate events in one half
			if ( symmetricalDP_ && m13Sq > m23Sq ) {
				Double_t tmpSq = m13Sq;
				m13Sq = m23Sq;
				m23Sq = tmpSq;
			}

			// Calculate histogram height for DP point and
			// compare with the maximum height
			if ( bgHistDPPdf_ != 0 ) {
				Double_t bgContDP = bgHistDPPdf_->interpolateXY(m13Sq, m23Sq)/maxPdfHeight_;
				if (LauRandom::randomFun()->Rndm() < bgContDP) {
					kinematics->updateKinematics(m13Sq, m23Sq);
					gotBG = kTRUE;	 
				}
			} else {
				if ( !doneGenWarning_ ) {
					cerr << "WARNING in LauBkgndDPModel::generate : We don't have a histogram so generating flat in the DP." << endl;
					doneGenWarning_ = kTRUE;
				}
				kinematics->updateKinematics(m13Sq, m23Sq);
				gotBG = kTRUE;
			}
		}
	}

	// Implement veto
	Bool_t vetoOK(kTRUE);
	const LauVetoes* vetoes = this->getVetoes();
	if (vetoes) {
		vetoOK = vetoes->passVeto(kinematics);
	}
	// Call this function recusively until we pass the veto.
	if (vetoOK == kFALSE) {
		this->generate();
	}
	return kTRUE;
}

void LauBkgndDPModel::fillDataTree(const LauFitDataTree& inputFitTree)
{
	// In LauFitDataTree, the first two variables should always be
	// m13^2 and m23^2. Other variables follow thus: charge.

	Int_t nBranches = inputFitTree.nBranches();
	if (nBranches < 2) {
		cout<<"Error in LauBkgndDPModel::fillDataTree. Expecting at least 2 variables "
			<<"in input data tree, but there are "<<nBranches<<"! Make sure you have "
			<<"the right number of variables in your input data file!"<<endl;
		return;
	}

	Double_t m13Sq(0.0), m23Sq(0.0), mPrime(0.0), thetaPrime(0.0);

	UInt_t nEvents = inputFitTree.nEvents();
	LauKinematics* kinematics = this->getKinematics();

	// clear and resize the data vector
	bgData_.clear();
	bgData_.resize(nEvents);

	for (UInt_t iEvt = 0; iEvt < nEvents; iEvt++) {

		const LauFitData& dataValues = inputFitTree.getData(iEvt);
		LauFitData::const_iterator iter = dataValues.find("m13Sq");
		m13Sq = iter->second;
		iter = dataValues.find("m23Sq");
		m23Sq = iter->second;

		// Update the kinematics. This will also update m' and theta' if squareDP = true
		kinematics->updateKinematics(m13Sq, m23Sq);

		if (squareDP_ == kTRUE) {
			mPrime = kinematics->getmPrime();
			thetaPrime = kinematics->getThetaPrime();
			curEvtHistVal_ = this->calcHistValue(mPrime, thetaPrime);
		} else {
			curEvtHistVal_ = this->calcHistValue(m13Sq, m23Sq);
		}

		bgData_[iEvt] = curEvtHistVal_;
	}
}

Double_t LauBkgndDPModel::getUnNormValue(UInt_t iEvt)
{
	// Retrieve the likelihood for the given event
	this->setDataEventNo(iEvt);
	return curEvtHistVal_;
}

Double_t LauBkgndDPModel::getLikelihood(UInt_t iEvt)
{
	// Retrieve the likelihood for the given event
	this->setDataEventNo(iEvt);
	Double_t llhd = curEvtHistVal_ / this->getPdfNorm();
	return llhd;
}

void LauBkgndDPModel::setDataEventNo(UInt_t iEvt)
{
	// Retrieve the data for event iEvt
	if (bgData_.size() > iEvt) {
		curEvtHistVal_ = bgData_[iEvt];
	} else {
		cerr<<"ERROR in LauBkgndDPModel::setDataEventNo : Event index too large: "<<iEvt<<" >= "<<bgData_.size()<<"."<<endl;
	}
}

