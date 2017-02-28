
#include <cstdlib>
#include <iostream>
#include <vector>

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooDataSet.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"

#include "LauRooFitSlave.hh"

void usage( std::ostream& out, const TString& progName )
{
	out<<"Usage:\n";
	out<<progName<<" gen <category = DD or LL> [nExpt = 1] [firstExpt = 0]\n";
	out<<"or\n";
	out<<progName<<" fit <category = DD or LL> <port> [nExpt = 1] [firstExpt = 0]"<<std::endl;
}

int main( int argc, char** argv )
{
	// Process command-line arguments
	// Usage:
	// ./SlaveRooFit gen <category = DD or LL> [nExpt = 1] [firstExpt = 0]
	// or
	// ./SlaveRooFit fit <category = DD or LL> <port> [nExpt = 1] [firstExpt = 0]
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
		if ( argc < 4 ) {
			usage( std::cerr, argv[0] );
			return EXIT_FAILURE;
		}
		port = atoi( argv[3] );
		if ( argc > 4 ) {
			nExpt = atoi( argv[4] );
			if ( argc > 5 ) {
				firstExpt = atoi( argv[5] );
			}
		}
	} else {
		usage( std::cerr, argv[0] );
		return EXIT_FAILURE;
	}

	// Set the names of the files to read/write
	TString dataFile("data-"); dataFile += category; dataFile += ".root";
	TString treeName("fitTree");
	TString rootFileName("");
	TString tableFileName("");
	if (command == "fit") {
		rootFileName = "fit"; rootFileName += category;
		rootFileName += "_expt_"; rootFileName += firstExpt;
		rootFileName += "-"; rootFileName += (firstExpt+nExpt-1);
		rootFileName += ".root";
		tableFileName = "fitResults";
	} else {
		rootFileName = "dummy.root";
		tableFileName = "genResults";
	}

	// Create the RooFit model
	std::cout << "Building the model..." << std::endl;
	RooRealVar mB("mB", "m_{B}", 5.150, 5.600, "GeV/c^{2}");

	RooRealVar sig_mb_mean1("sig_mb_mean1", "", 5.279, 5.200, 5.300);
	RooRealVar sig_mb_sigma1("sig_mb_sigma1", "", 0.020, 0.000, 0.100);
	RooRealVar sig_mb_sigma2("sig_mb_sigma2", "", 0.070, 0.000, 0.200);
	RooRealVar sig_mb_frac("sig_mb_frac", "", 0.90, 0.000, 1.000);
	sig_mb_mean1.setConstant(kTRUE);
	sig_mb_sigma1.setConstant(kTRUE);
	sig_mb_sigma2.setConstant(kTRUE);
	sig_mb_frac.setConstant(kTRUE);

	RooGaussian gauss1( "gauss1", "", mB, sig_mb_mean1, sig_mb_sigma1 );
	RooGaussian gauss2( "gauss2", "", mB, sig_mb_mean1, sig_mb_sigma2 );
	RooAddPdf sigPDF( "sigPDF", "", gauss1, gauss2, sig_mb_frac );

	RooRealVar comb_mb_slope("comb_mb_slope", "", -0.05, -1.0, 1.0);
	comb_mb_slope.setConstant(kTRUE);

	RooPolynomial combPDF( "combPDF", "", mB, RooArgList(comb_mb_slope) );

	Double_t nSigEvents = 5000.0;
	Double_t nCombBgEvents = 7000.0;
	Double_t nTotEvents = nSigEvents + nCombBgEvents;

	RooRealVar sigYield( "signalEvents", "", nSigEvents, -2.0*nTotEvents, 2.0*nTotEvents );
	RooRealVar combYield( "CombinatorialEvents", "", nCombBgEvents, -2.0*nTotEvents, 2.0*nTotEvents );

	RooAddPdf model( "model", "", RooArgList( sigPDF, combPDF ), RooArgList( sigYield, combYield ) );

	// Execute the generation/fit
	if ( command == "fit" ) {
		// Open the data file
		std::cout << "Getting the data..." << std::endl;
		TFile * file = TFile::Open(dataFile);
		if (!file) {
			std::cerr << "Problem opening data file" << std::endl;
			return EXIT_FAILURE;
		}
		TTree * tree = dynamic_cast<TTree*>( file->Get(treeName) );
		if (!tree) {
			std::cerr << "Problem extracting tree from data file" << std::endl;
			return EXIT_FAILURE;
		}
		RooDataSet data( "data", "", tree, RooArgSet(mB) );
		std::cout << "Found " << data.numEntries() << " events" << std::endl;

		std::vector<RooAbsData*> datasets;
		datasets.push_back(&data);

		// Create the slave instance
		LauRooFitSlave fitModel(model, datasets, kTRUE);
		fitModel.runSlave( dataFile, treeName, rootFileName, tableFileName, "localhost", port );
	} else {
		std::cerr << "Can't do this yet" << std::endl;
		//RooDataSet* data = model.generate( RooArgSet(mB), nTotEvents );
	}

	return EXIT_SUCCESS;
}
