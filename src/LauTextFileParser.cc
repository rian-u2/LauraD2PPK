
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauTextFileParser.cc
    \brief File containing implementation of LauTextFileParser class.
*/

// Class for defining strings that can also handle numbers
// Useful for writing lines of output text that has a combination of
// words and numbers

#include "LauTextFileParser.hh"
#include "LauString.hh"

#include <fstream>

using std::cout;
using std::cerr;
using std::endl;

LauTextFileParser::LauTextFileParser(const char* s) :
	theFile_(s),
	totalLines_(0),
	lineNumber_(0)
{
}

LauTextFileParser::LauTextFileParser(const std::string& s) :
	theFile_(s),
	totalLines_(0),
	lineNumber_(0)
{
}

LauTextFileParser::LauTextFileParser(const TString& s) :
	theFile_(s.Data()),
	totalLines_(0),
	lineNumber_(0)
{
}

LauTextFileParser::~LauTextFileParser() 
{
	LineMap::iterator mapIter;
	for (mapIter = lineMap_.begin(); mapIter != lineMap_.end(); ++mapIter) {
		std::vector<std::string> line = mapIter->second;
		line.clear();
	}
	lineMap_.clear();
}

void LauTextFileParser::processFile()
{
	// Read the input file and store each (non-comment) line in the internal map.
	// Store the strings/numbers from each line in a vector, using a whitespace
	// separator to get each value.

	std::ifstream getData(theFile_.c_str());

	std::string whiteSpace(" ");
	int lineNo(0);

	cout<<"Processing input file "<<theFile_<<endl;

	// Loop while the input file is readable
	while (getData.good()) {

		if (getData.peek() == '\n') {

			// Finish reading line
			char c;
			getData.get(c);

			// Stop while loop if we have reached the end of the file
			if (getData.eof()) {break;}

		} else if (getData.peek() == '#') {

			// Skip comment line
			getData.ignore(1000, '\n');
			getData.putback('\n');

			// Stop while loop if we have reached the end of the file
			if (getData.eof()) {break;}

		} else {

			// Read data line
			char line[100];
			getData.getline(line, 100);

			// Stop while loop if we have reached the end of the file
			if (getData.eof()) {break;}

			LauString lineString(line);
			// Split up the line according to white spaces
			std::vector<std::string> lineVect = lineString.split(whiteSpace);

			// Store this line in the internal map
			lineMap_[lineNo] = lineVect;
			lineNo++;

		}

	}

	totalLines_ = lineNo;
	cout<<"Finished storing "<<totalLines_<<" lines from "<<theFile_<<endl;
}

std::vector<std::string> LauTextFileParser::getNextLine()
{
	// Get the next line of white-space separated strings/numbers
	++lineNumber_;

	std::vector<std::string> theLine = this->getLine(lineNumber_);
	return theLine;
}

std::vector<std::string> LauTextFileParser::getLine(int lineNo)
{
	// Retrieve the vector of white-space separated strings/numbers
	// for the given (non-commented) line number
	std::vector<std::string> line;

	LineMap::iterator mapIter = lineMap_.find(lineNo-1);
	if (mapIter != lineMap_.end()) {
		line = mapIter->second;
	}

	return line;
}

