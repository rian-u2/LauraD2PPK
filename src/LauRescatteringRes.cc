
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRescatteringRes.cc
    \brief File containing implementation of LauRescatteringRes class.
*/

#include <iostream>

#include "TMath.h"

#include "TSystem.h"
#include "LauConstants.hh"
#include "LauRescatteringRes.hh"
#include "LauDaughters.hh"
#include "LauParameter.hh"
#include "LauResonanceInfo.hh"

ClassImp(LauRescatteringRes)


LauRescatteringRes::LauRescatteringRes(LauResonanceInfo* resInfo, const LauAbsResonance::LauResonanceModel resType,
		       const Int_t resPairAmpInt, const LauDaughters* daughters) :
	LauAbsResonance(resInfo, resPairAmpInt, daughters),
	lambdaPiPi_(0),
	lambdaKK_(0),
	kkps_(0), //use (==1) or not (==0) the kkpahse space
	Mf_(0), //Parametro Mf, do delta_pipi
	Ms_(0), //Parametro Ms, do delta_pipi
	Mprime_(0), //Parametro Mf, do delta_pipi
	Beta_(0), //Parametro Ms, do delta_pipi
	EpsA_(0), //Parametro Ms, do delta_pipi
	EpsB_(0), //Parametro Ms, do delta_pipi
	type_(0),
	model_(resType)
{
	TString parNameBase = this->getSanitisedName();
	TString lambdaPiPiName(parNameBase);
	lambdaPiPiName += "_lambdaPiPi";
	lambdaPiPi_ = resInfo->getExtraParameter( lambdaPiPiName );
	if ( lambdaPiPi_ == 0 ) {
		lambdaPiPi_ = new LauParameter( lambdaPiPiName, 1.0, 0.0, 10.0, kTRUE );
		lambdaPiPi_->secondStage(kTRUE);
		resInfo->addExtraParameter( lambdaPiPi_ );
	}
	TString lambdaKKName(parNameBase);
	lambdaKKName += "_lambdaKK";
	lambdaKK_ = resInfo->getExtraParameter( lambdaKKName );
	if ( lambdaKK_ == 0 ) {
		lambdaKK_ = new LauParameter( lambdaKKName, 2.8, 0.0, 10.0, kTRUE );
		lambdaKK_->secondStage(kTRUE);
		resInfo->addExtraParameter( lambdaKK_ );
	}
	TString kkpsName(parNameBase);
	kkpsName += "_kkps";
	kkps_ = resInfo->getExtraParameter( kkpsName );
	if ( kkps_ == 0 ) {
		kkps_ = new LauParameter( kkpsName, 0.0, 0.0, 10.0, kTRUE );
		kkps_->secondStage(kTRUE);
		resInfo->addExtraParameter( kkps_ );
	}
	TString MfName(parNameBase);
	MfName += "_Mf";
	Mf_ = resInfo->getExtraParameter( MfName );
	if ( Mf_ == 0 ) {
		Mf_ = new LauParameter( MfName, 1.32, 0.0, 10.0, kTRUE );
		Mf_->secondStage(kTRUE);
		resInfo->addExtraParameter( Mf_ );
	}
	TString MsName(parNameBase);
	MsName += "_Ms";
	Ms_ = resInfo->getExtraParameter( MsName );
	if ( Ms_ == 0 ) {
		Ms_ = new LauParameter( MsName, 0.92, 0.0, 10.0, kTRUE );
		Ms_->secondStage(kTRUE);
		resInfo->addExtraParameter( Ms_ );
	}
	TString BetaName(parNameBase);
	BetaName += "_Beta";
	Beta_ = resInfo->getExtraParameter( BetaName );
	if ( Beta_ == 0 ) {
		Beta_ = new LauParameter( BetaName, 1.00, -10.0, 10.0, kTRUE );
		Beta_->secondStage(kTRUE);
		resInfo->addExtraParameter( Beta_ );
	}
	TString MprimeName(parNameBase);
	MprimeName += "_Mprime";
	Mprime_ = resInfo->getExtraParameter( MprimeName );
	if ( Mprime_ == 0 ) {
		Mprime_ = new LauParameter( MprimeName, 2.11, 0.0, 10.0, kTRUE );
		Mprime_->secondStage(kTRUE);
		resInfo->addExtraParameter( Mprime_ );
	}
	TString EpsAName(parNameBase);
	EpsAName += "_Eps1";
	EpsA_ = resInfo->getExtraParameter( EpsAName );
	if ( EpsA_ == 0 ) {
		EpsA_ = new LauParameter( EpsAName, 1.9, 0.0, 10.0, kTRUE );
		EpsA_->secondStage(kTRUE);
		resInfo->addExtraParameter( EpsA_ );
	}
	
	TString EpsBName(parNameBase);
	EpsBName += "_Eps2";
	EpsB_ = resInfo->getExtraParameter( EpsBName );
	if ( EpsB_ == 0 ) {
		EpsB_ = new LauParameter( EpsBName, -3.7, -10.0, 10.0, kTRUE );
		EpsB_->secondStage(kTRUE);
		resInfo->addExtraParameter( EpsB_ );
	}
	
	
	
}

