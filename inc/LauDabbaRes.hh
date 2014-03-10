
// Copyright University of Warwick 2010 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauDabbaRes.hh
    \brief File containing declaration of LauDabbaRes class.
*/

/*! \class LauDabbaRes
    \brief Class for defining the Dabba resonance model

    Class for defining the Dabba resonance model
    Formulae and data values from arXiv:0901.2217 - author D.V.Bugg
*/

#ifndef LAU_DABBA_RES
#define LAU_DABBA_RES

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"


class LauDabbaRes : public LauAbsResonance {

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
		LauDabbaRes(TString resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauDabbaRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Dabba;}

		//! Set the parameter values
		/*!
			\param [in] b constant factor
			\param [in] alpha constant factor
			\param [in] beta constant factor
		*/	
		void setConstants(Double_t b, Double_t alpha, Double_t beta);

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/	
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Check that the daughter particles are D and pi
		void checkDaughterTypes() const;

	private:
		//! Defined as mD + mPi all squared
		Double_t mSumSq_; 
		//! Defined as mD*mD - 0.5*mPi*mPi
		Double_t sAdler_;
		//! Constant factor
		Double_t b_; 
		//! Constant factor
		Double_t alpha_; 
		//! Constant factor
		Double_t beta_;

		ClassDef(LauDabbaRes,0) // Dabba resonance model

};

#endif
