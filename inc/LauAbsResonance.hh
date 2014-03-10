
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsResonance.hh
    \brief File containing declaration of LauAbsResonance class.
*/

/*! \class LauAbsResonance
    \brief Abstract class for defining type for resonance amplitude models (Breit-Wigner, Flatte etc.)

    Abstract Class for defining the type for all classes used to model
    resonances in the Dalitz plot, such as Breit-Wigner functions.
    In addition, some common functionality is implemented, including data such
    as the mass and width of the desired state.
*/

#ifndef LAU_ABS_RESONANCE
#define LAU_ABS_RESONANCE

#include "TString.h"

#include "LauComplex.hh"
#include "LauParameter.hh"

class LauDaughters;
class LauKinematics;

class LauAbsResonance {

	public:
		//! Define the allowed resonance types
		enum LauResonanceModel {
			BW,		/*!< simple Breit-Wigner */
			RelBW,		/*!< relativistic Breit-Wigner */
			GS,		/*!< a modified Breit-Wigner from Gounaris-Sakurai */
			Flatte,		/*!< Flatte or coupled-channel Breit-Wigner */
			Sigma,		/*!< special shape for the sigma or f_0(600) */
			Kappa,		/*!< special shape for the kappa, a low-mass Kpi scalar */
			Dabba,		/*!< special shape for the dabba, a low-mass Dpi scalar */
			LASS,		/*!< the LASS amplitude to describe the Kpi S-wave */
			LASS_BW,	/*!< the resonant part of the LASS amplitude */
			LASS_NR,	/*!< the nonresonant part of the LASS amplitude */
			KMatrix,	/*!< S-wave description using K-matrix and P-vector */
			FlatNR,		/*!< a uniform nonresonant amplitude */
			NRModel,	/*!< a theoretical model nonresonant amplitude */
			BelleNR,	/*!< an empirical exponential nonresonant amplitude */
			PolNR		/*!< an empirical polynomial nonresonant amplitude */
		};

