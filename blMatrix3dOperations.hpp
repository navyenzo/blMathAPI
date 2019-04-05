#ifndef BL_MATRIX3DOPERATIONS_HPP
#define BL_MATRIX3DOPERATIONS_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        Useful functions for handling 3x3 matrices
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
#include "blMatrix3d.hpp"
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
inline blNumberType trace(const blMatrix3d<blNumberType>& matrix)
{
    // trace is the sum of
    // the diagonal components

    return (matrix[0][0] + matrix[1][1] + matrix[2][2]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the determinant
// of a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType det(const blMatrix3d<blNumberType>& matrix)
{
    // Initialize the determinant

    blNumberType result = 0;

    // Calculate the determinant

    result += matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[2][1]*matrix[1][2]);
    result -= matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[2][0]*matrix[1][2]);
    result += matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[2][0]*matrix[1][1]);

    // Return the determinant

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to transpose a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> transpose(const blMatrix3d<blNumberType>& matrix)
{
    return blMatrix3d<blNumberType>(matrix[0][0],matrix[1][0],matrix[2][0],
                                    matrix[0][1],matrix[1][1],matrix[2][1],
                                    matrix[0][2],matrix[1][2],matrix[2][2]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return an identity matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> eye3d(const blNumberType& diagonalValue = blNumberType(1))
{
    return blMatrix3d<blNumberType>(diagonalValue,0,0,
                                    0,diagonalValue,0,
                                    0,0,diagonalValue);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to calculate the inverse of a matrix
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> inv(const blMatrix3d<blNumberType>& matrix)
{
    // First:   Calculate the determinant
    //          of the matrix

    blNumberType D = det(matrix);

    // Second:  transpose the matrix

    blMatrix3d<blNumberType> Mt = transpose(matrix);

    // Third:   Calculate the matrix
    //          of minors

    blMatrix3d<blNumberType> Minors;

    Minors[0][0] = Mt[1][1]*Mt[2][2] - Mt[2][1]*Mt[1][2];
    Minors[0][1] = Mt[1][0]*Mt[2][2] - Mt[2][0]*Mt[1][2];
    Minors[0][2] = Mt[1][0]*Mt[2][1] - Mt[2][0]*Mt[1][1];
    Minors[1][0] = Mt[0][1]*Mt[2][2] - Mt[2][1]*Mt[0][2];
    Minors[1][1] = Mt[0][0]*Mt[2][2] - Mt[2][0]*Mt[0][2];
    Minors[1][2] = Mt[0][0]*Mt[2][1] - Mt[2][0]*Mt[0][1];
    Minors[2][0] = Mt[0][1]*Mt[1][2] - Mt[1][1]*Mt[0][2];
    Minors[2][1] = Mt[0][0]*Mt[1][2] - Mt[1][0]*Mt[0][2];
    Minors[2][2] = Mt[0][0]*Mt[1][1] - Mt[1][0]*Mt[0][1];

    // Fourth:  Calculate the
    //          adjoint matrix

    Minors[0][1] *= blNumberType(-1);
    Minors[1][0] *= blNumberType(-1);
    Minors[1][2] *= blNumberType(-1);
    Minors[2][1] *= blNumberType(-1);

    // Fifth:   Calculate the
    //          inverse

    return Minors/D;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to divide two matrices which
// means multiplying m1 by inv(m2)
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> operator/(const blMatrix3d<blNumberType>& m1,
                                          const blMatrix3d<blNumberType>& m2)
{
    return m1*inv(m2);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to multiply a scalar by a matrix where
// the scalar comes before the matrix in the equation
//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> operator*(const blNumberType& scalar,
                                          const blMatrix3d<blNumberType>& matrix)
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
                                          const blMatrix3d<blNumberType>& matrix)
{
    inv(matrix)*scalar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to multiply vectors with matrices
//-------------------------------------------------------------------
template<typename blNumberType>
inline blVector3d<blNumberType> operator*(const blVector3d<blNumberType>& vector1,
                                          const blMatrix3d<blNumberType>& matrix2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blVector3d<blNumberType>(vector1.x()*matrix2[0][0] + vector1.y()*matrix2[1][0] + vector1.z()*matrix2[2][0],
                                    vector1.x()*matrix2[0][1] + vector1.y()*matrix2[1][1] + vector1.z()*matrix2[2][1],
                                    vector1.x()*matrix2[0][2] + vector1.y()*matrix2[1][2] + vector1.z()*matrix2[2][2]);
}


template<typename blNumberType>
inline blVector3d<blNumberType> operator*(const blMatrix3d<blNumberType>& matrix1,
                                        const blVector3d<blNumberType>& vector2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blVector3d<blNumberType>(matrix1[0][0]*vector2.x() + matrix1[0][1]*vector2.y() + matrix1[0][2]*vector2.z(),
                                    matrix1[1][0]*vector2.x() + matrix1[1][1]*vector2.y() + matrix1[1][2]*vector2.z(),
                                    matrix1[2][0]*vector2.x() + matrix1[2][1]*vector2.y() + matrix1[2][2]*vector2.z());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// output a matrix3d
// to an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMatrix3d<blNumberType>& matrix3d)
{
    // We simply output the
    // components with a
    // space separating them

    os << matrix3d[0][0] << " " << matrix3d[0][1] << " " << matrix3d[0][2] << " ";
    os << matrix3d[1][0] << " " << matrix3d[1][1] << " " << matrix3d[1][2] << " ";
    os << matrix3d[2][0] << " " << matrix3d[2][1] << " " << matrix3d[2][2];

    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to
// input a matrix3d
// from an input stream
//-------------------------------------------------------------------
template<typename blNumberType>
inline std::istream& operator>>(std::istream& is,
                                blMatrix3d<blNumberType>& matrix3d)
{
    if(!(is >> matrix3d[0][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[0][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[0][2]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[1][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }
    if(!(is >> matrix3d[1][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[1][2]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[2][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d[2][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }
    if(!(is >> matrix3d[2][2]))
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
// string to a matrix3d
//-------------------------------------------------------------------
template<typename blStringIteratorType,
         typename blCharacterType,
         typename blNumberType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                  const blStringIteratorType& endIter,
                                                  const blCharacterType& decimalPointDelimiter,
                                                  blMathAPI::blMatrix3d<blNumberType>& convertedNumber,
                                                  const int& numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter)
{
    // We expect the
    // following format:
    // M = m00 m01 m02
    //     m10 m11 m12
    //     m20 m21 m22

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
    // get the m02 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[0][2],
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

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m12 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[1][2],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m20 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[2][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m21 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[2][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m22 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber[2][2],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_MATRIX3DOPERATIONS_HPP
