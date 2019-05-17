
/*
Copyright 2008 University of Warwick

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*
Laura++ package authors:
John Back
Paul Harrison
Thomas Latham
*/

/*! \file LauKMatrixPropagator.hh
    \brief File containing declaration of LauKMatrixPropagator class.
*/

/*! \class LauKMatrixPropagator
    \brief Class for defining a K-matrix propagator.

    Class used to define a K-matrix propagator.
    See the following papers for info:
    hep-ph/0204328, hep-ex/0312040, [hep-ex]0804.2089 and hep-ph/9705401.
*/

#ifndef LAU_KMATRIX_PROPAGATOR
#define LAU_KMATRIX_PROPAGATOR

#include "LauComplex.hh"
#include "LauKinematics.hh"
#include "LauParameter.hh"

#include "TMatrixD.h"
#include "TString.h"

#include <map>
#include <vector>

class LauKMatrixPropagator {

        public:
		//! Constructor
		/*! 
			\param [in] name name of the propagator
			\param [in] paramFileName the parameter file name
			\param [in] resPairAmpInt the number of the daughter not produced by the resonance
			\param [in] nChannels the number of channels
			\param [in] nPoles the number of poles
			\param [in] rowIndex this specifies which row of the propagator should be used when summing over the amplitude channels
		*/
	        LauKMatrixPropagator(const TString& name, const TString& paramFileName, 
                                     Int_t resPairAmpInt, Int_t nChannels, Int_t nPoles,
				     Int_t rowIndex = 1);

		//! Destructor
  	        virtual ~LauKMatrixPropagator();

		//! Calculate the invariant mass squared s
		/*!
			\param [in] kinematics the kinematics of the current event
		*/
		void updatePropagator(const LauKinematics* kinematics);

		//! Calculate the K-matrix propagator for the given s value
		/*!
			\param [in] s the invariant mass squared
		*/
		void updatePropagator(Double_t s);

		//! Read an input file to set parameters
		/*!
			\param [in] inputFile name of the input file
		*/	
	        void setParameters(const TString& inputFile);

                //! Get the scattering K matrix
                /*!
                        \return the real, symmetric scattering K matrix
		*/
                TMatrixD getKMatrix() const {return ScattKMatrix_;}

                //! Get the real part of the propagator full matrix
                /*!
		        \return the real part of the propagator full matrix
                */
                TMatrixD getRealPropMatrix() const {return realProp_;}

                //! Get the negative imaginary part of the full propagator matrix
                /*!
                        \return the negative imaginary part of the full propagator matrix
                */
        	TMatrixD getNegImagPropMatrix() const {return negImagProp_;}

		//! Get the real part of the term of the propagator
		/*!
			\param [in] channelIndex the channel number
			\return the real part of the propagator term
		*/
		Double_t getRealPropTerm(Int_t channelIndex) const;

		//! Get the imaginary part of the term of the propagator
		/*!
			\param [in] channelIndex the channel number
			\return the imaginiary part of the propagator term
		*/	
		Double_t getImagPropTerm(Int_t channelIndex) const;

		//! Get the 1/(m_pole^2 -s) terms for the scattering and production K-matrix formulae
		/*!
			\param [in] poleIndex the number of the pole required
			\return the value of 1/(m_pole^2 -s)
		*/
		Double_t getPoleDenomTerm(Int_t poleIndex) const;

		//! Get coupling constants that were loaded from the input file
		/*!
			\param [in] poleIndex number of the required pole
			\param [in] channelIndex number of the required channel
			\return the value of the coupling constant
		*/
		Double_t getCouplingConstant(Int_t poleIndex, Int_t channelIndex) const;

		//! Get scattering constants that were loaded from the input file
		/*!
			\param [in] channel1Index number of the first channel index
			\param [in] channel2Index number of the second channel index
			\return the value of the scattering constant
		*/
		Double_t getScatteringConstant(Int_t channel1Index, Int_t channel2Index) const;

		//! Get the "slowly-varying part" term of the amplitude
		/*!
			\return the svp term
		*/
		Double_t getProdSVPTerm() const {return prodSVP_;}

		//! Get the full complex propagator term for a given channel
		/*!
			\param [in] channelIndex the number of the required channel
			\return the complex propagator term
		*/
		LauComplex getPropTerm(Int_t channelIndex) const;

		//! Get the DP axis identifier
		/*!
			/return the value to identify the DP axis in question
		*/
		Int_t getResPairAmpInt() const {return resPairAmpInt_;}

		//! Get the number of channels
		/*!
			/return the number of channels
		*/
		Int_t getNChannels() const {return nChannels_;}

		//! Get the number of poles
		/*!
			/return the number of poles
		*/
		Int_t getNPoles() const {return nPoles_;}

		//! Get the propagator name
		/*!
			/return the name of the propagator
		*/
		TString getName() const {return name_;}

