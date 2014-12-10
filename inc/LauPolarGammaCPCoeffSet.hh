
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauPolarGammaCPCoeffSet.hh
    \brief File containing declaration of LauPolarGammaCPCoeffSet class.
*/

/*! \class LauPolarGammaCPCoeffSet
    \brief Class for defining a complex coefficient using a Cartesian nonCP part multiplied by a CP part defined by a magnitude, and strong and weak phases.

    Holds a set of real values that define the complex coefficient of an amplitude component.
    The amplitude has the form ( x + i * y ) * ( 1 + r * exp( i * delta +/- gamma ) ).
    [Phys. Rev. D79, 051301 (2009)]
*/

#ifndef LAU_POLARGAMMACP_COEFF_SET
#define LAU_POLARGAMMACP_COEFF_SET

#include <iosfwd>
#include <vector>

#include "Rtypes.h"

#include "LauAbsCoeffSet.hh"
#include "LauComplex.hh"
#include "LauParameter.hh"


class LauPolarGammaCPCoeffSet : public LauAbsCoeffSet {

	public:
		//! Constructor
		/*!
		    \param [in] compName the name of the coefficient set
		    \param [in] x the real nonCP part
		    \param [in] y the imaginary nonCP part
		    \param [in] r the magnitude of the CP term
		    \param [in] delta the CP-conserving phase
		    \param [in] gamma the CP-violating phase
		    \param [in] xFixed whether x is fixed
		    \param [in] yFixed whether y is fixed
		    \param [in] rFixed whether r is fixed
		    \param [in] deltaFixed whether delta is fixed
		    \param [in] gammaFixed whether gamma is fixed
		    \param [in] rSecondStage whether r should be floated only in the second stage of the fit
		    \param [in] deltaSecondStage whether delta should be floated only in the second stage of the fit
		    \param [in] gammaSecondStage whether gamma should be floated only in the second stage of the fit
		    \param [in] useGlobalGamma whether gamma should be shared with other resonances
		*/
		LauPolarGammaCPCoeffSet(const TString& compName, const Double_t x, const Double_t y, const Double_t r, const Double_t delta, const Double_t gamma,
				const Bool_t xFixed, const Bool_t yFixed, const Bool_t rFixed, const Bool_t deltaFixed, const Bool_t gammaFixed,
				const Bool_t rSecondStage = kFALSE, const Bool_t deltaSecondStage = kFALSE, const Bool_t gammaSecondStage = kFALSE, const Bool_t useGlobalGamma = kFALSE);

		//! Destructor
		virtual ~LauPolarGammaCPCoeffSet(){}
	
		//! Retrieve the parameters of the coefficient, e.g. so that they can be loaded into a fit
		/*!
		    \return the parameters of the coefficient
		*/
		virtual std::vector<LauParameter*> getParameters();

		//! Print the current values of the parameters
		virtual void printParValues() const;

		//! Print the column headings for a results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableHeading(std::ostream& stream) const;

		//! Print the parameters of the complex coefficient as a row in the results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableRow(std::ostream& stream) const;

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
		    This method is not supported by this class because there are more than four parameters so there is not a unique solution.
		    \param [in] coeff the complex coefficient for a particle
		    \param [in] coeffBar the complex coefficient for an antiparticle
		    \param [in] init whether or not the initial and generated values should also be adjusted
		*/
		virtual void setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar, Bool_t init );

		//! Calculate the CP asymmetry
		/*!
		    \return the CP asymmetry
		*/
		virtual LauParameter acp();

		//! Create a clone of the coefficient set
		/*!
		    \param [in] newName the clone's name
		    \param [in] cloneOption special option for the cloning operation
		    \param [in] constFactor a constant factor to multiply the clone's parameters by
		    \return a clone of the coefficient set
		*/
		virtual LauAbsCoeffSet* createClone(const TString& newName, CloneOption cloneOption = All, Double_t constFactor = 1.0);

	private:
		//! Copy constructor
		/*!
		    This creates cloned parameters, not copies.
		    \param [in] rhs the coefficient to clone
		    \param [in] cloneOption special option for the cloning operation
		    \param [in] constFactor a constant factor to multiply the clone's parameters by
		*/
		LauPolarGammaCPCoeffSet(const LauPolarGammaCPCoeffSet& rhs, CloneOption cloneOption = All, Double_t constFactor = 1.0);

		//! Copy assignment operator (not implemented)
		/*!
		    \param [in] rhs the coefficient to clone
		*/
		LauPolarGammaCPCoeffSet& operator=(const LauPolarGammaCPCoeffSet& rhs);

		//! Prepend the base name and index to the name of a parameter
		/*!
		    \param [out] par pointer to the parameter
		*/
		virtual void adjustName(LauParameter* par);

		// the actual fit parameters
		// (need to be pointers so they can be cloned)
		//! The nonCP real part
		LauParameter* x_;
		//! The nonCP imaginary part
		LauParameter* y_;
		//! The magnitude of the CP term
		LauParameter* r_;
		//! The CP-conserving phase
		LauParameter* delta_;
		//! The CP-violating phase
		LauParameter* gamma_;
		//! The CP-violating phase (shared by multiple resonances)
		static LauParameter* gammaGlobal_;

		//! Whether the global gamma is used for this resonance
		const Bool_t useGlobalGamma_;

		//! The nonCP part of the complex coefficient
		LauComplex nonCPPart_;
		//! The CP part of the complex coefficient for the particle
		LauComplex cpPart_;
		//! The CP part of the complex coefficient for the antiparticle
		LauComplex cpAntiPart_;

		//! The particle complex coefficient
		LauComplex particleCoeff_;
		//! The antiparticle complex coefficient
		LauComplex antiparticleCoeff_;

		//! The CP asymmetry
		LauParameter acp_;

		ClassDef(LauPolarGammaCPCoeffSet, 0)
};

#endif
