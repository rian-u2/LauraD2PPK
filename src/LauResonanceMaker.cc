
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauResonanceMaker.cc
    \brief File containing implementation of LauResonanceMaker class.
*/

#include <iostream>
using std::cout;
using std::endl;

#include "LauAbsResonance.hh"
#include "LauBelleNR.hh"
#include "LauBelleSymNR.hh"
#include "LauBreitWignerRes.hh"
#include "LauDabbaRes.hh"
#include "LauDaughters.hh"
#include "LauFlatteRes.hh"
#include "LauGounarisSakuraiRes.hh"
#include "LauKappaRes.hh"
#include "LauLASSRes.hh"
#include "LauLASSBWRes.hh"
#include "LauLASSNRRes.hh"
#include "LauNRAmplitude.hh"
#include "LauPolNR.hh"
#include "LauRelBreitWignerRes.hh"
#include "LauResonanceInfo.hh"
#include "LauResonanceMaker.hh"
#include "LauSigmaRes.hh"

ClassImp(LauResonanceMaker)


LauResonanceMaker::LauResonanceMaker(const LauDaughters* daughters) :
	nResDefMax_(0),
	daughters_(daughters)
{
	this->createResonanceVector();
}

LauResonanceMaker::~LauResonanceMaker()
{
}

void LauResonanceMaker::createResonanceVector() 
{
	// Function to create all possible resonances that this class supports.
	// Also add in the sigma and kappa - but a special paramterisation is used
	// instead of the PDG "pole mass and width" values.

	cout<<"In createResonanceVector: setting up possible resonance states..."<<endl;

	// Define the resonance names and store them in the array
	resInfo_.clear();
	resInfo_.reserve(100);
	// rho resonances                   name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// rho(770)
	resInfo_.push_back(LauResonanceInfo("rho0(770)",     0.77549,   0.1491,  1,     0,      5.3));
	resInfo_.push_back(LauResonanceInfo("rho+(770)",     0.77549,   0.1491,  1,    +1,      5.3));
	resInfo_.push_back(LauResonanceInfo("rho-(770)",     0.77549,   0.1491,  1,    -1,      5.3));
	// rho(1450)
	resInfo_.push_back(LauResonanceInfo("rho0(1450)",    1.465,    0.400,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("rho+(1450)",    1.465,    0.400,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("rho-(1450)",    1.465,    0.400,   1,    -1          ));
	// rho(1700)
	resInfo_.push_back(LauResonanceInfo("rho0(1700)",    1.720,    0.250,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("rho+(1700)",    1.720,    0.250,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("rho-(1700)",    1.720,    0.250,   1,    -1          ));

	// K* resonances                    name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// K*(892)
	resInfo_.push_back(LauResonanceInfo("K*0(892)",      0.89594,  0.0487,  1,     0,      3.4));
	resInfo_.push_back(LauResonanceInfo("K*+(892)",      0.89166,  0.0508,  1,    +1,      3.4));
	resInfo_.push_back(LauResonanceInfo("K*-(892)",      0.89166,  0.0508,  1,    -1,      3.4));
	// K*(1410)
	resInfo_.push_back(LauResonanceInfo("K*0(1410)",     1.414,    0.232,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("K*+(1410)",     1.414,    0.232,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("K*-(1410)",     1.414,    0.232,   1,    -1          ));
	// K*_0(1430)
	resInfo_.push_back(LauResonanceInfo("K*0_0(1430)",   1.425,    0.270,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("K*+_0(1430)",   1.425,    0.270,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("K*-_0(1430)",   1.425,    0.270,   0,    -1          ));
	// K*_2(1430)
	resInfo_.push_back(LauResonanceInfo("K*0_2(1430)",   1.4324,   0.109,   2,     0          ));
	resInfo_.push_back(LauResonanceInfo("K*+_2(1430)",   1.4256,   0.0985,  2,    +1          ));
	resInfo_.push_back(LauResonanceInfo("K*-_2(1430)",   1.4256,   0.0985,  2,    -1          ));
	// K*(1680)
	resInfo_.push_back(LauResonanceInfo("K*0(1680)",     1.717,    0.322,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("K*+(1680)",     1.717,    0.322,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("K*-(1680)",     1.717,    0.322,   1,    -1          ));

	// phi resonances                   name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// phi(1020)
	resInfo_.push_back(LauResonanceInfo("phi(1020)",     1.019455, 0.00426, 1,     0          ));
	// phi(1680)
	resInfo_.push_back(LauResonanceInfo("phi(1680)",     1.680,    0.150,   1,     0          ));

	// f resonances                     name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// f_0(980)
	resInfo_.push_back(LauResonanceInfo("f_0(980)",      0.990,    0.070,   0,     0          ));
	// f_2(1270)
	resInfo_.push_back(LauResonanceInfo("f_2(1270)",     1.2751,   0.1851,  2,     0          ));
	// f_0(1370)
	resInfo_.push_back(LauResonanceInfo("f_0(1370)",     1.370,    0.350,   0,     0          ));
	// f'_0(1300), from Belle's Kspipi paper
	resInfo_.push_back(LauResonanceInfo("f'_0(1300)",    1.449,    0.126,   0,     0          ));
	// f_0(1500)
	resInfo_.push_back(LauResonanceInfo("f_0(1500)",     1.505,    0.109,   0,     0          ));
	// f'_2(1525)
	resInfo_.push_back(LauResonanceInfo("f'_2(1525)",    1.525,    0.073,   2,     0          ));

	// omega resonances                 name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
        // omega(782)
        resInfo_.push_back(LauResonanceInfo("omega(782)",    0.78265,  0.00849, 1,     0          ));

	// a resonances                     name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// a_0(980)
	resInfo_.push_back(LauResonanceInfo("a0_0(980)",     0.9847,   0.092,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("a+_0(980)",     0.9847,   0.092,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("a-_0(980)",     0.9847,   0.092,   0,    -1          ));
	// a_0(1450)
	resInfo_.push_back(LauResonanceInfo("a0_0(1450)",    1.474,    0.265,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("a+_0(1450)",    1.474,    0.265,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("a-_0(1450)",    1.474,    0.265,   0,    -1          ));
	// a_2(1320)
	resInfo_.push_back(LauResonanceInfo("a0_2(1320)",    1.3183,   0.107,   2,     0          ));
	resInfo_.push_back(LauResonanceInfo("a+_2(1320)",    1.3183,   0.107,   2,    +1          ));
	resInfo_.push_back(LauResonanceInfo("a-_2(1320)",    1.3183,   0.107,   2,    -1          ));

	// charmonium resonances            name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// chi_c0
	resInfo_.push_back(LauResonanceInfo("chi_c0",        3.41475,  0.0104,  0,     0          ));
	// chi_c2
	resInfo_.push_back(LauResonanceInfo("chi_c2",        3.55620,  0.00198, 2,     0          ));
	// X(3872)
	resInfo_.push_back(LauResonanceInfo("X(3872)",       3.87168,   0.0012,  1,     0          ));

	// unknown scalars                  name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// sigma
	resInfo_.push_back(LauResonanceInfo("sigma0",        0.560,    0.500,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("sigma+",        0.560,    0.500,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("sigma-",        0.560,    0.500,   0,    -1          ));
	// kappa
	resInfo_.push_back(LauResonanceInfo("kappa0",        0.720,    0.700,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("kappa+",        0.720,    0.700,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("kappa-",        0.720,    0.700,   0,    -1          ));
	// dabba
	resInfo_.push_back(LauResonanceInfo("dabba0",        2.098,    0.520,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("dabba+",        2.098,    0.520,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("dabba-",        2.098,    0.520,   0,    -1          ));

	// excited charm states             name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// D*
	resInfo_.push_back(LauResonanceInfo("D*0",           2.00698,   0.0021,  1,     0          ));
	resInfo_.push_back(LauResonanceInfo("D*+",           2.01028,   0.000096, 1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("D*-",           2.01028,   0.000096, 1,    -1          ));
	// D*_0
	resInfo_.push_back(LauResonanceInfo("D*0_0",         2.318,    0.267,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("D*+_0",         2.403,    0.283,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("D*-_0",         2.403,    0.283,   0,    -1          ));
	// D*_2
	resInfo_.push_back(LauResonanceInfo("D*0_2",         2.4626,   0.049,   2,     0          ));
	//AVERAGE--resInfo_.push_back(LauResonanceInfo("D*0_2",         2.4618,   0.049,   2,     0          ));
	resInfo_.push_back(LauResonanceInfo("D*+_2",         2.4644,    0.037,   2,    +1          ));
	resInfo_.push_back(LauResonanceInfo("D*-_2",         2.4644,    0.037,   2,    -1          ));
	// D1(2420)
	resInfo_.push_back(LauResonanceInfo("D1(2420)",     2.4213,   0.0271,  1,     0          ));
	// D(2600)
	//OLD--resInfo_.push_back(LauResonanceInfo("D0(2600)",      2.6087,   0.093,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("D0(2600)",      2.612,   0.093,   0,     0          ));
	resInfo_.push_back(LauResonanceInfo("D+(2600)",      2.6213,   0.093,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("D-(2600)",      2.6213,   0.093,   0,    -1          ));
	// D(2760)
	//OLD--resInfo_.push_back(LauResonanceInfo("D0(2760)",      2.7633,   0.061,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("D0(2760)",      2.761,   0.063,   1,     0          ));
	resInfo_.push_back(LauResonanceInfo("D+(2760)",      2.7697,   0.061,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("D-(2760)",      2.7697,   0.061,   1,    -1          ));
	// D(2900)
	resInfo_.push_back(LauResonanceInfo("D0(3000)",      3.0,   0.15,   0,     0          ));
	// D(3400)
	resInfo_.push_back(LauResonanceInfo("D0(3400)",      3.4,   0.15,   0,     0          ));

	// excited strange charm states             name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)
	// Ds*
	resInfo_.push_back(LauResonanceInfo("Ds*+",       2.1123,    0.002,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("Ds*-",       2.1123,    0.002,   1,    -1          ));
	// Ds0*(2317)
	resInfo_.push_back(LauResonanceInfo("Ds0*+(2317)",       2.3178,    0.004,   0,    +1          ));
	resInfo_.push_back(LauResonanceInfo("Ds0*-(2317)",       2.3178,    0.004,   0,    -1          ));
	// Ds2*(2573)
	resInfo_.push_back(LauResonanceInfo("Ds2*+(2573)",       2.5719,    0.017,   2,    +1          ));
	resInfo_.push_back(LauResonanceInfo("Ds2*-(2573)",       2.5719,    0.017,   2,    -1          ));
	// Ds1*(2700)
	resInfo_.push_back(LauResonanceInfo("Ds1*+(2700)",       2.709,    0.125,   1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("Ds1*-(2700)",       2.709,    0.125,   1,    -1          ));

	// excited bottom states
	// B*
	resInfo_.push_back(LauResonanceInfo("B*0",           5.3252,   0.00,    1,     0          ));
	resInfo_.push_back(LauResonanceInfo("B*+",           5.3250,   0.00,    1,    +1          ));
	resInfo_.push_back(LauResonanceInfo("B*-",           5.3250,   0.00,    1,    -1          ));

	// excited strange bottom states
	// Bs*
	resInfo_.push_back(LauResonanceInfo("Bs*0",          5.4154,   0.00,    1,    0          ));
	
        // nonresonant models               name,            mass,     width,   spin, charge, range parameter (defaults to 4.0)               
        // Phase-space nonresonant model                                                                                                      
        resInfo_.push_back(LauResonanceInfo("NonReson",      0.0,      0.0,     0,     0          ));
        // Theory-based nonresonant model                                                                                                     
        resInfo_.push_back(LauResonanceInfo("NRModel",       0.0,      0.0,     0,     0          ));
        // Babar nonresonant polynomial model                                                                                                 
        resInfo_.push_back(LauResonanceInfo("BabarNR",       0.0,      0.0,     0,     0          ));
        // Belle nonresonant models                                                                                                           
        resInfo_.push_back(LauResonanceInfo("BelleSymNR",    0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("BelleNR",       0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("BelleNR_Swave", 0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("BelleNR_Pwave", 0.0,      0.0,     1,     0          ));
        resInfo_.push_back(LauResonanceInfo("BelleNR_Dwave", 0.0,      0.0,     2,     0          ));

	// Polynomial nonresonant models
        resInfo_.push_back(LauResonanceInfo("PolNR",         0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_S0",      0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_S1",      0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_S2",      0.0,      0.0,     0,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_P0",      0.0,      0.0,     1,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_P1",      0.0,      0.0,     1,     0          ));
        resInfo_.push_back(LauResonanceInfo("PolNR_P2",      0.0,      0.0,     1,     0          ));


        // Taylor expansion nonresonant model                                                                                                 
        resInfo_.push_back(LauResonanceInfo("NRTaylor",      0.0,      0.0,     0,     0          ));
        // LASS nonresonant model                                                                                                             
        resInfo_.push_back(LauResonanceInfo("LASSNR",        1.412,    0.294,   0,     0          ));

	nResDefMax_ = resInfo_.size();
}

LauAbsResonance* LauResonanceMaker::getResonance(const TString& resName, Int_t resPairAmpInt, const TString& resType)
{
	// Routine to return the appropriate LauAbsResonance object given the resonance
	// name (resName), which daughter is the bachelor track (resPairAmpInt = 1,2 or 3), 
	// and the resonance type ("BW" = Breit-Wigner, "Flatte" = Flatte distribution).

	Double_t resMass(0.0);
	Double_t resWidth(0.0);
	Int_t    resSpin(0);
	Int_t    resCharge(0);
	//Double_t resRange(0.0);

	Bool_t gotResonance(kFALSE);

	// Loop over all possible resonance states we have defined in 
	// createResonanceVector() until we get a match with the name of the resonance

	for (std::vector<LauResonanceInfo>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {

		if (resName == (*iter).getName()) {
			// We have recognised the resonance name. 
			cout<<"Creating resonance: "<<resName<<endl;

			resMass = (*iter).getMass();
			resWidth = (*iter).getWidth();
			resSpin = (*iter).getSpin();
			resCharge = (*iter).getCharge();
			//resRange = (*iter).getRange();

			// stop looping
			gotResonance = kTRUE;
			break;
		}
	}

	// if we couldn't find the right resonance then we should return a null pointer
	if (!gotResonance) {
		return 0;
	}

	LauAbsResonance* theResonance(0);

	// Now construct the resonnace using the right type.
	// If we don't recognise the resonance model name, just use a simple Breit-Wigner.

	TString resTypeName(resType); resTypeName.ToLower();

	if (!resTypeName.CompareTo("flatte")) {

		// Flatte distribution - coupled channel Breit-Wigner
		theResonance = 
			new LauFlatteRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if (!resTypeName.CompareTo("relbw")) {

		// Relativistic Breit-Wigner with Blatt-Weisskopf factors.
		theResonance = 
			new LauRelBreitWignerRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);
		// Set the Blatt-Weisskopf barrier radius for the resonance and its parent
		//LauRelBreitWignerRes * theRBW = dynamic_cast<LauRelBreitWignerRes*>(theResonance);
		//Double_t parentRange = 4.0;
		//theRBW->setBarrierRadii(resRange, parentRange);

	} else if (!resTypeName.CompareTo("dabba")) {

		// Dabba model - should only be used for the D-pi system
		theResonance = 
			new LauDabbaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if (!resTypeName.CompareTo("kappa")) {

		// Kappa model - should only be used for the K-pi system
		theResonance = 
			new LauKappaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if (!resTypeName.CompareTo("sigma")) {

		// Sigma model - should only be used for the pi-pi system
		theResonance = 
			new LauSigmaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if (!resTypeName.CompareTo("lass-bw")) {

		// LASS function to try and model the K-pi S-wave better
		theResonance = 
			new LauLASSBWRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);		  

	} else if (!resTypeName.CompareTo("lass-nr")) {

		// LASS function to try and model the K-pi S-wave better
		theResonance = 
			new LauLASSNRRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);		  

	} else if (!resTypeName.CompareTo("lass")) {

		// LASS function to try and model the K-pi S-wave better
		theResonance = 
			new LauLASSRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);		  

	} else if (!resTypeName.CompareTo("gs")) {

		// Gounaris-Sakurai function to try and model the rho(770) better
		theResonance = 
			new LauGounarisSakuraiRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);		  

	} else if (!resTypeName.CompareTo("nrmodel")) {

		// NR amplitude model - arguments are there to preserve the interface
		theResonance =
			new LauNRAmplitude(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if ( !resTypeName.CompareTo("bellesymnr")  || !resTypeName.CompareTo("nrtaylor") ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		theResonance =
			new LauBelleSymNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else if ( !resTypeName.CompareTo("bellenr") ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		theResonance =
			new LauBelleNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);
	} else if ( !resTypeName.CompareTo("polnr") ) {

		// Polynomial NR amplitude model - arguments are there to preserve the interface
		theResonance =
			new LauPolNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters_);

	} else {

		// Simple non-relativistic Breit-Wigner
		theResonance = 
			new LauBreitWignerRes(resName, resMass, resWidth, resSpin,  resCharge,
					resPairAmpInt, daughters_);

	}

	return theResonance;

}

Int_t LauResonanceMaker::resTypeInt(const TString& name) const
{
	// Internal function that returns the resonance integer, specified by the
	// order of the resonance vector defined in createResonanceVector(),
	// for a given resonance name.
	Int_t resTypInt(-99);
	Int_t i(0);

	if (name.Contains("NonReson")) {

		resTypInt = -1;

	} else {

		for (std::vector<LauResonanceInfo>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {

			if (name.BeginsWith((*iter).getName(), TString::kExact) == kTRUE) {
				// We have recognised the resonance from those that are available
				resTypInt = i;
				return resTypInt;
			}
			++i;
		}
	}

	return resTypInt;
}

