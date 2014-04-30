
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauLinearPdf.hh
    \brief File containing declaration of LauLinearPdf class.
*/

/*! \class LauLinearPdf
    \brief Class for defining a straight line PDF.

    Class that allows the user to define a straight line PDF.
*/

#ifndef LAU_LINEAR_PDF
#define LAU_LINEAR_PDF

#include <vector>

#include "TString.h"
#include "LauAbsPdf.hh"


class LauLinearPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameter - slope
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauLinearPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauLinearPdf();

		//! Copy constructor
		LauLinearPdf(const LauLinearPdf& other);

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
		//! Line slope
		LauAbsRValue* slope_;

		Bool_t posflag_;

		ClassDef(LauLinearPdf,0) // Define the Linear PDF
};

#endif
