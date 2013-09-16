// Code to combine neighbouring bins to calculate the 2D chi-square between
// two sets of histograms (e.g. low-stat data and high-stat toyMC).
// To run the code, do "./CalcChiSq chiSqInput.txt", where chiSqInput.txt is 
// an input control file, and contains the following lines:
// Low_stat_file_name      Low_stat_histo_name
// High_stat_file_name     High_stat_histo_name
// Min_bin_content         N_free_params        Low/high stat_histo_ratio

// Note that the low and high stat histograms must have the same bin axes
// ranges and number of bins.

// It works by using the low stat (first) histogram to find bin groups such 
// that the total number of entries in each group is >= Min_bin_content. 
// It looks for the lowest non-zero bin and adds neighbouring bins until the 
// minimum bin content is reached; this is repeated for the next lowest 
// non-zero bin (excluding bins already assigned to a group) until all bins 
// are processed. Bins with zero content are assigned to the nearest group.

// Consider a bin at (x,y). A group is formed by combining the bins in the 
// following order, stopping when the minimum bin content has been reached:
// (x,y-1); (x,y+1); (x+1,y-1); (x+1,y); (x+1,y+1); (x-1,y-1); (x-1,y); (x-1,y+1)
// If the "3x3" group does not have the required minimum content, then 
// a "4x4" group is tried, considering bins from bottom to top, alternating 
// right/left of the middle (deltaX = 0, 1, -1, 2, -2). This process can go 
// on ("nxn") until the minimum content has been reached or the maximum number 
// of x or y bins has been searched.

// The (Pearson) chi-squared is then the sum of the chi-squared contributions
// of all bin groups:
// (low_stat_number - high_stat_number)^2/(high_stat_number)
// The nDof = number of bin groups - number of free params - 1

#include "CalcChiSq.hh"

#include "TAxis.h"
#include "TSystem.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::cerr;
using std::endl;

CalcChiSq::CalcChiSq(TString inputFileName) :
	inputFileName_(inputFileName),
	fileName1_(""),
	fileName2_(""),
	histoName1_(""),
	histoName2_(""),
	minContent_(10.0),
	histo1_(0),
	histo2_(0),
	theHisto_(0),
	checkHisto_(0),
	chiSqHisto_(0),
	chiSqSignedHisto_(0),
	checkInt_(0),
	nCheckedBins_(0),
	nBinsX_(0),
	nBinsY_(0),
	nMaxBin_(0),
	nTotBins_(0),
	xMin_(0.0),
	xMax_(0.0),
	yMin_(0.0),
	yMax_(0.0),
	maxContent_(0.0),
	groupWeight_(0.0),
	epsilon_(1.0e-6),
	nParams_(0),
	scaleFactor_(1.0),
	verbose_(kFALSE)
	
{
	this->initialiseHistos();
}

CalcChiSq::~CalcChiSq()
{
}

void CalcChiSq::run()
{

	// Loop over all bins to find the next lowest bin and find its bin group
	// For all grouped bins, set the check integer to non-zero to make sure
	// we do not process them again.
	cout<<"Running chi-squared algorithm"<<endl;

	Int_t xBin(0), yBin(0);

	cout<<"Grouping bins"<<endl;
	while (nCheckedBins_ <= nTotBins_) {

		this->findLowestBin(xBin, yBin);
		this->findNeighbours(xBin, yBin);
	}

	// Next, assign the nearest neighbouring bin regions to those bins 
	// with zero (< epsilon) entries (checkInt = -1).
	cout<<"Assigning zero bins"<<endl;
	this->assignZeroBins();

	// Now calculate the chi-squared using the bin groups
	cout<<"Calculating chi-squared"<<endl;
	this->calculateChiSq();

	// Output the various histograms
	cout<<"Writing out histogram output"<<endl;

	TFile* outFile = new TFile("checkHistos.root", "recreate");

	histo1_->SetDirectory(outFile);
	histo2_->SetDirectory(outFile);
	checkHisto_->SetDirectory(outFile);
	chiSqHisto_->SetDirectory(outFile);
	chiSqSignedHisto_->SetDirectory(outFile);

	outFile->Write();
	outFile->Close();
	
	cout<<"Done"<<endl;

}

