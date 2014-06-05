
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

void usage( std::ostream& out, const TString& progName )
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
	// ./GenFit3pi gen [nExpt = 1] [firstExpt = 0]
	// or
	// ./GenFit3pi fit <iFit> [nExpt = 1] [firstExpt = 0]
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

	// This defines the DP => decay is B+ -> K+ K+ K-
	// Particle 1 = K+
	// Particle 2 = K+
	// Particle 3 = K-
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("B+", "K+", "K+", "K-", squareDP);

	// Optionally apply some vetoes to the DP
	LauVetoes* vetoes = new LauVetoes();

	// Define the efficiency model (defaults to unity everywhere)
	// Can optionally provide a histogram to model variation over DP
	// (example syntax given in commented-out section)
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);
	//TFile *effHistFile = TFile::Open("histoFiles/effHistos.root", "read");
	//TH2* effHist = dynamic_cast<TH2*>(effHistFile->Get("effHist"));
	//Bool_t useInterpolation = kTRUE;
	//Bool_t fluctuateBins = kFALSE;
	//Bool_t useUpperHalf = kTRUE;
	//effModel->setEffHisto(effHist, useInterpolation, fluctuateBins, 0.0, 0.0, useUpperHalf, squareDP);

	// Create the isobar model
	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);

	// Add various components to the isobar model,
	// optionally allowing the masses and width to float in the fit
	LauAbsResonance* res(0);

	//addResonance arguments: resName, resPairAmpInt, resType
	res = sigModel->addResonance("phi(1020)",   1, LauAbsResonance::RelBW);
	//changeResonance arguments: newMass, newWidth, newSpin
	res->changeResonance(1.019, 0.0044, -1);
	res->fixMass(kFALSE);
	res->fixWidth(kFALSE);

	res = sigModel->addResonance("f'_2(1525)",  1, LauAbsResonance::RelBW);
	res->fixMass(kFALSE);
	res->fixWidth(kFALSE);

	res = sigModel->addResonance("NonReson",   0, LauAbsResonance::FlatNR);

	// Reset the maximum signal DP ASq value
	// This will be automatically adjusted to avoid bias or extreme
	// inefficiency if you get the value wrong but best to set this by
	// hand once you've found the right value through some trial and
	// error.
	sigModel->setASqMaxValue(16.4);  

	// Create the fit model
	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	// Create the complex coefficients for the isobar model
	// Here we're using the magnitude and phase form:
	// c_j = a_j exp(i*delta_j)
	std::vector<LauAbsCoeffSet*> coeffset;
	coeffset.push_back( new LauMagPhaseCoeffSet("phi(1020)",  1.0, 0.0,  kTRUE,  kTRUE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f'_2(1525)", 1.0, 0.0, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("NonReson",   1.0, 0.0, kFALSE, kFALSE) );

	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	// Set the signal yield and define whether it is fixed or floated
	Int_t nSigEvents = 5000;
	Bool_t fixNSigEvents = kFALSE;
	LauParameter * signalEvents = new LauParameter("signalEvents", nSigEvents, -1.0*nSigEvents, 2.0*nSigEvents, fixNSigEvents);
	fitModel->setNSigEvents(signalEvents);

	// Set the number of experiments to generate or fit and which
	// experiment to start with
	fitModel->setNExpts( nExpt, firstExpt );

	// Switch on/off calculation of asymmetric errors.
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kFALSE);

	// Switch on/off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(kTRUE);

	// Switch on/off Extended ML Fit option
	Bool_t emlFit = ( fitModel->nBkgndClasses() > 0 );
	fitModel->doEMLFit(emlFit);

	// Switch on the two-stage fit (for the resonance parameters)
	fitModel->twoStageFit(kTRUE);

	TString dataFile("data.root");

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
	//fitModel->compareFitData(10, fitToyFileName);

	// Write out per-event likelihoods and sWeights
	//fitModel->writeSPlotData(splotFileName, "splot", kFALSE);

	// Execute the generation/fit
	fitModel->run( command, dataFile, treeName, rootFileName, tableFileName );

	return EXIT_SUCCESS;
}
