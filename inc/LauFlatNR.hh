
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFlatNR.hh
    \brief File containing declaration of LauFlatNR class.
*/

/*! \class LauFlatNR
    \brief Class for defining a uniform nonresonant amplitude
*/

#ifndef LAU_FLAT_NR
#define LAU_FLAT_NR

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"

class LauKinematics;


class LauFlatNR : public LauAbsResonance {

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
		LauFlatNR(TString resName, Double_t resMass, Double_t resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauFlatNR();

		//! Initialise the model
		virtual void initialise();

		//! Complex resonant amplitude
		/*!
			/param [in] kinematics kinematic parameters of the parent and daughter particles
			/return the complex amplitude
		*/	
		virtual LauComplex amplitude(const LauKinematics* kinematics);

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::FlatNR;}

	protected:
		//! This is not meant to be called
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:

		ClassDef(LauFlatNR,0) // Uniform non-resonant model
};

#endif
