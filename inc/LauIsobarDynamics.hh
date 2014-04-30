
// Copyright University of Warwick 2005 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauIsobarDynamics.hh
    \brief File containing declaration of LauIsobarDynamics class.
*/

/*! \class LauIsobarDynamics
    \brief Class for defining signal dynamics using the isobar model.
*/

#ifndef LAU_ISOBAR_DYNAMICS
#define LAU_ISOBAR_DYNAMICS

#include <vector>

#include "TString.h"

#include "LauAbsDPDynamics.hh"
#include "LauAbsResonance.hh"
#include "LauComplex.hh"

class LauDaughters;
class LauAbsEffModel;
class LauFitDataTree;
class LauKMatrixPropagator;
class LauDPPartialIntegralInfo;

class LauIsobarDynamics : public LauAbsDPDynamics {

	public:
		//! Constructor
		/*!
		    \param [in] daughters the daughters of the decay
		    \param [in] effModel the model to describe the efficiency across the Dalitz plot
		    \param [in] scfFractionModel the model to describe the fraction of poorly constructed events (the self cross feed fraction) across the Dalitz plot
		*/
		LauIsobarDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, LauAbsEffModel* scfFractionModel = 0);

		//! Constructor
		/*!
		    \param [in] daughters the daughters of the decay
		    \param [in] effModel the model to describe the efficiency across the Dalitz plot
		    \param [in] scfFractionModel the models to describe the fraction of poorly constructed events (the self cross feed fraction) across the Dalitz plot for various tagging categories
		*/
		LauIsobarDynamics(LauDaughters* daughters, LauAbsEffModel* effModel, LauTagCatScfFractionModelMap scfFractionModel);

		//! Destructor
		virtual ~LauIsobarDynamics();

		//! Initialise the Dalitz plot dynamics
		/*!
		    \param [in] coeffs the complex coefficients for the resonances
		*/
		virtual void initialise(const std::vector<LauComplex>& coeffs);

		//! recalculate Normalization
		virtual void recalculateNormalisation();

		//! Set the name of the file to which to save the results of the integrals
		/*!
		    \param [in] fileName the name of the file
		*/
		inline void setIntFileName(const TString& fileName) {intFileName_ = fileName;}

		// Integration
		//! Set the widths of the bins to use when integrating across the Dalitz plot
		/*!
		    \param [in] m13BinWidth the bin width to use when integrating over m13
		    \param [in] m23BinWidth the bin width to use when integrating over m23
		*/
		virtual void setIntegralBinWidths(Double_t m13BinWidth, Double_t m23BinWidth);

		//! Add a resonance to the Dalitz plot
		/*!
		    \param [in] resName the name of the resonant particle
		    \param [in] resPairAmpInt the index of the daughter not produced by the resonance
		    \param [in] resType the model for the resonance dynamics
		    \return the newly created resonance
		*/
		virtual LauAbsResonance* addResonance(const TString& resName, const Int_t resPairAmpInt, const LauAbsResonance::LauResonanceModel resType);

		//! Define a new K-matrix Propagator
		/*!
		    \param [in] propName the name of the propagator
		    \param [in] paramFileName the file that defines the propagator
		    \param [in] resPairAmpInt the index of the bachelor
		    \param [in] nChannels the number of channels
		    \param [in] nPoles the number of poles
		    \param [in] rowIndex the index of the row to be used when summing over all amplitude channels: S-wave corresponds to rowIndex = 1.
		*/
		virtual void defineKMatrixPropagator(const TString& propName, const TString& paramFileName,
						     Int_t resPairAmpInt, Int_t nChannels, Int_t nPoles, Int_t rowIndex = 1);

		//! Add a K-matrix production pole term to the model
		/*!
		    \param [in] poleName the name of the pole
		    \param [in] propName the name of the propagator to use
		    \param [in] poleIndex the index of the pole within the propagator
		*/
		virtual void addKMatrixProdPole(const TString& poleName, const TString& propName, Int_t poleIndex);

		//! Add a K-matrix slowly-varying part (SVP) term to the model
		/*!
		    \param [in] SVPName the name of the term
		    \param [in] propName the name of the propagator to use
		    \param [in] channelIndex the index of the channel within the propagator
		*/
		virtual void addKMatrixProdSVP(const TString& SVPName, const TString& propName, Int_t channelIndex);

		//! Change the properties of a resonance particle within this model
		/*!
		    Note that parameters set to -1 are ignored.
		    \param [in] resName the name of the resonance to modify
		    \param [in] newMass the new mass for this resonance
		    \param [in] newWidth the new width for this resonance
		    \param [in] newSpin the new spin for this resonance
		*/
		virtual void changeResonance(const TString& resName, Double_t newMass = -1.0, Double_t newWidth = -1.0, Int_t newSpin = -1);

		//! Generate a toy MC signal event
		/*!
		    \return kTRUE if the event is successfully generated, kFALSE otherwise
		*/
		virtual Bool_t generate();

		//! Check the status of the toy MC generation
		/*!
		    \param [in] printErrorMessages whether error messages should be printed
		    \param [in] printInfoMessages whether info messages should be printed
		    \return the status of the toy MC generation
		*/
		virtual ToyMCStatus checkToyMC(Bool_t printErrorMessages = kTRUE, Bool_t printInfoMessages = kFALSE);

		//! Retrieve the maximum number of iterations allowed when generating an event
		/*!
		    \return the maximum number of iterations allowed
		*/
		inline Int_t maxGenIterations() const {return iterationsMax_;}

		//! Calculate the likelihood (and all associated information) for the given event number
		/*!
		    \param [in] iEvt the event number
		*/
		virtual void calcLikelihoodInfo(UInt_t iEvt);

		//! Calculate the likelihood (and all associated information) given values of the Dalitz plot coordinates
		/*!
		    \param [in] m13Sq the invariant mass squared of the first and third daughters
		    \param [in] m23Sq the invariant mass squared of the second and third daughters
		*/
		virtual void calcLikelihoodInfo(Double_t m13Sq, Double_t m23Sq);

		//! Calculate the likelihood (and all associated information) given values of the Dalitz plot coordinates and the tagging category
		/*!
		    Also obtain the self cross feed fraction to cache with the rest of the Dalitz plot quantities.
		    \param [in] m13Sq the invariant mass squared of the first and third daughters
		    \param [in] m23Sq the invariant mass squared of the second and third daughters
		    \param [in] tagCat the tagging category
		*/
		virtual void calcLikelihoodInfo(Double_t m13Sq, Double_t m23Sq, Int_t tagCat);

		//! Retrieve the total amplitude for the current event
		/*!
		    \return the total amplitude
		*/
		virtual const LauComplex& getEvtDPAmp() const {return totAmp_;}

		//! Retrieve the invariant mass squared of the first and third daughters in the current event
		/*!
		    \return the invariant mass squared of the first and third daughters in the current event
		*/
		virtual Double_t getEvtm13Sq() const {return m13Sq_;}

		//! Retrieve the invariant mass squared of the second and third daughters in the current event
		/*!
		    \return the invariant mass squared of the second and third daughters in the current event
		*/
		virtual Double_t getEvtm23Sq() const {return m23Sq_;}

		//! Retrieve the square Dalitz plot coordinate, m', for the current event
		/*!
		    \return the square Dalitz plot coordinate, m', for the current event
		*/
		virtual Double_t getEvtmPrime() const {return mPrime_;}

		//! Retrieve the square Dalitz plot coordinate, theta', for the current event
		/*!
		    \return the square Dalitz plot coordinate, theta', for the current event
		*/
		virtual Double_t getEvtthPrime() const {return thPrime_;}

		//! Retrieve the efficiency for the current event
		/*!
		    \return the efficiency for the current event
		*/
		virtual Double_t getEvtEff() const {return eff_;}

		//! Retrieve the fraction of events that are poorly reconstructed (the self cross feed fraction) for the current event
		/*!
		    \return the self cross feed fraction for the current event
		*/
		virtual Double_t getEvtScfFraction() const {return scfFraction_;}

		//! Retrieve the Jacobian, for the transformation into square DP coordinates, for the current event
		/*!
		    \return the Jacobian for the current event
		*/
		virtual Double_t getEvtJacobian() const {return jacobian_;}

		//! Retrieve the likelihood for the current event
		/*!
		    evtLike_ = totAmp_.abs2()*eff_/DPNorm_

		    \return the likelihood for the current event
		*/
		virtual Double_t getEvtLikelihood() const {return evtLike_;}

		//! Calculate the fit fractions, mean efficiency and total DP rate
		/*!
		    \param [in] init whether the calculated values should be stored as the initial/generated values or the fitted values
		*/
		virtual void calcExtraInfo(Bool_t init = kFALSE);

		//! Calculates whether an event with the current kinematics should be accepted in order to produce a distribution of events that matches the model e.g. when reweighting embedded data
		/*!
		    Uses the accept/reject method.
		    \return kTRUE if the event has been accepted, kFALSE otherwise
		*/
 	        virtual Bool_t gotReweightedEvent();

		//! Calculate the acceptance rate, for events with the current kinematics, when generating events according to the model
		/*!
		    \return the weight for the current kinematics
		*/
 	        virtual Double_t getEventWeight();

		//! Set the maximum value of A squared to be used in the accept/reject
		/*!
		    \param [in] value the new value
		*/
		inline void setASqMaxValue(Double_t value) {aSqMaxSet_ = value;}

		//! Retrieve the maximum value of A squared to be used in the accept/reject
		/*!
		    \return the maximum value of A squared
		*/
		inline Double_t getASqMaxSetValue() const { return aSqMaxSet_; }

		//! Retrieve the maximum of A squared that has been found while generating
		/*!
		    \return the maximum of A squared that has been found
		*/
		inline Double_t getASqMaxVarValue() const { return aSqMaxVar_; }

		//! Retrieve the normalised dynamic part of the amplitude of the given amplitude component at the current point in the Dalitz plot
		/*!
		    \param [in] resID the index of the amplitude component within the model
		    \return the amplitude of the given amplitude component
		*/
		virtual LauComplex getDynamicAmp(Int_t resID) const {return ff_[resID].scale(fNorm_[resID]);}

		//! Retrieve the event-by-event running totals of amplitude cross terms for all pairs of amplitude components
		/*!
		    \return the event-by-event running totals of amplitude cross terms
		*/
		inline const std::vector< std::vector<LauComplex> >& getFiFjSum() const {return fifjSum_;}

		//! Retrieve the event-by-event running totals of efficiency corrected amplitude cross terms for all pairs of amplitude components
		/*!
		    \return the event-by-event running totals of amplitude cross terms with efficiency corrections applied
		*/
		inline const std::vector< std::vector<LauComplex> >& getFiFjEffSum() const {return fifjEffSum_;}

		//! Retrieve the normalisation factors for the dynamic parts of the amplitudes for all of the amplitude components
		/*!
		    \return the normalisation factors
		*/
		inline const std::vector<Double_t>& getFNorm() const {return fNorm_;}

		//! Fill the internal data structure that caches the resonance dynamics
		/*!
		    \param [in] fitDataTree the data source
		*/
		virtual void fillDataTree(const LauFitDataTree& fitDataTree);

		//! Load the data for a given event
		/*!
		    \param [in] iEvt the number of the event
		*/
		virtual void setDataEventNo(UInt_t iEvt);

		//! Set the parameters for the barrier factors for new resonances
		/*!
		    \param [in] resRadius the radius due to the resonance
		    \param [in] parRadius the radius due to the parent
		    \param [in] type the type of the barrier factor
		 */
		inline void setBarrierRadii( Double_t resRadius, Double_t parRadius = 4.0,
				LauAbsResonance::BarrierType type = LauAbsResonance::BWPrimeBarrier )
		{
			setBarrierRadius_ = kTRUE;
			resBarrierRadius_ = resRadius;
			parBarrierRadius_ = parRadius;
			barrierType_ = type;
		}

		//! Set the radius of the barrier factor due to the resonance to use for new amplitude components
		/*!
		    \param [in] radius the barrier radius
		*/
		inline void setResBarrierRadius(Double_t radius) {setBarrierRadius_ = kTRUE; resBarrierRadius_ = radius;}

		//! Set the radius of the barrier factor due to the parent to use for new amplitude components
		/*!
		    \param [in] radius the barrier radius
		*/
		inline void setParBarrierRadius(Double_t radius) {setBarrierRadius_ = kTRUE; parBarrierRadius_ = radius;}

		//! Set the type of barrier factor to use for new amplitude components
		/*!
		    \param [in] type the type of barrier factor. Allowed types are: BWBarrier, BWPrimeBarrier and ExpBarrier.
		*/
		inline void setBarrierType( LauAbsResonance::BarrierType type ) {setBarrierRadius_ = kTRUE; barrierType_ = type;}

		//! Retrieve the radius of the barrier factor due to the resonance to use for new amplitude components
		/*!
		    \return the barrier radius
		*/
		inline Double_t getResBarrierRadius() const {return resBarrierRadius_;}

		//! Retrieve the radius of the barrier factor due to the parent to use for new amplitude components
		/*!
		    \return the barrier radius
		*/
		inline Double_t getParBarrierRadius() const {return parBarrierRadius_;}

		//! Set the helicity flip flag for new amplitude components
		/*!
		    \param [in] boolean the helicity flip flag
		*/
		inline void flipHelicityForCPEigenstates(Bool_t boolean) {flipHelicity_ = boolean;}

	protected:
		//! Print a summary of the model to be used
		virtual void initSummary();

		//! Initialise the internal storage for this model
		virtual void initialiseVectors();

		//! Calculate the Dalitz plot normalisation integrals across the whole Dalitz plot
		virtual void calcDPNormalisation();

		//! Calculate the Dalitz plot normalisation integrals across the whole Dalitz plot
		virtual void calcDPNormalisationScheme();

		//! Calculate the Dalitz plot normalisation integrals over a given range
		/*!
		    \param [in] minm13 the minimum value of m13 in the integration range
		    \param [in] maxm13 the maximum value of m13 in the integration range
		    \param [in] minm23 the minimum value of m23 in the integration range
		    \param [in] maxm23 the maximum value of m23 in the integration range
		    \param [in] m13BinWidth the bin width in m13
		    \param [in] m23BinWidth the bin width in m23
		*/
		virtual void calcDPPartialIntegral(Double_t minm13, Double_t maxm13, Double_t minm23,
				Double_t maxm23, Double_t m13BinWidth, Double_t m23BinWidth);

		//! Write the results of the integrals (and related information) to a file
		virtual void writeIntegralsFile();

		//! Set the dynamic part of the amplitude for a given amplitude component at the current point in the Dalitz plot
		/*!
		    \param [in] index the index of the amplitude component
		    \param [in] realPart the real part of the amplitude
		    \param [in] imagPart the imaginary part of the amplitude
		*/
		virtual void setFFTerm(UInt_t index, Double_t realPart, Double_t imagPart);

		//! Calculate the total Dalitz plot amplitude at the current point in the Dalitz plot
		/*!
		    \param [in] cacheResData whether the amplitudes have already been cached
		    \param [in] weight the weight to apply (used when calculating the integrals)
		    \param [in] useEff whether to apply efficiency corrections
		*/
		virtual void dynamics(Bool_t cacheResData = kTRUE, Double_t weight = 1.0, Bool_t useEff = kTRUE);

		//! Set the maximum of A squared that has been found
		/*!
		    \param [in] value the new value
		*/
		inline void setASqMaxVarValue(Double_t value) {aSqMaxVar_ = value;}

		//! Calculate the normalisation factor for the log-likelihood function
		/*!
		    \return the normalisation factor
		*/
		virtual Double_t calcSigDPNorm();

		//! Calculate the dynamic part of the amplitude for a given component at the current point in the Dalitz plot
		/*!
		    \param [in] index the index of the amplitude component within the model
		*/
		virtual LauComplex resAmp(Int_t index);

		//! Retrieve the named resonance
		/*!
		    \param [in] name the name of the resonance to retrieve
		    \return the named resonance
		*/
		virtual LauAbsResonance* findResonance(const TString& name);

		//! Retrieve the named resonance
		/*!
		    \param [in] name the name of the resonance to retrieve
		    \return the named resonance
		*/
		virtual const LauAbsResonance* findResonance(const TString& name) const;

		//! Remove the charge from the given particle name
		/*!
		    \param [in,out] string the particle name
		*/
		virtual void removeCharge(TString& string) const;

		//! Check whether a resonance is a K-matrix component of a given propagator
		/*!
		    \param [in] resAmpInt the index of the resonance within the model
		    \param [in] propName the name of the K-matrix propagator
		    \return true if the resonance is a component of the given propagator, otherwise return false
		*/
		Bool_t gotKMatrixMatch(UInt_t resAmpInt, const TString& propName) const;

	private:
		//! The type used for containing the K-matrix propagators
		typedef std::map<TString, LauKMatrixPropagator*> KMPropMap;

		//! The type used for mapping K-matrix components to their propagators
		typedef std::map<TString, TString> KMStringMap;

		//! The resonances in the model
		std::vector<LauAbsResonance*> sigResonances_;

		//! The K-matrix propagators
		KMPropMap kMatrixPropagators_;

		//! The names of the M-matrix components in the model mapped to their propagators
		KMStringMap kMatrixPropSet_;

		//! The resonance types of all of the amplitude components
		std::vector<TString> resTypAmp_;

		//! The index within the resonance maker for each amplitude component
		std::vector<Int_t> resIntAmp_;

		//! The index of the daughter not produced by the resonance for each amplitude component
		std::vector<Int_t> resPairAmp_;

		//! The PDG codes of the daughters
		std::vector<Int_t> typDaug_;

		//! Whether the Dalitz plot is symmetrical
		Bool_t symmetricalDP_;

		//! Whether the integrals have been performed
		Bool_t integralsDone_;

		//! Whether the scheme for the integration has been determined
		Bool_t normalizationSchemeDone_;

		//! The storage of the integration scheme
		std::vector<LauDPPartialIntegralInfo*> dpPartialIntegralInfo_;

		//! The name of the file to save integrals to
		TString intFileName_;

		//! The bin width to use when integrating over m13
		Double_t m13BinWidth_;

		//! The bin width to use when integrating over m23
		Double_t m23BinWidth_;

		//! The invariant mass squared of the first and third daughters
		Double_t m13Sq_;

		//! The invariant mass squared of the second and third daughters
		Double_t m23Sq_;

		//! The square Dalitz plot coordinate, m'
		Double_t mPrime_;

		//! The square Dalitz plot coordinate theta'
		Double_t thPrime_;

		//! The efficiency at the current point in the Dalitz plot
		Double_t eff_;

		//!The fraction of events that are poorly reconstructed (the self cross feed fraction) at the current point in the Dalitz plot
		Double_t scfFraction_;

		//! The Jacobian, for the transformation into square DP coordinates at the current point in the Dalitz plot
		Double_t jacobian_;

		//! The value of A squared for the current event
		Double_t ASq_;

		//! The normalised likelihood for the current event
		Double_t evtLike_;

		//! The total amplitude for the current event
		LauComplex totAmp_;

		//! The event-by-event running total of efficiency corrected amplitude cross terms for each pair of amplitude components
		/*!
		    Calculated as the sum of ff_[i]*ff_[j]*efficiency for all events
		*/
		std::vector< std::vector<LauComplex> > fifjEffSum_;

		//! The event-by-event running total of the amplitude cross terms for each pair of amplitude components
		/*!
		    Calculated as the sum of ff_[i]*ff_[j] for all events
		*/
		std::vector< std::vector<LauComplex> > fifjSum_;

		//! The dynamic part of the amplitude for each amplitude component at the current point in the Dalitz plot
		std::vector<LauComplex> ff_;

		//! The event-by-event running total of the dynamical amplitude squared for each amplitude component
		std::vector<Double_t> fSqSum_;

		//! The normalisation factors for the dynamic parts of the amplitude for each amplitude component
		std::vector<Double_t> fNorm_;

		//! The maximum allowed number of attempts when generating an event
		Int_t iterationsMax_;

		//! The number of unsucessful attempts to generate an event so far
		Int_t nSigGenLoop_;

		//! The maximum allowed value of A squared
		Double_t aSqMaxSet_;

		//! The maximum value of A squared that has been seen so far while generating
		Double_t aSqMaxVar_;

		//! Should the radii of the resonance barrier factors be adjusted for new amplitude components
		Bool_t setBarrierRadius_;

		//! The radius of the resonance barrier factor for new amplitude components
		Double_t resBarrierRadius_;

		//! The radius of the parent barrier factor for new amplitude components
		Double_t parBarrierRadius_;

		//! The type of the barrier factor for new amplitude components
		LauAbsResonance::BarrierType barrierType_;

		//! The helicity flip flag for new amplitude components
		Bool_t flipHelicity_;

		//! Flag to recalculate the normalisation
		Bool_t recalcNormalisation_;

		ClassDef(LauIsobarDynamics,0)
};

#endif