LauRescatteringRes::~LauRescatteringRes()
{
	delete lambdaPiPi_;
	delete lambdaKK_;
	delete Mf_;
	delete Ms_;
	delete Beta_;
	delete Mprime_;
	delete EpsA_;
	delete EpsB_;
	delete kkps_;

}

void LauRescatteringRes::initialise()
{
	const LauDaughters* daughters = this->getDaughters();
	Int_t resPairAmpInt = this->getPairInt();
	if ( daughters->gotSymmetricalDP() && resPairAmpInt != 3 ) {
		std::cerr << "WARNING in LauRescatteringRes::initialise : Rescatteringhybrid with kkpi model and KK phase space.." << std::endl;
		std::cerr << "WARNING I think that this warning is not appropiate because Laura Simetrize at LauIsobarModel level." << std::endl;
	}

	if ( model_ != LauAbsResonance::KKPiPiScatt) {
		std::cerr << "WARNING in LauRescatteringRes::initialise : Unknown model requested, defaulting to Rescatering." << std::endl;
		model_ = LauAbsResonance::KKPiPiScatt;
	}


	TString name = this->getResonanceName();
	if (name.CompareTo("RescateringHbKK")==0 ){
		type_ = 0;
		std::cerr << "RescateringHbKK parameters......" << std::endl;
		std::cerr << "=== kkps "<<this->getkkps() << std::endl;
		std::cerr << "=== LambdaKK "<<this->getLambdaKK() << std::endl;
		std::cerr << "=== mf--ms--LambdaKK "<<this->getLambdaKK() << std::endl;
	}
	else if (name.CompareTo("Rescatering_ExclHbKK")==0 ){
		type_ = 1;
	}
	else{
		std::cerr << "ERROR in LauRescatteringRes::initialise : Resonance type unknown (known types : 0, 1)" << std::endl;
		std::cerr << "                              : Defaulting to 0." << std::endl;
	}
}


