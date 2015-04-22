
// Copyright University of Warwick 2006 - 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Authors:
// Thomas Latham
// John Back
// Paul Harrison

/*! \file Lau1DCubicSpline.hh
    \brief File containing declaration of Lau1DCubicSpline class.
 */

/*! \class Lau1DCubicSpline
    \brief File containing implementation of Lau1DCubicSpline class.

    Class for defining a 1D cubic spline based on a set of knots.
    The spline is defined by a piecewise cubic function which, between knots i and i+1, has the form

    f_i(x) = (1 - t)*y_i + t*y_i+1 + t*(1 - t)(a*(1 - t) + b*t)

    where t = (x - x_i)/(x_i+1 - x_i),
    a =  k_i  *(x_i+1 - x_i) - (y_i+1 - y_i),
    b = -k_i+1*(x_i+1 - x_i) + (y_i+1 - y_i)

    and k_i is (by construction) the first derivative at knot i.

    f(x) and f'(x) are continuous at the internal knots by construction.
    f''(x) is required to be continuous at all internal knots placing n-2 constraints on the n parameters, k_i.
    The final two constraints are set by the boundary conditions.
    At each boundary, the function may be:

    (i)   Clamped :     f'(x) = C at the last knot
    (ii)  Natural :     f''(x) = 0 at the last knot
    (iii) Not a knot :  f'''(x) continuous at the second last knot

    The algorithms used in this class can be found on:
    http://en.wikipedia.org/wiki/Spline_interpolation#Algorithm_to_find_the_interpolating_cubic_spline
    http://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 */

#ifndef LAU_1DCUBICSPLINE
#define LAU_1DCUBICSPLINE

#include <vector>

#include "Rtypes.h"

class Lau1DCubicSpline {

	public:
		//! Define the allowed boundary condition types
		enum LauSplineBoundaryType {
			Clamped, /*!< clamped boundary - f'(x) = C */
			Natural, /*!< natural boundary - f''(x) = 0 */
			NotAKnot /*!< 'not a knot' boundary - f'''(x) continuous at second last knot */
		};

		//! Constructor
		/*!
		    /param [in] xs the x-values of the knots
		    /param [in] ys the y-values of the knots
		    /param [in] leftBound the left-hand boundary condition
		    /param [in] rightBound the right-hand boundary condition
		    /param [in] dydx0 the gradient at the left-hand boundary of a clamped spline
		    /param [in] dydxn the gradient at the right-hand boundary of a clamped spline
		*/
		Lau1DCubicSpline(const std::vector<Double_t>& xs, const std::vector<Double_t>& ys,
				 LauSplineBoundaryType leftBound = Lau1DCubicSpline::NotAKnot, 
				 LauSplineBoundaryType rightBound = Lau1DCubicSpline::NotAKnot,
				 Double_t dydx0 = 0.0, Double_t dydxn = 0.0);

		//! Destructor
		virtual ~Lau1DCubicSpline();

		//! Evaluate the function at given point
		/*!
		    \param [in] x the x-coordinate
		    \return the value of the spline at x
		*/
		Double_t evaluate(Double_t x) const;

		//! Update the y-values of the knots
		/*!
		    \param [in] ys the y-values of the knots
		*/
		void updateYValues(const std::vector<Double_t>& ys);

		//! Update the boundary conditions for the spline
		/*!
		    /param [in] leftBound the left-hand boundary condition
		    /param [in] rightBound the right-hand boundary condition
		    /param [in] dydx0 the gradient at the left-hand boundary of a clamped spline
		    /param [in] dydxn the gradient at the right-hand boundary of a clamped spline
		*/
		void updateBoundaryConditions(LauSplineBoundaryType leftBound, 
					      LauSplineBoundaryType rightBound, 
					      Double_t dydx0 = 0.0,
					      Double_t dydxn = 0.0);

	private:
		//! Copy constructor - not implemented
		Lau1DCubicSpline( const Lau1DCubicSpline& rhs );

		//! Copy assignment operator - not implemented
		Lau1DCubicSpline& operator=(const Lau1DCubicSpline& rhs);

		//! Initialise the class
		void init();

		//! Calculate the first derivative at each knot
		void calcDerivatives();

		//! The number of knots in the spline
		const UInt_t nKnots_;

		//! The x-value at each knot
		std::vector<Double_t> x_;
		//! The y-value at each knot
		std::vector<Double_t> y_;
		//! The first derivative at each knot
		std::vector<Double_t> dydx_;

		//! The 'a' coefficients used to determine the derivatives
		std::vector<Double_t> a_;
		//! The 'b' coefficients used to determine the derivatives
		std::vector<Double_t> b_;
		//! The 'c' coefficients used to determine the derivatives
		std::vector<Double_t> c_;
		//! The 'd' coefficients used to determine the derivatives
		std::vector<Double_t> d_;

		//! The left-hand boundary condition on the spline
		LauSplineBoundaryType leftBound_;
		//! The right-hand boundary condition on the spline
		LauSplineBoundaryType rightBound_;

		//! The gradient at the left boundary for a clamped spline
		Double_t dydx0_;
		//! The gradient at the right boundary for a clamped spline
		Double_t dydxn_;

		ClassDef(Lau1DCubicSpline, 0); // Class for defining a 1D cubic spline
};

#endif
