
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDaughters.cc
    \brief File containing implementation of LauDaughters class.
*/

#include <iostream>

#include "TSystem.h"

#include "LauDatabasePDG.hh"
#include "LauDaughters.hh"
#include "LauKinematics.hh"
#include "LauParticlePDG.hh"

ClassImp(LauDaughters)


LauDaughters::LauDaughters(Int_t codeParent, Int_t code1, Int_t code2, Int_t code3, Bool_t useSquareDP) :
	kinematics_(0),
	parent_(0),
	symmetricalDP_(kFALSE)
{
	this->createParticleLists();

	TString nameParent = LauDatabasePDG::string( codeParent );
	TString name1 = LauDatabasePDG::string( code1 );
	TString name2 = LauDatabasePDG::string( code2 );
	TString name3 = LauDatabasePDG::string( code3 );
	this->setParentType(nameParent);
	this->setDaugType(name1, name2, name3);

	// Create kinematics object
	kinematics_ = new LauKinematics(this->getMassDaug1(), this->getMassDaug2(), this->getMassDaug3(), this->getMassParent(), useSquareDP);
}

LauDaughters::LauDaughters(const TString& nameParent, const TString& name1, const TString& name2, const TString& name3, Bool_t useSquareDP) :
	kinematics_(0),
	parent_(0),
	symmetricalDP_(kFALSE)
{
	this->createParticleLists();

	this->setParentType(nameParent);
	this->setDaugType(name1, name2, name3);

	// Create kinematics object
	kinematics_ = new LauKinematics(this->getMassDaug1(), this->getMassDaug2(), this->getMassDaug3(), this->getMassParent(), useSquareDP);
}

LauDaughters::~LauDaughters()
{
	delete kinematics_; kinematics_ = 0;
}

LauDaughters::LauDaughters( const LauDaughters& rhs ) :
	kinematics_(0),
	parent_(0),
	symmetricalDP_(kFALSE)
{
	this->createParticleLists();

	this->setParentType( rhs.getNameParent() );
	this->setDaugType( rhs.getNameDaug1() ,  rhs.getNameDaug2() ,  rhs.getNameDaug3() );

	// Create kinematics object
	kinematics_ = new LauKinematics(this->getMassDaug1(), this->getMassDaug2(), this->getMassDaug3(), this->getMassParent(), rhs.squareDP());
}

