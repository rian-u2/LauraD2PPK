
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauArgusPdf.hh
    \brief File containing declaration of LauArgusPdf class.
*/

/*! \class LauArgusPdf
    \brief Class for defining an ARGUS PDF.

    Class that allows the user to define an ARGUS PDF:
    Phys. Lett. B 241, 278 (1990)
*/

#ifndef LAU_ARGUS_PDF
#define LAU_ARGUS_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauArgusPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the curve parameters - the shape, xi, and the end-point, m0, of the curve
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauArgusPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauArgusPdf();

		//i! Copy constructor
		LauArgusPdf(const LauArgusPdf& other);

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
		//! Shape of curve
		LauAbsRValue* xi_;

		//! Endpoint of curve
		LauAbsRValue* m0_;

		ClassDef(LauArgusPdf,0) // Define the ARGUS PDF
};

#endif
