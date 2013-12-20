
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauEffModel.hh
    \brief File containing declaration of LauEffModel class.
*/

/*! \class LauEffModel
    \brief Class that implements the efficiency description across the signal Dalitz plot.

    Class that defines the efficiency model variation across the signal Dalitz plot.
    The method is based in a predetermined two-dimensional histogram to characterize the phase space acceptance.
    The efficiency variation is defined in terms of x = m_13^2, y = m_23^2 for the Dalitz plot (default) 
    or x = m', y = theta' for the square Dalitz plot
*/

#ifndef LAUEFFMODEL
#define LAUEFFMODEL

#include "Rtypes.h"

class TH2;

class LauDaughters;
class LauKinematics;
class LauVetoes;
class Lau2DAbsDP;


class LauEffModel {

	public:
		//! Constructor
		/*!
		    \param [in] daughters the daughters particles of the Dalitz plot model 
		    \param [in] vetoes the object describing the vetoes applied in the phase space
		*/
		LauEffModel(const LauDaughters* daughters, const LauVetoes* vetoes);

		//! Destructor
		virtual ~LauEffModel();

		//! Set the efficiency variation across the phase space using a predetermined 2D histogram.
		/*!
		    The efficiency is defined in terms of x = m_13^2, y = m_23^2 or x = m', y = theta' for the square Dalitz plot

		    \param [in] effHisto the 2-dimensional histogram that describes the efficiency variation
		    \param [in] useInterpolation boolean flag decision to switch on/off linear interpolation between bins should be used or simply the raw bin values.
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors.
		    \param [in] avEff the desired average efficiency - see Lau2DHistDP::raiseOrLowerBins, values less than zero switch off this behaviour
		    \param [in] absError the error on that efficiency - see Lau2DHistDP::raiseOrLowerBins, values less than zero switch off this behaviour
		    \param [in] useUpperHalfOnly boolean flag to determine whether, in the case of a symmetric DP, the histogram supplied only includes the upper half of the DP.
		    \param [in] squareDP boolean flag to determine whether the supplied histogram is given in square DP coordinates
		*/
		void setEffHisto(const TH2* effHisto,
				Bool_t useInterpolation = kTRUE, Bool_t fluctuateBins = kFALSE,
				Double_t avEff = -1.0, Double_t absError = -1.0,
				Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Set the efficiency variation across the phase space using a spline based on a predetermined 2D histogram.
		/*!
		    The efficiency is defined in terms of x = m_13^2, y = m_23^2 or x = m', y = theta' for the square Dalitz plot

		    \param [in] effHisto the 2-dimensional histogram that describes the efficiency variation
		    \param [in] fluctuateBins boolean flag to determine whether the bin contents should be fluctuated in accordance with their errors.
		    \param [in] avEff the desired average efficiency - see Lau2DHistDP::raiseOrLowerBins, values less than zero switch off this behaviour
		    \param [in] absError the error on that efficiency - see Lau2DHistDP::raiseOrLowerBins, values less than zero switch off this behaviour
		    \param [in] useUpperHalfOnly boolean flag to determine whether, in the case of a symmetric DP, the histogram supplied only includes the upper half of the DP.
		    \param [in] squareDP boolean flag to determine whether the supplied histogram is given in square DP coordinates
		*/
		void setEffSpline(const TH2* effHisto,
				 Bool_t fluctuateBins = kFALSE,
				 Double_t avEff = -1.0, Double_t absError = -1.0,
				 Bool_t useUpperHalfOnly = kFALSE, Bool_t squareDP = kFALSE);

		//! Determine the efficiency for a given point in the Dalitz plot.
		/*!
		    The method uses the 2D histogram set by the setEffHisto() function and the vetoes information.

		    \param [in] kinematics the object that defines the DP position
		    \return the efficiency value at the given point in the DP
		*/
		Double_t calcEfficiency( const LauKinematics* kinematics ) const;

		//! Determine whether the given DP position is outside the vetoes
		/*!
		    \param [in] kinematics the object that defines the DP position
		    \return kTRUE if the DP position is outside all veto regions, kFALSE otherwise
		*/
		Bool_t passVeto( const LauKinematics* kinematics ) const;

		//! Determine whether the efficiency histogram has had its bins fluctuated within their errors
		Bool_t fluctuateEffHisto() const {return fluctuateEffHisto_;}

	private:
		//! Copy constructor - not implemented
		LauEffModel( const LauEffModel& rhs );

		//! Get the efficiency from a two-dimensional histogram by interpolating in x and y
		/*!
		    \param [in] xVal the value to be interpolated in x 
		    \param [in] yVal the value to be interpolated in y 
		*/
		Double_t getEffHistValue(Double_t xVal, Double_t yVal) const;

		//! The daughters object
		const LauDaughters* daughters_;

		//! The vetoes object
		const LauVetoes* vetoes_;

		//! The efficiency histogram object
		Lau2DAbsDP* effHisto_;

		//! Use of the square Dalitz plot
		Bool_t squareDP_;
		//! Fluctuate histogram within the error
		Bool_t fluctuateEffHisto_;

		ClassDef(LauEffModel, 0)   // Implement the signal efficiency across the DP

};

#endif
