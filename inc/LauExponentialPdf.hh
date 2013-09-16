
// Copyright University of Warwick 2011 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauExponentialPdf.hh
    \brief File containing declaration of LauExponentialPdf class.
*/

/*! \class LauExponentialPdf
    \brief Class for defining an Exponential PDF 

    Class that allows the user to define an Exponential PDF, 
    requires a single parameter for the slope of the exponential:
    exp(slope*x)
*/

#ifndef LAU_EXPONENTIAL_PDF
#define LAU_EXPONENTIAL_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauExponentialPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - slope
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauExponentialPdf(const TString& theVarName, const std::vector<LauParameter*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauExponentialPdf();

		//! Copy constructor
		LauExponentialPdf(const LauExponentialPdf& other);

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
		//! Exponential slope ie exp(slope*x)
		LauParameter* slope_;

		ClassDef(LauExponentialPdf,0) // Define the Exponential PDF
};

#endif
