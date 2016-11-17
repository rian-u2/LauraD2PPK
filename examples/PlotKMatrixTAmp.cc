// Code to plot the transition amplitude T for the K-matrix pi pi S-wave

#include <iostream>
using std::cout;
using std::endl;

#include "LauKMatrixPropagator.hh"
#include "LauComplex.hh"

#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TAxis.h"
#include "TLine.h"
#include "TMath.h"

int main(const int /*argc*/, const char** /*argv*/) {

	// Define the "S-wave" K-matrix propagator
	Int_t nChannels = 5;
	Int_t nPoles = 5;
	Int_t resPairInt = 1;
	Int_t KMatrixIndex = 1; // for S-wave
	LauKMatrixPropagator* propagator = new LauKMatrixPropagator("KMSWave", "DToKspipiKMatrixCoeff.dat", 
								    resPairInt, nChannels, 
								    nPoles, KMatrixIndex);

	// Find the transition amplitude T for the pi pi mode for
	// invariant mass squared s between (2*mpi)^2 and 4.0 GeV^2
	Double_t mMin(0.28);
	Double_t mMax(2.0);
	Int_t nS = 2000;
	Double_t dm = (mMax - mMin)/(nS*1.0);

	// Argand plot
	TGraph* TxyGraph = new TGraph(nS);
	// Intensity
        TGraph* TSqGraph = new TGraph(nS);
	// Phase
	TGraph* TDeltaGraph = new TGraph(nS);
	// Inelasticity eta
	TGraph* TEtaGraph = new TGraph(nS);

	Double_t radToDeg = 180.0/TMath::Pi();
	// Keep track of the real value of T to know when it
	// changes sign from -ve to +ve => 180 phase shift
	Double_t oldReT(0.0);
	int n180Shift(0);

        for (Int_t i = 0; i < nS; i++) {

	    Double_t m = dm*i + mMin;
	    Double_t s = m*m;

	    LauComplex TAmp = propagator->getTransitionAmp(s, KMatrixIndex);

	    Double_t realT = TAmp.re();
	    Double_t imagT = TAmp.im();

	    // Argand diagram showing the transition amplitude phase motion
	    TxyGraph->SetPoint(i, realT, imagT);
	    // Transition amplitude squared
	    TSqGraph->SetPoint(i, m, TAmp.abs2());

	    // T - E = 0.5*i, where E = inelasticity vector, pointing to T from (0,i/2)
	    Double_t ReE = realT;
	    Double_t ImE = imagT - 0.5;

	    LauComplex EVect(ReE, ImE);
	    // Inelasticity
	    Double_t EMag = EVect.abs();
	    Double_t eta = 2.0*EMag;
	    TEtaGraph->SetPoint(i, m, eta);

	    // Find the phase shift angle, delta
	    Double_t delta = 0.5*TMath::ATan2(ImE, fabs(ReE))*radToDeg + 45.0;
	    if (realT < 0.0) {delta = 180.0 - delta;}

	    // Have we gone through 180 deg (or 2*delta through 360 deg)?
	    if (oldReT < 0.0 && realT > 0.0) {n180Shift += 1;}
	    // Add 180 if required
	    delta += 180.0*n180Shift;

	    TDeltaGraph->SetPoint(i, m, delta);

	    // Keep track of the real value of T to see if it changes sign
	    oldReT = realT;

	}

        TCanvas* theCanvas = new TCanvas("theCanvas", "", 1400, 1000);
        gROOT->SetStyle("Plain");
        gStyle->SetOptStat(0);
        theCanvas->Clear();
        theCanvas->UseCurrentStyle();

        theCanvas->Divide(2,2);
 	// Argand plot
	theCanvas->cd(1);
	TxyGraph->SetTitle("Argand plot");
	TxyGraph->GetXaxis()->SetTitle("Re(T)");
        TxyGraph->GetYaxis()->SetTitle("Im(T)");
        TxyGraph->Draw("apl");

	// Overlay the elastic boundaries
	TLine lineA1(-0.5, 0.0, -0.5, 1.0);
	lineA1.SetLineStyle(kDotted);
	lineA1.Draw();
	TLine lineA2(0.5, 0.0, 0.5, 1.0);
	lineA2.SetLineStyle(kDotted);
	lineA2.Draw();
	TLine lineA3(-0.5, 1.0, 0.5, 1.0);
	lineA3.SetLineStyle(kDotted);
	lineA3.Draw();
	
	// Intensity
        theCanvas->cd(2);
	TSqGraph->SetTitle("Intensity");
	TSqGraph->GetXaxis()->SetTitle("#sqrt{s} (GeV/c^{2})");
        TSqGraph->GetYaxis()->SetTitle("|T|^{2}");
        TSqGraph->Draw("apl");
	// Overlay the unitarity limit
	TAxis* xAxis = TSqGraph->GetXaxis();
	TLine lineB1(xAxis->GetXmin(), 1.0, xAxis->GetXmax(), 1.0);
	lineB1.SetLineStyle(kDotted);
	lineB1.Draw();

	// Phase
        theCanvas->cd(3);
	TDeltaGraph->SetTitle("Phase shift");
        TDeltaGraph->GetXaxis()->SetTitle("#sqrt{s} (GeV/c^{2})");
        TDeltaGraph->GetYaxis()->SetTitle("#delta (degrees)");
        TDeltaGraph->Draw("apl");

 	// Inelasticity
	theCanvas->cd(4);
	TEtaGraph->SetTitle("Inelasticity");
        TEtaGraph->GetXaxis()->SetTitle("#sqrt{s} (GeV/c^{2})");
	TEtaGraph->GetYaxis()->SetTitle("#eta");
        TEtaGraph->Draw("apl");
	// Overlay the elastic limit
	xAxis = TEtaGraph->GetXaxis();
	TLine lineD1(xAxis->GetXmin(), 1.0, xAxis->GetXmax(), 1.0);
	lineD1.SetLineStyle(kDotted);
	lineD1.Draw();


        theCanvas->Print("KMatrixTAmpPlots.png");


}
