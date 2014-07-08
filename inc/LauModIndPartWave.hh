
// Copyright University of Warwick 2004 - 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauModIndPartWave.hh
    \brief File containing declaration of LauModIndPartWave class.
*/

/*! \class LauModIndPartWave
    \brief Class for defining a model independent partial wave component

    Class for defining a model independent partial wave component.
    This model uses splines to produce a partial wave from a set of masses and amplitudes.
    The magnitude and phase at each point can be floated in the fit and the amplitudes at the kinematic limits are fixed to zero.
*/

#ifndef LAU_MODINDPARTWAVE
#define LAU_MODINDPARTWAVE

#include "LauComplex.hh"
#include "LauAbsResonance.hh"

class TSpline3;


class LauModIndPartWave : public LauAbsResonance {

  public:
    //! Constructor
    /*!
      \param [in] resInfo the object containing information on the resonance name, mass, width, spin, charge, etc.
      \param [in] resPairAmpInt the number of the daughter not produced by the resonance
      \param [in] daughters the daughter particles
    */
    LauModIndPartWave(LauResonanceInfo* resInfo, Int_t resPairAmpInt, const LauDaughters* daughters);

    //! Destructor
    virtual ~LauModIndPartWave();

    //! Initialise the model
    virtual void initialise();

    //! Add a knot to the magnitude and phase splines
    /*!
      Knots must be added in ascending order and two knots cannot be placed at the same mass.
      \param [in] mass the mass at which the knot is placed
      \param [in] magVal the value of the magnitude at the knot
      \param [in] phaseVal the value of the phase at the knot
      \param [in] fixMag whether the magnitude parameter should be fixed at the knot
      \param [in] fixPhase whether the phase parameter should be fixed at the knot
    */
    void addKnot(Double_t mass, Double_t magVal, Double_t phaseVal, Bool_t fixMag=kTRUE, Bool_t fixPhase=kTRUE);

    //! Get the resonance model type
    /*!
      \return the resonance model type
    */
    virtual LauAbsResonance::LauResonanceModel getResonanceModel() const {return LauAbsResonance::MIPW;}

    //! Retrieve the resonance parameters, e.g. so that they can be loaded into a fit
    /*!
      \return floating parameters of the resonance
    */
    virtual const std::vector<LauParameter*>& getFloatingParameters();

  protected:
    //! Complex resonant amplitude
    /*!
      \param [in] mass appropriate invariant mass for the resonance
      \param [in] spinTerm Zemach spin term
    */
    virtual LauComplex resAmp(Double_t mass, Double_t spinTerm);

  private:
    //! The spline used to calculate the magnitude at a given mass
    TSpline3* magSpline_;
    //! The spline used to calculate the phase at a given mass
    TSpline3* phaseSpline_;

    //! The number of knots in the magnitude and phase splines
    Int_t nKnots_;

    //! The masses at which knots are defined in the magnitude and phase splines
    std::vector<Double_t> masses_;
    //! The values of the magnitude spline at the knots
    std::vector<Double_t> magnitudes_;
    //! The values of the phase spline at the knots
    std::vector<Double_t> phases_;

    //! The parameters for the values at the knots in the magnitude spline 
    std::vector<LauParameter*> magnitudePars_;
    //! The parameters for the values at the knots in the phase spline
    std::vector<LauParameter*> phasePars_;

    //! Flag to identify whether the model has been intialised yet
    Bool_t initialised_;

    ClassDef(LauModIndPartWave,0) // model independent partial wave

};

#endif
