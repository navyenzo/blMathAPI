#ifndef BL_QUATERNION_HPP
#define BL_QUATERNION_HPP


//-------------------------------------------------------------------
// FILE:            blQuaternion.hpp
// CLASS:           blQuaternion
// BASE CLASS:      None
//
// PURPOSE:         A simple quaternion class
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blVector3d -- To represent x,y,z comples values
//                  iostream -- To output to the console
//
// NOTES:           - This quaternion class has three functions
//                    defined in this file that can create a quaternion,
//                    multiply two quaternions and add two quaternions
//                    without normalizing
//                  - This quaternion class has an additional operator
//                    defined in this file that allows multiplying
//                    a scalar by a quaternion
//                  - This quaternion class has a couple of
//                    functions to rotate vectors using
//                    a quaternion
//
// DATE CREATED:    Mar/30/2008
// DATE UPDATED:
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
template<typename blDataType>
class blQuaternion
{
public: // Constructors and destructor

    // Default constructor

    blQuaternion();

    // Constructor using
    // euler angles

    blQuaternion(const blDataType& xAngle,
                 const blDataType& yAngle,
                 const blDataType& zAngle);

    // Constructor using
    // angle and axis

    blQuaternion(const blDataType& Angle,
                 const blDataType& Ax,
                 const blDataType& Ay,
                 const blDataType& Az);

    // Constructor using
    // quaternion components

    blQuaternion(const blDataType& w,const blVector3d<blDataType>& xyz);

    // Copy constructor a
    // from different type

    template<typename blDataType2>
    blQuaternion(const blQuaternion<blDataType2>& qtn);

    // Default destructor
    ~blQuaternion(void);

public: // Overloaded operators

    bool                                operator==(const blQuaternion<blDataType>& qtn)const;
    bool                                operator!=(const blQuaternion<blDataType>& qtn)const;

    blQuaternion<blDataType>            operator*(const blDataType& scalar)const;
    blQuaternion<blDataType>            operator*(const blQuaternion<blDataType>& qtn)const;

    blQuaternion<blDataType>            operator/(const blDataType& scalar)const;
    blQuaternion<blDataType>            operator/(const blQuaternion<blDataType>& qtn)const;
    blQuaternion<blDataType>            operator+(const blQuaternion<blDataType>& qtn)const;

public: // Public functions

    // Function used to get the
    // equivalent euler angles

    blVector3d<blDataType>              getEulerAngles()const;

    // Function used to get
    // the conjugate

    blQuaternion<blDataType>            getConjugate()const;

    // Function used to
    // normalize the quaternion

    void                                normalize();
    blQuaternion<blDataType>            getNormalized()const;

    // Function used to get the
    // magnitude of the quaternion

    blDataType                          getMagnitude()const;

    // Function used to rotate
    // a vector using this quaternion

    void                                rotateVector(blVector3d<blDataType>& vectorToRotate)const;
    void                                rotateVectorTheOppositeWay(blVector3d<blDataType>& vectorToRotate)const;

public: // Public Variables

    // Variables used to keep
    // track of the current
    // angle and axis being
    // represented by quaternion

    blDataType                          m_Angle;
    blDataType                          m_Ax;
    blDataType                          m_Ay;
    blDataType                          m_Az;

    // Variables representing the
    // quaternion's components

