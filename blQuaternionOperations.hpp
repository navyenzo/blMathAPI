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
// Functions used to go from euler angles
// to a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>& eulerAnglesToQuaternion(const blNumberType& roll,
                                                           const blNumberType& pitch,
                                                           const blNumberType& yaw,
                                                           blQuaternion<blNumberType>& qtn)
{
    blNumberType c1 = std::cos(roll/static_cast<blNumberType>(2.0));
    blNumberType c2 = std::cos(pitch/static_cast<blNumberType>(2.0));
    blNumberType c3 = std::cos(yaw/static_cast<blNumberType>(2.0));

    blNumberType s1 = std::sin(roll/static_cast<blNumberType>(2.0));
    blNumberType s2 = std::sin(pitch/static_cast<blNumberType>(2.0));
    blNumberType s3 = std::sin(yaw/static_cast<blNumberType>(2.0));

    qtn.w() = c1*c2*c3 + s1*s2*s3;
    qtn.xyz().x() = s1*c2*c3 - c1*s2*s3;
    qtn.xyz().y() = c1*s2*c3 + s1*c2*s3;
    qtn.xyz().z() = c1*c2*s3 - s1*s2*c3;

    normalize(qtn);

    return qtn;
}



template<typename blNumberType>
inline blQuaternion<blNumberType>& eulerAnglesToQuaternion(const blVector3d<blNumberType>& eulerAngles,
                                                           blQuaternion<blNumberType>& qtn)
{
    return eulerAnglesToQuaternion(eulerAngles.x(),
                                   eulerAngles.y(),
                                   eulerAngles.z(),
                                   qtn);
}



template<typename blNumberType>
inline blQuaternion<blNumberType> eulerAnglesToQuaternion(const blNumberType& roll,
                                                          const blNumberType& pitch,
                                                          const blNumberType& yaw)
{
    blQuaternion<blNumberType> qtn;

    return eulerAnglesToQuaternion(roll,
                                   pitch,
                                   yaw,
                                   qtn);
}



