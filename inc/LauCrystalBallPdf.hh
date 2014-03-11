
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauCrystalBallPdf.hh
    \brief File containing declaration of LauCrystalBallPdf class.
*/

/*! \class LauCrystalBallPdf
    \brief Class for defining a Crystal Ball PDF.

    Class that allows the user to define a Crystal Ball PDF, a Gaussian with power law tail on one side.
    The guts of the implementation have been copied from RooFit.
*/

/*****************************************************************************
 * Class based on RooFit/RooCBShape.                                         *
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

#ifndef LAU_CRYSTAL_BALL_PDF
#define LAU_CRYSTAL_BALL_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauCrystalBallPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean and sigma of the Gaussian, alpha (the distance from the mean in which the Gaussian and the tail are matched up), n (power for the tail)
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauCrystalBallPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);

		//! Destructor
		virtual ~LauCrystalBallPdf();

		//! Copy constructor
		LauCrystalBallPdf(const LauCrystalBallPdf& other);

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

		//! Calculate the approximate error function of argument
		/*!
		    \param [in] arg the argument for which to calculate the error function
		    \return error function of argument
		*/
		Double_t approxErf(Double_t arg) const;

	private:
		//! Gaussian mean
		LauAbsRValue* mean_;
		//! Gaussian sigma
		LauAbsRValue* sigma_;
		//! Alpha - distance from the mean in which the Gaussian and the tail are matched up
		LauAbsRValue* alpha_;
		//! Power for tail (goes as 1/x^n)
		LauAbsRValue* n_;

		ClassDef(LauCrystalBallPdf,0) // Define the Crystal Ball PDF
};

#endif
