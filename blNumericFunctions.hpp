#ifndef BL_NUMERICFUNCTIONS_HPP
#define BL_NUMERICFUNCTIONS_HPP


//-------------------------------------------------------------------
// FILE:            blNumericFunctions.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         A collection of simple numeric functions that
//                  I have used and re-used throughout my work
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
// DATE CREATED:    Oct/19/2010
// DATE UPDATED:
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions check if
// a number is infinite or if it's not
// a number
//-------------------------------------------------------------------
template<typename blDataType>
inline bool isNaN(const blDataType& number)
{
    return (number != number);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline bool isInf(const blDataType& number)
{
    return (number <= std::numeric_limits<blDataType>::min() &&
            number >= std::numeric_limits<blDataType>::max());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions return
// the sign of a number
//-------------------------------------------------------------------
template <typename blDataType>
inline blDataType sign(const blDataType& number)
{
    return blDataType( (blDataType(0) < number) - (number < blDataType(0)) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline std::complex<blDataType> sign(const std::complex<blDataType>& number)
{
    return std::complex<blDataType>(blDataType( (blDataType(0) < number.real()) - (number.real() < blDataType(0)) ),0);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function raises any entity to
// the power of another entity no matter the type
// For example a matrix raised to the power of an integer
// The only requirement is that the multiplication operator
// be defined for the first entity
//-------------------------------------------------------------------
template <typename blDataType>
inline blDataType power(const blDataType& base,const int& exponent)
{
    blDataType result = base;

    for(int i = 1; i < exponent; ++i)
        result = result*base;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions round off
// a number to the specified precision
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType roundOff(const blDataType& number,
                           const int& precision)
{
    blDataType multiplier = std::pow(blDataType(10),blDataType(precision));

    return ( blDataType( int(multiplier * number + blDataType(0.5)) ) / blDataType(multiplier) );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline std::complex<blDataType> roundOff(const std::complex<blDataType>& number,
                                         const int& precision)
{
    // For a std::complex
    // number, we need to
    // round off both the
    // real and imaginary
    // parts

    return std::complex<blDataType>(roundOff<blDataType>(std::real(number),precision),
                                    roundOff<blDataType>(std::imag(number),precision));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions separate
// a number into its integral part and
// its fractional part
//-------------------------------------------------------------------
template<typename blNumberType,
         typename blIntegralPartType,
         typename blFractionalPartType>

inline void modf(const blNumberType& number,
                 blIntegralPartType& integralPart,
                 blFractionalPartType& fractionalPart)
{
    integralPart = (long long int)(number);

    fractionalPart = blFractionalPartType(number - blNumberType(integralPart));
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function calculates
// the greatest common divisor
//-------------------------------------------------------------------
template<typename blIntegerType>
inline blIntegerType gcd(const blIntegerType& a,
                         const blIntegerType& b)
{
    if(b == 0)
        return a;
    else if(a == 0)
        return b;

    blIntegerType c = a % b;

    if(c == 0)
        return b;

    blIntegerType d1 = b;
    blIntegerType d2;

    while(c > 0)
    {
        d2 = c;
        c = d1 % c;
        d1 = d2;
    }

    return d1;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function calculates
// the least common multiple
//-------------------------------------------------------------------
template<typename blIntegerType>
inline blIntegerType lcm(const blIntegerType& a,
                         const blIntegerType& b)
{
    return std::abs(a * b) / gcd(a,b);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function calculates if
// a number is zero
//-------------------------------------------------------------------
template<typename blDataType>
inline bool isZero(const blDataType& number,
                   const blDataType howManyEpsilons)
{
    if(std::abs(number) <= howManyEpsilons * std::numeric_limits<blDataType>::epsilon())
        return true;
    else
        return false;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following functions calculates
// the factorial of a number
//-------------------------------------------------------------------
template<typename blIntegerType>
inline blIntegerType factorial(const blIntegerType& number)
{
    auto result = number;

    for(auto i = (number - 1); i > 1; --i)
        result *= i;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// The following function maps a
// value from the input domain to
// the output range
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType linearMap(const blDataType& valueToMap,
                            const blDataType& lowInput,
                            const blDataType& highInput,
                            const blDataType& lowOutput,
                            const blDataType& highOutput)
{
    auto slope = (highOutput - lowOutput) / (highInput - lowInput);
    auto intercept = highOutput - slope * highInput;

    return ( slope * valueToMap + intercept );
}
//-------------------------------------------------------------------


#endif // BL_NUMERICFUNCTIONS_HPP
