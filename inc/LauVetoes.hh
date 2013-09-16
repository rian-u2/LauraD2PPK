
// Copyright University of Warwick 2004 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauVetoes.hh
    \brief File containing declaration of LauVetoes class.
*/

/*! \class LauVetoes
    \brief Class for defining vetoes within the Dalitz plot.

    Class for defining vetoes within the Dalitz plot.
    Each veto is defined by an index corresponding to one of the three invariant mass-squared variables, and maximum and minimum values for the veto's range in the specified variable.
    Each mass-squared variable is numbered according to the index of the daughter not involved in the vetoed mass-squared variable. For example a veto in m12 squared would receive the index 3.
*/

#ifndef LAU_VETOES
#define LAU_VETOES

#include <vector>

#include "Rtypes.h"

class LauKinematics;


class LauVetoes {

	public:
		//! Constructor
		LauVetoes();

		//! Destructor
		virtual ~LauVetoes();

		//! Copy constructor
		/*!
		    \param [in] other the object to be copied
		*/
		LauVetoes(const LauVetoes& other);

		//! Copy assignment operator
		/*!
		    \param [in] other the object to be copied
		    \return the assigned vetoes object
		*/
		LauVetoes& operator=(const LauVetoes& other);

		//! Add a veto to the Dalitz plot
		/*!
		    \param [in] resPairAmpInt the index of the mass-squared variable to be vetoed
		    \param [in] minMass the minimum mass of the veto
		    \param [in] maxMass the maximum mass of the veto
		*/
		void addMassVeto(Int_t resPairAmpInt, Double_t minMass, Double_t maxMass);

		//! Add a veto to the Dalitz plot
		/*!
		    \param [in] resPairAmpInt the index of the mass-squared variable to be vetoed
		    \param [in] minMassSq the minimum mass-squared of the veto
		    \param [in] maxMassSq the maximum mass-squared of the veto
		*/
		void addMassSqVeto(Int_t resPairAmpInt, Double_t minMassSq, Double_t maxMassSq);

		//! Check whether the specified Dalitz plot point passes the vetoes
		/*!
		    \param [in] m12Sq the mass-squared of the first and second daughters
		    \param [in] m23Sq the mass-squared of the second and third daughters
		    \param [in] m13Sq the mass-squared of the first and third daughters
		    \return true if the specified Dalitz plot point is outside all veto regions, false otherwise
		*/
		Bool_t passVeto(Double_t& m12Sq, Double_t& m23Sq, Double_t& m13Sq) const;

		//! Check whether the specified Dalitz plot point passes the vetoes
		/*!
		    \param [in] kinematics a point in the Dalitz plot
		    \return true if the specified Dalitz plot point is outside all veto regions, false otherwise
		*/
		Bool_t passVeto(const LauKinematics* kinematics) const;

		//! Retrieve the number of vetoes
		/*!
		    \return the number of vetoes
		*/
		Int_t getNVetoes() const {return nVetoes_;}

		//! Retrieve the index of the vetoed mass-squared variable for each veto
		/*!
		    \return the index of the vetoed mass-squared variable for each veto
		*/
		const std::vector<Int_t>& getVetoPairs() const {return vetoPair_;}

		//! Retrieve the minimum mass-squared for each veto
		/*!
		    \return the minimum mass-squared for each veto
		*/
		const std::vector<Double_t>& getVetoMinMass() const {return vetoMinMass_;}

		//! Retrieve the maximum mass-squared for each veto
		/*!
		    \return the maximum mass-squared for each veto
		*/
		const std::vector<Double_t>& getVetoMaxMass() const {return vetoMaxMass_;}

	private:
		//! The number of vetoes
		Int_t nVetoes_;

		//! The index of the vetoed mass-squared variable for each veto
		std::vector<Int_t> vetoPair_;

		//! The minimum mass-squared for each veto
		std::vector<Double_t> vetoMinMass_;

		//! The maximum mass-squared for each veto
		std::vector<Double_t> vetoMaxMass_;

		ClassDef(LauVetoes,0) // Vetoes in the Dalitz plot
};

#endif
