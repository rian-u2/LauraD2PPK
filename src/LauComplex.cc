
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauComplex.cc
    \brief File containing implementation of LauComplex class.
*/

/*****************************************************************************
 * Class based on RooFit/RooComplex.                                         *
 * Original copyright given below.                                           *
 *****************************************************************************
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

#include <iostream>

#include "LauComplex.hh"

ClassImp(LauComplex)


void LauComplex::print() const
{
	std::cout << (*this) << std::endl;
}

std::ostream& operator<<(std::ostream& os, const LauComplex& z)
{
	return os<<"("<<z.re()<<","<<z.im()<<")";
}

std::istream& operator>>(std::istream& ios, LauComplex& z)
{
	Double_t a(0.0), b(0.0);
	char temp;
	ios >> temp >> a >> temp >> b >> temp;
	z.setRealImagPart( a, b );
	return ios;
}

