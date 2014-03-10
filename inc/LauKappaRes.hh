
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKappaRes.hh
    \brief File containing declaration of LauKappaRes class.
*/

/*! \class LauKappaRes
    \brief Class for defining the Kappa resonance model

    Class for defining the Kappa resonance model.
    Formulae and data values from
    Phys.Lett.B 572, 1 (2003) - author D.V.Bugg
*/

#ifndef LAU_KAPPA_RES
#define LAU_KAPPA_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauKappaRes : public LauAbsResonance {

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
		LauKappaRes(TString resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauKappaRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Kappa;}

		//! Set the parameter values
		/*!
			\param [in] b1 factor from BES data
			\param [in] b2 factor from BES data
			\param [in] A factor from BES data
			\param [in] m0 factor from BES data
		*/
		void setConstants(Double_t b1, Double_t b2, Double_t A, Double_t m0);

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Check that Kappa daughters are K and pi
		void checkDaughterTypes() const;

	private:
		//! Define m mSum as mK + mPi
		Double_t mSum_; 
		//! Square of mSum
		Double_t mSumSq_; 
		//! Defined as mK*mK - 0.5*mPi*mPi
		Double_t sAdler_;
		//! Factor from BES data
		Double_t b1_; 
		//! Factor from BES data
		Double_t b2_; 
		//! Factor from BES data
		Double_t A_; 
		//! Factor from BES data
		Double_t m0_; 
		//! Square of m0
		Double_t m0Sq_; 
		//! Defined as m0Sq - sAdler
		Double_t denom_;

		ClassDef(LauKappaRes,0) // Kappa resonance model

};

#endif
