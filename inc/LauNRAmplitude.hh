
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauNRAmplitude.hh
    \brief File containing declaration of LauNRAmplitude class.
*/

/*! \class LauNRAmplitude
    \brief Class for defining the NR amplitude model.

    Class for defining the NR amplitude model. 
    Formulae and data values from arXiv:0709.0075v1 [hep-ph].
*/

#ifndef LAU_NR_AMPLITUDE
#define LAU_NR_AMPLITUDE

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"

class LauKinematics;


class LauNRAmplitude : public LauAbsResonance {

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
		LauNRAmplitude(TString resName, Double_t resMass, Double_t resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauNRAmplitude();

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
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::NRModel;}

	protected:
		//! This is not meant to be called
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Evaluate the expression 1.0 / (1.0 + TMath::Exp( c * (s-p) ))
		/*!
			\param [in] s invariant mass squared
			\param [in] c parameter from arXiv:0709.0075v1 [hep-ph]
			\param [in] p parameter from arXiv:0709.0075v1 [hep-ph]
			\return the value of the expression 1.0 / (1.0 + TMath::Exp( c * (s-p) ))
		*/	
		virtual Double_t f(Double_t s, Double_t c, Double_t p) const;

	private:
		//! Parameter from arXiv:0709.0075v1 [hep-ph]
		Double_t d_; 
		//! Parameter from arXiv:0709.0075v1 [hep-ph]
		Double_t c1_; 
		//! Parameter from arXiv:0709.0075v1 [hep-ph]
		Double_t c2_; 
		//! Parameter from arXiv:0709.0075v1 [hep-ph]
		Double_t p1_; 
		//! Parameter from arXiv:0709.0075v1 [hep-ph]
		Double_t p2_;

		ClassDef(LauNRAmplitude,0) // Non-resonant amplitude model
};

#endif
