
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauString.cc
    \brief File containing implementation of LauString class.
*/

#include "LauString.hh"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

LauString::LauString() : theString_("")
{
}

LauString::LauString(const char* s) : theString_(s)
{
}

LauString::LauString(const std::string& s) : theString_(s)
{
}

LauString::LauString(const TString& s) : theString_(s.Data())
{
}

LauString::~LauString() 
{
}

void LauString::addInteger(int integer)
{
	std::ostringstream o;
	o << integer;
	theString_ += o.str();
}

void LauString::addDouble(double value)
{
	std::ostringstream o;
	o << value;
	theString_ += o.str();
}

LauString LauString::operator += (int integer)
{
	this->addInteger(integer);
	return (*this);
}

LauString LauString::operator += (double value)
{
	this->addDouble(value);
	return (*this);
}

LauString LauString::operator += (const char* text)
{
	this->addText(text);
	return (*this);
}

LauString LauString::operator += (const std::string &text)
{
	this->addText(text);
	return (*this);
}

LauString LauString::operator += (const TString &text)
{
	this->addText(text.Data());
	return (*this);
}

std::vector<std::string> LauString::split(const LauString& splitter) const
{
	std::string splitString = splitter.getString();
	std::vector<std::string> result = this->split(splitString);
	return result;
}

std::vector<std::string> LauString::split(const std::string& splitter) const
{
	// Code from STLplus
	std::vector<std::string> result;

	if (!theString_.empty() && !splitter.empty()) {

		for (std::string::size_type offset = 0;;) {

			std::string::size_type found = theString_.find(splitter, offset);

			if (found != std::string::npos) {
				std::string tmpString = theString_.substr(offset, found-offset);
				if (tmpString.size() > 0) {result.push_back(tmpString);}
				offset = found + splitter.size();
			} else {
				std::string tmpString = theString_.substr(offset, theString_.size()-offset);
				if (tmpString.size() > 0) {result.push_back(tmpString);}
				break;
			}
		}
	}

	return result;
}
