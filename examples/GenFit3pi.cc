
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

	// This defines the DP => decay is B+ -> pi+ pi+ pi-
	// Particle 1 = pi+
	// Particle 2 = pi+
	// Particle 3 = pi-
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("B+", "pi+", "pi+", "pi-", squareDP);

	// Optionally apply some vetoes to the DP
	LauVetoes* vetoes = new LauVetoes();
	//Double_t DMin = 1.70;
	//Double_t DMax = 1.925;
	//Double_t JpsiMin = 3.051;
	//Double_t JpsiMax = 3.222;
	//Double_t psi2SMin = 3.676;
	//Double_t psi2SMax = 3.866;
	//vetoes->addMassVeto(2, DMin, DMax); // D0 veto, m13
	//vetoes->addMassVeto(2, JpsiMin, JpsiMax); // J/psi veto, m13
	//vetoes->addMassVeto(2, psi2SMin, psi2SMax); // psi(2S) veto, m13
	//vetoes->addMassVeto(1, DMin, DMax); // D0 veto, m23
	//vetoes->addMassVeto(1, JpsiMin, JpsiMax); // J/psi veto, m23
	//vetoes->addMassVeto(1, psi2SMin, psi2SMax); // psi(2S) veto, m23

	// Define the efficiency model (defaults to unity everywhere)
	// Can optionally provide a histogram to model variation over DP
	// (example syntax given in commented-out section)
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);
	//TFile *effHistFile = TFile::Open("histoFiles/B3piNRDPEff.root", "read");
	//TH2* effHist = dynamic_cast<TH2*>(effHistFile->Get("effHist"));
	//Bool_t useInterpolation = kTRUE;
	//Bool_t fluctuateBins = kFALSE;
	//Bool_t useUpperHalf = kTRUE;
	//effModel->setEffHisto(effHist, useInterpolation, fluctuateBins, 0.0, 0.0, useUpperHalf, squareDP);

	// Create the isobar model
	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);
	sigModel->addResonance("rho0(770)",  1, "RelBW"); // resPairAmpInt = 1 => resonance mass is m23.
	sigModel->addResonance("rho0(1450)", 1, "RelBW");
	sigModel->addResonance("f_0(980)",   1, "Flatte");
	sigModel->addResonance("f_2(1270)",  1, "RelBW");
	sigModel->addResonance("NonReson",   0);

	// Reset the maximum signal DP ASq value
	// This will be automatically adjusted to avoid bias or extreme
	// inefficiency if you get the value wrong but best to set this by
	// hand once you've found the right value through some trial and
	// error.
	sigModel->setASqMaxValue(0.27);  

	// Create the fit model
	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	// Create the complex coefficients for the isobar model
	// Here we're using the magnitude and phase form:
	// c_j = a_j exp(i*delta_j)
	std::vector<LauAbsCoeffSet*> coeffset;
	coeffset.push_back( new LauMagPhaseCoeffSet("rho0(770)",  1.00,  0.00,  kTRUE,  kTRUE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("rho0(1450)", 0.37,  1.99, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(980)",   0.27, -1.59, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_2(1270)",  0.53,  1.39, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("NonReson",   0.54, -0.84, kFALSE, kFALSE) );
	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	// Set the signal yield and define whether it is fixed or floated
	LauParameter * nSigEvents = new LauParameter("nSigEvents",500.0,-1000.0,1000.0,kFALSE);
	fitModel->setNSigEvents(nSigEvents);

	// Set the number of experiments to generate or fit and which
	// experiment to start with
	fitModel->setNExpts( nExpt, firstExpt );

	// Optionally load in continuum background DP model histogram
	// (example syntax given in commented-out section)
	//std::vector<TString> bkgndNames(1);
	//bkgndNames[0] = "qqbar";
	//LauParameter* nBkgndEvents = new LauParameter("qqbar",500.0,-1000.0,1000.0,kFALSE);
	//fitModel->setBkgndClassNames( bkgndNames );
	//fitModel->setNBkgndEvents( *nBkgndEvents );
	//TString qqFileName("histoFiles/offResDP.root");
	//TFile* qqFile = TFile::Open(qqFileName.Data(), "read");
	//TH2* qqDP = dynamic_cast<TH2*>(qqFile->Get("AllmTheta")); // m', theta'
	//LauBkgndDPModel* qqbarModel = new LauBkgndDPModel(daughters, vetoes);
	//qqbarModel->setBkgndHisto(qqDP, useInterpolation, fluctuateBins, useUpperHalf, squareDP);
	//fitModel->setBkgndModel( "qqbar", qqbarModel );

	// Switch on/off calculation of asymmetric errors.
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	// Switch on/off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(kTRUE);

	// Switch on/off Extended ML Fit option
	Bool_t emlFit = ( fitModel->nBkgndClasses() > 0 );
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
