
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsDPDynamics.hh
    \brief File containing declaration of LauAbsDPDynamics class.
*/

/*! \class LauAbsDPDynamics
    \brief Class for defining the abstract interface for signal Dalitz plot dynamics.
*/

#ifndef LAU_ABS_DP_DYNAMICS
#define LAU_ABS_DP_DYNAMICS

#include <vector>
#include <map>

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauParameter.hh"

class LauCacheData;
class LauComplex;
class LauDaughters;
class LauAbsEffModel;
class LauFitDataTree;
class LauKinematics;
class LauResonanceMaker;


class LauAbsDPDynamics {

	public:
		//! The type used for containing multiple self cross feed fraction models for different categories (e.g. tagging categories)
		typedef std::map<Int_t,LauAbsEffModel*> LauTagCatScfFractionModelMap;

		//! Constructor
		/*!
		    \param [in] daughters the daughters of the decay
		    \param [in] effModel the model to describe the efficiency across the Dalitz plot
		    \param [in] scfFractionModel the model to describe the fraction of poorly constructed events (the self cross feed fraction) across the Dalitz plot
		*/
		LauAbsDPDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, LauAbsEffModel* scfFractionModel = 0);

		//! Constructor
		/*!
		    \param [in] daughters the daughters of the decay
		    \param [in] effModel the model to describe efficiency across the Dalitz plot
		    \param [in] scfFractionModel the models to describe the fraction of poorly constructed events (the self cross feed fraction) across the Dalitz plot for various tagging categories
		*/
		LauAbsDPDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, const LauTagCatScfFractionModelMap& scfFractionModel);

		//! Destructor
		virtual ~LauAbsDPDynamics();

		//! The possible statuses for toy MC generation
		enum ToyMCStatus {
			GenOK,        /*!< Generation completed OK */
			MaxIterError, /*!< Maximum allowed number of iterations completed without success (ASqMax is too high) */
			ASqMaxError   /*!< An amplitude squared value was returned that was larger than the maximum expected (ASqMax is too low) */
		};

		//! Add a resonance to the Dalitz plot
		/*!
		    \param [in] resName the name of the resonant particle
		    \param [in] resPairAmpInt the index of the daughter not produced by the resonance (the bachelor)
		    \param [in] resType the model for the resonance dynamics
		    \return the newly created resonance
		*/
		virtual LauAbsResonance* addResonance(const TString& resName, const Int_t resPairAmpInt, const LauAbsResonance::LauResonanceModel resType) = 0;

		//! Initialise the Dalitz plot dynamics
		/*!
		    \param [in] coeffs the complex coefficients for the resonances
		*/
		virtual void initialise(const std::vector<LauComplex>& coeffs) = 0;

		//! Obtain the efficiency of the current event from the model
		/*!
		    \return the efficiency
		*/
		virtual Double_t retrieveEfficiency();

		//! Obtain the self cross feed fraction of the current event from the model
		/*!
		    \param [in] tagCat the tagging category of the current event
		    \return the self cross feed fraction
		*/
		virtual Double_t retrieveScfFraction(Int_t tagCat);

		//! Obtain data from a fit tree
		/*!
		    \param [in] inputFitTree the tree
		*/
		virtual void fillDataTree(const LauFitDataTree& inputFitTree) = 0;

		//! Load the data for a given event
		/*!
		    \param [in] iEvt the number of the event
		*/
		virtual void setDataEventNo(UInt_t iEvt);

		//! Check whether this model includes a named resonance
		/*!
		    \param [in] resName the resonance
		    \return true if the resonance is present, false otherwise
		*/
		virtual Bool_t hasResonance(const TString& resName) const;

		//! Retrieve the name of the charge conjugate of a named resonance
		/*!
		    \param [in] resName the resonance
		    \return the name of the charge conjugate
		*/
		virtual TString getConjResName(const TString& resName) const;

		//! Update the complex coefficients for the resonances
		/*!
		    \param [in] coeffs the new set of coefficients
		*/
		virtual void updateCoeffs(const std::vector<LauComplex>& coeffs);

		//! Generate a toy MC signal event
		/*!
		    \return true if the event is successfully generated, false otherwise
		*/
		virtual Bool_t generate() = 0;

		//! Check the status of the toy MC generation
		/*!
		    \param [in] printErrorMessages whether error messages should be printed
		    \param [in] printInfoMessages whether info messages should be printed
		    \return the status of the toy MC generation
		*/
		virtual ToyMCStatus checkToyMC(Bool_t printErrorMessages = kTRUE, Bool_t printInfoMessages = kFALSE) = 0;

		//! Calculate the likelihood (and all associated information) given values of the Dalitz plot coordinates
		/*!
		    \param [in] m13Sq the invariant mass squared of the first and third daughters
		    \param [in] m23Sq the invariant mass squared of the second and third daughters
		*/
		virtual void calcLikelihoodInfo(Double_t m13Sq, Double_t m23Sq) = 0;

		//! Calculate the likelihood (and all associated information) for the given event number
		/*!
		    \param [in] iEvt the event number
		*/
		virtual void calcLikelihoodInfo(UInt_t iEvt) = 0;

		//! Retrieve the likelihood for the current event
		/*!
		    \return the likelihood for the current event
		*/
		virtual Double_t getEvtLikelihood() const = 0;

		//! Retrieve the invariant mass squared of the first and third daughters in the current event
		/*!
		    \return the invariant mass squared of the first and third daughters in the current event
		*/
		virtual Double_t getEvtm13Sq() const = 0;

		//! Retrieve the invariant mass squared of the second and third daughters in the current event
		/*!
		    \return the invariant mass squared of the second and third daughters in the current event
		*/
		virtual Double_t getEvtm23Sq() const = 0;

		//! Retrieve the square Dalitz plot coordinate, m', for the current event
		/*!
		    \return the square Dalitz plot coordinate, m', for the current event
		*/
		virtual Double_t getEvtmPrime() const = 0;

		//! Retrieve the square Dalitz plot coordinate, theta', for the current event
		/*!
		    \return the square Dalitz plot coordinate, theta', for the current event
		*/
		virtual Double_t getEvtthPrime() const = 0;

		//! Retrieve the efficiency for the current event
		/*!
		    \return the efficiency for the current event
		*/
		virtual Double_t getEvtEff() const = 0;

		//! Retrieve the Jacobian, for the transformation into square DP coordinates, for the current event
		/*!
		    \return the Jacobian for the current event
		*/
		virtual Double_t getEvtJacobian() const = 0;		//Not sure whether this should be here or only in LauIsobarDynamics.

		//! Retrieve the fraction of events that are poorly reconstructed (the self cross feed fraction) in the Dalitz plot bin of the current event
		/*!
		    \return the self cross feed fraction for the current event
		*/
		virtual Double_t getEvtScfFraction() const = 0;

		//! Retrieve the total amplitude of all amplitude components at the current point in the Dalitz plot
		/*!
		    \return the total amplitude
		*/
		virtual const LauComplex& getEvtDPAmp() const = 0;

		//! Retrieve the amplitude of the given amplitude component at the current point in the Dalitz plot
		/*!
		    \param [in] resID the index of the amplitude component within the model
		    \return the amplitude of the given amplitude component
		*/
		virtual LauComplex getDynamicAmp(Int_t resID) const = 0;

		//! Calculate the fit fractions, mean efficiency and total DP rate
		/*!
		    \param [in] init whether the calculated values should be used to generate toys and as the initial values when fitting
		*/
		virtual void calcExtraInfo(Bool_t init = kFALSE) = 0;

	 	// Use this method to select events in the DP for embedded-reweighting.
		//! Calculates whether an event with the current kinematics should be accepted in order to produce a distribution of events that matches the model e.g. when reweighting embedded data
		/*!
		    \return true if the event has been accepted, false otherwise
		*/
 	        virtual Bool_t gotReweightedEvent() = 0;

		//! Calculate the acceptance rate, for events with the current kinematics, when generating events according to the model
		/*!
		    \return the weight for the current kinematics
		*/
 	        virtual Double_t getEventWeight() = 0;

		//! Retrieve the mean efficiency across the Dalitz plot
		/*!
		    \return the mean efficiency across the Dalitz plot
		*/
		inline LauParameter getMeanEff() const {return meanDPEff_;}

		//! Retrieve the overall Dalitz plot rate
		/*!
		    \return the overall Dalitz plot rate
		*/
		inline LauParameter getDPRate() const {return DPRate_;}

		//! Retrieve the fit fractions for the amplitude components
		/*!
		    \return the fit fractions
		*/
		inline const LauParArray& getFitFractions() const {return fitFrac_;}

		//! Retrieve the fit fractions for the amplitude components
		/*!
		    \return the fit fractions
		*/
		inline const LauParArray& getFitFractionsEfficiencyUncorrected() const {return fitFracEffUnCorr_;}

		//! Retrieve the number of defined resonances in the resonance maker
		/*!
		    \return the number of defined resonances
		*/
		inline UInt_t getnDefinedResonances() const {return nResDefMax_;}

		//! Retrieve the number of amplitude components
		/*!
		    \return the number of amplitude components
		*/
		inline UInt_t getnAmp() const {return nAmp_;}

		//! Retrieve the normalisation factor for the log-likelihood function
		/*!
		    \return the normalisation factor
		*/
		inline Double_t getDPNorm() const {return DPNorm_;}

		//! Retrieve the number of cached events
		/*!
		    \return the number of cached events
		*/
		inline UInt_t nData() const {return data_.size();}

		//! Retrieve the cached data
		/*!
		    \return the cached data
		*/
		inline const std::vector<LauCacheData*>& getCacheData() const {return data_;}

		//! Retrieve the daughters
		/*!
		    \return the daughters
		*/
		inline LauDaughters* getDaughters() {return daughters_;}

		//! Retrieve the resonance maker object
		/*!
		    \return the resonance maker
		*/
		inline LauResonanceMaker* getResonanceMaker() {return resonanceMaker_;}

		//! Retrieve the Dalitz plot kinematics
		/*!
		    \return the Dalitz plot kinematics
		*/
		inline LauKinematics* getKinematics() {return kinematics_;}

		//! Retrieve the model for the efficiency across the Dalitz plot
		/*!
		    \return the efficiency model
		*/
		inline LauAbsEffModel* getEffModel() {return effModel_;}

		//! Retrieve the model for the fraction of events that are poorly reconstructed (the self cross feed fraction) in each Dalitz plot bin for the first (or only) tagging category
		/*!
		    \return the self cross feed fraction model
		*/
		inline LauAbsEffModel* getScfFractionModel() {return scfFractionModel_[0];}

		//! Retrieve the model for the fraction of events that are poorly reconstructed (the self cross feed fraction) in each Dalitz plot bin for all tagging categories
		/*!
		    \return the self cross feed fraction models
		*/
		inline std::map <Int_t,LauAbsEffModel*> getScfFractionModels() {return scfFractionModel_;}

		//! Check whether a self cross feed fraction model is being used
		/*!
		    \return true if a self cross feed fraction model is being used, false otherwise
		*/
		inline Bool_t usingScfModel() { return ! scfFractionModel_.empty(); }

		//! Retrieve any extra parameters/quantities (e.g. K-matrix total fit fractions)
		/*!
		    \return any extra parameters
		*/
		std::vector<LauParameter> getExtraParameters() {return extraParameters_;}

	protected:
		//! Calculate the normalisation factor for the log-likelihood function
		/*!
		    \return the normalisation factor
		*/
		virtual Double_t calcSigDPNorm() = 0;

		//! Retrieve the named resonance
		/*!
		    \param [in] name the name of the resonance to retrieve
		    \return the named resonance
		*/
		virtual LauAbsResonance* findResonance(const TString& name) = 0;

		//! Retrieve the named resonance
		/*!
		    \param [in] name the name of the resonance to retrieve
		    \return the named resonance
		*/
		virtual const LauAbsResonance* findResonance(const TString& name) const = 0;

		//! The daughters of the decay
		LauDaughters* daughters_;

		//! Object to create resonances
		LauResonanceMaker* resonanceMaker_;

		//! The kinematics of the decay
		LauKinematics* kinematics_;

		//! The efficiency model across the Dalitz plot
		LauAbsEffModel* effModel_;

		//! The self cross feed fraction models across the Dalitz plot
		/*!
		    These model the fraction of signal events that are poorly reconstructed (the self cross feed fraction) as a function of Dalitz plot position.
		    If the self cross feed is depependent on the tagging category then seperate models can be defined.
		*/
		LauTagCatScfFractionModelMap scfFractionModel_;

		//! The number of amplitude components
		UInt_t nAmp_;

		//! The number of resonances defined in the resonance maker
		UInt_t nResDefMax_;

		//! The complex coefficients for the amplitude components
		std::vector<LauComplex> Amp_;

		//! The normalisation factor for the log-likelihood function
		Double_t DPNorm_;

		//! The fit fractions for the amplitude components
		LauParArray fitFrac_;

		//! The efficiency-uncorrected fit fractions for the amplitude components
		LauParArray fitFracEffUnCorr_;

		//! The overall Dalitz plot rate
		LauParameter DPRate_;

		//! The mean efficiency across the Dalitz plot
		LauParameter meanDPEff_;

		//! The cached data for all events
		std::vector<LauCacheData*> data_;

		//! The cached data for the current event
		LauCacheData* currentEvent_;

		//! any extra parameters/quantities (e.g. K-matrix total fit fractions)
		std::vector<LauParameter> extraParameters_;

	private:
		ClassDef(LauAbsDPDynamics,0)
};

#endif
