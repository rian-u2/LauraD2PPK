/*! \file LauDPPartialIntegralInfo.cc
    \brief File containing implementation of LauDPPartialIntegralInfo class.
*/

#include <iostream>

#include "LauDPPartialIntegralInfo.hh"
#include "LauIntegrals.hh"

ClassImp(LauDPPartialIntegralInfo)


LauDPPartialIntegralInfo::LauDPPartialIntegralInfo(const Double_t minm13, const Double_t maxm13,
						   const Double_t minm23, const Double_t maxm23,
						   const Double_t m13BinWidth, const Double_t m23BinWidth,
						   const Double_t precision,
						   const UInt_t nAmp,
						   const UInt_t nIncohAmp) :
	minm13_(minm13),
	maxm13_(maxm13),
	minm23_(minm23),
	maxm23_(maxm23),
	m13BinWidth_(m13BinWidth),
	m23BinWidth_(m23BinWidth),
	nm13Points_(static_cast<UInt_t>((maxm13-minm13)/m13BinWidth)),
	nm23Points_(static_cast<UInt_t>((maxm23-minm23)/m23BinWidth)),
	nAmp_(nAmp),
	nIncohAmp_(nIncohAmp)
{
	const Double_t meanm13 = 0.5*(minm13 + maxm13);
	const Double_t rangem13 = maxm13 - minm13;
	const Double_t halfRangem13 = 0.5*rangem13;

	const Double_t meanm23 = 0.5*(minm23 + maxm23);
	const Double_t rangem23 = maxm23 - minm23;
	const Double_t halfRangem23 = 0.5*rangem23;

	const Double_t intFactor = halfRangem13*halfRangem23;

	// Avoid integral if we have no points in either x or y space
	if (nm13Points_ == 0 || nm23Points_ == 0) {
		std::cerr << "ERROR in LauDPPartialIntegralInfo constructor : Range has zero grid points in one or both of the dimensions!" << std::endl;
		return;
	}

	LauIntegrals dpIntegrals(precision);
	dpIntegrals.calcGaussLegendreWeights(nm13Points_, m13Points_, m13Weights_);
	dpIntegrals.calcGaussLegendreWeights(nm23Points_, m23Points_, m23Weights_);

	// Print out total weights for the integration
	Double_t totm13Weight(0.0), totm23Weight(0.0);
	for (UInt_t i = 0; i < nm13Points_; ++i) {
		totm13Weight += m13Weights_[i];
	}
	for (UInt_t i = 0; i < nm23Points_; ++i) {
		totm23Weight += m23Weights_[i];
	}

	std::cout<<"INFO in LauDPPartialIntegralInfo constructor : nm13Points = "<<nm13Points_<<", nm23Points = "<<nm23Points_<<std::endl;
	std::cout<<"                                             : m13BinWidth = "<<m13BinWidth_<<", m23BinWidth = "<<m23BinWidth_<<std::endl;
	std::cout<<"                                             : Integrating over m13 = "<<minm13_<<" to "<<maxm13_<<", m23 = "<<minm23_<<" to "<<maxm23_<<std::endl;
	std::cout<<"                                             : totm13Weight = "<<totm13Weight<<", totm23Weight = "<<totm23Weight<<std::endl;

	// Calculate the m13 and m23 values at the grid points

	UInt_t midpoint = (nm13Points_ + 1)/2;
	for (UInt_t i = 0; i < midpoint; ++i) {

		UInt_t ii = nm13Points_ - 1 - i; // symmetric i index

		Double_t dm13 = halfRangem13*m13Points_[i];
		Double_t m13Val = meanm13 - dm13;
		m13Points_[i] = m13Val;

		m13Val = meanm13 + dm13;
		m13Points_[ii] = m13Val;

	}

	midpoint = (nm23Points_ +1)/2;
	for (UInt_t i = 0; i < midpoint; i++) {

		UInt_t ii = nm23Points_ - 1 - i; // symmetric i index

		Double_t dm23 = halfRangem23*m23Points_[i];
		Double_t m23Val = meanm23 - dm23;
		m23Points_[i] = m23Val;

		m23Val = meanm23 + dm23;
		m23Points_[ii] = m23Val;
	}

	// Now compute the combined weights at each grid point
	weights_.resize( nm13Points_ );
	efficiencies_.resize( nm13Points_ );
	amplitudes_.resize( nm13Points_ );
	incohIntensities_.resize( nm13Points_ );
	for (UInt_t i = 0; i < nm13Points_; ++i) {

		weights_[i].resize( nm23Points_ );
		efficiencies_[i].resize( nm23Points_ );
		amplitudes_[i].resize( nm23Points_ );
		incohIntensities_[i].resize( nm23Points_ );

		for (UInt_t j = 0; j < nm23Points_; ++j) {

			Double_t weight = m13Weights_[i]*m23Weights_[j];
			Double_t jacobian = 4.0*m13Points_[i]*m23Points_[j];
			weight *= (jacobian*intFactor);

			weights_[i][j] = weight;

			amplitudes_[i][j].resize( nAmp_ );
			incohIntensities_[i][j].resize( nIncohAmp_ );

		} // j weights loop
	} // i weights loop
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

