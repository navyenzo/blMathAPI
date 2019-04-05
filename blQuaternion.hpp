#ifndef BL_QUATERNION_HPP
#define BL_QUATERNION_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple quaternion class
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
#include "blVector3dOperations.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
class blQuaternion
{
public: // Constructors and destructor



    // Default constructor

    blQuaternion(const blNumberType& w = 1,const blVector3d<blNumberType>& xyz = blVector3d<blNumberType>(0,0,0));



    // Copy constructor

    template<typename blNumberType2>
    blQuaternion(const blQuaternion<blNumberType2>& qtn);



    // Default destructor

    ~blQuaternion();



public: // Overloaded operators



    template<typename blNumberType2>
    blQuaternion<blNumberType>&             operator=(const blQuaternion<blNumberType2>& qtn);

    bool                                    operator==(const blQuaternion<blNumberType>& qtn)const;
    bool                                    operator!=(const blQuaternion<blNumberType>& qtn)const;

    blQuaternion<blNumberType>&             operator*=(const blNumberType& scalar);
    blQuaternion<blNumberType>&             operator/=(const blNumberType& scalar);

    blQuaternion<blNumberType>              operator*(const blNumberType& scalar)const;
    blQuaternion<blNumberType>              operator*(const blQuaternion<blNumberType>& qtn)const;

    blQuaternion<blNumberType>              operator/(const blNumberType& scalar)const;
    blQuaternion<blNumberType>              operator/(const blQuaternion<blNumberType>& qtn)const;
    blQuaternion<blNumberType>              operator+(const blQuaternion<blNumberType>& qtn)const;

public: // Public functions



    // Functions used to get/set the
    // equivalent axis/angle and
    // the quaternion components

    const blNumberType&                     w()const;
    blNumberType&                           w();

    const blVector3d<blNumberType>&         xyz()const;
    blVector3d<blNumberType>&               xyz();



private: // Private Variables



    // Variables representing the
    // quaternion's components

    blNumberType                            m_w;
    blVector3d<blNumberType>                m_xyz;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>::blQuaternion(const blNumberType& w,
                                                const blVector3d<blNumberType>& xyz)
{
    m_w = w;
    m_xyz = xyz;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blQuaternion<blNumberType>::blQuaternion(const blQuaternion<blNumberType2>& qtn)
{
    m_w = static_cast<blNumberType>(qtn.w());
    m_xyz = qtn.xyz();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>::~blQuaternion()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blQuaternion<blNumberType>& blQuaternion<blNumberType>::operator=(const blQuaternion<blNumberType2>& qtn)
{
    if(this != &qtn)
    {
        m_w = static_cast<blNumberType>(qtn.w());
        m_xyz = qtn.xyz();
    }

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blQuaternion<blNumberType>::operator==(const blQuaternion<blNumberType>& qtn)const
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
template<typename blNumberType>
inline bool blQuaternion<blNumberType>::operator!=(const blQuaternion<blNumberType>& qtn)const
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
template<typename blNumberType>
inline const blNumberType& blQuaternion<blNumberType>::w()const
{
    return m_w;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blQuaternion<blNumberType>::w()
{
    return m_w;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blVector3d<blNumberType>& blQuaternion<blNumberType>::xyz()const
{
    return m_xyz;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType>& blQuaternion<blNumberType>::xyz()
{
    return m_xyz;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>& blQuaternion<blNumberType>::operator*=(const blNumberType& scalar)
{
    m_w *= scalar;
    m_xyz *= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType>& blQuaternion<blNumberType>::operator/=(const blNumberType& scalar)
{
    m_w /= scalar;
    m_xyz /= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> blQuaternion<blNumberType>::operator+(const blQuaternion<blNumberType>& qtn)const
{
    return blQuaternion<blNumberType>((m_w + qtn.w()),(m_xyz + qtn.xyz()));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> blQuaternion<blNumberType>::operator*(const blQuaternion<blNumberType>& qtn)const
{
    blNumberType newW = m_w*qtn.w() - m_xyz.x()*qtn.xyz().x() - m_xyz.y()*qtn.xyz().y() - m_xyz.z()*qtn.xyz().z();
    blNumberType newX = m_w*qtn.xyz().x() + m_xyz.x()*qtn.w() + m_xyz.y()*qtn.xyz().z() - m_xyz.z()*qtn.xyz().y();
    blNumberType newY = m_w*qtn.xyz().y() + m_xyz.y()*qtn.w() + m_xyz.z()*qtn.xyz().x() - m_xyz.x()*qtn.xyz().z();
    blNumberType newZ = m_w*qtn.xyz().z() + m_xyz.z()*qtn.w() + m_xyz.x()*qtn.xyz().y() - m_xyz.y()*qtn.xyz().x();

    return blQuaternion<blNumberType>(newW,blVector3d<blNumberType>(newX,newY,newZ));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> blQuaternion<blNumberType>::operator*(const blNumberType& scalar)const
{
    return blQuaternion<blNumberType>(m_w*scalar,m_xyz*scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> operator*(const blNumberType& scalar,
                                            const blQuaternion<blNumberType>& qtn)
{
    return qtn * scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> blQuaternion<blNumberType>::operator/(const blNumberType& scalar)const
{
    return blQuaternion<blNumberType>(m_w/scalar,m_xyz/scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blQuaternion<blNumberType> blQuaternion<blNumberType>::operator/(const blQuaternion<blNumberType>& qtn)const
{
    blNumberType denominator = qtn.w()*qtn.w() + qtn.xyz().x()*qtn.xyz().x() + qtn.xyz().y()*qtn.xyz().y() + qtn.xyz().z()*qtn.xyz().z();

    blNumberType newW = ( qtn.w()*m_w + qtn.xyz().x()*m_xyz.x() + qtn.xyz().y()*m_xyz.y() + qtn.xyz().z()*m_xyz.z() ) / denominator;

    blNumberType newX = ( qtn.w()*m_xyz.x() - qtn.xyz().x()*m_w - qtn.xyz().y()*m_w + qtn.xyz().z()*m_xyz.y() ) / denominator;

    blNumberType newY = ( qtn.w()*m_xyz.y() + qtn.xyz().x()*m_xyz.z() - qtn.xyz().y()*m_w - qtn.xyz().z()*m_w ) / denominator;

    blNumberType newZ = ( qtn.w()*m_xyz.z() - qtn.xyz().x()*m_xyz.y() + qtn.xyz().y()*m_xyz.x() - qtn.xyz().z()*m_w ) / denominator;

    return blQuaternion<blNumberType>(newW,blVector3d<blNumberType>(newX,newY,newZ));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_QUATERNION_HPP
