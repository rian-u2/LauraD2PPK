
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauCruijffPdf.hh
    \brief File containing declaration of LauCruijffPdf class.
*/

/*! \class LauCruijffPdf
    \brief Class for defining a Cruijff PDF.

    Class that allows the user to define a Cruijff PDF, a bifurcated Gaussian with asymmetric tails.
    The guts of the implementation have been copied from Wouter Hulsbergen's RooFit class.
*/

/*****************************************************************************
 * Class based on RooFit/RooCruijff.                                         *
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

#ifndef LAU_CRUIJFF_PDF
#define LAU_CRUIJFF_PDF

#include "TString.h"
#include "TRandom.h"
#include "LauAbsPdf.hh"
#include "LauParameter.hh"

#include <vector>

using std::vector;

class LauCruijffPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean, sigmaR, sigmaL, alphaR and alphaL
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		*/
		LauCruijffPdf(const TString& theVarName, const vector<LauAbsRValue*>& params, Double_t minAbscissa, Double_t maxAbscissa);
		
		//! Destructor
		virtual ~LauCruijffPdf();

		//! Copy constructor
		LauCruijffPdf(const LauCruijffPdf& other);

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
		//! Sigma of left Gaussian
		LauAbsRValue* sigmaL_;
		//! Sigma of right Gaussian
		LauAbsRValue* sigmaR_;
		//! Alpha of left Gaussian
		LauAbsRValue* alphaL_;
		//! Alpha of right Gaussian
		LauAbsRValue* alphaR_;

		ClassDef(LauCruijffPdf,0) // Define the Cruijff PDF
};

#endif