                //! Get the unitary transition amplitude for the given channel
                /*!
                        \param [in] s The invariant mass squared
                        \param [in] channel The index number of the channel process
                        \return the complex amplitude T
		*/
                LauComplex getTransitionAmp(Double_t s, Int_t channel);


                //! Get the complex phase space term for the given channel and invariant mass squared
                /*!
                        \param [in] s The invariant mass squared
                        \param [in] channel The index number of the channel process
                        \return the complex phase space term rho(channel, channel)
		*/
                LauComplex getPhaseSpaceTerm(Double_t s, Int_t channel);

                //! Get the Adler zero factor, which is set when updatePropagator is called
                /*!     
		        \return the Adler zero factor
		*/
                Double_t getAdlerZero() const {return adlerZeroFactor_;}
    

	        //! Get the THat amplitude for the given s and channel number
	        /*!
		        \param [in] s The invariant mass squared
			\param [in] channel The index number of the channel process
			\return the complex THat amplitude
		*/
                LauComplex getTHat(Double_t s, Int_t channel);


        protected:
		//! Calculate the scattering K-matrix for the given value of s
		/*!
			\param [in] s the invariant mass squared
		*/
		void calcScattKMatrix(Double_t s);

		//! Calculate the real and imaginary part of the phase space density diagonal matrix
		/*!
			\param [in] s the invariant mass squared
		*/
		void calcRhoMatrix(Double_t s);

		//! Calulate the term 1/(m_pole^2 - s) for the scattering and production K-matrix formulae
		/*!
			\param [in] s the invariant mass squared
		*/	
		void calcPoleDenomVect(Double_t s);

		//! Calculate the pipi phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcPiPiRho(Double_t s) const;

		//! Calculate the KK phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcKKRho(Double_t s) const;

		//! Calculate the 4 pi phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcFourPiRho(Double_t s) const;

		//! Calculate the eta-eta phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcEtaEtaRho(Double_t s) const;

		//! Calculate the eta-eta' phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcEtaEtaPRho(Double_t s) const;

		//! Calculate the Kpi phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcKPiRho(Double_t s) const;

		//! Calculate the K-eta' phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcKEtaPRho(Double_t s) const;

		//! Calculate the Kpipipi phase space factor
		/*!
			\param [in] s the invariant mass squared
			\return the complex phase space factor
		*/	
		LauComplex calcKThreePiRho(Double_t s) const;

		//! Calculate the "slow-varying part"
		/*!
			\param [in] s the invariant mass squared
			\param [in] s0 the invariant mass squared at the Adler zero
			\return the SVP term
		*/	
		Double_t calcSVPTerm(Double_t s, Double_t s0) const;

		//! Update the scattering "slowly-varying part" 
		/*!
			\param [in] s the invariant mass squared
		*/	
		void updateScattSVPTerm(Double_t s);

		//! Update the production "slowly-varying part" 
		/*!
			\param [in] s the invariant mass squared
		*/	
		void updateProdSVPTerm(Double_t s);

		//! Calculate the multiplicative factor containing severa Adler zero constants
		/*!
			\param [in] s the invariant mass squared
		*/	
		void updateAdlerZeroFactor(Double_t s);

		//! Check the phase space factors that need to be used
		/*!
			\param [in] phaseSpaceInt phase space types 
			\return true of false
		*/
		Bool_t checkPhaseSpaceType(Int_t phaseSpaceInt) const;


                //! Get the unitary transition amplitude matrix for the given kinematics
                /*!
                        \param [in] kinematics The pointer to the constant kinematics
		*/
                void getTMatrix(const LauKinematics* kinematics);

                //! Get the unitary transition amplitude matrix for the given kinematics
                /*!
                        \param [in] s The invariant mass squared of the system
		*/
                void getTMatrix(Double_t s);

                //! Get the square root of the phase space matrix
                void getSqrtRhoMatrix();
                
        private:
		//! Copy constructor (not implemented)
		LauKMatrixPropagator(const LauKMatrixPropagator& rhs);

		//! Copy assignment operator (not implemented)
		LauKMatrixPropagator& operator=(const LauKMatrixPropagator& rhs);

		//! Create a map for the K-matrix parameters	
	        typedef std::map<int, std::vector<LauParameter> > KMatrixParamMap;


	        //! Initialise and set the dimensions for the internal matrices and parameter arrays
        	void initialiseMatrices();

        	//! Store the (phase space) channel indices from a line in the parameter file
	        /*!
	                \param [in] theLine Vector of strings corresponding to the line from the parameter file
		*/
	        void storeChannels(const std::vector<std::string>& theLine);
 
        	//! Store the pole mass and couplings from a line in the parameter file
	        /*!
	                \param [in] theLine Vector of strings corresponding to the line from the parameter file
		*/
	        void storePole(const std::vector<std::string>& theLine);

        	//! Store the scattering coefficients from a line in the parameter file
	        /*!
	                \param [in] theLine Vector of strings corresponding to the line from the parameter file
		*/
	        void storeScattering(const std::vector<std::string>& theLine);

