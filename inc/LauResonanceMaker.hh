
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauResonanceMaker.hh
    \brief File containing declaration of LauResonanceMaker class.
*/

/*! \class LauResonanceMaker
    \brief Class for creating resonances.

    Class for creating resonances. All known resonances are stored within this class.
*/

#ifndef LAU_RESONANCE_MAKER
#define LAU_RESONANCE_MAKER

#include "LauResonanceInfo.hh"
#include "TString.h"

#include <vector>

class LauAbsResonance;
class LauDaughters;


class LauResonanceMaker {

	public:
		//! Constructor
		/*!
		    \param [in] daughters the three daughters of the decay
		*/
		LauResonanceMaker(const LauDaughters* daughters);

		//! Destructor
		virtual ~LauResonanceMaker();

		//! Create a resonance
		/*!
		    \param [in] resName the name of the resonant particle
		    \param [in] resPairAmpInt the index of the daughter not produced by the resonance
		    \param [in] resType the type of the resonance.
		    Allowed types are: flatte, relbw, dabba, kappa, sigma, lass-bw, lass-nr, lass, gs, nrmodel, bellesymnr and bellenr.
		    \return the resonance
		*/
		LauAbsResonance* getResonance(const TString& resName, Int_t resPairAmpInt, const TString& resType);

		//! Retrieve the integer index for the specified resonance
		/*!
		    \param [in] name the name of the resonant particle
		    \return the index
		*/
		Int_t resTypeInt(const TString& name) const;

		//! Retrieve the number of defined resonances
		/*!
		    \return the number of defined resonances
		*/
		UInt_t getNResDefMax() const {return nResDefMax_;}

	protected:
		//! Create the list of known resonances
		void createResonanceVector();

	private:
		//! The number of known resonances
		UInt_t nResDefMax_;

		//! The daughters
		const LauDaughters* daughters_;

		//! The known resonances
		std::vector<LauResonanceInfo> resInfo_;

		ClassDef(LauResonanceMaker,0) // Kinematic routines
};

#endif
