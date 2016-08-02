#ifndef BL_MATRIX3D_HPP
#define BL_MATRIX3D_HPP


//-------------------------------------------------------------------
// FILE:            blMatrix3d.hpp
// CLASS:           blMatrix3d
// BASE CLASS:      None
//
// PURPOSE:         A simple 3x3 matrix class
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
//                    file that are external to the 3x3 matrix class
//                    - Operators that allow multiplying and
//                      dividing a scalar by a 3x3 matrix
//                    - Operators that allow multiplying the
//                      matrix by a vector and viceversa
//                    - trace -- Sums the diagonal components
//                    - transpose -- Returns the transposed matrix
//                    - det -- Calculates the determinant
//                    - eye3d -- Builds a 3x3 identity matrix
//                    - inv -- Calculates the inverse of a matrix
//                    - operator<< -- ostream operator to output the
//                                    matrix contents to the console
//
// DATE CREATED:    Oct/19/2010
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
class blMatrix3d
{
public: // Default constructor and destructor

    // Default constructor

    blMatrix3d(const blDataType& initialValue = 0);

    // Copy constructor

    blMatrix3d(const blMatrix3d<blDataType>& matrix);

    // Copy constructor from
    // a different type matrix

    template<typename blDataType2>
    blMatrix3d(const blMatrix3d<blDataType2>& matrix);

    // Constructor using
    // 9 distinct values

    blMatrix3d(const blDataType& M00,const blDataType& M01,const blDataType& M02,
               const blDataType& M10,const blDataType& M11,const blDataType& M12,
               const blDataType& M20,const blDataType& M21,const blDataType& M22);

    // Constructor builds
    // matrix from a 3x3
    // two-dimensional array

    blMatrix3d(const blDataType (&matrixArray)[3][3]);

    // Constructor builds
    // matrix from a 3x3
    // two-dimensional array
    // of different type

    template<typename blDataType2>
    blMatrix3d(const blDataType2 (&matrixArray)[3][3]);

    // Constructor builds
    // matrix from a
    // two-dimensional array
    // of different dimensions

    template<int m,int n>
    blMatrix3d(const blDataType (&matrixArray)[m][n]);

    // Constructor builds
    // matrix from a
    // two-dimensional array
    // of different type
    // and different dimensions

    template<typename blDataType2,int m,int n>
    blMatrix3d(const blDataType2 (&matrixArray)[m][n]);

    // Virtual destructor

    ~blMatrix3d()
    {
    }

public: // Public variables

    // 3x3 matrix components

    blDataType                          M[3][3];

public: // Overloaded operators

    // Overloaded operators

    const blMatrix3d<blDataType>        operator-()const;
    blMatrix3d<blDataType>&             operator+=(const blMatrix3d<blDataType>& M);
    blMatrix3d<blDataType>&             operator-=(const blMatrix3d<blDataType>& M);
    blMatrix3d<blDataType>&             operator*=(const blDataType& scalar);
    blMatrix3d<blDataType>&             operator/=(const blDataType& scalar);

    const blMatrix3d<blDataType>        operator+(const blMatrix3d<blDataType>& M)const;
    const blMatrix3d<blDataType>        operator-(const blMatrix3d<blDataType>& M)const;
    const blMatrix3d<blDataType>        operator*(const blDataType& scalar)const;
    const blMatrix3d<blDataType>        operator/(const blDataType& scalar)const;

