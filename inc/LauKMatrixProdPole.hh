
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixProdPole.hh
    \brief File containing declaration of LauKMatrixProdPole class.
*/

/*! \class LauKMatrixProdPole
    \brief Class for defining a K-matrix production pole amplitude term.

    Class for defining a K-matrix production pole amplitude term
*/

#ifndef LAU_KMATRIX_PROD_POLE
#define LAU_KMATRIX_PROD_POLE

#include "LauAbsResonance.hh"
#include "TString.h"

class LauKMatrixPropagator;
class LauDaughters;
class LauKinematics;

class LauKMatrixProdPole : public LauAbsResonance {

        public:
		//! Constructor
		/*!
			\param [in] poleName name of the pole
			\param [in] poleIndex number of pole
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] propagator a K-matrix propagator
			\param [in] daughters the daughter particles
			\param [in] useProdAdler boolean to turn on/off the production Adler zero factor
		*/	
                LauKMatrixProdPole(const TString& poleName, Int_t poleIndex, Int_t resPairAmpInt,
		                   LauKMatrixPropagator* propagator, const LauDaughters* daughters,
				   Bool_t useProdAdler = kFALSE);

		//! Destructor
  		virtual ~LauKMatrixProdPole();

		// Initialise the model
  		virtual void initialise() {return;}

		//! The amplitude calculation
		/*!
			\param [in] kinematics the kinematic variables of the current event
			\return the complex amplitude
		*/	
  		virtual LauComplex amplitude(const LauKinematics* kinematics);

		//! Get the resonance model type
                /*!
                        \return the resonance model type
                */
		virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::KMatrix;}

	protected:
		//! Function not meant to be called, amplitude is called directly in this case
  		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

 	private:
		//! Copy constructor (not implemented)
		LauKMatrixProdPole(const LauKMatrixProdPole& rhs);

		//! Copy assignment operator (not implemented)
		LauKMatrixProdPole& operator=(const LauKMatrixProdPole& rhs);

		//! The K-matrix propagator
   		LauKMatrixPropagator* thePropagator_;
		//! The number of the pole
		Int_t poleIndex_;

                //! Boolean to turn on/off the production Adler zero factor
                Bool_t useProdAdler_;

   		ClassDef(LauKMatrixProdPole, 0) // K-matrix production pole

};

#endif
