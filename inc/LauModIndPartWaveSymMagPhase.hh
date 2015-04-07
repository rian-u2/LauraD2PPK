
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWaveSymMagPhase.hh
    \brief File containing declaration of LauModIndPartWaveSymMagPhase class.
 */

/*! \class LauModIndPartWaveSymMagPhase
    \brief Class for defining a model independent partial wave component where the amplitudes are parameterised in terms of magnitude and phase

    This model uses splines to produce a partial wave from the magnitude and phase values of the amplitude at a series of points in the phase space.
    The magnitude and phase at each point can be floated in the fit.
    This version is designed for use in symmetrised Dalitz-plots.
 */

#ifndef LAU_MODINDPARTWAVE_SYM_MAGPHASE
#define LAU_MODINDPARTWAVE_SYM_MAGPHASE

#include "LauComplex.hh"
#include "LauModIndPartWaveMagPhase.hh"

class TSpline3;


class LauModIndPartWaveSymMagPhase : public LauModIndPartWaveMagPhase {

	public:
		//! Constructor
		/*!
		    \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
		    \param [in] resPairAmpInt the number of the daughter not produced by the resonance
		    \param [in] daughters the daughter particles
		 */
		LauModIndPartWaveSymMagPhase(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauModIndPartWaveSymMagPhase();

		//! Is the amplitude pre-symmetrised?
		/*!
		    \return kTRUE, indicating that the amplitude is already symmetrised
		*/
		virtual Bool_t preSymmetrised() const {return kTRUE;}

		//! Get the resonance model type
		/*!
		    \return the resonance model type
		 */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::MIPW_Sym_MagPhase;}

		//! Calculate the complex amplitude 
		/*!
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/
		virtual LauComplex amplitude(const LauKinematics* kinematics);

	private:
		LauKinematics* kinematics_;

		ClassDef(LauModIndPartWaveSymMagPhase,0) // model independent partial wave

};

#endif
