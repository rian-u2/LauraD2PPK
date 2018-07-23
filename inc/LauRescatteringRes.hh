// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRescatteringRes.hh
    \brief File containing declaration of LauRescatteringRes class.
*/

/*! \class LauRescatteringRes
    \brief Class for defining the Rescatering model.

    Defines the Rescatering models from PiPi-KK Inelastic Scatering :
         2005: J.R. Pelaez, F. J. Ynduráin: PHYSICAL REVIEW D 71, 074016 (2005)
         2015: J. H. Alvarenga Nogueira, I. Bediaga, A. B. R. Cavalcante, T. Frederico, and O. Lourenço: PHYSICAL REVIEW D 92, 054010 (2015)
         2018: J.R. Pelaez,  A.Rodas: Unpublished yet PiPi -> KK scattering up to 1.47 GeV with hyperbolic dispersion relations.
*/

#ifndef LAU_RESCATERING_RES
#define LAU_RESCATERING_RES

#include "TString.h"

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class LauKinematics;
class LauParameter;


class LauRescatteringRes : public LauAbsResonance {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resType the model of the resonance
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauRescatteringRes(LauResonanceInfo* resInfo, const LauAbsResonance::LauResonanceModel resType,
				const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauRescatteringRes();

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
		//! Set the parameter lambdaPiPi, the NR term for the PiPi
		/*!
			\param [in] lambdaPiPi, the NR term for the PiPi
		*/
		void setLambdaPiPi(const Double_t lambda);

		//! Get the lambdaPiPi, the NR term for the PiPi
		/*!
			\return the lambdaPiPi, the NR term for the PiPi
		*/
		Double_t getLambdaPiPi() const {return (lambdaPiPi_!=0) ? lambdaPiPi_->value() : 0.0;}

		//! See if the lambdaPiPi parameter is fixed or floating
		/*!
			\return kTRUE if the lambdaPiPi  parameter is fixed, kFALSE otherwise
		*/
		Bool_t fixLambdaPiPi() const {return (lambdaPiPi_!=0) ? lambdaPiPi_->fixed() : kTRUE;}

		//! Set the parameter lambdaKK, the NR term for the KK
		/*!
			\param [in] lambdaKK, the NR term for the KK
		*/
		void setLambdaKK(const Double_t lambda);

		//! Get the lambdaKK, the NR term for the KK
		/*!
			\return the lambdaKK, the NR term for the KK
		*/
		Double_t getLambdaKK() const {return (lambdaKK_!=0) ? lambdaKK_->value() : 0.0;}

		//! See if the lambdaKK parameter is fixed or floating
		/*!
			\return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
		*/
		Bool_t fixLambdaKK() const {return (lambdaKK_!=0) ? lambdaKK_->fixed() : kTRUE;}

	void setkkps(const Double_t KKps);
	Double_t getkkps() const {return (kkps_!=0) ? kkps_->value() : 0.0;}
	Bool_t fixkkps() const {return (kkps_!=0) ? kkps_->fixed() : kTRUE;}

	void setMF(const Double_t mff);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getMF() const {return (Mf_!=0) ? Mf_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixMF() const {return (Mf_!=0) ? Mf_->fixed() : kTRUE;}
	
	void setMS(const Double_t mss);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getMS() const {return (Ms_!=0) ? Ms_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixMS() const {return (Ms_!=0) ? Ms_->fixed() : kTRUE;}
	void setMPrime(const Double_t mprimee);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getMPrime() const {return (Mprime_!=0) ? Mprime_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixMPrime() const {return (Mprime_!=0) ? Mprime_->fixed() : kTRUE;}
	void setBETA(const Double_t betaa);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getBETA() const {return (Beta_!=0) ? Beta_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixBETA() const {return (Beta_!=0) ? Beta_->fixed() : kTRUE;}
	void setEPSA(const Double_t epsaa);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getEPSA() const {return (EpsA_!=0) ? EpsA_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixEPSA() const {return (EpsA_!=0) ? EpsA_->fixed() : kTRUE;}
	void setEPSB(const Double_t epsbb);
	
	//! Get the lambdaKK, the NR term for the KK
	/*!
	 \return the lambdaKK, the NR term for the KK
	 */
	Double_t getEPSB() const {return (EpsB_!=0) ? EpsB_->value() : 0.0;}
	
	//! See if the lambdaKK parameter is fixed or floating
	/*!
	 \return kTRUE if the lambdaKK  parameter is fixed, kFALSE otherwise
	 */
	Bool_t fixEPSB() const {return (EpsB_!=0) ? EpsB_->fixed() : kTRUE;}
	
	


		//! Complex resonant amplitude
		/*!
			\param [in] mass appropriate invariant mass for the resonance
			\param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

	private:
		//! Copy constructor (not implemented)
		LauRescatteringRes(const LauRescatteringRes& rhs);

		//! Copy assignment operator (not implemented)
		LauRescatteringRes& operator=(const LauRescatteringRes& rhs);

		//! the NR term for the PiPi
		LauParameter* lambdaPiPi_;

		//! the NR term for the KK
		LauParameter* lambdaKK_;

		//! the NR term for the PiPi
		LauParameter* kkps_;

		//! the NR term for the PiPi
		LauParameter* Mf_;
	
		//! the NR term for the KK
		LauParameter* Ms_;

		//! the NR term for the PiPi
		LauParameter* Mprime_;
	
		//! the NR term for the KK
		LauParameter* Beta_;

		//! the NR term for the KK
		LauParameter* EpsA_;

		//! the NR term for the KK
		LauParameter* EpsB_;


		UInt_t  type_;

		//! The model to use
		LauAbsResonance::LauResonanceModel model_;

		ClassDef(LauRescatteringRes,0)
};

#endif
