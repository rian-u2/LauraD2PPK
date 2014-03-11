
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau1DHistPdf.hh
    \brief File containing declaration of Lau1DHistPdf class.
*/

/*! \class Lau1DHistPdf
    \brief Class for defining a 1D histogram PDF.

    Class for defining a 1D histogram PDF.
    Employs linear interpolation to get the PDF value based on how far away a
    point is from nearby bin centres.  The returned values are normalised to
    the total area.
*/

#ifndef LAU_1DHIST_PDF
#define LAU_1DHIST_PDF

#include "LauAbsPdf.hh"

class TH1;

class Lau1DHistPdf : public LauAbsPdf {

	public:
		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] hist the 1D histogram from which the PDF should be constructed
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		    \param [in] useInterpolation boolean flag to determine whether linear interpolation between bins should be used or simply the raw bin values
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors
		*/
		Lau1DHistPdf(const TString& theVarName, const TH1* hist, Double_t minAbscissa, Double_t maxAbscissa,
				Bool_t useInterpolation = kTRUE, Bool_t fluctuateBins = kFALSE);

		//! Destructor
		virtual ~Lau1DHistPdf();

		//! Copy constructor
		Lau1DHistPdf(const Lau1DHistPdf& other);

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
		    \param [in] kinematics the current DP kinematics (not strictly required in this case since PDF has no DP dependence)
		*/
		virtual void calcPDFHeight( const LauKinematics* kinematics );

	protected:
		//! Fluctuate the histogram bin contents in accorance with their errors
		void doBinFluctuation();

		//! Check the normalisation calculation
		void checkNormalisation();

		//! Get the bin content from the histogram
		/*!
		    \param [in] bin the bin number
		    \return the bin content
		*/
		Double_t getBinHistValue(Int_t bin) const;

		//! Perform the interpolation (unnormalised)
		/*!
		    \param [in] x the abscissa value
		    \return the unnormalised PDF value
		*/
		Double_t interpolate(Double_t x) const;

		//! Perform the interpolation and divide by the normalisation
		/*!
		    \param [in] x the abscissa value
		    \return the normalised PDF value
		*/
		Double_t interpolateNorm(Double_t x) const;

	private:
		//! The underlying histogram
		TH1* hist_;

		//! Control boolean for using the linear interpolation
		Bool_t useInterpolation_;
		//! Control boolean for performing the fluctuation of the histogram bin contents
		Bool_t fluctuateBins_;

		//! The number of bins in the histogram
		Int_t nBins_;
		//! The histogram axis minimum
		Double_t axisMin_;
		//! The histogram axis maximum
		Double_t axisMax_;
		//! The histogram axis range
		Double_t axisRange_;

		ClassDef(Lau1DHistPdf,0) // 1D histogram pdf class
};

#endif
