#ifndef BL_RECTANGLE_HPP
#define BL_RECTANGLE_HPP


//-------------------------------------------------------------------
// FILE:            blRectangle.hpp
// CLASS:           blRectangle
// BASE CLASS:      None
//
// PURPOSE:         A simple rectangle class with useful functions
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blPoint2d -- Used to store coordinate pairs
//                            -- Used to return the center of the
//                               rectangle
//                  std::abs -- To calculate width and height
//                  std::swap -- To sort the rectangle coordinates
//                  iostream -- To output to the console
//
// NOTES:
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
class blRectangle
{
public: // Constructors and destructors

    // Default constructor

    blRectangle(const blDataType& x1 = 0,
                const blDataType& y1 = 0,
                const blDataType& x2 = 0,
                const blDataType& y2 = 0);

    // Constructor from
    // two points

    blRectangle(const blPoint2d<blDataType>& P1,
                const blPoint2d<blDataType>& P2);

    // Copy constructor from
    // different type

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

    // Functions used to
    // get the width, height,
    // center, area of the
    // rectangle

    const blDataType                        width()const;
    const blDataType                        height()const;
    const blDataType                        area()const;
    const blPoint2d<blDataType>             center()const;

    // Function used to
    // sort the corners
    // (where x1,y1 coordinates
    // are made smaller
    // than x2,y2 coordinates

    void                                    sortCoordinates();

    // Function used to
    // clip the rectangle's
    // coordinates

    void                                    clipXCoords(const blDataType& xMin,
                                                        const blDataType& xMax);
    void                                    clipYCoords(const blDataType& yMin,
                                                        const blDataType& yMax);
    void                                    clipCoords(const blDataType& xMin,
                                                       const blDataType& yMin,
                                                       const blDataType& xMax,
                                                       const blDataType& yMax);

    // Functions used to
    // flip the x or y
    // coordinates of this
    // rectangle

    void                                    flipXCoords();
    void                                    flipYCoords();

    // Function used to
    // move the rectangle
    // by placing either
    // the first or second
    // coordinate pairs to
    // a specified location

    void                                    moveRectangleByPlacingP1At(const blDataType& x,
                                                                       const blDataType& y);
    void                                    moveRectangleByPlacingP2At(const blDataType& x,
                                                                       const blDataType& y);

    // Function used to
    // move the rectangle
    // by translation

    void                                    translateRectangle(const blDataType& xTranslation,
                                                               const blDataType& yTranslation);

    // Function used to
    // scale the rectangle's
    // coordinates

    void                                    scaleCoordinates(const blDataType& xScale,
                                                             const blDataType& yScale);

    // Function used to
    // scale the rectangle
    // (scale the width
    // and height) while
    // keeping the rectangle
    // centered at the
    // same point

    void                                    scaleRectangle(const blDataType& widthScale,
                                                           const blDataType& heightScale);

    // Function used to
    // set a new size
    // for the rectangle
    // leaving it centered
    // at its current center
    // position

    void                                    sizeRectangle(const blDataType& width,
                                                          const blDataType& height);

    // Functions used to
    // scale the rectangle
    // while keeping one of
    // its points fixed

    void                                    scaleRectangleWithP1Fixed(const blDataType& widthScale,
                                                                      const blDataType& heightScale);
    void                                    scaleRectangleWithP2Fixed(const blDataType& widthScale,
                                                                      const blDataType& heightScale);

    // Funtions used to
    // zoom in/out of
    // the rectangle
    // using relative
    // coordinates

    void                                    zoomRectangle(const blPoint2d<blDataType>& zoomP1,
                                                          const blPoint2d<blDataType>& zoomP2);

    void                                    zoomRectangle(const blRectangle<blDataType>& zoomRect);

    // Functions used to
    // map points to this
    // rectangle where
    // zero maps to point
    // p1 and one maps to
    // point p2

    void                                    mapPointToRectangle(blPoint2d<blDataType>& pointToMap);
    void                                    mapRectangleToRectangle(blRectangle<blDataType>& rectangleToMap);

    // Function used to
    // center the rectangle
    // about a point