        	//! Store miscelleanous parameters from a line in the parameter file
	        /*!
	                \param [in] keyword the name of the parameter to be set
	                \param [in] parString the string containing the value of the parameter
		*/
        	void storeParameter(const TString& keyword, const TString& parString);


              	//! String to store the propagator name
		TString name_;
		//! Name of the input parameter file
		TString paramFileName_;
		//! Number to identify the DP axis in question
		Int_t resPairAmpInt_;
		//! Row index - 1
		Int_t index_;

		//! s value of the previous pole
		Double_t previousS_;
		//! "slowly-varying part" for the scattering K-matrix
		Double_t scattSVP_;
		//! "slowly-varying part" for the production K-matrix
		Double_t prodSVP_;
		//! Real part of the propagator matrix
		TMatrixD realProp_; 
		//! Imaginary part of the propagator matrix
		TMatrixD negImagProp_;
		
		// Integers to specify the allowed channels for the phase space calculations.
		// Please keep Zero at the start and leave TotChannels at the end 
		// whenever more channels are added to this.
		//! Integers to specify the allowed channels for the phase space calculations 
		enum KMatrixChannels {Zero, PiPi, KK, FourPi, EtaEta, EtaEtaP,
				      KPi, KEtaP, KThreePi, TotChannels};

		//! Scattering K-matrix
		TMatrixD ScattKMatrix_; 
		//! Real part of the phase space density diagonal matrix
		TMatrixD ReRhoMatrix_;
		//! Imaginary part of the phase space density diagonal matrix
		TMatrixD ImRhoMatrix_;
		//! Identity matrix
		TMatrixD IMatrix_; 
		//! Null matrix
		TMatrixD zeroMatrix_;

		//! Real part of the square root of the phase space density diagonal matrix
		TMatrixD ReSqrtRhoMatrix_;
		//! Imaginary part of the square root of the phase space density diagonal matrix
		TMatrixD ImSqrtRhoMatrix_;
                //! Real part of the unitary T matrix
                TMatrixD ReTMatrix_;
                //! Imaginary part of the unitary T matrix
                TMatrixD ImTMatrix_;

		//! Number of channels
		Int_t nChannels_;
		//! Number of poles
		Int_t nPoles_;

		//! Vector of squared pole masses
	        std::vector<LauParameter> mSqPoles_;

		//! Array of coupling constants
	        LauParArray gCouplings_;
		//! Array of scattering SVP values
        	LauParArray fScattering_;

		//! Vector of phase space types
		std::vector<Int_t> phaseSpaceTypes_;
		//! Vector of squared masses 
		std::vector<Double_t> mSumSq_;
		//! Vector of mass differences
		std::vector<Double_t> mDiffSq_;
		//! Vector of 1/(m_pole^2 - s) terms for scattering and production K-matrix formulae
		std::vector<Double_t> poleDenomVect_;

		//! Constant from input file
		LauParameter mSq0_; 
		//! Constant from input file
		LauParameter s0Scatt_; 
		//! Constant from input file
		LauParameter s0Prod_; 
		//! Constant from input file
		LauParameter sA_; 
		//! Constant from input file
		LauParameter sA0_;

		//! Defined as 0.5*sA*mPi*mPi
		Double_t sAConst_;
		//! Defined as 4*mPi*mPi
		Double_t m2piSq_; 
		//! Defined as 4*mK*mK
		Double_t m2KSq_; 
		//! Defined as 4*mEta*mEta
		Double_t m2EtaSq_; 
		//! Defined as (mEta+mEta')^2
		Double_t mEtaEtaPSumSq_; 
		//! Defined as (mEta-mEta')^2
		Double_t mEtaEtaPDiffSq_;
		//! Defined as (mK+mPi)^2
		Double_t mKpiSumSq_; 
		//! Defined as (mK-mPi)^2
		Double_t mKpiDiffSq_; 
		//! Defined as (mK+mEta')^2
		Double_t mKEtaPSumSq_; 
		//! Defined as (mK-mEta')^2
		Double_t mKEtaPDiffSq_;
		//! Defined as (mK-3*mPi)^2
		Double_t mK3piDiffSq_; 
		//! Factor used to calculate the Kpipipi phase space term
		Double_t k3piFactor_; 
		//! Factor used to calculate the pipipipi phase space term
		Double_t fourPiFactor1_; 
		//! Factor used to calculate the pipipipi phase space term
		Double_t fourPiFactor2_;

		//! Multiplicative factor containing various Adler zero constants
		Double_t adlerZeroFactor_;
		//! Tracks if all params have been set
		Bool_t parametersSet_;

		//! Control the output of the functions
		Bool_t verbose_;

	        //! Control if scattering constants are channel symmetric: f_ji = f_ij
         	Bool_t scattSymmetry_;

		ClassDef(LauKMatrixPropagator,0) // K-matrix amplitude model
};

#endif