LauComplex LauRescatteringRes::amplitude(const LauKinematics* kinematics)
{
	// This function returns the complex dynamical amplitude for a Reescatering distribution  o original
        // pelaez paper parameters
     //   Double_t mprime =  1.5;  // Eq 2.15a [Pelaez et Yndúrain: arXiv:hep-ph/0411334v2 Mar 2005]
	   Double_t mprime =  this->getMPrime();  // Eq 2.15a [Pelaez et Yndúrain: arXiv:hep-ph/0411334v2 Mar 2005]
	   Double_t beta =  this->getBETA();	
	   Double_t eps1 =  this->getEPSA();	
	   Double_t eps2 =  this->getEPSB();	

        Double_t c0 = 1.3;
        Double_t mk = LauConstants::mK;
        Double_t mpi= LauConstants::mPi;
        Double_t mb= LauConstants::mB;
        Double_t lambPiPi = this->getLambdaPiPi();
        Double_t lambKK   = this->getLambdaKK();
	Double_t kkps = this->getkkps();
	Double_t mf = this->getMF();
	Double_t ms   = this->getMS();
        Double_t  PI =LauConstants::pi;
	// Calculate Mandelstam variables.
	// s = m_13^2, t = m_23^2, u = m_12^2. 
	Double_t s = 0;
	Double_t t = 0;
	Double_t u = 0;
        Int_t resPairAmpInt = getPairInt();

	//if (resPairAmpInt == 1) {
	//  s = kinematics->getm23Sq();
	//  t = kinematics->getm12Sq();
	//} else if (resPairAmpInt == 2) {
	//  s = kinematics->getm13Sq();
	//  t = kinematics->getm23Sq();
	//} else if (resPairAmpInt == 3) {
	//  s = kinematics->getm12Sq();
	//  t = kinematics->getm13Sq();


	if (resPairAmpInt == 1) {
	  s = kinematics->getm13Sq();
	  t = kinematics->getm23Sq();
	  u = kinematics->getm12Sq();
	} else if (resPairAmpInt == 2) {
	  s = kinematics->getm23Sq();
	  t = kinematics->getm12Sq();
          u = kinematics->getm13Sq();
	} else if (resPairAmpInt == 3) {
	  s = kinematics->getm12Sq();
	  t = kinematics->getm13Sq();
	  u = kinematics->getm23Sq();
	} else {
		std::cerr << "ERROR in LauAbsResonance::amplitude : Nonsense setup of resPairAmp array." << std::endl;
		gSystem->Exit(EXIT_FAILURE);
	}
	
	Double_t magnitude(0.);
	Double_t phase(0.);
	
	//in KK phasespace
	Double_t mth = 0.493*2.;
	Double_t ss = s/mth;

        // check if u variable is within the KK phase space
        Double_t  m=sqrt(s);
	Double_t  E2 =(m*m )/(2*m);
        Double_t  E3 =(mb*mb- m*m -mpi*mpi)/(2*m);
        Double_t  p2= sqrt(E2*E2 - mk*mk);
        Double_t  p3 =sqrt(E3*E3 - mpi*mpi);

        Double_t  umin=1000.;
        Double_t  umax=0.;
	
	if((E2 + E3)>(p2 + p3))umin=pow((E2 + E3),2) - pow((p2 + p3),2);
        if((E2 + E3)>(p2 - p3))umax=pow((E2 + E3),2) - pow((p2 - p3),2);
        
	if ((kkps ==1. && u>umin  && u<umax && ss>1. ) || kkps ==0. ) {
	
      	   // Calculate amplitude for s variable.
           Double_t mass_s = TMath::Sqrt(s);
           Double_t k2Square_s = (s - 4.0*mk*mk)/4.0;
           Double_t k2Abs_s=0;
           if (k2Square_s > 0) k2Abs_s = TMath::Sqrt(k2Square_s);
           else k2Abs_s = TMath::Sqrt(-1.0*k2Square_s);
	
           //fase beyond mkk**2
	   Double_t meta =0.54751;
	   Double_t B = 93.3;
	   Double_t C= 48.7;
  	   Double_t D=-88.3;
	   Double_t d0=226.5;
  	   Double_t k3=  0.;
  	   Double_t etaP= 0.0;
	   Double_t etaN=0.0;
  	   if(s>4.0*meta*meta){
  	     k3=  sqrt( s/4.0 - meta*meta);
   	     etaP= D*pow(k3,2.0)/pow(meta,2.0);
             etaN= k3/sqrt(s);
  	   }	
  	   Double_t  delta2pp  = d0 + B*k2Abs_s*k2Abs_s/pow(mk,2.0) + C*pow(k2Abs_s,4.0)/pow(mk,4.0) + etaP;//para 1.4>s>4mk i
	
	
 	   Double_t delta0_s= delta2pp*PI/180.0; // convert to rad
	
	
	
	
           Double_t eta0_s = 1.0 - (eps1*k2Abs_s/mass_s + eps2*k2Square_s/s)*(mprime*mprime-s)/s;   // Eq 2.15a 

           if ((mass_s < 2.0*mk)||(mass_s > mprime)) eta0_s = 1;
           Double_t mag_s = TMath::Sqrt( 1-eta0_s*eta0_s);

           Double_t tauRe_s = mag_s*TMath::Cos(2.0*delta0_s);
           Double_t tauIm_s = mag_s*TMath::Sin(2.0*delta0_s);

           Double_t NR1_s = 1.0/(1.0+s/(lambPiPi*lambPiPi));
           Double_t NR2_s = 1.0/(1.0+s/(lambKK*lambKK));

           //LauComplex resAmplitude(-tauIm_s*NR1_s*NR2_s - tauIm_t*NR1_t*NR2_t, tauRe_s*NR1_s*NR2_s + tauRe_t*NR1_t*NR2_t );
           if ((type_ == 1)&&(t<=s))
           {
	     NR1_s=0.0; NR2_s=0.0; tauRe_s=0.0; tauIm_s=0.0; 
           }

           magnitude=-tauIm_s*NR1_s;
	   phase= tauRe_s*NR1_s;//*NR2_s
        
	}
        LauComplex resAmplitude(magnitude,phase);
	return resAmplitude;
}

