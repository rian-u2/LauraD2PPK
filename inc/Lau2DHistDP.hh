
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DHistDP.hh
    \brief File containing declaration of Lau2DHistDP class.
*/

/*! \class Lau2DHistDP
    \brief Class for defining a 2D DP histogram.

    Class for defining a 2D DP histogram.
    Employs linear interpolation to get the histogram value based on how far away a point in (x,y)
    is to nearby bin centres. The returned values are not normalised to the total histogram area
    (useful for efficiency histograms for example).
    The histogram can be defined in the conventional DP (m13Sq vs m23Sq) or in the square DP.
*/

#ifndef LAU_2DHIST_DP
#define LAU_2DHIST_DP

#include "Lau2DAbsHistDP.hh"

class TH2;
class LauDaughters;
class LauKinematics;

class Lau2DHistDP : public Lau2DAbsHistDP {

	public:
		//! Constructor
		/*!
		    \param [in] hist the 2D DP histogram
		    \param [in] daughters the daughter particles
		    \param [in] useInterpolation boolean flag to determine whether linear interpolation between bins should be used or simply the raw bin values
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors (useful for systematic error evaluation)
		    \param [in] avEff the desired average efficiency - see Lau2DHistDP::raiseOrLowerBins
		    \param [in] avEffError the error on that efficiency - see Lau2DHistDP::raiseOrLowerBins
		    \param [in] useUpperHalfOnly boolean flag to specify that the supplied histogram contains only the upper half of a symmetric DP
		    \param [in] squareDP boolean flag to specify whether the supplied histogram is in square DP coordinates
		*/
		Lau2DHistDP(const TH2* hist, const LauDaughters* daughters,
				Bool_t useInterpolation = kTRUE, Bool_t fluctuateBins = kFALSE,
				Double_t avEff = -1.0, Double_t avEffError = -1.0, Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Copy constructor
		//Lau2DHistDP( const Lau2DHistDP& rhs );

		//! Destructor
		virtual ~Lau2DHistDP();

		//! Perform the interpolation
		/*!
		    \param [in] x the x-axis value
		    \param [in] y the y-aixs value
		    \return the interpolated histogram value
		*/
		Double_t interpolateXY(Double_t x, Double_t y) const;

	protected:
		//! Get the raw bin content from the histogram
		/*!
		    \param [in] xBinNo the x-axis bin number
		    \param [in] yBinNo the y-axis bin number
		    \return the bin conent
		*/
		Double_t getBinHistValue(Int_t xBinNo, Int_t yBinNo) const;

	private:
		//! Copy constructor - not implemented
		Lau2DHistDP( const Lau2DHistDP& rhs );

		//! Copy assignment operator - not implemented
		Lau2DHistDP& operator=(const Lau2DHistDP& rhs);

		//! The underlying histogram
		TH2* hist_;
		
		//! The histogram x-axis minimum
		Double_t minX_;
		//! The histogram x-axis maximum
		Double_t maxX_;
		//! The histogram y-axis minimum
		Double_t minY_;
		//! The histogram y-axis maximum
		Double_t maxY_;
		//! The histogram x-axis range
		Double_t rangeX_;
		//! The histogram y-axis range
		Double_t rangeY_;
		
		//! The histogram x-axis bin width
		Double_t binXWidth_;
		//! The histogram y-axis bin width
		Double_t binYWidth_; 
		
		//! The number of bins on the x-axis of the histogram
		Int_t nBinsX_;
		//! The number of bins on the y-axis of the histogram
		Int_t nBinsY_;

		//! Control boolean for using the linear interpolation
		Bool_t useInterpolation_;

		ClassDef(Lau2DHistDP,0) // 2D Histogram utility class for DP analyses
};

#endif
