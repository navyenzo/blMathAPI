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
template<typename blDataType>
class blMatrix3d
{
public: // Default constructor and destructor

    // Default constructor

    blMatrix3d(const blDataType& initialValue = blDataType(0));

    // Copy constructor

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

    template<typename blDataType2>
    blMatrix3d(const blDataType2 (&matrixArray)[3][3]);

    // Constructor builds
    // matrix from a
    // two-dimensional array
    // of different dimensions

    template<typename blDataType2,int m,int n>
    blMatrix3d(const blDataType2 (&matrixArray)[m][n]);

    // Virtual destructor

    ~blMatrix3d()
    {
    }

public: // Overloaded operators

    // Overloaded index operators

    blDataType*                         operator[](const int& rowIndex);
    const blDataType*                   operator[](const int& rowIndex)const;

    blDataType&                         operator()(const int& dataIndex);
    const blDataType&                   operator()(const int& dataIndex)const;

    blDataType&                         operator()(const int& rowIndex,const int& colIndex);
    const blDataType&                   operator()(const int& rowIndex,const int& colIndex)const;

    // Overloaded arithmetic operators

    blMatrix3d<blDataType>              operator-()const;
    blMatrix3d<blDataType>&             operator+=(const blMatrix3d<blDataType>& M);
    blMatrix3d<blDataType>&             operator-=(const blMatrix3d<blDataType>& M);
    blMatrix3d<blDataType>&             operator*=(const blDataType& scalar);
    blMatrix3d<blDataType>&             operator/=(const blDataType& scalar);

    blMatrix3d<blDataType>              operator+(const blMatrix3d<blDataType>& M)const;
    blMatrix3d<blDataType>              operator-(const blMatrix3d<blDataType>& M)const;
    blMatrix3d<blDataType>              operator*(const blDataType& scalar)const;
    blMatrix3d<blDataType>              operator/(const blDataType& scalar)const;

    blMatrix3d<blDataType>              operator*(const blMatrix3d<blDataType>& M)const;

private: // Private variables

    // 3x3 matrix components

