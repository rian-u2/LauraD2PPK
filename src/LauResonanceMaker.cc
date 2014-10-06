
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
#include "LauModIndPartWave.hh"
#include "LauGaussIncohRes.hh"
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
	this->setDefaultBWRadius( LauBlattWeisskopfFactor::Parent, 4.0 );
}

LauResonanceMaker::~LauResonanceMaker()
{
	for ( std::vector<LauBlattWeisskopfFactor*>::iterator iter = bwIndepFactors_.begin(); iter != bwIndepFactors_.end(); ++iter ) {
		delete *iter;
	}
	bwIndepFactors_.clear();
	for ( BWFactorCategoryMap::iterator iter = bwFactors_.begin(); iter != bwFactors_.end(); ++iter ) {
		delete iter->second;
	}
	bwFactors_.clear();
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
	// rho resonances              name,            mass,     width,    spin,  charge,  default BW category,             BW radius parameter (defaults to 4.0)
	// rho(770)
	neutral = new LauResonanceInfo("rho0(770)",     0.77526,  0.1478,   1,     0,       LauBlattWeisskopfFactor::Light,  5.3);
	positve = new LauResonanceInfo("rho+(770)",     0.77511,  0.1491,   1,     1,       LauBlattWeisskopfFactor::Light,  5.3);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// rho(1450)
	neutral = new LauResonanceInfo("rho0(1450)",    1.465,    0.400,    1,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("rho+(1450)",    1.465,    0.400,    1,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// rho(1700)
	neutral = new LauResonanceInfo("rho0(1700)",    1.720,    0.250,    1,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("rho+(1700)",    1.720,    0.250,    1,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// K* resonances               name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// K*(892)
	neutral = new LauResonanceInfo("K*0(892)",      0.89581,  0.0474,   1,     0,       LauBlattWeisskopfFactor::Kstar,  3.0);
	positve = new LauResonanceInfo("K*+(892)",      0.89166,  0.0508,   1,     1,       LauBlattWeisskopfFactor::Kstar,  3.0);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*(1410)
	neutral = new LauResonanceInfo("K*0(1410)",     1.414,    0.232,    1,     0,       LauBlattWeisskopfFactor::Kstar   );
	positve = new LauResonanceInfo("K*+(1410)",     1.414,    0.232,    1,     1,       LauBlattWeisskopfFactor::Kstar   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*_0(1430)
	neutral = new LauResonanceInfo("K*0_0(1430)",   1.425,    0.270,    0,     0,       LauBlattWeisskopfFactor::Kstar   );
	positve = new LauResonanceInfo("K*+_0(1430)",   1.425,    0.270,    0,     1,       LauBlattWeisskopfFactor::Kstar   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// LASS nonresonant model
	neutral = neutral->createSharedParameterRecord("LASSNR0");
	positve = positve->createSharedParameterRecord("LASSNR+");
	negatve = negatve->createSharedParameterRecord("LASSNR-");
	resInfo_.push_back( neutral );
	// K*_2(1430)
	neutral = new LauResonanceInfo("K*0_2(1430)",   1.4324,   0.109,    2,     0,       LauBlattWeisskopfFactor::Kstar   );
	positve = new LauResonanceInfo("K*+_2(1430)",   1.4256,   0.0985,   2,     1,       LauBlattWeisskopfFactor::Kstar   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// K*(1680)
	neutral = new LauResonanceInfo("K*0(1680)",     1.717,    0.322,    1,     0,       LauBlattWeisskopfFactor::Kstar   );
	positve = new LauResonanceInfo("K*+(1680)",     1.717,    0.322,    1,     1,       LauBlattWeisskopfFactor::Kstar   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// phi resonances              name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// phi(1020)
	neutral = new LauResonanceInfo("phi(1020)",     1.019461, 0.004266, 1,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// phi(1680)
	neutral = new LauResonanceInfo("phi(1680)",     1.680,    0.150,    1,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );

	// f resonances                name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// f_0(980)
	neutral = new LauResonanceInfo("f_0(980)",      0.990,    0.070,    0,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f_2(1270)
	neutral = new LauResonanceInfo("f_2(1270)",     1.2751,   0.1851,   2,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f_0(1370)
	neutral = new LauResonanceInfo("f_0(1370)",     1.370,    0.350,    0,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f'_0(1300), from Belle's Kspipi paper
	neutral = new LauResonanceInfo("f'_0(1300)",    1.449,    0.126,    0,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f_0(1500)
	neutral = new LauResonanceInfo("f_0(1500)",     1.505,    0.109,    0,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f'_2(1525)
	neutral = new LauResonanceInfo("f'_2(1525)",    1.525,    0.073,    2,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f_0(1710)
	neutral = new LauResonanceInfo("f_0(1710)",     1.722,    0.135,    0,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// f_2(2010)
	neutral = new LauResonanceInfo("f_2(2010)",     2.011,    0.202,    2,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );

	// omega resonances            name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
        // omega(782)
        neutral = new LauResonanceInfo("omega(782)",    0.78265,  0.00849,  1,     0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );

	// a resonances                name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// a_0(980)
	neutral = new LauResonanceInfo("a0_0(980)",     0.980,    0.092,    0,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("a+_0(980)",     0.980,    0.092,    0,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// a_0(1450)
	neutral = new LauResonanceInfo("a0_0(1450)",    1.474,    0.265,    0,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("a+_0(1450)",    1.474,    0.265,    0,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// a_2(1320)
	neutral = new LauResonanceInfo("a0_2(1320)",    1.3190,   0.1050,   2,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("a+_2(1320)",    1.3190,   0.1050,   2,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// charmonium resonances       name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// chi_c0
	neutral = new LauResonanceInfo("chi_c0",        3.41475,  0.0105,   0,     0,       LauBlattWeisskopfFactor::Charmonium   );
	resInfo_.push_back( neutral );
	// chi_c1
	neutral = new LauResonanceInfo("chi_c1",        3.51066,  0.00084,  0,     0,       LauBlattWeisskopfFactor::Charmonium   );
	resInfo_.push_back( neutral );
	// chi_c2
	neutral = new LauResonanceInfo("chi_c2",        3.55620,  0.00193,  2,     0,       LauBlattWeisskopfFactor::Charmonium   );
	resInfo_.push_back( neutral );
	// X(3872)
	neutral = new LauResonanceInfo("X(3872)",       3.87169,   0.0012,  1,     0,       LauBlattWeisskopfFactor::Charmonium   );
	resInfo_.push_back( neutral );

	// unknown scalars             name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// sigma
	neutral = new LauResonanceInfo("sigma0",        0.475,    0.550,    0,     0,       LauBlattWeisskopfFactor::Light   );
	positve = new LauResonanceInfo("sigma+",        0.475,    0.550,    0,     1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// kappa
	neutral = new LauResonanceInfo("kappa0",        0.682,    0.547,    0,     0,       LauBlattWeisskopfFactor::Kstar   );
	positve = new LauResonanceInfo("kappa+",        0.682,    0.547,    0,     1,       LauBlattWeisskopfFactor::Kstar   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// dabba
	neutral = new LauResonanceInfo("dabba0",        2.098,    0.520,    0,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("dabba+",        2.098,    0.520,    0,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited charm states        name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// D*
	neutral = new LauResonanceInfo("D*0",           2.00696,  0.0021,   1,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D*+",           2.01026,  83.4e-6,  1,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D*_0
	neutral = new LauResonanceInfo("D*0_0",         2.318,    0.267,    0,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D*+_0",         2.403,    0.283,    0,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D*_2
	//AVERAGE--neutral = new LauResonanceInfo("D*0_2",         2.4618,   0.049,    2,     0           );
	neutral = new LauResonanceInfo("D*0_2",         2.4626,   0.049,    2,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D*+_2",         2.4643,   0.037,    2,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D1(2420)
	neutral = new LauResonanceInfo("D0_1(2420)",    2.4214,   0.0274,   1,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D+_1(2420)",    2.4232,   0.025,    1,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D(2600)
	//OLD--neutral = new LauResonanceInfo("D0(2600)",      2.6087,   0.093,    0,     0           );
	//OLD--positve = new LauResonanceInfo("D+(2600)",      2.6213,   0.093,    0,     1           );
	neutral = new LauResonanceInfo("D0(2600)",      2.612,    0.093,    0,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D+(2600)",      2.612,    0.093,    0,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D(2760)
	//OLD--	neutral = new LauResonanceInfo("D0(2760)",      2.7633,   0.061,    1,     0           );
	//OLD--	positve = new LauResonanceInfo("D+(2760)",      2.7697,   0.061,    1,     1           );
	neutral = new LauResonanceInfo("D0(2760)",      2.761,    0.063,    1,     0,       LauBlattWeisskopfFactor::Charm   );
	positve = new LauResonanceInfo("D+(2760)",      2.761,    0.063,    1,     1,       LauBlattWeisskopfFactor::Charm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// D(2900)
	neutral = new LauResonanceInfo("D0(3000)",      3.0,      0.15,     0,     0,       LauBlattWeisskopfFactor::Charm   );
	resInfo_.push_back( neutral );
	// D(3400)
	neutral = new LauResonanceInfo("D0(3400)",      3.4,      0.15,     0,     0,       LauBlattWeisskopfFactor::Charm   );
	resInfo_.push_back( neutral );

	// excited strange charm       name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// Ds*
	positve = new LauResonanceInfo("Ds*+",          2.1121,   0.0019,   1,     1,       LauBlattWeisskopfFactor::StrangeCharm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds0*(2317)
	positve = new LauResonanceInfo("Ds*+_0(2317)",  2.3177,   0.0038,   0,     1,       LauBlattWeisskopfFactor::StrangeCharm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds2*(2573)
	positve = new LauResonanceInfo("Ds*+_2(2573)",  2.5719,   0.017,    2,     1,       LauBlattWeisskopfFactor::StrangeCharm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Ds1*(2700)
	positve = new LauResonanceInfo("Ds*+_1(2700)",  2.709,    0.117,    1,     1,       LauBlattWeisskopfFactor::StrangeCharm   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited bottom states       name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// B*
	neutral = new LauResonanceInfo("B*0",           5.3252,   0.00,     1,     0,       LauBlattWeisskopfFactor::Beauty,  6.0);
	positve = new LauResonanceInfo("B*+",           5.3252,   0.00,     1,     1,       LauBlattWeisskopfFactor::Beauty,  6.0);
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( neutral );
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );

	// excited strange bottom      name,            mass,     width,    spin,  charge,  BW category,    BW radius parameter (defaults to 4.0)
	// Bs*
	neutral = new LauResonanceInfo("Bs*0",          5.4154,   0.00,     1,     0,       LauBlattWeisskopfFactor::StrangeBeauty,  6.0);
	resInfo_.push_back( neutral );
	
	// nonresonant models          name,            mass,     width,   spin,   charge,  BW category,    BW radius parameter (defaults to 4.0)
	// Phase-space nonresonant model
	neutral = new LauResonanceInfo("NonReson",      0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// Theory-based nonresonant model
	neutral = new LauResonanceInfo("NRModel",       0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// Belle nonresonant models
	neutral = new LauResonanceInfo("BelleSymNR",    0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	neutral = new LauResonanceInfo("BelleNR",       0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	positve = new LauResonanceInfo("BelleNR+",      0.0,      0.0,     0,      1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	neutral = new LauResonanceInfo("BelleNR_Swave", 0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	positve = new LauResonanceInfo("BelleNR_Swave+",0.0,      0.0,     0,      1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	neutral = new LauResonanceInfo("BelleNR_Pwave", 0.0,      0.0,     1,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	positve = new LauResonanceInfo("BelleNR_Pwave+",0.0,      0.0,     1,      1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	neutral = new LauResonanceInfo("BelleNR_Dwave", 0.0,      0.0,     2,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	positve = new LauResonanceInfo("BelleNR_Dwave+",0.0,      0.0,     2,      1,       LauBlattWeisskopfFactor::Light   );
	negatve = positve->createChargeConjugate();
	resInfo_.push_back( positve );
	resInfo_.push_back( negatve );
	// Taylor expansion nonresonant model
	neutral = new LauResonanceInfo("NRTaylor",      0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
	// Polynomial nonresonant models
        neutral = new LauResonanceInfo("PolNR_S0",      0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_S1",      0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_S2",      0.0,      0.0,     0,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P0",      0.0,      0.0,     1,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P1",      0.0,      0.0,     1,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );
        neutral = new LauResonanceInfo("PolNR_P2",      0.0,      0.0,     1,      0,       LauBlattWeisskopfFactor::Light   );
	resInfo_.push_back( neutral );

	nResDefMax_ = resInfo_.size();
}

void LauResonanceMaker::setDefaultBWRadius(const LauBlattWeisskopfFactor::BlattWeisskopfCategory bwCategory, const Double_t bwRadius)
{
	if ( bwCategory == LauBlattWeisskopfFactor::Default || bwCategory == LauBlattWeisskopfFactor::Indep ) {
		std::cerr << "WARNING in LauResonanceMaker::setDefaultBWRadius : cannot set radius values for Default or Indep categories" << std::endl;
	}
	bwDefaultRadii_[bwCategory] = bwRadius;
}

LauBlattWeisskopfFactor* LauResonanceMaker::getBWFactor( const LauBlattWeisskopfFactor::BlattWeisskopfCategory bwCategory, const LauResonanceInfo* resInfo, const LauBlattWeisskopfFactor::BarrierType bwType )
{
	LauBlattWeisskopfFactor* bwFactor(0);

	BWFactorCategoryMap::iterator factor_iter = bwFactors_.find( bwCategory );
	BWRadiusCategoryMap::iterator radius_iter = bwDefaultRadii_.find( bwCategory );

	if ( bwCategory == LauBlattWeisskopfFactor::Indep ) {
		bwFactor = new LauBlattWeisskopfFactor( *resInfo, bwType, bwCategory );
		bwIndepFactors_.push_back(bwFactor);
	} else if ( factor_iter == bwFactors_.end() ) {
		if ( radius_iter == bwDefaultRadii_.end() ) {
			bwFactor = new LauBlattWeisskopfFactor( *resInfo, bwType, bwCategory );
		} else {
			bwFactor = new LauBlattWeisskopfFactor( *resInfo, radius_iter->second, bwType, bwCategory );
		}
		bwFactors_[bwCategory] = bwFactor;
	} else {
		const UInt_t resSpin = resInfo->getSpin();
		bwFactor = factor_iter->second->createClone( resSpin );
		if ( bwFactor->getBarrierType() != bwType ) {
			std::cerr << "WARNING in LauResonanceMaker::getBWFactor : A barrier factor already exists for the specified category but does not have the specified barrier type.\n";
			std::cerr << "                                          : If you want to use that type you will need to use a different category for this resonance." << std::endl;
		}
	}

	return bwFactor;
}

LauAbsResonance* LauResonanceMaker::getResonance(const LauDaughters* daughters, const TString& resName, const Int_t resPairAmpInt, const LauAbsResonance::LauResonanceModel resType, const LauBlattWeisskopfFactor::BlattWeisskopfCategory bwCategory, const LauBlattWeisskopfFactor::BarrierType bwType)
{
	// Routine to return the appropriate LauAbsResonance object given the resonance
	// name (resName), which daughter is the bachelor track (resPairAmpInt = 1,2 or 3), 
	// and the resonance type ("BW" = Breit-Wigner, "Flatte" = Flatte distribution).

	// Loop over all possible resonance states we have defined in 
	// createResonanceVector() until we get a match with the name of the resonance

	LauResonanceInfo* resInfo(0);
	for (std::vector<LauResonanceInfo*>::const_iterator iter=resInfo_.begin(); iter!=resInfo_.end(); ++iter) {

		if (resName == (*iter)->getName()) {
			// We have recognised the resonance name. 
			std::cout<<"INFO in LauResonanceMaker::getResonance : Creating resonance: "<<resName<<std::endl;

			resInfo = (*iter);

			// stop looping
			break;
		}
	}

	// if we couldn't find the right resonance then we should return a null pointer
	if ( resInfo == 0 ) {
		std::cout<<"WARNING in LauResonanceMaker::getResonance : Creating resonance: "<<resName<<std::endl;
		return 0;
	}

	LauAbsResonance* theResonance(0);

	// Now construct the resonnace using the right type.
	// If we don't recognise the resonance model name, just use a simple Breit-Wigner.

	if ( resType == LauAbsResonance::Flatte ) {

		// Flatte distribution - coupled channel Breit-Wigner
		std::cout<<"                                        : Using Flatte lineshape. "<<std::endl;
		theResonance = 
			new LauFlatteRes(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::RelBW ) {

		// Relativistic Breit-Wigner with Blatt-Weisskopf factors.
		std::cout<<"                                        : Using relativistic Breit-Wigner lineshape. "<<std::endl;
		theResonance = 
			new LauRelBreitWignerRes(resInfo, resPairAmpInt, daughters);

		LauBlattWeisskopfFactor::BlattWeisskopfCategory parCategory = LauBlattWeisskopfFactor::Parent;
		LauBlattWeisskopfFactor::BlattWeisskopfCategory resCategory = bwCategory;
		if ( bwCategory == LauBlattWeisskopfFactor::Default ) {
			resCategory = resInfo->getBWCategory();
		}
		LauBlattWeisskopfFactor* resBWFactor = this->getBWFactor( resCategory, resInfo, bwType );
		LauBlattWeisskopfFactor* parBWFactor = this->getBWFactor( parCategory, resInfo, bwType );
		theResonance->setBarrierRadii( resBWFactor, parBWFactor );

	} else if ( resType == LauAbsResonance::Dabba ) {

		// Dabba model - should only be used for the D-pi system
		std::cout<<"                                        : Using Dabba lineshape. "<<std::endl;
		theResonance = 
			new LauDabbaRes(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::Kappa ) {

		// Kappa model - should only be used for the K-pi system
		std::cout<<"                                        : Using Kappa lineshape. "<<std::endl;
		theResonance = 
			new LauKappaRes(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::Sigma ) {

		// Sigma model - should only be used for the pi-pi system
		std::cout<<"                                        : Using Sigma lineshape. "<<std::endl;
		theResonance = 
			new LauSigmaRes(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::LASS_BW ) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape (resonant part only). "<<std::endl;
		theResonance = 
			new LauLASSBWRes(resInfo, resPairAmpInt, daughters);		  

	} else if ( resType == LauAbsResonance::LASS_NR ) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape (nonresonant part only). "<<std::endl;
		theResonance = 
			new LauLASSNRRes(resInfo, resPairAmpInt, daughters);		  

	} else if ( resType == LauAbsResonance::LASS ) {

		// LASS function to try and model the K-pi S-wave better
		std::cout<<"                                        : Using LASS lineshape. "<<std::endl;
		theResonance = 
			new LauLASSRes(resInfo, resPairAmpInt, daughters);		  

	} else if ( resType == LauAbsResonance::GS ) {

		// Gounaris-Sakurai function to try and model the rho(770) better
		std::cout<<"                                        : Using Gounaris-Sakurai lineshape. "<<std::endl;
		theResonance = 
			new LauGounarisSakuraiRes(resInfo, resPairAmpInt, daughters);		  

		LauBlattWeisskopfFactor::BlattWeisskopfCategory parCategory = LauBlattWeisskopfFactor::Parent;
		LauBlattWeisskopfFactor::BlattWeisskopfCategory resCategory = bwCategory;
		if ( bwCategory == LauBlattWeisskopfFactor::Default ) {
			resCategory = resInfo->getBWCategory();
		}
		LauBlattWeisskopfFactor* resBWFactor = this->getBWFactor( resCategory, resInfo, bwType );
		LauBlattWeisskopfFactor* parBWFactor = this->getBWFactor( parCategory, resInfo, bwType );
		theResonance->setBarrierRadii( resBWFactor, parBWFactor );

	} else if ( resType == LauAbsResonance::FlatNR ) {

		// uniform NR amplitude - arguments are there to preserve the interface
		std::cout<<"                                        : Using uniform NR lineshape. "<<std::endl;
		// we override resPairAmpInt here
		theResonance =
			new LauFlatNR(resInfo, 0, daughters);

	} else if ( resType == LauAbsResonance::NRModel ) {

		// NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using NR-model lineshape. "<<std::endl;
		// we override resPairAmpInt here
		theResonance =
			new LauNRAmplitude(resInfo, 0, daughters);

	} else if ( resType == LauAbsResonance::BelleSymNR || resType == LauAbsResonance::TaylorNR ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using Belle symmetric NR lineshape. "<<std::endl;
		theResonance =
			new LauBelleSymNR(resInfo, resType, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::BelleNR || resType == LauAbsResonance::PowerLawNR ) {

		// Belle NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using Belle NR lineshape. "<<std::endl;
		theResonance =
			new LauBelleNR(resInfo, resType, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::PolNR ) {

		// Polynomial NR amplitude model - arguments are there to preserve the interface
		std::cout<<"                                        : Using polynomial NR lineshape. "<<std::endl;
		theResonance =
			new LauPolNR(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::MIPW ) {

		// Model independent partial wave
		std::cout<<"                                        : Using model independent partial wave lineshape. "<<std::endl;
		theResonance =
			new LauModIndPartWave(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::GaussIncoh ) {

		// Incoherent Gaussian
		std::cout<<"                                        : Using incoherent Gaussian lineshape. "<<std::endl;
		theResonance =
			new LauGaussIncohRes(resInfo, resPairAmpInt, daughters);

	} else if ( resType == LauAbsResonance::BW ) {

		// Simple non-relativistic Breit-Wigner
		std::cout<<"                                        : Using simple Breit-Wigner lineshape. "<<std::endl;
		theResonance = 
			new LauBreitWignerRes(resInfo, resPairAmpInt, daughters);

	} else {
		std::cerr << "ERROR in LauResonanceMaker::getResonance : Could not match resonace type \"" << resType << "\"." << std::endl;
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

void LauResonanceMaker::printAll( ostream& stream ) const
{
	for ( std::vector<LauResonanceInfo*>::const_iterator iter = resInfo_.begin(); iter != resInfo_.end(); ++iter ) {
		stream << (**iter) << std::endl;
	}
}

