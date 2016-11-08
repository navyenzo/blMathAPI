#ifndef BL_QUATERNION_HPP
#define BL_QUATERNION_HPP


//-------------------------------------------------------------------
// FILE:            blQuaternion.hpp
// CLASS:           blQuaternion
// BASE CLASS:      None
//
// PURPOSE:         A simple quaternion class
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
class blQuaternion
{
public: // Constructors and destructor

    // Default constructor

    blQuaternion(const blDataType& w = 1,const blVector3d<blDataType>& xyz = blVector3d<blDataType>(0,0,0));

    // Copy constructor

    template<typename blDataType2>
    blQuaternion(const blQuaternion<blDataType2>& qtn);

    // Default destructor

    ~blQuaternion();

public: // Overloaded operators

    template<typename blDataType2>
    blQuaternion<blDataType>&           operator=(const blQuaternion<blDataType2>& qtn);

    bool                                operator==(const blQuaternion<blDataType>& qtn)const;
    bool                                operator!=(const blQuaternion<blDataType>& qtn)const;

    blQuaternion<blDataType>&           operator*=(const blDataType& scalar);
    blQuaternion<blDataType>&           operator/=(const blDataType& scalar);

    blQuaternion<blDataType>            operator*(const blDataType& scalar)const;
    blQuaternion<blDataType>            operator*(const blQuaternion<blDataType>& qtn)const;

    blQuaternion<blDataType>            operator/(const blDataType& scalar)const;
    blQuaternion<blDataType>            operator/(const blQuaternion<blDataType>& qtn)const;
    blQuaternion<blDataType>            operator+(const blQuaternion<blDataType>& qtn)const;

public: // Public functions

    // Functions used to get/set the
    // equivalent axis/angle and
    // the quaternion components

    const blDataType&                   w()const;
    blDataType&                         w();

    const blVector3d<blDataType>&       xyz()const;
    blVector3d<blDataType>&             xyz();

private: // Private Variables

    // Variables representing the
    // quaternion's components

    blDataType                          m_w;
    blVector3d<blDataType>              m_xyz;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::blQuaternion(const blDataType& w,
                                              const blVector3d<blDataType>& xyz)
{
    m_w = w;
    m_xyz = xyz;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blQuaternion<blDataType>::blQuaternion(const blQuaternion<blDataType2>& qtn)
{
    m_w = static_cast<blDataType>(qtn.w());
    m_xyz = qtn.xyz();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>::~blQuaternion()
{
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blQuaternion<blDataType>& blQuaternion<blDataType>::operator=(const blQuaternion<blDataType2>& qtn)
{
    if(this != &qtn)
    {
        m_w = static_cast<blDataType>(qtn.w());
        m_xyz = qtn.xyz();
    }

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blQuaternion<blDataType>::operator==(const blQuaternion<blDataType>& qtn)const
{
    // Check if all the components
    // are equal

    if(m_w != qtn.w())
        return false;
    if(m_xyz != qtn.xyz())
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

    if(m_w != qtn.w())
        return true;
    if(m_xyz != qtn.xyz())
        return true;

    // By now we know the two
    // quaternions are equal

    return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blQuaternion<blDataType>::w()const
{
    return m_w;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blQuaternion<blDataType>::w()
{
    return m_w;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blVector3d<blDataType>& blQuaternion<blDataType>::xyz()const
{
    return m_xyz;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType>& blQuaternion<blDataType>::xyz()
{
    return m_xyz;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>& blQuaternion<blDataType>::operator*=(const blDataType& scalar)
{
    m_w *= scalar;
    m_xyz *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType>& blQuaternion<blDataType>::operator/=(const blDataType& scalar)
{
    m_w /= scalar;
    m_xyz /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator+(const blQuaternion<blDataType>& qtn)const
{
    return blQuaternion<blDataType>((m_w + qtn.w()),(m_xyz + qtn.xyz()));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator*(const blQuaternion<blDataType>& qtn)const
{
    blDataType newW = m_w*qtn.w() - m_xyz.x()*qtn.xyz().x() - m_xyz.y()*qtn.xyz().y() - m_xyz.z()*qtn.xyz().z();
    blDataType newX = m_w*qtn.xyz().x() + m_xyz.x()*qtn.w() + m_xyz.y()*qtn.xyz().z() - m_xyz.z()*qtn.xyz().y();
    blDataType newY = m_w*qtn.xyz().y() + m_xyz.y()*qtn.w() + m_xyz.z()*qtn.xyz().x() - m_xyz.x()*qtn.xyz().z();
    blDataType newZ = m_w*qtn.xyz().z() + m_xyz.z()*qtn.w() + m_xyz.x()*qtn.xyz().y() - m_xyz.y()*qtn.xyz().x();

    return blQuaternion<blDataType>(newW,blVector3d<blDataType>(newX,newY,newZ));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator*(const blDataType& scalar)const
{
    return blQuaternion<blDataType>(m_w*scalar,m_xyz*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> operator*(const blDataType& scalar,
                                          const blQuaternion<blDataType>& qtn)
{
    return qtn * scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator/(const blDataType& scalar)const
{
    return blQuaternion<blDataType>(m_w/scalar,m_xyz/scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blQuaternion<blDataType> blQuaternion<blDataType>::operator/(const blQuaternion<blDataType>& qtn)const
{
    blDataType denominator = qtn.w()*qtn.w() + qtn.xyz().x()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().y() + qtn.xyz().z()*qtn.xyz().z();

    blDataType newW = ( qtn.w()*m_w + qtn.xyz().x()*m_xyz.x() + qtn.xyz().y()*m_xyz.y() + qtn.xyz().z()*m_xyz.z() ) / denominator;

    blDataType newX = ( qtn.w()*m_xyz.x() - qtn.xyz().x()*m_w - qtn.xyz().y()*m_w + qtn.xyz().z()*m_xyz.y() ) / denominator;

    blDataType newY = ( qtn.w()*m_xyz.y() + qtn.xyz().x()*m_xyz.z() - qtn.xyz().y()*m_w - qtn.xyz().z()*m_w ) / denominator;

    blDataType newZ = ( qtn.w()*m_xyz.z() - qtn.xyz().x()*m_xyz.y() + qtn.xyz().y()*m_xyz.x() - qtn.xyz().z()*m_w ) / denominator;

    return blQuaternion<blDataType>(newW,blVector3d<blDataType>(newX,newY,newZ));
}
//-------------------------------------------------------------------


#endif // BL_QUATERNION_HPP
