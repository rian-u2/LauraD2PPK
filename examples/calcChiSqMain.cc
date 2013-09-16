
#include "CalcChiSq.hh"

#include "TString.h"

int main(const int argc, const char** argv)
{

	TString inputFile("chiSqInput.txt");

	if (argc > 1) {inputFile = TString(argv[1]);}

	CalcChiSq a(inputFile);

	//a.setVerbose(kTRUE);
	a.run();

	return 0;

}

