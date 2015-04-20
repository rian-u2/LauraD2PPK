
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWaveSymRealImag.hh
    \brief File containing declaration of LauModIndPartWaveSymRealImag class.
 */

/*! \class LauModIndPartWaveSymRealImag
    \brief Class for defining a model independent partial wave component where the amplitudes are parameterised in terms of real and imaginary parts

    This model uses splines to produce a partial wave from the values of the real and imaginary parts of the amplitude at a series of points in the phase space.
    The values at each point can be floated in the fit.
    This version is designed for use in symmetrised Dalitz-plots.
 */

#ifndef LAU_MODINDPARTWAVE_SYM_REALIMAG
#define LAU_MODINDPARTWAVE_SYM_REALIMAG

#include "LauComplex.hh"
#include "LauModIndPartWaveRealImag.hh"

class TSpline3;


class LauModIndPartWaveSymRealImag : public LauModIndPartWaveRealImag {

	public:
		//! Constructor
		/*!
		    \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
		    \param [in] resPairAmpInt the number of the daughter not produced by the resonance
		    \param [in] daughters the daughter particles
		 */
		LauModIndPartWaveSymRealImag(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauModIndPartWaveSymRealImag();

		//! Is the amplitude pre-symmetrised?
		/*!
		    \return kTRUE, indicating that the amplitude is already symmetrised
		*/
		virtual Bool_t preSymmetrised() const {return kTRUE;}

		//! Get the resonance model type
		/*!
		    \return the resonance model type
		 */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::MIPW_Sym_RealImag;}

		//! Calculate the complex amplitude 
		/*!
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/
		virtual LauComplex amplitude(const LauKinematics* kinematics);

	protected:
		//! Method to check that the supplied knot positions are valid
		/*!
		    \param [in] masses the mass values at which the knots are placed
		*/
		virtual std::set<Double_t> checkKnots(const std::set<Double_t>& masses);

	private:
		LauKinematics* kinematics_;

		ClassDef(LauModIndPartWaveSymRealImag,0) // model independent partial wave

};

#endif