void CalcChiSq::calculateChiSq()
{

	// Use the checkInt histogram to compare the same bins between histograms 1 and 2.
	// All histograms will have the same axes etc..
	Float_t totalChiSq(0.0);
	chiSqHisto_ = new TH2F("ChiSqHisto", "ChiSqHisto", nBinsX_, xMin_, xMax_, nBinsY_, yMin_, yMax_);
	chiSqSignedHisto_ = new TH2F("ChiSqSignedHisto", "ChiSqSignedHisto", nBinsX_, xMin_, xMax_, nBinsY_, yMin_, yMax_);
	chiSqHisto_->SetDirectory(0);
	chiSqSignedHisto_->SetDirectory(0);

	Int_t maxCheckInt = static_cast<Int_t>(checkHisto_->GetMaximum());
	Int_t nGroupBins(0);
	for ( Int_t iCheck = 1; iCheck <= maxCheckInt; ++iCheck ) {

		std::vector<Int_t> xVect, yVect;
		Float_t sum1(0.0), sum2(0.0);

		for ( Int_t i = 1; i <= nBinsX_; i++) {

			for ( Int_t j = 1; j <= nBinsY_; j++) {

				Int_t checkInt = this->getCheckBinValue(i, j);
				if (checkInt == iCheck) {

					// Keep track of which bins we are using
					xVect.push_back(i);
					yVect.push_back(j);

					// Calculate Pearson chi-square for this bin, using the
					// second histogram for the expected distribution
					Float_t weight1 = this->getHist1BinValue(i, j);
					Float_t weight2 = this->getHist2BinValue(i, j);
					sum1 += weight1;
					sum2 += weight2;
				}
			}
		}

		// Calculate the chi-squared for the bin group
		Float_t groupChiSq(0.0);
		Float_t diff = sum1 - sum2;
		if (sum2 > 0.0) {groupChiSq = (diff*diff)/sum2;}

		// Put the groupChiSq value to all matching bins in the same group
		Int_t nBins = xVect.size();
		for ( Int_t iBin = 0; iBin < nBins; iBin++) {

			Int_t xBin = xVect[iBin];
			Int_t yBin = yVect[iBin];
			chiSqHisto_->SetBinContent(xBin, yBin, groupChiSq);
			if ( diff > 0 ) {
				chiSqSignedHisto_->SetBinContent(xBin, yBin, groupChiSq);
			} else {
				chiSqSignedHisto_->SetBinContent(xBin, yBin, -groupChiSq);
			}
		}

		// Add groupChiSq to the overall total chi-squared
		totalChiSq += groupChiSq;
		// Increment the number of grouped bins
		++nGroupBins;
	}

	Float_t nDof = nGroupBins*1.0 - nParams_ - 1.0;
	Float_t totChiSqnDof = totalChiSq/nDof;
	cout<<"Total ChiSq/nDof = "<<totalChiSq<<"/"<<nDof<<" = "<<totChiSqnDof<<endl;
}

void CalcChiSq::findLowestBin(Int_t& xBin, Int_t& yBin)
{

	// Find the lowest non-zero bin in the histogram. If this has entries < minContent then
	// this needs to be combined with surrounding bins to create a "super-bin".
	Float_t lowestContent(2.0*maxContent_);
	Bool_t foundBin(kFALSE);

	// Loop over the bins along X and Y
	for ( Int_t i = 1; i <= nBinsX_; ++i ) {

		for ( Int_t j = 1; j <= nBinsY_; ++j ) {

			// Check that we have not processed this bin before
			Int_t skipBin = this->getCheckBinValue(i, j);
			if (skipBin == 0) {

				// Get the bin content
				Float_t binContent = this->getHistBinValue(i, j);
				if (binContent > epsilon_ && binContent < lowestContent) {

					// Keep track of which bin has the lowest (non-zero) content
					lowestContent = binContent;
					xBin = i; yBin = j;
					foundBin = kTRUE;
				}
			}
		}
	}

	// We have found a bin with the lowest number of (non-zero) entries
	if (foundBin == kTRUE) {
		if (verbose_ == kTRUE) {
			cerr<<"Found lowest non-zero bin at ("<<xBin<<", "<<yBin<<") with entries = "<<lowestContent<<endl;
		}
		// Increment the check histogram integer counter. All neighbouring bins will be assigned this number,
		// so that we know which bins belong to the new merged group.
		++checkInt_;
	}

}

