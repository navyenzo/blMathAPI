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
    
    size_t bucketIndex = 0;
    size_t bucketStep = srcDataSize / dstDataSize;

    auto previousBucketPoint = (*srcDataBegin);
    auto nextBucketAvgValue = previousBucketPoint;
    auto maxTriangleArea = previousBucketPoint;


    auto srcNextBucketIterator = srcDataBegin;
    auto srcCurrentBucketIterator = srcDataBegin;

    std::advance(srcNextBucketIterator,2*bucketStep);

    auto two = static_cast<decltype(previousBucketPoint)>(2);



    for(size_t bucketIndex = 0; bucketIndex < dstDataSize; bucketIndex += bucketStep)
    {
        // If we are in the first or
        // last buckets then we just
        // copy the first or last data
        // point

        if(bucketIndex == 0 || bucketIndex == (dstDataSize - 1))
            (*dstDataBegin) = (*srcDataBegin);
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

            for(size_t i = 0; i < bucketStep; ++i)
            {
                maxTriangleArea = std::max(maxTriangleArea,std::abs( (nextBucketAvgValue - previousBucketPoint) + two*(previousBucketPoint - (*srcCurrentBucketIterator)) ) / two);

                ++srcDataBegin;
            }

            // Advance to the next destination point

            ++dstDataBegin;
        }
    }
}
//-------------------------------------------------------------------


#endif // BL_DOWNSAMPLINGALGORITHMS_HPP
