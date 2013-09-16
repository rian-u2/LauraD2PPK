
// Example of how to create an input data file for Laura++ to fit
//
// This example assumes that the input file contains the branches "m13" and
// "m23", which correspond to m_D0barpi+ and m_D0barpi-, respectively.
// Any additional variables that you wish to include in the fit or simply for
// information can be trivially added by including lines such as the following
// in the appropriate place:
//
// Double_t myVar(0.0);
// ...
// inputTree->SetBranchAddress("myVar",&myVar);
// ...
// outputTree->Branch("myVar",&myVar,"myVar/D");
//
// Square DP co-ordinates can also be included by changing the 5th argument of
// the LauDaughters ctor to kTRUE and uncommenting the appropriate lines.

void makeFitFile(const TString& inputFileName, const TString& inputTreeName, const TString& outputFileName)
{
	gSystem->Load("Laura++/lib/libLaura++.so");

	LauDaughters* daughters = new LauDaughters( "B0", "pi+", "pi-", "D0_bar", kFALSE );
        LauKinematics* kinematics = daughters->getKinematics();

	TChain * inputTree = new TChain( inputTreeName );
	inputTree->Add( inputFileName );

	Int_t iExpt(0);

	Double_t m12(0.0), m13(0.0), m23(0.0);
	Double_t m12Sq(0.0), m13Sq(0.0), m23Sq(0.0);
	Double_t h12(0.0), h13(0.0), h23(0.0);
	//Double_t mPrime(0.0), thPrime(0.0);

	inputTree->SetBranchAddress("m13",&m13);
	inputTree->SetBranchAddress("m23",&m23);

	TFile * outputFile = TFile::Open(outputFileName,"recreate");
	TTree * outputTree = new TTree("fitTree","Input to Laura++ Fit");

	outputTree->Branch("iExpt",&iExpt,"iExpt/I");
	outputTree->Branch("m12",&m12,"m12/D");
	outputTree->Branch("m13",&m13,"m13/D");
	outputTree->Branch("m23",&m23,"m23/D");
	outputTree->Branch("m12Sq",&m12Sq,"m12Sq/D");
	outputTree->Branch("m13Sq",&m13Sq,"m13Sq/D");
	outputTree->Branch("m23Sq",&m23Sq,"m23Sq/D");
	outputTree->Branch("h12",&h12,"h12/D");
	outputTree->Branch("h13",&h13,"h13/D");
	outputTree->Branch("h23",&h23,"h23/D");
	//outputTree->Branch("mPrime",&mPrime,"mPrime/D");
	//outputTree->Branch("thPrime",&thPrime,"thPrime/D");

	if (nEvents == 0) {
		nEvents = inputTree->GetEntries();
	}

	for (Long64_t iEntry(0); iEntry<nEvents; ++iEntry) {

		inputTree->GetEntry(iEntry);

		m13Sq = m13*m13;
		m23Sq = m23*m23;

		kinematics->updateKinematics( m13Sq, m23Sq );
		if ( ! kinematics->withinDPLimits() ) {
			cerr << "WARNING : Reco position of event " << iEntry << " not within DP boundary, skipping it." << endl;
			continue;
		}

		m12Sq = kinematics->getm12Sq();
		m12 = kinematics->getm12();
		h12 = kinematics->getc12();
		h13 = kinematics->getc13();
		h23 = kinematics->getc23();
		//mPrime = kinematics->getmPrime();
		//thPrime = kinematics->getThetaPrime();

		outputTree->Fill();

	}

	outputFile->Write();
	outputFile->Close();
}

