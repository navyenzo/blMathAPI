#ifndef BL_MATHAPI_HPP
#define BL_MATHAPI_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A very simple library containing some
///                 basic constants, data structures and algorithms
///                 for mathematical problems
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

// A collection of mathematical constants
// that come up often in problems

#include "blMathConstants.hpp"



// A collection of simple
// numeric functions that I have
// used and re-used throughout my work

#include "blNumericFunctions.hpp"



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
// and some useful functions
// for handling 2x2 matrices

#include "blMatrix2d.hpp"
#include "blMatrix2dOperations.hpp"



// A simple 3x3 matrix class
// and some useful functions
// for handling 3x3 matrices

#include "blMatrix3d.hpp"
#include "blMatrix3dOperations.hpp"



// A simple quaternion class
// and some useful functions
// for handling quaternions

#include "blQuaternion.hpp"
#include "blQuaternionOperations.hpp"



// A simple rectangle class
// and some useful functions
// for handling rectangles

#include "blRectangle.hpp"
#include "blRectangleOperations.hpp"



// A collection of runga-kutta
// methods to solve systems of
// differential equations

#include "blRungaKutta.hpp"

//-------------------------------------------------------------------



#endif // BL_MATHAPI_HPP
