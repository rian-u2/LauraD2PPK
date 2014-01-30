
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau2DAbsDPPdf.hh
    \brief File containing declaration of Lau2DAbsDPPdf class.
*/

/*! \class Lau2DAbsDPPdf
    \brief Pure abstract base class for defining a variation across a 2D DP.

    Pure abstract base class for defining a normalised variation across a 2D DP.
*/

#ifndef LAU_2DABS_DP_PDF
#define LAU_2DABS_DP_PDF

#include "Rtypes.h"

class Lau2DAbsDPPdf {

	public:
		//! Constructor
		Lau2DAbsDPPdf() {}

		//! Destructor
		virtual ~Lau2DAbsDPPdf() {}

		//! Retrieve maximum height
		virtual Double_t getMaxHeight() const=0;

		//! Retrieve PDF normalisation
		virtual Double_t getHistNorm() const=0;

		//! Perform the interpolation (unnormalised)
		/*!
		    \param [in] x the x-axis value
		    \param [in] y the y-aixs value
		    \return the unnormalised PDF value
		*/
		virtual Double_t interpolateXY(Double_t x, Double_t y) const=0;

		//! Perform the interpolation and divide by the normalisation
		/*!
		    \param [in] x the x-axis abscissa value
		    \param [in] y the y-axis abscissa value
		    \return the normalised PDF value
		*/
		virtual Double_t interpolateXYNorm(Double_t x, Double_t y) const=0;

	private:
		//! Copy constructor - not implemented
		Lau2DAbsDPPdf( const Lau2DAbsDPPdf& rhs );

		//! Copy assignment operator - not implemented
		Lau2DAbsDPPdf& operator=(const Lau2DAbsDPPdf& rhs);

		ClassDef(Lau2DAbsDPPdf,0) // Abstract base class for 2D DP variation
};

#endif
