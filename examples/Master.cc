
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

#include <cstdlib>
#include <iostream>

#include <vector>

#include "TFile.h"
#include "TRandom.h"
#include "TString.h"
#include "TSystem.h"

#include "LauSimFitMaster.hh"

void usage( std::ostream& out, const TString& progName )
{
	out<<"Usage:\n";
	out<<progName<<" <iFit> <nExpt> [firstExpt = 0] [numSlaves = 2] [port = 0]\n";
}

int main(const int argc, const  char ** argv)
{
	if ( argc < 3 ) {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	UInt_t iFit = atoi( argv[1] );
	UInt_t nExpt = atoi( argv[2] );
	UInt_t firstExpt = 0;
	UInt_t nSlaves = 2;
	UInt_t port = 0;

	Bool_t useAsymmErrors = kFALSE;
	Bool_t twoStageFit = kFALSE;

	if ( argc > 3 ) {
		firstExpt = atoi( argv[3] );

		if ( argc > 4 ) {
			nSlaves = atoi( argv[4] );

			if ( argc > 5 ) {
				port = atoi( argv[5] );
			}
		}
	}

	TString ntupleName = "master-ntuple-";
	ntupleName += iFit;
	ntupleName += ".root";

	LauSimFitMaster master( nSlaves, port );
	master.runSimFit( ntupleName, nExpt, firstExpt, useAsymmErrors, twoStageFit );

	return EXIT_SUCCESS;
}
