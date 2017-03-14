#ifndef BL_DOWNSAMPLINGALGORITHMS_HPP
#define BL_DOWNSAMPLINGALGORITHMS_HPP


//-------------------------------------------------------------------
// FILE:            blDownsamplingAlgorithms.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A collection of "downsampling"
//                  algorithms for visualizing
//                  large data sets
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
//
// DATE CREATED:    Feb/21/2014
//
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file and sub-files
//-------------------------------------------------------------------
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
                             const size_t& srcDataSize,
                             dstDataIteratorType dstDataBegin,
                             const size_t& dstDataSize)
{
    // First we calculate
    // the downsampling step

    double downsamplingStep = double(srcDataSize)/double(dstDataSize);

    size_t previousSourceSamplingIndex = 0;
    double currentSourceSamplingIndex = 0;

    // Then we step through
    // source data and pick
    // every "DownsamplingStep"
    // data point and save it
    // into the destination
    // data set

    for(size_t i = 0; i < dstDataSize; ++i)
    {
        // Sample the
        // data point

        (*dstDataBegin) = (*srcDataBegin);

        // Calculate the
        // sampling indices

        currentSourceSamplingIndex += downsamplingStep;

        // Advance the
        // iterators

        std::advance(srcDataBegin,size_t(currentSourceSamplingIndex) - previousSourceSamplingIndex);

        ++dstDataBegin;

        // Recalculate the
        // previous sampling
        // index

        previousSourceSamplingIndex += size_t(currentSourceSamplingIndex - double(previousSourceSamplingIndex));
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
                                        const size_t& srcDataSize,
                                        dstDataIteratorType dstDataBegin,
                                        const size_t& dstDataSize)
{
    if(srcDataSize <= 0 || dstDataSize <= 0)
    {
        // We have no data to downsample

        return;
    }
    else if(dstDataSize >= srcDataSize)
    {
        // In this case we simply copy
        // the source data into the
        // destination data

        for(size_t i = 0,j = 0; i < srcDataSize && j < dstDataSize; ++i,++j)
        {
            (*dstDataBegin) = (*srcDataBegin);

            ++srcDataBegin;
            ++dstDataBegin;
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

    size_t bucketStep = srcDataSize / dstDataSize;

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

    for(size_t bucketIndex = 0; bucketIndex < dstDataSize; ++bucketIndex)
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

            for(size_t i = 0; i < bucketStep; ++i)
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

            for(size_t i = 0; i < bucketStep; ++i)
            {
                currentTriangleArea = std::abs( (nextBucketAvgValue - previousBucketPoint) + two*(previousBucketPoint - (*srcCurrentBucketIterator)) ) / two;

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
                                        const size_t& srcDataSize,
                                        xDstDataIteratorType xDstDataBegin,
                                        yDstDataIteratorType yDstDataBegin,
                                        const size_t& dstDataSize)
{
    if(srcDataSize <= 0 || dstDataSize <= 0)
    {
        // We have no data to downsample

        return;
    }
    else if(dstDataSize >= srcDataSize)
    {
        // In this case we simply copy
        // the source data into the
        // destination data

        for(size_t i = 0,j = 0; i < srcDataSize && j < dstDataSize; ++i,++j)
        {
            (*xDstDataBegin) = (*xSrcDataBegin);
            (*yDstDataBegin) = (*ySrcDataBegin);

            ++xSrcDataBegin;
            ++ySrcDataBegin;

            ++xDstDataBegin;
            ++yDstDataBegin;
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

    size_t bucketStep = srcDataSize / dstDataSize;

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

    for(size_t bucketIndex = 0; bucketIndex < dstDataSize; ++bucketIndex)
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

            for(size_t i = 0; i < bucketStep; ++i)
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

            for(size_t i = 0; i < bucketStep; ++i)
            {
                currentTriangleArea = std::abs( (yNextBucketAvgValue - yPreviousBucketPoint) + two*(yPreviousBucketPoint - (*ySrcCurrentBucketIterator)) ) / two;

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


#endif // BL_DOWNSAMPLINGALGORITHMS_HPP
