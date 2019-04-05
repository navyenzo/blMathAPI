#ifndef BL_NUMERICFUNCTIONS_HPP
#define BL_NUMERICFUNCTIONS_HPP


///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A collection of simple numeric functions that
///                 come up all the time and might be useful
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
#include <limits>
#include <complex>
#include <cstdint>
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functions check if
// a number is infinite or if it's not
// a number
//-------------------------------------------------------------------
template<typename blNumberType>
inline bool isNaN(const blNumberType& number)
{
    return (number != number);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline bool isInf(const blNumberType& number)
{
    return (number <= std::numeric_limits<blNumberType>::min() &&
            number >= std::numeric_limits<blNumberType>::max());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functions return
// the sign of a number
//-------------------------------------------------------------------
template <typename blNumberType>
inline blNumberType sign(const blNumberType& number)
{
    return static_cast<blNumberType>( (static_cast<blNumberType>(0) < number) - (number < static_cast<blNumberType>(0)) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline std::complex<blNumberType> sign(const std::complex<blNumberType>& number)
{
    return std::complex<blNumberType>(blNumberType( (blNumberType(0) < number.real()) - (number.real() < blNumberType(0)) ),0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Returns the absolute value of a function
// This function requires the argument type to
// define the < comparator and the - operator as
// it compares against zero and then negates the
// number if it is less than zero
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType abs(const blNumberType& number)
{
    if(number < static_cast<blNumberType>(0))
        return -number;
    else
        return number;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function raises any entity to
// the power of another entity no matter the type
// For example a matrix raised to the power of an integer
// The only requirement is that the multiplication operator
// be defined for the first entity
//-------------------------------------------------------------------
template <typename blNumberType>
inline blNumberType power(const blNumberType& base,const int& exponent)
{
    blNumberType result = base;

    for(int i = 1; i < exponent; ++i)
        result *= base;

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functions round off
// a number to the specified precision
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType roundOff(const blNumberType& number,
                           const int& precision)
{
    blNumberType multiplier = blMathAPI::power(blNumberType(10),blNumberType(precision));

    return ( blNumberType( int(multiplier * number + blNumberType(0.5)) ) / blNumberType(multiplier) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline std::complex<blNumberType> roundOff(const std::complex<blNumberType>& number,
                                         const int& precision)
{
    // For a std::complex
    // number, we need to
    // round off both the
    // real and imaginary
    // parts

    return std::complex<blNumberType>(roundOff<blNumberType>(std::real(number),precision),
                                    roundOff<blNumberType>(std::imag(number),precision));
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
    integralPart = static_cast<blIntegralPartType>(static_cast<int64_t>(number));

    fractionalPart = static_cast<blFractionalPartType>(number - static_cast<blNumberType>(integralPart));
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
    return blMathAPI::abs(a * b) / gcd(a,b);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following function calculates if
// a number is zero
//-------------------------------------------------------------------
template<typename blNumberType>
inline bool isZero(const blNumberType& number,
                   const blNumberType howManyEpsilons)
{
    if(blMathAPI::abs(number) <= howManyEpsilons * std::numeric_limits<blNumberType>::epsilon())
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
template<typename blNumberType>
inline blNumberType linearMap(const blNumberType& valueToMap,
                            const blNumberType& lowInput,
                            const blNumberType& highInput,
                            const blNumberType& lowOutput,
                            const blNumberType& highOutput)
{
    auto slope = (highOutput - lowOutput) / (highInput - lowInput);
    auto intercept = highOutput - slope * highInput;

    return ( slope * valueToMap + intercept );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_NUMERICFUNCTIONS_HPP