template<typename blNumberType>
inline blQuaternion<blNumberType> eulerAnglesToQuaternion(const blVector3d<blNumberType>& eulerAngles)
{
    blQuaternion<blNumberType> qtn;

    return eulerAnglesToQuaternion(eulerAngles.x(),
                                   eulerAngles.y(),
                                   eulerAngles.z(),
                                   qtn);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to go from a quaternion
// to euler angles
//-------------------------------------------------------------------
template<typename blNumberType>
inline void quaternionToEulerAngles(const blQuaternion<blNumberType>& qtn,
                                    blNumberType& roll,
                                    blNumberType& pitch,
                                    blNumberType& yaw)
{
    roll = std::atan2(2.0*(qtn.w()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().z()),
                      1.0 - 2.0*(qtn.xyz().x()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().y()));

    pitch = std::asin(2.0*(qtn.w()*qtn.xyz().y() - qtn.xyz().z()*qtn.xyz().x()));

    yaw = std::atan2(2.0*(qtn.w()*qtn.xyz().z() + qtn.xyz().x()*qtn.xyz().y()),
                     1.0 - 2.0*(qtn.xyz().y()*qtn.xyz().y() + qtn.xyz().z()*qtn.xyz().z()));
}



template<typename blNumberType>
inline void quaternionToEulerAngles(const blQuaternion<blNumberType>& qtn,
                                    blVector3d<blNumberType>& angles)
{
    quaternionToEulerAngles(qtn,angles.x(),angles.y(),angles.z());
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
inline blQuaternion<blNumberType>& axisAngleToQuaternion(const blNumberType& x,
                                                         const blNumberType& y,
                                                         const blNumberType& z,
                                                         const blNumberType& angle,
                                                         blQuaternion<blNumberType>& qtn)
{
    blMathAPI::blVector3d<blNumberType> axis = blMathAPI::blVector3d(x,y,z);

    return axisAngleToQuaternion(axis,angle,qtn);
}



template<typename blNumberType>
inline blQuaternion<blNumberType>& axisAngleToQuaternion(const blVector3d<blNumberType>& axis,
                                                         const blNumberType& angle,
                                                         blQuaternion<blNumberType>& qtn)
{
    auto normalizedAxis = getNormalized(axis);

    qtn.w() = std::cos(angle/blNumberType(2));

    blNumberType scalar = std::sin(angle/blNumberType(2));

    qtn.xyz() = normalizedAxis * scalar;

    normalize(qtn);

    return qtn;
}



template<typename blNumberType>
inline blQuaternion<blNumberType> axisAngleToQuaternion(const blVector3d<blNumberType>& axis,
                                                        const blNumberType& angle)
{
    blQuaternion<blNumberType> qtn;

    return axisAngleToQuaternion(axis,angle,qtn);
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
    if(qtn.w() == static_cast<blNumberType>(1))
    {
        // In this case we have
        // no rotation

        angle = static_cast<blNumberType>(0);

        axis = qtn.xyz();
    }
    else
    {
        auto normalizedQtn = getNormalized(qtn);

        angle = static_cast<blNumberType>(2) * std::acos(normalizedQtn.w());

        blNumberType s = std::sqrt(static_cast<blNumberType>(1) - normalizedQtn.w()*normalizedQtn.w());

        axis = normalizedQtn.xyz();

        if(s > 0.0001)
        {
            // To avoid division by zero, if s is close
            // to zero then the direction of the axis is
            // not important

            axis /= s;
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to go from a quaternion to a rotation matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>& quaternionToRotationMatrix(const blQuaternion<blNumberType>& qtn,
                                                            blMatrix3d<blNumberType>& matrix)
{
    blNumberType sqw = qtn.w()*qtn.w();
    blNumberType sqx = qtn.xyz().x()*qtn.xyz().x();
    blNumberType sqy = qtn.xyz().y()*qtn.xyz().y();
    blNumberType sqz = qtn.xyz().z()*qtn.xyz().z();

    blNumberType invs = static_cast<blNumberType>(1) / (sqw + sqx + sqy + sqz);

    matrix(0,0) = ( sqx - sqy - sqz + sqw) * invs;
    matrix(1,1) = (-sqx + sqy - sqz + sqw) * invs;
    matrix(2,2) = (-sqx - sqy + sqz + sqw) * invs;



    blNumberType tmp1 = qtn.xyz().x() * qtn.xyz().y();
    blNumberType tmp2 = qtn.xyz().z() * qtn.w();

    matrix(1,0) = static_cast<blNumberType>(2) * (tmp1 + tmp2) * invs;
    matrix(0,1) = static_cast<blNumberType>(2) * (tmp1 - tmp2) * invs;



    tmp1 = qtn.xyz().x() * qtn.xyz().z();
    tmp2 = qtn.xyz().y() * qtn.w();

    matrix(2,0) = static_cast<blNumberType>(2) * (tmp1 - tmp2) * invs;
    matrix(0,2) = static_cast<blNumberType>(2) * (tmp1 + tmp2) * invs;



    tmp1 = qtn.xyz().y() * qtn.xyz().z();
    tmp2 = qtn.xyz().z() * qtn.w();

    matrix(2,1) = static_cast<blNumberType>(2) * (tmp1 + tmp2) * invs;
    matrix(1,2) = static_cast<blNumberType>(2) * (tmp1 - tmp2) * invs;



    return matrix;
}



template<typename blNumberType>
inline blMatrix3d<blNumberType>& quaternionToRotationMatrix(const blQuaternion<blNumberType>& qtn)
{
    blMatrix3d<blNumberType> matrix;

    return quaternionToRotationMatrix(qtn,matrix);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to go from a rotation matrix to a quaternion
//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>& rotationMatrixToQuaternion(const blMatrix3d<blNumberType>& matrix,
                                                              blQuaternion<blNumberType>& qtn)
{
    blNumberType k = 0;

    auto matrixTrace = trace(matrix);



    if(matrixTrace > static_cast<blNumberType>(0))
    {
        k = static_cast<blNumberType>(0.5) / std::sqrt(static_cast<blNumberType>(1) + matrixTrace);

        qtn.w() = static_cast<blNumberType>(0.25) / k;
        qtn.xyz().x() = k * (matrix(1,2) - matrix(2,1));
        qtn.xyz().y() = k * (matrix(2,0) - matrix(0,2));
        qtn.xyz().z() = k * (matrix(0,1) - matrix(1,0));
    }
    else if((matrix(0,0) > matrix(1,1)) && (matrix(0,0) > matrix(2,2)))
    {
        k = static_cast<blNumberType>(0.5) / std::sqrt(static_cast<blNumberType>(1) + matrix(0,0) - matrix(1,1) - matrix(2,2));

        qtn.w() = k * (matrix(1,2) - matrix(2,1));
        qtn.xyz().x() = static_cast<blNumberType>(0.25) / k;
        qtn.xyz().y() = k * (matrix(1,0) + matrix(0,1));
        qtn.xyz().z() = k * (matrix(2,0) + matrix(0,2));
    }
    else if(matrix(1,1) > matrix(2,2))
    {
        k = static_cast<blNumberType>(0.5) / std::sqrt(static_cast<blNumberType>(1) + matrix(1,1) - matrix(0,0) - matrix(2,2));

        qtn.w() = k * (matrix(2,0) - matrix(0,2));
        qtn.xyz().x() = k * (matrix(1,0) + matrix(0,1));
        qtn.xyz().y() = static_cast<blNumberType>(0.25) / k;
        qtn.xyz().z() = k * (matrix(2,0) - matrix(0,2));
    }
    else
    {
        k = static_cast<blNumberType>(0.5) / std::sqrt(static_cast<blNumberType>(1) + matrix(2,2) - matrix(0,0) - matrix(1,1));

        qtn.w() = k * (matrix(0,1) - matrix(1,0));
        qtn.xyz().x() = k * (matrix(2,0) + matrix(0,2));
        qtn.xyz().y() = k * (matrix(2,1) + matrix(1,2));
        qtn.xyz().z() = static_cast<blNumberType>(0.25) / k;
    }



    normalize(qtn);



    return qtn;
}



template<typename blNumberType>
inline blQuaternion<blNumberType> rotationMatrixToQuaternion(const blMatrix3d<blNumberType>& matrix)
{
    blQuaternion<blNumberType> qtn;

    return rotationMatrixToQuaternion(matrix,qtn);
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
