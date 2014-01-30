
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DAbsHistDP.hh
    \brief File containing declaration of Lau2DAbsHistDP class.
*/

/*! \class Lau2DAbsHistDP
    \brief Abstract base class for defining a variation across a 2D DP based on a histogram.

    Abstract base class for defining an unnormalised variation across a 2D DP based on a histogram.
    Contains helper methods to vary bin contents in the input histogram within uncertainties and 
    scale the input histogram to match a given average value.
    The histogram can be defined in the conventional DP (m13Sq vs m23Sq) or in the square DP and
    the upper half can be used to describe symmetric DPs.
*/

#ifndef LAU_2DABSHIST_DP
#define LAU_2DABSHIST_DP

#include "Lau2DAbsDP.hh"

class TH2;
class LauDaughters;
class LauKinematics;

class Lau2DAbsHistDP : public Lau2DAbsDP {

	public:
		//! Constructor
		/*!
		    \param [in] daughters the daughter particles
		    \param [in] useUpperHalfOnly boolean flag to specify that the supplied histogram contains only the upper half of a symmetric DP
		    \param [in] squareDP boolean flag to specify whether the supplied histogram is in square DP coordinates
		*/
		Lau2DAbsHistDP(const LauDaughters* daughters, Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Copy constructor
		//Lau2DAbsHistDP( const Lau2DAbsHistDP& rhs );

		//! Destructor
		virtual ~Lau2DAbsHistDP();

		//! Perform the interpolation
		/*!
		    \param [in] x the x-axis value
		    \param [in] y the y-axis value
		    \return the interpolated histogram value
		*/
		virtual Double_t interpolateXY(Double_t x, Double_t y) const=0;

	protected:
		//! Fluctuate the contents of each histogram bin independently, in accordance with their errors
		/*!
		    \param [in,out] hist the histogram
		*/
		void doBinFluctuation(TH2* hist);

		//! Rescale the histogram bin contents based on the desired average efficiency and its uncertainty
		/*!
		    The new average is sampled from a Gaussian distribution G(x;avEff,avEffError).
		    The histogram is then rescaled according to newAvg/oldAvg.
		    \param [in,out] hist the histogram
		    \param [in] avEff the desired average efficiency
		    \param [in] avEffError the error on that efficiency
		*/
		void raiseOrLowerBins(TH2* hist, Double_t avEff, Double_t avEffError);

		//! Compute the average bin content for bins within the kinematic boundary
		/*!
		    This method just uses the raw bin contents with no interpolation
		    \param [in,out] hist the histogram
		    \return the average value over the DP
		*/
		Double_t computeAverageContents(TH2 const * const hist) const;

		//! Check whether the given co-ordinates are within the kinematic boundary
		/*!
		    \param [in] x the x co-ordinate
		    \param [in] y the y co-ordinate
		    \return true if the co-ordinates are within the kinematic boundary, otherwise false
		*/
		Bool_t withinDPBoundaries(Double_t x, Double_t y) const;

		//! If only using the upper half of the (symmetric) DP then transform into the correct half
		/*!
		    \param [in,out] x the x co-ordinate
		    \param [in,out] y the y co-ordinate
		*/
		void getUpperHalf(Double_t& x, Double_t& y) const;

	private:
		//! Copy constructor - not implemented
		Lau2DAbsHistDP( const Lau2DAbsHistDP& rhs );

		//! Copy assignment operator - not implemented
		Lau2DAbsHistDP& operator=(const Lau2DAbsHistDP& rhs);

		//! Kinematics used to check events are within DP boundary
		const LauKinematics* kinematics_;
		
		//! Boolean for using the upper half of DP
		Bool_t upperHalf_;
		//! Boolean for using square DP variables
		Bool_t squareDP_;

		ClassDef(Lau2DAbsHistDP,0) // Abstract base class for 2D DP variations based on a histogram
};

#endif
