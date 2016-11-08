#ifndef BL_VECTOR3DOPERATIONS_HPP
#define BL_VECTOR3DOPERATIONS_HPP


//-------------------------------------------------------------------
// FILE:            blVector3dOperations.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Useful functions for handling vectors
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
// Calculate the L1-norm of a vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm1(const blVector3d<blDataType>& v)
{
    return ( std::abs(v.x()) + std::abs(v.y()) + std::abs(v.z()) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L2-norm of a vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm2(const blVector3d<blDataType>& v)
{
    return std::sqrt( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Linf-norm of a vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normInf(const blVector3d<blDataType>& v)
{
    auto tempMax = std::max(v.x(),v.y());

    return std::max(tempMax,v.z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Lp-norm of a vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normP(const blVector3d<blDataType>& v,const int& p)
{
    return std::pow(std::pow(v.x(),p) + std::pow(v.y(),p)+ std::pow(v.z(),p),
                    1.0 / double(p));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to normalize a vector or to get
// a normalized vector from a given vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& normalize(blVector3d<blDataType>& v)
{
    v /= norm2(v);

    return v;
}


template<typename blDataType>
inline blVector3d<blDataType> getNormalized(const blVector3d<blDataType>& v)
{
    return (v/norm2(v));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to get a vector perpendicular
// to a given vector such that the dot product
// would give zero
//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> getPerpendicularUnitVector(const blVector3d<blDataType>& v)
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
            return blVector3d<blDataType>(0,1,0);
        else
        {
            if(v.z() == 0)
            {
                return blVector3d<blDataType>(0,0,1);
            }
            else
            {
                blVector3d<blDataType> vector( 1, 1, -(v.x() + v.y())/v.z() );

                normalize(vector);

                return vector;
            }
        }
    }
    else if(v.y() != 0 || v.z() != 0)
    {
        return blVector3d<blDataType>(1,0,0);
    }

    // The vector was a zero
    // vector, therefore any
    // vector would be perpendicular,
    // thus we are just going
    // to return the zero vector

    return blVector3d<blDataType>(0,0,0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to return a vector
// whose components are fractional
// inverses of the original vector
//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> getVectorWithFractionalInvertedElements(const blVector3d<blDataType>& v)
{
    return blVector3d<blDataType>(blDataType(1)/v.x(),blDataType(1)/v.y(),blDataType(1)/v.z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to take the cross
// product of two vectors
//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> crossProduct(const blVector3d<blDataType>& v1,
                                           const blVector3d<blDataType>& v2)
{
    return blVector3d<blDataType>(v1.y()*v2.z() - v1.z()*v2.y(),
                                  -v1.x()*v2.z() + v1.z()*v2.x(),
                                  v1.x()*v2.y() - v1.y()*v2.x());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a vector to
// an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blVector3d<blDataType>& v)
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
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blVector3d<blDataType>& v)
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
template<typename blDataType>
inline void min(const blVector3d<blDataType>& v1,
                const blVector3d<blDataType>& v2,
                blVector3d<blDataType>& minV)
{
    minV.x = std::min(v1.x(),v2.x());
    minV.y = std::min(v1.y(),v2.y());
    minV.z = std::min(v1.z(),v2.z());
}


template<typename blDataType>
inline void max(const blVector3d<blDataType>& v1,
                const blVector3d<blDataType>& v2,
                blVector3d<blDataType>& maxV)
{
    maxV.x = std::max(v1.x(),v2.x());
    maxV.y = std::max(v1.y(),v2.y());
    maxV.z = std::max(v1.z(),v2.z());
}


template<typename blDataType>
inline blVector3d<blDataType> min(const blVector3d<blDataType>& v1,
                                  const blVector3d<blDataType>& v2)
{
    blVector3d<blDataType> minV;

    min(v1,v2,minV);

    return minV;
}


template<typename blDataType>
inline blVector3d<blDataType> max(const blVector3d<blDataType>& v1,
                                  const blVector3d<blDataType>& v2)
{
    blVector3d<blDataType> maxV;

    max(v1,v2,maxV);

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
         typename blDataType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blVector3d<blDataType>& convertedNumber,
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


#endif // BL_VECTOR3DOPERATIONS_HPP
