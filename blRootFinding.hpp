#ifndef BL_ROOTFINDING_HPP
#define BL_ROOTFINDING_HPP


//-------------------------------------------------------------------
// FILE:            blRootFinding.hpp
// CLASS:           blRootFinding
// BASE CLASS:      None
//
// PURPOSE:         A collection of root finding
//                  methods to solve for zeros
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:
//
// NOTES:
//
// DATE CREATED:    Sep/27/2013
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:                bisectionMethod
//
// ARGUMENTS:               - a -- 1st end point
//                          - b -- 2nd end point
//                          - TOL -- Numerical tolerance to stop
//                                   the loop at
//                          - MaxIterations -- Maximum number of
//                                             iterations to go through
//
// TEMPLATE ARGUMENTS:      - blDataType
//                          - blFunctorType
//
// PURPOSE:                 Finds the root of the specified
//                          functor between the specified
//                          end points, stopping at the
//                          specified tolerance, using the
//                          Bisection Method
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blDataType,
         typename blFunctorType>

inline blDataType bisectionMethod(blDataType a,
                                  blDataType b,
                                  const blFunctorType& functor,
                                  const blDataType& TOL,
                                  const int& maxIterations)
{
    if(a == b)
    {
        return a;
    }

    auto Fa = functor(a);
    auto Fb = functor(b);

    if(sign(Fa) == sign(Fb))
    {
        if(Fa <= Fb)
            return a;
        else
            return b;
    }

    typedef decltype(functor(a)) returnType;

    blDataType c = a;
    returnType Fc = Fa;
    blDataType c_old;
    blDataType errorValue;

    int iterations = 0;

    do
    {
        c_old = c;

        c = (a + b) / blDataType(2);

        Fc = functor(c);

        if(sign(Fc) == sign(Fa))
            a = c;
        else
            b = c;

        errorValue = sign(c - c_old) * (c - c_old) / c;

        ++iterations;
    }
    while((iterations < maxIterations) &&
          (Fc != returnType(0)) &&
          (errorValue > TOL));

    return c;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:                falsePositionMethod
//
// ARGUMENTS:               - a -- 1st end point
//                          - b -- 2nd end point
//                          - TOL -- Numerical tolerance to stop
//                                   the loop at
//                          - MaxIterations -- Maximum number of
//                                             iterations to go through
//
// TEMPLATE ARGUMENTS:      - blDataType
//                          - blFunctorType
//
// PURPOSE:                 Finds the root of the specified
//                          functor between the specified
//                          end points, stopping at the
//                          specified tolerance, using the
//                          False Position Method
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blDataType,
         typename blFunctorType>

inline blDataType falsePositionMethod(blDataType a,
                                      blDataType b,
                                      const blFunctorType& functor,
                                      const blDataType& TOL,
                                      const int& maxIterations)
{
    if(a == b)
    {
        return a;
    }

    auto Fa = functor(a);
    auto Fb = functor(b);

    if(sign(Fa) == sign(Fb))
    {
        if(Fa <= Fb)
            return a;
        else
            return b;
    }

    typedef decltype(functor(a)) returnType;

    blDataType c = a;
    returnType Fc = Fa;
    blDataType c_old;
    blDataType errorValue;

    int iterations = 0;

    do
    {
        c_old = c;

        c = c = (Fb*a - Fa*b) / (Fb - Fa);

        Fc = functor(c);

        if(sign(Fc) == sign(Fa))
        {
            a = c;
            Fa = functor(a);
        }
        else
        {
            b = c;
            Fb = functor(b);
        }

        errorValue = sign(c - c_old) * (c - c_old) / c;

        ++iterations;
    }
    while((iterations < maxIterations) &&
          (Fc != returnType(0)) &&
          (errorValue > TOL));

    return c;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:                newtonRaphsonMethod
//
// ARGUMENTS:               - xi -- Initial guess at the root
//                          - Functor -- The function we need to
//                                       find the root for
//                          - FunctorDerivative -- Derivative of the
//                                                 functor we need to
//                                                 find the root for
//                          - TOL -- Numerical tolerance to stop
//                                   the loop at
//                          - MaxIterations -- Maximum number of
//                                             iterations to go through
//
// TEMPLATE ARGUMENTS:      - blDataType
//                          - blFunctorType
//
// PURPOSE:                 Finds the root of the specified
//                          functor between the specified
//                          end points, stopping at the
//                          specified tolerance, using the
//                          Newton-Raphson Method
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blDataType,
         typename blFunctorType,
         typename blFunctorDerivativeType>

inline blDataType newtonRaphsonMethod(blDataType xi,
                                      const blFunctorType& functor,
                                      const blFunctorDerivativeType& functorDerivative,
                                      const blDataType& TOL,
                                      const int& maxIterations)
{
    // The evaluated
    // function and
    // function
    // derivative

    blDataType F = functor(xi);
    blDataType Fd = functorDerivative(xi);

    // The new root
    // value

    blDataType xi_new = xi - F/Fd;

    // The error
    // variable

    blDataType errorValue = (sign(xi_new - xi)*(xi_new - xi) / xi_new);

    // The current number
    // of iterations while
    // we're solving for
    // the root

    int iterations = 0;

    while((iterations < maxIterations) &&
          (sign(F)*F > TOL) &&
          (errorValue > TOL))
    {
        // Store the newly
        // found root value

        xi = xi_new;

        // Calculate the
        // new root and
        // the functor
        // value at the
        // new root

        F = functor(xi);
        Fd = functorDerivative(xi);

        xi_new = xi - F/Fd;

        // Calculate the
        // error for the
        // newly calculated
        // root value

        errorValue = (sign(xi_new - xi)*(xi_new - xi) / xi_new);

        ++iterations;
    }

    return xi_new;
}
//-------------------------------------------------------------------


#endif // BL_ROOTFINDING_HPP
