
#include <iostream>

#include "TString.h"

#include "MergeDataFiles.hh"

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

	MergeDataFiles myMerger(inputFileName1,inputFileName2,treeName);
	myMerger.process(outputFileName);

	return EXIT_SUCCESS;
}

