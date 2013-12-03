
#include <cstdlib>

#include "TString.h"

#include "ResultsExtractor.hh"

int main(const int argc, const char** argv)
{
	Int_t nExpt(1);
	TString inputFileName("input-list.txt");
	TString outputFileName("output.root");
	TString treeName("fitResults");

	if (argc > 1) {
		nExpt = atoi(argv[1]);
	}
	if (argc > 2) {
		inputFileName = argv[2];
	}
	if (argc > 3) {
		outputFileName = argv[3];
	}
	if (argc > 4) {
		treeName = argv[4];
	}

	ResultsExtractor myExtractor(inputFileName,outputFileName,treeName);
	myExtractor.process(nExpt);

	return EXIT_SUCCESS;
}
