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

    // First we copy the first
    // and last data points

    (*dstDataBegin) = (*srcDataBegin);

    auto srcDataIterator = srcDataBegin;
    auto dstDataIterator = dstDataBegin;

    std::advance(srcDataBegin,srcDataSize - size_t(1));
    ++dstDataBegin;

    (*dstDataBegin) = (*srcDataBegin);

    if(dstDataSize == 2)
    {
        // We are done

        return;
    }

    // Now we got all the special
    // cases out of the way and
    // we've already copied the
    // first and last data points
}
//-------------------------------------------------------------------


#endif // BL_DOWNSAMPLINGALGORITHMS_HPP
