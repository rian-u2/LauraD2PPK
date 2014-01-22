
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauMagPhaseCoeffSet.hh
    \brief File containing declaration of LauMagPhaseCoeffSet class.
*/

/*! \class LauMagPhaseCoeffSet
    \brief Class for defining a complex coefficient using a magnitude and a phase.

    Holds a set of real values that define the complex coefficient of an amplitude component.
    The amplitude has the form mag*exp(i*phase).
*/

#ifndef LAU_MAGPHASE_COEFF_SET
#define LAU_MAGPHASE_COEFF_SET

#include <iosfwd>
#include <vector>

#include "Rtypes.h"

#include "LauAbsCoeffSet.hh"
#include "LauComplex.hh"
#include "LauParameter.hh"


class LauMagPhaseCoeffSet : public LauAbsCoeffSet {

	public:
		//! Constructor
		/*!
		    \param [in] compName the name of the coefficient set
		    \param [in] magnitude the magnitude
		    \param [in] phase the phase
		    \param [in] magFixed whether mag is fixed
		    \param [in] phaseFixed whether phase is fixed
		*/
		LauMagPhaseCoeffSet(const TString& compName, Double_t magnitude, Double_t phase, Bool_t magFixed, Bool_t phaseFixed);

		//! Destructor
		virtual ~LauMagPhaseCoeffSet(){}

		//! Retrieve the parameters of the coefficient, e.g. so that they can be loaded into a fit
		/*!
		    \return the parameters of the coefficient
		*/
		virtual std::vector<LauParameter*> getParameters();

		//! Print the column headings for a results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableHeading(std::ostream& stream);

		//! Print the parameters of the complex coefficient as a row in the results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableRow(std::ostream& stream);

		//! Randomise the starting values of the parameters for a fit
		virtual void randomiseInitValues();

		//! Make sure values are in "standard" ranges, e.g. phases should be between -pi and pi
		virtual void finaliseValues();

		//! Retrieve the complex coefficient for a particle
		/*!
		    \return the complex coefficient for a particle
		*/
		virtual const LauComplex& particleCoeff();

		//! Retrieve the complex coefficient for an antiparticle
		/*!
		    \return the complex coefficient for an antiparticle
		*/
		virtual const LauComplex& antiparticleCoeff();

		//! Set the parameters based on the complex coefficients for particles and antiparticles
		/*!
		    This class does not support CP violation so this method takes the average of the two inputs.
		    \param [in] coeff the complex coefficient for a particle
		    \param [in] coeffBar the complex coefficient for an antiparticle
		*/
		virtual void setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar );

		//! Calculate the CP asymmetry
		/*!
		    \return the CP asymmetry (zero by design)
		*/
		virtual LauParameter acp();

		//! Create a clone of the coefficient set
		/*!
		    \param [in] newName the clone's name
		    \param [in] constFactor a constant factor to multiply the clone's parameters by
		    \return a clone of the coefficient set
		*/
		virtual LauAbsCoeffSet* createClone(const TString& newName, Double_t constFactor = 1.0);

	protected:
		//! Copy constructor
		/*!
		    This creates cloned parameters, not copies.
		    \param [in] rhs the coefficient to clone
		    \param [in] constFactor a constant factor to multiply the clone's parameters by
		*/
		LauMagPhaseCoeffSet(const LauMagPhaseCoeffSet& rhs, Double_t constFactor = 1.0);
		
		//! Copy assignment operator
		/*!
		    This creates cloned parameters, not copies.
		    \param [in] rhs the coefficient to clone
		*/
		LauMagPhaseCoeffSet& operator=(const LauMagPhaseCoeffSet& rhs);


	private:
		//! The minimum allowed value for magnitudes
		Double_t minMag_;
		//! The maximum allowed value for magnitudes
		Double_t maxMag_;
		//! The minimum allowed value for phases
		Double_t minPhase_;
		//! The maximum allowed value for phases
		Double_t maxPhase_;

		// the actual fit parameters
		// (need to be pointers so they can be cloned)
		//! The magnitude
		LauParameter* magnitude_;
		//! The phase
		LauParameter* phase_;

		//! The complex coefficient
		LauComplex coeff_;

		ClassDef(LauMagPhaseCoeffSet, 0)
};

#endif