		//! Define the allowed types of barrier factors 
		enum BarrierType {
			BWBarrier,	/*!< Blatt-Weisskopf barrier factor (for use when momentum terms not used in angular term) */
			BWPrimeBarrier,	/*!< Blatt-Weisskopf barrier factor (for use when momentum terms are used in angular term) - the default */
			ExpBarrier	/*!< expoential barrier factor (mostly used for virtual contributions) */
		};

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
		LauAbsResonance(const TString& resName, LauParameter* resMass, LauParameter* resWidth,
				Int_t resSpin, Int_t resCharge, Int_t resPairAmpInt, 
				const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauAbsResonance();

		//! Initialise the model 
		virtual void initialise() = 0;

		//! Calculate the complex amplitude 
		/*!
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/
		virtual LauComplex amplitude(const LauKinematics* kinematics);

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauResonanceModel getResonanceModel() const = 0;

		//! Get the name of the resonance
		/*! 
			\return the resonance name
		*/
		const TString& getResonanceName() const {return resName_;}

		//! Get the integer to identify which DP axis the resonance belongs to
		/*! 
			\return the DP axis identification number, the ID of the bachelor
		*/
		Int_t getPairInt() const {return resPairAmpInt_;}

		//! Get the spin of the resonance
		/*! 
			\return the resonance spin
		*/
		Int_t getSpin() const {return resSpin_;}

		//! Get the charge of the resonance
		/*! 
			\return the resonance charge
		*/
		Int_t getCharge() const {return resCharge_;}

		//! Get the mass of the resonance
		/*! 
			\return the resonance mass
		*/
		Double_t getMass() const {return (resMass_!=0) ? resMass_->value() : -1.0;}

		//! Get the width of the resonance
		/*! 
			\return the resonance width
		*/
		Double_t getWidth() const {return (resWidth_!=0) ? resWidth_->value() : -1.0;}

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return parameters of the resonance
		*/
		const std::vector<LauParameter*>& getParameters() const {return resParameters_;}

		//! Get the helicity flip flag
		/*! 
			\return the flip helicity flag
		*/
		Bool_t flipHelicity() const {return flipHelicity_;}

		//! Set the helicity flip flag
		/*!
			\param [in] boolean the helicity flip status
		*/
		void flipHelicity(Bool_t boolean) {flipHelicity_ = boolean;}
	
		//! Get the ignore momenta flag
		/*! 
			\return the ignore momenta flag
		*/
		Bool_t ignoreMomenta() const {return ignoreMomenta_;}

  //! Set the ignore p_ and q_ flag
		/*!
			\param [in] boolean the ignore momenta status
		*/
		void ignoreMomenta(Bool_t boolean) {ignoreMomenta_ = boolean;}

		//! Allow the mass, width and spin of the resonance to be changed
		/*!
			\param [in] newMass new value of the resonance mass 
			\param [in] newWidth new value of the resonance width
			\param [in] newSpin new value of the resonance spin 
		*/
		void changeResonance(Double_t newMass, Double_t newWidth, Int_t newSpin);

		//! Set the updated parameters from changeResonance 
		/*!
			\param [in] value the updated parameter value
			\param [in] name the updated parameter name
		*/
		virtual void setResonanceParameter(Double_t value, const TString& name);

		//! Fix or release the resonance mass
		/*!
			\param [in] parFixed new status of mass
		*/
		void fixMass(Bool_t parFixed) { if (resMass_!=0) { resMass_->fixed(parFixed); } }

		//! Fix or release the resonance width
		/*!
			\param [in] parFixed new status of width
		*/
		void fixWidth(Bool_t parFixed) { if (resWidth_!=0) { resWidth_->fixed(parFixed); } }

		//! Get the status of resonance mass (fixed or released)
		/*!
			\return the status of resonance mass (fixed or released)
		*/
		Bool_t fixMass() const { return (resMass_!=0) ? resMass_->fixed() : kTRUE; }

		//! Get the status of resonance width (fixed or released)
		/*!
			\return the status of resonance width (fixed or released)
		*/
		Bool_t fixWidth() const { return (resWidth_!=0) ? resWidth_->fixed() : kTRUE; }

	protected:
		//! Get the name of the parent particle
		TString getNameParent() const;
		//! Get the name of the first daughter of the resonance
		TString getNameDaug1() const;
		//! Get the name of the second daughter of the resonance
		TString getNameDaug2() const;
		//! Get the name of the daughter that does not originate form the resonance
		TString getNameBachelor() const;
		//! Get the parent particle mass
		Double_t getMassParent() const;
		//! Get the mass of daughter 1
		Double_t getMassDaug1() const;
		//! Get the mass of daughter 2
		Double_t getMassDaug2() const;
		//! Get the mass of the bachelor daughter
		Double_t getMassBachelor() const;
		//! Get the Charge of the parent particle
		Int_t getChargeParent() const;
		//! Get the charge of daughter 1
		Int_t getChargeDaug1() const;
		//! Get the charge of daughter 2
		Int_t getChargeDaug2() const;
		//! Get the charge of the bachelor daughter
		Int_t getChargeBachelor() const;

		//! Get the current value of the daughter momentum in the resonance rest frame
		Double_t getQ() const {return q_;}
		//! Get the current value of the bachelor momentum in the resonance rest frame
		Double_t getP() const {return p_;}
		//! Get the current value of the bachelor momentum in the parent rest frame
		Double_t getPstar() const {return pstar_;}

		//! Access the daughters object
		const LauDaughters* getDaughters() const {return daughters_;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm) = 0;

	private:
		//! Information on the particles
		const LauDaughters* daughters_;

		//! Parent name
		TString nameParent_; 
		//! Daughter 1 name
		TString nameDaug1_;
		//! Daughter 2 name
		TString nameDaug2_;
		//! Bachelor name
		TString nameBachelor_;

		//! Parent charge
		Int_t chargeParent_;
		//! Daughter 1 charge
		Int_t chargeDaug1_; 
		//! Daughter 2 charge
		Int_t chargeDaug2_; 
		//! Bachelor charge
		Int_t chargeBachelor_;

		//! Parent mass
		Double_t massParent_; 
		//! Daughter 1 mass
		Double_t massDaug1_; 
		//! Daughter 2 mass 
		Double_t massDaug2_; 
		// Bachelor mass
		Double_t massBachelor_;

		//! Resonance name
		TString resName_;

		//! Resonance mass 
		LauParameter* resMass_; 
		//! Resonance width
		LauParameter* resWidth_;

		//! All parameters of the resonance
		std::vector<LauParameter*> resParameters_;

		//! Resonance spin
		Int_t resSpin_; 
		//! Resonance charge
		Int_t resCharge_; 
		//! DP axis identifier
		Int_t resPairAmpInt_;

		//! Boolean to flip helicity
		Bool_t flipHelicity_;
		//! Boolean to ignore q_ and p_ in spinTerm
		Bool_t ignoreMomenta_;

		//! Daughter momentum in resonance rest frame
		Double_t q_;
		//! Bachelor momentum in resonance rest frame
		Double_t p_;
		//! Bachelor momentum in parent rest frame
		Double_t pstar_;

		ClassDef(LauAbsResonance,0) // Abstract resonance class

};

#endif
