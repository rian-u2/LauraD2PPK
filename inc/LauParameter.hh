
// Copyright University of Warwick 2006 - 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file LauParameter.hh
    \brief File containing declaration of LauParameter class.
*/

/*! \class LauParameter
    \brief Class for defining the fit parameter objects.

    Holds all relevant information for the parameters for both generation and fitting step:
    current, initial and generated value, maximum and minimum range, error, asymmetric error, fix and float and etc.
*/

#ifndef LAU_PARAMETER
#define LAU_PARAMETER

#include <map>
#include <vector>

#include "TObject.h"
#include "TString.h"


class LauParameter : public TObject {

	public:
		//! Default constructor
		LauParameter();

		//! Constructor for named parameter
		/*!
		    \param [in] parName the parameter name 
		*/
		LauParameter(const TString& parName);

		//! Constructor for parameter value
		/*!
		    \param [in] parValue the parameter value
		*/
		LauParameter(Double_t parValue);

		//! Constructor double limit parameter
		/*!
		    \param [in] parValue the parameter value
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		*/
		LauParameter(Double_t parValue, Double_t min, Double_t max);

		//! Constructor double limit fixed parameter
		/*!
		    \param [in] parValue the parameter value
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		    \param [in] parFixed boolean flag to fix or float parameter
		*/
		LauParameter(Double_t parValue, Double_t min, Double_t max, Bool_t parFixed);

		//! Constructor for double error and limit parameter
		/*!
		    \param [in] parValue the parameter value
		    \param [in] parError the parameter error
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		*/
		LauParameter(Double_t parValue, Double_t parError, Double_t min, Double_t max);

		//! Constructor for parameter value and name
		/*!
		    \param [in] parName the parameter name
		    \param [in] parValue the parameter value
		*/
		LauParameter(const TString& parName, Double_t parValue);

		//! Constructor double limit parameter and name
		/*!
		    \param [in] parName the parameter name
		    \param [in] parValue the parameter value
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		*/
		LauParameter(const TString& parName, Double_t parValue, Double_t min, Double_t max);

		//! Constructor double limit fixed parameter and name
		/*!
		    \param [in] parName the parameter name
		    \param [in] parValue the parameter value
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		    \param [in] parFixed boolean flag to fix (kTRUE) or float (kFALSE) the parameter
		*/
		LauParameter(const TString& parName, Double_t parValue, Double_t min, Double_t max, Bool_t parFixed);

		//! Constructor double error and limit parameter and name
		/*!
		    \param [in] parName the parameter name
		    \param [in] parValue the parameter value
		    \param [in] parError the parameter error
		    \param [in] min the minimum value of the parameter
		    \param [in] max the maximum value of the parameter
		*/
		LauParameter(const TString& parName, Double_t parValue, Double_t parError, Double_t min, Double_t max);

		// Destructor
		virtual ~LauParameter(){}

		//! Copy constructor
		/*!
		    \param [in] rhs the parameter to be copied
		*/
		LauParameter(const LauParameter& rhs);

		//! Copy assignment operator
		/*!
		    \param [in] rhs the parameter to be copied
		*/
		LauParameter& operator=(const LauParameter& rhs);

		// the simple accessor functions

		//! The parameter name
		/*!
		    \return the name of the parameter
		*/
		inline const TString& name() const {return name_;}

		//! The value of the parameter
		/*!
		    \return the value of the parameter
		*/
		inline Double_t value() const {return value_;}

		//! The error on the parameter
		/*!
		    \return the error on the parameter
		*/
		inline Double_t error() const {return error_;}

		//! The lower error on the parameter
		/*!
		    \return the lower error on the parameter
		*/
		inline Double_t negError() const {return negError_;}

		//! The upper error on the parameter
		/*!
		    \return the upper error on the parameter
		*/
		inline Double_t posError() const {return posError_;}

		//! The value generated for the parameter
		/*!
		    \return the value generated for the parameter
		*/
		inline Double_t genValue() const {return genValue_;}

		//! The initial value of the parameter
		/*!
		    \return the initial value of the parameter given to the fitter
		*/
		inline Double_t initValue() const {return initValue_;}

		//! The minimum value allowed for the parameter
		/*!
		    \return the minimum value allowed for the parameter
		*/
		inline Double_t minValue() const {return minValue_;}