void LauDaughters::createParticleLists()
{
	// Create list of allowed daughters
	allowedDaughters_.clear();
	allowedDaughters_.push_back(LauDatabasePDG::particle("pi+"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("pi-"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("pi0"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("K+"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("K-"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("K_S0"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("eta"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("eta'"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D+"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D-"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D0"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D0_bar"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D_s+"));
	allowedDaughters_.push_back(LauDatabasePDG::particle("D_s-"));

	// Create list of allowed parents
	allowedParents_.clear();
	allowedParents_.push_back(LauDatabasePDG::particle("B+"));
	allowedParents_.push_back(LauDatabasePDG::particle("B-"));
	allowedParents_.push_back(LauDatabasePDG::particle("B0"));
	allowedParents_.push_back(LauDatabasePDG::particle("B0_bar"));
	allowedParents_.push_back(LauDatabasePDG::particle("B_s0"));
	allowedParents_.push_back(LauDatabasePDG::particle("B_s0_bar"));
	allowedParents_.push_back(LauDatabasePDG::particle("D+"));
	allowedParents_.push_back(LauDatabasePDG::particle("D-"));
	allowedParents_.push_back(LauDatabasePDG::particle("D0"));
	allowedParents_.push_back(LauDatabasePDG::particle("D0_bar"));
	allowedParents_.push_back(LauDatabasePDG::particle("D_s+"));
	allowedParents_.push_back(LauDatabasePDG::particle("D_s-"));
}

void LauDaughters::setParentType(const TString& nameParent)
{
	parent_ = 0;

	const Int_t codeParent = LauDatabasePDG::code( nameParent );

	for ( std::vector<const LauParticlePDG*>::const_iterator iter = allowedParents_.begin(); iter != allowedParents_.end(); ++iter ) {
		const Int_t code = (*iter)->code();
		if ( codeParent == code ) {
			parent_ = (*iter);
			std::cout<<"INFO in LauDaughters::setParentType : Setting parent to be "<<parent_->string()<<" == "<<parent_->code()<<std::endl;
			break;
		}
	}

	if ( ! parent_ ) {
		std::cerr<<"ERROR in LauDaughters::setParentType : Couldn't find a valid parent called \""<<nameParent<<"\"."<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
}

void LauDaughters::setDaugType(const TString& name1, const TString& name2, const TString& name3) 
{
	const TString names[3] = { name1, name2, name3 };
	const Int_t codes[3] = { LauDatabasePDG::code( name1 ), LauDatabasePDG::code( name2 ), LauDatabasePDG::code( name3 ) };

	daughters_.clear();
	daughters_.resize(3);

	for ( int i(0); i<3; ++i ) {
		for ( std::vector<const LauParticlePDG*>::const_iterator iter = allowedDaughters_.begin(); iter != allowedDaughters_.end(); ++iter ) {
			Int_t code = (*iter)->code();
			if ( codes[i] == code ) {
				daughters_[i] = (*iter);
				std::cout<<"INFO in LauDaughters::setDaugType : Setting daughter "<<i+1<<" to be "<<daughters_[i]->string()<<" == "<<daughters_[i]->code()<<std::endl;
				break;
			}
		}
		if ( ! daughters_[i] ) {
			std::cerr<<"ERROR in LauDaughters::setDaugType : Couldn't find a valid daughter called \""<<names[i]<<"\"."<<std::endl;
			gSystem->Exit(EXIT_FAILURE);
		}
	}

	// Initialise the various data members concerning particle masses
	this->sanityCheck();

	// Check whether we have a symmetrical Dalitz plot
	this->testDPSymmetry();
}

void LauDaughters::testDPSymmetry() 
{
	// Check to see if we have a symmetrical DP.

	symmetricalDP_ = kFALSE;
        if ( daughters_[0]->code() == daughters_[1]->code() ) {
		std::cout<<"INFO in LauDaughters::testDPSymmetry : We have a symmetrical DP. "<<std::endl;
		symmetricalDP_ = kTRUE;
	} else if ( daughters_[0]->code() == daughters_[2]->code() ) {
		std::cerr<<"WARNING in LauDaughters::testDPSymmetry : daughter 0 and daughter 2 are both "<<daughters_[0]->string()<<" but DP can only fold on daughers 0 and 1."<<std::endl;
	} else if ( daughters_[1]->code() == daughters_[2]->code() ) {
		std::cerr<<"WARNING in LauDaughters::testDPSymmetry : daughter 1 and daughter 2 are both "<<daughters_[1]->string()<<" but DP can only fold on daughers 0 and 1."<<std::endl;
	}

}

void LauDaughters::sanityCheck()
{
	// Check masses and charges of daughters

	Int_t totCharge(0);
	Double_t totMass(0.0);

	for ( std::vector<const LauParticlePDG*>::const_iterator iter = daughters_.begin(); iter != daughters_.end(); ++iter ) {
		totCharge += (*iter)->charge();
		totMass += (*iter)->mass();
	}

	if (totCharge != parent_->charge()) {
		std::cerr<<"ERROR in LauDaughters::sanityCheck : Total charge of daughters ("<<totCharge<<") not equal to charge of parent ("<<parent_->charge()<<")."<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	if (totMass > parent_->mass()) {
		std::cerr<<"ERROR in LauDaughters::sanityCheck : Total mass of daughters ("<<totMass<<") greater than mass of parent ("<<parent_->mass()<<")."<<std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
}

Double_t LauDaughters::getMassDaug1() const
{  
	return daughters_[0]->mass();
}

Double_t LauDaughters::getMassDaug2() const
{  
	return daughters_[1]->mass();
}

Double_t LauDaughters::getMassDaug3() const
{  
	return daughters_[2]->mass();
}

Double_t LauDaughters::getMassParent() const
{
	return parent_->mass();
}

TString LauDaughters::getNameDaug1() const
{
	return daughters_[0]->string();
}

TString LauDaughters::getNameDaug2() const
{
	return daughters_[1]->string();
}

TString LauDaughters::getNameDaug3() const
{
	return daughters_[2]->string();
}

TString LauDaughters::getNameParent() const
{
	return parent_->string();
}

Int_t LauDaughters::getTypeDaug1() const
{
	return daughters_[0]->code();
}

Int_t LauDaughters::getTypeDaug2() const
{
	return daughters_[1]->code();
}

Int_t LauDaughters::getTypeDaug3() const
{
	return daughters_[2]->code();
}

Int_t LauDaughters::getTypeParent() const
{
	return parent_->code();
}

Int_t LauDaughters::getChargeDaug1() const
{
	return daughters_[0]->charge();
}

Int_t LauDaughters::getChargeDaug2() const
{
	return daughters_[1]->charge();
}

Int_t LauDaughters::getChargeDaug3() const
{
	return daughters_[2]->charge();
}

Int_t LauDaughters::getChargeParent() const
{
	return parent_->charge();
}

Int_t LauDaughters::getCharge(Int_t resPairAmpInt) const
{
	Int_t charge = this->getChargeParent();
	if ( resPairAmpInt>0 && resPairAmpInt<4 ) {
		charge -= daughters_[resPairAmpInt-1]->charge();
	}
	return charge;
}

