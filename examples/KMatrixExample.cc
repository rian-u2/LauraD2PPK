
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <vector>
#include <map>

#include "LauDaughters.hh"
#include "LauVetoes.hh"
#include "LauIsobarDynamics.hh"
#include "LauSimpleFitModel.hh"
#include "LauAbsCoeffSet.hh"
#include "LauCartesianCPCoeffSet.hh"
#include "LauEffModel.hh"

#include "TString.h"

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
	// ./KMatrixExample gen [nExpt = 1] [firstExpt = 0]
	// or
	// ./KMatrixExample fit <iFit> [nExpt = 1] [firstExpt = 0]
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

	// This defines the DP => decay is B0 -> pi+ pi- K_S0
	// Particle 1 = pi+
	// Particle 2 = pi-
	// Particle 3 = K_S0
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("B0", "pi+", "pi-", "K_S0", squareDP);

	LauVetoes* vetoes = new LauVetoes();
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);

	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);

	// Define the "S-wave" K-matrix propagator
	Int_t resPairInt = 3;
	Int_t nChannels = 5;
	Int_t nPoles = 5;
	Int_t KMatrixIndex = 1; // for S-wave, use only the first "row"

	// The defineKMatrixPropagator requires four arguments
	// name of propagator, parameter file, mass pair index (1,2,3) for "s" variable, number of channels, number of
	// mass poles and the row index defining the K-matrix state (e.g. index = 1 for the first row -> S-wave).
	sigModel->defineKMatrixPropagator("KMSWave", "LauKMatrixCoeff.dat", resPairInt, nChannels, nPoles, KMatrixIndex);

	// Now define the pole and "slowly-varying part" (SVP) amplitudes for this K-matrix.
	// Each part will have their own complex coefficients which can (should) be fitted.
	// The addKMatrixProd functions need: name of pole/SVP, name of propagator and the index 
	// number of the amplitude (from 1 to nPoles or nChannels)
	sigModel->addKMatrixProdPole("KMPole1", "KMSWave", 1);
	sigModel->addKMatrixProdPole("KMPole2", "KMSWave", 2);
	sigModel->addKMatrixProdPole("KMPole3", "KMSWave", 3);
	sigModel->addKMatrixProdPole("KMPole4", "KMSWave", 4);
	sigModel->addKMatrixProdPole("KMPole5", "KMSWave", 5);

	sigModel->addKMatrixProdSVP("KMSVP1", "KMSWave", 1);
	sigModel->addKMatrixProdSVP("KMSVP2", "KMSWave", 2);
	sigModel->addKMatrixProdSVP("KMSVP3", "KMSWave", 3);
	sigModel->addKMatrixProdSVP("KMSVP4", "KMSWave", 4);
	sigModel->addKMatrixProdSVP("KMSVP5", "KMSWave", 5);

	// Define another K-matrix propagator and its three poles. This uses another coefficient data file.
	// Note that the name of this propagator must be different from the previous one.
	Int_t nChannels2 = 3;
	Int_t nPoles2 = 3;  
	sigModel->defineKMatrixPropagator("KMatrix2", "LauKMatrixCoeff2.dat", resPairInt, nChannels2, nPoles2, KMatrixIndex);
	// Add three poles for this new K-matrix
	sigModel->addKMatrixProdPole("KMP1", "KMatrix2", 1);
	sigModel->addKMatrixProdPole("KMP2", "KMatrix2", 2);
	sigModel->addKMatrixProdPole("KMP3", "KMatrix2", 3);

	//sigModel->addKMatrixProdSVP("KMS1", "KMatrix2", 1);
	//sigModel->addKMatrixProdSVP("KMS2", "KMatrix2", 1);  
	//sigModel->addKMatrixProdSVP("KMS3", "KMatrix2", 1);  

	// Add a normal relativistic BW
	sigModel->addResonance("rho0(770)", 3, LauAbsResonance::RelBW);

	sigModel->setASqMaxValue(3.0);

	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	std::vector<LauAbsCoeffSet*> coeffset;

	// Define the coefficients for the K-matrix amplitudes defined above ("beta" and "f" production coeffs)
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole1",   0.1822, -0.9120,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole2",   -1.017, -0.389,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole3",   -2.367, 0.503,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole4",   -0.008, .916,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole5",   0.00, 0.00,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));

	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP1",   0.220, 0.763,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP2",   0.890, 1.315,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP3",   -0.973, 3.931,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP4",   0.502, 2.510,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP5",   0.00, 0.00,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));

	coeffset.push_back(new LauCartesianCPCoeffSet("KMP1",   1.5822, 0.5120,  0.0, 0.0, kFALSE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMP2",   1.2822, -0.2120,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMP3",   1.2822, 0.3120,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));

	//coeffset.push_back(new LauCartesianCPCoeffSet("KMS1",   1.5822, 0.5120,  0.0, 0.0, kFALSE, kTRUE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMS2",   1.2822, -0.2120,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMS3",   1.2822, 0.3120,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));

	// Define the amplitude for the normal rho resonance
	coeffset.push_back(new LauCartesianCPCoeffSet("rho0(770)",  2.00, 0.00,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));

	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	Double_t nSigEvents = 5000;
	Bool_t fixSigEvents = kTRUE;
	LauParameter* nSig = new LauParameter("signalEvents",nSigEvents,-2.0*nSigEvents,2.0*nSigEvents,fixSigEvents);
	fitModel->setNSigEvents(nSig);
	fitModel->setNExpts(nExpt, firstExpt);

	// Switch on/off calculation of asymmetric errors.
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	// Switch on/off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(kFALSE);

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