		//! The maximum value allowed for the parameter
		/*!
		    \return the maximum value allowed for the parameter
		*/
		inline Double_t maxValue() const {return maxValue_;}

		//! The range allowed for the parameter
		/*!
		    \return the range allowed for the parameters, defined as the difference between the max and min value
		*/
		inline Double_t range() const {return this->maxValue() - this->minValue();}

		//! Check whether the parameter is fixed or floated
		/*!
		    \return the boolean flag true/false whether the parameter is fixed
		*/
		inline Bool_t fixed() const {return fixed_;}

		//! Check whether the parameter should be floated only in the first stage of a two stage fit
		/*!
		    \return the boolean flag true/false whether it floats only in the first stage
		*/
		inline Bool_t firstStage() const {return firstStage_;}

		//! Check whether the parameter should be floated only in the second stage of a two stage fit
		/*!
		    \return the boolean flag true/false whether it floats only in the second stage
		*/
		inline Bool_t secondStage() const {return secondStage_;}

		//! Check whether Gaussian constraints are needed  
		/*!
		    \return the boolean flag true/false whether the Gaussian constraints are needed
		*/
		inline Bool_t gaussCon() const {return gaussCon_;}

		//! The mean of the Gaussian constraint
		/*!
		    \return the mean value of the Gaussian constraint
		*/
		inline Double_t gaussMean() const {return gaussMean_;}

		//! The width of the Gaussian constraint
		/*!
		    \return the width of the Gaussian constraint
		*/
		inline Double_t gaussWidth() const {return gaussWidth_;}

		//! The parameter global correlation coefficient
		/*!
		    \return the global correlation coefficient
		*/
		inline Double_t globalCorrelationCoeff() const {return gcc_;}

		//! The bias in the parameter
		/*!
		    \return the bias in the parameter, defined as the difference between the value and the generated value
		*/
		inline Double_t bias() const {return bias_;}

		//! The pull value for the parameter
		/*!
		    \return the pull value for the parameter, defined as the bias divided by the error
		*/
		inline Double_t pull() const {return pull_;}

		// the simple "setter" functions

		//! Set the parameter name
		/*!
		    \param [in] newName the name of the parameter
		*/
		void name(const TString& newName);

		//! Set the value of the parameter
		/*!
		    \param [in] newValue the value of the parameter
		*/
		void value(Double_t newValue);

		//! Set the error on the parameter
		/*!
		    \param [in] newError the error on the parameter
		*/
		void error(Double_t newError);

		//! Set the lower error on the parameter
		/*!
		    \param [in] newNegError the lower error on the parameter
		*/
		void negError(Double_t newNegError);

		//! Set the upper error on the parameter
		/*!
		    \param [in] newPosError the upper error on the parameter
		*/
		void posError(Double_t newPosError);

		//! Set the error values on the parameter
		/*!
		    \param [in] newError the error on the parameter
		    \param [in] newNegError the lower error on the parameter
		    \param [in] newPosError the upper error on the parameter
		*/
		void errors(Double_t newError, Double_t newNegError, Double_t newPosError);

		//! Set the value and errors on the parameter
		/*!
		    \param [in] newValue the value of the parameter
		    \param [in] newError the error on the parameter
		    \param [in] newNegError the lower error on the parameter (default set to zero)
		    \param [in] newPosError the upper error on the parameter (default set to zero)
		*/
		void valueAndErrors(Double_t newValue, Double_t newError, Double_t newNegError = 0.0, Double_t newPosError = 0.0);

		//! Set the global correlation coefficient
		/*!
		    \param [in] gcc the value of the coefficient
		*/
		void globalCorrelationCoeff(Double_t newGCCValue);

		//! Set the generated value for the parameter
		/*!
		    \param [in] newGenValue the generated value for the parameter
		*/
		void genValue(Double_t newGenValue);

		//! Set the inital value for the parameter
		/*!
		    \param [in] newInitValue the initial value for the parameter
		*/
		void initValue(Double_t newInitValue);

		//! Set the minimum value for the parameter
		/*!
		    \param [in] newMinValue the minimum value for the parameter
		*/
		void minValue(Double_t newMinValue);

