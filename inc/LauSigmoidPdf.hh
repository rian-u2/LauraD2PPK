
// Copyright University of Warwick 2012 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSigmoidPdf.hh
    \brief File containing declaration of LauSigmoidPdf class.
*/

/*! \class LauSigmoidPdf
    \brief Class for defining a generalised sigmoid PDF.

    Class for defining a generalised sigmoid PDF:
    f(x) = 1 / ( 1 + e^(b - ax) )
    The standard sigmoid is obtained when a = 1 and b = 0.
*/


#ifndef LAU_SIGMOID_PDF
#define LAU_SIGMOID_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauSigmoidPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - a and b
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauSigmoidPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);
		
		//! Destructor
		virtual ~LauSigmoidPdf();

		//! Copy constructor
		LauSigmoidPdf(const LauSigmoidPdf& other);

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
		//! Parameter a
		LauAbsRValue* a_;
		//! Parameter b
		LauAbsRValue* b_;

		ClassDef(LauSigmoidPdf,0) // Define the Sigmoid PDF
};

#endif
