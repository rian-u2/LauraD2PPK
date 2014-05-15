
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBelleNR.hh
    \brief File containing declaration of LauBelleNR class.
*/

/*! \class LauBelleNR
    \brief Class for defining the Belle nonresonant model.

    Defines the nonresonant model from the Belle collaboration.
    arXiv:hep-ex/0412066
*/

#ifndef LAU_BELLE_NR
#define LAU_BELLE_NR

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;
class LauParameter;


class LauBelleNR : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resType the model of the resonance
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauBelleNR(LauResonanceInfo* resInfo, const LauAbsResonance::LauResonanceModel resType,
				const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauBelleNR();

		//! Initialise the model
		virtual void initialise();

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return model_;}

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

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return floating parameters of the resonance
		*/
		virtual const std::vector<LauParameter*>& getFloatingParameters();

	protected:
		//! Set the parameter alpha, the effective range
		/*!
			\param [in] alpha the new effective range parameter value
		*/
		void setAlpha(const Double_t alpha);

		//! Get the effective range parameter
		/*!
			\return the effective range parameter
		*/
		Double_t getAlpha() const {return (alpha_!=0) ? alpha_->value() : 0.0;}

		//! See if the alpha parameter is fixed or floating
		Bool_t fixAlpha() const {return (alpha_!=0) ? alpha_->fixed() : kTRUE;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! The range parameter
		LauParameter* alpha_;

		//! The model to use
		LauAbsResonance::LauResonanceModel model_;

		ClassDef(LauBelleNR,0) // Belle Non-resonant model
};

#endif
