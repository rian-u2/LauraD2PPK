
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauNovosibirskPdf.hh
    \brief File containing declaration of LauNovosibirskPdf class.
*/

/*! \class LauNovosibirskPdf
    \brief Class for defining a Novosibirsk function PDF.

    Class that allows the user to define a Novosibirsk function PDF.
*/

#ifndef LAU_NOVOSIBIRSK_PDF
#define LAU_NOVOSIBIRSK_PDF

#include "TString.h"
#include "TRandom.h"
#include "LauAbsPdf.hh"
#include "LauParameter.hh"

#include <vector>

using std::vector;

class LauNovosibirskPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean, sigma and tail
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauNovosibirskPdf(const TString& theVarName, const vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauNovosibirskPdf();

		//! Copy constructor
		LauNovosibirskPdf(const LauNovosibirskPdf& other);

		//! Calculate the likelihood (and intermediate info) for a given abscissa
		/*!
		    \param [in] abscissas the values of the abscissa(s)
		*/
		virtual void calcLikelihoodInfo(const LauAbscissas& abscissas);
		
		using LauAbsPdf::calcLikelihoodInfo;

		//! Calculate the PDF height
		/*!
		    \param [in] kinematics the current DP kinematics
		*/
		virtual void calcPDFHeight( const LauKinematics* kinematics );

	protected:

	private:
		//! Gaussian mean
		LauAbsRValue* mean_;
		//! Gaussian sigma
		LauAbsRValue* sigma_;
		//! Gaussian tail
		LauAbsRValue* tail_;

		ClassDef(LauNovosibirskPdf,0) // Define the Novosibirsk PDF
};

#endif
