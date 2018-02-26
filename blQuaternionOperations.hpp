#ifndef BL_QUATERNIONOPERATIONS_HPP
#define BL_QUATERNIONOPERATIONS_HPP


//-------------------------------------------------------------------
// FILE:            blQuaternionOperantions.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Useful functions for handling quaternions
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
// Calculate the L1-norm of a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm1(const blQuaternion<blDataType>& q)
{
    return ( std::abs(q.w()) + std::abs(q.xyz().x()) + std::abs(q.xyz().y()) + std::abs(q.xyz().z()) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the L2-norm of a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType norm2(const blQuaternion<blDataType>& q)
{
    return std::sqrt( q.w()*q.w() + q.xyz().x()*q.xyz().x() + q.xyz().y()*q.xyz().y() + q.xyz().z()*q.xyz().z() );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Linf-norm of a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normInf(const blQuaternion<blDataType>& q)
{
    auto tempMax = std::max(q.w(),q.xyz().x());
    tempMax = std::max(tempMax,q.xyz().y());

    return std::max(tempMax,q.xyz().z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Calculate the Lp-norm of a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType normP(const blQuaternion<blDataType>& q,const int& p)
{
    return std::pow( std::pow(q.w(),p) + std::pow(q.xyz().x(),p) + std::pow(q.xyz().y(),p)+ std::pow(q.xyz().z(),p),
                    1.0 / double(p) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to normalize a quaternion or to get
// a normalized quaternion from a given quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>& normalize(blQuaternion<blDataType>& q)
{
    q /= norm2(q);

    return q;
}


template<typename blDataType>
inline blQuaternion<blDataType> getNormalized(const blQuaternion<blDataType>& q)
{
    return (q/norm2(q));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to get the complex
// conjugate of a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> getConjugate(const blQuaternion<blDataType>& qtn)
{
    return blQuaternion<blDataType>(qtn.w(),-qtn.xyz());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to go from euler angles
// to a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline void eulerAnglesToQuaternion(const blVector3d<blDataType>& angles,
                                    blQuaternion<blDataType>& qtn)
{
    blQuaternion<blDataType> xQtn(std::cos(angles.x()/blDataType(2)),
                                  blVector3d<blDataType>(std::sin(angles.x()/blDataType(2)),
                                                         0,
                                                         0));

    blQuaternion<blDataType> yQtn(std::cos(angles.y()/blDataType(2)),
                                  blVector3d<blDataType>(0,
                                                         std::sin(angles.y()/blDataType(2)),
                                                         0));

    blQuaternion<blDataType> zQtn(std::cos(angles.z()/blDataType(2)),
                                  blVector3d<blDataType>(0,
                                                         0,
                                                         std::sin(angles.z()/blDataType(2))));

    qtn = xQtn*yQtn*zQtn;
}


template<typename blDataType>
inline blQuaternion<blDataType> eulerAnglesToQuaternion(const blVector3d<blDataType>& angles)
{
    blQuaternion<blDataType> qtn;

    eulerAnglesToQuaternion(angles,qtn);

    return qtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to go from a quaternion
// to euler angles
//-------------------------------------------------------------------
template<typename blDataType>
inline void quaternionToEulerAngles(const blQuaternion<blDataType>& qtn,
                                    blVector3d<blDataType>& angles)
{
    angles.x() = std::atan2(2.0*(qtn.w()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().z()),
                            1.0 - 2.0*(qtn.xyz().x()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().y()));

    angles.y() = std::asin(2.0*(qtn.w()*qtn.xyz().y() - qtn.xyz().z()*qtn.xyz().x()));

    angles.z() = std::atan2(2.0*(qtn.w()*qtn.xyz().z() + qtn.xyz().x()*qtn.xyz().y()),
                            1.0 - 2.0*(qtn.xyz().y()*qtn.xyz().y() + qtn.xyz().z()*qtn.xyz().z()));
}


template<typename blDataType>
inline blVector3d<blDataType> quaternionToEulerAngles(const blQuaternion<blDataType>& qtn)
{
    blVector3d<blDataType> angles;

    quaternionToEulerAngles(qtn,angles);

    return angles;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to go from axis/angle
// to a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline void axisAngleToQuaternion(const blVector3d<blDataType>& axis,
                                  const blDataType& angle,
                                  blQuaternion<blDataType>& qtn)
{
    auto normalizedAxis = getNormalized(axis);

    qtn.w() = std::cos(angle/blDataType(2));

    blDataType scalar = std::sin(angle/blDataType(2));

    qtn.xyz() = axis * scalar;
}


template<typename blDataType>
inline blQuaternion<blDataType> axisAngleToQuaternion(const blVector3d<blDataType>& axis,
                                                      const blDataType& angle)
{
    blQuaternion<blDataType> qtn;

    axisAngleToQuaternion(axis,angle,qtn);

    return qtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to go from a quaternion
// to axis/angle
//-------------------------------------------------------------------
template<typename blDataType>
inline void quaternionToAxisAngle(const blQuaternion<blDataType>& qtn,
                                  blVector3d<blDataType>& axis,
                                  blDataType& angle)
{
    if(qtn.w() == blDataType(1))
    {
        // In this case we have
        // no rotation

        angle = blDataType(0);

        axis = qtn.xyz();
    }
    else
    {
        // Calculate the magnitude

        auto mag = norm1(qtn.xyz());

        if(mag == blDataType(0))
        {
            // Magnitude is zero so
            // we set default values

            angle = 0;

            axis = blVector3d<blDataType>(1,0,0);
        }
        else
        {
            angle = blDataType(2) * std::acos(qtn.w());

            axis = qtn.xyz() / mag;
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to rotate a vector with
// a quaternion
//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& rotateVector(const blQuaternion<blDataType>& rotQtn,
                                           blVector3d<blDataType>& vectorToRotate)
{
    blQuaternion<blDataType> vectorQtn(0,vectorToRotate);

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
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,const blQuaternion<blDataType>& qtn)
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
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blQuaternion<blDataType>& qtn)
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
         typename blDataType>
inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                    const blStringIteratorType& endIter,
                                                    const blCharacterType& decimalPointDelimiter,
                                                    blMathAPI::blQuaternion<blDataType>& convertedNumber,
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


#endif // BL_QUATERNIONOPERATIONS_HPP
