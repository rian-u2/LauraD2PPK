
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
	range_(range)
{
	sanitiseName();
	mass_ = new LauParameter(sanitisedName_+"_MASS",mass,0.0,range,kTRUE);
	width_ = new LauParameter(sanitisedName_+"_WIDTH",width,0.0,3*width,kTRUE);
}

LauResonanceInfo::~LauResonanceInfo()
{
	delete mass_; mass_ = 0;
	delete width_; width_ = 0;
}

LauResonanceInfo::LauResonanceInfo( const LauResonanceInfo& other ) :
	name_( other.name_ ),
	sanitisedName_( other.sanitisedName_ ),
	mass_( other.mass_->createClone() ),
	width_( other.width_->createClone() ),
	spin_( other.spin_ ),
	charge_( other.charge_ ),
	range_( other.range_ )
{
}

LauResonanceInfo::LauResonanceInfo( const LauResonanceInfo& other, const TString& newName, const Int_t newCharge ) :
	name_( newName ),
	sanitisedName_(""),
	mass_( 0 ),
	width_( 0 ),
	spin_( other.spin_ ),
	charge_( newCharge ),
	range_( other.range_ )
{
	sanitiseName();
	mass_ = other.mass_->createClone( sanitisedName_+"_MASS" );
	width_ = other.mass_->createClone( sanitisedName_+"_WIDTH" );
}

LauResonanceInfo* LauResonanceInfo::createChargeConjugate() const
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

	return conjugate;
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