		//! Set the maximum value for the parameter
		/*!
		    \param [in] newMaxValue the maximum value for the parameter
		*/
		void maxValue(Double_t newMaxValue);

		//! Set the range for the parameter
		/*!
		    \param [in] newMinValue the minimum value for the parameter
		    \param [in] newMaxValue the maximum value for the parameter
		*/
		void range(Double_t newMinValue, Double_t newMaxValue);

		//! Set the value and range for the parameter
		/*!
		    \param [in] newValue the value of the parameter
		    \param [in] newMinValue the minimum value for the parameter
		    \param [in] newMaxValue the maximum value for the parameter
		*/
		void valueAndRange(Double_t newValue, Double_t newMinValue, Double_t newMaxValue);

		//! Fix or float the given parameter
		/*!
		    \param [in] parFixed boolean flag to fix or float the parameter
		*/
		void fixed(Bool_t parFixed);

		//! Set parameter as first-stage or not of the fit
		/*!
		    \param [in] firstStagePar boolean flag to check whether is a first-stage parameter
		*/
		void firstStage(Bool_t firstStagePar);

		//! Set parameter as second-stage or not of the fit
		/*!
		    \param [in] secondStagePar boolean flag to check whether is a second-stage parameter
		*/
		void secondStage(Bool_t secondStagePar);

		//! Choice to use Gaussian constraints
		/*!
		    \param [in] newGaussCon boolean flag to use Gaussian constraints
		*/
		void gaussCon(Bool_t newGaussCon);

		//! Set the Gaussian mean
		/*!
		    \param [in] newGaussMean the new value of the Gaussian mean
		*/
		void gaussMean(Double_t newGaussMean);

		//! Set the Gaussian width
		/*!
		    \param [in] newGaussWidth the new value of the Gaussian width
		*/
		void gaussWidth(Double_t newGaussWidth);

		//! Set the Gaussian parameters
		/*!
		    \param [in] newGaussCon boolean flag to use Gaussian constraints
		    \param [in] newGaussMean the new value of the Gaussian mean
		    \param [in] newGaussWidth the new value of the Gaussian width
		*/
		void gaussParam(Bool_t newGaussCon, Double_t newGaussMean, Double_t newGaussWidth);

		// operators

		//! Basic assignment  
		/*!
		   \param [in] val value to be assigned
		*/
		LauParameter& operator = (Double_t val);

		//! Addition assignment operator
		/*!
		   \param [in] val the value to be added to this one
		*/
		LauParameter& operator += (Double_t val);

		//! Subtraction assignment operator
		/*!
		   \param [in] val the value to be subtracted from this one
		*/
		LauParameter& operator -= (Double_t val);

		//! Multiplication assignment operator
		/*!
		   \param [in] val the value this one is to be multiplied by
		*/
		LauParameter& operator *= (Double_t val);

		//! Division assignment operator
		/*!
		   \param [in] val the value this one one is to be divided by
		*/
		LauParameter& operator /= (Double_t val);

		// functions for the cloning mechanism

		//! Check whether is a clone or not
		/*!
		   \return true/false whether is a clone
		*/
		inline Bool_t clone() const {return clone_;}

		//! Method to create a clone from the parent parameter using the copy constructor
		/*!
		   \param [in] constFactor the optional constant factor by which the clone shold be multiplied
		   \return the cloned parameter
		*/
		LauParameter* createClone(Double_t constFactor = 1.0);

		//! Method to create a clone from the parent parameter using the copy constructor and setting a new name
		/*!
		   \param [in] newName the new name of the cloned parameter
		   \param [in] constFactor the optional constant factor by which the clone shold be multiplied
		   \return the cloned parameter
		*/
		LauParameter* createClone(const TString& newName, Double_t constFactor = 1.0);

		//! Call to update the bias and pull values
		void updatePull();

		//! Randomise the value of the parameter (if it is floating).
		/*!
		   The pre-defined parameter range is used as the randomisation range.
		*/
		void randomiseValue();

		//! Randomise the value of the parameter (if it is floating).
		/*!
		   Use the given range unless either of the given values are
		   outside the range of the parameter, in which case that value
		   will be altered to the current max or min.

		   \param [in] minVal the minimum value for the parameter 
		   \param [in] maxVal the maximum value for the parameter 
		*/
		void randomiseValue(Double_t minVal, Double_t maxVal);

