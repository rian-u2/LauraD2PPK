
// Copyright University of Warwick 2008 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauLASSNRRes.hh
    \brief File containing declaration of LauLASSNRRes class.
*/

/*! \class LauLASSNRRes
    \brief Class for defining the non resonant part of the LASS model

    Class for defining the LASS resonance model, which includes a resonant
    part, plus an effective range term.  This class is the nonresonant part only.
*/

#ifndef LAU_LASS_NR_RES
#define LAU_LASS_NR_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauLASSNRRes : public LauAbsResonance {

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
		LauLASSNRRes(TString resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt, 
				const LauDaughters* daughters);

		//! Destructor
		virtual ~LauLASSNRRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::LASS_NR;}

		//! Get the effective range parameter
		/*!
			\return the effective range parameter
		*/
		virtual Double_t getEffectiveRange() {return r_;}
		//! Get the scattering length range parameter
		/*!
			\return the scattering length parameter
		*/
		virtual Double_t getScatteringLength() {return a_;}
		//! Get the background magnitude
		/*!
			\return the background magnitude
		*/
		virtual Double_t getBackgroundMag() {return B_;}
		//! Get the resonance magnitude
		/*!
			\return the resonance magnitude
		*/
		virtual Double_t getResonanceMag() {return R_;}
		//! Get the background phase
		/*!
			\return the backgorund phase
		*/
		virtual Double_t getBackgroundPhase() {return phiB_;}
		//! Get the resonance phase
		/*!
			\return the resonance phase
		*/
		virtual Double_t getResonancePhase() {return phiR_;}
		//! Get the cut off parameter
		/*!
			\return the cut off parameter
		*/
		virtual Double_t getCutOff() {return cutOff_;}

		//! Set the effective range parameter
		/*!
			\param [in] r the effective range parameter
		*/
		virtual void setEffectiveRange(Double_t r) {r_ = r;}
		//! Set the scattering length parameter
		/*!
			\param [in] a the scattering length parameter
		*/	
		virtual void setScatteringLength(Double_t a) {a_ = a;}
		//! Set the background magnitude
		/*!
			\param [in] B the background magnitude
		*/
		virtual void setBackgroundMag(Double_t B) {B_ = B;}
		//! Set the resonance magnitude
		/*!
			\param [in] R the resonance magnitude
		*/
		virtual void setResonanceMag(Double_t R) {R_ = R;}
		//! Set the background phase
		/*!
			\param [in] phiB the background phase
		*/	
		virtual void setBackgroundPhase(Double_t phiB) {phiB_ = phiB;}
		//! Set the resonance phase
		/*!
			\param [in] phiR the resonance phase
		*/	
		virtual void setResonancePhase(Double_t phiR) {phiR_ = phiR;}
		//! Set the cut off parameter
		/*!
			\param [in] cutOff the cut off parameter
		*/	
		virtual void setCutOff(Double_t cutOff) {cutOff_ = cutOff;}

		//! Set value of a resonance parameter
		/*! 
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/	
		virtual void setResonanceParameter(const TString& name, const Double_t value);

	protected:
		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/	
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Decay momentum of either daughter in the resonance rest frame
		//Double_t q0_;
		//! Sum of the daughter masses
		Double_t mDaugSum_; 
		//! Square of mDaugSum
		Double_t mDaugSumSq_;
		//! Difference between the daughter masses
		Double_t mDaugDiff_; 
		//! Square of mDaugDiff
		Double_t mDaugDiffSq_; 
		//! Square of the resonance mass
		//Double_t resMassSq_;
		//! LASS effective range parameter
		Double_t r_; 
		//! LASS scattering length parameter
		Double_t a_; 
		//! LASS background magnitude
		Double_t B_; 
		//! LASS resonance magnitude
		Double_t R_; 
		//! LASS background phase
		Double_t phiB_; 
		//! LASS resonance phase
		Double_t phiR_;
		//! LASS cut off parameter
		Double_t cutOff_;

		ClassDef(LauLASSNRRes,0) // LASS nonresonant model
};

#endif
