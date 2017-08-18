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

    blVector3d(const blDataType& x = 0,
               const blDataType& y = 0,
               const blDataType& z = 0);

    // Copy constructor

    template<typename blDataType2>
    blVector3d(const blVector3d<blDataType2>& vector);

    // Constructor from a point

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

    blDataType                      operator*(const blVector3d<blDataType>& vector)const;

public: // Public functions

    // Functions used to get/set the
    // vector's components

    const blDataType&               x()const;
    const blDataType&               y()const;
    const blDataType&               z()const;

    blDataType&                     x();
    blDataType&                     y();
    blDataType&                     z();

private: // Private variables

    // The vector's x,y
    // and z coordinates

    blDataType                      m_x;
    blDataType                      m_y;
    blDataType                      m_z;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>::blVector3d(const blDataType& x,
                                          const blDataType& y,
                                          const blDataType& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>::blVector3d(const blVector3d<blDataType2>& vector)
{
    m_x = static_cast<blDataType>(vector.x());
    m_y = static_cast<blDataType>(vector.y());
    m_z = static_cast<blDataType>(vector.z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>::blVector3d(const blPoint2d<blDataType2>& point)
{
    m_x = static_cast<blDataType>(point.x());
    m_y = static_cast<blDataType>(point.y());
    m_z = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator=(const blVector3d<blDataType2>& vector)
{
    if(this != &vector)
    {
        m_x = static_cast<blDataType>(vector.x());
        m_y = static_cast<blDataType>(vector.y());
        m_z = static_cast<blDataType>(vector.z());
    }

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator=(const blPoint2d<blDataType2>& point)
{
    m_x = static_cast<blDataType>(point.x());
    m_y = static_cast<blDataType>(point.y());
    m_z = 0;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blVector3d<blDataType>::x()const
{
    return m_x;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blVector3d<blDataType>::y()const
{
    return m_y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blVector3d<blDataType>::z()const
{
    return m_z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blVector3d<blDataType>::x()
{
    return m_x;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blVector3d<blDataType>::y()
{
    return m_y;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blVector3d<blDataType>::z()
{
    return m_z;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blVector3d<blDataType>::operator==(const blVector3d<blDataType>& vector)const
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
template<typename blDataType>
inline bool blVector3d<blDataType>::operator!=(const blVector3d<blDataType>& vector)const
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
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator-()const
{
    return blVector3d<blDataType>(-m_x,-m_y,-m_z);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator+=(const blVector3d<blDataType>& vector)
{
    m_x += vector.x();
    m_y += vector.y();
    m_z += vector.z();

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator-=(const blVector3d<blDataType>& vector)
{
    m_x -= vector.x();
    m_y -= vector.y();
    m_z -= vector.z();

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator*=(const blDataType& scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blVector3d<blDataType>::operator/=(const blDataType& scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    m_z /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> operator*(const blDataType& scalar,
                                        const blVector3d<blDataType>& vector)
{
    return vector * scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator*(const blDataType& scalar)const
{
    return blVector3d<blDataType>(m_x * scalar,m_y * scalar,m_z * scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator/(const blDataType& scalar)const
{
    return blVector3d<blDataType>(m_x / scalar,m_y / scalar, m_z / scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator+(const blVector3d<blDataType>& vector)const
{
    return blVector3d<blDataType>(m_x + vector.x(),m_y + vector.y(), m_z + vector.z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType> blVector3d<blDataType>::operator-(const blVector3d<blDataType>& vector)const
{
    return blVector3d<blDataType>(m_x - vector.x(),m_y - vector.y(),m_z - vector.z());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType blVector3d<blDataType>::operator*(const blVector3d<blDataType>& vector)const
{
    return (m_x * vector.x() + m_y * vector.y() + m_z * vector.z());
}
//-------------------------------------------------------------------


#endif // BL_VECTOR3D_HPP
