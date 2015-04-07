
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWaveRealImag.hh
    \brief File containing declaration of LauModIndPartWaveRealImag class.
 */

/*! \class LauModIndPartWaveRealImag
    \brief Class for defining a model independent partial wave component where the amplitudes are parameterised in terms of real and imaginary parts

    This model uses splines to produce a partial wave from the values of the real and imaginary parts of the amplitude at a series of points in the phase space.
    The values at each point can be floated in the fit.
 */

#ifndef LAU_MODINDPARTWAVE_REALIMAG
#define LAU_MODINDPARTWAVE_REALIMAG

#include "LauComplex.hh"
#include "LauAbsModIndPartWave.hh"

class TSpline3;


class LauModIndPartWaveRealImag : public LauAbsModIndPartWave {

	public:
		//! Constructor
		/*!
		    \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
		    \param [in] resPairAmpInt the number of the daughter not produced by the resonance
		    \param [in] daughters the daughter particles
		 */
		LauModIndPartWaveRealImag(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauModIndPartWaveRealImag();

		//! Set the values of the two real parameters that define the amplitude at a given knot
		/*!
		    \param [in] knot the knot to be updated
		    \param [in] realVal the value of the real part at the knot
		    \param [in] imagVal the value of the imaginary part at the knot
		    \param [in] fixRealPart whether the real part should be fixed
		    \param [in] fixImagPart whether the imaginary part should be fixed
		*/
		virtual void setKnotAmp(const UInt_t knot, const Double_t realVal, const Double_t imagVal, const Bool_t fixRealPart, const Bool_t fixImagPart);

		//! Get the resonance model type
		/*!
		    \return the resonance model type
		 */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::MIPW_RealImag;}

	protected:
		//! Evaluate the amplitude at the given point from the splines
		/*!
		    \param [in] mass appropriate invariant mass for the resonance
		*/
		virtual void evaluateAmplitude(const Double_t mass);

		//! Method to create the parameter objects for the given knot
		/*!
		    \param [in] iKnot the index of the knot
		*/
		virtual void createAmpParameters(const UInt_t iKnot);

	private:
		ClassDef(LauModIndPartWaveRealImag,0) // model independent partial wave

};

#endif
