#ifndef BL_VECTOR3DOPERATIONS_HPP
#define BL_VECTOR3DOPERATIONS_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Useful functions for handling 3d vector
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
#include "blVector3d.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the L1-norm of a vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm1(const blVector3d<blNumberType>& v)
{
    return ( blMathAPI::abs(v.x()) + blMathAPI::abs(v.y()) + blMathAPI::abs(v.z()) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the L2-norm of a vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm2(const blVector3d<blNumberType>& v)
{
    return std::sqrt( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the Linf-norm of a vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normInf(const blVector3d<blNumberType>& v)
{
    auto tempMax = std::max(v.x(),v.y());

    return std::max(tempMax,v.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the Lp-norm of a vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normP(const blVector3d<blNumberType>& v,const int& p)
{
    return blMathAPI::power(blMathAPI::power(v.x(),p) + blMathAPI::power(v.y(),p)+ blMathAPI::power(v.z(),p),
                            1.0 / double(p));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to normalize a vector or to get
// a normalized vector from a given vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& normalize(blVector3d<blNumberType>& v)
{
    v /= norm2(v);

    return v;
}


template<typename blNumberType>
inline blVector3d<blNumberType> getNormalized(const blVector3d<blNumberType>& v)
{
    return (v/norm2(v));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get a vector perpendicular
// to a given vector such that the dot product
// would give zero
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType> getPerpendicularUnitVector(const blVector3d<blNumberType>& v)
{
    // Find a component of this
    // vector that is non zero
    // and if unsuccessfull,
    // just return the zero vector
    //
    // P1*P2 = x1*x2 + y1*y2 + z1*z2 = 0

    if(v.x() != 0)
    {
        if(v.y() == 0)
            return blVector3d<blNumberType>(0,1,0);
        else
        {
            if(v.z() == 0)
            {
                return blVector3d<blNumberType>(0,0,1);
            }
            else
            {
                blVector3d<blNumberType> vector( 1, 1, -(v.x() + v.y())/v.z() );

                normalize(vector);

                return vector;
            }
        }
    }
    else if(v.y() != 0 || v.z() != 0)
    {
        return blVector3d<blNumberType>(1,0,0);
    }

    // The vector was a zero
    // vector, therefore any
    // vector would be perpendicular,
    // thus we are just going
    // to return the zero vector

    return blVector3d<blNumberType>(0,0,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return a vector
// whose components are fractional
// inverses of the original vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType> getVectorWithFractionalInvertedElements(const blVector3d<blNumberType>& v)
{
    return blVector3d<blNumberType>(blNumberType(1)/v.x(),blNumberType(1)/v.y(),blNumberType(1)/v.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to take the cross
// product of two vectors
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType> crossProduct(const blVector3d<blNumberType>& v1,
                                             const blVector3d<blNumberType>& v2)
{
    return blVector3d<blNumberType>(v1.y()*v2.z() - v1.z()*v2.y(),
                                  -v1.x()*v2.z() + v1.z()*v2.x(),
                                  v1.x()*v2.y() - v1.y()*v2.x());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// output a vector to
// an output stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,
                                const blVector3d<blNumberType>& v)
{
    // We simply output the x and y
    // components with a space
    // separating them

    os << v.x() << " " << v.y() << " " << v.z();

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
                                blVector3d<blNumberType>& v)
{
    if(!(is >> v.x()))
    {
        // Error -- Cound not read
        //          the x value

        return is;
    }

    if(!(is >> v.y()))
    {
        // Error -- Cound not read
        //          the y value

        return is;
    }

    if(!(is >> v.z()))
    {
        // Error -- Cound not read
        //          the z value

        return is;
    }

    return is;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to return a vector
// with the minimum or maximum values
// of each component when comparing
// multiple vector
//-------------------------------------------------------------------
template<typename blNumberType>
inline void min(const blVector3d<blNumberType>& v1,
                const blVector3d<blNumberType>& v2,
                blVector3d<blNumberType>& minV)
{
    minV.x = std::min(v1.x(),v2.x());
    minV.y = std::min(v1.y(),v2.y());
    minV.z = std::min(v1.z(),v2.z());
}


template<typename blNumberType>
inline void max(const blVector3d<blNumberType>& v1,
                const blVector3d<blNumberType>& v2,
                blVector3d<blNumberType>& maxV)
{
    maxV.x = std::max(v1.x(),v2.x());
    maxV.y = std::max(v1.y(),v2.y());
    maxV.z = std::max(v1.z(),v2.z());
}


template<typename blNumberType>
inline blVector3d<blNumberType> min(const blVector3d<blNumberType>& v1,
                                    const blVector3d<blNumberType>& v2)
{
    blVector3d<blNumberType> minV;

    blMathAPI::min(v1,v2,minV);

    return minV;
}


template<typename blNumberType>
inline blVector3d<blNumberType> max(const blVector3d<blNumberType>& v1,
                                    const blVector3d<blNumberType>& v2)
{
    blVector3d<blNumberType> maxV;

    blMathAPI::max(v1,v2,maxV);

    return maxV;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// convert a generic
// string to a vector
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blVector3d<blNumberType>& convertedNumber,
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

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the y value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.z(),
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_VECTOR3DOPERATIONS_HPP
