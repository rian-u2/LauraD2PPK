
// Copyright University of Warwick 2009 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauChebychevPdf.hh
    \brief File containing declaration of LauChebychevPdf class.
*/

/*! \class LauChebychevPdf
    \brief Class for defining a Chebychev Polynomial (1st kind) PDF.

    Class that allows the user to define a Chebychev Polynomial (1st kind) PDF.
    The guts of the implementation are from Gerhard Raven's RooFit class.
*/

/*****************************************************************************
 * Class based on RooFit/RooChebychev.                                       *
 * Original copyright given below.                                           *
 *****************************************************************************
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

#ifndef LAU_CHEBYCHEV_PDF
#define LAU_CHEBYCHEV_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;

class LauChebychevPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - the polynomial coefficients (polynomial can be anything from 0 to 7 orders).
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauChebychevPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauChebychevPdf();

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

	private:
		//! Copy constructor (not implemented)
		LauChebychevPdf(const LauChebychevPdf& other);

		//! Copy assignment operator (not implemented)
		LauChebychevPdf& operator=(const LauChebychevPdf& other);

		//! Coefficients of polynomial
		std::vector<LauAbsRValue*> coeffs_;

		ClassDef(LauChebychevPdf,0) // Chebychev PDF
};

#endif