void CalcChiSq::findNeighbours(Int_t xBin, Int_t yBin)
{

	// Find the nearest neighbours for this bin and see if we get total content > minContent.
	// If not, carry on until we do.

	Bool_t binOK = this->checkBin(xBin, yBin);
	if (binOK == kFALSE) {return;}

	// Do the actual bin first
	Float_t totWeight = this->getHistBinValue(xBin, yBin);
	if (totWeight > minContent_) {

		// If the bin has a large enough content, do nothing further
		this->setCheckBin(xBin, yBin, checkInt_);
		if (verbose_ == kTRUE) {
			cerr<<"Bin ("<<xBin<<", "<<yBin<<") has weight = "<<totWeight<<" > "<<minContent_<<endl;
		}
		return;

	} else if (totWeight < epsilon_) {

		// If the bin has zero content, set the checkInt to -1 and do nothing further
		this->setCheckBin(xBin, yBin, -1);
		return;
	}

	Int_t loop(0);
	Bool_t foundGroup = this->findGroup(xBin, yBin);
	totWeight += groupWeight_;

	if (foundGroup == kTRUE) {

		if (verbose_ == kTRUE) {
			cerr<<"*** For bin ("<<xBin<<", "<<yBin<<"), totWeight = "<<totWeight<<" for loop = "<<loop<<"\n"<<endl;
		}
		
	} else {

		// Try to find the nearest group and assign this bin with the same checkInt.
		// First, decrement checkInt, since no new group was found.
		checkInt_ = checkInt_ - 1;
		Int_t checkInt = this->findNearestGroup(xBin, yBin);

		if (verbose_ == kTRUE) {
			cerr<<"*** Could not find a suitable group for bin ("
			    <<xBin<<", "<<yBin<<"). Adding it to the nearest group with checkInt = "
			    <<checkInt<<endl;
		}

	}

}

Bool_t CalcChiSq::findGroup(Int_t iBin, Int_t jBin)
{
	groupWeight_ = 0.0;

	Float_t groupSum(0.0);
	Int_t i, j, loop;
	Bool_t gotGroup(kFALSE), stopLoop(kFALSE);
	std::vector<Int_t> xVect, yVect;

	for (loop = 1; loop <= nMaxBin_; loop++) {

		if (gotGroup == kTRUE || stopLoop == kTRUE) {break;}

		Int_t loopMax = 2*loop + 1;

		for (i = 1; i <= loopMax; i++) {
			
			if (gotGroup == kTRUE) {break;}
			
			Int_t C(0);
			if (i%2 == 0) {
				C = i/2;
			} else {
				C = -(i - 1)/2;
			}

			Int_t x = iBin + C;

			for (j = -loop; j <= loop; j++) {

				if (gotGroup == kTRUE || stopLoop == kTRUE) {break;}
				Int_t y = jBin + j;
			
				// Check that the bin is OK
				Bool_t binOK = this->checkBin(x, y);
				if (binOK == kTRUE) {

					// Check that we have not processed this bin before
					Int_t checkInt = this->getCheckBinValue(x, y);
					if (checkInt != 0) {
						// We have processed this bin before. 
						// Stop merging bins to form the group.
 						stopLoop = kTRUE;
					} else {				       
						// Add this bin to the group
						Float_t weight = this->getHistBinValue(x, y);
						groupSum += weight;
						// Keep track of which bins we are adding to the group
						xVect.push_back(x);
						yVect.push_back(y);
						if (verbose_ == kTRUE) {
							cerr<<"Added bin ("<<x<<", "<<y
							    <<") to the group with weight = "<<weight<<endl;
						}

						// Stop adding bins if we have the minimum content required
						if (groupSum > minContent_) {
							gotGroup = kTRUE;
							groupWeight_ = groupSum;
						}

					} // checkInt is zero
				} // binOK
			} // j
		} // i

	} // loop

	if (gotGroup == kTRUE) {

		// Loop over the vector of bins in the group and assign the checkInt_ integer to them
		Int_t vectSize = xVect.size();
		Int_t iVect;
		for (iVect = 0; iVect < vectSize; iVect++) {
			Int_t xBin = xVect[iVect];
			Int_t yBin = yVect[iVect];
			this->setCheckBin(xBin, yBin, checkInt_);
		}

	}

	return gotGroup;

}

