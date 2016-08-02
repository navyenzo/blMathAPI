#ifndef BL_MATRIX2D_HPP
#define BL_MATRIX2D_HPP


//-------------------------------------------------------------------
// FILE:            blMatrix2d.hpp
// CLASS:           blMatrix2d
// BASE CLASS:      None
//
// PURPOSE:         A simple 2x2 matrix class
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    blVector3d -- Used to multiply a vector by a matrix
//                                and viceversa
//
// NOTES:           - There are additional functions defined in this
//                    file that are external to the 2x2 matrix class
//                  - Operators that allow multiplying and
//                    dividing a scalar by a 2x2 matrix
//                  - Operators that allow multiplying the
//                    matrix by a vector and viceversa
//                  - trace -- Sums the diagonal components
//                  - transpose -- Returns the transposed matrix
//                  - det -- Calculates the determinant
//                  - eye2d -- Builds a 2x2 identity matrix
//                  - inv -- Calculates the inverse of a matrix
//                  - operator<< -- ostream operator to output the
//                                    matrix contents to the console
//
// DATE CREATED:    Jul/08/2011
// DATE UPDATED:
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
template<typename blDataType>
class blMatrix2d
{
public: // Default constructor and destructor

    // Default constructor

    blMatrix2d(const blDataType& initialValue = 0);

    // Copy constructor

    blMatrix2d(const blMatrix2d<blDataType>& matrix);

    // Copy constructor from
    // a different type matrix

    template<typename blDataType2>
    blMatrix2d(const blMatrix2d<blDataType2>& matrix);

    // Constructor using
    // 9 distinct values

    blMatrix2d(const blDataType& M00,const blDataType& M01,
               const blDataType& M10,const blDataType& M11);

    // Constructor builds
    // matrix from a 2x2
    // two-dimensional array

    blMatrix2d(const blDataType (&matrixArray)[2][2]);

    // Constructor builds
    // matrix from a 2x2
    // two-dimensional array
    // of different type

    template<typename blDataType2>
    blMatrix2d(const blDataType2 (&matrixArray)[2][2]);

    // Constructor builds
    // matrix from a
    // two-dimensional
    // array of different
    // dimensions

    template<int m,int n>
    blMatrix2d(const blDataType (&matrixArray)[m][n]);

    // Constructor builds
    // matrix from a
    // two-dimensional
    // array of different
    // type and different
    // dimensions

    template<typename blDataType2,int m,int n>
    blMatrix2d(const blDataType2 (&matrixArray)[m][n]);

    // Virtual destructor

    ~blMatrix2d()
    {
    }

public: // Public variables

    // 3x3 matrix components

    blDataType                          M[2][2];

public: // Overloaded operators

    // Overloaded operators

    const blMatrix2d<blDataType>        operator-()const;
    blMatrix2d<blDataType>&             operator+=(const blMatrix2d<blDataType>& M);
    blMatrix2d<blDataType>&             operator-=(const blMatrix2d<blDataType>& M);
    blMatrix2d<blDataType>&             operator*=(const blDataType& scalar);
    blMatrix2d<blDataType>&             operator/=(const blDataType& scalar);

    const blMatrix2d<blDataType>        operator+(const blMatrix2d<blDataType>& M)const;
    const blMatrix2d<blDataType>        operator-(const blMatrix2d<blDataType>& M)const;
    const blMatrix2d<blDataType>        operator*(const blDataType& scalar)const;
    const blMatrix2d<blDataType>        operator/(const blDataType& scalar)const;