    void                                    centerRectangle(const blPoint2d<blDataType>& newCenter);

    // Function used to
    // reset the rectangle
    // to zero

    void                                    reset();

public: // Public variables

    // rectangle coordinates

    blPoint2d<blDataType>                   p1;
    blPoint2d<blDataType>                   p2;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>::blRectangle(const blDataType& x1,
                                            const blDataType& y1,
                                            const blDataType& x2,
                                            const blDataType& y2)
{
    p1.x = x1;
    p1.y = y1;

    p2.x = x2;
    p2.y = y2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>::blRectangle(const blPoint2d<blDataType>& P1,
                                            const blPoint2d<blDataType>& P2)
{
    p1 = P1;
    p2 = P2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blRectangle<blDataType>::blRectangle(const blRectangle<blDataType2>& rectangle)
{
    p1 = blPoint2d<blDataType>(rectangle.p1);
    p2 = blPoint2d<blDataType>(rectangle.p2);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blRectangle<blDataType>& blRectangle<blDataType>::operator=(const blRectangle<blDataType2>& rectangle)
{
    p1 = blPoint2d<blDataType>(rectangle.p1);
    p2 = blPoint2d<blDataType>(rectangle.p2);

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool blRectangle<blDataType>::operator==(const blRectangle<blDataType>& rectangle)const
{
    if(p1 == rectangle.p1 &&
       p2 == rectangle.p2)
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
    if(p1 == rectangle.p1 &&
       p2 == rectangle.p2)
    {
        return false;
    }
    else
        return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::reset()
{
    p1.x = 0;
    p1.y = 0;

    p2.x = 0;
    p2.y = 0;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blRectangle<blDataType>::width()const
{
    return std::abs(p2.x - p1.x);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blRectangle<blDataType>::height()const
{
    return std::abs(p2.y - p1.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType blRectangle<blDataType>::area()const
{
    return (this->width() * this->height());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blPoint2d<blDataType> blRectangle<blDataType>::center()const
{
    return (p1 + p2)/blDataType(2);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::sortCoordinates()
{
    // Sort x coordinates
    if(p1.x > p2.x)
        std::swap(p1.x,p2.x);

    // Sort y coordinates
    if(p1.y > p2.y)
        std::swap(p1.y,p2.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::clipXCoords(const blDataType& xMin,
                                                 const blDataType& xMax)
{
    // Clip the x Coordinates
    if(xMin <= xMax)
    {
        if(p1.x <= p2.x)
        {
            if(p1.x < xMin)
                p1.x = xMin;
            if(p2.x > xMax)
                p2.x = xMax;
        }
        else
        {
            if(p2.x < xMin)
                p2.x = xMin;
            if(p1.x > xMax)
                p1.x = xMax;
        }
    }
    else
    {
        if(p1.x <= p2.x)
        {
            if(p1.x < xMax)
                p1.x = xMax;
            if(p2.x > xMin)
                p2.x = xMin;
        }
        else
        {
            if(p2.x < xMax)
                p2.x = xMax;
            if(p1.x > xMin)
                p1.x = xMin;
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::clipYCoords(const blDataType& yMin,
                                                 const blDataType& yMax)
{
    // Clip the y Coordinates
    if(yMin < yMax)
    {
        if(p1.y <= p2.y)
        {
            if(p1.y < yMin)
                p1.y = yMin;
            if(p2.y > yMax)
                p2.y = yMax;
        }
        else
        {
            if(p2.y < yMin)
                p2.y = yMin;
            if(p1.y > yMax)
                p1.y = yMax;
        }
    }
    else
    {
        if(p1.y <= p2.y)
        {
            if(p1.y < yMax)
                p1.y = yMax;
            if(p2.y > yMin)
                p2.y = yMin;
        }
        else
        {
            if(p2.y < yMax)
                p2.y = yMax;
            if(p1.y > yMin)
                p1.y = yMin;
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::clipCoords(const blDataType& xMin,
                                                const blDataType& yMin,
                                                const blDataType& xMax,
                                                const blDataType& yMax)
{
    clipXCoords(xMin,xMax);
    clipYCoords(yMin,yMax);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::moveRectangleByPlacingP1At(const blDataType& x,
                                                                const blDataType& y)
{
    translateRectangle(x - p1.x,y - p1.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::moveRectangleByPlacingP2At(const blDataType& x,
                                                                const blDataType& y)
{
    translateRectangle(x - p2.x,y - p2.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::translateRectangle(const blDataType& xTranslation,
                                                        const blDataType& yTranslation)
{
    // Add xTranslation and yTranslation to all coordinates
    p1.x += xTranslation;
    p1.y += yTranslation;
    p2.x += xTranslation;
    p2.y += yTranslation;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::scaleRectangle(const blDataType& widthScale,
                                                    const blDataType& heightScale)
{
    // Get the center point of this rectangle
    blPoint2d<blDataType> centerPoint = this->center();

    // Calculate the new scaled width and height
    blDataType halfOfNewWidth = (this->width()/blDataType(2)) * widthScale;
    blDataType halfOfNewHeight = (this->height()/blDataType(2)) * heightScale;

    // Place the x coords
    if(p1.x <= p2.x)
    {
        p1.x = centerPoint.x - halfOfNewWidth;
        p2.x = centerPoint.x + halfOfNewWidth;
    }
    else
    {
        p1.x = centerPoint.x + halfOfNewWidth;
        p2.x = centerPoint.x - halfOfNewWidth;
    }

    // Place the y coords
    if(p1.y <= p2.y)
    {
        p1.y = centerPoint.y - halfOfNewHeight;
        p2.y = centerPoint.y + halfOfNewHeight;
    }
    else
    {
        p1.y = centerPoint.y + halfOfNewHeight;
        p2.y = centerPoint.y - halfOfNewHeight;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::scaleRectangleWithP1Fixed(const blDataType& widthScale,
                                                               const blDataType& heightScale)
{
    // Get the center point of this rectangle
    blPoint2d<blDataType> centerPoint = this->center();

    // Calculate the new scaled width and height
    blDataType newWidth = this->width() * widthScale;
    blDataType newHeight = this->height() * heightScale;

    // Add the new width and height
    // to the point P1
    if(p1.x < p2.x)
        p2.x = p1.x + newWidth;
    else
        p2.x = p1.x - newWidth;

    if(p1.y < p2.y)
        p2.y = p1.y + newHeight;
    else
        p2.y = p1.y - newHeight;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::scaleRectangleWithP2Fixed(const blDataType& widthScale,
                                                           const blDataType& heightScale)
{
    // Get the center point of this rectangle
    blPoint2d<blDataType> centerPoint = this->center();

    // Calculate the new scaled width and height
    blDataType newWidth = this->width() * widthScale;
    blDataType newHeight = this->height() * heightScale;

    // Add the new width and height
    // to the point P1
    if(p2.x > p1.x)
        p1.x = p2.x - newWidth;
    else
        p1.x = p2.x + newWidth;

    if(p2.y > p1.y)
        p1.y = p2.y - newHeight;
    else
        p1.y = p2.y + newHeight;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::scaleCoordinates(const blDataType& xScale,
                                                      const blDataType& yScale)
{
    // Simply scale the x
    // and y coordinates
    // by the passed arguments
    p1.x *= xScale;
    p1.y *= yScale;
    p2.x *= xScale;
    p2.y *= yScale;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::centerRectangle(const blPoint2d<blDataType>& newCenter)
{
    // Find the current center of this rectangle
    blPoint2d<blDataType> oldCenter = this->center();

    // Calculate the difference between the
    // new and old centers
    blPoint2d<blDataType> Translation = newCenter - oldCenter;

    // Translate the rectangle accordingly
    this->translateRectangle(Translation.x,Translation.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::flipXCoords()
{
    std::swap(p1.x,p2.x);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::flipYCoords()
{
    std::swap(p1.y,p2.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::mapPointToRectangle(blPoint2d<blDataType>& pointToMap)
{
    pointToMap.x = p1.x + pointToMap.x * (p2.x - p1.x);
    pointToMap.y = p1.y + pointToMap.y * (p2.y - p1.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::mapRectangleToRectangle(blRectangle<blDataType>& rectangleToMap)
{
    mapPointToRectangle(rectangleToMap.p1);
    mapPointToRectangle(rectangleToMap.p2);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::zoomRectangle(const blPoint2d<blDataType>& zoomP1,
                                                   const blPoint2d<blDataType>& zoomP2)
{
    blPoint2d<blDataType> NewP1 = zoomP1;
    blPoint2d<blDataType> NewP2 = zoomP2;

    mapPointToRectangle(NewP1);
    mapPointToRectangle(NewP2);

    p1 = NewP1;
    p2 = NewP2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::zoomRectangle(const blRectangle<blDataType>& zoomRect)
{
    blPoint2d<blDataType> NewP1 = zoomRect.p1;
    blPoint2d<blDataType> NewP2 = zoomRect.p2;

    mapPointToRectangle(NewP1);
    mapPointToRectangle(NewP2);

    p1 = NewP1;
    p2 = NewP2;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline void blRectangle<blDataType>::sizeRectangle(const blDataType& newWidth,
                                                   const blDataType& newHeight)
{
    // Get the center point of this rectangle
    blPoint2d<blDataType> centerPoint = this->center();

    // Place the x coords
    if(p1.x <= p2.x)
    {
        p1.x = centerPoint.x - std::abs(newWidth/2.0);
        p2.x = centerPoint.x + std::abs(newWidth/2.0);
    }
    else
    {
        p1.x = centerPoint.x + std::abs(newWidth/2.0);
        p2.x = centerPoint.x - std::abs(newWidth/2.0);
    }

    // Place the y coords
    if(p1.y <= p2.y)
    {
        p1.y = centerPoint.y - std::abs(newHeight/2.0);
        p2.y = centerPoint.y + std::abs(newHeight/2.0);
    }
    else
    {
        p1.y = centerPoint.y + std::abs(newHeight/2.0);
        p2.y = centerPoint.y - std::abs(newHeight/2.0);
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            blMap
//
// ARGUMENTS:           - valueToMap
//                      - mapRectangle
//
// TEMPLATE ARGUMENTS:  - blDataType
//
// PURPOSE:             - This function maps a value
//                        from the input range to
//                        the output range where the
//                        ranges are defined by the
//                        specified rectangle
//
// DEPENDENCIES:        - blMap
//                      - blRectangle
//
// NOTES:
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType blMap(const blDataType& valueToMap,
                        const blMathAPI::blRectangle<blDataType>& Map)
{
    return blMap(valueToMap,
                 Map.p1.x,
                 Map.p1.y,
                 Map.p2.x,
                 Map.p2.y);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a rectangle
// to an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMathAPI::blRectangle<blDataType>& rectangle)
{
    // We simply output the
    // components with a
    // space separating them

    os << rectangle.p1 << " " << rectangle.p2;

    return os;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// input a rectangle
// from an input stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blRectangle<blDataType>& rectangle)
{
    if(!(is >> rectangle.p1))
    {
        // Error -- Cound not read
        //          the p1 value

        return is;
    }

    if(!(is >> rectangle.p2))
    {
        // Error -- Cound not read
        //          the p2 value

        return is;
    }

    return is;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to
// convert a generic
// string to a rectangle
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blDataType>
inline blStringIteratorType blConvertStringToNumber(const blStringIteratorType& beginIter,
                                                    const blStringIteratorType& endIter,
                                                    const blCharacterType& DecimalPointDelimiter,
                                                    blMathAPI::blRectangle<blDataType>& ConvertedNumber,
                                                    const int& NumberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // We expect the
    // following format:
    // R = p1 p2

    blStringIteratorType newStringPosition;

    // First we try to
    // get first point

    newStringPosition = blConvertStringToNumber(beginIter,
                                                endIter,
                                                DecimalPointDelimiter,
                                                ConvertedNumber.p1,
                                                NumberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the second
    // point

    newStringPosition = blConvertStringToNumber(newStringPosition,
                                                endIter,
                                                DecimalPointDelimiter,
                                                ConvertedNumber.p2,
                                                NumberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_RECTANGLE_HPP
