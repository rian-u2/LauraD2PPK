
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

#include "LauBlattWeisskopfFactor.hh"
#include "LauComplex.hh"
#include "LauParameter.hh"

class LauDaughters;
class LauKinematics;
class LauResonanceInfo;

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
			PowerLawNR,	/*!< an empirical power law nonresonant amplitude */
			BelleSymNR,	/*!< an empirical exponential nonresonant amplitude for symmetrised DPs */
			TaylorNR,	/*!< an empirical Taylor expansion nonresonant amplitude for symmetrised DPs */
			PolNR,		/*!< an empirical polynomial nonresonant amplitude */
			MIPW, 		/*!< a model independent partial wave */
			GaussIncoh	/*!< an incoherent Gaussian shape */
		};

		//! Constructor (for use by standard resonances)
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauAbsResonance(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Constructor (for use by K-matrix components)
		/*!
			\param [in] resName the name of the component
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauAbsResonance(const TString& resName, const Int_t resPairAmpInt, const LauDaughters* daughters);

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

		//! Get the name of the resonance
		/*! 
			\return the resonance name
		*/
		const TString& getSanitisedName() const {return sanitisedName_;}

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

		//! Get the mass parameter of the resonance
		/*! 
			\return the resonance mass parameter
		*/
		LauParameter* getMassPar() {return resMass_;}

		//! Get the width parameter of the resonance
		/*! 
			\return the resonance width parameter
		*/
		LauParameter* getWidthPar() {return resWidth_;}

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return floating parameters of the resonance
		*/
		virtual const std::vector<LauParameter*>& getFloatingParameters() { return this->getParameters(); };

		//! Get the helicity flip flag
		/*! 
			\return the flip helicity flag
		*/
		Bool_t flipHelicity() const {return flipHelicity_;}

		//! Set the helicity flip flag
		/*!
			\param [in] boolean the helicity flip status
		*/
		void flipHelicity(const Bool_t boolean) {flipHelicity_ = boolean;}
	
		//! Get the ignore momenta flag
		/*! 
			\return the ignore momenta flag
		*/
		Bool_t ignoreMomenta() const {return ignoreMomenta_;}

		//! Set the ignore p_ and q_ flag
		/*!
			\param [in] boolean the ignore momenta status
		*/
		void ignoreMomenta(const Bool_t boolean) {ignoreMomenta_ = boolean;}

		//! Allow the mass, width and spin of the resonance to be changed
		/*!
			Negative values wil be ignored, so if, for example, you
			want to only change the spin you can provide negative
			values for the mass and width

			\param [in] newMass new value of the resonance mass 
			\param [in] newWidth new value of the resonance width
			\param [in] newSpin new value of the resonance spin 
		*/
		void changeResonance(const Double_t newMass, const Double_t newWidth, const Int_t newSpin);

		//! Allow the Blatt-Weisskopf radius for the resonance and parent factors to be changed
		/*!
			Negative values wil be ignored, so if, for example, you
			want to only change the parent radius you can provide a
			negative value for the resonance radius

			\param [in] resRadius new value of the resonance radius 
			\param [in] parRadius new value of the parent radius
		*/
		void changeBWBarrierRadii(const Double_t resRadius, const Double_t parRadius);

		//! Set value of the various parameters
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);

		//! Allow the various parameters to float in the fit
		/*!
			\param [in] name the name of the parameter to be floated
		*/
		virtual void floatResonanceParameter(const TString& name);

		//! Access the given resonance parameter
		/*!
			\param [in] name the name of the parameter
			\return the corresponding parameter
		 */
		virtual LauParameter* getResonanceParameter(const TString& name);

		//! Fix or release the resonance mass
		/*!
			\param [in] parFixed new status of mass
		*/
		void fixMass(const Bool_t parFixed) { if (resMass_!=0) { resMass_->fixed(parFixed); } }

		//! Fix or release the resonance width
		/*!
			\param [in] parFixed new status of width
		*/
		void fixWidth(const Bool_t parFixed) { if (resWidth_!=0) { resWidth_->fixed(parFixed); } }

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

		//! Set the form factor model and parameters
		/*!
			\param [in] resFactor the barrier factor for the resonance decay
			\param [in] parFactor the barrier factor for the parent decay
		*/
		void setBarrierRadii(LauBlattWeisskopfFactor* resFactor, LauBlattWeisskopfFactor* parFactor)
		{
			resBWFactor_ = resFactor;
			parBWFactor_ = parFactor;
		}

		//! Fix or release the Blatt-Weisskopf barrier radii
		void fixBarrierRadii(const Bool_t fixResRadius, const Bool_t fixParRadius);

		//! Get the status of resonance barrier radius (fixed or released)
		Bool_t fixResRadius() const;

		//! Get the status of parent barrier radius (fixed or released)
		Bool_t fixParRadius() const;

		//! Get the radius of the resonance barrier factor
		Double_t getResRadius() const;

		//! Get the radius of the parent barrier factor
		Double_t getParRadius() const;

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

		//! Get the centrifugal barrier for the parent decay
		LauBlattWeisskopfFactor* getParBWFactor() {return parBWFactor_;}
		const LauBlattWeisskopfFactor* getParBWFactor() const {return parBWFactor_;}
		//! Get the centrifugal barrier for the resonance decay
		LauBlattWeisskopfFactor* getResBWFactor() {return resBWFactor_;}
		const LauBlattWeisskopfFactor* getResBWFactor() const {return resBWFactor_;}

		//! Access the resonance info object
		LauResonanceInfo* getResInfo() const {return resInfo_;}

		//! Access the daughters object
		const LauDaughters* getDaughters() const {return daughters_;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm) = 0;

		//! Clear list of floating parameters
		void clearFloatingParameters() { resParameters_.clear(); }

		//! Add parameter to the list of floating parameters
		/*!
			\param [in] param the parameter to be added to the list
		*/
		void addFloatingParameter( LauParameter* param );

		//! Access the list of floating parameters
		std::vector<LauParameter*>& getParameters() { return resParameters_; }


	private:
		//! Copy constructor (not implemented)
		LauAbsResonance(const LauAbsResonance& rhs);

		//! Copy assignment operator (not implemented)
		LauAbsResonance& operator=(const LauAbsResonance& rhs);

		//! Information on the resonance
		LauResonanceInfo* resInfo_;

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

		//! Resonance name with illegal characters removed
		TString sanitisedName_;

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
		//! Blatt Weisskopf barrier for parent decay
		LauBlattWeisskopfFactor* parBWFactor_;
		//! Blatt Weisskopf barrier for resonance decay
		LauBlattWeisskopfFactor* resBWFactor_;

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
