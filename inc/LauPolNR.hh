
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPolNR.hh
    \brief File containing declaration of LauPolNR class.
*/

/*! \class LauPolNR
    \brief Class for defining the terms of Babar nonresonant model.

    Defines the nonresonant model from the Babar collaboration.
    arXiv:1201.5897
*/

#ifndef LAU_POL_NR
#define LAU_POL_NR

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;


class LauPolNR : public LauAbsResonance {

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
		LauPolNR(const TString& resName, Double_t resMass, Double_t resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauPolNR();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
		/*!
		    \return the resonance model type
		*/
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::PolNR;}

		//! Set the parameter omega, the offset parameter
		/*!
		    \param [in] omega the new offset parameter
		*/
		virtual void setOmega(const Double_t omega) {omega_ = omega;}

		//! Get the offset parameter
		/*!
		    \return the offset parameter
		*/
		virtual Double_t getOmega() const {return omega_;}

	protected:
		//! Complex resonant amplitude
		/*!
		    \param [in] mass appropriate invariant mass for the resonance
		    \param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! The offset parameter
		Double_t omega_;

		//! The order in the mass
		UInt_t order_;

		ClassDef(LauPolNR,0) // Polynomial Non-resonant model
};

#endif
