
// Copyright University of Warwick 2004 - 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauRhoOmegaMix.hh
    \brief File containing declaration of LauRhoOmegaMix class.
*/

/*! \class LauRhoOmegaMix
    \brief Class for defining the rho-omega resonance mixing model

    Formulae from Paul Rensing thesis, SLAC Report 421 and Bill Dunwoodie's note
    http://www.slac.stanford.edu/~wmd/omega-rho_mixing/omega-rho_mixing.note
*/

#ifndef LAU_RHO_OMEGA_MIX
#define LAU_RHO_OMEGA_MIX

#include "TString.h"

#include "LauAbsResonance.hh"
#include "LauComplex.hh"


class LauRhoOmegaMix : public LauAbsResonance {

public:
    //! Constructor
    /*!
      \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
      \param [in] resPairAmpInt the number of the daughter not produced by the resonance
      \param [in] daughters the daughter particles
    */	
    LauRhoOmegaMix(LauResonanceInfo* resInfo, const Int_t resPairAmpInt, const LauDaughters* daughters);

    //! Destructor
    virtual ~LauRhoOmegaMix();

    //! Initialise the model
    virtual void initialise();

    //! Get the resonance model type
    /*!
      \return the resonance model type
    */
    virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::RhoOmegaMix;}

    //! Set value of the various parameters
    /*!
      \param [in] name the name of the parameter to be changed
      \param [in] value the new parameter value
    */
    virtual void setResonanceParameter(const TString& name, const Double_t value);

    //! Allow the various parameters to float in the fit
    /*!
      \param [in] name the name of the parameter to be floated
    */
    virtual void floatResonanceParameter(const TString& name);
    
    //! Access the given resonance parameter
    /*!
      \param [in] name the name of the parameter
      \return the corresponding parameter
    */
    virtual LauParameter* getResonanceParameter(const TString& name);
    
    //! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
    /*!
      \return floating parameters of the resonance
    */
    virtual const std::vector<LauParameter*>& getFloatingParameters();
    
protected:

    //! Set the omega pole mass parameter
    /*!
      \param [in] mOmega new value for the omega mass parameter
    */
    void setmOmegaValue(const Double_t mOmega);    
    
    //! Get the omega pole mass parameter value
    /*!
      \return value of the omega pole mass parameter
    */
    Double_t getmOmegaValue() const { return (mOmega_!=0) ? mOmega_->unblindValue() : 0.0; }
    
    //! Fix the omega pole mass parameter value
    /*!
      \return kTRUE if the omega pole mass parameter is fixed, kFALSE otherwise
    */
    Bool_t fixmOmegaValue() const { return (mOmega_!=0) ? mOmega_->fixed() : 0.0; }


    //! Set the omega pole width parameter
    /*!
      \param [in] wOmega new value for the omega width parameter
    */
    void setwOmegaValue(const Double_t wOmega);
        
    //! Get the omega pole width parameter value
    /*!
      \return value of the omega pole width parameter
    */
    Double_t getwOmegaValue() const { return (wOmega_!=0) ? wOmega_->unblindValue() : 0.0; }
    
    //! Fix the omega pole width parameter value
    /*!
      \return kTRUE if the omega pole width parameter is fixed, kFALSE otherwise
    */
    Bool_t fixwOmegaValue() const { return (wOmega_!=0) ? wOmega_->fixed() : 0.0; }

    
    //! Set the omega B magnitude mixing parameter
    /*!
      \param [in] magB new value for the omega B magnitude mixing parameter
    */
    void setmagBValue(const Double_t magB);

    //! Get the omega B magnitude mixing parameter
    /*!
      \return value of the omega B magnitude mixing parameter
    */
    Double_t getmagBValue() const { return (magB_!=0) ? magB_->unblindValue() : 0.0; }
    
    //! Fix the omega B magnitude mixing parameter value
    /*!
      \return kTRUE if the omega B magnitude mixing parameter is fixed, kFALSE otherwise
    */
    Bool_t fixmagBValue() const { return (magB_!=0) ? magB_->fixed() : 0.0; }


    //! Set the omega B phase mixing parameter
    /*!
      \param [in] phiB new value for the omega B phase mixing parameter
    */
    void setphiBValue(const Double_t phiB);

    //! Get the omega B phase mixing parameter
    /*!
      \return value of the omega B phase mixing parameter
    */
    Double_t getphiBValue() const { return (phiB_!=0) ? phiB_->unblindValue() : 0.0; }
    
    //! Fix the omega B phase mixing parameter value
    /*!
      \return kTRUE if the omega B phase mixing parameter is fixed, kFALSE otherwise
    */
    Bool_t fixphiBValue() const { return (phiB_!=0) ? phiB_->fixed() : 0.0; }


    //! Set the omega mixing parameter delta
    /*!
      \param [in] delta new value for the omega mixing parameter delta
    */
    void setdeltaValue(const Double_t delta);

    //! Get the omega mixing parameter delta
    /*!
      \return value of the omega mixing parameter delta
    */
    Double_t getdeltaValue() const { return (delta_!=0) ? delta_->unblindValue() : 0.0; }
    
    //! Fix the omega mixing parameter delta value
    /*!
      \return kTRUE if the omega mixing parameter delta is fixed, kFALSE otherwise
    */
    Bool_t fixdeltaValue() const { return (delta_!=0) ? delta_->fixed() : 0.0; }
  
 
    //! Complex resonant ampltiude
    /*!
      \param [in] mass appropriate invariant mass for the resonance
      \param [in] spinTerm Zemach spin term
    */	
    virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);
    
    //! Check that both daughters are the same type of particle
    void checkDaughterTypes() const;

private:

    //! Copy constructor (not implemented)
    LauRhoOmegaMix(const LauRhoOmegaMix& rhs);
    
    //! Copy assignment operator (not implemented)
    LauRhoOmegaMix& operator=(const LauRhoOmegaMix& rhs);
    
    //! Momentum of the daughters in the resonance rest frame (at pole mass)
    Double_t q0_;
    //! Momentum of the bachelor in the resonance rest frame (at pole mass)
    Double_t p0_;
    //! Momentum of the bachelor in the parent rest frame (at pole mass)
    Double_t pstar0_;
    //! The resonance mass
    Double_t resMass_;
    //! Square of the resonance mass
    Double_t resMassSq_;
    //! The resonance width
    Double_t resWidth_;
    //! The resonance barrier radius
    Double_t resRadius_;
    //! The parent barrier radius
    Double_t parRadius_;
    //! Sum of the two daughter masses
    Double_t mDaugSum_;
    //! Square of the sum of the two daughter masses
    Double_t mDaugSumSq_;
    //! Difference of the two daughter masses
    Double_t mDaugDiff_;
    //! Square of the difference of the two daughter masses
    Double_t mDaugDiffSq_;
    //! Square of the parent mass
    Double_t mParentSq_;
    //! Square of the bachelor mass
    Double_t mBachSq_;
    //! Value of the form factor for resonance decay (at pole mass)
    Double_t FR0_;
    //! Value of the form factor for parent decay (at pole mass)
    Double_t FP0_;

    //! Pole mass of the omega contribution
    LauParameter* mOmega_;

    //! Pole width of the omega contribution
    LauParameter* wOmega_;

    //! B magnitude parameter of the omega mixing contribution
    LauParameter* magB_;

    //! B phase parameter of the omega mixing contribution
    LauParameter* phiB_;

    //! delta parameter of the omega mixing contribution
    LauParameter* delta_;

    ClassDef(LauRhoOmegaMix,0) // Rho-omega mixing model

};

#endif
