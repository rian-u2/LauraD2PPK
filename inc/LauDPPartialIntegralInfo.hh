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
		    \param [in] minm13 the minimum of the m13 range
		    \param [in] maxm13 the maximum of the m13 range
		    \param [in] minm23 the minimum of the m23 range
		    \param [in] maxm23 the maximum of the m23 range
		    \param [in] m13BinWidth the m13 bin width
		    \param [in] m23BinWidth the m23 bin width
		*/
		LauDPPartialIntegralInfo(const Double_t minm13, const Double_t maxm13, const Double_t minm23, const Double_t maxm23, const Double_t m13BinWidth, const Double_t m23BinWidth);

		//! Destructor
		virtual ~LauDPPartialIntegralInfo();

		//! Retrieve the minm13 of DP
		/*!
		    \return the the minm13 of DP
		*/
		inline Double_t getMinm13() const {return minm13_;}

		//! Retrieve the maxm13 of DP
		/*!
		    \return the the maxm13 of DP
		*/
		inline Double_t getMaxm13() const {return maxm13_;}

		//! Retrieve the minm23 of DP
		/*!
		    \return the the minm23 of DP
		*/
		inline Double_t getMinm23() const {return minm23_;}

		//! Retrieve the maxm23 of DP
		/*!
		    \return the the maxm23 of DP
		*/
		inline Double_t getMaxm23() const {return maxm23_;}

		//! Retrieve the m13BinWidth of DP
		/*!
		    \return the the m13BinWidth of DP
		*/
		inline Double_t getM13BinWidth() const {return m13BinWidth_;}

		//! Retrieve the m23BinWidth of DP
		/*!
		    \return the the m23BinWidth of DP
		*/
		inline Double_t getM23BinWidth() const {return m23BinWidth_;}


	private:
		//! Copy constructor (not implemented)
		LauDPPartialIntegralInfo( const LauDPPartialIntegralInfo& other );

		//! Copy assignment operator (not implemented)
		LauDPPartialIntegralInfo& operator=( const LauDPPartialIntegralInfo& other );

		//! The minimum of the m13 range
		Double_t minm13_;

		//! The maximum of the m13 range
		Double_t maxm13_;

		//! The minimum of the m23 range
		Double_t minm23_;

		//! The maximum of the m23 range
		Double_t maxm23_;

		//! The bin width for m13
		Double_t m13BinWidth_;

		//! The bin width for m23
		Double_t m23BinWidth_;

		ClassDef(LauDPPartialIntegralInfo, 0)
};

ostream& operator<<( ostream& stream, const LauDPPartialIntegralInfo& infoRecord );

#endif
