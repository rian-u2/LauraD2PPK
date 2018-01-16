
/*
Copyright 2008 University of Warwick

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

#include "TH2Poly.h"
#include "TString.h"

#include <vector>

/*
   A utility class to allow the calculation of the chisq of the fit to the Dalitz plot.
   A text config file is provided that gives the datasets for the data and
   toy MC generated from the fit results.  These can be in the traditional DP
   or the square DP.  A sample config file is provided.  The fields are:
   <name of file containing data histogram> <name of data tree> <name of the x axis variable in data> <name of the y axis variable in data>
   <name of file containing toy MC histogram> <name of toy MC tree> <name of the x axis variable in toy MC> <name of the y axis variable in toy MC>
   <the minimum content for any bin> <the number of free parameter in the fit> <the scalefactor by which the toy MC bin content should be multiplied> <minimum x value> <maximum x value> <minimum y value> <maximum y value>
*/

class CalcChiSq {

public:

	CalcChiSq(TString inputFileName = "chiSqInput.txt");
	virtual ~CalcChiSq();

	void run();
	inline void setVerbose(Bool_t flag) {verbose_ = flag;}

private:

	void initialiseHistos();
	void pickBinning(Double_t* xs, Double_t* ys, Int_t nEntries, std::vector<Int_t>& divisions);
	void getHisto(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t* xs, Double_t* ys, Int_t nEntries, std::vector<Int_t>& divisions, UInt_t iter=0);

	void calculateChiSq();
	void makePlots();

	TString inputFileName_;
	TString fileName1_, fileName2_, treeName1_, treeName2_, xName1_, xName2_, yName1_, yName2_;
	Float_t minContent_;

	TH2Poly *theHisto_, *histo1_, *histo2_;
	TH2Poly *pullHisto_;
	TH2Poly *chiSqHisto_;
	TH2Poly *chiSqSignedHisto_;

	Float_t xMin_, xMax_, yMin_, yMax_;
	Int_t nParams_;
	Float_t scaleFactor_;
	Bool_t verbose_;

};
