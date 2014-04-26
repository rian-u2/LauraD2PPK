/*! \file LauDPPartialIntegralInfo.hh
    \brief File containing declaration of LauDPPartialIntegralInfo class.
*/

/*! \class LauDPPartialIntegralInfo
    \brief Class for defining the properties of a resonant particle.
*/

#ifndef LAU_DPPARTIALINTEGRAL_INFO
#define LAU_DPPARTIALINTEGRAL_INFO

#include <iosfwd>
#include "TString.h"


class LauDPPartialIntegralInfo {

	public:


		//! Constructor
		/*!
		    \param [in] name the name
		    \param [in] minm13 the minm13
		    \param [in] maxm13 the maxm13
		    \param [in] minm23 the minm23
		    \param [in] maxm23 the maxm23
		    \param [in] m13BinWidth the m13BinWidth
		    \param [in] m23BinWidth the m23BinWidth
		*/
        LauDPPartialIntegralInfo(const TString& name, Double_t minm13, Double_t maxm13, Double_t minm23, Double_t maxm23, Double_t m13BinWidth, Double_t m23BinWidth);
		//! Destructor
		virtual ~LauDPPartialIntegralInfo();

		//! Retrieve the name of the resonant particle
		/*!
		    \return the name of the resonant particle
		*/
		TString getName() const {return name_;}

		//! Retrieve the minm13 of DP
		/*!
		    \return the the minm13 of DP
		*/
		Double_t getMinm13() const {return minm13_;}

		//! Retrieve the maxm13 of DP
		/*!
		    \return the the maxm13 of DP
		*/
		Double_t getMaxm13() const {return maxm13_;}

		//! Retrieve the minm23 of DP
		/*!
		    \return the the minm23 of DP
		*/
		Double_t getMinm23() const {return minm23_;}

		//! Retrieve the maxm23 of DP
		/*!
		    \return the the maxm23 of DP
		*/
		Double_t getMaxm23() const {return maxm23_;}

		//! Retrieve the m13BinWidth of DP
		/*!
		    \return the the m13BinWidth of DP
		*/
		Double_t getM13BinWidth() const {return m13BinWidth_;}

		//! Retrieve the m23BinWidth of DP
		/*!
		    \return the the m23BinWidth of DP
		*/
		Double_t getM23BinWidth() const {return m23BinWidth_;}



	protected:

	private:
		//! Copy constructor
		LauDPPartialIntegralInfo( const LauDPPartialIntegralInfo& other );

		//! Copy constructor (with new name)
		LauDPPartialIntegralInfo( const LauDPPartialIntegralInfo& other, const TString& newName);

		//! Copy assignment operator (not implemented)
		LauDPPartialIntegralInfo& operator=( const LauDPPartialIntegralInfo& other );

		//! The name of the resonant particle
		TString name_;

		Double_t minm13_;
		Double_t maxm13_;
		Double_t minm23_;
		Double_t maxm23_;
		Double_t m13BinWidth_;
		Double_t m23BinWidth_;

		ClassDef(LauDPPartialIntegralInfo, 0)   // Specify each allowed resonance

};

ostream& operator<<( ostream& stream, const LauDPPartialIntegralInfo& infoRecord );

#endif
