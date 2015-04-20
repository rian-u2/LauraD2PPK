
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsModIndPartWave.hh
    \brief File containing declaration of LauAbsModIndPartWave class.
 */

/*! \class LauAbsModIndPartWave
    \brief Abstract base class for defining a model independent partial wave component

    Abstract base class for defining a model independent partial wave component.
    This model uses splines to produce a partial wave from two sets of real numbers that represent the amplitude at a series of points in the phase space.
    These real numbers at each point can be floated in the fit.
    Classes inheriting from this define whether these real numbers are e.g. the magnitude and phase or e.g. the real and imaginary part of the amplitude.
 */

#ifndef LAU_ABSMODINDPARTWAVE
#define LAU_ABSMODINDPARTWAVE

#include <set>

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class TSpline3;


class LauAbsModIndPartWave : public LauAbsResonance {

	public:
		//! Constructor
		/*!
		    \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
		    \param [in] resPairAmpInt the number of the daughter not produced by the resonance
		    \param [in] daughters the daughter particles
		*/
		LauAbsModIndPartWave(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor
		virtual ~LauAbsModIndPartWave();

		//! Initialise the model
		virtual void initialise();

		//! Define the knot positions
		/*!
		    If absent from the set provided, knots are added automatically at the upper and lower kinematic limits

		    \param [in] masses the mass values at which the knots are placed
		*/
		void defineKnots(const std::set<Double_t>& masses);

		//! Return the number of knots that have been defined (including those at the upper and lower kinematic limits)
		/*!
		    \return the number of knots
		*/
		UInt_t nKnots() const { return nKnots_; }

		//! Set the values of the two real parameters that define the amplitude at a given knot
		/*!
		    \param [in] knot the knot to be updated
		    \param [in] ampVal1 the value of first real parameter representing the amplitude at the knot
		    \param [in] ampVal2 the value of second real parameter representing the amplitude at the knot
		    \param [in] fixAmpVal1 whether the first real parameter should be fixed
		    \param [in] fixAmpVal2 whether the second real parameter should be fixed
		*/
		virtual void setKnotAmp(const UInt_t knot, const Double_t ampVal1, const Double_t ampVal2, const Bool_t fixAmpVal1, const Bool_t fixAmpVal2) = 0;

		//! Set whether the parameters should be floated only in the second-stage of a two-stage fit
		/*!
		    By default, the parameters describing the amplitude at each
		    knot will float from the outset of a fit.
		    If, however, a good estimate of these is already known, it
		    can be more efficient to initially fix them and then to
		    float them only in a second stage (as is done for other
		    resonance lineshape parameters).
		    This function allows the toggling of this behaviour.

		    \param secondStage whether the parameters should float only in the second stage
		*/
		void floatKnotsSecondStage(const Bool_t secondStage);

		//! Retrieve the value of the second stage flag
		Bool_t floatKnotsSecondStage() const {return secondStage_;};

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return floating parameters of the resonance
		*/
		virtual const std::vector<LauParameter*>& getFloatingParameters();

	protected:
		//! Complex resonant amplitude
		/*!
		    \param [in] mass appropriate invariant mass for the resonance
		    \param [in] spinTerm Zemach spin term
		*/
		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

		//! Evaluate the amplitude at the given point from the splines
		/*!
		    \param [in] mass appropriate invariant mass for the resonance
		*/
		virtual void evaluateAmplitude(const Double_t mass) = 0;

		//! Method to check that the supplied knot positions are valid
		/*!
		    \param [in] masses the mass values at which the knots are placed
		*/
		virtual std::set<Double_t> checkKnots(const std::set<Double_t>& masses);

		//! Method to create the parameter objects for the given knot
		/*!
		    \param [in] iKnot the index of the knot
		*/
		virtual void createAmpParameters(const UInt_t iKnot) = 0;

		//! Helper function to set the current amplitude value
		/*!
		    \param [in] realPart the real part of the amplitude
		    \param [in] imagPart the imaginary part of the amplitude
		*/
		void setAmp(const Double_t realPart, const Double_t imagPart)
		{
			amp_.setRealImagPart(realPart,imagPart);
		}

		//! Helper function to access the masses
		const std::vector<Double_t>& getMasses() {return masses_;}

		//! Helper function to access the 1st parameter set
		std::vector<Double_t>& getAmp1Vals() {return amp1Vals_;}

		//! Helper function to access the 2nd parameter set
		std::vector<Double_t>& getAmp2Vals() {return amp2Vals_;}

		//! Helper function to access the 1st parameter set
		std::vector<LauParameter*>& getAmp1Pars() {return amp1Pars_;}

		//! Helper function to access the 2nd parameter set
		std::vector<LauParameter*>& getAmp2Pars() {return amp2Pars_;}

		//! Helper function to access the 1st spline
		const TSpline3* getSpline1() const {return spline1_;}

		//! Helper function to access the 1st spline
		const TSpline3* getSpline2() const {return spline2_;}

	private:
		//! The number of knots
		UInt_t nKnots_;

		//! The masses at which knots are defined in the magnitude and phase splines
		std::vector<Double_t> masses_;

		//! The values of the first real parameter at each knot
		std::vector<Double_t> amp1Vals_;
		//! The values of the second real parameter at each knot
		std::vector<Double_t> amp2Vals_;

		//! The parameters for the first real value at the knots
		std::vector<LauParameter*> amp1Pars_;
		//! The parameters for the second real value at the knots
		std::vector<LauParameter*> amp2Pars_;

		//! The spline used to interpolate the values of the first real parameter
		TSpline3* spline1_;
		//! The spline used to interpolate the values of the second real parameter
		TSpline3* spline2_;

		//! Flag to determine if the parameters should be floated only in the second stage of the fit
		Bool_t secondStage_;

		//! The current value of the amplitude
		LauComplex amp_;

		ClassDef(LauAbsModIndPartWave,0) // model independent partial wave

};

#endif
