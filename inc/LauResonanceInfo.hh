
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauResonanceInfo.hh
    \brief File containing declaration of LauResonanceInfo class.
*/

/*! \class LauResonanceInfo
    \brief Class for defining the properties of a resonant particle.
*/

#ifndef LAU_RESONANCE_INFO
#define LAU_RESONANCE_INFO

#include "TString.h"


class LauResonanceInfo {

	public:
		//! Constructor
		/*!
		    \param [in] name the name of the resonant particle
		    \param [in] mass the mass of the resonant particle
		    \param [in] width the width of the resonant particle
		    \param [in] spin the spin of the resonant particle
		    \param [in] charge the charge of the resonant particle
		    \param [in] range the range of the resonant particle
		*/
		LauResonanceInfo(const TString& name, Double_t mass, Double_t width, Int_t spin, Int_t charge, Double_t range = 4.0);

		//! Destructor
		virtual ~LauResonanceInfo(){}

		//! Retrieve the name of the resonant particle
		/*!
		    \return the name of the resonant particle
		*/
		TString getName() const {return name_;}

		//! Retrieve the mass of the resonant particle
		/*!
		    \return the mass of the resonant particle
		*/
		Double_t getMass() const {return mass_;}

		//! Retrieve the width of the resonant particle
		/*!
		    \return the width of the resonant particle
		*/
		Double_t getWidth() const {return width_;}

		//! Retrieve the spin of the resonant particle
		/*!
		    \return the spin of the resonant particle
		*/
		Int_t getSpin() const {return spin_;}

		//! Retrieve the charge of the resonant particle
		/*!
		    \return the charge of the resonant particle
		*/
		Int_t getCharge() const {return charge_;}

		//! Retrieve the range of the resonant particle
		/*!
		    \return the range of the resonant particle
		*/
		Double_t getRange() const {return range_;}

	protected:

	private:
		//! The name of the resonant particle
		TString name_;

		//! The mass of the resonant particle
		Double_t mass_;

		//! The width of the resonant particle
		Double_t width_;

		//! The spin of the resonant particle
		Int_t spin_;

		//! The charge of the resonant particle
		Int_t charge_;

		//! The range of the resonant particle
		Double_t range_;

		ClassDef(LauResonanceInfo, 0)   // Specify each allowed resonance

};

#endif
