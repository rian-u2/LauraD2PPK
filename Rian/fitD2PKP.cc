/*
Copyright 2005 University of Warwick

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
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TH2.h"
#include "TString.h"
#include "TTree.h"
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "LauSimpleFitModel.hh"
#include "LauBkgndDPModel.hh"
#include "LauDaughters.hh"
#include "LauEffModel.hh"
#include "LauIsobarDynamics.hh"
#include "LauMagPhaseCoeffSet.hh"
#include "LauResonanceMaker.hh"
#include "LauVetoes.hh"

// Variável global para armazenar eventos problemáticos
std::vector<Int_t> problematicEvents;

void plotSH(Int_t iFit) {

    TString fname, imgHname, imgLname;

	double M_D = 1.86966;
    double M_K = 0.49368;
    double M_P = 0.13957;

    double s13_min = (M_P + M_P)*(M_P + M_P);
    double s13_max = (M_D - M_K)*(M_D - M_K);
    double s23_min = (M_P + M_K)*(M_P + M_K);
    double s23_max = (M_D - M_P)*(M_D - M_P);

    // Open the ROOT files
    // TFile *file1 = TFile::Open("/home/oryan/laura/Rian/data/entries.root");
	TFile *file1 = TFile::Open("/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v34.root");
    fname = "fitDpipiK_"; fname += iFit; fname += "_expt_0-0.root";
    TFile *file2 = TFile::Open(fname); // Use a single file for both fits

    // Access trees A and B
    TTree *treeA = (TTree*)file1->Get("DecayTree");
    TTree *treeB = (TTree*)file2->Get("genResults");

    // Create histograms for the variables
    TH1F *histA1 = new TH1F("histA1", "m13Sq", 100, s13_min, s13_max); // For plotL
    TH1F *histB1 = new TH1F("histB1", "Fitted Histogram from Tree B", 100, s13_min, s13_max); // For plotL

    TH1F *histA2 = new TH1F("histA2", "m23Sq", 100, s23_min, s23_max); // For plotH
    TH1F *histB2 = new TH1F("histB2", "Fitted Histogram from Tree B", 100, s23_min, s23_max); // For plotH

    histA1->SetStats(0);
    histA2->SetStats(0);

    // Fill histograms with data from trees
    treeA->Draw("m13Sq>>histA1");
    treeB->Draw("m13Sq>>histB1"); // Assuming you will use the same file for the different fits

    treeA->Draw("m23Sq>>histA2");
    treeB->Draw("m23Sq>>histB2"); // Same file, different fit

    // Create canvases to draw the histograms
    TCanvas *c1 = new TCanvas("c1", "sLow vs Fitted Histogram", 850, 600);
	
    histA1->SetMinimum(0); // Set the minimum Y-axis value (adjust as needed)
    histA1->SetMaximum(30000); // Set the maximum Y-axis value (adjust as needed)
    histA1->SetFillColor(kBlue - 10);
    histA1->Draw();
    histB1->SetLineColor(kRed);
    histB1->SetLineWidth(2);
    histB1->Draw("SAME HIST");
    TLegend *legend1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend1->AddEntry(histA1, "dados", "f");
    legend1->AddEntry(histB1, " MC (Fit 1)", "l");
    legend1->Draw();
    histA1->GetXaxis()->SetTitle("s13");
    histA1->GetYaxis()->SetTitle("Counts");
    c1->Update();
    
    imgLname = "s13_"; imgLname += iFit; imgLname += ".png";

    c1->SaveAs(imgLname);


    TCanvas *c2 = new TCanvas("c2", "sHigh vs. Fitted Histogram", 850, 600);
    histA2->SetMinimum(0); // Set the minimum Y-axis value (adjust as needed)
    histA2->SetMaximum(18500); // Set the maximum Y-axis value (adjust as needed)
    histA2->SetFillColor(kBlue - 10);
    histA2->Draw();
    histB2->SetLineColor(kRed);
    histB2->SetLineWidth(2);
    histB2->Draw("SAME HIST");
    TLegend *legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend2->AddEntry(histA2, "dados", "f");
    legend2->AddEntry(histB2, " MC (Fit 2)", "l");
    legend2->Draw();
    histA2->GetXaxis()->SetTitle("s23");
    histA2->GetYaxis()->SetTitle("Counts");
    c2->Update();
    
    imgHname = "s23_"; imgHname += iFit; imgHname += ".png";

    c2->SaveAs(imgHname);

    // Close the ROOT files
    file1->Close();
    file2->Close();
}


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
	// if ( argc < 2 ) {
	// 	usage( std::cerr, argv[0] );
	// 	return EXIT_FAILURE;
	// }

	// TString command = argv[1];
	// command.ToLower();
	// Int_t iFit(0);
	// Int_t nExpt(1);
	// Int_t firstExpt(0);
	// if ( command == "gen" ) {
	// 	if ( argc > 2 ) {
	// 		nExpt = atoi( argv[2] );
	// 		if ( argc > 3 ) {
	// 			firstExpt = atoi( argv[3] );
	// 		}
	// 	}
	// } else if ( command == "fit" ) {
	// 	if ( argc < 3 ) {
	// 		usage( std::cerr, argv[0] );
	// 		return EXIT_FAILURE;
	// 	}
	// 	iFit = atoi( argv[2] );
	// 	if ( argc > 3 ) {
	// 		nExpt = atoi( argv[3] );
	// 		if ( argc > 4 ) {
	// 			firstExpt = atoi( argv[4] );
	// 		}
	// 	}
	// } else {
	// 	usage( std::cerr, argv[0] );
	// 	return EXIT_FAILURE;
	// }




	// Verifica o número mínimo de argumentos
    if (argc < 2) {
        usage(std::cerr, argv[0]);
        return EXIT_FAILURE;
    }

    TString command = argv[1];
    command.ToLower();

    // Variáveis para o comando "fit"
    TString dataFile;  // Caminho do arquivo ROOT
    Int_t iFit = 0;    // Índice do ajuste
    Int_t nExpt = 1;   // Número de experimentos
    Int_t firstExpt = 0; // Índice do primeiro experimento

    // Processa os argumentos de linha de comando
    if (command == "gen") {
        // Comando "gen": ./fitD2PKP gen [nExpt] [firstExpt]
        if (argc > 2) {
            nExpt = atoi(argv[2]);
            if (argc > 3) {
                firstExpt = atoi(argv[3]);
            }
        }
    } else if (command == "fit") {
        // Comando "fit": ./fitD2PKP fit <arquivo.root> <iFit> [nExpt] [firstExpt]
        if (argc < 3) {
            std::cerr << "Uso: " << argv[0] << " fit <arquivo.root> <iFit> [nExpt] [firstExpt]" << std::endl;
            return EXIT_FAILURE;
        }
        dataFile = argv[2];  // Caminho do arquivo ROOT
        iFit = atoi(argv[3]); // Índice do ajuste
        if (argc > 4) {
            nExpt = atoi(argv[4]);
            if (argc > 5) {
                firstExpt = atoi(argv[5]);
            }
        }
    } else {
        // Comando inválido
        usage(std::cerr, argv[0]);
        return EXIT_FAILURE;
    }

	// If you want to use square DP histograms for efficiency,
	// backgrounds or you just want the square DP co-ordinates
	// stored in the toy MC ntuple then set this to kTRUE
	Bool_t squareDP = kFALSE;

	// This defines the DP => decay is D+ -> pi+ pi+ k-
	// Particle 1 = pi+
	// Particle 2 = pi+
	// Particle 3 = k-
	// The DP is defined in terms of m13Sq and m23Sq
	LauDaughters* daughters = new LauDaughters("D+", "pi+", "K+", "pi-", squareDP);

	// Optionally apply some vetoes to the DP
	// (example syntax given but commented-out)
	LauVetoes* vetoes = new LauVetoes();

	//Double_t DMin = 1.70;
	//Double_t DMax = 1.925;
	//Double_t JpsiMin = 3.051;
	//Double_t JpsiMax = 3.222;
	//Double_t psi2SMin = 3.676;
	//Double_t psi2SMax = 3.866;
	//vetoes->addMassVeto(1, DMin, DMax); // D0 veto, m23 (and automatically m13)
	//vetoes->addMassVeto(1, JpsiMin, JpsiMax); // J/psi veto, m23 (and automatically m13)
	//vetoes->addMassVeto(1, psi2SMin, psi2SMax); // psi(2S) veto, m23 (and automatically m13)

	Double_t minMass = ((0.4976-0.01)*(0.4976-0.01));
	Double_t maxMass = ((0.4976+0.01)*(0.4976+0.01));
	vetoes->addMassVeto(2, minMass, maxMass);

	// Define the efficiency model (defaults to unity everywhere)
	LauEffModel* effModel = new LauEffModel(daughters, vetoes);

	// Can optionally provide a histogram to model variation over DP
	// (example syntax given but commented-out)
	TFile *effHistFile = TFile::Open("/home/oryan/laura/Rian/eff_bkg_files/EffWithVeto.root", "read");
	TH2* effHist = dynamic_cast<TH2*>(effHistFile->Get("NewEffHist"));
	Bool_t useInterpolation = kTRUE;
	Bool_t fluctuateBins = kFALSE;
	Bool_t useUpperHalf = kTRUE;
	effModel->setEffHisto(effHist, useInterpolation, fluctuateBins, 0.0, 0.0, useUpperHalf, squareDP);

	// Create the isobar model

	// Set the values of the Blatt-Weisskopf barrier radii and whether they are fixed or floating
	LauResonanceMaker& resMaker = LauResonanceMaker::get();
	resMaker.setDefaultBWRadius( LauBlattWeisskopfFactor::Parent,     5.0 );
	resMaker.setDefaultBWRadius( LauBlattWeisskopfFactor::Kstar,      1.5 );
	resMaker.fixBWRadius( LauBlattWeisskopfFactor::Parent,  kTRUE );
	resMaker.fixBWRadius( LauBlattWeisskopfFactor::Kstar,   kTRUE );

	LauIsobarDynamics* sigModel = new LauIsobarDynamics(daughters, effModel);
	// Add various components to the isobar model,
	// modifying some resonance parameters
	// LauAbsFance* reson(0);
	// addResonance arguments: resName, resPairAmpInt, resType
	
	// LauAbsResonance *reson(0);
	// sigModel->addResonance("rho0(770)",  2, LauAbsResonance::RelBW);
	// sigModel->addResonance("K*0(892)",  2, LauAbsResonance::RelBW);
	// reson = sigModel->addResonance("kappa0",  2, LauAbsResonance::Kappa);
    // reson->changeResonance(0.8, 0.4, -1);
	// //printf("MUDOU PQ TA AQUI O NEGOGIO: %f", (Double_t)reson->getResonanceParameter("wi"));

	// sigModel->addResonance("K*0_0(1430)",  2, LauAbsResonance::RelBW);
	// sigModel->addResonance("K*0_2(1430)",  2, LauAbsResonance::RelBW);
	// sigModel->addResonance("K*0(1680)",  2, LauAbsResonance::RelBW);


	

	LauAbsResonance * rho_770 = sigModel->addResonance("rho0(770)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * omega = sigModel->addResonance("omega(782)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * rho_1450 = sigModel->addResonance("rho0(1450)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * f2_1270 = sigModel->addResonance("f_2(1270)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * f2_1525 = sigModel->addResonance("f'_2(1525)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * f0_1370 = sigModel->addResonance("f_0(1370)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * f0_1500 = sigModel->addResonance("f_0(1500)",  2, LauAbsResonance::RelBW);
	LauAbsResonance * sigma = sigModel->addResonance("sigma0",  2, LauAbsResonance::RelBW);
	LauAbsResonance * f0_980 = sigModel->addResonance("f_0(980)",  2, LauAbsResonance::RelBW);
	// LauAbsResonance * f0_980 = sigModel->addResonance("f_0(980)",  2, LauAbsResonance::Flatte);

	LauAbsResonance * K_892 = sigModel->addResonance("K*0(892)",  1, LauAbsResonance::RelBW);
	LauAbsResonance * K2_1430 = sigModel->addResonance("K*0_2(1430)",  1, LauAbsResonance::RelBW);
	LauAbsResonance * K0_1430 = sigModel->addResonance("K*0_0(1430)",  1, LauAbsResonance::RelBW);
	LauAbsResonance * K_1410 = sigModel->addResonance("K*0(1410)",  1, LauAbsResonance::RelBW);
	LauAbsResonance * kappa = sigModel->addResonance("kappa0",  1, LauAbsResonance::RelBW);
	// LauAbsResonance * kappa = sigModel->addResonance("kappa0",  1, LauAbsResonance::Kappa);

	sigModel->addResonance("NonReson", 0, LauAbsResonance :: FlatNR);

	// Mass and Width values from PDG Live 2025
	rho_770->changeResonance(0.77526 , 0.1474, 1);
	omega->changeResonance(0.78266, 0.00868, 1);
	rho_1450->changeResonance(1.465, 0.400, 1);
	f2_1270->changeResonance(1.2754, 0.1866, 2);
	f2_1525->changeResonance(1.51743 , 0.072, 2);
	f0_1370->changeResonance(1.250, 0.3, 0);
	f0_1500->changeResonance(1.522, 0.108, 0);
	sigma->changeResonance(0.37, 0.400, 0);
	f0_980->changeResonance(0.990, 0.04, 0);
	


	K_892->changeResonance(0.89555 , 0.0473, 1);
	K2_1430->changeResonance(1.4324 , 0.109 , 2);
	K0_1430->changeResonance(1.425, 0.270 , 0);
	K_1410->changeResonance(1.414, 0.232 , 1);
	kappa->changeResonance(0.845, 0.468 , 0);


			// O NUMERO REPRESENTA ONDE NAO FICA A RESSONANCIA

	// Reset the maximum signal DP ASq value
	// This will be automatically adjusted to avoid bias or extreme
	// inefficiency if you get the value wrong but best to set this by
	// hand once you've found the right value through some trial and error.

	// sigModel->setASqMaxValue(0.35);

	// Create the fit model
	LauSimpleFitModel* fitModel = new LauSimpleFitModel(sigModel);

	// Create the complex coefficients for the isobar model
	// Here we're using the magnitude and phase form:
	// c_j = a_j exp(i*delta_j)
	std::vector<LauAbsCoeffSet*> coeffset;

	coeffset.push_back( new LauMagPhaseCoeffSet("rho0(770)",		1.00,	0.00,  kTRUE,  kTRUE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("omega(782)",		0.0682962, 	-1.15797, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("rho0(1450)",		0.221829, 	0.503647, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_2(1270)", 		0.115391, 	0.270249, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f'_2(1525)", 		0.0340333, 	-2.28327, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(1370)",		0.247342, 	-1.91523, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(1500)",		0.320451, 	-0.674077, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("sigma0", 			0.608306, 	-0.232464, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("f_0(980)", 		0.133243, 	3.05403, kFALSE, kFALSE) );

	coeffset.push_back( new LauMagPhaseCoeffSet("K*0(892)", 		0.924958, 	-3.06648, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("K*0_2(1430)",		0.0990001, 	0.689738, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("K*0_0(1430)",		0.332363, 	2.06983, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("K*0(1410)", 		0.216015, 	2.81874, kFALSE, kFALSE) );
	coeffset.push_back( new LauMagPhaseCoeffSet("kappa0", 			0.18911, 	-0.250233, kFALSE, kFALSE) );

	coeffset.push_back( new LauMagPhaseCoeffSet("NonReson", 	1, 	1, kFALSE, kFALSE) );
	
	for (std::vector<LauAbsCoeffSet*>::iterator iter=coeffset.begin(); iter!=coeffset.end(); ++iter) {
		fitModel->setAmpCoeffSet(*iter);
	}

	// Set the signal yield and define whether it is fixed or floated
	const Double_t nSigEvents = 224378*0.9;
	LauParameter * signalEvents = new LauParameter("signalEvents",nSigEvents,-1.0*nSigEvents,2.0*nSigEvents,kTRUE);
	fitModel->setNSigEvents(signalEvents);

	// Set the number of experiments to generate or fit and which
	// experiment to start with
	fitModel->setNExpts( nExpt, firstExpt,kTRUE );


	// Set up a background model

	// First declare the names of the background class(es)
	std::vector<TString> bkgndNames(1);
	bkgndNames[0] = "qqbar";
	fitModel->setBkgndClassNames( bkgndNames );

	// Define and set the yield parameter for the background
	const Double_t nBkg =  224378*0.1;
	LauParameter* nBkgndEvents = new LauParameter("qqbar",nBkg,-2.0*nBkg,2.0*nBkg,kTRUE);
	fitModel->setNBkgndEvents( nBkgndEvents );

	// Create the background DP model
	LauBkgndDPModel* qqbarModel = new LauBkgndDPModel(daughters, vetoes);

	// Load in background DP model histogram
	// (example syntax given but commented-out - the background will be treated as being uniform in the DP in the absence of a histogram)
	TString qqFileName("/home/oryan/laura/Rian/eff_bkg_files/BkgWithVeto.root");
	TFile* qqFile = TFile::Open(qqFileName, "read");
	TH2* qqDP = dynamic_cast<TH2*>(qqFile->Get("NewBkgHist")); // m', theta'
	qqbarModel->setBkgndHisto(qqDP, kTRUE, kFALSE, kFALSE, kFALSE); //qqbarModel->setBkgndHisto(qqDP, useInterpolation, fluctuateBins, useUpperHalf, squareDP);

	// Add the background DP model into the fit model
	fitModel->setBkgndDPModel( "qqbar", qqbarModel );


	// Configure various fit options

	// Switch on/off calculation of asymmetric errors.
	fitModel->useAsymmFitErrors(kFALSE);

	// Randomise initial fit values for the signal mode
	fitModel->useRandomInitFitPars(kTRUE);

	const Bool_t haveBkgnds = ( fitModel->nBkgndClasses() > 0 );

	// Switch on/off Poissonian smearing of total number of events
	fitModel->doPoissonSmearing(haveBkgnds);

	// Switch on/off Extended ML Fit option
	fitModel->doEMLFit(haveBkgnds);

	// Generate toy from the fitted parameters
	TString fitToyFileName("fitToyMC_");
	fitToyFileName += iFit;
	fitToyFileName += ".root";
	fitModel->compareFitData(1, fitToyFileName);
	

	// Write out per-event likelihoods and sWeights
	//TString splotFileName("splot_3pi_");
	//splotFileName += iFit;
	//splotFileName += ".root";
	//fitModel->writeSPlotData(splotFileName, "splot", kFALSE);

	// Set the names of the files to read/write

	// TString dataFile("data/entries.root");  //TString dataFile("gen-DpipiK.root");
	//TString dataFile("gen-D2PKP.root");
	// TString dataFile("/home/oryan/laura/Rian/data/HighPurity_signal_m13m23_v34.root"); 
	// TString treeName("Red_Tree");			//TString treeName("genResults"); 
	TString treeName("DecayTree");
	TString rootFileName("");
	TString tableFileName("");

	if (command == "fit") {
		rootFileName = "fitDpipiK_"; rootFileName += iFit;
		rootFileName += "_expt_"; rootFileName += firstExpt;
		rootFileName += "-"; rootFileName += (firstExpt+nExpt-1);
		rootFileName += ".root";
		tableFileName = "fitDpipiKResults_"; tableFileName += iFit; tableFileName +=".txt";
		// tableFileName = "fitDpipiK_"; tableFileName += iFit;
	} else {
		rootFileName = "dummy.root";
		tableFileName = "genDPiPiKResults";
	}
	
	// Execute the generation/fit
	fitModel->run( command, dataFile, treeName, rootFileName ,tableFileName );
	if (command == "fit") {
	// plotSH(iFit);
	}

// 	std::ofstream outFile("/home/oryan/laura/Rian/problematic_events.txt");
// if (outFile.is_open()) {
//     for (Int_t event : problematicEvents) {
//         outFile << event << std::endl;
//     }
//     outFile.close();
// 	std::cout << "Eventos problemáticos salvos em 'problematic_events.txt'." << problematicEvents[1] << std::endl;

// }
// else {
//     std::cerr << "Erro ao abrir o arquivo para salvar eventos problemáticos." << std::endl;
// }
// problematicEvents.clear();
	return EXIT_SUCCESS;
}