Int_t CalcChiSq::findNearestGroup(Int_t iBin, Int_t jBin)
{

	// We could not create a suitable group for the bin (iBin, jBin). 
	// Instead, assign it to the nearest group. Do this by searching bins vertically,
	// starting at the centre horizonatally and extending right and left outwards.
	// Find the first group that has checkInt != 0 and assign the same checkInt.

	Int_t checkInt(0);
	Bool_t gotGroup(kFALSE);

	for ( Int_t loop = 1; loop <= nMaxBin_; ++loop ) {

		if (gotGroup == kTRUE) {break;}

		Int_t loopMax = 2*loop + 1;
		
		for ( Int_t i = 1; i <= loopMax; ++i ) {
			
			if (gotGroup == kTRUE) {break;}

			Int_t C(0);
			if (i%2 == 0) {
				C = i/2;
			} else {
				C = -(i - 1)/2;
			}

			Int_t x = iBin + C;

			for ( Int_t j = -loop; j <= loop; ++j ) {

				if (gotGroup == kTRUE) {break;}

				Int_t y = jBin + j;

				Bool_t binOK = this->checkBin(x, y);
				if (binOK == kTRUE) {

					Int_t binCheckInt = this->getCheckBinValue(x, y);
					Float_t binWeight = this->getHistBinValue(x, y);
					if (binCheckInt != 0 && binWeight > epsilon_) {
						// Found bin
						this->setCheckBin(iBin, jBin, binCheckInt);
						checkInt = binCheckInt;
						gotGroup = kTRUE;
					}
				}
			} // j loop

		} // i loop
	}

	return checkInt;
}

void CalcChiSq::assignZeroBins()
{
	// Assign the nearest neighbouring bin regions to those bins with zero entries (checkInt = 0 or -1).
	for ( Int_t iBin = 1; iBin <= nBinsX_; ++iBin ) {
		for ( Int_t jBin = 1; jBin <= nBinsY_; ++jBin ) {

			Int_t checkInt = this->getCheckBinValue(iBin, jBin);
			if (checkInt <= 0) {
				Int_t newCheckInt = this->findNearestGroup(iBin, jBin);
				if (verbose_ == kTRUE) {
					cerr<<"Zero bin ("<<iBin<<", "<<jBin<<") assigned checkInt = "<<newCheckInt<<endl;
				}
				this->setCheckBin(iBin, jBin, newCheckInt);
			}

		}
	}
}

void CalcChiSq::setCheckBin(Int_t iBin, Int_t jBin, Int_t checkInt)
{
	if (verbose_ == kTRUE) {
		cerr<<"Set check bin "<<iBin<<", "<<jBin<<" with checkInt = "<<checkInt<<endl;
	}
	checkHisto_->SetBinContent(iBin, jBin, checkInt);
	nCheckedBins_++;
}

Int_t CalcChiSq::getCheckBinValue(Int_t iBin, Int_t jBin)
{
	Int_t value = static_cast<Int_t>(checkHisto_->GetBinContent(iBin, jBin));
	return value;

}

Float_t CalcChiSq::getHistBinValue(Int_t iBin, Int_t jBin)
{

	Float_t value = static_cast<Float_t>(theHisto_->GetBinContent(iBin, jBin));
	return value;

}

