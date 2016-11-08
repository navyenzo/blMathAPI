#ifndef BL_POINT2DOPERATIONS_HPP
#define BL_POINT2DOPERATIONS_HPP


//-------------------------------------------------------------------
// FILE:            blPoint2dOperations.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Useful functions for handling points
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
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L1-norm of a point
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm1(const blPoint2d<blDataType>& p)
{
    return ( std::abs(p.x()) + std::abs(p.y()) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L2-norm of a point
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm2(const blPoint2d<blDataType>& p)
{
    return std::sqrt( p.x()*p.x() + p.y()*p.y() );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Linf-norm of a point
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normInf(const blPoint2d<blDataType>& p)
{
    return std::max(p.x(),p.y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Lp-norm of a point
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normP(const blPoint2d<blDataType>& point,const int& p)
{
    return std::pow(std::pow(point.x(),p) + std::pow(point.y(),p),
                    1.0 / double(p));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to normalize a point or to get
// a normalized point from a given point
//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& normalize(blPoint2d<blDataType>& p)
{
    p /= norm2(p);

    return p;
}


template<typename blDataType>
inline blPoint2d<blDataType> getNormalized(const blPoint2d<blDataType>& p)
{
    return (p/norm2(p));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to get a point perpendicular
// to a given point such that the dot product
// would give zero
//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> getPerpendicularUnitPoint(const blPoint2d<blDataType>& p)
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
            return blPoint2d<blDataType>(0,1);
        else
        {
            blPoint2d<blDataType> point(1,-p.x()/p.y());

            normalize(point);

            return point;
        }
    }
    else if(p.y() != 0)
    {
        return blPoint2d<blDataType>(1,0);
    }

    // The Point was a zero Point,
    // therefore any Point would
    // be perpendicular, thus we
    // are just going to return
    // the zero Point

    return blPoint2d<blDataType>(0,0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to return a point
// whose components are fractional
// inverses of the original point
//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> getPointWithFractionalInvertedElements(const blPoint2d<blDataType>& p)
{
    return blPoint2d<blDataType>(blDataType(1)/p.x(),blDataType(1)/p.y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a point to
// an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blPoint2d<blDataType>& p)
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
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blPoint2d<blDataType>& p)
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
template<typename blDataType>
inline void min(const blPoint2d<blDataType>& p1,
                const blPoint2d<blDataType>& p2,
                blPoint2d<blDataType>& minP)
{
    minP.x = std::min(p1.x(),p2.x());
    minP.y = std::min(p1.y(),p2.y());
}


template<typename blDataType>
inline void max(const blPoint2d<blDataType>& p1,
                const blPoint2d<blDataType>& p2,
                blPoint2d<blDataType>& maxP)
{
    maxP.x = std::max(p1.x(),p2.x());
    maxP.y = std::max(p1.y(),p2.y());
}


template<typename blDataType>
inline blPoint2d<blDataType> min(const blPoint2d<blDataType>& p1,
                                 const blPoint2d<blDataType>& p2)
{
    blPoint2d<blDataType> minP;

    min(p1,p2,minP);

    return minP;
}


template<typename blDataType>
inline blPoint2d<blDataType> max(const blPoint2d<blDataType>& p1,
                                 const blPoint2d<blDataType>& p2)
{
    blPoint2d<blDataType> maxP;

    max(p1,p2,maxP);

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
         typename blDataType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blPoint2d<blDataType>& convertedNumber,
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


#endif // BL_POINT2DOPERATIONS_HPP
