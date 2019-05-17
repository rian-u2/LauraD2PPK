
/*
Copyright 2013 University of Warwick

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

#include <iostream>

#include "TString.h"

#include "LauMergeDataFiles.hh"

int main(const int argc, const char** argv)
{
	if (argc < 3) {
		std::cerr<<"Usage: "<<argv[0]<<" <inputFileName1> <inputFileName2> [treeName] [outputFileName]"<<std::endl;
		return EXIT_FAILURE;
	}

	TString inputFileName1(argv[1]);
	TString inputFileName2(argv[2]);

	TString treeName("fitTree");
	if (argc > 3) {
		treeName = argv[3];
	}
	TString outputFileName("test.root");
	if (argc > 4) {
		outputFileName = argv[4];
	}

	LauMergeDataFiles myMerger(inputFileName1,inputFileName2,treeName);
	myMerger.process(outputFileName);

	return EXIT_SUCCESS;
}

