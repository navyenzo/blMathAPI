#ifndef BL_POINT2D_HPP
#define BL_POINT2D_HPP


//-------------------------------------------------------------------
// FILE:            blPoint2d.hpp
// CLASS:           blPoint2d
// BASE CLASS:      None
//
// PURPOSE:         A simple 2d point class
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
//
// NOTES:           - This 2d point class has an additional operator
//                    defined in this file that allows multiplying
//                    a scalar by a 2d point
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
class blPoint2d
{
public: // Constructors and destructors

    // Default constructor

    blPoint2d(const blDataType& X = 0,const blDataType& Y = 0);

    // Copy constructor

    blPoint2d(const blPoint2d<blDataType>& point);

    // Constructor from a
    // point of different type

    template<typename blDataType2>
    blPoint2d(const blPoint2d<blDataType2>& point);

    // Destructor

    ~blPoint2d();

public: // Overloaded operators

    bool                            operator==(const blPoint2d<blDataType>& point)const;
    bool                            operator!=(const blPoint2d<blDataType>& point)const;

    const blPoint2d<blDataType>     operator-()const;
    blPoint2d<blDataType>&          operator+=(const blPoint2d<blDataType>& point);
    blPoint2d<blDataType>&          operator-=(const blPoint2d<blDataType>& point);
    blPoint2d<blDataType>&          operator*=(const blDataType& scalar);
    blPoint2d<blDataType>&          operator/=(const blDataType& scalar);

    const blPoint2d<blDataType>     operator+(const blPoint2d<blDataType>& point)const;
    const blPoint2d<blDataType>     operator-(const blPoint2d<blDataType>& point)const;
    const blPoint2d<blDataType>     operator*(const blDataType& scalar)const;
    const blPoint2d<blDataType>     operator/(const blDataType& scalar)const;

    // Dot product

    const blDataType                operator*(const blPoint2d<blDataType>& point)const;

public: // Public functions

    // Point magnitude

    const blDataType                getMagnitude()const;

    // Functions to get a normilized
    // point and to get a point
    // perpendicular to this one

    const blPoint2d<blDataType>     getPerpendicularUnitPoint()const;
    const blPoint2d<blDataType>     getNormalized()const;

    // Function used to get a point
    // with inverted elements

    const blPoint2d<blDataType>     getPointWithInvertedElements()const;

    // Function used to normalize
    // this point

    const blPoint2d<blDataType>&    normalize();

    // Functions to calculate norms

    const blDataType                norm1()const;
    const blDataType                norm2()const;
    const blDataType                normInf()const;

public: // Public variables

    // The point's x and y
    // coordinates

    blDataType                      x;
    blDataType                      y;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>::blPoint2d(const blDataType& X,const blDataType& Y)
{
    x = X;
    y = Y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>::blPoint2d(const blPoint2d<blDataType>& point)
{
    x = point.x;
    y = point.y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blPoint2d<blDataType>::blPoint2d(const blPoint2d<blDataType2>& point)
{
    x = static_cast<blDataType>(point.x);
    y = static_cast<blDataType>(point.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>::~blPoint2d(void)
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::getPointWithInvertedElements()const
{
    return blPoint2d<blDataType>(blDataType(1)/x,blDataType(1)/y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator-()const
{
    return blPoint2d<blDataType>(-x,-y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blPoint2d<blDataType>::operator==(const blPoint2d<blDataType>& point)const
{
    // Check the components

    if(x != point.x)
        return false;
    if(y != point.y)
        return false;

    // By now we know the
    // components match so
    // the points are equal

    return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blPoint2d<blDataType>::operator!=(const blPoint2d<blDataType>& point)const
{
    // Check the components

    if(x != point.x)
        return true;
    if(y != point.y)
        return true;

    // By now we know the
    // components match so
    // the points are equal

    return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator+=(const blPoint2d<blDataType> &point)
{
    x += point.x;
    y += point.y;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator-=(const blPoint2d<blDataType> &point)
{
    x -= point.x;
    y -= point.y;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator*=(const blDataType& scalar)
{
    x *= scalar;
    y *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator/=(const blDataType& scalar)
{
    x /= scalar;
    y /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blDataType& scalar,
                                       const blPoint2d<blDataType>& point)
{
    return blPoint2d<blDataType>(scalar*point.x,scalar*point.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator*(const blDataType& scalar)const
{
    return blPoint2d<blDataType>(x * scalar,y * scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator/(const blDataType& scalar)const
{
    return blPoint2d<blDataType>(x / scalar,y / scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator+(const blPoint2d<blDataType>& point)const
{
    return blPoint2d<blDataType>(x + point.x,y + point.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator-(const blPoint2d<blDataType>& point)const
{
    return blPoint2d<blDataType>(x - point.x,y - point.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blPoint2d<blDataType>::operator*(const blPoint2d<blDataType>& point)const
{
    return (x * point.x + y * point.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blPoint2d<blDataType>::getMagnitude()const
{
    return std::sqrt(blDataType(x*x + y*y));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::getPerpendicularUnitPoint()const
{
    // Find a component of this
    // Point that is non zero
    // and if unsuccessfull,
    // just return the zero Point
    //
    // P1*P2 = x1*x2 + y1*y2 = 0

    if(x != 0)
    {
        if(y == 0)
            return blPoint2d<blDataType>(0,1);
        else
        {
            blPoint2d<blDataType> point(x,-(x*x)/y);
            point.normalize();

            return point;
        }
    }
    else if(y != 0)
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
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::getNormalized()const
{
    blDataType magnitude = this->getMagnitude();
    return blPoint2d<blDataType>(x/magnitude,y/magnitude);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType>& blPoint2d<blDataType>::normalize()
{
    blDataType magnitude = getMagnitude();

    x /= magnitude;
    y /= magnitude;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blPoint2d<blDataType>::norm1()const
{
    return (std::abs(x) + std::abs(y));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blPoint2d<blDataType>::norm2()const
{
    return std::sqrt(x*x + y*y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blPoint2d<blDataType>::normInf()const
{
    if(x > y)
        return x;
    else
        return y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a point to
// an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blPoint2d<blDataType>& point)
{
    // We simply output the x and y
    // components with a space
    // separating them
    os << point.x << " " << point.y;

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
                                blPoint2d<blDataType>& point)
{
    if(!(is >> point.x))
    {
        // Error -- Cound not read
        //          the x value
        return is;
    }

    if(!(is >> point.y))
    {
        // Error -- Cound not read
        //          the y value
        return is;
    }

    return is;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void min(const blPoint2d< blDataType >& value1,
                const blPoint2d< blDataType >& value2,
                blPoint2d< blDataType >& minValue)
{
    minValue.x = std::min(value1.x,value2.x);
    minValue.y = std::min(value1.y,value2.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void max(const blPoint2d< blDataType >& value1,
                const blPoint2d< blDataType >& value2,
                blPoint2d< blDataType >& maxValue)
{
    maxValue.x = std::max(value1.x,value2.x);
    maxValue.y = std::max(value1.y,value2.y);
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

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_POINT2D_HPP