	protected:
		//! Method to check whether value provided is within the range and that the minimum and maximum limits make sense 
		/*!
		   \param [in] val the value of the parameter
		   \param [in] minVal the minimum value allowed
		   \param [in] maxVal the maximum value allowed
		*/
		void checkRange(Double_t val, Double_t minVal, Double_t maxVal);

		//! Method to check whether value provided is whithin the range and that the minimum and maximum limits make sense 
		inline void checkRange()
		{
			this->checkRange(this->value(),this->minValue(),this->maxValue());
		}

		//! Mark this as a clone of the given parent
		/*!
		    \param theparent the parent parameter
		*/
		inline void clone(LauParameter* theparent) {
			parent_ = theparent;
			clone_ = (parent_==0) ? kFALSE : kTRUE;
		}

		//! The parent parameter
		/*!
		    \return the parent parameter
		*/
		inline LauParameter* parent() const {return parent_;}

		//! Method to clear the clone parameters
		inline void wipeClones() {clones_.clear();}

		//! Method to update clone values
		/*!
		    \param [in] justValue boolean flag to determine whether it is necessary to update all the parameter settings or only its value.
		*/
		void updateClones(Bool_t justValue = kFALSE);

	private:
		//! LauFitNtuple is a friend class
		friend class LauFitNtuple;

		//! The parameter name
		TString name_;

		//! The parameter value
		Double_t value_;

		//! The error on the parameter
		Double_t error_;
		//! The lower error on the parameter
		Double_t negError_;
		//! The upper error on the parameter
		Double_t posError_;

		//! Toy generation value
		Double_t genValue_;

		//! Initial fit value
		Double_t initValue_;
		//! Minimum value for the parameter
		Double_t minValue_;
		//! Maximum value for the parameter
		Double_t maxValue_;

		//! Fix/float option for parameter
		Bool_t fixed_;
		//! Flag whether it is floated only in the first stage of the fit
		Bool_t firstStage_;
		//! Flag whether it is floated only in the second stage of the fit
		Bool_t secondStage_;

		//! Choice to use Gaussian constraint
		Bool_t gaussCon_;
		//! Mean value of the Gaussian constraint
		Double_t gaussMean_;
		//! Width of the Gaussian constraint
		Double_t gaussWidth_;

		//! Global correlation coefficient
		Double_t gcc_;

		//! Parameter bias
		Double_t bias_;
		//! Parameter pull
		Double_t pull_;

		//! Flag whether the parameter is a clone
		Bool_t clone_;
		//! The parent parameter
		LauParameter* parent_;

		//! The clones of this parameter
		std::map<LauParameter*, Double_t> clones_;

		ClassDef(LauParameter, 1)

};

// operators to allow mathematical operations with double precision numbers
Double_t operator + (const LauParameter& lhs, Double_t rhs);
Double_t operator + (Double_t lhs, const LauParameter& rhs);
Double_t operator + (const LauParameter& lhs, const LauParameter& rhs);
Double_t operator - (const LauParameter& lhs, Double_t rhs);
Double_t operator - (Double_t lhs, const LauParameter& rhs);
Double_t operator - (const LauParameter& lhs, const LauParameter& rhs);
Double_t operator * (const LauParameter& lhs, Double_t rhs);
Double_t operator * (Double_t lhs, const LauParameter& rhs);
Double_t operator * (const LauParameter& lhs, const LauParameter& rhs);
Double_t operator / (const LauParameter& lhs, Double_t rhs);
Double_t operator / (Double_t lhs, const LauParameter& rhs);
Double_t operator / (const LauParameter& lhs, const LauParameter& rhs);
Double_t operator += (Double_t& lhs, const LauParameter& rhs);
Double_t operator -= (Double_t& lhs, const LauParameter& rhs);
Double_t operator *= (Double_t& lhs, const LauParameter& rhs);
Double_t operator /= (Double_t& lhs, const LauParameter& rhs);

//! Output stream operator
ostream& operator << (ostream& stream, const LauParameter& par);

//! Type to define an array of parameters
typedef std::vector< std::vector<LauParameter> >  LauParArray;

#endif
