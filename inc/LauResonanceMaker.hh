
// Copyright University of Warwick 2004 - 2014.
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
    \brief Singleton factory class for creating resonances.

    Singleton factory class for creating resonances. Information records for all known resonances are stored within this class.
*/

#ifndef LAU_RESONANCE_MAKER
#define LAU_RESONANCE_MAKER

#include <iosfwd>
#include <vector>

#include "TString.h"

#include "LauAbsResonance.hh"

class LauDaughters;
class LauResonanceInfo;


class LauResonanceMaker {

	public:
		//! Get the factory instance
		static LauResonanceMaker& get();

		//! Create a resonance
		/*!
		    \param [in] daughters defines the Dalitz plot in which the resonance should be created
		    \param [in] resName the name of the resonant particle
		    \param [in] resPairAmpInt the index of the daughter not produced by the resonance
		    \param [in] resType the type of the resonance.
		    \return the resonance
		*/
		LauAbsResonance* getResonance(const LauDaughters* daughters, const TString& resName, const Int_t resPairAmpInt, const LauAbsResonance::LauResonanceModel resType);

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

		//! Print the information records, one per line, to the requested stream
		/*!
		    \param [in,out] stream the stream to which to print the info
		*/
		void printAll( ostream& stream ) const;

	protected:
		//! Create the list of known resonances
		void createResonanceVector();

	private:
		//! Constructor
		LauResonanceMaker();

		//! Destructor
		virtual ~LauResonanceMaker();

		//! Copy constructor (not inplemented)
		LauResonanceMaker( const LauResonanceMaker& other );

		//! Copy assignment (not implemented)
		LauResonanceMaker& operator=( const LauResonanceMaker& other );

		//! The singleton instance
		static LauResonanceMaker* resonanceMaker_;

		//! The number of known resonances
		UInt_t nResDefMax_;

		//! The known resonances
		std::vector<LauResonanceInfo*> resInfo_;

		ClassDef(LauResonanceMaker,0) // Kinematic routines
};

#endif
