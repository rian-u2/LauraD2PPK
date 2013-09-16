
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixPropFactory.cc
    \brief File containing implementation of LauKMatrixPropFactory class.
*/

// Class for storing K-matrix propagator objects
// using the factory method.

#include "LauKMatrixPropFactory.hh"
#include "LauKMatrixPropagator.hh"

#include <iostream>
using std::cout;
using std::endl;

// the singleton instance
LauKMatrixPropFactory* LauKMatrixPropFactory::theFactory_ = 0;

LauKMatrixPropFactory::LauKMatrixPropFactory()
{
	// Constructor
	map_.clear();
}

LauKMatrixPropFactory::~LauKMatrixPropFactory() 
{
	// Destructor
	KMatrixPropMap::iterator iter;
	for (iter = map_.begin(); iter != map_.end(); ++iter) {
		LauKMatrixPropagator* thePropagator = iter->second;
		delete thePropagator;
	}
	map_.clear();
}

LauKMatrixPropFactory* LauKMatrixPropFactory::getInstance()
{
	if (theFactory_ == 0) {
		theFactory_ = new LauKMatrixPropFactory();
	}
	return theFactory_;
}

LauKMatrixPropagator* LauKMatrixPropFactory::getPropagator(const TString& name, const TString& paramFileName, 
		                                           Int_t resPairAmpInt, Int_t nChannels, 
		                                           Int_t nPoles, Int_t rowIndex)
{
	LauKMatrixPropagator* thePropagator(0);

	KMatrixPropMap::iterator iter = map_.find(name);

	if ( iter != map_.end() ) {
		// We have already made this propagator
		thePropagator = iter->second;
	} else {
		// The propagator does not exist. Create it and store it in the map.
		thePropagator = new LauKMatrixPropagator(name, paramFileName, resPairAmpInt, 
				                         nChannels, nPoles, rowIndex);
		map_[name] = thePropagator;
	}

	return thePropagator;
}

