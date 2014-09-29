
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsIncohRes.hh
    \brief File containing declaration of LauAbsIncohRes class.
*/

/*! \class LauAbsIncohRes
    \brief Abstract class for defining incoherent resonant amplitude models
*/

#ifndef LAU_ABS_INCOH_RES
#define LAU_ABS_INCOH_RES

#include "TString.h"

#include "LauAbsResonance.hh"

class LauKinematics;


class LauAbsIncohRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauAbsIncohRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauAbsIncohRes();

		//! Get intensity factor
		/*!
			/param [in] kinematics kinematic parameters of the parent and daughter particles
			/return the intensity factor
		*/	
		virtual Double_t intensityFactor(const LauKinematics* kinematics)=0;

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Copy constructor (not implemented)
		LauAbsIncohRes(const LauAbsIncohRes& rhs);

		//! Copy assignment operator (not implemented)
		LauAbsIncohRes& operator=(const LauAbsIncohRes& rhs);

		ClassDef(LauAbsIncohRes,0) // Abstract incoherent resonance class
};

#endif
