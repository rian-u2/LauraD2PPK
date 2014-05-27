
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsBkgndDPModel.hh
    \brief File containing declaration of LauAbsBkgndDPModel class.
*/

/*! \class LauAbsBkgndDPModel
    \brief The abstract interface for a background Dalitz plot model

    Class which defines the abstract interface for a background Dalitz plot model
*/

#ifndef LAU_ABS_BKGND_DP_MODEL
#define LAU_ABS_BKGND_DP_MODEL

#include "Rtypes.h"

class LauDaughters;
class LauKinematics;
class LauFitDataTree;
class LauVetoes;

class LauAbsBkgndDPModel {

	public:
		//! Destructor
		virtual ~LauAbsBkgndDPModel() {}

		//! Initialise the model
		virtual void initialise() = 0;

		//! Generate a toy MC event from the model
		/*!
		    \return success/failure flag
		*/
		virtual Bool_t generate() = 0;

		//! Get likelihood for a given event
		/*!
		    \param [in] iEvt the event number
		    \return the likelihood value
		*/
		virtual Double_t getLikelihood(UInt_t iEvt) = 0;

		//! Get unnormalised likelihood for a given event
		/*!
		    \param [in] iEvt the event number
		    \return the unnormalised likelihood value
		*/
		virtual Double_t getUnNormValue(UInt_t iEvt) = 0;

		//! Get PDF normalisation constant
		/*!
		    \return the PDF normalisation constant
		*/
		virtual Double_t getPdfNorm() const = 0;

		//! Cache the input data and (if appropriate) the per-event likelihood values
		/*!
		    \param [in] fitDataTree the input data
		*/
		virtual void fillDataTree(const LauFitDataTree& fitDataTree) = 0;

		//! Get the daughter particles
		/*!
		    \return the daughters
		*/
		const LauDaughters* getDaughters() const {return daughters_;}

		//! Get the daughter particles
		/*!
		    \return the daughters
		*/
		LauDaughters* getDaughters() {return daughters_;}

		//! Get the Dalitz plot kinematics
		/*!
		    \return the kinematics
		*/
		const LauKinematics* getKinematics() const {return kinematics_;}

		//! Get the Dalitz plot kinematics
		/*!
		    \return the kinematics
		*/
		LauKinematics* getKinematics() {return kinematics_;}

		//! Get vetoes in the Dalitz plot
		/*!
		    \return the vetoes
		*/
		const LauVetoes* getVetoes() const {return vetoes_;}

		//! Get vetoes in the Dalitz plot
		/*!
		    \return the vetoes
		*/
		LauVetoes* getVetoes() {return vetoes_;}

	protected:
		//! Constructor
		/*!
		   \param [in] daughters the daughter particles
		   \param [in] vetoes the vetoes within the Dalitz plot
		*/
		LauAbsBkgndDPModel(LauDaughters* daughters, LauVetoes* vetoes);

		//! Set data event number
		/*!
		    \param [in] iEvt the event number
		*/
		virtual void setDataEventNo(UInt_t iEvt) = 0;

	private:
		//! Copy constructor (not implemented)
		LauAbsBkgndDPModel(const LauAbsBkgndDPModel& rhs);

		//! Copy assignment operator (not implemented)
		LauAbsBkgndDPModel& operator=(const LauAbsBkgndDPModel& rhs);

		//! The daughter particles
		LauDaughters* daughters_;

		//! Dalitz plot kinematics
		LauKinematics* kinematics_;

		//! Vetoes within the Dalitz plot
		LauVetoes* vetoes_;

		ClassDef(LauAbsBkgndDPModel,0) // Abstract DP background model
};

#endif