LauComplex LauRescatteringRes::resAmp(Double_t mass, Double_t spinTerm)
{
	std::cerr << "ERROR in LauRescatteringRes : This method should never be called." << std::endl;
	std::cerr << "                          : Returning zero amplitude for mass = " << mass << " and spinTerm = " << spinTerm << "." << std::endl;
	return LauComplex(0.0, 0.0);
}


const std::vector<LauParameter*>& LauRescatteringRes::getFloatingParameters()
{
	this->clearFloatingParameters();

	if ( ! this->fixLambdaPiPi() ) {
		this->addFloatingParameter( lambdaPiPi_ );
	}
	if ( ! this->fixLambdaKK() ) {
		this->addFloatingParameter( lambdaKK_ );
	}
	if ( ! this->fixkkps() ) {
		this->addFloatingParameter( kkps_ );
	}
	if ( ! this->fixMF() ) {
		this->addFloatingParameter( Mf_ );
	}
	if ( ! this->fixMS() ) {
		this->addFloatingParameter( Ms_ );
	}
	if ( ! this->fixMPrime() ) {
		this->addFloatingParameter( Mprime_ );
	}
	if ( ! this->fixBETA() ) {
		this->addFloatingParameter( Beta_ );
	}
	if ( ! this->fixEPSA() ) {
		this->addFloatingParameter( EpsA_ );
	}
	if ( ! this->fixEPSB() ) {
		this->addFloatingParameter( EpsB_ );
	}
	
	return this->getParameters();
}

