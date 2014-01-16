
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRealImagCoeffSet.hh
    \brief File containing declaration of LauRealImagCoeffSet class.
*/

/*! \class LauRealImagCoeffSet
    \brief Class for defining a complex coefficient using real and imaginary parts.

    Holds a set of real values that define the complex coefficient of an amplitude component.
    The amplitude has the form x + i*y.
*/

#ifndef LAU_REALIMAG_COEFF_SET
#define LAU_REALIMAG_COEFF_SET

#include <iosfwd>
#include <vector>

#include "Rtypes.h"

#include "LauAbsCoeffSet.hh"
#include "LauComplex.hh"
#include "LauParameter.hh"


class LauRealImagCoeffSet : public LauAbsCoeffSet {

	public:
		//! Constructor
		/*!
		    \param [in] compName the name of the coefficient set
		    \param [in] x the real part
		    \param [in] y the imaginary part
		    \param [in] xFixed whether x is fixed
		    \param [in] yFixed whether y is fixed
		*/
		LauRealImagCoeffSet(const TString& compName, Double_t x, Double_t y, Bool_t xFixed, Bool_t yFixed);

		//! Destructor
		virtual ~LauRealImagCoeffSet(){}

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
		LauRealImagCoeffSet(const LauRealImagCoeffSet& rhs, Double_t constFactor = 1.0);
		
		//! Copy assignment operator
		/*!
		    This creates cloned parameters, not copies.
		    \param [in] rhs the coefficient to clone
		*/
		LauRealImagCoeffSet& operator=(const LauRealImagCoeffSet& rhs);


	private:
		//! The minimum allowed value for parameters
		Double_t minPar_;
		//! The maximum allowed value for parameters
		Double_t maxPar_;

		// the actual fit parameters
		// (need to be pointers so they can be cloned)
		//! The real part
		LauParameter* x_;
		//! The imaginary part
		LauParameter* y_;

		//! The complex coefficient
		LauComplex coeff_;

		ClassDef(LauRealImagCoeffSet, 0)
};

#endif
