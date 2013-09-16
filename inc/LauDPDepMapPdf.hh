
// Copyright University of Warwick 2009 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDPDepMapPdf.hh
    \brief File containing declaration of LauDPDepMapPdf class.
*/

/*! \class LauDPDepMapPdf
    \brief Class to allow having different PDFs in different regions of the DP.

    Class to allow having different PDFs in different regions of the DP.
    The DP regions are specified in a 2D histogram or in a 1D histogram of some projection of the DP.
    Each PDF is then associated with that region.
*/


#ifndef LAU_DPDEPMAP_PDF
#define LAU_DPDEPMAP_PDF

#include <vector>

#include "Rtypes.h"

#include "LauAbsPdf.hh"

class LauDaughters;
class Lau2DHistDP;
class LauParameter;
class TH2;
class TH1;


class LauDPDepMapPdf : public LauAbsPdf {

	public:
		//! Define possibilties for the DP axes
		enum DPAxis {
			M12,		/*!< dependence is on m^2_12 */
			M13,		/*!< dependence is on m^2_13 */
			M23,		/*!< dependence is on m^2_23 */
			CentreDist,	/*!< dependence is on the distance from the DP centre */
			MMIN,		/*!< dependence is on the minimum of m^2_13 and m^2_23 */
			MMAX		/*!< dependence is on the maximum of m^2_13 and m^2_23 */
		};

		//! Constructor - map described by 2D histogram
		/*!
		    \param [in] pdfs the PDFs 
		    \param [in] daughters the daughter particles
		    \param [in] dpHisto the 2D histogram
		    \param [in] upperHalf specifies whether only upper half of DP is supplied in the case of a symmetric DP
		*/
		LauDPDepMapPdf( const std::vector<LauAbsPdf*> &pdfs,
				const LauDaughters* daughters,
				const TH2* dpHisto, Bool_t upperHalf = kFALSE);

		//! Constructor - map described by 1D histogram of a DP "axis"
		/*!
		    \param [in] pdfs the PDFs
		    \param [in] daughters the daughter particles
		    \param [in] dpAxisHisto the 1D histogram 
		    \param [in] dpAxis the DP axis
		*/
		LauDPDepMapPdf( const std::vector<LauAbsPdf*> &pdfs,
				const LauDaughters* daughters,
				const TH1* dpAxisHisto,
				DPAxis dpAxis);

		//! Destructor
		virtual ~LauDPDepMapPdf();

		//! Copy constructor
		LauDPDepMapPdf(const LauDPDepMapPdf& other);

		//! Specifies whether or not the PDF is DP dependent.
		/*!
		    \return true if the PDF is DP-dependent (the default)
		*/
		virtual Bool_t isDPDependent() const {return kTRUE;}

		//! Cache information from data
		/*!
		    \param [in] inputData the input data 
		*/
		virtual void cacheInfo(const LauFitDataTree& inputData);

		//! Calculate the likelihood (and intermediate info) for a given abscissa
		/*!
		    \param [in] abscissas the values of the abscissa(s)
		*/
		virtual void calcLikelihoodInfo(const LauAbscissas& abscissas);
		
		//! Calculate the likelihood (and intermediate info) for a given event number
		/*!
		    \param [in] iEvt event number
		*/
		virtual void calcLikelihoodInfo(UInt_t iEvt);

		//! Check that PDF is positive
		virtual void checkPositiveness(); // Nothing to check here.

		//! Calculate the normalisation
		virtual void calcNorm();
		
		//! Calculate the PDF height
		/*!
		    \param [in] kinematics the current DP kinematics
		*/
		virtual void calcPDFHeight( const LauKinematics* kinematics );

	protected:
		//! Determine the DP region
		/*!
		    \param [in] m13Sq the invariant mass squared of daughters 1 and 3
		    \param [in] m23Sq the invariant mass squared of daughters 2 and 3
		*/
		UInt_t determineDPRegion( Double_t m13Sq, Double_t m23Sq ) const;

	private:
		//! Daughter particles
		LauDaughters* daughters_;

		//! The PDFs
		std::vector<LauAbsPdf*> pdfs_;

		//! 2D histogram - DP
		Lau2DHistDP* dpDependence_;
		//! 1D histogram - DP axis
		TH1* dpAxisDependence_;

		//! The DP axis we depend on
		DPAxis dpAxis_;

		//! Cached indices values
		std::vector<UInt_t> indices_;

		ClassDef(LauDPDepMapPdf,0) // Define the sum PDF
};

#endif
