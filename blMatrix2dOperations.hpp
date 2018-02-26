#ifndef BL_MATRIX2DOPERATIONS_HPP
#define BL_MATRIX2DOPERATIONS_HPP


//-------------------------------------------------------------------
// FILE:            blMatrix2dOperations.hpp
// CLASS:           None
// BASE CLASS:      None
//
// PURPOSE:         Useful functions for handling 2x2 matrices
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
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Enums used for this file and sub-files
//-------------------------------------------------------------------
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to calculate the
// trace of the matrix
//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType trace(const blMatrix2d<blDataType>& matrix)
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
template<typename blDataType>
inline blDataType det(const blMatrix2d<blDataType>& matrix)
{
    return (matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to transpose a matrix
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> transpose(const blMatrix2d<blDataType>& matrix)
{
    return blMatrix2d<blDataType>(matrix[0][0],matrix[1][0],
                                  matrix[0][1],matrix[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to return an identity matrix
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> eye2d(const blDataType& diagonalValue = blDataType(1))
{
    return blMatrix2d<blDataType>(diagonalValue,0,
                                  0,diagonalValue);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to calculate the inverse of a matrix
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> inv(const blMatrix2d<blDataType>& matrix)
{
    return blMatrix2d<blDataType>(matrix[1][1],-matrix[0][1],-matrix[1][0],matrix[0][0]) / det(matrix);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to divide two matrices which
// means multiplying m1 by inv(m2)
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> operator/(const blMatrix2d<blDataType>& m1,
                                        const blMatrix2d<blDataType>& m2)
{
    return m1*inv(m2);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to multiply a scalar by a matrix where
// the scalar comes before the matrix in the equation
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> operator*(const blDataType& scalar,
                                        const blMatrix2d<blDataType>& matrix)
{
    return matrix*scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to divide a scalar by a matrix
// which means multiply a scalar by the inverse
// of that matrix
//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> operator/(const blDataType& scalar,
                                        const blMatrix2d<blDataType>& matrix)
{
    inv(matrix)*scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Functions used to multiply points with matrices
//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blPoint2d<blDataType>& point1,
                                       const blMatrix2d<blDataType>& matrix2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blPoint2d<blDataType>(point1.x()*matrix2[0][0] + point1.y()*matrix2[1][0],
                                 point1.x()*matrix2[0][1] + point1.y()*matrix2[1][1]);
}


template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blMatrix2d<blDataType>& matrix1,
                                       const blPoint2d<blDataType>& point2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    return blPoint2d<blDataType>(matrix1[0][0]*point2.x() + matrix1[0][1]*point2.y(),
                                 matrix1[1][0]*point2.x() + matrix1[1][1]*point2.y());
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a matrix2d
// to an output stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMatrix2d<blDataType>& matrix2d)
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
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blMatrix2d<blDataType>& matrix2d)
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
         typename blDataType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                    const blStringIteratorType& endIter,
                                                    const blCharacterType& decimalPointDelimiter,
                                                    blMathAPI::blMatrix2d<blDataType>& convertedNumber,
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


#endif // BL_MATRIX2DOPERATIONS_HPP
