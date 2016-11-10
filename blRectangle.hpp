#ifndef BL_RECTANGLE_HPP
#define BL_RECTANGLE_HPP


//-------------------------------------------------------------------
// FILE:            blRectangle.hpp
// CLASS:           blRectangle
// BASE CLASS:      None
//
// PURPOSE:         A simple rectangle class
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
class blRectangle
{
public: // Constructors and destructors

    // Default constructor

    blRectangle(const blDataType& x1 = blDataType(0),
                const blDataType& y1 = blDataType(0),
                const blDataType& x2 = blDataType(0),
                const blDataType& y2 = blDataType(0));

    // Constructor from
    // two points

    blRectangle(const blPoint2d<blDataType>& P1,
                const blPoint2d<blDataType>& P2);

    // Copy constructor

    template<typename blDataType2>
    blRectangle(const blRectangle<blDataType2>& rectangle);

    // Virtual destructor

    virtual ~blRectangle()
    {
    }

public: // Overloaded operators

    template<typename blDataType2>
    blRectangle<blDataType>&                operator=(const blRectangle<blDataType2>& rectangle);

    bool                                    operator==(const blRectangle<blDataType>& rectangle)const;
    bool                                    operator!=(const blRectangle<blDataType>& rectangle)const;

public: // Public functions

    // Functions used to get/set
    // the rectangle's point coordinates

    const blPoint2d<blDataType>&            p1()const;
    const blPoint2d<blDataType>&            p2()const;

    blPoint2d<blDataType>&                  p1();
    blPoint2d<blDataType>&                  p2();

    // Function used to
    // reset the rectangle
    // to zero

    void                                    reset();

private: // Private variables

    // Rectangle coordinates

    blPoint2d<blDataType>                   m_p1;
    blPoint2d<blDataType>                   m_p2;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>::blRectangle(const blDataType& x1,
                                            const blDataType& y1,
                                            const blDataType& x2,
                                            const blDataType& y2)
{
    m_p1.x() = x1;
    m_p1.y() = y1;

    m_p2.x() = x2;
    m_p2.y() = y2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>::blRectangle(const blPoint2d<blDataType>& P1,
                                            const blPoint2d<blDataType>& P2)
{
    m_p1 = P1;
    m_p2 = P2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blRectangle<blDataType>::blRectangle(const blRectangle<blDataType2>& rectangle)
{
    m_p1 = rectangle.p1();
    m_p2 = rectangle.p2();
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blRectangle<blDataType>& blRectangle<blDataType>::operator=(const blRectangle<blDataType2>& rectangle)
{
    if(this != &rectangle)
    {
        m_p1 = blPoint2d<blDataType>(rectangle.p1());
        m_p2 = blPoint2d<blDataType>(rectangle.p2());
    }

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blRectangle<blDataType>::operator==(const blRectangle<blDataType>& rectangle)const
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
template<typename blDataType>
inline bool blRectangle<blDataType>::operator!=(const blRectangle<blDataType>& rectangle)const
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
template<typename blDataType>
inline const blPoint2d<blDataType>& blRectangle<blDataType>::p1()const
{
    return m_p1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType>& blRectangle<blDataType>::p2()const
{
    return m_p2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blRectangle<blDataType>::p1()
{
    return m_p1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType>& blRectangle<blDataType>::p2()
{
    return m_p2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::reset()
{
    m_p1.x() = 0;
    m_p1.y() = 0;

    m_p2.x() = 0;
    m_p2.y() = 0;
}
//-------------------------------------------------------------------


#endif // BL_RECTANGLE_HPP
