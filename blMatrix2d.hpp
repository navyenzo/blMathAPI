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
class blMatrix2d
{
public: // Default constructor and destructor

    // Default constructor

    blMatrix2d(const blDataType& initialValue = blDataType(0));

    // Copy constructor

    template<typename blDataType2>
    blMatrix2d(const blMatrix2d<blDataType2>& matrix);

    // Constructor using
    // 4 distinct values

    blMatrix2d(const blDataType& M00,const blDataType& M01,
               const blDataType& M10,const blDataType& M11);

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
    // type and different
    // dimensions

    template<typename blDataType2,int m,int n>
    blMatrix2d(const blDataType2 (&matrixArray)[m][n]);

    // Virtual destructor

    ~blMatrix2d()
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

    blMatrix2d<blDataType>              operator-()const;
    blMatrix2d<blDataType>&             operator+=(const blMatrix2d<blDataType>& matrix);
    blMatrix2d<blDataType>&             operator-=(const blMatrix2d<blDataType>& matrix);
    blMatrix2d<blDataType>&             operator*=(const blDataType& scalar);
    blMatrix2d<blDataType>&             operator/=(const blDataType& scalar);

    blMatrix2d<blDataType>              operator+(const blMatrix2d<blDataType>& matrix)const;
    blMatrix2d<blDataType>              operator-(const blMatrix2d<blDataType>& matrix)const;
    blMatrix2d<blDataType>              operator*(const blDataType& scalar)const;
    blMatrix2d<blDataType>              operator/(const blDataType& scalar)const;

    blMatrix2d<blDataType>              operator*(const blMatrix2d<blDataType>& matrix)const;

private: // Private variables

    // 3x3 matrix components

    blDataType                          M[2][2];
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
    M[1][0] = initialValue;
    M[1][1] = initialValue;
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
template<typename blDataType2>
inline blMatrix2d<blDataType>::blMatrix2d(const blMatrix2d<blDataType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    M[0][0] = static_cast<blDataType>(matrix[0][0]);
    M[0][1] = static_cast<blDataType>(matrix[0][1]);
    M[1][0] = static_cast<blDataType>(matrix[1][0]);
    M[1][1] = static_cast<blDataType>(matrix[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
template<typename blDataType2>

inline blMatrix2d<blDataType>::blMatrix2d(const blDataType2 (&matrixArray)[2][2])
{
    // Copy values from the
    // array into this matrix

    M[0][0] = static_cast<blDataType>(matrixArray[0][0]);
    M[0][1] = static_cast<blDataType>(matrixArray[0][1]);
    M[1][0] = static_cast<blDataType>(matrixArray[1][0]);
    M[1][1] = static_cast<blDataType>(matrixArray[1][1]);
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
            M[i][j] = static_cast<blDataType>( matrixArray[i][j] );
        }
    }
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType* blMatrix2d<blDataType>::operator[](const int& rowIndex)
{
    return &M[rowIndex][0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType* blMatrix2d<blDataType>::operator[](const int& rowIndex)const
{
    return &M[rowIndex][0];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blMatrix2d<blDataType>::operator()(const int& dataIndex)
{
    return M[0][dataIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blMatrix2d<blDataType>::operator()(const int& dataIndex)const
{
    return M[0][dataIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blMatrix2d<blDataType>::operator()(const int& rowIndex,const int& colIndex)
{
    return M[rowIndex][colIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blMatrix2d<blDataType>::operator()(const int& rowIndex,const int& colIndex)const
{
    return M[rowIndex][colIndex];
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator-()const
{
    return blMatrix2d<blDataType>(-M[0][0],-M[0][1],-M[1][0],-M[1][1]);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator+=(const blMatrix2d<blDataType>& matrix)
{
    M[0][0] += matrix[0][0];
    M[0][1] += matrix[0][1];
    M[1][0] += matrix[1][0];
    M[1][1] += matrix[1][1];

    return (*this);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType>& blMatrix2d<blDataType>::operator-=(const blMatrix2d<blDataType>& matrix)
{
    M[0][0] -= matrix[0][0];
    M[0][1] -= matrix[0][1];
    M[1][0] -= matrix[1][0];
    M[1][1] -= matrix[1][1];

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
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator*(const blDataType& scalar)const
{
    return blMatrix2d<blDataType>(M[0][0]*scalar,
                                  M[0][1]*scalar,
                                  M[1][0]*scalar,
                                  M[1][1]*scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator/(const blDataType& scalar)const
{
    return blMatrix2d<blDataType>(M[0][0]/scalar,
                                  M[0][1]/scalar,
                                  M[1][0]/scalar,
                                  M[1][1]/scalar);
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator*(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix2d<blDataType> result;

    result[0][0] = M[0][0]*matrix[0][0] + M[0][1]*matrix[1][0];
    result[0][1] = M[0][0]*matrix[0][1] + M[0][1]*matrix[1][1];
    result[1][0] = M[1][0]*matrix[0][0] + M[1][1]*matrix[1][0];
    result[1][1] = M[1][0]*matrix[0][1] + M[1][1]*matrix[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator+(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix2d<blDataType> result;

    result[0][0] = M[0][0] + matrix[0][0];
    result[0][1] = M[0][1] + matrix[0][1];
    result[1][0] = M[1][0] + matrix[1][0];
    result[1][1] = M[1][1] + matrix[1][1];

    return result;
}
//-------------------------------------------------------------------


//-------------------------------------------------------------------
template<typename blDataType>
inline blMatrix2d<blDataType> blMatrix2d<blDataType>::operator-(const blMatrix2d<blDataType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix2d<blDataType> result;

    result[0][0] = M[0][0] - matrix[0][0];
    result[0][1] = M[0][1] - matrix[0][1];
    result[1][0] = M[1][0] - matrix[1][0];
    result[1][1] = M[1][1] - matrix[1][1];

    return result;
}
//-------------------------------------------------------------------


#endif // BL_MATRIX2D_HPP
