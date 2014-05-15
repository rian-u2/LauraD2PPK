
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRelBreitWignerRes.hh
    \brief File containing declaration of LauRelBreitWignerRes class.
*/

/*! \class LauRelBreitWignerRes
    \brief Class for defining the relativistic Breit-Wigner resonance model

    Class for defining the relativistic Breit-Wigner resonance model, which
    includes the use of Blatt-Weisskopf barrier factors.
*/

#ifndef LAU_REL_BREIT_WIGNER_RES
#define LAU_REL_BREIT_WIGNER_RES

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"


class LauRelBreitWignerRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauRelBreitWignerRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauRelBreitWignerRes();

		//! Initialise the model 
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::RelBW;}

		//! Set the form factor model and parameters
		/*!
			\param [in] resRadius the radius of the barrier for the resonance decay
			\param [in] parRadius the radius of the barrier for the parent decay
			\param [in] type the form-factor model
		*/
		virtual void setBarrierRadii(const Double_t resRadius, const Double_t parRadius, const LauAbsResonance::BarrierType type);

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

		//! Calculate the form factor for the resonance
		/*!
			\param [in] z particle momentum multipled by the barrier radius
			\return value of the form factor 
		*/
		Double_t calcFFactor(Double_t z);


	private:
		//! Momentum of the daughters in the resonance rest frame (at pole mass)
		Double_t q0_;
		//! Momentum of the bachelor in the resonance rest frame (at pole mass)
		Double_t p0_;
		//! Momentum of the bachelor in the parent rest frame (at pole mass)
		Double_t pstar0_;
		//! The resonance mass
		Double_t resMass_;
		//! Square of the resonance mass
		Double_t resMassSq_;
		//! The resonance width
		Double_t resWidth_;
		//! Sum of the two daughter masses
		Double_t mDaugSum_;
		//! Square of the sum of the two daughter masses
		Double_t mDaugSumSq_;
		//! Difference of the two daughter masses
		Double_t mDaugDiff_;
		//! Square of the difference of the two daughter masses
		Double_t mDaugDiffSq_;
		//! Square of the parent mass
		Double_t mParentSq_;
		//! Square of the bachelor mass
		Double_t mBachSq_;

		//! Value of the form factor for resonance decay (at pole mass)
		Double_t FR0_;
		//! Value of the form factor for parent decay (at pole mass)
		Double_t FB0_;

		ClassDef(LauRelBreitWignerRes,0) // Relativistic Breit-Wigner resonance model

};

#endif
