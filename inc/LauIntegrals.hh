
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauIntegrals.hh
    \brief File containing declaration of LauIntegrals class.
*/

/*! \class LauIntegrals
    \brief Class for performing numerical integration routines.

    Class for calculating the Gauss-Legendre or Gauss-Hermite weights
    required for numerical integration of DP and other PDFs.
*/

#ifndef LAU_INTEGRALS
#define LAU_INTEGRALS

#include <vector>

#include "Rtypes.h"


class LauIntegrals {

	public:
		//! Constructor
		/*!
		    \param [in] weightsPrecision the desired precision to which the weights should be calculated
		*/
		LauIntegrals(Double_t weightsPrecision = 1.0e-6);

		//! Destructor
		virtual ~LauIntegrals();

		//! Calculate the Gauss-Legendre weights
		/*!
		    \param [in] numPoints the number of points in the integration
		    \param [out] abscissas the values of the abscissa at each integration point
		    \param [out] weights the weight at each integration point
		*/
		void calcGaussLegendreWeights(const Int_t numPoints, std::vector<Double_t>& abscissas, std::vector<Double_t>& weights);

		//! Calculate the Gauss-Hermite weights
		/*!
		    \param [in] numPoints the number of points in the integration
		    \param [out] abscissas the values of the abscissa at each integration point
		    \param [out] weights the weight at each integration point
		*/
		void calcGaussHermiteWeights(const Int_t numPoints, std::vector<Double_t>& abscissas, std::vector<Double_t>& weights);

	private:
		//! The precision to which the weights should be calculated
		Double_t weightsPrecision_;

		ClassDef(LauIntegrals,0)
};

#endif
