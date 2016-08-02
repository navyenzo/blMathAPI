#ifndef BL_VECTOR3D_HPP
#define BL_VECTOR3D_HPP


//-------------------------------------------------------------------
// FILE:            blVector3d.hpp
// CLASS:           blVector3d
// BASE CLASS:      None
//
// PURPOSE:         A simple 3d vector class
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    - std::abs -- To calculate norms
//                  - std::sqrt -- To calculate magnitude
//                  - iostream -- To output to the console
// NOTES:           - This 3d vector class has an additional operator
//                    defined in this file that allows multiplying a
//                    scalar by a 3d vector
//                  - CrossProduct -- Defined in this file to take the
//                                    cross product of two vectors
//
// DATE CREATED:    Mar/30/2010
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
class blVector3d
{
public: // Constructors and destructors

    // Default constructor

    blVector3d(const blDataType& X = 0,
               const blDataType& Y = 0,
               const blDataType& Z = 0);

    // Copy constructor

    template<typename blDataType2>
    blVector3d(const blVector3d<blDataType2>& vector);

    // Constructor from
    // a blPoint2d

    template<typename blDataType2>
    blVector3d(const blPoint2d<blDataType2>& point);

    // Destructor

    ~blVector3d()
    {
    }

public: // Overloaded operators

    template<typename blDataType2>
    blVector3d<blDataType>&         operator=(const blVector3d<blDataType2>& vector);

    template<typename blDataType2>
    blVector3d<blDataType>&         operator=(const blPoint2d<blDataType2>& point);

    bool                            operator==(const blVector3d<blDataType>& vector)const;
    bool                            operator!=(const blVector3d<blDataType>& vector)const;

    const blVector3d<blDataType>    operator-()const;
    blVector3d<blDataType>&         operator+=(const blVector3d<blDataType>& vector);
    blVector3d<blDataType>&         operator-=(const blVector3d<blDataType>& vector);
    blVector3d<blDataType>&         operator*=(const blDataType& scalar);
    blVector3d<blDataType>&         operator/=(const blDataType& scalar);

    const blVector3d<blDataType>    operator+(const blVector3d<blDataType>& vector)const;
    const blVector3d<blDataType>    operator-(const blVector3d<blDataType>& vector)const;
    const blVector3d<blDataType>    operator*(const blDataType& scalar)const;
    const blVector3d<blDataType>    operator/(const blDataType& scalar)const;

    // Dot product

    const blDataType                operator*(const blVector3d<blDataType>& vector)const;

public: // Public functions

    // vector magnitude

    const blDataType                getMagnitude()const;

    // Functions to get a normilized
    // vector and to get a vector
    // perpendicular to this one

    const blVector3d<blDataType>    getPerpendicularUnitVector()const;
    const blVector3d<blDataType>    getNormalized()const;

    // Function used to get
    // a vector with inverted
    // elements

    const blVector3d<blDataType>    getVectorWithInvertedElements()const;

    // Function used to
    // normalize this vector

    const blVector3d<blDataType>&   normalize();

    // Functions to
    // calculate norms

    const blDataType                norm1()const;
    const blDataType                norm2()const;
    const blDataType                normInf()const;

public: // Public variables

    // The vector's x,y
    // and z coordinates

