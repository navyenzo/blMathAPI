#ifndef BL_RECTANGLE_HPP
#define BL_RECTANGLE_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple rectangle class
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
class blRectangle
{
public: // Constructors and destructors



    // Default constructor

    blRectangle(const blNumberType& x1 = blNumberType(0),
                const blNumberType& y1 = blNumberType(0),
                const blNumberType& x2 = blNumberType(0),
                const blNumberType& y2 = blNumberType(0));



    // Constructor from
    // two points

    blRectangle(const blPoint2d<blNumberType>& P1,
                const blPoint2d<blNumberType>& P2);



    // Copy constructor

    template<typename blNumberType2>
    blRectangle(const blRectangle<blNumberType2>& rectangle);



    // Destructor

    ~blRectangle()
    {
    }



public: // Overloaded operators



    template<typename blNumberType2>
    blRectangle<blNumberType>&              operator=(const blRectangle<blNumberType2>& rectangle);

    bool                                    operator==(const blRectangle<blNumberType>& rectangle)const;
    bool                                    operator!=(const blRectangle<blNumberType>& rectangle)const;



public: // Public functions



    // Functions used to get/set
    // the rectangle's point coordinates

    const blPoint2d<blNumberType>&          p1()const;
    const blPoint2d<blNumberType>&          p2()const;

    blPoint2d<blNumberType>&                p1();
    blPoint2d<blNumberType>&                p2();



    // Function used to
    // reset the rectangle
    // to zero

    void                                    reset();



private: // Private variables



    // Rectangle coordinates

    blPoint2d<blNumberType>                 m_p1;
    blPoint2d<blNumberType>                 m_p2;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>::blRectangle(const blNumberType& x1,
                                            const blNumberType& y1,
                                            const blNumberType& x2,
                                            const blNumberType& y2)
{
    m_p1.x() = x1;
    m_p1.y() = y1;

    m_p2.x() = x2;
    m_p2.y() = y2;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>::blRectangle(const blPoint2d<blNumberType>& P1,
                                            const blPoint2d<blNumberType>& P2)
{
    m_p1 = P1;
    m_p2 = P2;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blRectangle<blNumberType>::blRectangle(const blRectangle<blNumberType2>& rectangle)
{
    m_p1 = rectangle.p1();
    m_p2 = rectangle.p2();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blRectangle<blNumberType>& blRectangle<blNumberType>::operator=(const blRectangle<blNumberType2>& rectangle)
{
    if(this != &rectangle)
    {
        m_p1 = blPoint2d<blNumberType>(rectangle.p1());
        m_p2 = blPoint2d<blNumberType>(rectangle.p2());
    }

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blRectangle<blNumberType>::operator==(const blRectangle<blNumberType>& rectangle)const
{
    if(m_p1 == rectangle.p1() && m_p2 == rectangle.p2())
    {
        return true;
    }
    else
        return false;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool blRectangle<blNumberType>::operator!=(const blRectangle<blNumberType>& rectangle)const
{
    if(m_p1 == rectangle.p1() && m_p2 == rectangle.p2())
    {
        return false;
    }
    else
        return true;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType>& blRectangle<blNumberType>::p1()const
{
    return m_p1;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blPoint2d<blNumberType>& blRectangle<blNumberType>::p2()const
{
    return m_p2;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& blRectangle<blNumberType>::p1()
{
    return m_p1;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType>& blRectangle<blNumberType>::p2()
{
    return m_p2;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline void blRectangle<blNumberType>::reset()
{
    m_p1.x() = 0;
    m_p1.y() = 0;

    m_p2.x() = 0;
    m_p2.y() = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_RECTANGLE_HPP
