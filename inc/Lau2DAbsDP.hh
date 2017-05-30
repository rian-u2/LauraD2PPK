
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DAbsDP.hh
    \brief File containing declaration of Lau2DAbsDP class.
*/

/*! \class Lau2DAbsDP
    \brief Pure abstract base class for defining a variation across a 2D DP.

    Pure abstract base class for defining an unnormalised variation across a 2D DP.
*/

#ifndef LAU_2DABS_DP
#define LAU_2DABS_DP

#include "Rtypes.h"


class Lau2DAbsDP {

	public:
		//!Constructor
		Lau2DAbsDP() {}

		//! Destructor
		virtual ~Lau2DAbsDP() {}

		//! Perform the interpolation
		/*!
		    \param [in] x the x-axis value
		    \param [in] y the y-aixs value
		    \return the interpolated histogram value
		*/
		virtual Double_t interpolateXY(Double_t x, Double_t y) const=0;

		//! Determine whether the histogram is defined in the square DP
		/*
		    \return kTRUE if the square DP is being used, kFALSE otherwise
		*/
		virtual Bool_t usingSquareDP() const=0;

	private:
		//! Copy constructor - not implemented
		Lau2DAbsDP( const Lau2DAbsDP& rhs );

		//! Copy assignment operator - not implemented
		Lau2DAbsDP& operator=(const Lau2DAbsDP& rhs);

		ClassDef(Lau2DAbsDP,0) // Abstract base class for 2D DP variation
};

#endif
