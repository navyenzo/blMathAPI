#ifndef BL_RECTANGLEOPERATIONS_HPP
#define BL_RECTANGLEOPERATIONS_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Some useful functions to handle rectangles
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
#include "blRectangle.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to calculate the width, height
// area and center of a rectangle
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType width(const blRectangle<blNumberType>& rectangle)
{
    return blMathAPI::abs(rectangle.p2().x() - rectangle.p1().x());
}


template<typename blNumberType>
inline blNumberType height(const blRectangle<blNumberType>& rectangle)
{
    return blMathAPI::abs(rectangle.p2().y() - rectangle.p1().y());
}


template<typename blNumberType>
inline blNumberType area(const blRectangle<blNumberType>& rectangle)
{
    return width(rectangle)*height(rectangle);
}


template<typename blNumberType>
inline blPoint2d<blNumberType> center(const blRectangle<blNumberType>& rectangle)
{
    return (rectangle.p1() + rectangle.p2())/blNumberType(2);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to sord a rectangle's
// coordinates so that p1.x and p1.y are
// smaller than p2.x and p2.y
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& sortCoordinates(blRectangle<blNumberType>& rectangle)
{
    // Sort x coordinates

    if(rectangle.p1().x() > rectangle.p2().x())
        std::swap(rectangle.p1().x(),rectangle.p2().x());

    // Sort y coordinates
    if(rectangle.p1().y() > rectangle.p2().y())
        std::swap(rectangle.p1().y(),rectangle.p2().y());

    return rectangle;
}


template<typename blNumberType>
inline blRectangle<blNumberType>& getSortedCoordinates(const blRectangle<blNumberType>& rectangle)
{
    blRectangle<blNumberType> sortedRectangle = rectangle;

    // Sort x coordinates

    if(sortedRectangle.p1().x() > sortedRectangle.p2().x())
        std::swap(sortedRectangle.p1().x(),sortedRectangle.p2().x());

    // Sort y coordinates
    if(sortedRectangle.p1().y() > sortedRectangle.p2().y())
        std::swap(sortedRectangle.p1().y(),sortedRectangle.p2().y());

    return sortedRectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to clip coordinates if they
// go past a specified limit
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& clipXCoords(const blNumberType& xMin,
                                            const blNumberType& xMax,
                                            blRectangle<blNumberType>& rectangle)
{
    if(xMin <= xMax)
    {
        if(rectangle.p1().x() <= rectangle.p2().x())
        {
            if(rectangle.p1().x() < xMin)
                rectangle.p1().x() = xMin;
            if(rectangle.p2().x() > xMax)
                rectangle.p2().x() = xMax;
        }
        else
        {
            if(rectangle.p2().x() < xMin)
                rectangle.p2().x() = xMin;
            if(rectangle.p1().x() > xMax)
                rectangle.p1().x() = xMax;
        }
    }
    else
    {
        if(rectangle.p1().x() <= rectangle.p2().x())
        {
            if(rectangle.p1().x() < xMax)
                rectangle.p1().x() = xMax;
            if(rectangle.p2().x() > xMin)
                rectangle.p2().x() = xMin;
        }
        else
        {
            if(rectangle.p2().x() < xMax)
                rectangle.p2().x() = xMax;
            if(rectangle.p1().x() > xMin)
                rectangle.p1().x() = xMin;
        }
    }

    return rectangle;
}


template<typename blNumberType>
inline blRectangle<blNumberType>& clipYCoords(const blNumberType& yMin,
                                            const blNumberType& yMax,
                                            blRectangle<blNumberType>& rectangle)
{
    if(yMin <= yMax)
    {
        if(rectangle.p1().y() <= rectangle.p2().y())
        {
            if(rectangle.p1().y() < yMin)
                rectangle.p1().y() = yMin;
            if(rectangle.p2().y() > yMax)
                rectangle.p2().y() = yMax;
        }
        else
        {
            if(rectangle.p2().y() < yMin)
                rectangle.p2().y() = yMin;
            if(rectangle.p1().y() > yMax)
                rectangle.p1().y() = yMax;
        }
    }
    else
    {
        if(rectangle.p1().y() <= rectangle.p2().y())
        {
            if(rectangle.p1().y() < yMax)
                rectangle.p1().y() = yMax;
            if(rectangle.p2().y() > yMin)
                rectangle.p2().y() = yMin;
        }
        else
        {
            if(rectangle.p2().y() < yMax)
                rectangle.p2().y() = yMax;
            if(rectangle.p1().y() > yMin)
                rectangle.p1().y() = yMin;
        }
    }

    return rectangle;
}


template<typename blNumberType>
inline blRectangle<blNumberType>& clipCoords(const blNumberType& xMin,
                                           const blNumberType& yMin,
                                           const blNumberType& xMax,
                                           const blNumberType& yMax,
                                           blRectangle<blNumberType>& rectangle)
{
    clipXCoords(xMin,xMax,rectangle);
    clipYCoords(yMin,yMax,rectangle);

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to translated a rectangle
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& translate(const blNumberType& xTranslation,
                                            const blNumberType& yTranslation,
                                            blRectangle<blNumberType>& rectangle)
{
    // Add xTranslation and
    // yTranslation to all coordinates

    rectangle.p1().x() += xTranslation;
    rectangle.p1().y() += yTranslation;
    rectangle.p2().x() += xTranslation;
    rectangle.p2().y() += yTranslation;

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to move rectangles
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& moveByPlacingP1At(const blNumberType& x,
                                                    const blNumberType& y,
                                                    blRectangle<blNumberType>& rectangle)
{
    return translate(x - rectangle.p1().x(),y - rectangle.p1().y(),rectangle);
}



template<typename blNumberType>
inline blRectangle<blNumberType>& moveRectangleByPlacingP2At(const blNumberType& x,
                                                             const blNumberType& y,
                                                             blRectangle<blNumberType>& rectangle)
{
    return translateRectangle(x - rectangle.p2().x(),y - rectangle.p2().y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to scale rectangles
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& scaleRectangle(const blNumberType& widthScale,
                                                 const blNumberType& heightScale,
                                                 blRectangle<blNumberType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blNumberType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blNumberType halfOfNewWidth = width(rectangle)/blNumberType(2) * widthScale;
    blNumberType halfOfNewHeight = height(rectangle)/blNumberType(2) * heightScale;

    // Place the x coords

    if(rectangle.p1().x() <= rectangle.p2().x())
    {
        rectangle.p1().x() = centerPoint.x() - halfOfNewWidth;
        rectangle.p2().x() = centerPoint.x() + halfOfNewWidth;
    }
    else
    {
        rectangle.p1().x() = centerPoint.x() + halfOfNewWidth;
        rectangle.p2().x() = centerPoint.x() - halfOfNewWidth;
    }

    // Place the y coords

    if(rectangle.p1().y() <= rectangle.p2().y())
    {
        rectangle.p1().y() = centerPoint.y() - halfOfNewHeight;
        rectangle.p2().y() = centerPoint.y() + halfOfNewHeight;
    }
    else
    {
        rectangle.p1().y() = centerPoint.y() + halfOfNewHeight;
        rectangle.p2().y() = centerPoint.y() - halfOfNewHeight;
    }

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to scale a rectangle
// while keeping its point P1 fixed
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& scaleRectangleWithP1Fixed(const blNumberType& widthScale,
                                                            const blNumberType& heightScale,
                                                            blRectangle<blNumberType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blNumberType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blNumberType newWidth = width(rectangle) * widthScale;
    blNumberType newHeight = height(rectangle) * heightScale;

    // Add the new width and height
    // to the point P1

    if(rectangle.p1().x() < rectangle.p2().x())
        rectangle.p2().x() = rectangle.p1().x() + newWidth;
    else
        rectangle.p2().x() = rectangle.p1().x() - newWidth;

    if(rectangle.p1().y() < rectangle.p2().y())
        rectangle.p2().y() = rectangle.p1().y() + newHeight;
    else
        rectangle.p2().y() = rectangle.p1().y() - newHeight;

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to scale a rectangle
// while keeping its point P2 fixed
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& scaleRectangleWithP2Fixed(const blNumberType& widthScale,
                                                            const blNumberType& heightScale,
                                                            blRectangle<blNumberType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blNumberType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blNumberType newWidth = width(rectangle) * widthScale;
    blNumberType newHeight = height(rectangle) * heightScale;

    // Add the new width and height
    // to the point P2

    if(rectangle.p2().x() > rectangle.p1().x())
        rectangle.p1().x() = rectangle.p2().x() - newWidth;
    else
        rectangle.p1().x() = rectangle.p2().x() + newWidth;

    if(rectangle.p2().y() > rectangle.p1().y())
        rectangle.p1().y() = rectangle.p2().y() - newHeight;
    else
        rectangle.p1().y() = rectangle.p2().y() + newHeight;

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to scale a rectangle's
// individual coordinates
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& scaleCoordinates(const blNumberType& xScale,
                                                   const blNumberType& yScale,
                                                   blRectangle<blNumberType>& rectangle)
{
    // Simply scale the x
    // and y coordinates
    // by the passed arguments

    rectangle.p1() *= xScale;
    rectangle.p1() *= yScale;
    rectangle.p2() *= xScale;
    rectangle.p2() *= yScale;

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to center a rectangle
// about a specified point
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& centerRectangle(const blPoint2d<blNumberType>& newCenter,
                                                  blRectangle<blNumberType>& rectangle)
{
    // Calculate the difference
    // between the new and old centers

    blPoint2d<blNumberType> translation = newCenter - center(rectangle);

    // Translate the rectangle
    // accordingly

    return translate(translation.x,translation.y,rectangle);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to flip a rectangle's coordinates
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& flipXCoords(blRectangle<blNumberType>& rectangle)
{
    std::swap(rectangle.p1().x(),rectangle.p2().x());

    return rectangle;
}


template<typename blNumberType>
inline blRectangle<blNumberType>& flipYCoords(blRectangle<blNumberType>& rectangle)
{
    std::swap(rectangle.p1().y(),rectangle.p2().y());

    return rectangle;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to map a point onto a rectangle
// Function assumes that the point coordinates vary
// from 0 to 1
// The point is then mapped onto an actual coordinate
// while lies somewhere in the specified rectangle
// Ex:  point P(0,0) would map to rectangle coordinate P1
// Ex:  point P(1,1) would map to rectangle coordinate P2
//-------------------------------------------------------------------
template<typename blNumberType,typename blNumberType2>
inline blPoint2d<blNumberType>& mapPointToRectangle(const blRectangle<blNumberType>& rectangleMap,
                                                    blPoint2d<blNumberType2>& pointToMap)
{
    pointToMap.x = static_cast<blNumberType2>(rectangleMap.p1().x() + static_cast<blNumberType>(pointToMap.x) * (rectangleMap.p2().x() - rectangleMap.p1().x()));
    pointToMap.y = static_cast<blNumberType2>(rectangleMap.p1().y() + static_cast<blNumberType>(pointToMap.y) * (rectangleMap.p2().y() - rectangleMap.p1().y()));

    return pointToMap;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Same function as above but this function
// maps a rectangle whose coordinates vary
// from 0 to 1 onto a specified rectangle
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& mapRectangleToRectangle(const blRectangle<blNumberType>& rectangleMap,
                                                          blRectangle<blNumberType>& rectangleToMap)
{
    mapPointToRectangle(rectangleMap,rectangleToMap.p1());
    mapPointToRectangle(rectangleMap,rectangleToMap.p2());

    return rectangleToMap;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to "zoom" where a "zoom rectangle" whose
// coordinates vary from 0 to 1 is mapped onto a rectangle
// and that rectangle's coordinates are changed so that now
// it is "zoomed"
//-------------------------------------------------------------------
template<typename blNumberType>
inline blRectangle<blNumberType>& zoomRectangle(const blRectangle<blNumberType>& zoomRectangle,
                                                blRectangle<blNumberType>& rectangleToZoom)
{
    // First we map the zoom
    // rectangle's coordinates
    // onto the rectangle to zoom

    blRectangle<blNumberType> rectangleToMap = zoomRectangle;

    mapRectangleToRectangle(rectangleToZoom,rectangleToMap);

    // Then we set the new rectangle's
    // zoomed coordinates

    rectangleToZoom = rectangleToMap;

    return rectangleToZoom;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Change the size of rectangle while
// keeping it centered where it currently is
//-------------------------------------------------------------------
template<typename blNumberType,typename blNumberType2>
inline blRectangle<blNumberType>& sizeRectangle(const blNumberType2& newWidth,
                                                const blNumberType2& newHeight,
                                                blRectangle<blNumberType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blNumberType> centerPoint = center(rectangle);

    // Place the x coords

    if(rectangle.p1().x() <= rectangle.p2().x())
    {
        rectangle.p1().x() = centerPoint.x() - blMathAPI::abs(static_cast<blNumberType>(newWidth)/2.0);
        rectangle.p2().x() = centerPoint.x() + blMathAPI::abs(static_cast<blNumberType>(newWidth)/2.0);
    }
    else
    {
        rectangle.p1().x() = centerPoint.x() + blMathAPI::abs(static_cast<blNumberType>(newWidth)/2.0);
        rectangle.p2().x() = centerPoint.x() - blMathAPI::abs(static_cast<blNumberType>(newWidth)/2.0);
    }

    // Place the y coords

    if(rectangle.p1().y() <= rectangle.p2().y())
    {
        rectangle.p1().y() = centerPoint.y() - blMathAPI::abs(static_cast<blNumberType>(newHeight)/2.0);
        rectangle.p2().y() = centerPoint.y() + blMathAPI::abs(static_cast<blNumberType>(newHeight)/2.0);
    }
    else
    {
        rectangle.p1().y() = centerPoint.y() + blMathAPI::abs(static_cast<blNumberType>(newHeight)/2.0);
        rectangle.p2().y() = centerPoint.y() - blMathAPI::abs(static_cast<blNumberType>(newHeight)/2.0);
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// output a rectangle
// to an output stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMathAPI::blRectangle<blNumberType>& rectangle)
{
    // We simply output the
    // components with a
    // space separating them

    os << rectangle.p1() << " " << rectangle.p2();

    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// input a rectangle
// from an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::istream& operator>>(std::istream& is,
                                blRectangle<blNumberType>& rectangle)
{
    if(!(is >> rectangle.p1()))
    {
        // Error -- Cound not read
        //          the p1 value

        return is;
    }

    if(!(is >> rectangle.p2()))
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
         typename blNumberType>
inline blStringIteratorType blConvertStringToNumber(const blStringIteratorType& beginIter,
                                                    const blStringIteratorType& endIter,
                                                    const blCharacterType& DecimalPointDelimiter,
                                                    blMathAPI::blRectangle<blNumberType>& ConvertedNumber,
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
                                                ConvertedNumber.p1(),
                                                NumberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the second
    // point

    newStringPosition = blConvertStringToNumber(newStringPosition,
                                                endIter,
                                                DecimalPointDelimiter,
                                                ConvertedNumber.p2(),
                                                NumberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_RECTANGLEOPERATIONS_HPP
