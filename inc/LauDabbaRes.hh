
// Copyright University of Warwick 2010 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDabbaRes.hh
    \brief File containing declaration of LauDabbaRes class.
*/

/*! \class LauDabbaRes
    \brief Class for defining the Dabba resonance model

    Class for defining the Dabba resonance model
    Formulae and data values from arXiv:0901.2217 - author D.V.Bugg
*/

#ifndef LAU_DABBA_RES
#define LAU_DABBA_RES

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"


class LauDabbaRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resName the name of the resonance
			\param [in] resMass the mass of the resonance
			\param [in] resWidth the width of the resonance
			\param [in] resSpin the spin of the resonance
			\param [in] resCharge the charge of the resonance
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/	
		LauDabbaRes(TString resName, Double_t resMass, Double_t resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauDabbaRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Dabba;}

		//! Set value of the various parameters
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);

	protected:
		//! Set the parameter values
		/*!
			\param [in] b constant factor
			\param [in] alpha constant factor
			\param [in] beta constant factor
		*/	
		void setConstants(Double_t b, Double_t alpha, Double_t beta);

		//! Set the b parameter
		/*!
			\param [in] b new value for b parameter
		*/
		void setBValue(const Double_t b) { b_ = b; }

		//! Set the alpha parameter
		/*!
			\param [in] alpha new value for alpha parameter
		*/
		void setAlphaValue(const Double_t alpha) { alpha_ = alpha; }

		//! Set the beta parameter
		/*!
			\param [in] beta new value for beta parameter
		*/
		void setBetaValue(const Double_t beta) { beta_ = beta; }

		//! Get the b parameter value
		/*!
			\return value of the b parameter
		*/
		Double_t getBValue() const { return b_; }

		//! Get the alpha parameter value
		/*!
			\return value of the alpha parameter
		*/
		Double_t getAlphaValue() const { return alpha_; }

		//! Get the beta parameter value
		/*!
			\return value of the beta parameter
		*/
		Double_t getBetaValue() const { return beta_; }

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/	
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Check that the daughter particles are D and pi
		void checkDaughterTypes() const;

	private:
		//! Defined as mD + mPi all squared
		Double_t mSumSq_; 
		//! Defined as mD*mD - 0.5*mPi*mPi
		Double_t sAdler_;
		//! Constant factor
		Double_t b_; 
		//! Constant factor
		Double_t alpha_; 
		//! Constant factor
		Double_t beta_;

		ClassDef(LauDabbaRes,0) // Dabba resonance model

};

#endif
