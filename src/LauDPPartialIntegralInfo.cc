/*! \file LauDPPartialIntegralInfo.cc
    \brief File containing implementation of LauDPPartialIntegralInfo class.
*/

#include <iostream>

#include "LauDPPartialIntegralInfo.hh"

ClassImp(LauDPPartialIntegralInfo)


Double_t minm13_;
Double_t maxm13_;
Double_t minm23_;
Double_t maxm23_;
Double_t m13BinWidth_;
Double_t m23BinWidth_;

LauDPPartialIntegralInfo::LauDPPartialIntegralInfo(const TString& name, Double_t minm13, Double_t maxm13, Double_t minm23, Double_t maxm23, Double_t m13BinWidth, Double_t m23BinWidth) :
	name_(name),
	minm13_(minm13),
	maxm13_(maxm13),
	minm23_(minm23),
	maxm23_(maxm23),
	m13BinWidth_(m13BinWidth),
	m23BinWidth_(m23BinWidth)
{
}

LauDPPartialIntegralInfo::~LauDPPartialIntegralInfo()
{
}

LauDPPartialIntegralInfo::LauDPPartialIntegralInfo( const LauDPPartialIntegralInfo& other ) :
	name_( other.name_ ),
	minm13_( other.minm13_ ),
	maxm13_( other.maxm13_ ),
	minm23_( other.minm23_ ),
	maxm23_( other.maxm23_ ),
	m13BinWidth_( other.m13BinWidth_ ),
	m23BinWidth_( other.m23BinWidth_ )
{
}

LauDPPartialIntegralInfo::LauDPPartialIntegralInfo( const LauDPPartialIntegralInfo& other, const TString& newName ) :
	name_( newName ),
	minm13_( other.minm13_ ),
	maxm13_( other.maxm13_ ),
	minm23_( other.minm23_ ),
	maxm23_( other.maxm23_ ),
	m13BinWidth_( other.m13BinWidth_ ),
	m23BinWidth_( other.m23BinWidth_ )
{
}

ostream& operator<<( ostream& stream, const LauDPPartialIntegralInfo& infoRecord )
{
	stream << infoRecord.getName() << ": ";
	stream << "minm13 = " << infoRecord.getMinm13() << ", ";
	stream << "maxm13 = " << infoRecord.getMaxm13() << ", ";
	stream << "minm23 = " << infoRecord.getMinm23() << ", ";
	stream << "maxm23 = " << infoRecord.getMaxm23() << ", ";
	stream << "m13BinWidth = " << infoRecord.getM13BinWidth() << ", ";
	stream << "m23BinWidth = " << infoRecord.getM23BinWidth();
	return stream;
}