    blDataType                          m_w;
    blVector3d<blDataType>              m_xyz;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::blQuaternion(void)
{
    m_Angle = 0;
    m_Ax = 1;
    m_Ay = 0;
    m_Az = 0;
    m_w = 1;
    m_xyz = blVector3d<blDataType>(0,0,0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blQuaternion<blDataType>::blQuaternion(const blQuaternion<blDataType2>& qtn)
{
    // Copy angle/axis

    m_Angle = static_cast<blDataType>(qtn.m_Angle);
    m_Ax = static_cast<blDataType>(qtn.m_Ax);
    m_Ay = static_cast<blDataType>(qtn.m_Ay);
    m_Az = static_cast<blDataType>(qtn.m_Az);

    // Copy quaternion components

    m_w = static_cast<blDataType>(qtn.m_w);
    m_xyz = qtn.m_xyz;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::blQuaternion(const blDataType& Angle,
                                              const blDataType& Ax,
                                              const blDataType& Ay,
                                              const blDataType& Az)
{
    // Store the angle and axis

    m_Angle = Angle;
    m_Ax = Ax;
    m_Ay = Ay;
    m_Az = Az;

    // Calculate the magnitude
    // of the axis

    blDataType Magnitude = std::sqrt(m_Ax*m_Ax + m_Ay*m_Ay + m_Az*m_Az);

    if(Magnitude != 0 && m_Angle != 0)
    {
        // Normalize the axis

        m_Ax /= Magnitude;
        m_Ay /= Magnitude;
        m_Az /= Magnitude;

        // Find the quaternion
        // components

        blDataType s = sin(Angle/blDataType(2));
        m_w = cos(Angle/blDataType(2));
        m_xyz = blVector3d<blDataType>(s*m_Ax,s*m_Ay,s*m_Az);
    }
    else
    {
        // Set default values

        m_w = 1;
        m_xyz = blVector3d<blDataType>(0,0,0);

        m_Angle = 0;
        m_Ax = 1;
        m_Ay = 0;
        m_Az = 0;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::blQuaternion(const blDataType& xAngle,
                                              const blDataType& yAngle,
                                              const blDataType& zAngle)
{
    // Calculate the quaternion
    // for the angle around the
    // x-axis

    blQuaternion<blDataType> Qx = blQuaternion<blDataType>(std::cos(xAngle/blDataType(2)),blVector3d<blDataType>(std::sin(xAngle/blDataType(2)),0,0));

    // Calculate the quaternion
    // for the angle around the
    // y-axis

    blQuaternion<blDataType> Qy = blQuaternion<blDataType>(std::cos(yAngle/blDataType(2)),blVector3d<blDataType>(0,std::sin(yAngle/blDataType(2)),0));

    // Calculate the quaternion
    // for the angle around the
    // z-axis

    blQuaternion<blDataType> Qz = blQuaternion<blDataType>(std::cos(zAngle/blDataType(2)),blVector3d<blDataType>(0,0,std::sin(zAngle/blDataType(2))));

    // Calculate this quaternion

    (*this) = Qx*Qy*Qz;

    // Normalize this quaternion

    this->normalize();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::blQuaternion(const blDataType& w,
                                              const blVector3d<blDataType>& xyz)
{
    // Store the quaternion
    // components

    m_w = w;
    m_xyz = xyz;

    // Calculate the corresponding
    // angle and axis

    if(m_w == 1)
    {
        // In this case, we
        // have no rotation

        m_Angle = 0;
        m_Ax = m_xyz.x;
        m_Ay = m_xyz.y;
        m_Az = m_xyz.z;
    }
    else
    {
        // Calculate the magnitude
        // of the xyz vector

        blDataType VecMag = m_xyz.getMagnitude();

        if(VecMag == 0)
        {
            // Magnitude is zero so
            // we set the defaul values

            m_Angle = 0;
            m_Ax = 1;
            m_Ay = 0;
            m_Az = 0;
        }
        else
        {
            // Calculate the corresponding
            // angle and axis

            m_Angle = 2.0*acos(m_w);
            m_Ax = m_xyz.x/VecMag;
            m_Ay = m_xyz.y/VecMag;
            m_Az = m_xyz.z/VecMag;

            // Normalize this quaternion

            this->normalize();
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType blQuaternion<blDataType>::getMagnitude()const
{
    // Calculate the magnitude
    // by taking the square root
    // of the sum of its components

    blDataType Mag = std::sqrt(m_w*m_w + m_xyz.x*m_xyz.x + m_xyz.y*m_xyz.y + m_xyz.z*m_xyz.z);
    return Mag;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blQuaternion<blDataType>::rotateVector(blVector3d<blDataType>& vectorToRotate)const
{
    vectorToRotate = vectorToRotate.getMagnitude() *
                     (((*this) * blQuaternion<blDataType>(0,vectorToRotate) * getConjugate()).m_xyz).getNormalized();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blQuaternion<blDataType>::rotateVectorTheOppositeWay(blVector3d<blDataType>& vectorToRotate)const
{
    vectorToRotate = vectorToRotate.getMagnitude() *
                     ((getConjugate() * blQuaternion<blDataType>(0,vectorToRotate) * (*this)).m_xyz).getNormalized();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blQuaternion<blDataType>::normalize()
{
    // Calculate the magnitude

    blDataType Mag = this->getMagnitude();

    // If the magnitude is non zero,
    // then normalize the quaternion

    if(Mag != 0)
    {
        m_w /= Mag;
        m_xyz.x /= Mag;
        m_xyz.y /= Mag;
        m_xyz.z /= Mag;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::getNormalized()const
{
    // Copy this quaternion
    blQuaternion<blDataType> normalizedQtn(*this);

    // Normalize the copied
    // quaternion

    normalizedQtn.normalize();

    return normalizedQtn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::~blQuaternion(void)
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blQuaternion<blDataType>::operator==(const blQuaternion<blDataType>& qtn)const
{
    // Check if all the components
    // are equal

    if(m_w != qtn.m_w)
        return false;
    if(m_xyz != qtn.m_xyz)
        return false;

    // By now we know the
    // two quaternions are equal

    return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blQuaternion<blDataType>::operator!=(const blQuaternion<blDataType>& qtn)const
{
    // Check if any of the
    // components are not equal

    if(m_w != qtn.m_w)
        return true;
    if(m_xyz != qtn.m_xyz)
        return true;

    // By now we know the two
    // quaternions are equal

    return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> blQuaternion<blDataType>::getEulerAngles()const
{
    blDataType Phi = atan2(2.0*(m_w*m_xyz.x + m_xyz.y*m_xyz.z),
                           1.0 - 2.0*(m_xyz.x*m_xyz.x + m_xyz.y*m_xyz.y));

    blDataType Theta = asin(2.0*(m_w*m_xyz.y - m_xyz.z*m_xyz.x));

    blDataType Sci = atan2(2.0*(m_w*m_xyz.z + m_xyz.x*m_xyz.y),
                           1.0 - 2.0*(m_xyz.y*m_xyz.y + m_xyz.z*m_xyz.z));

    return blVector3d<blDataType>(Phi,Theta,Sci);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::getConjugate()const
{
    return blQuaternion<blDataType>(m_w,-m_xyz);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> CreateQtnWithoutNormalizing(const blDataType& w,
                                                            const blVector3d<blDataType> xyz)
{
    blQuaternion<blDataType> result;

    result.m_w = w;
    result.m_xyz = xyz;

    // Re-adjust the axis
    // angle because of
    // the normalization

    if(result.m_w == 1)
    {
        result.m_Angle = 0;
        result.m_Ax = result.m_xyz.x;
        result.m_Ay = result.m_xyz.y;
        result.m_Az = result.m_xyz.z;
    }
    else
    {
        blDataType VecMag = result.m_xyz.getMagnitude();

        if(VecMag == 0)
        {
            result.m_Angle = 0;
            result.m_Ax = 1;
            result.m_Ay = 0;
            result.m_Az = 0;
        }
        else
        {
            result.m_Angle = 2.0*acos(result.m_w);
            result.m_Ax = result.m_xyz.x/VecMag;
            result.m_Ay = result.m_xyz.y/VecMag;
            result.m_Az = result.m_xyz.z/VecMag;
        }
    }

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> MultiplyQtnsWithoutNormalizing(const blQuaternion<blDataType>& qtn1,
                                                               const blQuaternion<blDataType>& qtn2)
{
    blQuaternion<blDataType> result;

    result.m_w = qtn1.m_w*qtn2.m_w - qtn1.m_xyz.x*qtn2.m_xyz.x - qtn1.m_xyz.y*qtn2.m_xyz.y - qtn1.m_xyz.z*qtn2.m_xyz.z;
    result.m_xyz.x = qtn1.m_w*qtn2.m_xyz.x + qtn1.m_xyz.x*qtn2.m_w + qtn1.m_xyz.y*qtn2.m_xyz.z - qtn1.m_xyz.z*qtn2.m_xyz.y;
    result.m_xyz.y = qtn1.m_w*qtn2.m_xyz.y + qtn1.m_xyz.y*qtn2.m_w + qtn1.m_xyz.z*qtn2.m_xyz.x - qtn1.m_xyz.x*qtn2.m_xyz.z;
    result.m_xyz.z = qtn1.m_w*qtn2.m_xyz.z + qtn1.m_xyz.z*qtn2.m_w + qtn1.m_xyz.x*qtn2.m_xyz.y - qtn1.m_xyz.y*qtn2.m_xyz.x;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> AddQtnsWithoutNormalizing(const blQuaternion<blDataType>& qtn1,
                                                          const blQuaternion<blDataType>& qtn2)
{
    blQuaternion<blDataType> result = CreateQtnWithoutNormalizing(qtn1.m_w + qtn2.m_w,
                                                                  qtn1.m_xyz + qtn2.m_xyz);

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator+(const blQuaternion<blDataType>& qtn)const
{
    return blQuaternion<blDataType>((m_w + qtn.m_w),(m_xyz + qtn.m_xyz));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator*(const blQuaternion<blDataType>& qtn)const
{
    blDataType w = m_w*qtn.m_w - m_xyz.x*qtn.m_xyz.x - m_xyz.y*qtn.m_xyz.y - m_xyz.z*qtn.m_xyz.z;
    blDataType x = m_w*qtn.m_xyz.x + m_xyz.x*qtn.m_w + m_xyz.y*qtn.m_xyz.z - m_xyz.z*qtn.m_xyz.y;
    blDataType y = m_w*qtn.m_xyz.y + m_xyz.y*qtn.m_w + m_xyz.z*qtn.m_xyz.x - m_xyz.x*qtn.m_xyz.z;
    blDataType z = m_w*qtn.m_xyz.z + m_xyz.z*qtn.m_w + m_xyz.x*qtn.m_xyz.y - m_xyz.y*qtn.m_xyz.x;

    return blQuaternion<blDataType>(w,blVector3d<blDataType>(x,y,z));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator*(const blDataType& scalar)const
{
    blQuaternion<blDataType> result(*this);
    result.m_w *= scalar;
    result.m_xyz *= scalar;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> operator*(const blDataType& scalar,
                                          const blQuaternion<blDataType>& qtn)
{
    blQuaternion<blDataType> result(qtn);
    result.m_w *= scalar;
    result.m_xyz *= scalar;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator/(const blDataType& scalar)const
{
    blQuaternion<blDataType> result(*this);
    result.m_w /= scalar;
    result.m_xyz /= scalar;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator/(const blQuaternion<blDataType>& qtn)const
{
    blDataType denominator = qtn.m_w*qtn.m_w + qtn.m_xyz.x*qtn.m_xyz.x + qtn.m_xyz.y*qtn.m_xyz.y + qtn.m_xyz.z*qtn.m_xyz.z;

    blDataType w = ( qtn.m_w*m_w + qtn.m_xyz.x*m_xyz.x + qtn.m_xyz.y*m_xyz.y + qtn.m_xyz.z*m_xyz.z ) / denominator;

    blDataType x = ( qtn.m_w*m_xyz.x - qtn.m_xyz.x*m_w - qtn.m_xyz.y*m_w + qtn.m_xyz.z*m_xyz.y ) / denominator;

    blDataType y = ( qtn.m_w*m_xyz.y + qtn.m_xyz.x*m_xyz.z - qtn.m_xyz.y*m_w - qtn.m_xyz.z*m_w ) / denominator;

    blDataType z = ( qtn.m_w*m_xyz.z - qtn.m_xyz.x*m_xyz.y + qtn.m_xyz.y*m_xyz.x - qtn.m_xyz.z*m_w ) / denominator;

    return blQuaternion<blDataType>(w,blVector3d<blDataType>(x,y,z));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void rotateVector(blVector3d<blDataType>& vectorToRotate,
                         const blQuaternion<blDataType>& rotQtn)
{
    vectorToRotate = vectorToRotate.getMagnitude() *
                     ((rotQtn * blQuaternion<blDataType>(0,vectorToRotate) * rotQtn.getConjugate()).m_xyz).getNormalized();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void rotateVectorTheOppositeWay(blVector3d<blDataType>& vectorToRotate,
                                       const blQuaternion<blDataType>& rotQtn)
{
    vectorToRotate = vectorToRotate.getMagnitude() *
                     ((rotQtn.getConjugate() * blQuaternion<blDataType>(0,vectorToRotate) * rotQtn).m_xyz).getNormalized();
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

    os << qtn.m_w << " " << qtn.m_xyz;
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
    if(!(is >> qtn.m_w))
    {
        // Error -- Cound not read
        //          the w value
        return is;
    }

    if(!(is >> qtn.m_xyz))
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
                                              convertedNumber.m_w,
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the xyz vector

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.m_xyz,
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_QUATERNION_HPP
