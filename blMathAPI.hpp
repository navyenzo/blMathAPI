#ifndef BL_MATHAPI_HPP
#define BL_MATHAPI_HPP


//-------------------------------------------------------------------
// FILE:            blMath.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A very simple library containing some
//                  basic constants, data structures and algorithms
//                  for simple mathematical problems
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
// DATE CREATED:    Oct/23/2008
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
#include <cmath>
#include <limits>
#include <complex>
#include <numeric>
#include <iostream>
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
namespace blMathAPI
{
    // A collection of mathematical constants
    // that come up often in problems

    #include "blMathConstants.hpp"



    // A collection of simple
    // numeric functions that I have
    // used and re-used throughout my work

    #include "blNumericFunctions.hpp"



    // A collection of simple algorithms
    // I developed to parse data buffers

    #include "blBufferAlgorithms.hpp"



    // A collection of "downsampling"
    // algorithms for visualizing
    // large data sets

    #include "blDownsamplingAlgorithms.hpp"



    // Functions used to convert
    // strings to numbers or viceversa

    #include "blStringToNumberConversions.hpp"



    // A collection of root finding
    // methods to solve for zeros

    #include "blRootFinding.hpp"



    // A simple 2d point class
    // and some useful functions
    // for handling points

    #include "blPoint2d.hpp"
    #include "blPoint2dOperations.hpp"



    // A simple 3d vector class
    // and some useful functions
    // for handling vectors

    #include "blVector3d.hpp"
    #include "blVector3dOperations.hpp"



    // A simple 2x2 matrix class

    #include "blMatrix2d.hpp"



    // A simple 3x3 matrix class

    #include "blMatrix3d.hpp"



    // A simple quaternion class
    // and some useful functions
    // for handling quaternions

    #include "blQuaternion.hpp"
    #include "blQuaternionOperations.hpp"



    // A simple rectangle class
    // with useful functions

    #include "blRectangle.hpp"



    // A collection of runga-kutta
    // methods to solve systems of
    // differential equations

    #include "blRungaKutta.hpp"
}
//-------------------------------------------------------------------


#endif // BL_MATHAPI_HPP
