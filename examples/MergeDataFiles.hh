
#include <map>
#include <cstdlib>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"

// A utility class to allow the merging of data files on a expt-by-expt basis,
// i.e. such that events for expt 0 from tree 1 will be followed by events for expt 0 from tree 2,
// then expt 1 from tree1, expt 1 from tree 2 etc.

class MergeDataFiles
{
	public:
		MergeDataFiles(const TString& fileName1, const TString& fileName2, const TString& treeName);
		~MergeDataFiles();

		void process(const TString& fileName);

	protected:
		typedef std::map<TString,Double_t> LeafDoubleMap;
		typedef std::map<TString,Int_t> LeafIntegerMap;
		typedef std::map< Int_t,std::pair<Int_t,Int_t> > ExptsMap;

		void openInputFiles();
		void setupInputTrees();
		void setupOutputTree();
		void findExperiments(TTree* tree, ExptsMap& exptsMap);
		Bool_t checkExperimentMaps() const;
		void readExperiment(TTree* tree, const ExptsMap::const_iterator& exptsMap, Int_t offset);
		void writeFile();

	private:
		TString fileName1_;
		TString fileName2_;
		TString treeName_;

		TFile * inputFile1_;
		TFile * inputFile2_;

		TTree * inputTree1_;
		TTree * inputTree2_;

		TFile * outputFile_;
		TTree * outputTree_;

		// Tree variables
		Int_t iExpt_;
		Int_t iEvtWithinExpt_;

		LeafDoubleMap doubleVars_;
		LeafIntegerMap integerVars_;

		ExptsMap tree1Expts_;
		ExptsMap tree2Expts_;
};

