#ifndef BL_BUFFERALGORITHMS_HPP
#define BL_BUFFERALGORITHMS_HPP


//-------------------------------------------------------------------
// FILE:            blBufferAlgorithms.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A collection of simple algorithms
//                  I developed to parse data buffers
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
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
// The following functions can be used to:
// -- Read from a stream into a buffer/variable
//    of any type
// -- Write from a buffer/variable of
//    any type into a stream
//
// It assumes the following:
//
// -- stream defines the functions: "read" and "write" that look
//    like the iostream functions
//
// -- buffer defines data() function that returns pointer
//    to its first element
//
// -- buffer defines size() function that returns
//    the size/length of the buffer
//-------------------------------------------------------------------
template<typename blInputStreamType,
         typename blValueType>

inline blInputStreamType& readValue(blInputStreamType& is,blValueType& value)
{
    is.read(reinterpret_cast<char*>(&value),sizeof(value));
    return is;
}



template<typename blInputStreamType,
         typename blBufferType>

inline blInputStreamType& readBuffer(blInputStreamType& is,blBufferType& buffer)
{
    is.read(reinterpret_cast<char*>(buffer.data()),sizeof(buffer.data()[0])*buffer.size());
    return is;
}



template<typename blInputStreamType,
         typename blBufferType>

inline blInputStreamType& readBuffer(blInputStreamType& is,blBufferType& buffer,const int& bufferLength)
{
    is.read(reinterpret_cast<char*>(buffer.data()),sizeof(buffer.data()[0])*bufferLength);
    return is;
}



template<typename blOutputStreamType,
         typename blValueType>

inline blOutputStreamType& writeValue(blOutputStreamType& os,const blValueType& value)
{
    os.write(reinterpret_cast<const char*>(&value),sizeof(value));
    return os;
}



template<typename blOutputStreamType,
         typename blBufferType>

inline blOutputStreamType& writeBuffer(blOutputStreamType& os,const blBufferType& buffer)
{
    os.write(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*buffer.size());
    return os;
}



template<typename blOutputStreamType,
         typename blBufferType>

