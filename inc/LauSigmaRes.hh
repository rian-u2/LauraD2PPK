
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauSigmaRes.hh
    \brief File containing declaration of LauSigmaRes class.
*/

/*! \class LauSigmaRes
    \brief Class for defining the Sigma resonance model

    Class for defining the Sigma resonance model. Formulae and data values from
    Phys.Lett.B 572, 1 (2003) - author D.V.Bugg
*/

#ifndef LAU_SIGMA_RES
#define LAU_SIGMA_RES

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"


class LauSigmaRes : public LauAbsResonance {

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
		LauSigmaRes(TString resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt,
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauSigmaRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Sigma;}

		//! Set the parameter values
		/*!
			\param [in] b1 factor from BES data
			\param [in] b2 factor from BES data
			\param [in] A factor from BES data
			\param [in] m0 factor from BES data
		*/
		void setConstants(Double_t b1, Double_t b2, Double_t A, Double_t m0);

	protected:
		//! Complex resonant ampltiude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/	
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Check that both daughters are the same type of particle
		void checkDaughterTypes() const;

	private:
		//! Defined as 4*mPi*mPi
		Double_t mPiSq4_;
		//! Defined as 0.5*mPi*mPi
		Double_t sAdler_; 
		//! Factor from BES data
		Double_t b1_; 
		//! Factor from BES data
		Double_t b2_; 
		//! Factor from BES data
		Double_t A_; 
		//! Factor from BES data
		Double_t m0_; 
		//! Defined as m0 squared
		Double_t m0Sq_; 
		//! Defined as m0Sq - sAdler
		Double_t denom_;

		ClassDef(LauSigmaRes,0) // Sigma resonance model

};

#endif
