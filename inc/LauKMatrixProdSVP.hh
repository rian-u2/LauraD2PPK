
// Copyright University of Warwick 2008 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauKMatrixProdSVP.hh
    \brief File containing declaration of LauKMatrixProdSVP class.
*/

/*! \class LauKMatrixProdSVP
    \brief Class for defining a K-matrix production "slowly-varying part" (SVP) amplitude

    Class for defining a K-matrix production "slowly-varying part" (SVP) amplitude
*/

#ifndef LAU_KMATRIX_PROD_SVP
#define LAU_KMATRIX_PROD_SVP

#include "LauAbsResonance.hh"
#include "TString.h"

class LauKMatrixPropagator;
class LauDaughters;
class LauKinematics;

class LauKMatrixProdSVP : public LauAbsResonance {

        public:
		//! Constructor
		/*!
			\param [in] poleName name of the pole
			\param [in] channelIndex the channel number 
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] propagator a K-matrix propagator
			\param [in] daughters the daughter particles
		*/	
                LauKMatrixProdSVP(const TString& poleName, Int_t channelIndex, Int_t resPairAmpInt,
		                  LauKMatrixPropagator* propagator, const LauDaughters* daughters);

		//! Destructor
  		virtual ~LauKMatrixProdSVP();

		//! Initialise the model
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
		//! Function not meant to be called
  		virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

 	private:
		//! The K-matrix propagator
   		LauKMatrixPropagator* thePropagator_;
		//! The number of the channel
		Int_t channelIndex_;

   		ClassDef(LauKMatrixProdSVP, 0) // K-matrix production SVP term

};

#endif
