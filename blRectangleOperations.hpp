#ifndef BL_RECTANGLEOPERATIONS_HPP
#define BL_RECTANGLEOPERATIONS_HPP


//-------------------------------------------------------------------
// FILE:            blRectangle.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Some useful functions to handle rectangles
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
// Functions used to calculate the width, height
// area and center of a rectangle
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType width(const blRectangle<blDataType>& rectangle)
{
    return std::abs(rectangle.p2().x() - rectangle.p1().x());
}


template<typename blDataType>
inline blDataType height(const blRectangle<blDataType>& rectangle)
{
    return std::abs(rectangle.p2().y() - rectangle.p1().y());
}


template<typename blDataType>
inline blDataType area(const blRectangle<blDataType>& rectangle)
{
    return width(rectangle)*height(rectangle);
}


template<typename blDataType>
inline blPoint2d<blDataType> center(const blRectangle<blDataType>& rectangle)
{
    return (rectangle.p1() + rectangle.p2())/blDataType(2);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to sord a rectangle's
// coordinates so that p1.x and p1.y are
// smaller than p2.x and p2.y
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& sortCoordinates(blRectangle<blDataType>& rectangle)
{
    // Sort x coordinates

    if(rectangle.p1().x() > rectangle.p2().x())
        std::swap(rectangle.p1().x(),rectangle.p2().x());

    // Sort y coordinates
    if(rectangle.p1().y() > rectangle.p2().y())
        std::swap(rectangle.p1().y(),rectangle.p2().y());

    return rectangle;
}


template<typename blDataType>
inline blRectangle<blDataType>& getSortedCoordinates(const blRectangle<blDataType>& rectangle)
{
    blRectangle<blDataType> sortedRectangle = rectangle;

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
template<typename blDataType>
inline blRectangle<blDataType>& clipXCoords(const blDataType& xMin,
                                            const blDataType& xMax,
                                            blRectangle<blDataType>& rectangle)
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


template<typename blDataType>
inline blRectangle<blDataType>& clipYCoords(const blDataType& yMin,
                                            const blDataType& yMax,
                                            blRectangle<blDataType>& rectangle)
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


template<typename blDataType>
inline blRectangle<blDataType>& clipCoords(const blDataType& xMin,
                                           const blDataType& yMin,
                                           const blDataType& xMax,
                                           const blDataType& yMax,
                                           blRectangle<blDataType>& rectangle)
{
    clipXCoords(xMin,xMax,rectangle);
    clipYCoords(yMin,yMax,rectangle);

    return rectangle;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to translated a rectangle
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& translate(const blDataType& xTranslation,
                                          const blDataType& yTranslation,
                                          blRectangle<blDataType>& rectangle)
{
    // Add xTranslation and
    // yTranslation to all coordinates

    rectangle.p1().x() += xTranslation;
    rectangle.p1().y() += xTranslation;
    rectangle.p2().x() += xTranslation;
    rectangle.p2().y() += xTranslation;

    return rectangle;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to move rectangles
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& moveByPlacingP1At(const blDataType& x,
                                                  const blDataType& y,
                                                  blRectangle<blDataType>& rectangle)
{
    return translate(x - rectangle.p1().x(),y - rectangle.p1().y(),rectangle);
}


template<typename blDataType>
inline blRectangle<blDataType>& moveRectangleByPlacingP2At(const blDataType& x,
                                                           const blDataType& y,
                                                           blRectangle<blDataType>& rectangle)
{
    return translateRectangle(x - rectangle.p2().x(),y - rectangle.p2().y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to scale rectangles
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& scaleRectangle(const blDataType& widthScale,
                                               const blDataType& heightScale,
                                               blRectangle<blDataType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blDataType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blDataType halfOfNewWidth = width(rectangle)/blDataType(2) * widthScale;
    blDataType halfOfNewHeight = height(rectangle)/blDataType(2) * heightScale;

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
template<typename blDataType>
inline blRectangle<blDataType>& scaleRectangleWithP1Fixed(const blDataType& widthScale,
                                                          const blDataType& heightScale,
                                                          blRectangle<blDataType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blDataType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blDataType newWidth = width(rectangle) * widthScale;
    blDataType newHeight = height(rectangle) * heightScale;

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
template<typename blDataType>
inline blRectangle<blDataType>& scaleRectangleWithP2Fixed(const blDataType& widthScale,
                                                          const blDataType& heightScale,
                                                          blRectangle<blDataType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blDataType> centerPoint = center(rectangle);

    // Calculate the new
    // scaled width and height

    blDataType newWidth = width(rectangle) * widthScale;
    blDataType newHeight = height(rectangle) * heightScale;

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
template<typename blDataType>
inline blRectangle<blDataType>& scaleCoordinates(const blDataType& xScale,
                                                 const blDataType& yScale,
                                                 blRectangle<blDataType>& rectangle)
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
template<typename blDataType>
inline blRectangle<blDataType>& centerRectangle(const blPoint2d<blDataType>& newCenter,
                                                blRectangle<blDataType>& rectangle)
{
    // Calculate the difference
    // between the new and old centers

    blPoint2d<blDataType> translation = newCenter - center(rectangle);

    // Translate the rectangle
    // accordingly

    return translate(translation.x,translation.y,rectangle);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to flip a rectangle's coordinates
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& flipXCoords(blRectangle<blDataType>& rectangle)
{
    std::swap(rectangle.p1().x(),rectangle.p2().x());

    return rectangle;
}


template<typename blDataType>
inline blRectangle<blDataType>& flipYCoords(blRectangle<blDataType>& rectangle)
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
template<typename blDataType,typename blDataType2>
inline blPoint2d<blDataType>& mapPointToRectangle(const blRectangle<blDataType>& rectangleMap,
                                                  blPoint2d<blDataType2>& pointToMap)
{
    pointToMap.x = static_cast<blDataType2>(rectangleMap.p1().x() + static_cast<blDataType>(pointToMap.x) * (rectangleMap.p2().x() - rectangleMap.p1().x()));
    pointToMap.y = static_cast<blDataType2>(rectangleMap.p1().y() + static_cast<blDataType>(pointToMap.y) * (rectangleMap.p2().y() - rectangleMap.p1().y()));

    return pointToMap;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Same function as above but this function
// maps a rectangle whose coordinates vary
// from 0 to 1 onto a specified rectangle
//-------------------------------------------------------------------
template<typename blDataType>
inline blRectangle<blDataType>& mapRectangleToRectangle(const blRectangle<blDataType>& rectangleMap,
                                                        blRectangle<blDataType>& rectangleToMap)
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
template<typename blDataType>
inline blRectangle<blDataType>& zoomRectangle(const blRectangle<blDataType>& zoomRectangle,
                                              blRectangle<blDataType>& rectangleToZoom)
{
    // First we map the zoom
    // rectangle's coordinates
    // onto the rectangle to zoom

    blRectangle<blDataType> rectangleToMap = zoomRectangle;

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
template<typename blDataType,typename blDataType2>
inline blRectangle<blDataType>& sizeRectangle(const blDataType2& newWidth,
                                              const blDataType2& newHeight,
                                              blRectangle<blDataType>& rectangle)
{
    // Get the center point
    // of this rectangle

    blPoint2d<blDataType> centerPoint = center(rectangle);

    // Place the x coords

    if(rectangle.p1().x() <= rectangle.p2().x())
    {
        rectangle.p1().x() = centerPoint.x() - std::abs(static_cast<blDataType>(newWidth)/2.0);
        rectangle.p2().x() = centerPoint.x() + std::abs(static_cast<blDataType>(newWidth)/2.0);
    }
    else
    {
        rectangle.p1().x() = centerPoint.x() + std::abs(static_cast<blDataType>(newWidth)/2.0);
        rectangle.p2().x() = centerPoint.x() - std::abs(static_cast<blDataType>(newWidth)/2.0);
    }

    // Place the y coords

    if(rectangle.p1().y() <= rectangle.p2().y())
    {
        rectangle.p1().y() = centerPoint.y() - std::abs(static_cast<blDataType>(newHeight)/2.0);
        rectangle.p2().y() = centerPoint.y() + std::abs(static_cast<blDataType>(newHeight)/2.0);
    }
    else
    {
        rectangle.p1().y() = centerPoint.y() + std::abs(static_cast<blDataType>(newHeight)/2.0);
        rectangle.p2().y() = centerPoint.y() - std::abs(static_cast<blDataType>(newHeight)/2.0);
    }
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

    os << rectangle.p1() << " " << rectangle.p2();

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

#endif // BL_RECTANGLEOPERATIONS_HPP