inline blOutputStreamType& writeBuffer(blOutputStreamType& os,const blBufferType& buffer,const int& bufferLength)
{
    os.write(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*bufferLength);
    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function reads from a specified
// input stream and write the information into a
// specified output stream using a specified buffer
//
// -- The function assumes that the streams define
//    the "read", "write" and "gcount" functions
//
// -- The function also assumes that the buffer
//    defines the "operator[]" and "size" functions
//-------------------------------------------------------------------
template<typename blInputStreamType,
         typename blOutputStreamType,
         typename blBufferType>

inline void readFromStreamWriteToStream(blInputStreamType& inputStream,
                                        blOutputStreamType& outputStream,
                                        blBufferType& buffer)
{
    // Variable used to know how
    // many bytes were read from
    // the input stream during
    // the last read

    int numberOfBytesRead = 1;



    // Keep reading/writing until
    // no more bytes are read

    if(buffer.size() > 0)
    {
        while(numberOfBytesRead > 0)
        {
            inputStream.read(reinterpret_cast<char*>(&buffer[0]),sizeof(buffer[0]) * buffer.size());

            numberOfBytesRead = inputStream.gcount();

            outputStream.write(reinterpret_cast<char*>(&buffer[0]),numberOfBytesRead);
        }
    }



    // We're done

    return;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function checks
// two buffers to see if they are
// partially equal
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline bool isPartiallyEqual(blBuffer1IteratorType beginOfBufferToCheck,
                             const blBuffer1IteratorType& endOfBufferToCheck,
                             blBuffer2IteratorType beginOfBufferToCheckAgainst,
                             const blBuffer2IteratorType& endOfBufferToCheckAgainst)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer or
    // until two elements
    // don't match

    while((beginOfBufferToCheck != endOfBufferToCheck) &&
          (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst))
    {
        if(!(*beginOfBufferToCheck == *beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // If the first buffer
    // hasn't reached its
    // end, then it's not
    // partially equal

    if(beginOfBufferToCheck != endOfBufferToCheck)
        return false;
    else
        return true;
}


template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blPredicateFunctorType>
inline bool isPartiallyEqual(blBuffer1IteratorType beginOfBufferToCheck,
                             const blBuffer1IteratorType& endOfBufferToCheck,
                             blBuffer2IteratorType beginOfBufferToCheckAgainst,
                             const blBuffer2IteratorType& endOfBufferToCheckAgainst,
                             const blPredicateFunctorType& predicateFunctor)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer or
    // until two elements
    // don't match

    while((beginOfBufferToCheck != endOfBufferToCheck) &&
          (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst))
    {
        if(!predicateFunctor(*beginOfBufferToCheck,*beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // If the first buffer
    // hasn't reached its
    // end, then it's not
    // partially equal

    if(beginOfBufferToCheck != endOfBufferToCheck)
        return false;
    else
        return true;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions check if
// two buffers are equal
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType>

inline bool isEqual(blBuffer1IteratorType beginOfBufferToCheck,
                    const blBuffer1IteratorType& endOfBufferToCheck,
                    blBuffer2IteratorType beginOfBufferToCheckAgainst,
                    const blBuffer2IteratorType& endOfBufferToCheckAgainst)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer.
    // If we don't reach
    // the ends of both
    // buffers at the same
    // time, then they are
    // not equal

    while( (beginOfBufferToCheck != endOfBufferToCheck) &&
           (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst) )
    {
        if(!(*beginOfBufferToCheck == *beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // Let's make sure that
    // the ends of both
    // buffers have been
    // reached, otherwise
    // we return false.

    if( (beginOfBufferToCheck == endOfBufferToCheck) &&
        (beginOfBufferToCheckAgainst == endOfBufferToCheckAgainst) )
    {
        return true;
    }
    else
    {
        return false;
    }
}


template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blPredicateFunctorType>

inline bool isEqual(blBuffer1IteratorType beginOfBufferToCheck,
                    const blBuffer1IteratorType& endOfBufferToCheck,
                    blBuffer2IteratorType beginOfBufferToCheckAgainst,
                    const blBuffer2IteratorType& endOfBufferToCheckAgainst,
                    const blPredicateFunctorType& predicateFunctor)
{
    // Loop through every
    // element until we
    // reach the end of
    // either buffer.
    // If we don't reach
    // the ends of both
    // buffers at the same
    // time, then they are
    // not equal

    while( (beginOfBufferToCheck != endOfBufferToCheck) &&
           (beginOfBufferToCheckAgainst != endOfBufferToCheckAgainst) )
    {
        if(!predicateFunctor(*beginOfBufferToCheck,*beginOfBufferToCheckAgainst))
        {
            return false;
        }

        ++beginOfBufferToCheck;
        ++beginOfBufferToCheckAgainst;
    }

    // Let's make sure that
    // the ends of both
    // buffers have been
    // reached, otherwise
    // we return false.

    if( (beginOfBufferToCheck == endOfBufferToCheck) &&
        (beginOfBufferToCheckAgainst == endOfBufferToCheckAgainst) )
    {
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function copies content
// from input buffer to output buffer
// stopping whenever it reaches the end
// of either buffer
//-------------------------------------------------------------------
template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blIntegerType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const blIntegerType& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const blIntegerType& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    blIntegerType numberOfInputRepeats = 0;
    blIntegerType numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }

    return currentOutputIter;
}


template<typename blBuffer1IteratorType,
         typename blBuffer2IteratorType,
         typename blIntegerType>

inline blBuffer2IteratorType copy(const blBuffer1IteratorType& inputBegin,
                                  const blBuffer1IteratorType& inputEnd,
                                  const blBuffer2IteratorType& outputBegin,
                                  const blBuffer2IteratorType& outputEnd,
                                  const blIntegerType& numberOfTimesToCycleOverInputIfInputIteratorIsCyclic,
                                  const blIntegerType& numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic,
                                  blBuffer1IteratorType& inputBufferPlaceAfterLastCopiedElement)
{
    auto currentInputIter = inputBegin;
    auto currentOutputIter = outputBegin;

    blIntegerType numberOfInputRepeats = 0;
    blIntegerType numberOfOutputRepeats = 0;

    while( (currentInputIter != inputEnd) &&
           (currentOutputIter != outputEnd) &&
           (numberOfInputRepeats <= numberOfTimesToCycleOverInputIfInputIteratorIsCyclic) &&
           (numberOfOutputRepeats <= numberOfTimesToCycleOverOutputIfOutputIteratorIsCyclic) )
    {
        (*currentOutputIter) = (*currentInputIter);

        ++currentInputIter;
        ++currentOutputIter;

        if(currentInputIter == inputBegin)
            ++numberOfInputRepeats;

        if(currentOutputIter == outputBegin)
            ++numberOfOutputRepeats;
    }

    inputBufferPlaceAfterLastCopiedElement = currentInputIter;

    return currentOutputIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function searches for tokens
// in a buffer
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType>

inline blBufferIteratorType find(const blBufferIteratorType& beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}


template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blBufferIteratorType find(blBufferIteratorType beginIter,
                                 const blBufferIteratorType& endIter,
                                 const blTokenType& token,
                                 const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic,
                                 const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor((*currentIter),token))
        {
            return currentIter;
        }

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    return endIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions look for the
// last occurrence of a specified token
// in a buffer
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType>

inline blBufferIteratorType findLast(const blBufferIteratorType& beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if((*currentIter) == token)
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}


template<typename blTokenType,
         typename blBufferIteratorType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blBufferIteratorType findLast(const blBufferIteratorType& beginIter,
                                     const blBufferIteratorType& endIter,
                                     const blTokenType& token,
                                     const blIntegerType& numberOfTimesToCycleIfIteratorIsCyclic,
                                     const blPredicateFunctorType& predicateFunctor)
{
    blBufferIteratorType currentIter = beginIter;

    blBufferIteratorType iterToLastOccurrence = currentIter;

    blIntegerType numberOfRepeats = 0;

    while(currentIter != endIter &&
          numberOfRepeats <= numberOfTimesToCycleIfIteratorIsCyclic)
    {
        if(predicateFunctor(*currentIter,token))
            iterToLastOccurrence = currentIter;

        ++currentIter;

        if(currentIter == beginIter)
            ++numberOfRepeats;
    }

    if((*iterToLastOccurrence) == token)
        return iterToLastOccurrence;
    else
        return endIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions count the number of
// data rows in a buffer by searching for "data row"
// tokens in the buffer
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType>

inline size_t countDataRows(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter,
                            const blTokenType& rowToken,
                            const bool& shouldZeroLengthRowsBeCounted)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case there
        // are no rows

        return size_t(0);
    }

    // Iterators used to
    // find the tokens in
    // the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The total number
    // of rows found by
    // this function

    size_t totalNumberOfRows = size_t(0);

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // we do not want
            // to count this
            // as a data row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the total
            // number of rows

            ++totalNumberOfRows;

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;

            // In case of circular
            // iterators we might
            // be back to the
            // beginning, so we
            // quit in that case

            if(firstTokenIterator == beginIter)
                break;
        }
    }

    // We're done counting

    return totalNumberOfRows;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blPredicateFunctorType>

inline size_t countDataRows(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter,
                            const blTokenType& rowToken,
                            const bool& shouldZeroLengthRowsBeCounted,
                            const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case there
        // are no rows

        return size_t(0);
    }

    // Iterators used to
    // find the tokens in
    // the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The total number
    // of rows found by
    // this function

    size_t totalNumberOfRows = size_t(0);

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // we do not want
            // to count this
            // as a data row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the total
            // number of rows

            ++totalNumberOfRows;

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;

            // In case of circular
            // iterators we might
            // be back to the
            // beginning, so we
            // quit in that case

            if(firstTokenIterator == beginIter)
                break;
        }
    }

    // We're done counting

    return totalNumberOfRows;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions find data rows in a
// buffer by searching for the specified row
// token and then count the length of each row
// to find the length of the longest one
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType>

inline size_t findLengthOfLongestDataRow(const blDataIteratorType& beginIter,
                                         const blDataIteratorType& endIter,
                                         const blTokenType& rowToken)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return size_t(0);
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;

    // The length of the
    // longest data row

    size_t longestLength = 0;

    // The length of the
    // current data row

    size_t lengthOfCurrentRow = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        // Calculate the
        // length of the
        // current data row

        if(firstTokenIterator != secondTokenIterator)
            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator) - 1;
        else
            lengthOfCurrentRow = 0;

        // Compare the lengths

        if(lengthOfCurrentRow > longestLength)
        {
            longestLength = lengthOfCurrentRow;
        }

        firstTokenIterator = secondTokenIterator;

        // Advance the iterator
        // if we've not reached
        // the end yet

        if(firstTokenIterator != endIter)
            ++firstTokenIterator;

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    // We're done
    // counting

    return longestLength;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blPredicateFunctorType>

inline size_t findLengthOfLongestDataRow(const blDataIteratorType& beginIter,
                                         const blDataIteratorType& endIter,
                                         const blTokenType& rowToken,
                                         const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs
    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return size_t(0);
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;

    // The length of the
    // longest data row

    size_t longestLength = 0;

    // The length of the
    // current data row

    size_t lengthOfCurrentRow = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        // Calculate the
        // length of the
        // current data row

        if(firstTokenIterator != secondTokenIterator)
            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator) - 1;
        else
            lengthOfCurrentRow = 0;

        // Compare the lengths

        if(lengthOfCurrentRow > longestLength)
        {
            longestLength = lengthOfCurrentRow;
        }

        firstTokenIterator = secondTokenIterator;

        // Advance the iterator
        // if we've not reached
        // the end yet

        if(firstTokenIterator != endIter)
            ++firstTokenIterator;

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    // We're done
    // counting

    return longestLength;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions count the total
// number of rows in a buffer together with
// the length of the longest row
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType countDataRowsAndLongestRowLength(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           blIntegerType& totalNumberOfRows,
                                                           blIntegerType& lengthOfLongestRow)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return endIter;
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;
    blDataIteratorType iteratorToBeginningOfLongestDataRow;

    // The length of the
    // longest data row

    lengthOfLongestRow = 0;

    // The length of the
    // current data row

    blIntegerType lengthOfCurrentRow = 0;

    // The total
    // number of
    // rows

    totalNumberOfRows = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this we don't
            // count the zero
            // sized row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the
            // total number
            // of rows

            ++totalNumberOfRows;

            // Calculate the
            // length of
            // the current
            // data row

            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator);

            // Compare the
            // lengths

            if(lengthOfCurrentRow > lengthOfLongestRow)
            {

                lengthOfLongestRow = lengthOfCurrentRow;
                iteratorToBeginningOfLongestDataRow = firstTokenIterator;
            }

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    return iteratorToBeginningOfLongestDataRow;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType,
         typename blPredicateFunctorType>

inline blDataIteratorType countDataRowsAndLongestRowLength(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           blIntegerType& totalNumberOfRows,
                                                           blIntegerType& lengthOfLongestRow,
                                                           const blPredicateFunctorType& predicateFunctor)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // Error -- Passed a zero
        //          length buffer

        return endIter;
    }

    // The iterators to
    // the tokens found
    // in the data buffer

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = endIter;
    blDataIteratorType iteratorToBeginningOfLongestDataRow;

    // The length of the
    // longest data row

    lengthOfLongestRow = 0;

    // The length of the
    // current data row

    blIntegerType lengthOfCurrentRow = 0;

    // The total
    // number of
    // rows

    totalNumberOfRows = 0;

    while(firstTokenIterator != endIter)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0,
                                   predicateFunctor);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this we don't
            // count the zero
            // sized row

            ++firstTokenIterator;
        }
        else
        {
            // Increse the
            // total number
            // of rows

            ++totalNumberOfRows;

            // Calculate the
            // length of
            // the current
            // data row

            lengthOfCurrentRow = std::distance(firstTokenIterator,secondTokenIterator);

            // Compare the
            // lengths

            if(lengthOfCurrentRow > lengthOfLongestRow)
            {

                lengthOfLongestRow = lengthOfCurrentRow;
                iteratorToBeginningOfLongestDataRow = firstTokenIterator;
            }

            firstTokenIterator = secondTokenIterator;

            // Advance the iterator
            // if we've not reached
            // the end yet

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }

        // In case of circular
        // iterators we might
        // be back to the
        // beginning, so we
        // quit in that case

        if(firstTokenIterator == beginIter)
            break;
    }

    return iteratorToBeginningOfLongestDataRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// THe following functions find the corresponding
