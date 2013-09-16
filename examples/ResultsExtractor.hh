
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

