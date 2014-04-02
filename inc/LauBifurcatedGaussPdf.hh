
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBifurcatedGaussPdf.hh
    \brief File containing declaration of LauBifurcatedGaussPdf class.
*/

/*! \class LauBifurcatedGaussPdf
    \brief Class for defining a bifurcated Gaussian PDF.

    Class that allows the user to define a bifurcated Gaussian PDF,
    a Gaussian that has different widths either side of the peak position.
*/

#ifndef LAU_BIFURCATED_GAUSS_PDF
#define LAU_BIFURCATED_GAUSS_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauBifurcatedGaussPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean, sigmaL and sigmaR
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauBifurcatedGaussPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauBifurcatedGaussPdf();

		//! Copy constructor
		LauBifurcatedGaussPdf(const LauBifurcatedGaussPdf& other);

		//! Calculate the likelihood (and intermediate info) for a given abscissa
		/*!
		    \param [in] abscissas the values of the abscissa(s)
		*/
		virtual void calcLikelihoodInfo(const LauAbscissas& abscissas);
		
		using LauAbsPdf::calcLikelihoodInfo;

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
		LauAbsRValue* mean_;

		//! Sigma of left Gaussian
		LauAbsRValue* sigmaL_;

		//! Sigma of right Gaussian
		LauAbsRValue* sigmaR_;

		ClassDef(LauBifurcatedGaussPdf,0) // Define the Bifurcated Gaussian PDF
};

#endif
