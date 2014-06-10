
// Copyright University of Warwick 2006 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauResonanceInfo.cc
    \brief File containing implementation of LauResonanceInfo class.
*/

#include <iostream>

#include "LauParameter.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauResonanceInfo)


LauResonanceInfo::LauResonanceInfo(const TString& name, Double_t mass, Double_t width, Int_t spin, Int_t charge, Double_t range) :
	name_(name),
	sanitisedName_(""),
	mass_(0),
	width_(0),
	spin_(spin),
	charge_(charge),
	range_(range),
	conjugate_(0),
	extraPars_()
{
	this->sanitiseName();
	mass_ = new LauParameter(sanitisedName_+"_MASS",mass,0.0,3.0*mass,kTRUE);
	mass_->secondStage(kTRUE);
	width_ = new LauParameter(sanitisedName_+"_WIDTH",width,0.0,3.0*width,kTRUE);
	width_->secondStage(kTRUE);
}

LauResonanceInfo::~LauResonanceInfo()
{
	delete mass_; mass_ = 0;
	delete width_; width_ = 0;
}

LauResonanceInfo::LauResonanceInfo( const LauResonanceInfo& other, const TString& newName, const Int_t newCharge ) :
	name_(newName),
	sanitisedName_(""),
	mass_(0),
	width_(0),
	spin_(other.spin_),
	charge_(newCharge),
	range_(other.range_),
	conjugate_(0),
	extraPars_()
{
	this->sanitiseName();
	mass_ = other.mass_->createClone( sanitisedName_+"_MASS" );
	width_ = other.mass_->createClone( sanitisedName_+"_WIDTH" );
	for ( std::set<LauParameter*>::iterator iter = other.extraPars_.begin(); iter != other.extraPars_.end(); ++iter ) {
		TString parName = (*iter)->name();
		parName.Remove(0, parName.Last('_'));
		parName.Prepend( sanitisedName_ );
		LauParameter* par = (*iter)->createClone( parName );
		extraPars_.insert( par );
	}
}

LauResonanceInfo* LauResonanceInfo::createChargeConjugate()
{
	Int_t newCharge = -charge_;

	TString newName( name_ );
	Ssiz_t index = newName.Index("+");
	if ( index != -1 ) {
		newName.Replace( index, 1, "-" );
	} else {
		index = newName.Index("-");
		if ( index != -1 ) {
			newName.Replace( index, 1, "+" );
		}
	}

	LauResonanceInfo* conjugate = new LauResonanceInfo( *this, newName, newCharge );
	conjugate->conjugate_ = this;
	this->conjugate_ = conjugate;

	return conjugate;
}

LauResonanceInfo* LauResonanceInfo::createSharedParameterRecord( const TString& name )
{
	LauResonanceInfo* newinfo = new LauResonanceInfo( *this, name, charge_ );

	sharedParRecords_.push_back(newinfo);

	return newinfo;
}

LauParameter* LauResonanceInfo::getExtraParameter( const TString& parName )
{
	LauParameter* par(0);
	for ( std::set<LauParameter*>::iterator iter = extraPars_.begin(); iter != extraPars_.end(); ++iter ) {
		if ( (*iter)->name() == parName ) {
			par = (*iter);
		}
	}
	return par;
}

void LauResonanceInfo::addExtraParameter( LauParameter* param )
{
	bool ok = extraPars_.insert( param ).second;
	if ( !ok ) {
		std::cerr << "WARNING in LauResonanceInfo::addExtraParameter : parameter already present, not adding again" << std::endl;
		return;
	}

	if ( conjugate_ != 0 ) {
		conjugate_->addCloneOfExtraParameter(param);
	}

	for ( std::vector<LauResonanceInfo*>::iterator iter = sharedParRecords_.begin(); iter != sharedParRecords_.end(); ++iter ) {
		(*iter)->addCloneOfExtraParameter(param);
	}
}

void LauResonanceInfo::addCloneOfExtraParameter( LauParameter* param )
{
	TString parName = param->name();
	parName.Remove(0, parName.Last('_'));
	parName.Prepend( sanitisedName_ );

	LauParameter* cloneParam = param->createClone( parName );
	extraPars_.insert( cloneParam );
}

ostream& operator<<( ostream& stream, const LauResonanceInfo& infoRecord )
{
	stream << infoRecord.getName() << ": ";
	stream << "mass = " << infoRecord.getMass()->value() << ", ";
	stream << "width = " << infoRecord.getWidth()->value() << ", ";
	stream << "spin = " << infoRecord.getSpin() << ", ";
	Int_t charge = infoRecord.getCharge();
	if ( charge < 0 ) {
		stream << "charge = " << infoRecord.getCharge() << ", ";
	} else {
		stream << "charge =  " << infoRecord.getCharge() << ", ";
	}
	stream << "range = " << infoRecord.getRange();

	return stream;
}

void LauResonanceInfo::sanitiseName()
{
	sanitisedName_ = name_;
	sanitisedName_ = sanitisedName_.ReplaceAll("+","p");
	sanitisedName_ = sanitisedName_.ReplaceAll("-","m");
	sanitisedName_ = sanitisedName_.ReplaceAll("*","st");
	sanitisedName_ = sanitisedName_.ReplaceAll("(","_");
	sanitisedName_ = sanitisedName_.ReplaceAll(")","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("[","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("]","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("<","_");
	sanitisedName_ = sanitisedName_.ReplaceAll(">","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("{","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("}","_");
	sanitisedName_ = sanitisedName_.ReplaceAll(" ","_");
	sanitisedName_ = sanitisedName_.ReplaceAll("$","");
	sanitisedName_ = sanitisedName_.ReplaceAll("%","");
	sanitisedName_ = sanitisedName_.ReplaceAll("&","");
	sanitisedName_ = sanitisedName_.ReplaceAll("/","");
	sanitisedName_ = sanitisedName_.ReplaceAll(":","");
	sanitisedName_ = sanitisedName_.ReplaceAll(";","");
	sanitisedName_ = sanitisedName_.ReplaceAll("=","");
	sanitisedName_ = sanitisedName_.ReplaceAll("\\","");
	sanitisedName_ = sanitisedName_.ReplaceAll("^","");
	sanitisedName_ = sanitisedName_.ReplaceAll("|","");
	sanitisedName_ = sanitisedName_.ReplaceAll(",","");
	sanitisedName_ = sanitisedName_.ReplaceAll(".","");
	sanitisedName_.Remove(TString::kBoth,'_');
}

