#ifndef BL_QUATERNIONOPERATIONS_HPP
#define BL_QUATERNIONOPERATIONS_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Useful functions for handling quaternions
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
#include "blQuaternion.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the L1-norm of a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm1(const blQuaternion<blNumberType>& q)
{
    return ( blMathAPI::abs(q.w()) + blMathAPI::abs(q.xyz().x()) + blMathAPI::abs(q.xyz().y()) + blMathAPI::abs(q.xyz().z()) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the L2-norm of a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType norm2(const blQuaternion<blNumberType>& q)
{
    return std::sqrt( q.w()*q.w() + q.xyz().x()*q.xyz().x() + q.xyz().y()*q.xyz().y() + q.xyz().z()*q.xyz().z() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the Linf-norm of a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normInf(const blQuaternion<blNumberType>& q)
{
    auto tempMax = std::max(q.w(),q.xyz().x());
    tempMax = std::max(tempMax,q.xyz().y());

    return std::max(tempMax,q.xyz().z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Calculate the Lp-norm of a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType normP(const blQuaternion<blNumberType>& q,const int& p)
{
    return blMathAPI::power( blMathAPI::power(q.w(),p) + blMathAPI::power(q.xyz().x(),p) + blMathAPI::power(q.xyz().y(),p)+ blMathAPI::power(q.xyz().z(),p),
                             1.0 / double(p) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to normalize a quaternion or to get
// a normalized quaternion from a given quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>& normalize(blQuaternion<blNumberType>& q)
{
    q /= norm2(q);

    return q;
}


template<typename blNumberType>
inline blQuaternion<blNumberType> getNormalized(const blQuaternion<blNumberType>& q)
{
    return (q/norm2(q));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the complex
// conjugate of a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> getConjugate(const blQuaternion<blNumberType>& qtn)
{
    return blQuaternion<blNumberType>(qtn.w(),-qtn.xyz());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to go from euler angles
// to a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline void eulerAnglesToQuaternion(const blVector3d<blNumberType>& angles,
                                    blQuaternion<blNumberType>& qtn)
{
    blQuaternion<blNumberType> xQtn(std::cos(angles.x()/blNumberType(2)),
                                    blVector3d<blNumberType>(std::sin(angles.x()/blNumberType(2)),
                                                             0,
                                                             0));

    blQuaternion<blNumberType> yQtn(std::cos(angles.y()/blNumberType(2)),
                                    blVector3d<blNumberType>(0,
                                                             std::sin(angles.y()/blNumberType(2)),
                                                             0));

    blQuaternion<blNumberType> zQtn(std::cos(angles.z()/blNumberType(2)),
                                    blVector3d<blNumberType>(0,
                                                             0,
                                                             std::sin(angles.z()/blNumberType(2))));

    qtn = xQtn*yQtn*zQtn;
}



template<typename blNumberType>
inline blQuaternion<blNumberType> eulerAnglesToQuaternion(const blVector3d<blNumberType>& angles)
{
    blQuaternion<blNumberType> qtn;

    eulerAnglesToQuaternion(angles,qtn);

    return qtn;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to go from a quaternion
// to euler angles
//-------------------------------------------------------------------
template<typename blNumberType>
inline void quaternionToEulerAngles(const blQuaternion<blNumberType>& qtn,
                                    blVector3d<blNumberType>& angles)
{
    angles.x() = std::atan2(2.0*(qtn.w()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().z()),
                            1.0 - 2.0*(qtn.xyz().x()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().y()));

    angles.y() = std::asin(2.0*(qtn.w()*qtn.xyz().y() - qtn.xyz().z()*qtn.xyz().x()));

    angles.z() = std::atan2(2.0*(qtn.w()*qtn.xyz().z() + qtn.xyz().x()*qtn.xyz().y()),
                            1.0 - 2.0*(qtn.xyz().y()*qtn.xyz().y() + qtn.xyz().z()*qtn.xyz().z()));
}


template<typename blNumberType>
inline blVector3d<blNumberType> quaternionToEulerAngles(const blQuaternion<blNumberType>& qtn)
{
    blVector3d<blNumberType> angles;

    quaternionToEulerAngles(qtn,angles);

    return angles;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to go from axis/angle
// to a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline void axisAngleToQuaternion(const blVector3d<blNumberType>& axis,
                                  const blNumberType& angle,
                                  blQuaternion<blNumberType>& qtn)
{
    auto normalizedAxis = getNormalized(axis);

    qtn.w() = std::cos(angle/blNumberType(2));

    blNumberType scalar = std::sin(angle/blNumberType(2));

    qtn.xyz() = axis * scalar;
}


template<typename blNumberType>
inline blQuaternion<blNumberType> axisAngleToQuaternion(const blVector3d<blNumberType>& axis,
                                                      const blNumberType& angle)
{
    blQuaternion<blNumberType> qtn;

    axisAngleToQuaternion(axis,angle,qtn);

    return qtn;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to go from a quaternion
// to axis/angle
//-------------------------------------------------------------------
template<typename blNumberType>
inline void quaternionToAxisAngle(const blQuaternion<blNumberType>& qtn,
                                  blVector3d<blNumberType>& axis,
                                  blNumberType& angle)
{
    if(qtn.w() == blNumberType(1))
    {
        // In this case we have
        // no rotation

        angle = blNumberType(0);

        axis = qtn.xyz();
    }
    else
    {
        // Calculate the magnitude

        auto mag = norm1(qtn.xyz());

        if(mag == blNumberType(0))
        {
            // Magnitude is zero so
            // we set default values

            angle = 0;

            axis = blVector3d<blNumberType>(1,0,0);
        }
        else
        {
            angle = blNumberType(2) * std::acos(qtn.w());

            axis = qtn.xyz() / mag;
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to rotate a vector with
// a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& rotateVector(const blQuaternion<blNumberType>& rotQtn,
                                           blVector3d<blNumberType>& vectorToRotate)
{
    blQuaternion<blNumberType> vectorQtn(0,vectorToRotate);

    auto rotQtnConj = getConjugate(rotQtn);

    auto unitRotatedVector = getNormalized( ( rotQtn * vectorQtn * rotQtnConj).xyz() );

    vectorToRotate = ( norm2(vectorToRotate) * unitRotatedVector );

    return vectorToRotate;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// output a quaternion
// to an output stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,const blQuaternion<blNumberType>& qtn)
{
    // We simply output the
    // components with a
    // space separating them

    os << qtn.w() << " " << qtn.xyz();
    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// input a quaternion
// from an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::istream& operator>>(std::istream& is,
                                blQuaternion<blNumberType>& qtn)
{
    if(!(is >> qtn.w()))
    {
        // Error -- Cound not read
        //          the w value
        return is;
    }

    if(!(is >> qtn.xyz()))
    {
        // Error -- Cound not read
        //          the xyz vector
        return is;
    }

    return is;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// convert a generic
// string to a quaternion
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>
inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blMathAPI::blQuaternion<blNumberType>& convertedNumber,
                                                  const int& numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // We expect the
    // following format:
    // Q = w blVector3d(x y z)

    blStringIteratorType newStringPosition;

    // First we try to
    // get the w value

    newStringPosition = convertStringToNumber(beginIter,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.w(),
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the xyz vector

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.xyz(),
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_QUATERNIONOPERATIONS_HPP
