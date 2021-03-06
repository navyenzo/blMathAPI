#ifndef BL_DOWNSAMPLINGALGORITHMS_HPP
#define BL_DOWNSAMPLINGALGORITHMS_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A collection of "downsampling" algorithms for
///                 visualizing and/or analyzing large data sets
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
#include <iterator>
#include "blNumericFunctions.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function downsamples a
// source into the destination container
// simply by skipping every so many values
//-------------------------------------------------------------------
template<typename srcDataIteratorType,
         typename dstDataIteratorType>

inline void simpleDownsample(srcDataIteratorType srcDataBegin,
                             const std::size_t& srcDataSize,
                             dstDataIteratorType dstDataBegin,
                             const std::size_t& dstDataSize)
{
    // First we calculate
    // the downsampling step

    double downsamplingStep = double(srcDataSize)/double(dstDataSize);

    std::size_t previousSourceSamplingIndex = 0;
    double currentSourceSamplingIndex = 0;

    // Then we step through
    // source data and pick
    // every "DownsamplingStep"
    // data point and save it
    // into the destination
    // data set

    for(std::size_t i = 0; i < dstDataSize; ++i)
    {
        // Sample the
        // data point

        (*dstDataBegin) = (*srcDataBegin);

        // Calculate the
        // sampling indices

        currentSourceSamplingIndex += downsamplingStep;

        // Advance the
        // iterators

        std::advance(srcDataBegin,std::size_t(currentSourceSamplingIndex) - previousSourceSamplingIndex);

        ++dstDataBegin;

        // Recalculate the
        // previous sampling
        // index

        previousSourceSamplingIndex += std::size_t(currentSourceSamplingIndex - double(previousSourceSamplingIndex));
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function downsamples a source
// into the destination container by use of the
// Largest-Triangle-Three-Buckets algorithm
//-------------------------------------------------------------------
template<typename srcDataIteratorType,
         typename dstDataIteratorType>

inline void largestTriangleThreeBuckets(srcDataIteratorType srcDataBegin,
                                        const std::size_t& srcDataSize,
                                        dstDataIteratorType dstDataBegin,
                                        const std::size_t& dstDataSize)
{
    if(srcDataSize <= 0 || dstDataSize <= 0)
    {
        // We have no data to downsample

        return;
    }
    else if(dstDataSize >= srcDataSize)
    {
        // In this case we are trying to upsample
        // the source data, we do this using
        // a linear sampling

        double srcStep = double(srcDataSize)/double(dstDataSize);

        int dstIndex = 0;

        int srcIndex = 0;
        double idealSrcIndex = 0;

        while(srcIndex < srcDataSize && dstIndex < dstDataSize)
        {
            // Copy the data point

            (*dstDataBegin) = (*srcDataBegin);

            // Move forward in the destination array

            ++dstDataBegin;

            // Calculate how much to move forward
            // in the source array

            idealSrcIndex += srcStep;

            if(int(idealSrcIndex) > srcIndex)
            {
                srcIndex = int(idealSrcIndex);

                ++srcDataBegin;
            }
        }

        return;
    }
    else if(dstDataSize == 1)
    {
        // In this case we just
        // copy the first data point

        (*dstDataBegin) = (*srcDataBegin);

        return;
    }



    // Now we got all the special
    // cases out of the way



    // Calculate the size of each bucket

    std::size_t bucketStep = srcDataSize / dstDataSize;

    // Create temporary point values
    // used to find the point to sample

    auto previousBucketPoint = (*srcDataBegin);
    auto nextBucketAvgValue = previousBucketPoint;

    // Temporary variables used to find
    // the max triangle area formed by
    // the sampled points

    auto maxTriangleArea = previousBucketPoint;
    auto currentTriangleArea = maxTriangleArea;

    // Iterators used to move through the
    // source data buckets at a time

    auto srcCurrentBucketIterator = srcDataBegin;

    auto srcNextBucketIterator = srcDataBegin;
    std::advance(srcNextBucketIterator,1 + bucketStep);

    // Value of 2 used to calculate
    // the triangle area

    auto two = static_cast<decltype(previousBucketPoint)>(2);



    // Let's step through the data and
    // sample the points of interest

    for(std::size_t bucketIndex = 0; bucketIndex < dstDataSize; ++bucketIndex)
    {
        // If we are in the first or
        // last buckets then we just
        // copy the first or last data
        // point

        if(bucketIndex == 0)
        {
            (*dstDataBegin) = (*srcDataBegin);
            ++srcCurrentBucketIterator;
        }
        else if(bucketIndex == dstDataSize - 1)
        {
            std::advance(srcDataBegin,srcDataSize - 1);
            (*dstDataBegin) = (*srcDataBegin);
        }
        else
        {
            // Calculate the average value
            // of the next bucket

            nextBucketAvgValue = 0;

            for(std::size_t i = 0; i < bucketStep; ++i)
            {
                nextBucketAvgValue += (*srcNextBucketIterator);
                ++srcNextBucketIterator;
            }

            nextBucketAvgValue /= static_cast<decltype(nextBucketAvgValue)>(bucketStep);

            // Calculate which point gives
            // the triangle with the biggest
            // area and choose that point as
            // the point for this current bucket

            maxTriangleArea = 0;
            currentTriangleArea = 0;

            for(std::size_t i = 0; i < bucketStep; ++i)
            {
                currentTriangleArea = blMathAPI::abs( (nextBucketAvgValue - previousBucketPoint) + two*(previousBucketPoint - (*srcCurrentBucketIterator)) ) / two;

                if(currentTriangleArea > maxTriangleArea)
                {
                    maxTriangleArea = currentTriangleArea;
                    (*dstDataBegin) = (*srcCurrentBucketIterator);
                }

                ++srcCurrentBucketIterator;
            }
        }

        // Advance to the next destination point

        ++dstDataBegin;
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function downsamples a source
// into the destination container by use of the
// Largest-Triangle-Three-Buckets algorithm like above
// The difference is that this function takes an x-axis
// as well as y-axis and samples the y-axis while also
// taking the x-axis points corresponding to the sampled
// y-axis points
//-------------------------------------------------------------------
template<typename xSrcDataIteratorType,
         typename ySrcDataIteratorType,
         typename xDstDataIteratorType,
         typename yDstDataIteratorType>

inline void largestTriangleThreeBuckets(xSrcDataIteratorType xSrcDataBegin,
                                        ySrcDataIteratorType ySrcDataBegin,
                                        const std::size_t& srcDataSize,
                                        xDstDataIteratorType xDstDataBegin,
                                        yDstDataIteratorType yDstDataBegin,
                                        const std::size_t& dstDataSize)
{
    if(srcDataSize <= 0 || dstDataSize <= 0)
    {
        // We have no data to downsample

        return;
    }
    else if(dstDataSize >= srcDataSize)
    {
        // In this case we are trying to upsample
        // the source data, we do this using
        // a linear sampling

        double srcStep = double(srcDataSize)/double(dstDataSize);

        int dstIndex = 0;

        int srcIndex = 0;
        double idealSrcIndex = 0;

        while(srcIndex < srcDataSize && dstIndex < dstDataSize)
        {
            // Copy the data point

            (*xDstDataBegin) = (*xSrcDataBegin);
            (*yDstDataBegin) = (*ySrcDataBegin);

            // Move forward in the destination array

            ++xDstDataBegin;
            ++yDstDataBegin;

            // Calculate how much to move forward
            // in the source array

            idealSrcIndex += srcStep;

            if(int(idealSrcIndex) > srcIndex)
            {
                srcIndex = int(idealSrcIndex);

                ++xSrcDataBegin;
                ++ySrcDataBegin;
            }
        }

        return;
    }
    else if(dstDataSize == 1)
    {
        // In this case we just
        // copy the first data point

        (*xDstDataBegin) = (*xSrcDataBegin);
        (*yDstDataBegin) = (*ySrcDataBegin);

        return;
    }



    // Now we got all the special
    // cases out of the way



    // Calculate the size of each bucket

    std::size_t bucketStep = srcDataSize / dstDataSize;

    // Create temporary point values
    // used to find the point to sample

    auto yPreviousBucketPoint = (*ySrcDataBegin);
    auto yNextBucketAvgValue = yPreviousBucketPoint;

    // Temporary variables used to find
    // the max triangle area formed by
    // the sampled points

    auto maxTriangleArea = yPreviousBucketPoint;
    auto currentTriangleArea = maxTriangleArea;

    // Iterators used to move through the
    // source data n buckets at a time

    auto xSrcCurrentBucketIterator = xSrcDataBegin;
    auto ySrcCurrentBucketIterator = ySrcDataBegin;

    auto ySrcNextBucketIterator = ySrcDataBegin;
    std::advance(ySrcNextBucketIterator,1 + bucketStep);

    // Value of 2 used to calculate
    // the triangle area

    auto two = static_cast<decltype(yPreviousBucketPoint)>(2);



    // Let's step through the data and
    // sample the points of interest

    for(std::size_t bucketIndex = 0; bucketIndex < dstDataSize; ++bucketIndex)
    {
        // If we are in the first or
        // last buckets then we just
        // copy the first or last data
        // point

        if(bucketIndex == 0)
        {
            (*xDstDataBegin) = (*xSrcDataBegin);
            (*yDstDataBegin) = (*ySrcDataBegin);

            ++xSrcCurrentBucketIterator;
            ++ySrcCurrentBucketIterator;
        }
        else if(bucketIndex == dstDataSize - 1)
        {
            std::advance(xSrcDataBegin,srcDataSize - 1);
            std::advance(ySrcDataBegin,srcDataSize - 1);

            (*xDstDataBegin) = (*xSrcDataBegin);
            (*yDstDataBegin) = (*ySrcDataBegin);
        }
        else
        {
            // Calculate the average value
            // of the next bucket

            yNextBucketAvgValue = 0;

            for(std::size_t i = 0; i < bucketStep; ++i)
            {
                yNextBucketAvgValue += (*ySrcNextBucketIterator);
                ++ySrcNextBucketIterator;
            }

            yNextBucketAvgValue /= static_cast<decltype(yNextBucketAvgValue)>(bucketStep);

            // Calculate which point gives
            // the triangle with the biggest
            // area and choose that point as
            // the point for this current bucket

            maxTriangleArea = 0;
            currentTriangleArea = 0;

            for(std::size_t i = 0; i < bucketStep; ++i)
            {
                currentTriangleArea = blMathAPI::abs( (yNextBucketAvgValue - yPreviousBucketPoint) + two*(yPreviousBucketPoint - (*ySrcCurrentBucketIterator)) ) / two;

                if(currentTriangleArea > maxTriangleArea)
                {
                    maxTriangleArea = currentTriangleArea;

                    (*xDstDataBegin) = (*xSrcCurrentBucketIterator);
                    (*yDstDataBegin) = (*ySrcCurrentBucketIterator);
                }

                ++xSrcCurrentBucketIterator;
                ++ySrcCurrentBucketIterator;
            }
        }

        // Advance to the next destination point

        ++xDstDataBegin;
        ++yDstDataBegin;
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_DOWNSAMPLINGALGORITHMS_HPP
