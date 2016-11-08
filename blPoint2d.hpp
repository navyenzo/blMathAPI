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
template<typename blDataType>
class blPoint2d
{
public: // Constructors and destructors

    // Default constructor

    blPoint2d(const blDataType& x = 0,const blDataType& y = 0);

    // Copy constructor

    template<typename blDataType2>
    blPoint2d(const blPoint2d<blDataType2>& point);

    // Destructor

    ~blPoint2d();

public: // Overloaded operators

    template<typename blDataType2>
    blPoint2d<blDataType>&          operator=(const blPoint2d<blDataType2>& point);

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

    // Functions used to get/set
    // the point's coordinates

    const blDataType&               x()const;
    const blDataType&               y()const;

    blDataType&                     x();
    blDataType&                     y();

private: // Private variables

    // The point's x and y
    // coordinates

    blDataType                      m_x;
    blDataType                      m_y;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>::blPoint2d(const blDataType& x,const blDataType& y)
{
    m_x = x;
    m_y = y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blPoint2d<blDataType>::blPoint2d(const blPoint2d<blDataType2>& point)
{
    m_x = static_cast<blDataType>(point.x());
    m_y = static_cast<blDataType>(point.y());
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
template<typename blDataType2>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator=(const blPoint2d<blDataType2>& point)
{
    if(this != &point)
    {
        m_x = static_cast<blDataType>(point.x());
        m_y = static_cast<blDataType>(point.y());
    }

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blPoint2d<blDataType>::x()const
{
    return m_x;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blPoint2d<blDataType>::y()const
{
    return m_y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blPoint2d<blDataType>::x()
{
    return m_x;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blPoint2d<blDataType>::y()
{
    return m_y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blPoint2d<blDataType>::operator-()const
{
    return blPoint2d<blDataType>(-m_x,-m_y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blPoint2d<blDataType>::operator==(const blPoint2d<blDataType>& point)const
{
    // Check the components

    if(m_x != point.x())
        return false;
    if(m_y != point.y())
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

    if(m_x != point.x())
        return true;
    if(m_y != point.y())
        return true;

    // By now we know the
    // components match so
    // the points are equal

    return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator+=(const blPoint2d<blDataType>& point)
{
    m_x += point.x();
    m_y += point.y();

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator-=(const blPoint2d<blDataType>& point)
{
    m_x -= point.x();
    m_y -= point.y();

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator*=(const blDataType& scalar)
{
    m_x *= scalar;
    m_y *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blPoint2d<blDataType>::operator/=(const blDataType& scalar)
{
    m_x /= scalar;
    m_y /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blDataType& scalar,
                                       const blPoint2d<blDataType>& point)
{
    return point * scalar;
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

#endif // BL_POINT2D_HPP
