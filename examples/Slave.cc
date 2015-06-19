
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
#include "LauRandom.hh"
#include "LauVetoes.hh"

void usage( std::ostream& out, const TString& progName )
{
	out<<"Usage:\n";
	out<<progName<<" gen <category = DD or LL> [nExpt = 1] [firstExpt = 0]\n";
	out<<"or\n";
	out<<progName<<" fit <category = DD or LL> <iFit> <port> [nExpt = 1] [firstExpt = 0]"<<std::endl;
}

int main( int argc, char** argv )
{
	// Process command-line arguments
	// Usage:
	// ./Slave gen <category = DD or LL> [nExpt = 1] [firstExpt = 0]
	// or
	// ./Slave fit <category = DD or LL> <iFit> <port> [nExpt = 1] [firstExpt = 0]
	if ( argc < 3 ) {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	TString command = argv[1];
	command.ToLower();
	TString category = argv[2];
	if ( category != "DD" && category != "LL" ) {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}
	Int_t iFit(0);
	UInt_t port(5000);
	Int_t nExpt(1);
	Int_t firstExpt(0);
	if ( command == "gen" ) {
		if ( argc > 3 ) {
			nExpt = atoi( argv[3] );
			if ( argc > 4 ) {
				firstExpt = atoi( argv[4] );
			}
		}
	} else if ( command == "fit" ) {
		if ( argc < 5 ) {
			usage( std::cerr, argv[0] );
			return EXIT_FAILURE;
		}
		iFit = atoi( argv[3] );
		port = atoi( argv[4] );
		if ( argc > 5 ) {
			nExpt = atoi( argv[5] );
			if ( argc > 6 ) {
				firstExpt = atoi( argv[6] );
			}
		}
	} else {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	LauRandom::setSeed(0);

	// If you want to use square DP histograms for efficiency,
	// backgrounds or you just want the square DP co-ordinates
	// stored in the toy MC ntuple then set this to kTRUE
	Bool_t squareDP = kFALSE;

	// This defines the DP => decay is B0 -> pi0 pi0 K_S0
	// Particle 1 = pi0
	// Particle 2 = pi0
	// Particle 3 = KS_0
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("B0", "pi0", "pi0", "K_S0", squareDP);

	// Optionally apply some vetoes to the DP
	LauVetoes* vetoes = new LauVetoes();

	// Define the efficiency model (defaults to unity everywhere)
	// Can optionally provide a histogram to model variation over DP
	// (example syntax given in commented-out section)
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);
	//TFile *effHistFile = TFile::Open("histoFiles/efficiency.root", "read");
	//TH2* effHist = dynamic_cast<TH2*>(effHistFile->Get("effHist"));
	//Bool_t useInterpolation = kTRUE;
	//Bool_t fluctuateBins = kFALSE;
	//Bool_t useUpperHalf = kTRUE;
	//effModel->setEffHisto(effHist, useInterpolation, fluctuateBins, 0.0, 0.0, useUpperHalf, squareDP);

	// Create the isobar model
	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);
	LauAbsResonance* res(0);
	res = sigModel->addResonance("f_0(980)",    3, LauAbsResonance::Flatte); // resPairAmpInt = 3 => resonance mass is m12.
	res = sigModel->addResonance("f_2(1270)",   3, LauAbsResonance::RelBW);
	res = sigModel->addResonance("K*0(892)",    1, LauAbsResonance::RelBW);
	res->fixMass(kFALSE);
	res = sigModel->addResonance("K*0_0(1430)", 1, LauAbsResonance::LASS);

	// Reset the maximum signal DP ASq value
	// This will be automatically adjusted to avoid bias or extreme
	// inefficiency if you get the value wrong but best to set this by
	// hand once you've found the right value through some trial and
	// error.
	sigModel->setASqMaxValue(1.25);  

	TString integralsFileName("integ-");
	integralsFileName += category;
	integralsFileName += ".dat";
	sigModel->setIntFileName( integralsFileName );

	// Create the fit model
	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	// Create the complex coefficients for the isobar model
	// Here we're using the magnitude and phase form:
	// c_j = a_j exp(i*delta_j)
	std::vector<LauAbsCoeffSet*> coeffset;
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(980)",    1.00,  0.00,  kTRUE,  kTRUE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_2(1270)",   0.53,  1.39, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("K*0(892)",    0.87,  1.99, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("K*0_0(1430)", 1.17, -1.59, kFALSE, kFALSE) );
	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	// Set the signal yield and define whether it is fixed or floated
	TString sigEventsName = "signalEvents" + category;
	Double_t nSig(500.0);
	if ( category == "DD" ) {
		nSig = 750.0;
	}
	LauParameter * nSigEvents = new LauParameter(sigEventsName,nSig,-2.0*nSig,2.0*nSig,kFALSE);
	fitModel->setNSigEvents(nSigEvents);

	// Set the number of experiments to generate or fit and which
	// experiment to start with
	fitModel->setNExpts( nExpt, firstExpt );

	// Optionally load in continuum background DP model histogram
	// (example syntax given in commented-out section)
	std::vector<TString> bkgndNames(1);
	bkgndNames[0] = "comb" + category;
	fitModel->setBkgndClassNames( bkgndNames );
	Double_t nBkgnd = 1200.0;
	if ( category == "DD" ) {
		nBkgnd = 2500.0;
	}
	LauParameter* nBkgndEvents = new LauParameter(bkgndNames[0],nBkgnd,-2.0*nBkgnd,2.0*nBkgnd,kFALSE);
	fitModel->setNBkgndEvents( nBkgndEvents );
	//TString bkgndFileName("histoFiles/bkgndDPs.root");
	//TFile* bkgndFile = TFile::Open(bkgndFileName.Data(), "read");
	//TH2* bkgndDP = dynamic_cast<TH2*>(bkgndFile->Get("AllmTheta")); // m', theta'
	LauBkgndDPModel* bkgndModel = new LauBkgndDPModel(daughters, vetoes);
	//bkgndModel->setBkgndHisto(bkgndDP, useInterpolation, fluctuateBins, useUpperHalf, squareDP);
	fitModel->setBkgndDPModel( bkgndNames[0], bkgndModel );

	// Switch on/off calculation of asymmetric errors.
	//fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	// Switch on/off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(kTRUE);

	// Switch on/off Extended ML Fit option
	Bool_t emlFit = ( fitModel->nBkgndClasses() > 0 );
	fitModel->doEMLFit(emlFit);

	// Activate two-stage fit
	fitModel->twoStageFit(kTRUE);

	// Set the names of the files to read/write
	TString dataFile("gen-"); dataFile += category; dataFile += ".root";
	TString treeName("genResults");
	TString rootFileName("");
	TString tableFileName("");
	TString fitToyFileName("fitToyMC_");
	TString splotFileName("splot_");
	if (command == "fit") {
		rootFileName = "fit"; rootFileName += category; rootFileName += iFit;
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
	if ( command == "fit" ) {
		fitModel->runSlave( dataFile, treeName, rootFileName, tableFileName, "localhost", port );
	} else {
		fitModel->run( command, dataFile, treeName, rootFileName, tableFileName );
	}

	return EXIT_SUCCESS;
}
