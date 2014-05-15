
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
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/	
		LauSigmaRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauSigmaRes();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::Sigma;}

		//! Set value of the various parameters
		/*!
			\param [in] name the name of the parameter to be changed
			\param [in] value the new parameter value
		*/
		virtual void setResonanceParameter(const TString& name, const Double_t value);

	protected:
		//! Set the parameter values
		/*!
			\param [in] b1 factor from BES data
			\param [in] b2 factor from BES data
			\param [in] A factor from BES data
			\param [in] m0 factor from BES data
		*/
		void setConstants(Double_t b1, Double_t b2, Double_t A, Double_t m0);

		//! Set the b1 parameter
		/*!
			\param [in] b1 new value for b1 parameter
		*/
		void setB1Value(const Double_t b1) { b1_ = b1; }

		//! Set the b2 parameter
		/*!
			\param [in] b2 new value for b2 parameter
		*/
		void setB2Value(const Double_t b2) { b2_ = b2; }

		//! Set the A parameter
		/*!
			\param [in] A new value for A parameter
		*/
		void setAValue(const Double_t A) { A_ = A; }

		//! Set the m0 parameter
		/*!
			\param [in] m0 new value for m0 parameter
		*/
		void setM0Value(const Double_t m0) { m0_ = m0; m0Sq_ = m0*m0; denom_ = m0Sq_ - sAdler_; }

		//! Get the b1 parameter value
		/*!
			\return value of the b1 parameter
		*/
		Double_t getB1Value() const { return b1_; }

		//! Get the b2 parameter value
		/*!
			\return value of the b2 parameter
		*/
		Double_t getB2Value() const { return b2_; }

		//! Get the A parameter value
		/*!
			\return value of the A parameter
		*/
		Double_t getAValue() const { return A_; }

		//! Get the m0 parameter value
		/*!
			\return value of the m0 parameter
		*/
		Double_t getM0Value() const { return m0_; }

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