    blDataType                      x;
    blDataType                      y;
    blDataType                      z;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>::blVector3d(const blDataType& X,
                                          const blDataType& Y,
                                          const blDataType& Z)
{
    x = X;
    y = Y;
    z = Z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>::blVector3d(const blVector3d<blDataType2>& vector)
{
    x = static_cast<blDataType>(vector.x);
    y = static_cast<blDataType>(vector.y);
    z = static_cast<blDataType>(vector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>::blVector3d(const blPoint2d<blDataType2>& point)
{
    x = static_cast<blDataType>(point.x);
    y = static_cast<blDataType>(point.y);
    z = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator=(const blVector3d<blDataType2>& vector)
{
    x = static_cast<blDataType>(vector.x);
    y = static_cast<blDataType>(vector.y);
    z = static_cast<blDataType>(vector.z);

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator=(const blPoint2d<blDataType2>& point)
{
    x = static_cast<blDataType>(point.x);
    y = static_cast<blDataType>(point.y);
    z = 0;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::getVectorWithInvertedElements()const
{
    return blVector3d<blDataType>(blDataType(1)/x,blDataType(1)/y,blDataType(1)/z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blVector3d<blDataType>::operator==(const blVector3d<blDataType>& vector)const
{
    // Check the components
    if(x != vector.x)
        return false;
    if(y != vector.y)
        return false;
    if(z != vector.z)
        return false;

    // By now we know the components
    // match so the vectors are equal
    return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blVector3d<blDataType>::operator!=(const blVector3d<blDataType>& vector)const
{
    // Check the components
    if(x != vector.x)
        return true;
    if(y != vector.y)
        return true;
    if(z != vector.z)
        return true;

    // By now we know the components
    // match so the vectors are equal
    return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator-()const
{
    return blVector3d<blDataType>(-x,-y,-z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator+=(const blVector3d<blDataType>& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator-=(const blVector3d<blDataType>& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator*=(const blDataType& scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator/=(const blDataType& scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> operator*(const blDataType& scalar,
                                        const blVector3d<blDataType>& vector)
{
    return blVector3d<blDataType>(scalar*vector.x,scalar*vector.y,scalar*vector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator*(const blDataType& scalar)const
{
    return blVector3d<blDataType>(x * scalar,y * scalar,z * scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator/(const blDataType& scalar)const
{
    return blVector3d<blDataType>(x / scalar,y / scalar, z / scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator+(const blVector3d<blDataType>& vector)const
{
    return blVector3d<blDataType>(x + vector.x,y + vector.y, z + vector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator-(const blVector3d<blDataType>& vector)const
{
    return blVector3d<blDataType>(x - vector.x,y - vector.y,z - vector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blVector3d<blDataType>::operator*(const blVector3d<blDataType>& vector)const
{
    return (x * vector.x + y * vector.y + z * vector.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blVector3d<blDataType>::getMagnitude()const
{
    return std::sqrt(blDataType(x*x + y*y + z*z));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::getPerpendicularUnitVector()const
{
    // Find a component of this
    // vector that is non zero
    // and if unsuccessfull,
    // just return the zero vector
    //
    // P1*P2 = x1*x2 + y1*y2 + z1*z2 = 0

    if(x != 0)
    {
        if(y == 0)
            return blVector3d<blDataType>(0,1,0);
        else
        {
            if(z == 0)
            {
                return blVector3d<blDataType>(0,0,1);
            }
            else
            {
                blVector3d<blDataType> vector(1,1,(x + y)/z);
                vector.normalize();

                return vector;
            }
        }
    }
    else if(y != 0 || z != 0)
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
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::getNormalized()const
{
    blDataType magnitude = this->getMagnitude();
    return blVector3d<blDataType>(x/magnitude,y/magnitude,z/magnitude);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType>& blVector3d<blDataType>::normalize()
{
    blDataType magnitude = getMagnitude();

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blVector3d<blDataType>::norm1()const
{
    return (std::abs(x) + std::abs(y) + std::abs(z));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blVector3d<blDataType>::norm2()const
{
    return std::sqrt(x*x + y*y + z*z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blVector3d<blDataType>::normInf()const
{
    if(x > y)
    {
        if(x > z)
            return x;
        else
            return z;
    }
    else
    {
        if(y > z)
            return y;
        else
            return z;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> crossProduct(const blVector3d<blDataType> v1,
                                           const blVector3d<blDataType> v2)
{
    return blVector3d<blDataType>(v1.y*v2.z - v1.z*v2.y,
                                  -v1.x*v2.z + v1.z*v2.x,
                                  v1.x*v2.y - v1.y*v2.x);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a vector to
// an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,const blVector3d<blDataType>& vector)
{
    // We simply output the x,y
    // and z components with a
    // space separating them

    os << vector.x << " " << vector.y << " " << vector.z;

    return os;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// input a vector from
// an input stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blVector3d<blDataType>& vector)
{
    if(!(is >> vector.x))
    {
        // Error -- Cound not read
        //          the x value
        return is;
    }

    if(!(is >> vector.y))
    {
        // Error -- Cound not read
        //          the y value
        return is;
    }

    if(!(is >> vector.z))
    {
        // Error -- Cound not read
        //          the z value
        return is;
    }

    return is;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void min(const blVector3d< blDataType >& value1,
                const blVector3d< blDataType >& value2,
                blVector3d< blDataType >& minValue)
{
    minValue.x = std::min(value1.x,value2.x);
    minValue.y = std::min(value1.y,value2.y);
    minValue.z = std::min(value1.z,value2.z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void max(const blVector3d< blDataType >& value1,
                const blVector3d< blDataType >& value2,
                blVector3d< blDataType >& maxValue)
{
    maxValue.x = std::max(value1.x,value2.x);
    maxValue.y = std::max(value1.y,value2.y);
    maxValue.z = std::max(value1.z,value2.z);
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
    // V = x y z

    blStringIteratorType newStringPosition;

    // First we try to
    // get the x value

    newStringPosition = convertStringToNumber(beginIter,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.x,
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the y value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.y,
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the z value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.z,
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_VECTOR3D_HPP
