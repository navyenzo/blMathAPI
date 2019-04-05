#ifndef BL_ROOTFINDING_HPP
#define BL_ROOTFINDING_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A collection of root finding
///                 methods to solve equations of
///                 the type:  f(x) = 0
///
/// AUTHOR:         Vincenzo Barbato
///                 navyenzo@gmail.com
///
/// NOTE:           All things in this library are defined within the
///                 blMathAPI namespace
///
/// LISENSE:        MIT-LICENCE
///                 http://www.opensource.org/licenses/mit-license.php
///
///
///
///-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes needed for this file
//-------------------------------------------------------------------
#include "blNumericFunctions.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements a single step in the
// Inverse Quadratic Interpolation Method
//-------------------------------------------------------------------
template<typename blDataType>

inline blDataType& bisectionStep(const blDataType& a,
                                 const blDataType& b,
                                 blDataType& xnew)
{
    xnew = (a + b) / blDataType(2);

    return xnew;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements a single step in the
// False Position Method
//-------------------------------------------------------------------
template<typename blDataType>

inline blDataType& falsePositionStep(blDataType a,
                                     blDataType b,
                                     blDataType Fa,
                                     blDataType Fb,
                                     blDataType& xnew)
{
    xnew = (a * Fb - b * Fa) / (Fb - Fa);

    return xnew;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements a single step in the
// Secant Method
//-------------------------------------------------------------------
template<typename blDataType>

inline blDataType& secantStep(blDataType a,
                              blDataType b,
                              blDataType Fa,
                              blDataType Fb,
                              blDataType& xnew)
{
    xnew = b - Fb *  ( (b - a) / (Fb - Fa) );

    return xnew;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements a single step in the
// Inverse Quadratic Interpolation Method
//-------------------------------------------------------------------
template<typename blDataType>

inline blDataType& inverseQuadraticInterpolationStep(const blDataType& a,
                                                     const blDataType& b,
                                                     const blDataType& c,
                                                     const blDataType& Fa,
                                                     const blDataType& Fb,
                                                     const blDataType& Fc,
                                                     blDataType& xnew)
{
    xnew = (
             a * (Fb * Fc) / ((Fa - Fb)*(Fa - Fc)) +
             b * (Fa * Fc) / ((Fb - Fa)*(Fb - Fc)) +
             c * (Fa * Fb) / ((Fc - Fa)*(Fc - Fb))
           );

    return xnew;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Enum used to pick a bracketed method
//-------------------------------------------------------------------
enum blBracketedMethod {BL_BISECTION_METHOD,
                        BL_FALSE_POSITION_METHOD,
                        BL_SECANT_METHOD,
                        BL_INVERSE_QUADRATIC_INTERPOLATION_METHOD};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements a bracketed method algorithm to
// find the root of a given function, the user can choose the
// specified bracketed method:
// -- Bisection method
// -- False Position method
// -- Secant Method
// -- Inverse Quadratic Interpolation method
//-------------------------------------------------------------------
template<typename blDataType,
         typename blFunctorType>

inline blDataType bracketedMethod(blDataType a,
                                  blDataType b,
                                  const blFunctorType& functor,
                                  const blDataType& TOL,
                                  const int& maxIterations,
                                  const blBracketedMethod& method)
{
    // First we check for the specified
    // bounds being the same

    if(a == b)
    {
        return a;
    }



    // Here we evaluate the function at
    // the specified bounds

    auto Fa = functor(a);
    auto Fb = functor(b);



    // Now we check if there is a root
    // between the specified bounds
    // including the bounds themselves

    if(Fa == 0)
        return a;
    else if(Fb == 0)
        return b;
    else if(Fa * Fb > 0)
    {
        return Fa;
    }



    // The return type of the functor

    typedef decltype(Fa) blFunctorReturnType;



    // Now we move on with the method

    blDataType c = a;
    auto Fc = Fa;

    blDataType errorValue;

    int iterations = 0;

    do
    {
        // Find the next guess calling the
        // specified bracketed method

        switch(method)
        {
        case BL_BISECTION_METHOD:

            bisectionStep(a,b,c);

            break;

        case BL_FALSE_POSITION_METHOD:

            falsePositionStep(a,b,Fa,Fb,c);

            break;

        case BL_INVERSE_QUADRATIC_INTERPOLATION_METHOD:

            // For this case we need 3 distinct
            // initial guesses

            if(Fa != Fc && Fb != Fc)
                inverseQuadraticInterpolationStep(a,b,c,Fa,Fb,Fc,c);
            else
                secantStep(a,b,Fa,Fb,c);

            break;

        case BL_SECANT_METHOD:
        default:

            secantStep(a,b,Fa,Fb,c);

            break;
        }



        // Evaluate the function at the
        // newly found guess

        Fc = functor(c);



        // Assign the new bounds

        if(Fc * Fa > 0)
        {
            a = c;
            Fa = Fc;
        }
        else
        {
            b = c;
            Fb = Fc;
        }



        // Calculate the convergence error

        errorValue = blMathAPI::abs(a - b);



        // Increase the count of iterations

        ++iterations;
    }
    while((iterations < maxIterations) &&
          (Fc != blFunctorReturnType(0)) &&
          (sign(errorValue)*errorValue > sign(TOL)*TOL));



    // We return the found root

    return c;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements Brent's Method
//-------------------------------------------------------------------
template<typename blDataType,
         typename blFunctorType>

inline blDataType brentsMethod(blDataType a,
                               blDataType b,
                               const blFunctorType& functor,
                               const blDataType& convergenceTolerance,
                               const int& maxIterations)
{
    // First we check for the specified
    // bounds being the same

    if(a == b)
    {
        return a;
    }



    // Here we evaluate the function at
    // the specified bounds

    auto Fa = functor(a);
    auto Fb = functor(b);



    // Now we check if there is a root
    // between the specified bounds
    // including the bounds themselves

    if(Fa == 0)
        return a;
    else if(Fb == 0)
        return b;
    else if(Fa * Fb > 0)
    {
        return Fa;
    }



    // The next move we'll make is sort
    // a and b such that a is smaller than
    // b to facilitate Brent's method algorithm

    if(blMathAPI::abs(Fa) < blMathAPI::abs(Fb))
    {
        std::swap(a,b);
        std::swap(Fa,Fb);
    }



    // The return type of the functor

    typedef decltype(Fa) blFunctorReturnType;



    // Define the zero value

    blFunctorReturnType zero = blFunctorReturnType(0);


    // Flag used to signal whether the bisection
    // method was used last iteration step to
    // find the root

    bool mFlag = true;



    //  Bounds used to check conditions
    // necessary to invoke the bisection
    // method



    // Intermedial variables used
    // throughout the method

    blDataType lim1 = a;
    blDataType lim2 = a;

    blDataType c = a;
    blDataType s = a;
    blDataType d = a;

    auto Fc = Fa;
    auto Fs = Fa;

    blDataType absBminusA = blMathAPI::abs(b - a);
    blDataType absBminusC = blMathAPI::abs(b - c);
    blDataType absCminusD = blMathAPI::abs(c - d);
    blDataType absD = blMathAPI::abs(d);
    blDataType absSminusB = blMathAPI::abs(s - b);

    auto two = blDataType(2);
    auto three = blDataType(3);
    auto four = blDataType(4);





    // The current number of iterations

    int iterations = 0;

    int count = 0;



    while(blMathAPI::abs(Fs) > zero &&
          absBminusA > convergenceTolerance &&
          iterations < maxIterations)
    {
        if(Fc != Fa && Fc != Fb)
        {
            // In this case we invoke the
            // inverse quadratic interpolation
            // step to find the new root

            inverseQuadraticInterpolationStep(a,b,c,Fa,Fb,Fc,s);
        }
        else
        {
            // In this case we invoke the
            // secand step to find the new
            // root

            secantStep(a,b,Fa,Fb,s);
        }



        // Now we check if finding the root
        // is progressing nicely otherwise
        // we invoke the bisection method
        // to better approximate the new root

        if(a < b)
        {
            lim1 = (three * a + b)/four;
            lim2 = b;
        }
        else
        {
            lim1 = b;
            lim2 = (three * a + b)/four;
        }



        // Calculate all the absolute signs
        // needed to evaluate all the necessary
        // conditions

        absSminusB = blMathAPI::abs(s - b);
        absBminusC = blMathAPI::abs(b - c);
        absCminusD = blMathAPI::abs(c - d);
        absBminusA = blMathAPI::abs(b - a);
        absD = blMathAPI::abs(d);



        if(s < lim1 ||
           s > lim2 ||
           (mFlag == true && absSminusB >= absBminusC/two) ||
           (mFlag == false && absSminusB >= absCminusD/two) ||
           (mFlag == true && absBminusC < convergenceTolerance) ||
           (mFlag == false && absCminusD < convergenceTolerance))
        {
            bisectionStep(a,b,s);
            mFlag = true;
            ++count;
        }
        else
        {
            mFlag = false;
        }



        Fs = functor(s);



        d = c;

        c = b;
        Fc = Fb;



        if(Fa*Fs < zero)
        {
            b = s;
            Fb = Fs;
        }
        else
        {
            a = s;
            Fa = Fs;
        }



        if(blMathAPI::abs(Fa) < blMathAPI::abs(Fb))
        {
            std::swap(a,b);
            std::swap(Fa,Fb);
        }



        // Increase the count of iterations

        ++iterations;
    }



    // We return the found root

    return s;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function implements the Newton Raphson Method
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



    // We return the found root

    return xi_new;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_ROOTFINDING_HPP
