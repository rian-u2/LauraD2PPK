
// Copyright University of Warwick 2007 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDPDepBifurGaussPdf.hh
    \brief File containing declaration of LauDPDepBifurGaussPdf class.
*/

/*! \class LauDPDepBifurGaussPdf
    \brief Class for defining a Bifurcated Gaussian PDF (DP dependent).

    Class that allows the user to define a Bifurcated Gaussian PDF where one or more of the parameters have a dependence on the DP position.
*/

#ifndef LAU_DPDEP_BIFURGAUSS_PDF
#define LAU_DPDEP_BIFURGAUSS_PDF

#include <vector>

#include "TString.h"

#include "LauAbsPdf.hh"


class LauDPDepBifurGaussPdf : public LauAbsPdf {

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

		//! Define possibilties for the scaling method
 		enum ScaleMethod {
			poly,		/*!< dependence is polynomial */
			polyNegPower	/*!< dependence is a Laurent polynomial with only negative powers */
		};

		//! Constructor
		/*!
		    \param [in] theVarName the name of the abscissa variable
		    \param [in] params the PDF parameters - mean and sigma
		    \param [in] minAbscissa the minimum value of the abscissa
		    \param [in] maxAbscissa the maximum value of the abscissa
		    \param [in] daughters the daughter particles
		    \param [in] meanCoeffs the coefficients of the DP dependence of the Gaussian mean
		    \param [in] sigmaLCoeffs the coefficients of the DP dependence of the sigma for the left Gaussian
		    \param [in] sigmaRCoeffs the coefficients of the DP dependence of the sigma for the right Gaussian
		    \param [in] dpAxis the DP axis that defines the parameter dependence
		*/
		LauDPDepBifurGaussPdf(const TString& theVarName, const std::vector<LauAbsRValue*>& params,
				Double_t minAbscissa, Double_t maxAbscissa,
				const LauDaughters* daughters,
				const std::vector<Double_t>& meanCoeffs,
				const std::vector<Double_t>& sigmaLCoeffs,
				const std::vector<Double_t>& sigmaRCoeffs,
				DPAxis dpAxis);

		//! Destructor
		virtual ~LauDPDepBifurGaussPdf();

		//! Copy constructor
		LauDPDepBifurGaussPdf(const LauDPDepBifurGaussPdf& other);

		//! Specifies whether or not the PDF is DP dependent.
		/*!
		    \return true if the PDF is DP-dependent (the default)
		*/
		virtual Bool_t isDPDependent() const {return kTRUE;}

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
		
		//! Retrieve scaling method information
		/*!
		    \return scaling method
		*/
		ScaleMethod scaleMethod() const {return scaleMethod_;}
		
		//! Set the scaling method
		/*!
		    \param [in] method the scaling method
		*/
                void scaleMethod(ScaleMethod method) {scaleMethod_ = method;}
						
	protected:
		//! Scale the Gaussian parameters with polynomial method
		/*!
		    \param [in] perEventDist the event distribution
		*/
		void scalePars_poly(Double_t perEventDist);
		
		//! Scale the Gaussian parameters with negative power polynomial method
		/*!
		    \param [in] perEventDist the event distribution
		*/
		void scalePars_polyNegPower(Double_t perEventDist);
		
	private:
		//! The current DP kinematics
		const LauKinematics* kinematics_;

		//! Gaussian mean
		LauAbsRValue* mean_;
		//! Left Gaussian sigma
		LauAbsRValue* sigmaL_;
		//! Right Gaussian sigma
		LauAbsRValue* sigmaR_;

		//! Gaussian mean
		Double_t meanVal_;
		//! Left Gaussian sigma
		Double_t sigmaLVal_;
		//! Right Gaussian sigma
		Double_t sigmaRVal_;

		//! Coefficients of Gaussian mean
		const std::vector<Double_t> meanCoeffs_;
		//! Coefficients of left Gaussian sigma
		const std::vector<Double_t> sigmaLCoeffs_;
		//! Coefficients of right Gaussian sigma
		const std::vector<Double_t> sigmaRCoeffs_;

		//! The DP axis we depend on
		DPAxis dpAxis_;

		//! Scaling method information
		ScaleMethod scaleMethod_;

		ClassDef(LauDPDepBifurGaussPdf,0) // Define the MVA PDF
};

#endif
