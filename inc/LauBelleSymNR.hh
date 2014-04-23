
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleSymNR.hh
    \brief File containing declaration of LauBelleSymNR class.
*/

/*! \class LauBelleSymNR
    \brief Class for defining the symmetric Belle Non Resonant model

    Defines the Non Resonant model from the Belle collaboration for the case 
    of a symmetrical DP
*/

#ifndef LAU_BELLE_SYM_NR
#define LAU_BELLE_SYM_NR

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;


class LauBelleSymNR : public LauAbsResonance {

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
		LauBelleSymNR(const TString& resName, Double_t resMass, Double_t resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);
		
		//! Destructor 
		virtual ~LauBelleSymNR();

		//! Initialise 
		virtual void initialise();

		//! Get the complex dynamical amplitude
		/*! 
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/
		virtual LauComplex amplitude(const LauKinematics* kinematics);

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::BelleNR;}

		//! Set value of the various parameters
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);

	protected:
		//! Set the parameter alpha, the effective range
		/*!
			\param [in] alpha the new effective range parameter
		*/
		virtual void setAlpha(Double_t alpha) {alpha_ = alpha;}

		//! Get the effective range parameter
		/*!
			\return the effective range parameter
		*/
		virtual Double_t getAlpha() {return alpha_;}

		//! This is not called, amplitude is used directly instead
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Define the range parameter
		Double_t alpha_;

		//! Tracks if initialise has been called
		Bool_t initialised_;

		//! Int to set the correct model type
		Int_t shapeNo_;

		ClassDef(LauBelleSymNR,0) // Belle Non-resonant model

};

#endif
