
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DSplineDP.hh
    \brief File containing declaration of Lau2DSplineDP class.
*/

/*! \class Lau2DSplineDP
    \brief Class for defining variations across a 2D DP using a spline.

    Class for defining variations across a 2D DP using a spline.
    Employs a 2D cubic spline to get the histogram value based on an input histogram.
    The returned values are not normalised to the total histogram area
    (useful for efficiency histograms for example).
    The histogram can be defined in the conventional DP (m13Sq vs m23Sq) or in the square DP.
*/

#ifndef LAU_2DSPLINE_DP
#define LAU_2DSPLINE_DP

#include "Lau2DAbsHistDP.hh"

class TH2;
class Lau2DCubicSpline;
class LauDaughters;
class LauKinematics;

class Lau2DSplineDP : public Lau2DAbsHistDP {

	public:
		//! Constructor
		/*!
		    \param [in] hist the 2D DP histogram
		    \param [in] daughters the daughter particles
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors (useful for systematic error evaluation).
		    The seed for the random number generator used to fluctuate the bins should first be set using LauRandom::setSeed.
		    \param [in] avEff the desired average efficiency - see Lau2DSplineDP::raiseOrLowerBins.
		    The seed for the random number generator used to raise or lower the bins should first be set using LauRandom::setSeed.
		    \param [in] avEffError the error on that efficiency - see Lau2DSplineDP::raiseOrLowerBins
		    \param [in] useUpperHalfOnly boolean flag to specify that the supplied histogram contains only the upper half of a symmetric DP
		    \param [in] squareDP boolean flag to specify whether the supplied histogram is in square DP coordinates
		*/
		Lau2DSplineDP(const TH2* hist, const LauDaughters* daughters,
				Bool_t fluctuateBins = kFALSE, Double_t avEff = -1.0, 
				Double_t avEffError = -1.0, Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Constructor
		/*!
		    \param [in] hist the 2D DP histogram
		    \param [in] errorHi the 2D DP histogram containing the upper uncertainty
		    \param [in] errorLo the 2D DP histogram containing the lower uncertainty
		    \param [in] daughters the daughter particles
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors (useful for systematic error evaluation).
		    The seed for the random number generator used to fluctuate the bins should first be set using LauRandom::setSeed.
		    \param [in] avEff the desired average efficiency - see Lau2DSplineDP::raiseOrLowerBins.
		    The seed for the random number generator used to raise or lower the bins should first be set using LauRandom::setSeed.
		    \param [in] avEffError the error on that efficiency - see Lau2DSplineDP::raiseOrLowerBins
		    \param [in] useUpperHalfOnly boolean flag to specify that the supplied histogram contains only the upper half of a symmetric DP
		    \param [in] squareDP boolean flag to specify whether the supplied histogram is in square DP coordinates
		*/
		Lau2DSplineDP(const TH2* hist, const TH2* errorHi, const TH2* errorLo, const LauDaughters* daughters,
				Bool_t fluctuateBins = kFALSE, Double_t avEff = -1.0, 
				Double_t avEffError = -1.0, Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Destructor
		virtual ~Lau2DSplineDP();

		//! Perform the interpolation
		/*!
		    \param [in] x the x-axis value
		    \param [in] y the y-aixs value
		    \return the interpolated histogram value
		*/
		Double_t interpolateXY(Double_t x, Double_t y) const;

	private:
		//! Copy constructor - not implemented
		Lau2DSplineDP( const Lau2DSplineDP& rhs );

		//! Copy assignment operator - not implemented
		Lau2DSplineDP& operator=(const Lau2DSplineDP& rhs);

		//! A 2D cubic spline generated from the histogram
		Lau2DCubicSpline* spline_;
	
		ClassDef(Lau2DSplineDP,0) // 2D Spline utility class for DP analyses
};

#endif
