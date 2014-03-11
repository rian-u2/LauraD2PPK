
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauParametricStepFuncPdf.hh
    \brief File containing declaration of LauParametricStepFuncPdf class.
*/

/*! \class LauParametricStepFuncPdf
    \brief Class for defining a Parametric Step Function PDF.

    Class that allows the user to define a Parametric Step Function PDF.
    Code mostly copied from RooFit/RooParametricStepFunction.
*/

/*****************************************************************************
 * Class based on RooFit/RooParametricStepFunction.                          *
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


#ifndef LAU_PAR_STEP_FUNC_PDF
#define LAU_PAR_STEP_FUNC_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"

class LauParameter;


class LauParametricStepFuncPdf : public LauAbsPdf {

	public:
		//! Define the allowed options for the normalisation bin
		enum NormBin {
			First, /*!< The height of the first bin is determined from the rest to satisfy the normalisation */
			Last   /*!< The height of the last bin is determined from the rest to satisfy the normalisation */
		};
		
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the bin contents of all the but the normalisation bin, so (N_bins - 1 entries)
		    \param [in] limits the limits of the bins (lower limit of all bins and upper limit of the last), so (N_bins + 1) entries
		    \param [in] normalisationBin the normalisation bin
		*/
		LauParametricStepFuncPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params, const std::vector<Double_t>& limits, NormBin normalisationBin = Last);

		//! Destructor
		virtual ~LauParametricStepFuncPdf();

		//! Copy constructor
		LauParametricStepFuncPdf(const LauParametricStepFuncPdf& other);

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
		//! Number of bins
		/*!
		    \return the number of bins
		*/
		UInt_t nBins() const {return limits_.size()-1;}

		//! Normalisation bin
		/*!
		    \return the normalisation bin
		*/
		NormBin normBin() const {return normBin_;}

	private:
		//! normalisation bin
		NormBin normBin_;
		//! limits of the bins
		std::vector<Double_t> limits_;

		ClassDef(LauParametricStepFuncPdf,0) // Define the PSF PDF
};

#endif
