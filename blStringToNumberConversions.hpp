#ifndef BL_STRINGTONUMBERCONVERSIONS_HPP
#define BL_STRINGTONUMBERCONVERSIONS_HPP


//-------------------------------------------------------------------
// FILE:            blStringToNumberConversions.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A collection of simple functions to
//                  convert strings to numbers and to
//                  some blMathAPI structures
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
// DATE CREATED:    Oct/18/2013
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            countIntToStringLength
//
// ARGUMENTS:           - Number
//
// TEMPLATE ARGUMENTS:  - None
//
// PURPOSE:             - Count the number of characters that an
//                        integer is going to need when we convert
//                        it to a string
//
// DEPENDENCIES:        - None
//
// NOTES:
//-------------------------------------------------------------------
template<typename blIntegerType>

inline int countIntToStringLength(blIntegerType number)
{
    int count = 0;

    if(number < 0)
    {
        // In this case, we
        // return the number
        // of characters of the
        // positive integer plus
        // one needed for the
        // negative sign

        ++count;
    }

    if(number < 10)
        return 1 + count;

    while(number > 0)
    {
        ++count;
        number /= 10;
    }

    return count;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            countLeadingDecimalZerosInFloatingPointNumber
//
// ARGUMENTS:           - Number
//                      - Precision
//
// TEMPLATE ARGUMENTS:  - blNumberType
//
// PURPOSE:             - Count the number of leading zeros after
//                        the decimal point in a floating point
//                        number
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blNumberType>

inline int countLeadingDecimalZerosInFloatingPointNumber(blNumberType number,
                                                         const int& precision)
{
    if(number == 0)
        return 0;

    if(number < 0)
        return countLeadingDecimalZerosInFloatingPointNumber(-number,precision);

    int count = 0;

    number *= blNumberType(10);

    while( number < 1 &&
           (count < precision) )
    {
        number *= blNumberType(10);

        ++count;
    }

    return count;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            countFloatingPointToStringLength
//
// ARGUMENTS:           - Number
//                      - Precision
//                      - ShouldLeadingZeroBeCounted
//
// TEMPLATE ARGUMENTS:  - blNumberType
//
// PURPOSE:             - Count the number of characters that a
//                        floating point number is going to need
//                        when we convert it to a string using the
//                        specified decimal precision
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blNumberType>
inline int countFloatingPointToStringLength(blNumberType number,
                                            const int& precision,
                                            const bool& shouldLeadingZeroBeCounted)
{
    // We return the
    // count of digits
    // needed by the
    // integral part of
    // the number plus
    // the point delimiter
    // plus the specified
    // precision

    if(number < 0)
        return ( countFloatingPointToStringLength(-number,precision,shouldLeadingZeroBeCounted) + 1);

    if(number < 1 &&
       !shouldLeadingZeroBeCounted)
    {
        // In this case
        // we don't want
        // to count the
        // zero right before
        // the decimal point

        if(precision > 0)
            return ( countIntToStringLength(number) + precision );
        else
            return ( countIntToStringLength(number) );
    }
    else
    {
        if(precision > 0)
            return ( countIntToStringLength(number) + 1 + precision );
        else
            return ( countIntToStringLength(number) );
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            countFloatingPointToStringLengthUsingScientificNotation
//
// ARGUMENTS:           - Number
//                      - Precision
//                      - ShouldLeadingZeroBeCounted
//
// TEMPLATE ARGUMENTS:  - blNumberType
//
// PURPOSE:             - Count the number of characters that a
//                        floating point number is going to need
//                        when we convert it to a string using the
//                        specified decimal precision and using
//                        scientific notation
//
// DEPENDENCIES:
//
// NOTES:
//-------------------------------------------------------------------
template<typename blNumberType>

inline int countFloatingPointToStringLengthUsingScientificNotation(blNumberType number,
                                                                   const int& precision,
                                                                   const bool& shouldLeadingZeroBeCounted)
{
    // Using "Normalized"
    // scientific notation
    // the number will
    // look like: X.XXXeYYY

    // That means that the
    // number of digits needed
    // are going to be:
    // 0 or 1 -- For negative sign
    // 1 -- For the integral part
    // 1 -- For the decimal point
    //      delimiter
    // Precision -- For the decimal part
    // 1 -- For the 'e' indicating
    //      the exponent
    // N -- For the exponent

    int digitsNeededForExponent;

    if(number > 0)
    {
        digitsNeededForExponent = countIntToStringLength( countIntToStringLength(number) / 10 );

        if(number < 1 &&
           !shouldLeadingZeroBeCounted)
        {
            return ( digitsNeededForExponent + 2 + precision);
        }
        else
            return ( digitsNeededForExponent + 3 + precision);
    }
    else
        return ( countFloatingPointToStringLengthUsingScientificNotation(-number,precision,shouldLeadingZeroBeCounted) + 1 );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            intToString
//
// ARGUMENTS:           - Number
//                      - Base
//                      - BeginReverseIter
//                      - EndReverseIter
//
// TEMPLATE ARGUMENTS:  - blNumberIntegerType
//                      - blStringIteratorType
//
// PURPOSE:             - Convert an integer to a string, where the
//                        the number will be converted in reverse
//                        order.
//
//                      - The function will return an iterator
//                        to the place in the string after the
//                        last place that it wrote to.
//
// DEPENDENCIES:        None
//
// NOTES:
//-------------------------------------------------------------------
template<typename blIntegerType,
         typename blStringIteratorType>

inline blStringIteratorType intToString(blIntegerType number,
                                        const int& base,
                                        blStringIteratorType beginReverseIter,
                                        const blStringIteratorType& endReverseIter)
{
    if(beginReverseIter == endReverseIter)
        return beginReverseIter;

    if(number < 0)
    {
        beginReverseIter = intToString(-number,
                                       base,
                                       beginReverseIter,
                                       endReverseIter);

        if(beginReverseIter != endReverseIter)
        {
            (*beginReverseIter) = '-';
            ++beginReverseIter;

            return beginReverseIter;
        }
    }

    if(number == 0)
    {
        (*beginReverseIter) = '0';

        ++beginReverseIter;
    }
    else
    {
        while( (unsigned long long int)(number) > 0 &&
               beginReverseIter != endReverseIter )
        {
            (*beginReverseIter) = ((unsigned long long int)(number) % base) + '0';

            ++beginReverseIter;

            number /= base;
        }
    }

    return beginReverseIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            floatingPointToString
//
// ARGUMENTS:           - Number
//                      - Precision
//                      - BeginReverseIter
//                      - EndReverseIter
//                      - ShouldLeadingZeroBeCounted
//                      - ShouldLastDecimalDigitBeRounded
//
// TEMPLATE ARGUMENTS:  - blFloatingPointType
//                      - blStringIteratorType
//
// PURPOSE:             - Convert an integer to a string, where the
//                        the number will be converted in reverse
//                        order.
//
//                      - The function will return an iterator
//                        to the place in the string after the
//                        last place that it wrote to.
//
// DEPENDENCIES:        - blModF -- Used to separate the integral
//                                  and fractional parts of the
//                                  number
//
// NOTES:
//-------------------------------------------------------------------
template<typename blFloatingPointType,
         typename blStringIteratorType>

inline blStringIteratorType floatingPointToString(blFloatingPointType number,
                                                  const int& precision,
                                                  blStringIteratorType beginReverseIter,
                                                  const blStringIteratorType& endReverseIter,
                                                  const bool& shouldLeadingZeroBeCounted,
                                                  const bool& shouldLastDecimalDigitBeRounded = true)
{
    // First, we separate
    // the integral and
    // fractional parts
    // of the number

    blFloatingPointType integralPart,fractionalPart;

    fractionalPart = std::modf(number,&integralPart);

    if(precision > 0)
    {
        // Count the number of
        // leading decimal
        // zeros in the fractional
        // part

        int numberOfLeadingDecimalZeros = countLeadingDecimalZerosInFloatingPointNumber(fractionalPart,precision);

        // Here we multiply
        // the fractional part
        // by 10^Precision to
        // convert it to an
        // integer

        fractionalPart *= ( std::pow(double(10),double(precision)) );

        // Check if last
        // decimal digit
        // needs to be
        // rounded up

        if( shouldLastDecimalDigitBeRounded &&
            ( (unsigned long long int)(fractionalPart) % 10 >= 5 ) )
        {
            ++fractionalPart;
        }

        // And now we write
        // the fractional part
        // into the string
        // (Making sure we
        // convert it as a
        // positive number and
        // not negative

        if(fractionalPart > 0)
            beginReverseIter = intToString(fractionalPart,10,beginReverseIter,endReverseIter);
        else
            beginReverseIter = intToString(-fractionalPart,10,beginReverseIter,endReverseIter);

        // Here we add the
        // additional leading
        // zeros if needed

        int leadingDecimalZerosAddedSoFar = 0;

        while( (leadingDecimalZerosAddedSoFar < numberOfLeadingDecimalZeros) &&
               (beginReverseIter != endReverseIter) )
        {
            (*beginReverseIter) = '0';

            ++beginReverseIter;
            ++leadingDecimalZerosAddedSoFar;
        }

        // We then add the
        // decimal point
        // delimiter to
        // the string

        if(beginReverseIter != endReverseIter)
        {
            (*beginReverseIter) = '.';
            ++beginReverseIter;
        }
    }

    // Finally, we convert
    // the integral part
    // to string

    if( int(integralPart) == 0 &&
        number < 0 &&
        beginReverseIter != endReverseIter &&
        !shouldLeadingZeroBeCounted)
    {
        // In this case, we
        // just write the
        // negative sign

        (*beginReverseIter) = '-';

        ++beginReverseIter;
    }
    else
    {
        if(int(integralPart) != 0 ||
           shouldLeadingZeroBeCounted)
        {
            beginReverseIter = intToString(integralPart,10,beginReverseIter,endReverseIter);
        }

        if( int(integralPart) == 0 &&
            number < 0 &&
            beginReverseIter != endReverseIter )
        {
            (*beginReverseIter) = '-';

            ++beginReverseIter;
        }
    }

    return beginReverseIter;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// FUNCTION:            floatingPointToStringUsingScientificNotation
//
// ARGUMENTS:           - Number
//                      - Precision
//                      - BeginReverseIter
//                      - EndReverseIter
//                      - ShouldLastDecimalDigitBeRounded
//
// TEMPLATE ARGUMENTS:  - blFloatingPointType
//                      - blStringIteratorType
//
// PURPOSE:             - Convert an integer to a string, where the
//                        the number will be converted in reverse
//                        order.
//
//                      - The function will return an iterator
//                        to the place in the string after the
//                        last place that it wrote to.
//
// DEPENDENCIES:        - blModF -- Used to separate the integral
//                                  and fractional parts of the
//                                  number
//
// NOTES:
//-------------------------------------------------------------------
template<typename blFloatingPointType,
         typename blStringIteratorType>

inline blStringIteratorType floatingPointToStringUsingScientificNotation(blFloatingPointType number,
                                                                         const int& precision,
                                                                         blStringIteratorType beginReverseIter,
                                                                         const blStringIteratorType& endReverseIter,
                                                                         const bool& shouldLastDecimalDigitBeRounded = true)
{
    // First we check the
    // integral part of
    // the number

    if(int(number) > 0 && int(number) < 10)
    {
        // In this case, the
        // number is already
        // expressed in "Normalized"
        // scientific notation

        return floatingPointToString(number,
                                     precision,
                                     beginReverseIter,
                                     endReverseIter,
                                     true,
                                     shouldLastDecimalDigitBeRounded);
    }

    if(int(number) > 9)
    {
        int numberOfDigits;

        if(number > 0)
            numberOfDigits = countIntToStringLength(int(number));
        else
            numberOfDigits = countIntToStringLength(int(-number));

        // The first thing we
        // write to the string
        // is the exponent

        beginReverseIter = intToString(numberOfDigits - 1,
                                       10,
                                       beginReverseIter,
                                       endReverseIter);

        // We then write the "e"
        // to the string

        if(beginReverseIter != endReverseIter)
        {
            (*beginReverseIter) = 'e';
            ++beginReverseIter;
        }
        else
        {
            // Ran out of string
            // length

            return beginReverseIter;
        }

        // Next we normalize
        // the number

        number /= std::pow(blFloatingPointType(10),blFloatingPointType(numberOfDigits - 1));

        // Finally we write
        // the floating point
        // to the string

        return floatingPointToString(number,
                                     precision,
                                     beginReverseIter,
                                     endReverseIter,
                                     true,
                                     shouldLastDecimalDigitBeRounded);
    }

    // If we've made it this
    // far in the function then
    // that means we have a
    // number > 0 but < 1

    // The first thing we do
    // is count the number of
    // leading zeros after
    // the decimal point

    int numberOfLeadingZeros = countLeadingDecimalZerosInFloatingPointNumber(number,precision);

    // Next we write the
    // exponent to the string

    beginReverseIter = intToString(numberOfLeadingZeros + 1,
                                   10,
                                   beginReverseIter,
                                   endReverseIter);

    // We then write the "e"
    // to the string

    if(beginReverseIter != endReverseIter)
    {
        (*beginReverseIter) = 'e';
        ++beginReverseIter;
    }
    else
    {
        // Ran out of string
        // length

        return beginReverseIter;
    }

    // Next we normalize
    // the number

    number *= std::pow(blFloatingPointType(10),blFloatingPointType(numberOfLeadingZeros + 1));

    // Finally we write
    // the floating point
    // to the string

    return floatingPointToString(number,
                                 precision,
                                 beginReverseIter,
                                 endReverseIter,
                                 true,
                                 shouldLastDecimalDigitBeRounded);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to test whether a character
// is purely numeric, or numeric plus some accepted
// characters in a number such as the decimal point,
// plus sign, minus sign, exponent etc.
//-------------------------------------------------------------------
template<typename blCharacterType>

inline bool isCharNumeric(const blCharacterType& character)
{
    return (character >= '0' && character <= '9');
}



template<typename blCharacterType>

inline bool isCharNumericPlus(const blCharacterType& character)
{
    return ( (character >= '0' && character <= '9')
             || character == '-'
             || character == '+'
             || character == 'e'
             || character == 'E'
             || character == '.');
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// FUNCTION:            convertStringToNumber
//
// ARGUMENTS:           - BeginIter
//                      - EndIter
//                      - DecimalPointDelimiter
//                      - ConvertedNumber
//
// TEMPLATE ARGUMENTS:  - blStringIteratorType
//                      - blCharacterType
//                      - blNumberType
//
// PURPOSE:             - This function converts a sequence
//                        of characters to a number.
//                      - The function returns an iterator
//                        to the place after the last character
//                        in the sequence that was used to
//                        determine the number.
//                      - More clearly, it returns an iterator
//                        to the first non-valid character.
//
// DEPENDENCIES:        - std::pow
//
// NOTES:               - This function allows the user to
//                        specify the symbol that represents
//                        the decimal point, for example '.'
//                        or ',' or whatever.
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blNumberType& convertedNumber,
                                                  const int& numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // First we check
    // if the user
    // passed a zero
    // sized string

    if(beginIter == endIter)
    {
        // In this case
        // there's nothing
        // to convert so we
        // simply return

        return endIter;
    }

    // Initialize the
    // converted number

    convertedNumber = blNumberType(0);

    // Iterator used to
    // parse the string

    blStringIteratorType currentPos = beginIter;

    // Boolean to check
    // if the number is
    // negative

    bool isNumberNegative = false;

    // Boolean and
    // multiplier
    // used to handle
    // decimal point
    // digits

    bool hasDecimalPointBeenEncounteredAlready = false;
    blNumberType decimalPointMultiplier = blNumberType(1);

    // The first step
    // is to check the
    // first digit for
    // special characters

    if((*currentPos) == '-')
    {
        // This means the
        // number is negative

        isNumberNegative = true;

        // Advance the position

        ++currentPos;
    }
    else if((*currentPos) == '+')
    {
        // This means the
        // number is positive
        // so we simply advance
        // the position to the
        // next character

        ++currentPos;
    }
    else if((*currentPos) == decimalPointDelimiter)
    {
        // This means the
        // number starts with
        // a decimal point

        hasDecimalPointBeenEncounteredAlready = true;
        ++currentPos;
    }
    else if((*currentPos) == 'e' || (*currentPos) == 'E')
    {
        // In this case, the
        // first character of
        // the string is an 'e'
        // or 'E', which means
        // that the number is
        // an exponent.
        // Since it is the first
        // character, then the
        // number will be
        // 10^Exponent.
        // Therefore, we find
        // the exponent and
        // then raise 10
        // to its power

        ++currentPos;

        blNumberType exponent;

        blStringIteratorType newPos = convertStringToNumber(currentPos,
                                                            endIter,
                                                            decimalPointDelimiter,
                                                            exponent,
                                                            numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter - 1);

        if(newPos == currentPos)
        {
            // We obviously
            // had no exponent
            // so we assume
            // that it was e0
            // or * 10^0, which
            // means it is 1

            convertedNumber = blNumberType(1);
            return currentPos;
        }
        else
        {
            // In this case,
            // we had a valid
            // exponent

            convertedNumber = blNumberType(std::pow(double(10),double(exponent)));
            currentPos = newPos;
        }

        return currentPos;
    }

    // Keep track of how
    // many times we go
    // over the BeginIter
    // in case of a circular
    // iterator

    int numberOfRepeats = 0;

    // Now we loop through
    // the remaining elements
    // of the string and
    // calculate the number
    // accordingly.

    // NOTE:    Remember that we
    //          are looping from
    //          left to right, so
    //          from the highest
    //          digit to the lowest
    //          value digit (numerically
    //          speaking)

    while((currentPos != endIter) &&
          numberOfRepeats <= numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
    {
        if((*currentPos) >= '0' && (*currentPos) <= '9')
        {
            // This means we
            // have a valid
            // numeric digit

            if(hasDecimalPointBeenEncounteredAlready)
            {
                // This means that
                // the digit is
                // after the decimal
                // point, so we add
                // the current digit
                // divided by its
                // place after the
                // decimal point

                decimalPointMultiplier *= blNumberType(10);
                convertedNumber = convertedNumber + blNumberType((*currentPos) - '0')/decimalPointMultiplier;
            }
            else
            {
                // This means that
                // the digit is before
                // the decimal point,
                // so we multiply the
                // current number by
                // 10 and add the new
                // digit

                convertedNumber = convertedNumber * blNumberType(10) + blNumberType((*currentPos) - '0');
            }
        }
        else if((*currentPos) == decimalPointDelimiter && !hasDecimalPointBeenEncounteredAlready)
        {
            // This means that
            // we have just found
            // the decimal point
            // so we just store the
            // fact that we found it
            // in the boolean

            hasDecimalPointBeenEncounteredAlready = true;
        }
        else if((*currentPos) == 'e' || (*currentPos) == 'E')
        {
            // In this case, it
            // means that we're
            // about to multiply
            // the current number
            // by 10^Exponent.
            // Thus, we find the value of the
            // exponent and then multiply

            // First we move
            // to the next
            // position in the
            // string (the one
            // after the 'e' or 'E')

            ++currentPos;

            // Then we calculate
            // the exponent by
            // recursively calling
            // this function

            blNumberType exponent;

            blStringIteratorType newPos = convertStringToNumber(currentPos,
                                                                endIter,
                                                                decimalPointDelimiter,
                                                                exponent,
                                                                numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter - numberOfRepeats);

            if(newPos == currentPos)
            {
                // If the iterators
                // are equal, that
                // means that the
                // function did not
                // find a valid exponent.
                // In this case, we
                // assume the exponent
                // was zero and we
                // multiply the current
                // number by 10^0,
                // meaning multiply by 1.
                // So we are done
                break;
            }
            else
            {
                // In this case,
                // we had a valid
                // exponent, so
                // we multiply the
                // current number
                // by 10^Exponent

                convertedNumber = convertedNumber * blNumberType(std::pow(double(10),double(exponent)));

                currentPos = newPos;

                // We are done

                break;
            }
        }
        else
        {
            // In this case, we
            // found a non-valid
            // character, so we
            // are done

            break;
        }

        // Advance the
        // iterator

        ++currentPos;

        if(currentPos == beginIter)
            ++numberOfRepeats;
    }

    // Check if the number
    // is negative

    if(isNumberNegative)
        convertedNumber *= blNumberType(-1);

    // Now we return the
    // current position

    return currentPos;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functor can be used as an iterator
// to iterate over a string assuming the string
// buffer reppresents an (nx1) column vector of
// numbers and when dereferenced it, it returns the
// number's value
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

class blStringMatrixIterator
{
public:

    // Iterator traits

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



    blStringMatrixIterator(const blDataIteratorType& beginIter,
                           const blDataIteratorType& endIter)
    {
        m_beginIter = beginIter;
        m_endIter = endIter;
        m_iter = m_beginIter;

        m_number = 0;

        m_currentLine = 0;

        calculateTotalNumberOfRows();

        convertToNumber();
    }



    blStringMatrixIterator(const blStringMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator) = default;



    ~blStringMatrixIterator()
    {
    }



    blStringMatrixIterator<blDataIteratorType,blNumberType>&        operator=(const blStringMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator) = default;



    operator bool()const
    {
        return !(m_iter == m_endIter);
    }



    bool                            operator==(const blStringMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const
    {
        return (m_iter == stringColumnVectorIterator.getIter());
    }

    bool                            operator!=(const blStringMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const
    {
        return (m_iter != stringColumnVectorIterator.getIter());
    }



    const blNumberType&             operator[](const ptrdiff_t& index)
    {
        (*this) += index - m_currentLine;
        return m_number;
    }



    const blNumberType&             operator()(const ptrdiff_t& index)
    {
        (*this) += index - m_currentLine;
        return m_number;
    }



    const blNumberType&             at(const ptrdiff_t& index)
    {
        (*this) += index - m_currentLine;
        return m_number;
    }



    blNumberType*                   operator->()
    {
        return &m_number;
    }

    const blNumberType&             operator*()const
    {
        return m_number;
    }



    blStringMatrixIterator<blDataIteratorType,blNumberType>&        operator+=(const ptrdiff_t& movement)
    {
        if(movement > 0)
        {
            int actualMovement = findBeginningOfNthDataRow(m_iter,m_endIter,'\n',false,movement,m_iter);

            if(actualMovement < movement)
                m_iter = m_endIter;

            m_currentLine += actualMovement;

            convertToNumber();
        }
        else if(movement < 0)
        {
            int newRowToFind = m_currentLine + movement;

            if(newRowToFind < 0)
            {
                m_currentLine = 0;
                m_iter = m_beginIter;
            }
            else
            {
                m_currentLine = findBeginningOfNthDataRow(m_beginIter,m_endIter,'\n',false,newRowToFind,m_iter);
            }

            convertToNumber();
        }

        return (*this);
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>&        operator-=(const ptrdiff_t& movement)
    {
        return this->operator+=(-movement);
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>&        operator++()
    {
        return operator+=(1);
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>&        operator--()
    {
        return operator+=(-1);
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>         operator++(int)
    {
        auto temp(*this);

        operator+=(1);

        return temp;
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>         operator--(int)
    {
        auto temp(*this);

        operator+=(-1);

        return temp;
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>         operator+(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp += movement;

        return temp;
    }

    blStringMatrixIterator<blDataIteratorType,blNumberType>         operator-(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp -= movement;

        return temp;
    }



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    ptrdiff_t                       operator-(const blStringMatrixIterator<blDataIteratorType,blNumberType>& stringColumnVectorIterator)const
    {
        return (m_iter - stringColumnVectorIterator.getIter());
    }



    void                            setIterators(const blDataIteratorType& beginIter,
                                                 const blDataIteratorType& endIter)
    {
        m_beginIter = beginIter;
        m_endIter = endIter;
        m_iter = m_beginIter;

        m_number = 0;

        m_currentLine = 0;

        calculateTotalNumberOfRows();

        convertToNumber();
    }



    const int&                      calculateTotalNumberOfRows()
    {
        m_totalNumberOfLines = countDataRows(m_beginIter,
                                             m_endIter,
                                             '\n',
                                             false);

        return m_totalNumberOfLines;
    }



    const int&                      getCurrentLine()const
    {
        return m_currentLine;
    }



    const blDataIteratorType&       getBeginIter()const
    {
        return m_beginIter;
    }



    const blDataIteratorType&       getEndIter()const
    {
        return m_endIter;
    }



    const blDataIteratorType&       getIter()const
    {
        return m_iter;
    }



    const blNumberType&             getNumber()const
    {
        return m_number;
    }



    const int&                      getTotalNumberOfLines()const
    {
        return m_totalNumberOfLines;
    }



private:

    void                            convertToNumber()
    {
        convertStringToNumber(m_iter,m_endIter,'.',m_number,0);
    }



protected:

    // Begin and end iterators
    // used to know where the
    // given buffer begins and
    // ends

    blDataIteratorType              m_beginIter;
    blDataIteratorType              m_endIter;



    // The iterator used to move through
    // the buffer

    blDataIteratorType              m_iter;



    // The converted number of where the
    // iterator is currently pointing at
    // in the buffer

    blNumberType                    m_number;



    //  Current line in the buffer

    int                             m_currentLine;



    // Total number of data rows

    int                             m_totalNumberOfLines;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functor based on the previous one, assumes
// the string is an (n x 1) column vector of values, representing
// data points, where each data point is a matrix of data of
// size (rows x cols), the string is assumed to be formatted as
// follows:
//
// Line 1 -- Serial number (a number representing a signature/type)
// Line 2 -- rows
// Line 3 -- cols
// Line 4 - Line n -- The data points one matrix at a time
// NOTE:  If the matrix is a 2d matrix then the cols = 1, for 3d matrices
//        the cols > 1
//
// For example a (2xN) matrix would look like the following:
//
// 123454321 (some serial number)
// 2 (the rows in each data point)
// 1 (the columns in each data point, so this means each data point
//   is a single column vector
// 0,0
// 1,0
// 2,0
// 0,1
// 1,1
// 2,1
// 0,2
// 1,2
// 2,2
// 0,3
// ...
// 2,N
// End of file
//-------------------------------------------------------------------
template<typename blDataIteratorType,
         typename blNumberType>

class blStringMatrixIterator2 : public blStringMatrixIterator<blDataIteratorType,blNumberType>
{
public:

    // Iterator traits

    using iterator_category = std::random_access_iterator_tag;
    using value_type = blNumberType;
    using difference_type = ptrdiff_t;
    using pointer = blNumberType*;
    using reference = blNumberType&;



    blStringMatrixIterator2(const blDataIteratorType& beginIter,
                            const blDataIteratorType& endIter)
                            : blStringMatrixIterator<blDataIteratorType,blNumberType>(beginIter,endIter)
    {
        m_serialNumber = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(0);

        m_rows = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(1);
        m_cols = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(2);

        m_totalNumberOfDataPointsPerRow  = std::max(this->m_totalNumberOfLines - 3,0) / m_rows;

        m_currentRow = 0;
        m_currentCol = 0;

        ++(*this);
    }



    blStringMatrixIterator2(const blStringMatrixIterator2<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



    ~blStringMatrixIterator2()
    {
    }



    blStringMatrixIterator2<blDataIteratorType,blNumberType>&      operator=(const blStringMatrixIterator2<blDataIteratorType,blNumberType>& stringColumnVectorIterator2) = default;



    void                            setIterators(const blDataIteratorType& beginIter,
                                                 const blDataIteratorType& endIter)
    {
        blStringMatrixIterator<blDataIteratorType,blNumberType>::setIterators(beginIter,endIter);

        m_serialNumber = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(0);

        m_rows = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(1);
        m_cols = blStringMatrixIterator<blDataIteratorType,blNumberType>::at(2);

        m_totalNumberOfDataPointsPerRow  = std::max(this->m_totalNumberOfLines - 3,0) / m_rows;

        m_currentRow = 0;
        m_currentCol = 0;

        ++(*this);
    }



    // Let's override the arithmetic operators
    // to make this move like a row-major matrix

    blStringMatrixIterator2<blDataIteratorType,blNumberType>&       operator+=(const ptrdiff_t& movement)
    {
        int currentIndex = m_currentRow * m_totalNumberOfDataPointsPerRow + m_currentCol;
        int desiredIndex = currentIndex + movement;

        int desiredRow = desiredIndex / m_totalNumberOfDataPointsPerRow;
        int desiredCol = desiredIndex % m_totalNumberOfDataPointsPerRow;

        this->at(desiredRow,desiredCol);

        return (*this);
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>&       operator-=(const ptrdiff_t& movement)
    {
        return this->operator+=(-movement);
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>&       operator++()
    {
        return operator+=(1);
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>&       operator--()
    {
        return operator+=(-1);
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>        operator++(int)
    {
        auto temp(*this);

        operator+=(1);

        return temp;
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>        operator--(int)
    {
        auto temp(*this);

        operator+=(-1);

        return temp;
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>        operator+(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp += movement;

        return temp;
    }

    blStringMatrixIterator2<blDataIteratorType,blNumberType>        operator-(const ptrdiff_t& movement)const
    {
        auto temp(*this);

        temp -= movement;

        return temp;
    }



    // Let's override the access operators so that
    // they access only the data points and not
    // the string header (serial number, rows, cols)



    const blNumberType&             operator[](const ptrdiff_t& index)
    {
        blStringMatrixIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             operator()(const ptrdiff_t& index)
    {
        blStringMatrixIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             operator()(const int& row,
                                               const int& col)
    {
        return this->at(row,col);
    }



    const blNumberType&             at(const ptrdiff_t& index)
    {
        blStringMatrixIterator<blDataIteratorType,blNumberType>::at(index + 3);

        return this->m_number;
    }



    const blNumberType&             at(const int& row,
                                       const int& col)
    {
        // First we try to find
        // the correct line
        // in the buffer

        blStringMatrixIterator<blDataIteratorType,blNumberType>::at(row + this->m_rows * col + 3);

        // Then we update the
        // current row and column

        m_currentRow = (this->m_currentLine - 3) % m_rows;
        m_currentCol = (this->m_currentLine - 3) / m_rows;

        return this->m_number;
    }



    const int&                      getSerialNumber()const
    {
        return m_serialNumber;
    }

    const int&                      getRows()const
    {
        return m_rows;
    }

    const int&                      getCols()const
    {
        return m_cols;
    }



    const int&                      getCurrentRow()const
    {
        return m_currentRow;
    }

    const int&                      getCurrentCol()const
    {
        return m_currentCol;
    }



    int                             getTotalNumberOfDataPointsPerRow()const
    {
        return m_totalNumberOfDataPointsPerRow;
    }



protected:

    // Serial number

    int                             m_serialNumber;



    // Data is represented as rows x cols

    int                             m_rows;
    int                             m_cols;



    // Total number of data points per row

    int                             m_totalNumberOfDataPointsPerRow;



    //  Current row and column in the buffer

    int                             m_currentRow;
    int                             m_currentCol;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function calculates the
// page number of a string.
// The page number would correspond to the string's
// position in a theoretical library big enough to hold
// all the knowledge that could ever be expressed
// using the number of characters in the string
//
// This is like an example of a "Library of Babel"
//
// Each string has a unique page number
// The function is NOT case sensitive
//
// The calculation expect the number type to be
// an arbitrary precision number big enough to be
// able to hold all the possible combinations of
// the alphabet being considered
//
// As of now, the calcultion uses a base 29 to
// represent the 26 letters of the english alphabet
// plus the space, point and comma
//-------------------------------------------------------------------
template<typename numberType>

void calculatePageNumber(const std::string& textInput,
                         numberType& pageNumber)
{
    // This calculation is based
    // on the following:

    // space = 0
    // point = 1
    // comma = 2
    // 'A' thru 'Z' and 'a' thru 'z' = 3 thru 28
    // anything else for now = 0 (space)

    pageNumber = 0;
    numberType currentCharacterValue(0);
    numberType base = numberType(29);

    for(unsigned int i = 0; i < textInput.size(); ++i)
    {
        if(textInput[i] >= 'A' && textInput[i] <= 'Z')
            currentCharacterValue = numberType(static_cast<int>(textInput[i]) - static_cast<int>('A') + static_cast<int>(3)) * pow(base,i);

        else if(textInput[i] >= 'a' && textInput[i] <= 'z')
            currentCharacterValue = numberType(static_cast<int>(textInput[i]) - static_cast<int>('a') + static_cast<int>(3)) * pow(base,i);

        else if(textInput[i] == '.')
            currentCharacterValue =  pow(base,i);

        else if(textInput[i] == ',')
            currentCharacterValue = numberType(2) * pow(base,i);

        else
            currentCharacterValue = 0;


        pageNumber += currentCharacterValue;
    }

    return;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function calculates the string
// corresponding to a page number, the inverse
// calculation of the above function
//-------------------------------------------------------------------
template<typename numberType,
         typename stringIteratorType>

void calculateStringFromPageNumber(const numberType& pageNumber,
                                   const stringIteratorType& textBeginIterator,
                                   const stringIteratorType& textEndIterator)
{
    if(textBeginIterator == textEndIterator)
    {
        // We have no string to write
        // the result into

        return;
    }

    // This function calculates the string
    // from a page number using a base 29
    // system

    // The base 29 system is represented as follows:
    // ' ' -- space character = 0
    // '.' -- point character = 1
    // ',' -- comma character = 2
    // 'A' thru 'Z' and 'a' thru 'z' -- alphabetical characters = 3 thru 29

    // First let's save the current
    // iterators

    auto iterator = textBeginIterator;

    // Now let's create the necessary
    // variables needed to convert the
    // page number

    numberType quotient = pageNumber;
    char remainder = 0;
    numberType divisor = numberType(29);
    numberType zero = numberType(0);

    do
    {
        // Calculate the quotient and remainder

        remainder = static_cast<char>(quotient % divisor);
        quotient = quotient / divisor;

        // Convert the remainder to
        // the string character

        switch(remainder)
        {
        case 0:
            (*iterator) = ' ';
            break;
        case 1:
            (*iterator) = '.';
            break;
        case 2:
            (*iterator) = ',';
            break;
        default:
            (*iterator) = remainder - static_cast<char>(3) + 'a';
            break;
        }

        // Move on to the next
        // string position

        ++iterator;

    }
    while((iterator != textEndIterator) && (quotient > zero));
}
//-------------------------------------------------------------------


#endif // BL_STRINGTONUMBERCONVERSIONS_HPP