// row and column position of the user specified
// buffer position
//
// NOTES:               For example:  We have a text string and we
//                                    want to know in which line
//                                    and character position the
//                                    99th character of the text
//                                    lies in.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline void getRowAndColNumberOfPositionInDataBuffer(const blDataIteratorType& beginIter,
                                                     const blDataIteratorType& endIter,
                                                     const blTokenType& token,
                                                     const bool& shouldZeroLengthRowsBeCounted,
                                                     const blDataIteratorType& iteratorToDataPosition,
                                                     blIntegerType& rowNumber,
                                                     blIntegerType& colNumber)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case, we
        // have no data to
        // parse, or no
        // tokens to find

        if(!shouldZeroLengthRowsBeCounted)
        {
            rowNumber = blIntegerType(-1);
            colNumber = blIntegerType(-1);
        }
        else
        {
            rowNumber = blIntegerType(0);
            colNumber = blIntegerType(0);
        }

        return;
    }

    // The iterator to
    // the tokens found
    // in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    // The starting
    // position of the
    // row we're currently
    // parsing

    blDataIteratorType startingPositionOfCurrentRow = beginIter;

    // We initialize the
    // row number differently
    // depending on whether
    // or not rows of zero size
    // are to be counted

    if(shouldZeroLengthRowsBeCounted)
        rowNumber = blIntegerType(0);
    else
        rowNumber = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          std::distance(firstTokenIterator,iteratorToDataPosition) > 0)
    {
        // Find the next
        // token in the
        // data buffer

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   token,
                                   0);

        // Check to see if
        // the row we found
        // was a zero length
        // row

        if(secondTokenIterator != endIter &&
           secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else if(secondTokenIterator != endIter &&
                std::distance(secondTokenIterator,iteratorToDataPosition) >= 0)
        {
            ++rowNumber;

            firstTokenIterator = secondTokenIterator;
            ++firstTokenIterator;

            startingPositionOfCurrentRow = firstTokenIterator;
        }
        else
        {
            firstTokenIterator = secondTokenIterator;
        }
    }

    // We calculated the
    // row, now we need
    // to calculate the
    // column

    colNumber = std::distance(startingPositionOfCurrentRow,iteratorToDataPosition);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to the
