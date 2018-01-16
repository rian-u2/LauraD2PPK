
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

#include <map>
#include <vector>

#include "TString.h"

class TChain;
class TFile;
class TH1;
class TTree;

/*
   A utility class to allow the extraction of the best fit from a series of
   fits to a given data sample.
   When fitting amplitude models, the likelihood parameter space is highly
   complex.  Hence the fitter can often wander into local minima.  To mitigate
   this effect a data sample can be fitted many times with randomised starting
   values of the isobar parameters.  It is then necessary to determine which of
   these fits gives the best solution, i.e. the minimum NLL.  This class
   performs this task, reading in a series of fits for each data sample and
   writing out a single file that contains the results of the best fit for each
   data sample.
*/

class ResultsExtractor
{
	public:
		ResultsExtractor(const TString& inputFileName, const TString& outputFileName, const TString& treeName);
		~ResultsExtractor();

		void process(Int_t numExpts);

	protected:
		void setupInputTree();
		void setupOutputTree(TTree * tree);
		void setInputTreeBranchStatus(Bool_t status);
		void clearMaps();
		void writeFile();

	private:
		TString inputFileName_;
		TString outputFileName_;
		TString treeName_;
		TChain * inputTree_;
		TFile * outputFile_;
		TTree * outputTree_;
		Int_t nEntries_;

		// Tree variables
		Int_t iExpt_;
		Int_t fitStatus_;
		Double_t NLL_;

		std::map<TString,Double_t> otherVars_;

		std::map< Int_t, std::pair<Double_t,Int_t> > bestNLL_;
		std::map< Int_t, std::pair<Double_t,Int_t> > worstNLL_;
		std::map< Int_t, std::vector<Double_t> > allNLLs_;

		std::map< Int_t, TH1* > nllHistos_;
};

