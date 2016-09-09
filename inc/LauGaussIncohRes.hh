
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauGaussIncohRes.hh
    \brief File containing declaration of LauGaussIncohRes class.
*/

/*! \class LauGaussIncohRes
    \brief Class for defining an incoherent resonance with a Gaussian mass dependence

    Useful for modelling resolution-dominated sharp structures such as D*(2010)
*/

#ifndef LAU_GAUSS_INCOH_RES
#define LAU_GAUSS_INCOH_RES

#include "TString.h"

#include "LauAbsIncohRes.hh"
#include "LauComplex.hh"

class LauKinematics;


class LauGaussIncohRes : public LauAbsIncohRes {

	public:
		//! Constructor
		/*!
			\param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] daughters the daughter particles
		*/
		LauGaussIncohRes(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

		//! Destructor	
		virtual ~LauGaussIncohRes();

		//! Initialise the model
		virtual void initialise();

		//! Get intensity factor
		/*!
			/param [in] kinematics kinematic parameters of the parent and daughter particles
			/return the intensity factor
		*/	
		virtual Double_t intensityFactor(const LauKinematics* kinematics);

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::GaussIncoh;}

		//! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
		/*!
		    \return floating parameters of the resonance
		*/
		virtual const std::vector<LauParameter*>& getFloatingParameters();

	private:
		//! Copy constructor (not implemented)
		LauGaussIncohRes(const LauGaussIncohRes& rhs);

		//! Copy assignment operator (not implemented)
		LauGaussIncohRes& operator=(const LauGaussIncohRes& rhs);

		ClassDef(LauGaussIncohRes,0) // Gaussian incoherent resonance model
};

#endif
