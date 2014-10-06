
// Copyright University of Warwick 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauBlattWeisskopfFactor.hh
    \brief File containing declaration of LauBlattWeisskopfFactor class.
*/

/*! \class LauBlattWeisskopfFactor
    \brief Class that implements the Blatt-Weisskopf barrier factor

    This factor is used in resonance models such as the Relativistic Breit-Wigner.
*/

#ifndef LAU_BLATTWEISSKOPFFACTOR
#define LAU_BLATTWEISSKOPFFACTOR

#include "Rtypes.h"

class LauParameter;
class LauResonanceInfo;


class LauBlattWeisskopfFactor {

	public:
		//! Define the allowed types of barrier factors 
		enum BarrierType {
			BWBarrier,	/*!< Blatt-Weisskopf barrier factor (for use when momentum terms not used in angular term) */
			BWPrimeBarrier,	/*!< Blatt-Weisskopf barrier factor (for use when momentum terms are used in angular term) - the default */
			ExpBarrier	/*!< expoential barrier factor (mostly used for virtual contributions) */
		};

		//! Define resonance categories that will share common barrier factor radii
		enum BlattWeisskopfCategory {
			Default,	//*!< indicates that LauResonanceMaker should use the appropriate category for the given resonance */
			Parent,		//*!< indicates that this is the factor for the decay of the parent particle */
			Indep,		//*!< indicates that this resonance should be independent of all others */
			Light,		//*!< default category for light unflavoured states, e.g. rho(77), f0(980), etc. */
			Kstar,		//*!< default category for K* states */
			Charm,		//*!< default category for D* states */
			StrangeCharm,	//*!< default category for Ds* states */
			Charmonium,     //*!< default category for ccbar states */
			Beauty,		//*!< default category for B* states */
			StrangeBeauty,	//*!< default category for Bs* states */
			CharmBeauty,	//*!< default category for Bc* states */
			Custom1,	//*!< user-defined category */
			Custom2,	//*!< user-defined category */
			Custom3,	//*!< user-defined category */
			Custom4		//*!< user-defined category */
		};

		//! Constructor
		LauBlattWeisskopfFactor( const LauResonanceInfo& resInfo, const BarrierType barrierType, const BlattWeisskopfCategory category );

		//! Constructor
		LauBlattWeisskopfFactor( const LauResonanceInfo& resInfo, const Double_t resRadius, const BarrierType barrierType, const BlattWeisskopfCategory category );

		//! Destructor
		~LauBlattWeisskopfFactor();

		//! Method to create a new factor with cloned radius parameter
		/*!
		    \param newSpin the value of the spin to use for the created instance
		*/
		LauBlattWeisskopfFactor* createClone( const UInt_t newSpin );

		//! Retrieve the radius parameter
		const LauParameter* getRadiusParameter() const { return radius_; }

		//! Retrieve the radius parameter
		LauParameter* getRadiusParameter() { return radius_; }

		//! Retrieve the barrier type
		BarrierType getBarrierType() const { return barrierType_; }

		//! Calculate form factor value
		/*!
		    \param p the value of the momentum
		*/
		Double_t calcFormFactor( const Double_t p ) const;

	protected:
		//! Set the name of the radius parameter
		TString setRadiusName( const LauResonanceInfo& resInfo, const BlattWeisskopfCategory category );

	private:
		//! Copy constructor
		LauBlattWeisskopfFactor( const LauBlattWeisskopfFactor& other, const UInt_t newSpin );

		//! Copy assignment operator (not implemented)
		LauBlattWeisskopfFactor& operator=( const LauBlattWeisskopfFactor& other );

		//! Resonance spin
		const UInt_t spin_;

		//! Radius parameter
		LauParameter* radius_;

		//! Barrier type
		const BarrierType barrierType_;

		ClassDef(LauBlattWeisskopfFactor, 0)
};

#endif
