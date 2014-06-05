
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPrint.hh
    \brief File containing declaration of LauPrint class.
*/

/*! \class LauPrint
    \brief Class to define various output print commands.

    Class to define various output print commands (for output tables etc..)
*/

#ifndef LAU_PRINT
#define LAU_PRINT

#include "Rtypes.h"

#include <iosfwd>


class LauPrint {

	public:
		//! Constructor
		LauPrint();

		//! Destructor
		virtual ~LauPrint();

		//! Method to choose the printing format to a specified level of precision
		/*!
		   \param [in,out] stream the output stream to be printed to
		   \param [in] value the double value to be printed
		*/
		void printFormat(std::ostream& stream, Double_t value) const;

	private:
		//! Copy constructor (not implemented)
		LauPrint(const LauPrint& rhs);

		//! Copy assignment operator (not implemented)
		LauPrint& operator=(const LauPrint& rhs);

		ClassDef(LauPrint,0)

};

#endif
