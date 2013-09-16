
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGaussPdf.hh
    \brief File containing declaration of LauGaussPdf class.
*/

/*! \class LauGaussPdf
    \brief Class for defining a Gaussian PDF.

    Class that allows the user to define a Gaussian PDF.
*/

#ifndef LAU_GAUSS_PDF
#define LAU_GAUSS_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauGaussPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean, sigma
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauGaussPdf(const TString& theVarName, const std::vector<LauParameter*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauGaussPdf();

		//! Copy constructor
		LauGaussPdf(const LauGaussPdf& other);

		//! Calculate the likelihood (and intermediate info) for a given abscissa
		/*!
		    \param [in] abscissas the values of the abscissa(s)
		*/
		virtual void calcLikelihoodInfo(const LauAbscissas& abscissas);
		
		using LauAbsPdf::calcLikelihoodInfo;

		//! Check that PDF is positive
		virtual void checkPositiveness() {}; // Nothing to check here.

		//! Calculate the normalisation
		virtual void calcNorm();
		
		//! Calculate the PDF height
		/*!
		    \param [in] kinematics the current DP kinematics
		*/
		virtual void calcPDFHeight( const LauKinematics* kinematics );

	protected:

	private:
		//! Gaussian mean
		LauParameter* mean_;
		//! Gaussian sigma
		LauParameter* sigma_;

		ClassDef(LauGaussPdf,0) // Define the Gaussian PDF
};

#endif
