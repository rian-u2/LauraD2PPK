#include "TFile.h"
#include "TH2.h"
#include "TString.h"

#include <vector>

/*
   A utility class to allow the calculation of the chisq of the fit to the Dalitz plot.
   A text config file is provided that gives the histograms for the data and
   toy MC generated from the fit results.  These can be in the traditional DP
   or the square DP.  A sample config file is provided.  The fields are:
   <name of file containing data histogram> <name of data histogram>
   <name of file containing toy MC histogram> <name of toy MC histogram>
   <the minimum content for any bin> <the number of free parameter in the fit> <the scalefactor by which the toy MC bin content should be multiplied>
*/

class CalcChiSq {

public:

	CalcChiSq(TString inputFileName = "chiSqInput.txt");
	virtual ~CalcChiSq();

	void run();
	inline void setVerbose(Bool_t flag) {verbose_ = flag;}

private:

	void initialiseHistos();
	void findLowestBin(Int_t& xBin, Int_t& yBin);
	void findNeighbours(Int_t xBin, Int_t yBin);
	void assignZeroBins();

	void calculateChiSq();

	Bool_t findGroup(Int_t iBin, Int_t jBin);
	Int_t findNearestGroup(Int_t iBin, Int_t jBin);

	void setCheckBin(Int_t iBin, Int_t jBin, Int_t checkInt);
	Int_t getCheckBinValue(Int_t iBin, Int_t jBin);
	Float_t getHistBinValue(Int_t iBin, Int_t jBin);
	Float_t getHist1BinValue(Int_t iBin, Int_t jBin);
	Float_t getHist2BinValue(Int_t iBin, Int_t jBin);

	Bool_t checkBin(Int_t iBin, Int_t jBin);

	TString inputFileName_;
	TString fileName1_, fileName2_, histoName1_, histoName2_;
	Float_t minContent_;

	TH2F *histo1_, *histo2_, *theHisto_;
	TH2I *checkHisto_;
	TH2F *chiSqHisto_;
	TH2F *chiSqSignedHisto_;

	Int_t checkInt_, nCheckedBins_, nBinsX_, nBinsY_, nMaxBin_, nTotBins_;
	Float_t xMin_, xMax_, yMin_, yMax_, maxContent_, groupWeight_, epsilon_;
	Int_t nParams_;
	Float_t scaleFactor_;
	Bool_t verbose_;

};
