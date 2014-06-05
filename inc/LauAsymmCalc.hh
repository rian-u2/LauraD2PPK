
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAsymmCalc.hh
    \brief File containing declaration of LauAsymmCalc class.
*/

/*! \class LauAsymmCalc
    \brief Class for calculating the asymmetry between two variables.
*/

#ifndef LAU_ASYMM_CALC
#define LAU_ASYMM_CALC

#include "Rtypes.h"


class LauAsymmCalc {

	public:
		//! Constructor
		/*!
		    \param [in] negValue the negative value
		    \param [in] posValue the positive value
		*/
		LauAsymmCalc(Double_t negValue, Double_t posValue);

		//! Destructor
		virtual ~LauAsymmCalc();

		//! Copy constructor
		LauAsymmCalc(const LauAsymmCalc& rhs);

		//! Copy assignment operator
		LauAsymmCalc& operator=(const LauAsymmCalc& rhs);

		//! Retrieve the asymmetry
		/*!
		    \return the asymmetry
		*/
		Double_t getAsymmetry() {return asymm_;}

	protected:
		//! Calculate the asymmetry
		/*!
		    \return the asymmetry
		*/
		Double_t calcAsymmetry();

	private:
		//! The negative value
		Double_t negValue_;

		//! The positive value
		Double_t posValue_;

		//! The asymmetry
		Double_t asymm_;

		ClassDef(LauAsymmCalc,0) // Calculate asymmetry between two variables
};

#endif
