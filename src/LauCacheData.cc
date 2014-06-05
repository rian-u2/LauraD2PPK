
// Copyright University of Warwick 2005 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauCacheData.cc
    \brief File containing implementation of LauCacheData class.
*/

#include "LauCacheData.hh"

ClassImp(LauCacheData)  


LauCacheData::LauCacheData() :
	m13Sq_(0.0),
	m23Sq_(0.0),
	mPrime_(0.0),
	thPrime_(0.0),
	eff_(0.0),
	scfFraction_(0.0),
	jacobian_(0.0)
{
}

LauCacheData::~LauCacheData()
{
}

LauCacheData::LauCacheData(const LauCacheData& rhs)
{
	this->storem13Sq(rhs.retrievem13Sq());
	this->storem23Sq(rhs.retrievem23Sq());
	this->storemPrime(rhs.retrievemPrime());
	this->storethPrime(rhs.retrievethPrime());
	this->storeEff(rhs.retrieveEff());
	this->storeScfFraction(rhs.retrieveScfFraction());
	this->storeJacobian(rhs.retrieveJacobian());
	this->storeRealAmp(rhs.retrieveRealAmp());
	this->storeImagAmp(rhs.retrieveImagAmp());
}

LauCacheData& LauCacheData::operator=(const LauCacheData& rhs)
{
	if (&rhs != this) {
		this->storem13Sq(rhs.retrievem13Sq());
		this->storem23Sq(rhs.retrievem23Sq());
		this->storemPrime(rhs.retrievemPrime());
		this->storethPrime(rhs.retrievethPrime());
		this->storeEff(rhs.retrieveEff());
		this->storeScfFraction(rhs.retrieveScfFraction());
		this->storeJacobian(rhs.retrieveJacobian());
		this->storeRealAmp(rhs.retrieveRealAmp());
		this->storeImagAmp(rhs.retrieveImagAmp());
	}
	return *this;
}

