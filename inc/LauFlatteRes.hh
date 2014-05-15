
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauFlatteRes.hh
    \brief File containing declaration of LauFlatteRes class.
*/

/*! \class LauFlatteRes
    \brief Class for defining the Flatte resonance model

    Class for defining the Flatte resonance model.
    For use with the f_0(980) resonance.
*/

#ifndef LAU_FLATTE_RES
#define LAU_FLATTE_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"


class LauFlatteRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance 
			\param [in] daughters the daughter particles
		*/	
		LauFlatteRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);
		
		//! Destructor
		virtual ~LauFlatteRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Flatte;}

		//! Set value of a resonance parameter
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);
		
	protected:
		//! Get the g1 parameter
		/*! 
			\return constant factor g1
		*/	
		Double_t getg1Parameter() const {return g1_;}

		//! Get the g2 parameter
		/*! 
			\return constant factor g2
		*/	
		Double_t getg2Parameter() const {return g2_;}

		//! Set the constant g factors
		/*!
			\param [in] g1 gPiPi factor
			\param [in] g2 gKK factor
		*/	
		void setGFactors(Double_t g1, Double_t g2);

		//! Set the g1 parameter
		/*! 
			\param [in] g1 constant factor
		*/	
		void setg1Parameter(Double_t g1) {g1_ = g1;}

		//! Set the g2 parameter
		/*! 
			\param [in] g2 constant factor
		*/	
		void setg2Parameter(Double_t g2) {g2_ = g2;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Define allowed types
		enum FlattePartType {FlattePi, FlatteK};

		//! The resonance mass
		Double_t resMass_;
		//! Square of the resonance mass
		Double_t resMassSq_;
		//! Constant factor (default value from BES data)
		Double_t g1_; 
		//! Constant factor (default value from BES data)
		Double_t g2_;
		//! Defined as (mPi0+mPi0)*(mPi0+mPi0)
		Double_t mSumSq0_; 
		//! Defined as (mPi+mPi)*(mPi+mPi)
		Double_t mSumSq1_; 
		//! Defined as (mK+mK)*(mK+mK)
		Double_t mSumSq2_; 
		//! Defined as (mK0+mK0)*(mK0+mK0)
		Double_t mSumSq3_;

		ClassDef(LauFlatteRes,0) // Flatte resonance model

};

#endif
