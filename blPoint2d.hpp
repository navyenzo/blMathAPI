#ifndef BL_POINT2D_HPP
#define BL_POINT2D_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple 2d point class
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
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
class blPoint2d
{
public: // Constructors and destructors



    // Default constructor

    blPoint2d(const blNumberType& x = 0,const blNumberType& y = 0);

    // Copy constructor

    template<typename blNumberType2>
    blPoint2d(const blPoint2d<blNumberType2>& point);

    // Destructor

    ~blPoint2d();



public: // Overloaded operators

    template<typename blNumberType2>
    blPoint2d<blNumberType>&                operator=(const blPoint2d<blNumberType2>& point);

    bool                                    operator==(const blPoint2d<blNumberType>& point)const;
    bool                                    operator!=(const blPoint2d<blNumberType>& point)const;

    const blPoint2d<blNumberType>           operator-()const;
    blPoint2d<blNumberType>&                operator+=(const blPoint2d<blNumberType>& point);
    blPoint2d<blNumberType>&                operator-=(const blPoint2d<blNumberType>& point);
    blPoint2d<blNumberType>&                operator*=(const blNumberType& scalar);
    blPoint2d<blNumberType>&                operator/=(const blNumberType& scalar);

    const blPoint2d<blNumberType>           operator+(const blPoint2d<blNumberType>& point)const;
    const blPoint2d<blNumberType>           operator-(const blPoint2d<blNumberType>& point)const;
    const blPoint2d<blNumberType>           operator*(const blNumberType& scalar)const;
    const blPoint2d<blNumberType>           operator/(const blNumberType& scalar)const;



    // Dot product

    const blNumberType                      operator*(const blPoint2d<blNumberType>& point)const;



public: // Public functions



    // Functions used to get/set
    // the point's coordinates

    const blNumberType&                     x()const;
    const blNumberType&                     y()const;

    blNumberType&                           x();
    blNumberType&                           y();



private: // Private variables



    // The point's x and y
    // coordinates

    blNumberType                            m_x;
    blNumberType                            m_y;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>::blPoint2d(const blNumberType& x,const blNumberType& y)
{
    m_x = x;
    m_y = y;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blPoint2d<blNumberType>::blPoint2d(const blPoint2d<blNumberType2>& point)
{
    m_x = static_cast<blNumberType>(point.x());
    m_y = static_cast<blNumberType>(point.y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>::~blPoint2d(void)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blPoint2d<blNumberType>& blPoint2d<blNumberType>::operator=(const blPoint2d<blNumberType2>& point)
{
    if(this != &point)
    {
        m_x = static_cast<blNumberType>(point.x());
        m_y = static_cast<blNumberType>(point.y());
    }

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blPoint2d<blNumberType>::x()const
{
    return m_x;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blPoint2d<blNumberType>::y()const
{
    return m_y;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blPoint2d<blNumberType>::x()
{
    return m_x;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blPoint2d<blNumberType>::y()
{
    return m_y;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType> blPoint2d<blNumberType>::operator-()const
{
    return blPoint2d<blNumberType>(-m_x,-m_y);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blPoint2d<blNumberType>::operator==(const blPoint2d<blNumberType>& point)const
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
template<typename blNumberType>
inline bool blPoint2d<blNumberType>::operator!=(const blPoint2d<blNumberType>& point)const
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
template<typename blNumberType>
inline blPoint2d<blNumberType>& blPoint2d<blNumberType>::operator+=(const blPoint2d<blNumberType>& point)
{
    m_x += point.x();
    m_y += point.y();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& blPoint2d<blNumberType>::operator-=(const blPoint2d<blNumberType>& point)
{
    m_x -= point.x();
    m_y -= point.y();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& blPoint2d<blNumberType>::operator*=(const blNumberType& scalar)
{
    m_x *= scalar;
    m_y *= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& blPoint2d<blNumberType>::operator/=(const blNumberType& scalar)
{
    m_x /= scalar;
    m_y /= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType> operator*(const blNumberType& scalar,
                                       const blPoint2d<blNumberType>& point)
{
    return point * scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType> blPoint2d<blNumberType>::operator*(const blNumberType& scalar)const
{
    return blPoint2d<blNumberType>(m_x * scalar,m_y * scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType> blPoint2d<blNumberType>::operator/(const blNumberType& scalar)const
{
    return blPoint2d<blNumberType>(m_x / scalar,m_y / scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType> blPoint2d<blNumberType>::operator+(const blPoint2d<blNumberType>& point)const
{
    return blPoint2d<blNumberType>(m_x + point.x(),m_y + point.y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType> blPoint2d<blNumberType>::operator-(const blPoint2d<blNumberType>& point)const
{
    return blPoint2d<blNumberType>(m_x - point.x(),m_y - point.y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType blPoint2d<blNumberType>::operator*(const blPoint2d<blNumberType>& point)const
{
    return (m_x * point.x() + m_y * point.y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_POINT2D_HPP
