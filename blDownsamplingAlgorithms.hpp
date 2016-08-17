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
// FUNCTION:            blSimpleDownsample
//
// ARGUMENTS:           - SrcDataBegin
//                      - SrcDataSize
//                      - DstDataBegin
//                      - DstDataSize
//
// TEMPLATE ARGUMENTS:  - blSrcDataIteratorType
//                      - blDstDataIteratorType
//
// PURPOSE:             - This function downsamples the specified
//                        data by grabbing every nth point
//
// DEPENDENCIES:        None
//
// NOTES:
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
// FUNCTION:            blModeMedianBucketDownsample
//
// ARGUMENTS:           - SrcDataBegin
//                      - SrcDataSize
//                      - DstDataBegin
//                      - DstDataSize
//
// TEMPLATE ARGUMENTS:  - blSrcDataIteratorType
//                      - blDstDataIteratorType
//
// PURPOSE:             - This function downsamples the specified
//                        data by grabbing every nth point
//
// DEPENDENCIES:        None
//
// NOTES:
//-------------------------------------------------------------------
template<typename blSrcDataIteratorType,
         typename blDstDataIteratorType>

inline void blModeMedianBucketDownsample(blSrcDataIteratorType SrcDataBegin,
                                         const size_t& SrcDataSize,
                                         blDstDataIteratorType DstDataBegin,
                                         const size_t& DstDataSize)
{
    // typedef typename std::iterator_traits<blSrcDataIteratorType>::value_type        blDataType;

    if(SrcDataSize <= DstDataSize)
    {
        // In this case, the
        // source data size
        // is equal or less
        // to the destination
        // data so we use
        // the simple downsampling
        // algorithm

        blSimpleDownsample(SrcDataBegin,
                           SrcDataSize,
                           DstDataBegin,
                           DstDataSize);

        return;
    }
}
//-------------------------------------------------------------------


#endif // BL_DOWNSAMPLINGALGORITHMS_HPP
