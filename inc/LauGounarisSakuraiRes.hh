
// Copyright University of Warwick 2006 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGounarisSakuraiRes.hh
    \brief File containing declaration of LauGounarisSakuraiRes class.
*/

/*! \class LauGounarisSakuraiRes
    \brief Class for defininf the Gounaris-Sakurai resonance model

    Class for defining the relativistic Gounaris-Sakurai resonance model, which
    includes the use of Blatt-Weisskopf barrier factors.
*/

#ifndef LAU_GOUNARIS_SAKURAI_RES
#define LAU_GOUNARIS_SAKURAI_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauGounarisSakuraiRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance 
			\param [in] daughters the daughter particles
		*/	
		LauGounarisSakuraiRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauGounarisSakuraiRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::GS;}

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
		//! Copy constructor (not implemented)
		LauGounarisSakuraiRes(const LauGounarisSakuraiRes& rhs);

		//! Copy assignment operator (not implemented)
		LauGounarisSakuraiRes& operator=(const LauGounarisSakuraiRes& rhs);

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
		//! Difference between the two daughter masses
		Double_t mDaugDiff_; 
		//! Square of the difference of the two daughter masses
		Double_t mDaugDiffSq_;
		//! Square of the parent mass
		Double_t mParentSq_; 
		//! Square of the bachelor mass
		Double_t mBachSq_;
		//! Extra parameter required by GS shape
		Double_t h0_; 
		//! Extra parameter required by GS shape
		Double_t dhdm0_; 
		//! Extra parameter required by GS shape
		Double_t d_;

		//! Radius of the barrier for resonance decay
		Double_t resR_; 
		//! Radius of the barrier for parent decay
		Double_t parR_;
		//! Square of the radius of the barrier for resonance decay
		Double_t resRSq_; 
		//! Square of the radius of the barrier for parent decay
		Double_t parRSq_; 
		//! Value of the form factor for resonance decay (at pole mass)
		Double_t FR0_; 
		//! Value of the form factor for parent decay (at pole mass)
		Double_t FB0_;
		//! Model to be used for the form factor
		LauAbsResonance::BarrierType barrierType_;

		ClassDef(LauGounarisSakuraiRes,0) // Gounaris-Sakurai resonance model

};

#endif
