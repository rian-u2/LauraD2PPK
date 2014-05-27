
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsEffModel.hh
    \brief File containing declaration of LauAbsEffModel class.
*/

/*! \class LauAbsEffModel
    \brief Pure abstract base class for defining the efficiency description across the signal Dalitz plot.

    Pure abstract base class for defining the efficiency description across the signal Dalitz plot.
    The efficiency variation is defined in terms of x = m_13^2, y = m_23^2 for the Dalitz plot (default) 
    or x = m', y = theta' for the square Dalitz plot
*/

#ifndef LAUABSEFFMODEL
#define LAUABSEFFMODEL

#include "Rtypes.h"

class LauKinematics;


class LauAbsEffModel {

	public:
		//! Constructor
		LauAbsEffModel() {}

		//! Destructor
		virtual ~LauAbsEffModel() {}

		//! Determine the efficiency for a given point in the Dalitz plot.
		/*!
		    \param [in] kinematics the object that defines the DP position
		    \return the efficiency value at the given point in the DP
		*/
		virtual Double_t calcEfficiency( const LauKinematics* kinematics ) const=0;

		//! Determine whether the given DP position is outside the vetoes
		/*!
		    \param [in] kinematics the object that defines the DP position
		    \return kTRUE if the DP position is outside all veto regions, kFALSE otherwise
		*/
		virtual Bool_t passVeto( const LauKinematics* kinematics ) const=0;

		//! Determine whether the efficiency histogram has had its bins fluctuated within their errors
		virtual Bool_t fluctuateEffHisto() const=0;

		//! Return the daughters object
		/*
		    \return the LauDaughters object associated with the DP
		*/
		virtual const LauDaughters* getDaughters() const=0;

		//! Determine whether the efficiency histogram is in the square DP
		/*
		    \return kTRUE if the square DP is being used, kFALSE otherwise
		*/
		virtual Bool_t usingSquareDP() const=0;

	private:
		//! Copy constructor - not implemented
		LauAbsEffModel( const LauAbsEffModel& rhs );

		//! Copy assignment operator - not implemented
		LauAbsEffModel& operator=( const LauAbsEffModel& rhs );

		ClassDef(LauAbsEffModel, 0)   // pABC for the signal efficiency across the DP

};

#endif