    const blMatrix2d<blDataType>        operator*(const blMatrix2d<blDataType>& M)const;
    const blMatrix2d<blDataType>        operator/(const blMatrix2d<blDataType>& M)const;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>::blMatrix2d(const blDataType& initialValue)
{
    // Initialize all values to
    // the passed value

    M[0][0] = initialValue;
    M[0][1] = initialValue;
    M[0][2] = initialValue;
    M[1][0] = initialValue;
    M[1][1] = initialValue;
    M[1][2] = initialValue;
    M[2][0] = initialValue;
    M[2][1] = initialValue;
    M[2][2] = initialValue;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>::blMatrix2d(const blDataType& M00,
                                          const blDataType& M01,
                                          const blDataType& M10,
                                          const blDataType& M11)
{
    // Initialize all values to their
    // specified initial value

    M[0][0] = M00;
    M[0][1] = M01;
    M[1][0] = M10;
    M[1][1] = M11;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>::blMatrix2d(const blMatrix2d<blDataType>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = matrix.M[0][0];
    M[0][1] = matrix.M[0][1];
    M[1][0] = matrix.M[1][0];
    M[1][1] = matrix.M[1][1];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blMatrix2d<blDataType>::blMatrix2d(const blMatrix2d<blDataType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = blDataType(matrix.M[0][0]);
    M[0][1] = blDataType(matrix.M[0][1]);
    M[1][0] = blDataType(matrix.M[1][0]);
    M[1][1] = blDataType(matrix.M[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>::blMatrix2d(const blDataType (&matrixArray)[2][2])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = matrixArray[0][0];
    M[0][1] = matrixArray[0][1];
    M[1][0] = matrixArray[1][0];
    M[1][1] = matrixArray[1][1];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>

inline blMatrix2d<blDataType>::blMatrix2d(const blDataType2 (&matrixArray)[2][2])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = blDataType(matrixArray[0][0]);
    M[0][1] = blDataType(matrixArray[0][1]);
    M[1][0] = blDataType(matrixArray[1][0]);
    M[1][1] = blDataType(matrixArray[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<int m,int n>

inline blMatrix2d<blDataType>::blMatrix2d(const blDataType (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    M[0][0] = 0;
    M[0][1] = 0;
    M[1][0] = 0;
    M[1][1] = 0;

    // Loop and assign
    // the values

    for(int i = 0; i < 2 && i < m; ++i)
    {
        for(int j = 0; j < 2 && j < n; ++j)
        {
            M[i][j] = matrixArray[i][j];
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2,int m,int n>

inline blMatrix2d<blDataType>::blMatrix2d(const blDataType2 (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    M[0][0] = 0;
    M[0][1] = 0;
    M[1][0] = 0;
    M[1][1] = 0;

    // Loop and assign
    // the values

    for(int i = 0; i < 2 && i < m; ++i)
    {
        for(int j = 0; j < 2 && j < n; ++j)
        {
            M[i][j] = blDataType( matrixArray[i][j] );
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator-()const
{
    blMatrix2d<blDataType> negative;

    negative[0][0] = -M[0][0];
    negative[0][1] = -M[0][1];
    negative[1][0] = -M[1][0];
    negative[1][1] = -M[1][1];

    return negative;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator+=(const blMatrix2d<blDataType>& matrix)
{
    M[0][0] += matrix.M[0][0];
    M[0][1] += matrix.M[0][1];
    M[1][0] += matrix.M[1][0];
    M[1][1] += matrix.M[1][1];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator-=(const blMatrix2d<blDataType>& matrix)
{
    M[0][0] -= matrix.M[0][0];
    M[0][1] -= matrix.M[0][1];
    M[1][0] -= matrix.M[1][0];
    M[1][1] -= matrix.M[1][1];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator*=(const blDataType& scalar)
{
    M[0][0] *= scalar;
    M[0][1] *= scalar;
    M[1][0] *= scalar;
    M[1][1] *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator/=(const blDataType& scalar)
{
    M[0][0] /= scalar;
    M[0][1] /= scalar;
    M[1][0] /= scalar;
    M[1][1] /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> operator*(const blDataType& scalar,
                                        const blMatrix2d<blDataType>& matrix)
{
    return blMatrix2d<blDataType>(matrix.M[0][0]*scalar,
                                  matrix.M[0][1]*scalar,
                                  matrix.M[1][0]*scalar,
                                  matrix.M[1][1]*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> operator/(const blDataType& scalar,
                                    const blMatrix2d<blDataType>& matrix)
{
    return matrix*scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator*(const blDataType& scalar)const
{
    return blMatrix2d<blDataType>(M[0][0]*scalar,
                                  M[0][1]*scalar,
                                  M[1][0]*scalar,
                                  M[1][1]*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator/(const blDataType& scalar)const
{
    return blMatrix2d<blDataType>(M[0][0]/scalar,
                                  M[0][1]/scalar,
                                  M[1][0]/scalar,
                                  M[1][1]/scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blPoint2d<blDataType>& point1,
                                       const blMatrix2d<blDataType>& matrix2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blPoint2d<blDataType> result;

    result.x = point1.x*matrix2.M[0][0] + point1.y*matrix2.M[1][0];
    result.y = point1.x*matrix2.M[0][1] + point1.y*matrix2.M[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blPoint2d<blDataType> operator*(const blMatrix2d<blDataType>& matrix1,
                                   const blPoint2d<blDataType>& point2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blPoint2d<blDataType> result;

    result.x = matrix1.M[0][0]*point2.x + matrix1.M[0][1]*point2.y;
    result.y = matrix1.M[1][0]*point2.x + matrix1.M[1][1]*point2.y;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator*(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix2d<blDataType> result;

    result.M[0][0] = M[0][0]*matrix.M[0][0] + M[0][1]*matrix.M[1][0];
    result.M[0][1] = M[0][0]*matrix.M[0][1] + M[0][1]*matrix.M[1][1];
    result.M[1][0] = M[1][0]*matrix.M[0][0] + M[1][1]*matrix.M[1][0];
    result.M[1][1] = M[1][0]*matrix.M[0][1] + M[1][1]*matrix.M[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator+(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix2d<blDataType> result;

    result.M[0][0] = M[0][0] + matrix.M[0][0];
    result.M[0][1] = M[0][1] + matrix.M[0][1];
    result.M[1][0] = M[1][0] + matrix.M[1][0];
    result.M[1][1] = M[1][1] + matrix.M[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator-(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix2d<blDataType> result;

    result.M[0][0] = M[0][0] - matrix.M[0][0];
    result.M[0][1] = M[0][1] - matrix.M[0][1];
    result.M[1][0] = M[1][0] - matrix.M[1][0];
    result.M[1][1] = M[1][1] - matrix.M[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType trace(const blMatrix2d<blDataType>& matrix)
{
    // trace is the sum
    // of the diagonal
    // components

    return (matrix.M[0][0] + matrix.M[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType det(const blMatrix2d<blDataType>& matrix)
{
    // Calculate the
    // determinant

    return (matrix.M[0][0]*matrix.M[1][1] - matrix.M[1][0]*matrix.M[0][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> transpose(const blMatrix2d<blDataType>& matrix)
{
    // Initialize the
    // transpose matrix

    return blMatrix2d<blDataType>(matrix.M[0][0],matrix.M[1][0],
                                  matrix.M[0][1],matrix.M[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> eye2d(const blDataType& diagonalValue = 1)
{
    return blMatrix2d<blDataType>(diagonalValue,0,
                                  0,diagonalValue);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> inv(const blMatrix2d<blDataType>& matrix)
{
    return (
            blMatrix2d<blDataType>(matrix.M[1][1],-matrix.M[0][1],
                                   -matrix.M[1][0],matrix.M[0][0]) / det(matrix)
            );
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix2d<blDataType> blMatrix2d<blDataType>::operator/(const blMatrix2d<blDataType>& matrix)const
{
    return (*this) * inv(matrix);
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

    os << matrix2d.M[0][0] << " " << matrix2d.M[0][1] << " ";
    os << matrix2d.M[1][0] << " " << matrix2d.M[1][1];

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
    if(!(is >> matrix2d.M[0][0]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d.M[0][1]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d.M[1][0]))
    {
        // Error -- Cound not read
        //          the value

        return is;
    }

    if(!(is >> matrix2d.M[1][1]))
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
                                              convertedNumber.M[0][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m01 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[0][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m10 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[1][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m11 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[1][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_MATRIX2D_HPP
