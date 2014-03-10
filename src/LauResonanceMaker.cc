
// Copyright University of Warwick 2004 - 2014.
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

#include "LauAbsResonance.hh"
#include "LauBelleNR.hh"
#include "LauBelleSymNR.hh"
#include "LauBreitWignerRes.hh"
#include "LauDabbaRes.hh"
#include "LauDaughters.hh"
#include "LauFlatteRes.hh"
#include "LauFlatNR.hh"
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


LauResonanceMaker* LauResonanceMaker::resonanceMaker_ = 0;


LauResonanceMaker::LauResonanceMaker() :
	nResDefMax_(0)
{
	this->createResonanceVector();
}

LauResonanceMaker::~LauResonanceMaker()
{
}

LauResonanceMaker& LauResonanceMaker::get()
{
	if ( resonanceMaker_ == 0 ) {
		resonanceMaker_ = new LauResonanceMaker();
	}

	return *resonanceMaker_;
}

void LauResonanceMaker::createResonanceVector() 
{
	// Function to create all possible resonances that this class supports.
	// Also add in the sigma and kappa - but a special paramterisation is used
	// instead of the PDG "pole mass and width" values.

	std::cout << "INFO in LauResonanceMaker::createResonanceVector : Setting up possible resonance states..." << std::endl;

	LauResonanceInfo* neutral(0);
	LauResonanceInfo* positve(0);
	LauResonanceInfo* negatve(0);

	// Define the resonance names and store them in the array
	resInfo_.clear();
	resInfo_.reserve(100);
	// rho resonances              name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// rho(770)
	neutral = new LauResonanceInfo("rho0(770)",     0.77549,  0.1491,   1,     0,       5.3);
	positve = new LauResonanceInfo("rho+(770)",     0.77549,  0.1491,   1,     1,       5.3);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// rho(1450)
	neutral = new LauResonanceInfo("rho0(1450)",    1.465,    0.400,    1,     0           );
	positve = new LauResonanceInfo("rho+(1450)",    1.465,    0.400,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// rho(1700)
	neutral = new LauResonanceInfo("rho0(1700)",    1.720,    0.250,    1,     0           );
	positve = new LauResonanceInfo("rho+(1700)",    1.720,    0.250,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// K* resonances               name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// K*(892)
	neutral = new LauResonanceInfo("K*0(892)",      0.89594,  0.0487,   1,     0,       3.4);
	positve = new LauResonanceInfo("K*+(892)",      0.89166,  0.0508,   1,     1,       3.4);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*(1410)
	neutral = new LauResonanceInfo("K*0(1410)",     1.414,    0.232,    1,     0           );
	positve = new LauResonanceInfo("K*+(1410)",     1.414,    0.232,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*_0(1430)
	neutral = new LauResonanceInfo("K*0_0(1430)",   1.425,    0.270,    0,     0           );
	positve = new LauResonanceInfo("K*+_0(1430)",   1.425,    0.270,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*_2(1430)
	neutral = new LauResonanceInfo("K*0_2(1430)",   1.4324,   0.109,    2,     0           );
	positve = new LauResonanceInfo("K*+_2(1430)",   1.4256,   0.0985,   2,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*(1680)
	neutral = new LauResonanceInfo("K*0(1680)",     1.717,    0.322,    1,     0           );
	positve = new LauResonanceInfo("K*+(1680)",     1.717,    0.322,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// phi resonances              name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// phi(1020)
	neutral = new LauResonanceInfo("phi(1020)",     1.019455, 0.00426,  1,     0           );
	resInfo_.push_back( neutral );
	// phi(1680)
	neutral = new LauResonanceInfo("phi(1680)",     1.680,    0.150,    1,     0           );
	resInfo_.push_back( neutral );

	// f resonances                name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// f_0(980)
	neutral = new LauResonanceInfo("f_0(980)",      0.990,    0.070,    0,     0           );
	resInfo_.push_back( neutral );
	// f_2(1270)
	neutral = new LauResonanceInfo("f_2(1270)",     1.2751,   0.1851,   2,     0           );
	resInfo_.push_back( neutral );
	// f_0(1370)
	neutral = new LauResonanceInfo("f_0(1370)",     1.370,    0.350,    0,     0           );
	resInfo_.push_back( neutral );
	// f'_0(1300), from Belle's Kspipi paper
	neutral = new LauResonanceInfo("f'_0(1300)",    1.449,    0.126,    0,     0           );
	resInfo_.push_back( neutral );
	// f_0(1500)
	neutral = new LauResonanceInfo("f_0(1500)",     1.505,    0.109,    0,     0           );
	resInfo_.push_back( neutral );
	// f'_2(1525)
	neutral = new LauResonanceInfo("f'_2(1525)",    1.525,    0.073,    2,     0           );
	resInfo_.push_back( neutral );
	// f_0(1710)
	neutral = new LauResonanceInfo("f_0(1710)",     1.720,    0.135,    0,     0           );
	resInfo_.push_back( neutral );

	// omega resonances            name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
        // omega(782)
        neutral = new LauResonanceInfo("omega(782)",    0.78265,  0.00849,  1,     0           );
	resInfo_.push_back( neutral );

	// a resonances                name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// a_0(980)
	neutral = new LauResonanceInfo("a0_0(980)",     0.9847,   0.092,    0,     0           );
	positve = new LauResonanceInfo("a+_0(980)",     0.9847,   0.092,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// a_0(1450)
	neutral = new LauResonanceInfo("a0_0(1450)",    1.474,    0.265,    0,     0           );
	positve = new LauResonanceInfo("a+_0(1450)",    1.474,    0.265,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// a_2(1320)
	neutral = new LauResonanceInfo("a0_2(1320)",    1.3183,   0.107,    2,     0           );
	positve = new LauResonanceInfo("a+_2(1320)",    1.3183,   0.107,    2,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// charmonium resonances       name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// chi_c0
	neutral = new LauResonanceInfo("chi_c0",        3.41475,  0.0104,   0,     0           );
	resInfo_.push_back( neutral );
	// chi_c2
	neutral = new LauResonanceInfo("chi_c2",        3.55620,  0.00198,  2,     0           );
	resInfo_.push_back( neutral );
	// X(3872)
	neutral = new LauResonanceInfo("X(3872)",       3.87168,   0.0012,   1,    0           );
	resInfo_.push_back( neutral );

	// unknown scalars             name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// sigma
	neutral = new LauResonanceInfo("sigma0",        0.560,    0.500,    0,     0           );
	positve = new LauResonanceInfo("sigma+",        0.560,    0.500,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// kappa
	neutral = new LauResonanceInfo("kappa0",        0.720,    0.700,    0,     0           );
	positve = new LauResonanceInfo("kappa+",        0.720,    0.700,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// dabba
	neutral = new LauResonanceInfo("dabba0",        2.098,    0.520,    0,     0           );
	positve = new LauResonanceInfo("dabba+",        2.098,    0.520,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited charm states        name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// D*
	neutral = new LauResonanceInfo("D*0",           2.00698,  0.0021,   1,     0           );
	positve = new LauResonanceInfo("D*+",           2.01028,  0.000096, 1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D*_0
	neutral = new LauResonanceInfo("D*0_0",         2.318,    0.267,    0,     0           );
	positve = new LauResonanceInfo("D*+_0",         2.403,    0.283,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D*_2
	//AVERAGE--neutral = new LauResonanceInfo("D*0_2",         2.4618,   0.049,    2,     0           );
	neutral = new LauResonanceInfo("D*0_2",         2.4626,   0.049,    2,     0           );
	positve = new LauResonanceInfo("D*+_2",         2.4644,   0.037,    2,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D1(2420)
	neutral = new LauResonanceInfo("D1(2420)",      2.4213,   0.0271,   1,     0           );
	resInfo_.push_back( neutral );
	// D(2600)
	//OLD--neutral = new LauResonanceInfo("D0(2600)",      2.6087,   0.093,    0,     0           );
	neutral = new LauResonanceInfo("D0(2600)",      2.612,    0.093,    0,     0           );
	positve = new LauResonanceInfo("D+(2600)",      2.6213,   0.093,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D(2760)
	//OLD--	neutral = new LauResonanceInfo("D0(2760)",      2.7633,   0.061,    1,     0           );
	neutral = new LauResonanceInfo("D0(2760)",      2.761,    0.063,    1,     0           );
	positve = new LauResonanceInfo("D+(2760)",      2.7697,   0.061,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D(2900)
	neutral = new LauResonanceInfo("D0(3000)",      3.0,      0.15,     0,     0           );
	resInfo_.push_back( neutral );
	// D(3400)
	neutral = new LauResonanceInfo("D0(3400)",      3.4,      0.15,     0,     0           );
	resInfo_.push_back( neutral );

	// excited strange charm       name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// Ds*
	positve = new LauResonanceInfo("Ds*+",          2.1123,   0.002,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds0*(2317)
	positve = new LauResonanceInfo("Ds0*+(2317)",   2.3178,   0.004,    0,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds2*(2573)
	positve = new LauResonanceInfo("Ds2*+(2573)",   2.5719,   0.017,    2,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds1*(2700)
	positve = new LauResonanceInfo("Ds1*+(2700)",   2.709,    0.125,    1,     1           );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited bottom states       name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// B*
	neutral = new LauResonanceInfo("B*0",           5.3252,   0.00,     1,     0,       6.0);
	positve = new LauResonanceInfo("B*+",           5.3250,   0.00,     1,     1,       6.0);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited strange bottom      name,            mass,     width,    spin,  charge,  range parameter (defaults to 4.0)
	// Bs*
	neutral = new LauResonanceInfo("Bs*0",          5.4154,   0.00,     1,     0,       6.0);
	resInfo_.push_back( neutral );
	
	// nonresonant models          name,            mass,     width,   spin,   charge,  range parameter (defaults to 4.0)
	// Phase-space nonresonant model
	neutral = new LauResonanceInfo("NonReson",      0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	// Theory-based nonresonant model
	neutral = new LauResonanceInfo("NRModel",       0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	// Belle nonresonant models
	neutral = new LauResonanceInfo("BelleSymNR",    0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	neutral = new LauResonanceInfo("BelleNR",       0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	neutral = new LauResonanceInfo("BelleNR_Swave", 0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	neutral = new LauResonanceInfo("BelleNR_Pwave", 0.0,      0.0,     1,      0           );
	resInfo_.push_back( neutral );
	neutral = new LauResonanceInfo("BelleNR_Dwave", 0.0,      0.0,     2,      0           );
	resInfo_.push_back( neutral );
	// Taylor expansion nonresonant model
	neutral = new LauResonanceInfo("NRTaylor",      0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
	// Polynomial nonresonant models
        neutral = new LauResonanceInfo("PolNR_S0",      0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_S1",      0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_S2",      0.0,      0.0,     0,      0           );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P0",      0.0,      0.0,     1,      0           );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P1",      0.0,      0.0,     1,      0           );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P2",      0.0,      0.0,     1,      0           );
	resInfo_.push_back( neutral );
	// LASS nonresonant model
	neutral = new LauResonanceInfo("LASSNR",        1.412,    0.294,   0,      0           );
	resInfo_.push_back( neutral );

	nResDefMax_ = resInfo_.size();
}

LauAbsResonance* LauResonanceMaker::getResonance(const LauDaughters* daughters, const TString& resName, Int_t resPairAmpInt, const TString& resType)
{
	// Routine to return the appropriate LauAbsResonance object given the resonance
	// name (resName), which daughter is the bachelor track (resPairAmpInt = 1,2 or 3), 
	// and the resonance type ("BW" = Breit-Wigner, "Flatte" = Flatte distribution).

	LauParameter* resMass(0);
	LauParameter* resWidth(0);
	Int_t    resSpin(0);
	Int_t    resCharge(0);
	//Double_t resRange(0.0);

	Bool_t gotResonance(kFALSE);

	// Loop over all possible resonance states we have defined in 
	// createResonanceVector() until we get a match with the name of the resonance

	for (std::vector<LauResonanceInfo*>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {

		if (resName == (*iter)->getName()) {
			// We have recognised the resonance name. 
			std::cout<<"INFO in LauResonanceMaker::getResonance : Creating resonance: "<<resName<<std::endl;

			resMass = (*iter)->getMass();
			resWidth = (*iter)->getWidth();
			resSpin = (*iter)->getSpin();
			resCharge = (*iter)->getCharge();
			//resRange = (*iter)->getRange();

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
		std::cout<<"                                        : Using Flatte lineshape. "<<std::endl;
		theResonance = 
			new LauFlatteRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("relbw")) {

		// Relativistic Breit-Wigner with Blatt-Weisskopf factors.
		std::cout<<"                                        : Using relativistic Breit-Wigner lineshape. "<<std::endl;
		theResonance = 
			new LauRelBreitWignerRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);
		// Set the Blatt-Weisskopf barrier radius for the resonance and its parent
		//LauRelBreitWignerRes * theRBW = dynamic_cast<LauRelBreitWignerRes*>(theResonance);
		//Double_t parentRange = 4.0;
		//theRBW->setBarrierRadii(resRange, parentRange);

	} else if (!resTypeName.CompareTo("dabba")) {

		// Dabba model - should only be used for the D-pi system
		std::cout<<"                                        : Using Dabba lineshape. "<<std::endl;
		theResonance = 
			new LauDabbaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("kappa")) {

		// Kappa model - should only be used for the K-pi system
		std::cout<<"                                        : Using Kappa lineshape. "<<std::endl;
		theResonance = 
			new LauKappaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("sigma")) {

		// Sigma model - should only be used for the pi-pi system
		std::cout<<"                                        : Using Sigma lineshape. "<<std::endl;
		theResonance = 
			new LauSigmaRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("lass-bw")) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape (resonant part only). "<<std::endl;
		theResonance = 
			new LauLASSBWRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);		  

	} else if (!resTypeName.CompareTo("lass-nr")) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape (nonresonant part only). "<<std::endl;
		theResonance = 
			new LauLASSNRRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);		  

	} else if (!resTypeName.CompareTo("lass")) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape. "<<std::endl;
		theResonance = 
			new LauLASSRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);		  

	} else if (!resTypeName.CompareTo("gs")) {

		// Gounaris-Sakurai function to try and model the rho(770) better
		std::cout<<"                                        : Using Gounaris-Sakurai lineshape. "<<std::endl;
		theResonance = 
			new LauGounarisSakuraiRes(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);		  

	} else if (!resTypeName.CompareTo("flatnr")) {

		// uniform NR amplitude - arguments are there to preserve the interface
		std::cout<<"                                        : Using uniform NR lineshape. "<<std::endl;
		theResonance =
			new LauFlatNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("nrmodel")) {

		// NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using NR-model lineshape. "<<std::endl;
		theResonance =
			new LauNRAmplitude(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if ( !resTypeName.CompareTo("bellesymnr")  || !resTypeName.CompareTo("nrtaylor") ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using Belle symmetric NR lineshape. "<<std::endl;
		theResonance =
			new LauBelleSymNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if ( !resTypeName.CompareTo("bellenr") ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using Belle NR lineshape. "<<std::endl;
		theResonance =
			new LauBelleNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);
	} else if ( !resTypeName.CompareTo("polnr") ) {

		// Polynomial NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using polynomial NR lineshape. "<<std::endl;
		theResonance =
			new LauPolNR(resName, resMass, resWidth, resSpin, resCharge,
					resPairAmpInt, daughters);

	} else if (!resTypeName.CompareTo("bw")) {

		// Simple non-relativistic Breit-Wigner
		std::cout<<"                                        : Using simple Breit-Wigner lineshape. "<<std::endl;
		theResonance = 
			new LauBreitWignerRes(resName, resMass, resWidth, resSpin,  resCharge,
					resPairAmpInt, daughters);

	} else {
		std::cerr << "ERROR in LauResonanceMaker::getResonance : Could not match resonace type \"" << resTypeName << "\"." << std::endl;
		return 0;
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

	for (std::vector<LauResonanceInfo*>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {

		if (name.BeginsWith((*iter)->getName(), TString::kExact) == kTRUE) {
			// We have recognised the resonance from those that are available
			resTypInt = i;
			return resTypInt;
		}
		++i;
	}

	return resTypInt;
}

std::vector<LauParameter*> LauResonanceMaker::getFloatingParameters()
{
	std::vector<LauParameter*> param;

	for (std::vector<LauResonanceInfo*>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {
		LauParameter* massPar = (*iter)->getMass();
		if ( (!massPar->fixed()) && (!massPar->clone()) ) {
			std::cout << "INFO in LauResonanceMaker::getFloatingParameters: resNameMass = " << massPar->name() << ", fixed = "<< massPar->fixed() << std::endl;
			param.push_back(massPar);
		}

		LauParameter* widthPar = (*iter)->getWidth();
		if ( (!widthPar->fixed()) && (!widthPar->clone()) ) {
			std::cout << "INFO in LauResonanceMaker::getFloatingParameters: resNameWidth = " << widthPar->name() << ", fixed = "<< widthPar->fixed() << std::endl;
			param.push_back(widthPar);
		}
	}

	return param;
}

void LauResonanceMaker::printAll( ostream& stream ) const
{
	for ( std::vector<LauResonanceInfo*>::const_iterator iter = resInfo_.begin(); iter != resInfo_.end(); ++iter ) {
		stream << (**iter) << std::endl;
	}
}

