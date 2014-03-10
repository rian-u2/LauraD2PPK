
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBreitWignerRes.hh
    \brief File containing declaration of LauBreitWignerRes class.
*/

/*! \class LauBreitWignerRes
    \brief Class for defining the simple Breit-Wigner resonance model

    Class for defining the simple Breit-Wigner resonance model.
    This is a non-relativistic Breit-Wigner, with no mass-dependent width or form factors.
*/

#ifndef LAU_BREIT_WIGNER_RES
#define LAU_BREIT_WIGNER_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauBreitWignerRes : public LauAbsResonance {

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
		LauBreitWignerRes(TString resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt, 
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauBreitWignerRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::BW;}

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		ClassDef(LauBreitWignerRes,0) // Breit-Wigner resonance model

};

#endif
