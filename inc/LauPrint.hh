
/*
Copyright 2004 University of Warwick

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
