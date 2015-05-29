
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
		    \param [in] blindingString the blinding string
		    \param [in] width the width of the Gaussian for sampling the offset
		*/
		LauBlind(const TString blindingString, const Int_t width)
			: offset_(0) {calcOffset(blindingString, width);}

		//! Obtain the blinded value
		/*!
		    \param [in] val the unblinded value
		    \return the blinded value
		*/
		Double_t blind(const Double_t val) const { return val+offset_; }

		//! Obtain the unblinded value
		/*!
		    \param [in] val the blinded value
		    \return the unblinded value
		*/
		Double_t unblind(const Double_t val) const { return val-offset_; }

	private:

		//! Calculate the offset
		/*!
		    \param [in] blindingString the blinding string
		    \param [in] width the width of the Gaussian for sampling the offset
		*/
		void calcOffset(const TString blindingString, const Int_t width);

		//! The offset used to blind the value
		Double_t offset_;

};

#endif