// beginning of the user specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginningOfNthDataRow(const blDataIteratorType& beginIter,
                                               const blDataIteratorType& endIter,
                                               const blTokenType& rowToken,
                                               const bool& shouldZeroLengthRowsBeCounted,
                                               const blIntegerType& whichRowToFind,
                                               blDataIteratorType& nthRowBeginIter)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case
        // we have no
        // data to look
        // through

        nthRowBeginIter = beginIter;

        return blIntegerType(0);
    }

    // The iterator
    // to the tokens
    // found in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    nthRowBeginIter = firstTokenIterator;

    // The current
    // data row

    blIntegerType currentRow = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          currentRow < whichRowToFind)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else
        {
            ++currentRow;

            nthRowBeginIter = firstTokenIterator;

            firstTokenIterator = secondTokenIterator;

            // If we have not
            // reached the end,
            // then we advance
            // the iterator

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }
    }

    // We're done

    return currentRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to the
// beginning of the user specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
// The function allows the user to specify
// whether or not to count zero sized rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginAndEndOfNthDataRow(const blDataIteratorType& beginIter,
                                                 const blDataIteratorType& endIter,
                                                 const blTokenType& rowToken,
                                                 const bool& shouldZeroLengthRowsBeCounted,
                                                 const blIntegerType& whichRowToFind,
                                                 blDataIteratorType& nthRowBeginIter,
                                                 blDataIteratorType& nthRowEndIter)
{
    // Check the inputs

    if(beginIter == endIter)
    {
        // In this case
        // we have no
        // data to look
        // through

        nthRowBeginIter = beginIter;
        nthRowEndIter = beginIter;

        return blIntegerType(0);
    }

    // The iterator
    // to the tokens
    // found in the data

    blDataIteratorType firstTokenIterator = beginIter;
    blDataIteratorType secondTokenIterator = beginIter;

    nthRowBeginIter = firstTokenIterator;
    nthRowEndIter = firstTokenIterator;

    // The current
    // data row

    blIntegerType currentRow = blIntegerType(-1);

    while(firstTokenIterator != endIter &&
          currentRow < whichRowToFind)
    {
        // Find the next
        // token in the
        // data

        secondTokenIterator = find(firstTokenIterator,
                                   endIter,
                                   rowToken,
                                   0);

        if(secondTokenIterator == firstTokenIterator &&
           !shouldZeroLengthRowsBeCounted)
        {
            // In this case,
            // the row is of
            // zero length and
            // we don't count it

            ++firstTokenIterator;
        }
        else
        {
            ++currentRow;

            nthRowBeginIter = firstTokenIterator;
            nthRowEndIter = secondTokenIterator;

            firstTokenIterator = secondTokenIterator;

            // If we have not
            // reached the end,
            // then we advance
            // the iterator

            if(firstTokenIterator != endIter)
                ++firstTokenIterator;
        }
    }

    // We're done

    return currentRow;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function, just like the one above
// finds the beginning and end of the user
// specified nth row.
// The function returns the "actual" row found
// in case that there are less than "n" rows.
// The function allows the user to specify
// whether or not to count zero sized rows.
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findBeginAndEndOfNthDataRow2(const blDataIteratorType& beginIter,
                                                  const blDataIteratorType& endIter,
                                                  const blTokenType& rowToken,
                                                  const bool& shouldZeroLengthRowsBeCounted,
                                                  const blIntegerType& whichRowToFind,
                                                  blIntegerType& nthRowBeginIndex,
                                                  blIntegerType& nthRowEndIndex)
{
    blDataIteratorType nthRowBeginIter;
    blDataIteratorType nthRowEndIter;

    blIntegerType actualRowFound = findBeginAndEndOfNthDataRow(beginIter,
                                                               endIter,
                                                               rowToken,
                                                               shouldZeroLengthRowsBeCounted,
                                                               whichRowToFind,
                                                               nthRowBeginIter,
                                                               nthRowEndIter);

    nthRowBeginIndex = std::distance(beginIter,nthRowBeginIter);
    nthRowEndIndex = std::distance(beginIter,nthRowEndIter);

    return actualRowFound;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets an iterator to a data
// point in the data array corresponding to
// the specified Nth data row and Mth data
// column
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType findIterToNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                            const blDataIteratorType& endIter,
                                                            const blTokenType& rowToken,
                                                            const bool& shouldZeroLengthRowsBeCounted,
                                                            const blIntegerType& whichRowToFind,
                                                            const blIntegerType& whichColToFind)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn;
    blDataIteratorType iteratorToEndingPositionOfNthRow;

    findBeginAndEndOfNthDataRow(beginIter,
                                endIter,
                                rowToken,
                                shouldZeroLengthRowsBeCounted,
                                whichRowToFind,
                                iteratorToPositionOfNthRowAndMthColumn,
                                iteratorToEndingPositionOfNthRow);

    // We calculate the
    // actual column
    // that the iterator
    // will be pointing to

    blIntegerType actualColFound = std::min( whichColToFind,
                                             blIntegerType(std::distance(iteratorToPositionOfNthRowAndMthColumn,
                                                                         iteratorToEndingPositionOfNthRow)) );

    // Advance the iterator
    // to get it to the Mth
    // column making sure
    // it does not pass the
    // end of the row

    std::advance(iteratorToPositionOfNthRowAndMthColumn,actualColFound);

    return iteratorToPositionOfNthRowAndMthColumn;
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blDataIteratorType findIterToNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                            const blDataIteratorType& endIter,
                                                            const blTokenType& rowToken,
                                                            const bool& shouldZeroLengthRowsBeCounted,
                                                            const blIntegerType& whichRowToFind,
                                                            const blIntegerType& whichColToFind,
                                                            blIntegerType& actualRowFound,
                                                            blIntegerType& actualColFound)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn;
    blDataIteratorType iteratorToEndingPositionOfNthRow;

    actualRowFound = findBeginAndEndOfNthDataRow(beginIter,
                                                 endIter,
                                                 rowToken,
                                                 shouldZeroLengthRowsBeCounted,
                                                 whichRowToFind,
                                                 iteratorToPositionOfNthRowAndMthColumn,
                                                 iteratorToEndingPositionOfNthRow);

    // We calculate the
    // actual column
    // that the iterator
    // will be pointing to

    actualColFound = std::min( whichColToFind,
                               blIntegerType(std::distance(iteratorToPositionOfNthRowAndMthColumn,
                                                           iteratorToEndingPositionOfNthRow)) );

    // Advance the iterator
    // to get it to the Mth
    // column making sure
    // it does not pass the
    // end of the row

    std::advance(iteratorToPositionOfNthRowAndMthColumn,actualColFound);

    return iteratorToPositionOfNthRowAndMthColumn;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// This function gets the position in the
