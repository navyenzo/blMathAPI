#ifndef BL_VECTOR3D_HPP
#define BL_VECTOR3D_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple 3d vector class
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
#include "blPoint2dOperations.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
class blVector3d
{
public: // Constructors and destructors



    // Default constructor

    blVector3d(const blNumberType& x = 0,
               const blNumberType& y = 0,
               const blNumberType& z = 0);



    // Copy constructor

    template<typename blNumberType2>
    blVector3d(const blVector3d<blNumberType2>& vector);



    // Constructor from a point

    template<typename blNumberType2>
    blVector3d(const blPoint2d<blNumberType2>& point);



    // Destructor

    ~blVector3d()
    {
    }



public: // Overloaded operators



    template<typename blNumberType2>
    blVector3d<blNumberType>&               operator=(const blVector3d<blNumberType2>& vector);

    template<typename blNumberType2>
    blVector3d<blNumberType>&               operator=(const blPoint2d<blNumberType2>& point);

    bool                                    operator==(const blVector3d<blNumberType>& vector)const;
    bool                                    operator!=(const blVector3d<blNumberType>& vector)const;

    const blVector3d<blNumberType>          operator-()const;
    blVector3d<blNumberType>&               operator+=(const blVector3d<blNumberType>& vector);
    blVector3d<blNumberType>&               operator-=(const blVector3d<blNumberType>& vector);
    blVector3d<blNumberType>&               operator*=(const blNumberType& scalar);
    blVector3d<blNumberType>&               operator/=(const blNumberType& scalar);

    const blVector3d<blNumberType>          operator+(const blVector3d<blNumberType>& vector)const;
    const blVector3d<blNumberType>          operator-(const blVector3d<blNumberType>& vector)const;
    const blVector3d<blNumberType>          operator*(const blNumberType& scalar)const;
    const blVector3d<blNumberType>          operator/(const blNumberType& scalar)const;



    // Dot product

    blNumberType                            operator*(const blVector3d<blNumberType>& vector)const;



public: // Public functions



    // Functions used to get/set the
    // vector's components

    const blNumberType&                     x()const;
    const blNumberType&                     y()const;
    const blNumberType&                     z()const;

    blNumberType&                           x();
    blNumberType&                           y();
    blNumberType&                           z();



private: // Private variables



    // The vector's x,y
    // and z coordinates

    blNumberType                            m_x;
    blNumberType                            m_y;
    blNumberType                            m_z;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>::blVector3d(const blNumberType& x,
                                          const blNumberType& y,
                                          const blNumberType& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blVector3d<blNumberType>::blVector3d(const blVector3d<blNumberType2>& vector)
{
    m_x = static_cast<blNumberType>(vector.x());
    m_y = static_cast<blNumberType>(vector.y());
    m_z = static_cast<blNumberType>(vector.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blVector3d<blNumberType>::blVector3d(const blPoint2d<blNumberType2>& point)
{
    m_x = static_cast<blNumberType>(point.x());
    m_y = static_cast<blNumberType>(point.y());
    m_z = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator=(const blVector3d<blNumberType2>& vector)
{
    if(this != &vector)
    {
        m_x = static_cast<blNumberType>(vector.x());
        m_y = static_cast<blNumberType>(vector.y());
        m_z = static_cast<blNumberType>(vector.z());
    }

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator=(const blPoint2d<blNumberType2>& point)
{
    m_x = static_cast<blNumberType>(point.x());
    m_y = static_cast<blNumberType>(point.y());
    m_z = 0;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blVector3d<blNumberType>::x()const
{
    return m_x;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blVector3d<blNumberType>::y()const
{
    return m_y;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blVector3d<blNumberType>::z()const
{
    return m_z;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blVector3d<blNumberType>::x()
{
    return m_x;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blVector3d<blNumberType>::y()
{
    return m_y;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blVector3d<blNumberType>::z()
{
    return m_z;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blVector3d<blNumberType>::operator==(const blVector3d<blNumberType>& vector)const
{
    // Check the components

    if(m_x != vector.x())
        return false;
    if(m_y != vector.y())
        return false;
    if(m_z != vector.z())
        return false;

    // By now we know the components
    // match so the vectors are equal

    return true;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blVector3d<blNumberType>::operator!=(const blVector3d<blNumberType>& vector)const
{
    // Check the components

    if(m_x != vector.x())
        return true;
    if(m_y != vector.y())
        return true;
    if(m_z != vector.z())
        return true;

    // By now we know the components
    // match so the vectors are equal

    return false;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType> blVector3d<blNumberType>::operator-()const
{
    return blVector3d<blNumberType>(-m_x,-m_y,-m_z);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator+=(const blVector3d<blNumberType>& vector)
{
    m_x += vector.x();
    m_y += vector.y();
    m_z += vector.z();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator-=(const blVector3d<blNumberType>& vector)
{
    m_x -= vector.x();
    m_y -= vector.y();
    m_z -= vector.z();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator*=(const blNumberType& scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& blVector3d<blNumberType>::operator/=(const blNumberType& scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType> operator*(const blNumberType& scalar,
                                        const blVector3d<blNumberType>& vector)
{
    return vector * scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType> blVector3d<blNumberType>::operator*(const blNumberType& scalar)const
{
    return blVector3d<blNumberType>(m_x * scalar,m_y * scalar,m_z * scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType> blVector3d<blNumberType>::operator/(const blNumberType& scalar)const
{
    return blVector3d<blNumberType>(m_x / scalar,m_y / scalar, m_z / scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType> blVector3d<blNumberType>::operator+(const blVector3d<blNumberType>& vector)const
{
    return blVector3d<blNumberType>(m_x + vector.x(),m_y + vector.y(), m_z + vector.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType> blVector3d<blNumberType>::operator-(const blVector3d<blNumberType>& vector)const
{
    return blVector3d<blNumberType>(m_x - vector.x(),m_y - vector.y(),m_z - vector.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType blVector3d<blNumberType>::operator*(const blVector3d<blNumberType>& vector)const
{
    return (m_x * vector.x() + m_y * vector.y() + m_z * vector.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_VECTOR3D_HPP
