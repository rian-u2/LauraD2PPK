/*! \file LauDPPartialIntegralInfo.cc
    \brief File containing implementation of LauDPPartialIntegralInfo class.
*/

#include <iostream>

#include "LauDPPartialIntegralInfo.hh"

ClassImp(LauDPPartialIntegralInfo)


LauDPPartialIntegralInfo::LauDPPartialIntegralInfo(const Double_t minm13, const Double_t maxm13, const Double_t minm23, const Double_t maxm23, const Double_t m13BinWidth, const Double_t m23BinWidth) :
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

ostream& operator<<( ostream& stream, const LauDPPartialIntegralInfo& infoRecord )
{
	stream << "minm13 = " << infoRecord.getMinm13() << ", ";
	stream << "maxm13 = " << infoRecord.getMaxm13() << ", ";
	stream << "minm23 = " << infoRecord.getMinm23() << ", ";
	stream << "maxm23 = " << infoRecord.getMaxm23() << ", ";
	stream << "m13BinWidth = " << infoRecord.getM13BinWidth() << ", ";
	stream << "m23BinWidth = " << infoRecord.getM23BinWidth() << std::endl;
	return stream;
}

