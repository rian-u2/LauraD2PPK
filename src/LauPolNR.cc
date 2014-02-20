
// Copyright University of Warwick 2004 - 2013.                                                                                               
// Distributed under the Boost Software License, Version 1.0.                                                                                 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)                                                    

// Authors:                                                                                                                                   
// Thomas Latham                                                                                                                              
// John Back                                                                                                                                  
// Paul Harrison                                                                                                                              

/*! \file LauPolNR.cc                                                                                                                         
    \brief File containing implementation of LauPolNR class.                                                                                  
*/

//****************************************************************************                                                                
// Class for defining the Polynomial Non-Resonant model                                                                                       
//****************************************************************************                                                                

// --CLASS DESCRIPTION [MODEL] --                                                                                                             
// Class for defining the  Polynomial Non-Resonant model.                                                                                     

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "TMath.h"

#include "LauPolNR.hh"
#include "LauDaughters.hh"

ClassImp(LauPolNR)


LauPolNR::LauPolNR(const TString& resName, Double_t resMass, Double_t resWidth, Int_t resSpin,
		   Int_t resCharge, Int_t resPairAmpInt, const LauDaughters* daughters) :
LauAbsResonance(resName, resMass, resWidth, resSpin, resCharge, resPairAmpInt, daughters),
  omega_(0.0)
{
  this->ignoreMomenta(kTRUE);
}

LauPolNR::~LauPolNR()
{
}

void LauPolNR::initialise()
{
  const LauDaughters* daughters = this->getDaughters();
  Int_t resPairAmpInt = this->getPairInt();
  if ( daughters->gotSymmetricalDP() && resPairAmpInt != 3 ) {
    cerr << "WARNING in LauPolNR::initialise : Dalitz plot is symmetric - this lineshape is not appropriate." << endl;
  }
}

LauComplex LauPolNR::resAmp(Double_t mass, Double_t spinTerm)
{
  Double_t magnitude;
  TString name = this->getResonanceName();
  //TODO : MAKE A BETTER FETCHER FOR THE ORDER OF THE RESONANCE TERM                                                                         
  if (name.EndsWith("0",TString::kExact)){
    magnitude = spinTerm;
  }
  else if (name.EndsWith("1",TString::kExact)){
    magnitude = (mass-omega_)*spinTerm;
  }
  else if (name.EndsWith("2",TString::kExact)){
    magnitude = (mass-omega_)*(mass-omega_)*spinTerm;
  }
  else if (name.EndsWith("3",TString::kExact)){
    magnitude = (mass-omega_)*(mass-omega_)*(mass-omega_)*spinTerm;
  }
  else{
    cerr << "ERROR in LauPolNR::resAmp : Resonance order unknown (known orders : 0, 1, 2 and 3)" << endl;
    magnitude = 0.;
  }
  LauComplex resAmplitude(magnitude, 0.0);

  return resAmplitude;
}

