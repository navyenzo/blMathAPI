#ifndef BL_POINT2DOPERATIONS_HPP
#define BL_POINT2DOPERATIONS_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Useful functions for handling 2d points
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
#include "blPoint2d.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L1-norm of a point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm1(const blPoint2d<blNumberType>& p)
{
    return ( blMathAPI::abs(p.x()) + blMathAPI::abs(p.y()) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L2-norm of a point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm2(const blPoint2d<blNumberType>& p)
{
    return std::sqrt( p.x()*p.x() + p.y()*p.y() );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Linf-norm of a point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normInf(const blPoint2d<blNumberType>& p)
{
    return std::max(p.x(),p.y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Lp-norm of a point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normP(const blPoint2d<blNumberType>& point,const int& p)
{
    return blMathAPI::power(blMathAPI::power(point.x(),p) + blMathAPI::power(point.y(),p),
                            1.0 / double(p));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to normalize a point or to get
// a normalized point from a given point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& normalize(blPoint2d<blNumberType>& p)
{
    p /= norm2(p);

    return p;
}


template<typename blNumberType>
inline blPoint2d<blNumberType> getNormalized(const blPoint2d<blNumberType>& p)
{
    return (p/norm2(p));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to get a point perpendicular
// to a given point such that the dot product
// would give zero
//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType> getPerpendicularUnitPoint(const blPoint2d<blNumberType>& p)
{
    // Find a component of this
    // Point that is non zero
    // and if unsuccessfull,
    // just return the zero Point
    //
    // P1*P2 = x1*x2 + y1*y2 = 0

    if(p.x() != 0)
    {
        if(p.y() == 0)
            return blPoint2d<blNumberType>(0,1);
        else
        {
            blPoint2d<blNumberType> point(1,-p.x()/p.y());

            normalize(point);

            return point;
        }
    }
    else if(p.y() != 0)
    {
        return blPoint2d<blNumberType>(1,0);
    }

    // The Point was a zero Point,
    // therefore any Point would
    // be perpendicular, thus we
    // are just going to return
    // the zero Point

    return blPoint2d<blNumberType>(0,0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to return a point
// whose components are fractional
// inverses of the original point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType> getPointWithFractionalInvertedElements(const blPoint2d<blNumberType>& p)
{
    return blPoint2d<blNumberType>(blNumberType(1)/p.x(),blNumberType(1)/p.y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a point to
// an output stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,
                                const blPoint2d<blNumberType>& p)
{
    // We simply output the x and y
    // components with a space
    // separating them

    os << p.x() << " " << p.y();

    return os;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// input a point from
// an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::istream& operator>>(std::istream& is,
                                blPoint2d<blNumberType>& p)
{
    if(!(is >> p.x()))
    {
        // Error -- Cound not read
        //          the x value

        return is;
    }

    if(!(is >> p.y()))
    {
        // Error -- Cound not read
        //          the y value

        return is;
    }

    return is;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to return a point
// with the minimum or maximum values
// of each component when comparing
// multiple points
//-------------------------------------------------------------------
template<typename blNumberType>
inline void min(const blPoint2d<blNumberType>& p1,
                const blPoint2d<blNumberType>& p2,
                blPoint2d<blNumberType>& minP)
{
    minP.x = std::min(p1.x(),p2.x());
    minP.y = std::min(p1.y(),p2.y());
}


template<typename blNumberType>
inline void max(const blPoint2d<blNumberType>& p1,
                const blPoint2d<blNumberType>& p2,
                blPoint2d<blNumberType>& maxP)
{
    maxP.x = std::max(p1.x(),p2.x());
    maxP.y = std::max(p1.y(),p2.y());
}


template<typename blNumberType>
inline blPoint2d<blNumberType> min(const blPoint2d<blNumberType>& p1,
                                   const blPoint2d<blNumberType>& p2)
{
    blPoint2d<blNumberType> minP;

    blMathAPI::min(p1,p2,minP);

    return minP;
}


template<typename blNumberType>
inline blPoint2d<blNumberType> max(const blPoint2d<blNumberType>& p1,
                                   const blPoint2d<blNumberType>& p2)
{
    blPoint2d<blNumberType> maxP;

    blMathAPI::max(p1,p2,maxP);

    return maxP;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// convert a generic
// string to a point
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blPoint2d<blNumberType>& convertedNumber,
                                                  const int& numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // We expect the
    // following format:
    // P = x y

    blStringIteratorType newStringPosition;

    // First we try to
    // get the x value

    newStringPosition = convertStringToNumber(beginIter,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.x(),
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the y value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.y(),
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_POINT2DOPERATIONS_HPP
