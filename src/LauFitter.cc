
/*
Copyright 2005 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauFitter.cc
    \brief File containing implementation of LauFitter methods.
*/

#include <iostream>

#include "LauFitter.hh"
#include "LauAbsFitter.hh"
#include "LauMinuit.hh"


LauAbsFitter* LauFitter::theInstance_ = 0;
LauFitter::Type LauFitter::fitterType_ = LauFitter::Minuit;

ClassImp(LauFitter)

void LauFitter::setFitterType( Type type )
{
	if ( theInstance_ != 0 ) {
		std::cerr << "ERROR in LauFitter::setFitterType : The fitter has already been created, cannot change the type now." << std::endl;
		return;
	}

	fitterType_ = type;
}

LauAbsFitter* LauFitter::fitter()
{
	// Returns a pointer to a singleton LauAbsFitter object.
	// Creates the object the first time it is called.

	if ( theInstance_ == 0 ) {
		if ( fitterType_ == Minuit ) {
			theInstance_ = new LauMinuit();
		}
	}

	return theInstance_;
}

