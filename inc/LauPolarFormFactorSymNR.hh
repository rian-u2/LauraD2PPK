
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPolarFormFactorSymNR.hh
    \brief File containing declaration of LauPolarFormFactorSymNR class.
*/

/*! \class LauPolarFormFactorSymNR
    \brief Class for defining the Reescatering model.

    Defines the reescatering model from:
         Pelaez et Yndúrain: arXiv:hep-ph/0411334v2 Mar 2005
         Nogueira, Bediaga, Cavalcante, Frederico, Lorenco: JHEP ???
*/

#ifndef LAU_POLAR_FORM_FACTOR_SYM_NR
#define LAU_POLAR_FORM_FACTOR_SYM_NR

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;
class LauParameter;


class LauPolarFormFactorSymNR : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resType the model of the resonance
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauPolarFormFactorSymNR(LauResonanceInfo* resInfo, const LauAbsResonance::LauResonanceModel resType, 
                                               const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauPolarFormFactorSymNR();

		//! Initialise the model
		virtual void initialise();

		//! Get the complex dynamical amplitude
		/*! 
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/
		virtual LauComplex amplitude(const LauKinematics* kinematics);

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
		//! Set the parameter lambda, the NR term for the 
		/*!
			\param [in] lambda, the NR term for the 
		*/
		void setLambda(const Double_t lambda);

		//! Get the lambda, the NR term for the 
		/*!
			\return the lambda, the NR term for the 
		*/
		Double_t getLambda() const {return (lambda_!=0) ? lambda_->value() : 0.0;}

		//! See if the lambda parameter is fixed or floating
		/*!
			\return kTRUE if the lambda  parameter is fixed, kFALSE otherwise
		*/
		Bool_t fixLambda() const {return (lambda_!=0) ? lambda_->fixed() : kTRUE;}

		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Copy constructor (not implemented)
		LauPolarFormFactorSymNR(const LauPolarFormFactorSymNR& rhs);

		//! Copy assignment operator (not implemented)
		LauPolarFormFactorSymNR& operator=(const LauPolarFormFactorSymNR& rhs);

		LauParameter* lambda_;

		//! The model to use
		LauAbsResonance::LauResonanceModel model_;

		ClassDef(LauPolarFormFactorSymNR,0)
};

#endif
