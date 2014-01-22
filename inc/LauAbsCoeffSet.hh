
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauAbsCoeffSet.hh
    \brief File containing declaration of LauAbsCoeffSet class.
*/

/*! \class LauAbsCoeffSet
    \brief Class for defining the abstract interface for complex coefficient classes.

    Class for defining the abstract interface for complex coefficient classes.
    Some common code is implemented but most methods are not.
*/

#ifndef LAU_ABS_COEFF_SET
#define LAU_ABS_COEFF_SET

#include <iosfwd>
#include <vector>

#include "TString.h"

class LauComplex;
class LauParameter;


class LauAbsCoeffSet {

	public:
		//! Destructor
		virtual ~LauAbsCoeffSet(){}

		//! Retrieve the parameters of the coefficient so that they can be loaded into a fit
		/*!
		    \return the parameters of the coefficient
		*/
		virtual std::vector<LauParameter*> getParameters() = 0;

		//! Print the column headings for a results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableHeading(std::ostream& stream) = 0;

		//! Print the parameters of the complex coefficient as a row in the results table
		/*!
                    \param [out] stream the stream to print to
		*/
		virtual void printTableRow(std::ostream& stream) = 0;

		//! Randomise the starting values of the parameters for a fit
		virtual void randomiseInitValues() = 0;

		//! Make sure values are in "standard" ranges, e.g. phases should be between -pi and pi
		virtual void finaliseValues() = 0;

		//! Retrieve the complex coefficient for a particle
		/*!
		    \return the complex coefficient for a particle
		*/
		virtual const LauComplex& particleCoeff() = 0;

		//! Retrieve the complex coefficient for an antiparticle
		/*!
		    \return the complex coefficient for an antiparticle
		*/
		virtual const LauComplex& antiparticleCoeff() = 0;

		//! Set the parameters based on the complex coefficients for particles and antiparticles
		/*!
		    \param [in] coeff the complex coefficient for a particle
		    \param [in] coeffBar the complex coefficient for an antiparticle
		*/
		virtual void setCoeffValues( const LauComplex& coeff, const LauComplex& coeffBar ) = 0;

		//! Calculate the CP asymmetry
		/*!
		    \return the CP asymmetry
		*/
		virtual LauParameter acp() = 0;

		//! Create a clone of the coefficient set
		/*!
		    \param [in] newName the clone's name
		    \param [in] constFactor a constant factor to multiply the clone's parameters by
		    \return a clone of the coefficient set
		*/
		virtual LauAbsCoeffSet* createClone(const TString& newName, Double_t constFactor = 1.0) = 0;

		//! Retrieve the name of the coefficient set
		/*!
		    The name should correspond to the name of the resonance in the model.
		    \return the name of the coefficient set
		*/
		virtual TString name() const {return name_;}

		//! Set the name of the coefficient set
		/*!
		    The name should correspond to the name of the resonance in the model.
		    \param [in] theName the name to set
		*/
		virtual void name(const TString& theName) {name_ = theName;}

		//! Retrieve the base name of the coefficient set
		/*!
		    The base name is generally of the form "Ai", where i is an integer.
		    This is used in the fit results ntuple.
		    \return the base name of the coefficient set
		*/
		virtual TString baseName() const {return basename_;}

		//! Set the base name of the coefficient set
		/*!
		    The base name is generally of the form "Ai", where i is an integer.
		    This is used in the fit results ntuple.
		    \param [in] theBasename the base name to set
		*/
		virtual void baseName(const TString& theBasename) {basename_ = theBasename;}

		//! Retrieve the index number of the coefficient set
		/*!
		    \return the index number of the coefficient set
		*/
		virtual UInt_t index() const {return index_;}

		//! Set the index number of the coefficient set
		/*!
		    \param [in] newIndex the new index
		*/
		virtual void index(UInt_t newIndex);

	protected:
		//! Constructor
		/*! 
		    \param [in] theName the name of the coefficient set
		*/
		LauAbsCoeffSet(const TString& theName);

		//! Prepend the base name and index to the name of a parameter
		/*!
		    \param [out] par the parameter
		*/
		virtual void adjustName(LauParameter& par);

		//! Prepend the base name and index to the name of a parameter
		/*!
		    \param [out] par pointer to the parameter
		*/
		virtual void adjustName(LauParameter* par);

	private:
		//! The name of the coefficient set
		TString name_;

		//! The base name of the coefficient set
		TString basename_;

		//! The index number of the coefficient set
		UInt_t index_;

		ClassDef(LauAbsCoeffSet, 0)

};

#endif
