
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauParamFixed.hh
    \brief File containing declaration of LauParamFixed class.
*/

/*! \class LauParamFixed
    \brief Predicate to allow counting of the number of fixed parameters
*/

#ifndef LAU_PARAM_FIXED
#define LAU_PARAM_FIXED

#include "LauAbsRValue.hh"

class LauParamFixed {
	public:
		//! Predicate that check whether the parameter is fixed
		/*!
		  \param [in] par the LauParameter that holds the information about the parameter 
		  \return whether or not the parameter is fixed
		*/
		inline bool operator() (const LauAbsRValue* par) const {
			return par->fixed();
		}
};

#endif
