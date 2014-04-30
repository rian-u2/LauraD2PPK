
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleNR.hh
    \brief File containing declaration of LauBelleNR class.
*/

/*! \class LauBelleNR
    \brief Class for defining the Belle nonresonant model.

    Defines the nonresonant model from the Belle collaboration.
    arXiv:hep-ex/0412066
*/

#ifndef LAU_BELLE_NR
#define LAU_BELLE_NR

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;


class LauBelleNR : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resName the name of the resonance
			\param [in] resType the model of the resonance
			\param [in] resMass the mass of the resonance
			\param [in] resWidth the width of the resonance
			\param [in] resSpin the spin of the resonance
			\param [in] resCharge the charge of the resonance
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauBelleNR(const TString& resName, const LauAbsResonance::LauResonanceModel resType,
				LauParameter* resMass, LauParameter* resWidth,
				const Int_t resSpin, const Int_t resCharge,
				const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauBelleNR();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return model_;}

		//! Set value of the various parameters
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);

	protected:
		//! Set the parameter alpha, the effective range
		/*!
			\param [in] alpha the new effective range parameter value
		*/
		virtual void setAlpha(Double_t alpha) {alpha_ = alpha;}

		//! Get the effective range parameter
		/*!
			\return the effective range parameter
		*/
		virtual Double_t getAlpha() const {return alpha_;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! The range parameter
		Double_t alpha_;

		//! The model to use
		LauAbsResonance::LauResonanceModel model_;

		ClassDef(LauBelleNR,0) // Belle Non-resonant model
};

#endif