    blDataType                          M[3][3];
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
template<typename blDataType2>
inline blMatrix3d<blDataType>::blMatrix3d(const blMatrix3d<blDataType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = static_cast<blDataType>(matrix[0][0]);
    M[0][1] = static_cast<blDataType>(matrix[0][1]);
    M[0][2] = static_cast<blDataType>(matrix[0][2]);
    M[1][0] = static_cast<blDataType>(matrix[1][0]);
    M[1][1] = static_cast<blDataType>(matrix[1][1]);
    M[1][2] = static_cast<blDataType>(matrix[1][2]);
    M[2][0] = static_cast<blDataType>(matrix[2][0]);
    M[2][1] = static_cast<blDataType>(matrix[2][1]);
    M[2][2] = static_cast<blDataType>(matrix[2][2]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>
inline blMatrix3d<blDataType>::blMatrix3d(const blDataType2 (&matrixArray)[3][3])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = static_cast<blDataType>(matrixArray[0][0]);
    M[0][1] = static_cast<blDataType>(matrixArray[0][1]);
    M[0][2] = static_cast<blDataType>(matrixArray[0][2]);
    M[1][0] = static_cast<blDataType>(matrixArray[1][0]);
    M[1][1] = static_cast<blDataType>(matrixArray[1][1]);
    M[1][2] = static_cast<blDataType>(matrixArray[1][2]);
    M[2][0] = static_cast<blDataType>(matrixArray[2][0]);
    M[2][1] = static_cast<blDataType>(matrixArray[2][1]);
    M[2][2] = static_cast<blDataType>(matrixArray[2][2]);
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
            M[i][j] = static_cast<blDataType>(matrixArray[i][j]);
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType* blMatrix3d<blDataType>::operator[](const int& rowIndex)
{
    return &M[rowIndex][0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType* blMatrix3d<blDataType>::operator[](const int& rowIndex)const
{
    return &M[rowIndex][0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blMatrix3d<blDataType>::operator()(const int& dataIndex)
{
    return M[0][dataIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blMatrix3d<blDataType>::operator()(const int& dataIndex)const
{
    return M[0][dataIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blMatrix3d<blDataType>::operator()(const int& rowIndex,const int& colIndex)
{
    return M[rowIndex][colIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blMatrix3d<blDataType>::operator()(const int& rowIndex,const int& colIndex)const
{
    return M[rowIndex][colIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator-()const
{
    return blMatrix3d<blDataType>(-M[0][0],-M[0][1],-M[0][2],
                                  -M[1][0],-M[1][1],-M[1][2],
                                  -M[2][0],-M[2][1],-M[2][2]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator+=(const blMatrix3d<blDataType>& matrix)
{
    M[0][0] += matrix[0][0];
    M[0][1] += matrix[0][1];
    M[0][2] += matrix[0][2];
    M[1][0] += matrix[1][0];
    M[1][1] += matrix[1][1];
    M[1][2] += matrix[1][2];
    M[2][0] += matrix[2][0];
    M[2][1] += matrix[2][1];
    M[2][2] += matrix[2][2];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType>& blMatrix3d<blDataType>::operator-=(const blMatrix3d<blDataType>& matrix)
{
    M[0][0] -= matrix[0][0];
    M[0][1] -= matrix[0][1];
    M[0][2] -= matrix[0][2];
    M[1][0] -= matrix[1][0];
    M[1][1] -= matrix[1][1];
    M[1][2] -= matrix[1][2];
    M[2][0] -= matrix[2][0];
    M[2][1] -= matrix[2][1];
    M[2][2] -= matrix[2][2];

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
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator*(const blDataType& scalar)const
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
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator/(const blDataType& scalar)const
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
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator*(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix3d<blDataType> result;

    result[0][0] = M[0][0]*matrix[0][0] + M[0][1]*matrix[1][0] + M[0][2]*matrix[2][0];
    result[0][1] = M[0][0]*matrix[0][1] + M[0][1]*matrix[1][1] + M[0][2]*matrix[2][1];
    result[0][2] = M[0][0]*matrix[0][2] + M[0][1]*matrix[1][2] + M[0][2]*matrix[2][2];
    result[1][0] = M[1][0]*matrix[0][0] + M[1][1]*matrix[1][0] + M[1][2]*matrix[2][0];
    result[1][1] = M[1][0]*matrix[0][1] + M[1][1]*matrix[1][1] + M[1][2]*matrix[2][1];
    result[1][2] = M[1][0]*matrix[0][2] + M[1][1]*matrix[1][2] + M[1][2]*matrix[2][2];
    result[2][0] = M[2][0]*matrix[0][0] + M[2][1]*matrix[1][0] + M[2][2]*matrix[2][0];
    result[2][1] = M[2][0]*matrix[0][1] + M[2][1]*matrix[1][1] + M[2][2]*matrix[2][1];
    result[2][2] = M[2][0]*matrix[0][2] + M[2][1]*matrix[1][2] + M[2][2]*matrix[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator+(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix3d<blDataType> result;

    result[0][0] = M[0][0] + matrix[0][0];
    result[0][1] = M[0][1] + matrix[0][1];
    result[0][2] = M[0][2] + matrix[0][2];
    result[1][0] = M[1][0] + matrix[1][0];
    result[1][1] = M[1][1] + matrix[1][1];
    result[1][2] = M[1][2] + matrix[1][2];
    result[2][0] = M[2][0] + matrix[2][0];
    result[2][1] = M[2][1] + matrix[2][1];
    result[2][2] = M[2][2] + matrix[2][2];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix3d<blDataType> blMatrix3d<blDataType>::operator-(const blMatrix3d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix3d<blDataType> result;

    result[0][0] = M[0][0] - matrix[0][0];
    result[0][1] = M[0][1] - matrix[0][1];
    result[0][2] = M[0][2] - matrix[0][2];
    result[1][0] = M[1][0] - matrix[1][0];
    result[1][1] = M[1][1] - matrix[1][1];
    result[1][2] = M[1][2] - matrix[1][2];
    result[2][0] = M[2][0] - matrix[2][0];
    result[2][1] = M[2][1] - matrix[2][1];
    result[2][2] = M[2][2] - matrix[2][2];

    return result;
}
//-------------------------------------------------------------------


#endif // BL_MATRIX3D_HPP
