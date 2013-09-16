
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauString.hh
    \brief File containing declaration of LauString class.
*/

/*! \class LauString
    \brief Class for defining a string.
*/

#ifndef LAU_STRING_HH
#define LAU_STRING_HH

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "TString.h"

class LauString {

	public:

		//! Constructor for an empty string
		LauString();

		//! Constructor for a string using an array of characters
		/*!
		    \param [in] s string text
		*/
		LauString(const char* s);

		//! Constructor for a string using an STL string
		/*!
		    \param [in] s string text
		*/
		LauString(const std::string& s);

		//! Constructor for a string using a TString
		/*!
		    \param [in] s string text
		*/
		LauString(const TString& s);

		//! Destructor
		virtual ~LauString();

		//! Add an integer value to the string
		/*!
		    \param [in] integer integer to add
		*/
		void addInteger(int integer);

		//! Add a double value to the string
		/*!
		    \param [in] value double to add
		*/
		void addDouble(double value);

		//! Add some text from a character array
		/*!
		    \param [in] text text to add
		*/
		void addText(const char* text) {theString_ += text;}

		//! Add some text from an STL string
		/*!
		    \param [in] text text to add
		*/
		void addText(const std::string& text) {theString_ += text;}

		//! Add some text from a TString
		/*!
		    \param [in] text text to add
		*/
		void addText(const TString& text) {theString_ += text.Data();}

		//! Add an integer to the string
		/*!
		    \param [in] integer integer to add
		*/
		LauString operator += (int integer);

		//! Add a double to the string
		/*!
		    \param [in] value double to add
		*/
		LauString operator += (double value);

		//! Add some text from a character array
		/*!
		    \param [in] text text to add
		*/
		LauString operator += (const char* text);

		//! Add some text from an STL string
		/*!
		    \param [in] text text to add
		*/
		LauString operator += (const std::string& text);

		//! Add some text from a TString
		/*!
		    \param [in] text text to add
		*/
		LauString operator += (const TString& text);

		//! Retrieve the string as an STL string
		/*!
		    \return the string as an STL string
		*/
		std::string getString() const {return theString_;}

		//! Retrieve the string as an array of characters
		/*!
		    \return the string as an array of characters
		*/
		const char* getData() const {return theString_.c_str();}

		//! Retrieve the string as a TString
		/*!
		    \return the string as a TString
		*/
		TString getTString() const {return TString(theString_.c_str());}

		//! Retrieve the total size of the string
		/*!
		    \return the total size of the string
		*/
		int size() const {return theString_.size();}

		//! Split up a string according to a split string (e.g. ":" or " ")
		/*!
		    \param [in] splitter substring to split on
		*/
		std::vector<std::string> split(const std::string& splitter) const;

		//! Split up a string according to a split string (e.g. ":" or " ")
		/*!
		    \param [in] splitter substring to split on
		*/
		std::vector<std::string> split(const LauString& splitter) const;

	protected:

	private:
		//! The string
		std::string theString_;

};

#endif
