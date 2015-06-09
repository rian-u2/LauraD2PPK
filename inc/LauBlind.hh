
// Copyright University of Warwick 2006 - 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBlind.hh
    \brief File containing declaration of LauBlind class.
*/

/*! \class LauBlind
    \brief Class for blinding and unblinding a number based on a blinding string.

    Numbers are blinded by applying an offset. The blinding string is converted 
    to an integer using TMath::Hash and this integer is used to seed a TRandom3. 
    The offset is sampled from a Gaussian of defined width using the seeded TRandom3.
*/

#ifndef LAU_BLIND
#define LAU_BLIND

#include "TString.h"

class LauBlind {

	public:
		//! Constructor
		/*!
		    \param [in] blindingStr the blinding string
		    \param [in] width the width of the Gaussian for sampling the offset
		*/
		LauBlind(const TString& blindingStr, const Double_t width);

		//! Copy constructor
		LauBlind(const LauBlind& rhs);

		//! Destructor
		virtual ~LauBlind();

		//! Obtain the blinded value
		/*!
		    \param [in] val the unblinded value
		    \return the blinded value
		*/
		inline Double_t blind(const Double_t val) const { return val+offset_; }

		//! Obtain the unblinded value
		/*!
		    \param [in] val the blinded value
		    \return the unblinded value
		*/
		inline Double_t unblind(const Double_t val) const { return val-offset_; }

		//! Obtain the blinding string
		/*!
		    \return the blinding string
		*/
		inline const TString& blindingString() const { return blindingString_; }

		//! Obtain the Gaussian width
		/*!
		    \return the Gaussian width
		*/
		inline Double_t blindingWidth() const { return blindingWidth_; }

	private:
		//! Copy assignment operator (not implemented)
		LauBlind& operator=(const LauBlind& rhs);

		//! Calculate the offset
		void calcOffset();

		//! The blinding string
		const TString blindingString_;

		//! The Gaussian width
		const Double_t blindingWidth_;

		//! The offset used to blind the value
		Double_t offset_;

	public:
		//! Default constructor
		/*!
		    This is purely to allow I/O to succeed, should not generally be used
		*/
		LauBlind();


		ClassDef(LauBlind, 1)
};

#endif
