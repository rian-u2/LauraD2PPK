
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPoleRes.hh
    \brief File containing declaration of LauPoleRes class.
*/

/*! \class LauPoleRes
    \brief Class for defining the simple Breit-Wigner resonance model

    Class for defining the simple Breit-Wigner resonance model.
    This is a pole type resonance 1/((m_s)^2-m^2); m_s=m0-iw0, good to represent the sigma (f0(500)).
*/

#ifndef LAU_POLE_RES
#define LAU_POLE_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauPoleRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauPoleRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauPoleRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::POLE;}

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return floating parameters of the resonance
		*/
		virtual const std::vector<LauParameter*>& getFloatingParameters();

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Copy constructor (not implemented)
		LauPoleRes(const LauPoleRes& rhs);

		//! Copy assignment operator (not implemented)
		LauPoleRes& operator=(const LauPoleRes& rhs);

		ClassDef(LauPoleRes,0) // Pole resonance model

};

#endif
