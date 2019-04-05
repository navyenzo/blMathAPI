#ifndef BL_MATRIX2DOPERATIONS_HPP
#define BL_MATRIX2DOPERATIONS_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Useful functions for handling 2x2 matrices
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
#include "blMatrix2d.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the
// trace of the matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType trace(const blMatrix2d<blNumberType>& matrix)
{
    // trace is the sum
    // of the diagonal
    // components

    return (matrix[0][0] + matrix[1][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the determinant
// of a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType det(const blMatrix2d<blNumberType>& matrix)
{
    return (matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to transpose a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> transpose(const blMatrix2d<blNumberType>& matrix)
{
    return blMatrix2d<blNumberType>(matrix[0][0],matrix[1][0],
                                    matrix[0][1],matrix[1][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return an identity matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> eye2d(const blNumberType& diagonalValue = blNumberType(1))
{
    return blMatrix2d<blNumberType>(diagonalValue,0,
                                    0,diagonalValue);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the inverse of a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> inv(const blMatrix2d<blNumberType>& matrix)
{
    return blMatrix2d<blNumberType>(matrix[1][1],-matrix[0][1],-matrix[1][0],matrix[0][0]) / det(matrix);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to divide two matrices which
// means multiplying m1 by inv(m2)
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> operator/(const blMatrix2d<blNumberType>& m1,
                                          const blMatrix2d<blNumberType>& m2)
{
    return m1*inv(m2);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to multiply a scalar by a matrix where
// the scalar comes before the matrix in the equation
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> operator*(const blNumberType& scalar,
                                          const blMatrix2d<blNumberType>& matrix)
{
    return matrix*scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to divide a scalar by a matrix
// which means multiply a scalar by the inverse
// of that matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> operator/(const blNumberType& scalar,
                                          const blMatrix2d<blNumberType>& matrix)
{
    inv(matrix)*scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to multiply points with matrices
//-------------------------------------------------------------------
template<typename blNumberType>
inline blPoint2d<blNumberType> operator*(const blPoint2d<blNumberType>& point1,
                                         const blMatrix2d<blNumberType>& matrix2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blPoint2d<blNumberType>(point1.x()*matrix2[0][0] + point1.y()*matrix2[1][0],
                                 point1.x()*matrix2[0][1] + point1.y()*matrix2[1][1]);
}



template<typename blNumberType>
inline blPoint2d<blNumberType> operator*(const blMatrix2d<blNumberType>& matrix1,
                                         const blPoint2d<blNumberType>& point2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blPoint2d<blNumberType>(matrix1[0][0]*point2.x() + matrix1[0][1]*point2.y(),
                                 matrix1[1][0]*point2.x() + matrix1[1][1]*point2.y());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// output a matrix2d
// to an output stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMatrix2d<blNumberType>& matrix2d)
{
    // We simply output the
    // components with a
    // space separating them

    os << matrix2d[0][0] << " " << matrix2d[0][1] << " ";
    os << matrix2d[1][0] << " " << matrix2d[1][1];

    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// input a matrix2d
// from an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::istream& operator>>(std::istream& is,
                                blMatrix2d<blNumberType>& matrix2d)
{
    if(!(is >> matrix2d[0][0]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d[0][1]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d[1][0]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d[1][1]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    return is;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// convert a generic
// string to a matrix2d
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blMathAPI::blMatrix2d<blNumberType>& convertedNumber,
                                                  const int& numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // We expect the
    // following format:
    // M = m00 m01
    //     m10 m11

    blStringIteratorType newStringPosition;

    // First we try to
    // get the m00 value

    newStringPosition = convertStringToNumber(beginIter,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[0][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m01 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[0][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m10 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[1][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m11 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[1][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_MATRIX2DOPERATIONS_HPP
