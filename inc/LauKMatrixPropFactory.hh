
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixPropFactory.hh
    \brief File containing declaration of LauKMatrixPropFactory class.
*/

/*! \class LauKMatrixPropFactory
    \brief Factory class for the K-matrix propagators.

    Factory class for creating and storing K-matrix propagator objects.
*/

#ifndef LAU_KMATRIX_PROP_FACTORY
#define LAU_KMATRIX_PROP_FACTORY

class LauKMatrixPropagator;

#include "TString.h"
#include <map>

class LauKMatrixPropFactory {

	public:
		//! Destructor
		virtual ~LauKMatrixPropFactory();

		//! Get a static instance of this factory class. Only one is created per application.
		static LauKMatrixPropFactory* getInstance();

		//! Retrieve the propagator if it already exists, otherwise create one.
		/*!
		  \param [in] name name of the propagator
		  \param [in] paramFileName the parameter file
		  \param [in] resPairAmpInt the number of the daughter not produced by the resonance
		  \param [in] nChannels the number of channels
		  \param [in] nPoles the number of poles
		  \param [in] rowIndex this specifies which row of the propagator should be used when summing over the amplitude channels

		  \return the propagator
		 */
		LauKMatrixPropagator* getPropagator(const TString& name, const TString& paramFileName, 
				                    Int_t resPairAmpInt, Int_t nChannels,
				                    Int_t nPoles, Int_t rowIndex);

	protected:

		//! A typedef to define a map used to keep track of which propagators have been created.
		typedef std::map<TString, LauKMatrixPropagator*> KMatrixPropMap;

	private:
		//! Private constructor (to ensure the singleton nature of this class)
		LauKMatrixPropFactory();

		//! Copy constructor (not implemented)
		LauKMatrixPropFactory(const LauKMatrixPropFactory& rhs);

		//! Copy assignment operator (not implemented)
		LauKMatrixPropFactory& operator=(const LauKMatrixPropFactory& rhs);

		//! The singleton instance
		static LauKMatrixPropFactory* theFactory_;

		//! The map used to store the propagator information
		KMatrixPropMap map_;
};

#endif