Float_t CalcChiSq::getHist1BinValue(Int_t iBin, Int_t jBin)
{

	Float_t value = static_cast<Float_t>(histo1_->GetBinContent(iBin, jBin));
	return value;

}

Float_t CalcChiSq::getHist2BinValue(Int_t iBin, Int_t jBin)
{

	Float_t value = static_cast<Float_t>(histo2_->GetBinContent(iBin, jBin));
	// Apply scaling factor to compare with histogram 1 values
	value *= scaleFactor_;
	return value;

}

Bool_t CalcChiSq::checkBin(Int_t iBin, Int_t jBin)
{

	// Check that the bin co-ordinates are inside the histogram.
	// Bin indices go from 1 to nBin (0 = underflow, nBin+1 = overflow).
	Bool_t ok(kTRUE);
	if (iBin < 1 || iBin > nBinsX_) {
		ok = kFALSE;
	} else if (jBin < 1 || jBin > nBinsY_) {
		ok = kFALSE;
	}

	return ok;

}

void CalcChiSq::initialiseHistos()
{

        // Open the input control file:
        // Low_stat_file_name      Low_stat_histo_name
        // High_stat_file_name     High_stat_histo_name
        // Min_bin_content         N_free_params        Low/high stat_histo_ratio
	std::ifstream getData(inputFileName_.Data());

	// get the info on the low stat histo
	getData >> fileName1_ >> histoName1_;
	if (!getData.good()) {
		cerr<<"Error. Could not read first line of the input file "<<inputFileName_<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// open the file that contains the low stat histogram
	TFile * file1 = TFile::Open(fileName1_.Data(), "read");

	if (file1 == 0) {gSystem->Exit(EXIT_FAILURE);}

	// retrieve the low stat histogram
	histo1_ = dynamic_cast<TH2F*>(file1->Get(histoName1_.Data()));

	if (histo1_ == 0) {
		cerr<<"Error. Could not find the histogram "<<histoName1_
		    <<" in the file "<<fileName1_<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// remove the histogram from it's file to the ROOT directory
	histo1_->SetDirectory(0);

	// get the info on the high stat histogram
	getData >> fileName2_ >> histoName2_;
	if (!getData.good()) {
		cerr<<"Error. Could not read the second line of the input file "<<inputFileName_<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// if both histograms are in the same file then just retrieve the
	// high stat histogram from the file we already have open
	TFile * file2(0);
	if ( fileName2_ == fileName1_ ) {
		histo2_ = dynamic_cast<TH2F*>(file1->Get(histoName2_.Data()));
	}
	// otherwise open the other file and retrieve the high stat histogram from there
	else {
		file2 = TFile::Open(fileName2_.Data(), "read");

		if (file2 == 0) {gSystem->Exit(EXIT_FAILURE);}

		histo2_ = dynamic_cast<TH2F*>(file2->Get(histoName2_.Data()));
	}
	
	if (histo2_ == 0) {
		cerr<<"Error. Could not find the histogram "<<histoName2_
		    <<" in the file "<<fileName2_<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// remove the histogram from it's file to the ROOT directory
	histo2_->SetDirectory(0);

	// close the file(s) containing the histograms
	if (file1 != 0) {file1->Close();}
	delete file1;
	if (file2 != 0) {file2->Close();}
	delete file2;

	// get the info on the minimum content, number of parameters and scalefactor
	Int_t nParameters(0);
	Float_t minContent(0.0), scaleFactor(1.0);
	getData >> minContent >> nParameters >> scaleFactor;
	if (getData.good()) {
		minContent_ = minContent;
		nParams_ = nParameters;
		scaleFactor_ = scaleFactor;
	}

	// close the text file
	getData.close();

	// get information from the histograms on number of bins, axis ranges, etc.
	Int_t nBX1 = histo1_->GetNbinsX();
	Int_t nBX2 = histo2_->GetNbinsX();

	if (nBX1 != nBX2) {
		cerr<<"Error. Histogram "<<histoName1_<<" has "<<nBX1
		    <<" x bins whereas histogram "<<histoName2_<<" has "<<nBX2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	Int_t nBY1 = histo1_->GetNbinsY();
	Int_t nBY2 = histo2_->GetNbinsY();

	if (nBY1 != nBY2) {
		cerr<<"Error. Histogram "<<histoName1_<<" has "<<nBY1
		    <<" y bins whereas histogram "<<histoName2_<<" has "<<nBY2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	TAxis* xAxis1 = histo1_->GetXaxis();
	Float_t xMin1 = xAxis1->GetXmin();
	Float_t xMax1 = xAxis1->GetXmax();	

	TAxis* yAxis1 = histo1_->GetYaxis();
	Float_t yMin1 = yAxis1->GetXmin();
	Float_t yMax1 = yAxis1->GetXmax();

	TAxis* xAxis2 = histo2_->GetXaxis();
	Float_t xMin2 = xAxis2->GetXmin();
	Float_t xMax2 = xAxis2->GetXmax();

	TAxis* yAxis2 = histo2_->GetYaxis();
	Float_t yMin2 = yAxis2->GetXmin();
	Float_t yMax2 = yAxis2->GetXmax();

	if (fabs(xMin1 - xMin2) > 1.0e-3) {
		cerr<<"Error. Histogram "<<histoName1_<<" has x min = "<<xMin1
		    <<" whereas histogram "<<histoName2_<<" has "<<xMin2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	} else if (fabs(xMax1 - xMax2) > 1.0e-3) {
		cerr<<"Error. Histogram "<<histoName1_<<" has x max = "<<xMax1
		    <<" whereas histogram "<<histoName2_<<" has "<<xMax2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	} else if (fabs(yMin1 - yMin2) > 1.0e-3) {
		cerr<<"Error. Histogram "<<histoName1_<<" has y min = "<<yMin1
		    <<" whereas histogram "<<histoName2_<<" has "<<yMin2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	} else if (fabs(yMax1 - yMax2) > 1.0e-3) {
		cerr<<"Error. Histogram "<<histoName1_<<" has y max = "<<yMax1
		    <<" whereas histogram "<<histoName2_<<" has "<<yMax2<<endl;
		gSystem->Exit(EXIT_FAILURE);
	}

	// Set the first histogram to be the one we use to find the bin groups
	theHisto_ = histo1_;

	nBinsX_ = nBX1;
	nBinsY_ = nBY1;
	nMaxBin_ = nBinsX_;	
	if (nBinsY_ > nMaxBin_) {nMaxBin_ = nBinsY_;}       
	nTotBins_ = nBinsX_*nBinsY_;

	maxContent_ = theHisto_->GetMaximum();

	xMin_ = xMin1;
	xMax_ = xMax1;
	yMin_ = yMin1;
	yMax_ = yMax1;

	// Also create a histogram that stores which bins have been "combined". The histogram is first empty.
	// The first non-zero bin is found, and neighbouring bins are added to it until we get the minContent.
	// These bins are then assigned the same integer number in checkHisto_. We iterate until all bins
	// are processed. The checkHisto_ is then used to process groups of bins for both sets of data and
	// fit result histograms.
	checkHisto_ = new TH2I("CheckHisto", "CheckHisto", nBinsX_, xMin_, xMax_, nBinsY_, yMin_, yMax_);
	checkHisto_->SetDirectory(0);

	// Also initialise the integer for the check histogram to zero
	checkInt_ = 0; nCheckedBins_ = 0;

	cout<<"Using the files and histograms: "<<fileName1_<<"; "<<histoName1_
	    <<" and "<<fileName2_<<"; "<<histoName2_<<endl;
	cout<<"Selecting histogram "<<theHisto_->GetName()<<" for finding the bin groups"<<endl;
	cout<<"Relative scaling factor histo1/histo2 set to "<<scaleFactor_<<endl;
	cout<<"Minimum bin content is "<<minContent_<<endl;
	cout<<"Number of free parameters is "<<nParams_<<endl;

}