    const blMatrix3d<blDataType>        operator*(const blMatrix3d<blDataType>& M)const;
    const blMatrix3d<blDataType>        operator/(const blMatrix3d<blDataType>& M)const;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType& initialValue)
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
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType& M00,
                                          const blDataType& M01,
                                          const blDataType& M02,
                                          const blDataType& M10,
                                          const blDataType& M11,
                                          const blDataType& M12,
                                          const blDataType& M20,
                                          const blDataType& M21,
                                          const blDataType& M22)
{
    // Initialize all values
    // to their specified
    // initial value

    M[0][0] = M00;
    M[0][1] = M01;
    M[0][2] = M02;
    M[1][0] = M10;
    M[1][1] = M11;
    M[1][2] = M12;
    M[2][0] = M20;
    M[2][1] = M21;
    M[2][2] = M22;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>::blMatrix3d(const blMatrix3d<blDataType>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = matrix.M[0][0];
    M[0][1] = matrix.M[0][1];
    M[0][2] = matrix.M[0][2];
    M[1][0] = matrix.M[1][0];
    M[1][1] = matrix.M[1][1];
    M[1][2] = matrix.M[1][2];
    M[2][0] = matrix.M[2][0];
    M[2][1] = matrix.M[2][1];
    M[2][2] = matrix.M[2][2];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blMatrix3d<blDataType>::blMatrix3d(const blMatrix3d<blDataType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = blDataType(matrix.M[0][0]);
    M[0][1] = blDataType(matrix.M[0][1]);
    M[0][2] = blDataType(matrix.M[0][2]);
    M[1][0] = blDataType(matrix.M[1][0]);
    M[1][1] = blDataType(matrix.M[1][1]);
    M[1][2] = blDataType(matrix.M[1][2]);
    M[2][0] = blDataType(matrix.M[2][0]);
    M[2][1] = blDataType(matrix.M[2][1]);
    M[2][2] = blDataType(matrix.M[2][2]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType (&matrixArray)[3][3])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = matrixArray[0][0];
    M[0][1] = matrixArray[0][1];
    M[0][2] = matrixArray[0][2];
    M[1][0] = matrixArray[1][0];
    M[1][1] = matrixArray[1][1];
    M[1][2] = matrixArray[1][2];
    M[2][0] = matrixArray[2][0];
    M[2][1] = matrixArray[2][1];
    M[2][2] = matrixArray[2][2];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType2 (&matrixArray)[3][3])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = blDataType(matrixArray[0][0]);
    M[0][1] = blDataType(matrixArray[0][1]);
    M[0][2] = blDataType(matrixArray[0][2]);
    M[1][0] = blDataType(matrixArray[1][0]);
    M[1][1] = blDataType(matrixArray[1][1]);
    M[1][2] = blDataType(matrixArray[1][2]);
    M[2][0] = blDataType(matrixArray[2][0]);
    M[2][1] = blDataType(matrixArray[2][1]);
    M[2][2] = blDataType(matrixArray[2][2]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<int m,int n>
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    M[0][0] = 0;
    M[0][1] = 0;
    M[0][2] = 0;
    M[1][0] = 0;
    M[1][1] = 0;
    M[1][2] = 0;
    M[2][0] = 0;
    M[2][1] = 0;
    M[2][2] = 0;

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
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType2 (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    M[0][0] = 0;
    M[0][1] = 0;
    M[0][2] = 0;
    M[1][0] = 0;
    M[1][1] = 0;
    M[1][2] = 0;
    M[2][0] = 0;
    M[2][1] = 0;
    M[2][2] = 0;

    // Loop and assign
    // the values

    for(int i = 0; i < 2 && i < m; ++i)
    {
        for(int j = 0; j < 2 && j < n; ++j)
        {
            M[i][j] = blDataType(matrixArray[i][j]);
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator-()const
{
    blMatrix3d<blDataType> negative;

    negative[0][0] = -M[0][0];
    negative[0][1] = -M[0][1];
    negative[0][2] = -M[0][2];
    negative[1][0] = -M[1][0];
    negative[1][1] = -M[1][1];
    negative[1][2] = -M[1][2];
    negative[2][0] = -M[2][0];
    negative[2][1] = -M[2][1];
    negative[2][2] = -M[2][2];

    return negative;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator+=(const blMatrix3d<blDataType>& matrix)
{
    M[0][0] += matrix.M[0][0];
    M[0][1] += matrix.M[0][1];
    M[0][2] += matrix.M[0][2];
    M[1][0] += matrix.M[1][0];
    M[1][1] += matrix.M[1][1];
    M[1][2] += matrix.M[1][2];
    M[2][0] += matrix.M[2][0];
    M[2][1] += matrix.M[2][1];
    M[2][2] += matrix.M[2][2];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator-=(const blMatrix3d<blDataType>& matrix)
{
    M[0][0] -= matrix.M[0][0];
    M[0][1] -= matrix.M[0][1];
    M[0][2] -= matrix.M[0][2];
    M[1][0] -= matrix.M[1][0];
    M[1][1] -= matrix.M[1][1];
    M[1][2] -= matrix.M[1][2];
    M[2][0] -= matrix.M[2][0];
    M[2][1] -= matrix.M[2][1];
    M[2][2] -= matrix.M[2][2];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator*=(const blDataType& scalar)
{
    M[0][0] *= scalar;
    M[0][1] *= scalar;
    M[0][2] *= scalar;
    M[1][0] *= scalar;
    M[1][1] *= scalar;
    M[1][2] *= scalar;
    M[2][0] *= scalar;
    M[2][1] *= scalar;
    M[2][2] *= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator/=(const blDataType& scalar)
{
    M[0][0] /= scalar;
    M[0][1] /= scalar;
    M[0][2] /= scalar;
    M[1][0] /= scalar;
    M[1][1] /= scalar;
    M[1][2] /= scalar;
    M[2][0] /= scalar;
    M[2][1] /= scalar;
    M[2][2] /= scalar;

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> operator*(const blDataType& scalar,
                                        const blMatrix3d<blDataType>& matrix)
{
    return blMatrix3d<blDataType>(matrix.M[0][0]*scalar,
                                  matrix.M[0][1]*scalar,
                                  matrix.M[0][2]*scalar,
                                  matrix.M[1][0]*scalar,
                                  matrix.M[1][1]*scalar,
                                  matrix.M[1][2]*scalar,
                                  matrix.M[2][0]*scalar,
                                  matrix.M[2][1]*scalar,
                                  matrix.M[2][2]*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> operator/(const blDataType& scalar,
                                        const blMatrix3d<blDataType>& matrix)
{
    return matrix*scalar;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator*(const blDataType& scalar)const
{
    return blMatrix3d<blDataType>(M[0][0]*scalar,
                                  M[0][1]*scalar,
                                  M[0][2]*scalar,
                                  M[1][0]*scalar,
                                  M[1][1]*scalar,
                                  M[1][2]*scalar,
                                  M[2][0]*scalar,
                                  M[2][1]*scalar,
                                  M[2][2]*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator/(const blDataType& scalar)const
{
    return blMatrix3d<blDataType>(M[0][0]/scalar,
                                  M[0][1]/scalar,
                                  M[0][2]/scalar,
                                  M[1][0]/scalar,
                                  M[1][1]/scalar,
                                  M[1][2]/scalar,
                                  M[2][0]/scalar,
                                  M[2][1]/scalar,
                                  M[2][2]/scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> operator*(const blVector3d<blDataType>& vector1,
                                        const blMatrix3d<blDataType>& matrix2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blVector3d<blDataType> result;

    result.x = vector1.x*matrix2.M[0][0] + vector1.y*matrix2.M[1][0] + vector1.z*matrix2.M[2][0];
    result.y = vector1.x*matrix2.M[0][1] + vector1.y*matrix2.M[1][1] + vector1.z*matrix2.M[2][1];
    result.z = vector1.x*matrix2.M[0][2] + vector1.y*matrix2.M[1][2] + vector1.z*matrix2.M[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blVector3d<blDataType> operator*(const blMatrix3d<blDataType>& matrix1,
                                        const blVector3d<blDataType>& vector2)
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blVector3d<blDataType> result;

    result.x = matrix1.M[0][0]*vector2.x + matrix1.M[0][1]*vector2.y + matrix1.M[0][2]*vector2.z;
    result.y = matrix1.M[1][0]*vector2.x + matrix1.M[1][1]*vector2.y + matrix1.M[1][2]*vector2.z;
    result.z = matrix1.M[2][0]*vector2.x + matrix1.M[2][1]*vector2.y + matrix1.M[2][2]*vector2.z;

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator*(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix3d<blDataType> result;

    result.M[0][0] = M[0][0]*matrix.M[0][0] + M[0][1]*matrix.M[1][0] + M[0][2]*matrix.M[2][0];
    result.M[0][1] = M[0][0]*matrix.M[0][1] + M[0][1]*matrix.M[1][1] + M[0][2]*matrix.M[2][1];
    result.M[0][2] = M[0][0]*matrix.M[0][2] + M[0][1]*matrix.M[1][2] + M[0][2]*matrix.M[2][2];
    result.M[1][0] = M[1][0]*matrix.M[0][0] + M[1][1]*matrix.M[1][0] + M[1][2]*matrix.M[2][0];
    result.M[1][1] = M[1][0]*matrix.M[0][1] + M[1][1]*matrix.M[1][1] + M[1][2]*matrix.M[2][1];
    result.M[1][2] = M[1][0]*matrix.M[0][2] + M[1][1]*matrix.M[1][2] + M[1][2]*matrix.M[2][2];
    result.M[2][0] = M[2][0]*matrix.M[0][0] + M[2][1]*matrix.M[1][0] + M[2][2]*matrix.M[2][0];
    result.M[2][1] = M[2][0]*matrix.M[0][1] + M[2][1]*matrix.M[1][1] + M[2][2]*matrix.M[2][1];
    result.M[2][2] = M[2][0]*matrix.M[0][2] + M[2][1]*matrix.M[1][2] + M[2][2]*matrix.M[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator+(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix3d<blDataType> result;

    result.M[0][0] = M[0][0] + matrix.M[0][0];
    result.M[0][1] = M[0][1] + matrix.M[0][1];
    result.M[0][2] = M[0][2] + matrix.M[0][2];
    result.M[1][0] = M[1][0] + matrix.M[1][0];
    result.M[1][1] = M[1][1] + matrix.M[1][1];
    result.M[1][2] = M[1][2] + matrix.M[1][2];
    result.M[2][0] = M[2][0] + matrix.M[2][0];
    result.M[2][1] = M[2][1] + matrix.M[2][1];
    result.M[2][2] = M[2][2] + matrix.M[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator-(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix3d<blDataType> result;

    result.M[0][0] = M[0][0] - matrix.M[0][0];
    result.M[0][1] = M[0][1] - matrix.M[0][1];
    result.M[0][2] = M[0][2] - matrix.M[0][2];
    result.M[1][0] = M[1][0] - matrix.M[1][0];
    result.M[1][1] = M[1][1] - matrix.M[1][1];
    result.M[1][2] = M[1][2] - matrix.M[1][2];
    result.M[2][0] = M[2][0] - matrix.M[2][0];
    result.M[2][1] = M[2][1] - matrix.M[2][1];
    result.M[2][2] = M[2][2] - matrix.M[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType trace(const blMatrix3d<blDataType>& matrix)
{
    // trace is the sum of
    // the diagonal components

    return (matrix.M[0][0] + matrix.M[1][1] + matrix.M[2][2]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType det(const blMatrix3d<blDataType>& matrix)
{
    // Initialize the determinant

    blDataType result = 0;

    // Calculate the determinant

    result += matrix.M[0][0]*(matrix.M[1][1]*matrix.M[2][2] - matrix.M[2][1]*matrix.M[1][2]);
    result -= matrix.M[0][1]*(matrix.M[1][0]*matrix.M[2][2] - matrix.M[2][0]*matrix.M[1][2]);
    result += matrix.M[0][2]*(matrix.M[1][0]*matrix.M[2][1] - matrix.M[2][0]*matrix.M[1][1]);

    // Return the determinant

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> transpose(const blMatrix3d<blDataType>& matrix)
{
    // Initialize the
    // transpose matrix

    blMatrix3d<blDataType> matrixTranspose = 0;

    // Assign the components

    matrixTranspose.M[0][0] = matrix.M[0][0];
    matrixTranspose.M[0][1] = matrix.M[1][0];
    matrixTranspose.M[0][2] = matrix.M[2][0];
    matrixTranspose.M[1][0] = matrix.M[0][1];
    matrixTranspose.M[1][1] = matrix.M[1][1];
    matrixTranspose.M[1][2] = matrix.M[2][1];
    matrixTranspose.M[2][0] = matrix.M[0][2];
    matrixTranspose.M[2][1] = matrix.M[1][2];
    matrixTranspose.M[2][2] = matrix.M[2][2];

    return matrixTranspose;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> eye3d(const blDataType& diagonalValue = 1)
{
    return blMatrix3d<blDataType>(diagonalValue,0,0,
                                  0,diagonalValue,0,
                                  0,0,diagonalValue);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> inv(const blMatrix3d<blDataType>& matrix)
{
    // First:   Calculate the determinant
    //          of the matrix

    blDataType D = det(matrix);

    // Second:  transpose the matrix

    blMatrix3d<blDataType> Mt = transpose(matrix);

    // Third:   Calculate the matrix
    //          of minors

    blMatrix3d<blDataType> Minors;
    Minors.M[0][0] = Mt.M[1][1]*Mt.M[2][2] - Mt.M[2][1]*Mt.M[1][2];
    Minors.M[0][1] = Mt.M[1][0]*Mt.M[2][2] - Mt.M[2][0]*Mt.M[1][2];
    Minors.M[0][2] = Mt.M[1][0]*Mt.M[2][1] - Mt.M[2][0]*Mt.M[1][1];
    Minors.M[1][0] = Mt.M[0][1]*Mt.M[2][2] - Mt.M[2][1]*Mt.M[0][2];
    Minors.M[1][1] = Mt.M[0][0]*Mt.M[2][2] - Mt.M[2][0]*Mt.M[0][2];
    Minors.M[1][2] = Mt.M[0][0]*Mt.M[2][1] - Mt.M[2][0]*Mt.M[0][1];
    Minors.M[2][0] = Mt.M[0][1]*Mt.M[1][2] - Mt.M[1][1]*Mt.M[0][2];
    Minors.M[2][1] = Mt.M[0][0]*Mt.M[1][2] - Mt.M[1][0]*Mt.M[0][2];
    Minors.M[2][2] = Mt.M[0][0]*Mt.M[1][1] - Mt.M[1][0]*Mt.M[0][1];

    // Fourth:  Calculate the
    //          adjoint matrix

    Minors.M[0][1] *= blDataType(-1);
    Minors.M[1][0] *= blDataType(-1);
    Minors.M[1][2] *= blDataType(-1);
    Minors.M[2][1] *= blDataType(-1);

    // Fifth:   Calculate the
    //          inverse

    return Minors/D;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blMatrix3d<blDataType> blMatrix3d<blDataType>::operator/(const blMatrix3d<blDataType>& matrix)const
{
    return (*this) * inv(matrix);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// output a matrix3d
// to an input stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::ostream& operator<<(std::ostream& os,
                                const blMatrix3d<blDataType>& matrix3d)
{
    // We simply output the
    // components with a
    // space separating them

    os << matrix3d.M[0][0] << " " << matrix3d.M[0][1] << " " << matrix3d.M[0][2] << " ";
    os << matrix3d.M[1][0] << " " << matrix3d.M[1][1] << " " << matrix3d.M[1][2] << " ";
    os << matrix3d.M[2][0] << " " << matrix3d.M[2][1] << " " << matrix3d.M[2][2];

    return os;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Function used to
// input a matrix3d
// from an input stream
//-------------------------------------------------------------------
template<typename blDataType>
inline std::istream& operator>>(std::istream& is,
                                blMatrix3d<blDataType>& matrix3d)
{
    if(!(is >> matrix3d.M[0][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[0][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[0][2]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[1][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }
    if(!(is >> matrix3d.M[1][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[1][2]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[2][0]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }

    if(!(is >> matrix3d.M[2][1]))
    {
        // Error -- Cound not read
        //          the value
        return is;
    }
    if(!(is >> matrix3d.M[2][2]))
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
         typename blDataType>

inline blStringIteratorType convertStringToNumber(const blStringIteratorType& beginIter,
                                                    const blStringIteratorType& endIter,
                                                    const blCharacterType& decimalPointDelimiter,
                                                    blMathAPI::blMatrix3d<blDataType>& convertedNumber,
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
    // get the m02 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[0][2],
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

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m12 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                                endIter,
                                                decimalPointDelimiter,
                                                convertedNumber.M[1][2],
                                                numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m20 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[2][0],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m21 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[2][1],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    if(newStringPosition != endIter)
        ++newStringPosition;

    // Then we try to
    // get the m22 value

    newStringPosition = convertStringToNumber(newStringPosition,
                                              endIter,
                                              decimalPointDelimiter,
                                              convertedNumber.M[2][2],
                                              numberOfTimesToRepeatTheSearchIfBeginIterEqualsEndIter);

    return newStringPosition;
}
//-------------------------------------------------------------------


#endif // BL_MATRIX3D_HPP
