#ifndef BL_RUNGAKUTTA_HPP
#define BL_RUNGAKUTTA_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A collection of runga-kutta
///                 methods to solve systems of
///                 differential equations
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
#include <vector>
#include "blNumericFunctions.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function calculates one step
// of an ODE system using the 4th-order Runge-Kutta
// algorithm
//
// - Use it in a loop to numerically compute
//   the solution to an ODE system
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blStateVectorType,
         typename blInitialConditionsVectorType,
         typename blRKcoeffsVectorType,
         typename blODEFunctorType>

inline void rk4(const blODEFunctorType& ODEfunctor,
                const int& numberOfStateVariables,
                const blInitialConditionsVectorType& y0,
                const blNumberType& t,
                const blNumberType& h,
                blStateVectorType& y,
                blRKcoeffsVectorType& RKcoeffs,
                blStateVectorType& yTemp)
{
    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the state variables vector and
    //              the same as the size of the
    //              initial conditions vector.
    //
    //          2.  The size of the Runge-Kutta coefficients
    //              vector is four times the size of the
    //              state variables vector
    //
    //          3.  The coefficient vector
    //              is 4*StateSize coefficients
    //
    //          4.  The coefficients vector is ordered in
    //              sequential order like:  K1,L1,M1,N1,
    //              K2,L2,M2,N2,...,K4,L4,M4,N4

    // Calculate the first
    // coefficients

    ODEfunctor(t,y0,yTemp);

    // Update the state
    // values for calculating
    // the second coefficients

    for(int i = 0; i < numberOfStateVariables; ++i)
    {
        RKcoeffs[i] = yTemp[i];

        y[i] = y0[i] + h * RKcoeffs[i]/2.0;
    }

    // Calculate the second
    // coefficients

    ODEfunctor(t + h/2.0,y,yTemp);

    // Update the state
    // values for calculating
    // the third coefficients

    for(int i = 0; i < numberOfStateVariables; ++i)
    {
        RKcoeffs[i + numberOfStateVariables] = yTemp[i];

        y[i] = y0[i] + h * RKcoeffs[i + numberOfStateVariables]/2.0;
    }

    // Calculate the third
    // coefficients

    ODEfunctor(t + h/2.0,y,yTemp);

    // Update the state
    // values for calculating
    // the fourth coefficients

    for(int i = 0; i < numberOfStateVariables; ++i)
    {
        RKcoeffs[i + 2 * numberOfStateVariables] = yTemp[i];

        y[i] = y0[i] + h * RKcoeffs[i + 2 * numberOfStateVariables];
    }

    // Calculate the fourth
    // coefficients

    ODEfunctor(t + h,y,yTemp);

    // Finally we calculate the
    // new values of the state
    // variables

    for(int i = 0; i < numberOfStateVariables; ++i)
    {
        RKcoeffs[i + 3 * numberOfStateVariables] = yTemp[i];

        y[i] = y0[i] + (h / 6.0) * (RKcoeffs[i] + 2.0 * RKcoeffs[i + numberOfStateVariables] + 2.0 * RKcoeffs[i + 2 * numberOfStateVariables] + RKcoeffs[i + 3 * numberOfStateVariables]);
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function calculates one step
// of an ODE system using the 4th-order Runge-Kutta-Gill
// algorithm
//
// - Use it in a loop to numerically compute
//   the solution to an ODE system
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blStateVectorType,
         typename blInitialConditionsVectorType,
         typename blRKcoeffsVectorType,
         typename blODEFunctorType>

inline void rkg4(const blODEFunctorType& ODEfunctor,
                 const int& n,
                 const blInitialConditionsVectorType& y0,
                 const blNumberType& t,
                 const blNumberType& h,
                 blStateVectorType& y,
                 blRKcoeffsVectorType& k,
                 blStateVectorType& yTemp)
{
    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the state variables vector and
    //              the same as the size of the
    //              initial conditions vector.
    //
    //          2.  The size of the Runge-Kutta coefficients
    //              vector is four times the size of the
    //              state variables vector
    //
    //          3.  The coefficient vector
    //              is 4*StateSize coefficients
    //
    //          4.  The coefficients vector is ordered in
    //              sequential order like:  K1,L1,M1,N1,
    //              K2,L2,M2,N2,...,K4,L4,M4,N4

    // numerical constants
    // used throughout the
    // algorithm that never
    // change

    static blNumberType c1 = 1.0 / std::sqrt(2.0);
    static blNumberType c2 = c1 - 0.5;
    static blNumberType c3 = 1.0 - c1;
    static blNumberType c4 = 1.0 + c1;

    blNumberType half_h = h / 2.0;

    // Calculate the first
    // coefficients

    ODEfunctor(t,y0,yTemp);

    // Update the state
    // values for calculating
    // the second coefficients

    for(int i = 0; i < n; ++i)
    {
        k[i] = yTemp[i];

        y[i] = y0[i] + half_h * k[i];
    }

    // Calculate the second
    // coefficients

    ODEfunctor(t + half_h,y,yTemp);

    // Update the state
    // values for calculating
    // the third coefficients

    for(int i = 0; i < n; ++i)
    {
        k[i + n] = yTemp[i];

        y[i] = y0[i] + c2 * h * k[i] + c3 * h * k[i + n]/2.0;
    }

    // Calculate the third
    // coefficients

    ODEfunctor(t + half_h,y,yTemp);

    // Update the state
    // values for calculating
    // the fourth coefficients

    for(int i = 0; i < n; ++i)
    {
        k[i + 2 * n] = yTemp[i];

        y[i] = y0[i] - c1 * h * k[i + n] + c4 * h * k[i + 2 * n];
    }

    // Calculate the fourth
    // coefficients

    ODEfunctor(t + h,y,yTemp);

    // Finally we calculate the
    // new values of the state
    // variables

    for(int i = 0; i < n; ++i)
    {
        k[i + 3 * n] = yTemp[i];

        y[i] = y0[i] + (h / 6.0) * (k[i] + 2.0 * k[i + n] + 2.0 * k[i + 2 * n] + k[i + 3 * n]);
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function numerically solves
// an ODE system using a fixed-step 4th-order
// Runge-Kutta algorithm
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blSolutionMatrixType,
         typename blInitialConditionsVectorType,
         typename blODEFunctorType>

inline void rk4Solver(const blODEFunctorType& ODEfunctor,
                      const int& numberOfStateVariables,
                      blNumberType& t0,
                      blNumberType& tf,
                      const int& numberOfSteps,
                      blSolutionMatrixType& y,
                      const blInitialConditionsVectorType& y0)
{
    if(numberOfStateVariables <= 0)
        return;

    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the initial conditions vector
    //              and they both are the size stated
    //              by the numberOfStateVariables
    //
    //          2.  The solution is a vector of vectors,
    //              or matrix, where the rows correspond
    //              to the different solutions (y1,y2,y3,...,yn)
    //              and each row vector is as long as
    //              the specified numberOfSteps + 1, and
    //              there are as many rows as the
    //              specified numberOfStateVariables


    // Calculate the time step

    blNumberType h = (tf - t0) / blNumberType(numberOfSteps);

    // Variable used for time

    blNumberType t = t0;

    // The vector of coefficients
    // used in the rk4 algorithm

    std::vector<blNumberType> RKGcoeffs(numberOfStateVariables * 4,blNumberType(0));

    // These vectors hold the
    // following information:
    //
    // 1.   Current state to update
    // 2.   Initial conditions at
    //      the current time step
    // 3.   Intermediate calculation
    //      results

    blInitialConditionsVectorType currentStateVector(numberOfStateVariables,blNumberType(0));
    blInitialConditionsVectorType initialConditions(numberOfStateVariables,blNumberType(0));
    blInitialConditionsVectorType yTemp(numberOfStateVariables,blNumberType(0));

    for(int i = 0; i < numberOfStateVariables; ++i)
        initialConditions[i] = y0[i];

    // Loop through each time
    // step and calculate the
    // solution vectors

    for(int i = 1; i < numberOfSteps; ++i)
    {
        // Solve the current state

        rkg4(ODEfunctor,numberOfStateVariables,initialConditions,t,h,currentStateVector,RKGcoeffs,yTemp);

        // Store the solved state
        // into the solution vectors

        for(int j = 0; j < numberOfStateVariables; ++j)
            y[j][i + 1] = currentStateVector[j];

        // Store the just solved
        // state as the initial
        // conditions

        for(int j = 0; j < numberOfStateVariables; ++j)
            initialConditions[j] = currentStateVector[j];

        t += h;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function implements one step of
// the Runge-Kutta-Fehlberg algorithm for adaptive
// integration of a system of equations
//
// - Use it in a loop to numerically compute
//   the solution to an ODE system
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blStateVectorType,
         typename blInitialConditionsVectorType,
         typename blRKcoeffsVectorType,
         typename blODEFunctorType>

inline void rkf(const blODEFunctorType& ODEfunctor,
                const int& n,
                const blInitialConditionsVectorType& y0,
                const blNumberType& t,
                const blNumberType& h,
                blStateVectorType& y4th,
                blStateVectorType& y5th,
                blRKcoeffsVectorType& k,
                blStateVectorType& yTemp)
{
    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the state variables vector and
    //              the same as the size of the
    //              initial conditions vector.
    //
    //          2.  The size of the Runge-Kutta coefficients
    //              vector is four times the size of the
    //              state variables vector
    //
    //          3.  The coefficient vector
    //              is 4*StateSize coefficients
    //
    //          4.  The coefficients vector is ordered in
    //              sequential order like:  K1,L1,M1,N1,
    //              K2,L2,M2,N2,...,K4,L4,M4,N4

    // Calculate the K1 coeffs

    ODEfunctor(t,y0,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i] = h * yTemp[i];

        y4th[i] = y0[i] + 0.25 * k[i];
    }

    // Calculate the K2 coeffs

    ODEfunctor(t + 0.25 * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + n] = h * yTemp[i];

        y4th[i] = y0[i] + 0.09375 * k[i] + 0.28125 * k[i + n];
    }

    // Calculate the K3 coeffs

    ODEfunctor(t + 0.375 * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 2 * n] = h * yTemp[i];

        y4th[i] = y0[i] + (1932.0/2197.0) * k[i] - (7200.0/2197.0) * k[i + n] + (7296.0/2197.0) * k[i + 2 * n];
    }

    // Calculate the K4 coeffs

    ODEfunctor(t + (12.0/13.0) * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 3 * n] = h * yTemp[i];

        y4th[i] = y0[i] + (439.0/216.0) * k[i] - 8.0 * k[i + n] + (3680.0/513.0) * k[i + 2 * n] - (845.0/4101.0) * k[i + 3 * n];
    }

    // Calculate the K5 coeffs

    ODEfunctor(t + h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 4 * n] = h * yTemp[i];

        y4th[i] = y0[i] - (8.0/27) * k[i] + 2.0 * k[i + n] - (3544.0/2565.0) * k[i + 2 * n] + (1859.0/4104.0) * k[i + 3 * n] - 0.275 * k[i + 4 * n];
    }

    // Calculate the K6 coeffs

    ODEfunctor(t + 0.5 * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 5 * n] = h * yTemp;

        // Using the 4th-order RK

        y4th[i] = y0[i] + (25.0/216.0) * k[i] + (1408.0/2565.0) * k[i + 2 * n] + (2197.0/4104.0) * k[1 + 3 * n] - 0.20 * k[i + 4 * n];

        // Using the 5th-order RK

        y5th[i] = y0[i] + (16.0/135.0) * k[i] + (6656.0/12825.0) * k[i + 2 * n] + (28561.0/56430.0) * k[i + 3 * n] - 0.18 * k[i + 4 * n] + (2.0/55.0) * k[i + 5 * n];
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function implements one step of
// the CAsh-Karp algorithm for adaptive
// integration of a system of equations
//
// - Use it in a loop to numerically compute
//   the solution to an ODE system
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blStateVectorType,
         typename blInitialConditionsVectorType,
         typename blRKcoeffsVectorType,
         typename blODEFunctorType>

inline void rkCK(const blODEFunctorType& ODEfunctor,
                 const int& n,
                 const blInitialConditionsVectorType& y0,
                 const blNumberType& t,
                 const blNumberType& h,
                 blStateVectorType& y4th,
                 blStateVectorType& y5th,
                 blRKcoeffsVectorType& k,
                 blStateVectorType& yTemp)
{
    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the state variables vector and
    //              the same as the size of the
    //              initial conditions vector.
    //
    //          2.  The size of the Runge-Kutta coefficients
    //              vector is four times the size of the
    //              state variables vector
    //
    //          3.  The coefficient vector
    //              is 4*StateSize coefficients
    //
    //          4.  The coefficients vector is ordered in
    //              sequential order like:  K1,L1,M1,N1,
    //              K2,L2,M2,N2,...,K4,L4,M4,N4

    // Calculate the K1 coeffs

    ODEfunctor(t,y0,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i] = h * yTemp[i];

        y4th[i] = y0[i] + 0.20 * k[i];
    }

    // Calculate the K2 coeffs

    ODEfunctor(t + 0.20 * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + n] = h * yTemp[i];

        y4th[i] = y0[i] + (3.0/40.0) * k[i] + (9.0/40.0) * k[i + n];
    }

    // Calculate the K3 coeffs

    ODEfunctor(t + 0.3 * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 2 * n] = h * yTemp[i];

        y4th[i] = y0[i] + 0.3 * k[i] - 0.9 * k[i + n] + (6.0/5.0) * k[i + 2 * n];
    }

    // Calculate the K4 coeffs

    ODEfunctor(t + (3.0/5.0) * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 3 * n] = h * yTemp[i];

        y4th[i] = y0[i] - (11.0/54.0) * k[i] + 2.5 * k[i + n] - (70.0/27.0) * k[i + 2 * n] + (35.0/27.0) * k[i + 3 * n];
    }

    // Calculate the K5 coeffs

    ODEfunctor(t + h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 4 * n] = h * yTemp[i];

        y4th[i] = y0[i] + (1631.0/55296.0) * k[i] + (175.0/512.0) * k[i + n] + (575.0/13824.0) * k[i + 2 * n] + (44275.0/110592.0) * k[i + 3 * n] + (253.0/4096.0) * k[i + 4 * n];
    }

    // Calculate the K6 coeffs

    ODEfunctor(t + (7.0/8.0) * h,y4th,yTemp);

    for(int i = 0; i < n; ++i)
    {
        k[i + 5 * n] = h * yTemp;

        // Using the 4th-order RK

        y4th[i] = y0[i] + (37.0/378.0) * k[i] + (250.0/621.0) * k[i + 2 * n] + (125.0/594.0) * k[1 + 3 * n] + (512.0/1771.0) * k[i + 4 * n];

        // Using the 5th-order RK

        y5th[i] = y0[i] + (2825.0/27648.0) * k[i] + (18575.0/48384.0) * k[i + 2 * n] + (13525.0/55296.0) * k[i + 3 * n] + (277.0/14336.0) * k[i + 4 * n] + 0.25 * k[i + 5 * n];
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function numerically solves
// an ODE system using a fixed-step 4th-order
// Runge-Kutta algorithm
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blSolutionMatrixType,
         typename blTimeVectorType,
         typename blInitialConditionsVectorType,
         typename blODEFunctorType>

inline int rkfCKSolver(const blODEFunctorType& ODEfunctor,
                       const int& numberOfStateVariables,
                       blNumberType& t0,
                       blNumberType& tf,
                       const int& minNumberOfSteps,
                       const int& maxNumberOfSteps,
                       blSolutionMatrixType& y,
                       blTimeVectorType t,
                       const blInitialConditionsVectorType& y0,
                       const blNumberType& minError,
                       const blNumberType& maxError)
{
    if(numberOfStateVariables <= 0 ||
       minNumberOfSteps > maxNumberOfSteps ||
       maxNumberOfSteps <= 0)
    {
        return 0;
    }

    // NOTE:  This function assumes the following:
    //
    //          1.  The size of the state equations
    //              vector is the same as the size
    //              of the initial conditions vector
    //              and they both are the size stated
    //              by the numberOfStateVariables
    //
    //          2.  The solution is a vector of vectors,
    //              or matrix, where the rows correspond
    //              to the different solutions (y1,y2,y3,...,yn)
    //              and each row vector is as long as
    //              the specified numberOfSteps + 1, and
    //              there are as many rows as the
    //              specified numberOfStateVariables


    // Calculate the min
    // and max time steps

    blNumberType hmin = (tf - t0) / blNumberType(maxNumberOfSteps);
    blNumberType hmax = (tf - t0) / blNumberType(minNumberOfSteps);

    // The time variable

    blNumberType currentTime = t0;

    // The initial time step

    blNumberType h = (hmax + hmin) / 2.0;

    // Error for each step

    blNumberType stepError = 0;

    // The actual number of
    // steps taken by the
    // algorithm to reach the
    // final time tf

    int n = 0;

    // Variable used to calculate
    // the new step in case the
    // error is too big or too
    // small

    blNumberType s = 0;

    // The vector of coefficients
    // used in the rkf algorithm
    // k1,k2,k3,k4,k5,k6

    std::vector<blNumberType> RKFcoeffs(numberOfStateVariables * 6,blNumberType(0));

    // These vectors hold the
    // following information:
    //
    // 1.   Current state to update using 4th-order
    // 2.   Current state to update using 5th-order
    // 3.   Initial conditions at
    //      the current time step
    // 4.   Intermediate calculation
    //      results

    blInitialConditionsVectorType y4thCurrentStateVector(numberOfStateVariables,blNumberType(0));
    blInitialConditionsVectorType y5thCurrentStateVector(numberOfStateVariables,blNumberType(0));
    blInitialConditionsVectorType initialConditions(numberOfStateVariables,blNumberType(0));
    blInitialConditionsVectorType yTemp(numberOfStateVariables,blNumberType(0));

    for(int i = 0; i < numberOfStateVariables; ++i)
        initialConditions[i] = y0[i];

    // Loop through each time
    // step and calculate the
    // solution vectors

    while(currentTime < tf && n < maxNumberOfSteps)
    {
        // Solve the current state

        rkCK(ODEfunctor,
             numberOfStateVariables,
             initialConditions,
             t,
             h,
             y4thCurrentStateVector,
             y5thCurrentStateVector,
             RKFcoeffs,
             yTemp);

        // Calculate the max error

        stepError = 0;

        for(int i = 0; i < numberOfStateVariables; ++i)
            stepError = std::max(stepError,std::abs(y5thCurrentStateVector[i] - y4thCurrentStateVector[i]));

        // Let's compare the current
        // step error to the specified
        // min/max errors

        if(stepError <= maxError)
        {
            // In this case the step
            // didn't cause too large
            // of an error, so we can
            // store the results and
            // move to the next step

            for(int j = 0; j < numberOfStateVariables; ++j)
                y[j][n + 1] = y5thCurrentStateVector[j];

            for(int j = 0; j < numberOfStateVariables; ++j)
                initialConditions[j] = y5thCurrentStateVector[j];

            t[n] = currentTime;

            currentTime += h;

            ++n;

            // Before we move on
            // let's check if maybe
            // the step was too small,
            // which means we can make
            // it bigger

            if(stepError < minError)
            {
                s = 0.84 * std::pow(minError / stepError,0.25);

                h = s*h;
            }
        }
        else
        {
            // In this case the step was
            // too small, and we can
            // make it bigger

            s = 0.84 * std::pow(maxError / stepError,0.25);

            h = s * h;
        }
    }

    return n;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_RUNGAKUTTA_HPP
