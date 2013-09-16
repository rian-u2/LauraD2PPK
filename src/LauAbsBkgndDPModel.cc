
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsBkgndDPModel.cc
    \brief File containing implementation of LauAbsBkgndDPModel class.
*/

#include "LauAbsBkgndDPModel.hh"
#include "LauDaughters.hh"

ClassImp(LauAbsBkgndDPModel)


LauAbsBkgndDPModel::LauAbsBkgndDPModel(LauDaughters* daughters, LauVetoes* vetoes) :
	daughters_(daughters),
	kinematics_(daughters ? daughters->getKinematics() : 0),
	vetoes_(vetoes)
{
}

