
#include <cstdlib>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH2.h"
#include "TString.h"
#include "TTree.h"

#include "LauSimpleFitModel.hh"
#include "LauBkgndDPModel.hh"
#include "LauDaughters.hh"
#include "LauEffModel.hh"
#include "LauIsobarDynamics.hh"
#include "LauMagPhaseCoeffSet.hh"
#include "LauVetoes.hh"

void usage( std::ostream& out, const char* progName )
{
	out<<"Usage:\n";
	out<<progName<<" gen [nExpt = 1] [firstExpt = 0]\n";
	out<<"or\n";
	out<<progName<<" fit <iFit> [nExpt = 1] [firstExpt = 0]"<<std::endl;
}

int main( int argc, char** argv )
{
	// Process command-line arguments
	// Usage:
	// ./GenFit3KS gen [nExpt = 1] [firstExpt = 0]
	// or
	// ./GenFit3KS fit <iFit> [nExpt = 1] [firstExpt = 0]
	if ( argc < 2 ) {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	TString command = argv[1];
	command.ToLower();
	Int_t iFit(0);
	Int_t nExpt(1);
	Int_t firstExpt(0);
	if ( command == "gen" ) {
		if ( argc > 2 ) {
			nExpt = atoi( argv[2] );
			if ( argc > 3 ) {
				firstExpt = atoi( argv[3] );
			}
		}
	} else if ( command == "fit" ) {
		if ( argc < 3 ) {
			usage( std::cerr, argv[0] );
			return EXIT_FAILURE;
		}
		iFit = atoi( argv[2] );
		if ( argc > 3 ) {
			nExpt = atoi( argv[3] );
			if ( argc > 4 ) {
				firstExpt = atoi( argv[4] );
			}
		}
	} else {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	// If you want to use square DP histograms for efficiency,
	// backgrounds or you just want the square DP co-ordinates
	// stored in the toy MC ntuple then set this to kTRUE
	Bool_t squareDP = kFALSE;

	// This defines the DP => decay is B0 -> KS KS KS
	// Particle 1 = KS
	// Particle 2 = KS
	// Particle 3 = KS
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("B0", "K_S0", "K_S0", "K_S0", squareDP);

	// Optionally apply some vetoes to the DP
	LauVetoes* vetoes = new LauVetoes();

	// Define the efficiency model (defaults to unity everywhere)
	// Can optionally provide a histogram to model variation over DP
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);

	// Create the isobar model
	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);
	//LauAbsResonance* reson(0);
	/*reson =*/ sigModel->addResonance("f_0(980)",     3, LauAbsResonance::Flatte);
	/*reson =*/ sigModel->addResonance("f_0(1710)",    3, LauAbsResonance::RelBW);
	/*reson =*/ sigModel->addResonance("f_2(2010)",    3, LauAbsResonance::RelBW);
	/*reson =*/ sigModel->addResonance("chi_c0",       3, LauAbsResonance::RelBW);

	// Reset the maximum signal DP ASq value
	// This will be automatically adjusted to avoid bias or extreme
	// inefficiency if you get the value wrong but best to set this by
	// hand once you've found the right value through some trial and
	// error.
	sigModel->setASqMaxValue(0.285);  

	// Create the fit model
	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	// Create the complex coefficients for the isobar model
	// Here we're using the magnitude and phase form:
	// c_j = a_j exp(i*delta_j)
	std::vector<LauAbsCoeffSet*> coeffset;
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(980)",    1.00,  0.00,  kTRUE,  kTRUE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(1710)",   0.40,  1.11, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_2(2010)",   0.45,  2.50, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("chi_c0",      0.40,  0.63, kFALSE, kFALSE) );
	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	// Set the signal yield and define whether it is fixed or floated
	LauParameter * nSigEvents = new LauParameter("nSigEvents",10000.0,-50000.0,50000.0,kFALSE);
	fitModel->setNSigEvents(nSigEvents);

	// Set the number of experiments to generate or fit and which
	// experiment to start with
	fitModel->setNExpts( nExpt, firstExpt );


	// Switch on/off calculation of asymmetric errors.
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	// Switch on/off Poissonian smearing of total number of events
	const Bool_t poissonSmear = ( fitModel->nBkgndClasses() > 0 );
	fitModel->doPoissonSmearing(poissonSmear);

	// Switch on/off Extended ML Fit option
	const Bool_t emlFit = ( fitModel->nBkgndClasses() > 0 );
	fitModel->doEMLFit(emlFit);

	// Set the names of the files to read/write
	TString dataFile("gen.root");
	TString treeName("genResults");
	TString rootFileName("");
	TString tableFileName("");
	TString fitToyFileName("fitToyMC_");
	TString splotFileName("splot_");
	if (command == "fit") {
		rootFileName = "fit"; rootFileName += iFit;
		rootFileName += "_expt_"; rootFileName += firstExpt;
		rootFileName += "-"; rootFileName += (firstExpt+nExpt-1);
		rootFileName += ".root";
		tableFileName = "fitResults_"; tableFileName += iFit;
		fitToyFileName += iFit;
		fitToyFileName += ".root";
		splotFileName += iFit;
		splotFileName += ".root";
	} else {
		rootFileName = "dummy.root";
		tableFileName = "genResults";
	}

	// Generate toy from the fitted parameters
	//fitModel->compareFitData(100, fitToyFileName);

	// Write out per-event likelihoods and sWeights
	//fitModel->writeSPlotData(splotFileName, "splot", kFALSE);

	// Execute the generation/fit
	fitModel->run( command, dataFile, treeName, rootFileName, tableFileName );

	return EXIT_SUCCESS;
}