void LauRescatteringRes::setResonanceParameter(const TString& name, const Double_t value)
{
	// Set various parameters for the lineshape
	if (name == "lambdaPiPi") {
		this->setLambdaPiPi(value);
		std::cout << "INFO in LauRescatteringRes::setResonanceParameter : Setting parameter lambdaPiPi = " << this->getLambdaPiPi() << std::endl;
	}
	else if (name == "lambdaKK") {
		this->setLambdaKK(value);
		std::cout << "INFO in LauRescatteringRes::setResonanceParameter : Setting parameter lambdaKK = " << this->getLambdaKK() << std::endl;
	}
	else if (name == "kkps") {
		this->setkkps(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter kkps = " << this->getkkps() << std::endl;
	}
	else if (name == "Mf") {
		this->setMF(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Mf = " << this->getMF() << std::endl;
	}
	else if (name == "Ms") {
		this->setMS(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Ms = " << this->getMS() << std::endl;
	}
	else if (name == "Mprime") {
		this->setMPrime(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Mprime = " << this->getMPrime() << std::endl;
	}
	else if (name == "Beta") {
		this->setBETA(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Beta = " << this->getBETA() << std::endl;
	}
	else if (name == "EpsA") {
		this->setEPSA(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Beta = " << this->getEPSA() << std::endl;
	}
	else if (name == "EpsB") {
		this->setEPSB(value);
		std::cout << "INFO in LauPhaseRescRes::setResonanceParameter : Setting parameter Beta = " << this->getEPSB() << std::endl;
	}
	
	else {
		std::cerr << "WARNING in LauRescatteringRes::setResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

void LauRescatteringRes::floatResonanceParameter(const TString& name)
{
	if (name == "lambdaPiPi") {
		if ( lambdaPiPi_->fixed() ) {
			lambdaPiPi_->fixed( kFALSE );
			this->addFloatingParameter( lambdaPiPi_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "lambdaKK") {
		if ( lambdaKK_->fixed() ) {
			lambdaKK_->fixed( kFALSE );
			this->addFloatingParameter( lambdaKK_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "kkps") {
		if ( kkps_->fixed() ) {
			kkps_->fixed( kFALSE );
			this->addFloatingParameter( kkps_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "Mf") {
		if ( Mf_->fixed() ) {
			Mf_->fixed( kFALSE );
			this->addFloatingParameter( Mf_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "Ms") {
		if ( Ms_->fixed() ) {
			Ms_->fixed( kFALSE );
			this->addFloatingParameter( Ms_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "Mprime") {
		if ( Mprime_->fixed() ) {
			Mprime_->fixed( kFALSE );
			this->addFloatingParameter( Mprime_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "Beta") {
		if ( Beta_->fixed() ) {
			Beta_->fixed( kFALSE );
			this->addFloatingParameter( Beta_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "EpsA") {
		if ( EpsA_->fixed() ) {
			EpsA_->fixed( kFALSE );
			this->addFloatingParameter( EpsA_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	else if (name == "EpsB") {
		if ( EpsB_->fixed() ) {
			EpsB_->fixed( kFALSE );
			this->addFloatingParameter( EpsB_ );
		} else {
			std::cerr << "WARNING in LauRescatteringRes::floatResonanceParameter: Parameter already floating.  No parameter changes made." << std::endl;
		}
	}
	
	else {
		std::cerr << "WARNING in LauRescatteringRes::fixResonanceParameter: Parameter name not reconised.  No parameter changes made." << std::endl;
	}
}

LauParameter* LauRescatteringRes::getResonanceParameter(const TString& name)
{
	if (name == "lambdaPiPi") {
		return lambdaPiPi_;
	}
	else if (name == "lambdaKK") {
		return lambdaKK_;
	}
	if (name == "kkps") {
		return kkps_;
	}
	if (name == "Mf") {
		return Mf_;
	}
	else if (name == "Ms") {
		return Ms_;
	}
	if (name == "Mprime") {
		return Mprime_;
	}
	else if (name == "Beta") {
		return Beta_;
	}
	if (name == "EpsA") {
		return EpsA_;
	}
	if (name == "EpsB") {
		return EpsB_;
	}
	
	else {
		std::cerr << "WARNING in LauRescatteringRes::getResonanceParameter: Parameter name not reconised." << std::endl;
		return 0;
	}
}

void LauRescatteringRes::setLambdaPiPi(const Double_t lambda)
{
	lambdaPiPi_->value( lambda );
	lambdaPiPi_->genValue( lambda );
	lambdaPiPi_->initValue( lambda );
}

void LauRescatteringRes::setLambdaKK(const Double_t lambda)
{
	lambdaKK_->value( lambda );
	lambdaKK_->genValue( lambda );
	lambdaKK_->initValue( lambda );
}
void LauRescatteringRes::setkkps(const Double_t KKps)
{
	kkps_->value( KKps);
	kkps_->genValue( KKps);
	kkps_->initValue( KKps);
}
void LauRescatteringRes::setMF(const Double_t mff)
{
	Mf_->value( mff );
	Mf_->genValue( mff );
	Mf_->initValue( mff );
}
void LauRescatteringRes::setMS(const Double_t mss)
{
	Ms_->value( mss );
	Ms_->genValue( mss );
	Ms_->initValue( mss );
}
void LauRescatteringRes::setMPrime(const Double_t mprimee)
{
	Mprime_->value( mprimee );
	Mprime_->genValue( mprimee);
	Mprime_->initValue( mprimee );
}
void LauRescatteringRes::setBETA(const Double_t betaa)
{
	Beta_->value( betaa );
	Beta_->genValue( betaa );
	Beta_->initValue( betaa );
}
void LauRescatteringRes::setEPSA(const Double_t epsaa)
{
	EpsA_->value( epsaa );
	EpsA_->genValue( epsaa );
	EpsA_->initValue( epsaa );
}
void LauRescatteringRes::setEPSB(const Double_t epsbb)
{
	EpsB_->value( epsbb );
	EpsB_->genValue( epsbb );
	EpsB_->initValue( epsbb );
}


