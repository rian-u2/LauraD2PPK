
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

int main(const int argc, const  char ** argv) {

	// Generate K-matrix amplitude distribution across the DP
	LauDaughters* daughters = new LauDaughters("D+", "pi+", "pi+", "pi-", kFALSE);
	LauVetoes* vetoes = new LauVetoes();
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);

	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);

	// Define the "S-wave" K-matrix propagator
	Int_t nChannels = 5;
	Int_t nPoles = 5;
	Int_t resPairInt = 1;
	Int_t KMatrixIndex = 1; // for S-wave
	sigModel->defineKMatrixPropagator("KMSWave", "FOCUSD3pi.dat", resPairInt, nChannels, nPoles, KMatrixIndex);
	// Now define the pole and "slowly-varying part" (SVP) amplitudes for the K-matrix.
	// Each part will have their own complex coefficients which can (should) be fitted.
	sigModel->addKMatrixProdPole("KMPole1", "KMSWave", 1);
	sigModel->addKMatrixProdPole("KMPole2", "KMSWave", 2);
	sigModel->addKMatrixProdPole("KMPole3", "KMSWave", 3);
	//sigModel->addKMatrixProdPole("KMPole4", "KMSWave", 4);
	//sigModel->addKMatrixProdPole("KMPole5", "KMSWave", 5);

	sigModel->addKMatrixProdSVP("KMSVP1", "KMSWave", 1);
	sigModel->addKMatrixProdSVP("KMSVP2", "KMSWave", 2);
	//sigModel->addKMatrixProdSVP("KMSVP3", "KMSWave", 3);
	//sigModel->addKMatrixProdSVP("KMSVP4", "KMSWave", 4);
	//sigModel->addKMatrixProdSVP("KMSVP5", "KMSWave", 5);

	sigModel->addResonance("rho0(770)", 1, LauAbsResonance::RelBW);
	sigModel->addResonance("f_2(1270)", 1, LauAbsResonance::RelBW);

	sigModel->setASqMaxValue(10.0);

	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	std::vector<LauAbsCoeffSet*> coeffset;

	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole1",   0.85, -0.55,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole2",   -1.10, -0.30,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMPole3",   -0.84, 0.35,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMPole4",   -0.004, .46,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMPole5",   0.00, 0.00,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));

	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP1",   0.230, 0.352,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP2",   0.330, 0.42,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP3",   -0.48, 1.25,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP4",   0.30, 1.32,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));
	//coeffset.push_back(new LauCartesianCPCoeffSet("KMSVP5",   0.00, 0.00,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));

	coeffset.push_back(new LauCartesianCPCoeffSet("rho0(770)",  1.0, 0.00,  0.0, 0.0, kTRUE, kTRUE, kTRUE, kTRUE));
	coeffset.push_back(new LauCartesianCPCoeffSet("f_2(1270)",  0.45, 0.35,  0.0, 0.0, kFALSE, kFALSE, kTRUE, kTRUE));

	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	Double_t nSigEvents = 20000;
	Bool_t fixSigEvents = kTRUE;
	Int_t nExpt = 1;
	Int_t firstExpt = 0;

	LauParameter * nSig = new LauParameter("signalEvents",nSigEvents,-2.0*nSigEvents,2.0*nSigEvents,fixSigEvents);
	fitModel->setNSigEvents(nSig);
	fitModel->setNExpts(nExpt, firstExpt);

	// Do not calculate asymmetric errors
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	// Switch off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(kFALSE);

	// Switch on Extended ML Fit option - only really use if Poisson smearing is also enabled
	fitModel->doEMLFit(kFALSE);

	int mode(0);
	if (argc > 1) {mode = atoi(argv[1]);}

	// Run
	if (mode == 0) {
		fitModel->run("gen", "gen.root", "fitTree", "dummy.root", "genResults");
	} else {
		//fitModel->compareFitData(1);
		fitModel->run("fit", "gen.root", "fitTree", "fit.root", "fitResults");
	}

}