// data buffer of a data point specified
// by its Nth Row and Mth Column
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           const blIntegerType& whichRowToFind,
                                                           const blIntegerType& whichColToFind)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn = findIterToNthDataRowAndMthDataCol(beginIter,
                                                                                                  endIter,
                                                                                                  rowToken,
                                                                                                  shouldZeroLengthRowsBeCounted,
                                                                                                  whichRowToFind,
                                                                                                  whichColToFind);

    return std::distance(beginIter,iteratorToPositionOfNthRowAndMthColumn);
}


template<typename blDataIteratorType,
         typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataCol(const blDataIteratorType& beginIter,
                                                           const blDataIteratorType& endIter,
                                                           const blTokenType& rowToken,
                                                           const bool& shouldZeroLengthRowsBeCounted,
                                                           const blIntegerType& whichRowToFind,
                                                           const blIntegerType& whichColToFind,
                                                           blIntegerType& actualRowFound,
                                                           blIntegerType& actualColFound)
{
    // We first try to
    // find the starting
    // and ending positions
    // of the specified
    // Nth data row

    blDataIteratorType iteratorToPositionOfNthRowAndMthColumn = findIterToNthDataRowAndMthDataCol(beginIter,
                                                                                                  endIter,
                                                                                                  rowToken,
                                                                                                  shouldZeroLengthRowsBeCounted,
                                                                                                  whichRowToFind,
                                                                                                  whichColToFind,
                                                                                                  actualRowFound,
                                                                                                  actualColFound);

    return std::distance(beginIter,iteratorToPositionOfNthRowAndMthColumn);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// std::string specializations
// of the
// above functions
//-------------------------------------------------------------------
template<typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataColInString(const std::string& theString,
                                                                   const blTokenType& rowToken,
                                                                   const blIntegerType& whichRowToFind,
                                                                   const blIntegerType& whichColToFind)
{
    return findPositionOfNthDataRowAndMthDataCol(theString.begin(),
                                                 theString.end(),
                                                 rowToken,
                                                 true,
                                                 whichRowToFind,
                                                 whichColToFind);
}


template<typename blTokenType,
         typename blIntegerType>

inline blIntegerType findPositionOfNthDataRowAndMthDataColInString(const std::string& theString,
                                                                   const blTokenType& rowToken,
                                                                   const blIntegerType& whichRowToFind,
                                                                   const blIntegerType& whichColToFind,
                                                                   blIntegerType& actualRowFound,
                                                                   blIntegerType& actualColFound)
{
    return findPositionOfNthDataRowAndMthDataCol(theString.begin(),
                                                 theString.end(),
                                                 rowToken,
                                                 true,
                                                 whichRowToFind,
                                                 whichColToFind,
                                                 actualRowFound,
                                                 actualColFound);
}
//-------------------------------------------------------------------



#endif // BL_BUFFERALGORITHMS_HPP
