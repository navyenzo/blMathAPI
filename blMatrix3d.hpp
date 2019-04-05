#ifndef BL_MATRIX3D_HPP
#define BL_MATRIX3D_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple 3x3 matrix class
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
#include "blMatrix2dOperations.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
class blMatrix3d
{
public: // Default constructor and destructor



    // Default constructor

    blMatrix3d(const blNumberType& initialValue = blNumberType(0));



    // Copy constructor

    template<typename blNumberType2>
    blMatrix3d(const blMatrix3d<blNumberType2>& matrix);



    // Constructor using
    // 9 distinct values

    blMatrix3d(const blNumberType& M00,const blNumberType& M01,const blNumberType& M02,
               const blNumberType& M10,const blNumberType& M11,const blNumberType& M12,
               const blNumberType& M20,const blNumberType& M21,const blNumberType& M22);



    // Constructor builds
    // matrix from a 3x3
    // two-dimensional array

    template<typename blNumberType2>
    blMatrix3d(const blNumberType2 (&matrixArray)[3][3]);



    // Constructor builds
    // matrix from a
    // two-dimensional array
    // of different dimensions

    template<typename blNumberType2,int m,int n>
    blMatrix3d(const blNumberType2 (&matrixArray)[m][n]);



    // Destructor

    ~blMatrix3d()
    {
    }



public: // Overloaded operators



    // Overloaded index operators

    blNumberType*                           operator[](const int& rowIndex);
    const blNumberType*                     operator[](const int& rowIndex)const;

    blNumberType&                           operator()(const int& dataIndex);
    const blNumberType&                     operator()(const int& dataIndex)const;

    blNumberType&                           operator()(const int& rowIndex,const int& colIndex);
    const blNumberType&                     operator()(const int& rowIndex,const int& colIndex)const;



    // Overloaded arithmetic operators

    blMatrix3d<blNumberType>                operator-()const;
    blMatrix3d<blNumberType>&               operator+=(const blMatrix3d<blNumberType>& m_matrix);
    blMatrix3d<blNumberType>&               operator-=(const blMatrix3d<blNumberType>& m_matrix);
    blMatrix3d<blNumberType>&               operator*=(const blNumberType& scalar);
    blMatrix3d<blNumberType>&               operator/=(const blNumberType& scalar);

    blMatrix3d<blNumberType>                operator+(const blMatrix3d<blNumberType>& m_matrix)const;
    blMatrix3d<blNumberType>                operator-(const blMatrix3d<blNumberType>& m_matrix)const;
    blMatrix3d<blNumberType>                operator*(const blNumberType& scalar)const;
    blMatrix3d<blNumberType>                operator/(const blNumberType& scalar)const;

    blMatrix3d<blNumberType>                operator*(const blMatrix3d<blNumberType>& m_matrix)const;



private: // Private variables



    // 3x3 matrix components

    blNumberType                            m_matrix[3][3];
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>::blMatrix3d(const blNumberType& initialValue)
{
    // Initialize all values to
    // the passed value

    m_matrix[0][0] = initialValue;
    m_matrix[0][1] = initialValue;
    m_matrix[0][2] = initialValue;
    m_matrix[1][0] = initialValue;
    m_matrix[1][1] = initialValue;
    m_matrix[1][2] = initialValue;
    m_matrix[2][0] = initialValue;
    m_matrix[2][1] = initialValue;
    m_matrix[2][2] = initialValue;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>::blMatrix3d(const blNumberType& M00,
                                            const blNumberType& M01,
                                            const blNumberType& M02,
                                            const blNumberType& M10,
                                            const blNumberType& M11,
                                            const blNumberType& M12,
                                            const blNumberType& M20,
                                            const blNumberType& M21,
                                            const blNumberType& M22)
{
    // Initialize all values
    // to their specified
    // initial value

    m_matrix[0][0] = M00;
    m_matrix[0][1] = M01;
    m_matrix[0][2] = M02;
    m_matrix[1][0] = M10;
    m_matrix[1][1] = M11;
    m_matrix[1][2] = M12;
    m_matrix[2][0] = M20;
    m_matrix[2][1] = M21;
    m_matrix[2][2] = M22;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blMatrix3d<blNumberType>::blMatrix3d(const blMatrix3d<blNumberType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    m_matrix[0][0] = static_cast<blNumberType>(matrix[0][0]);
    m_matrix[0][1] = static_cast<blNumberType>(matrix[0][1]);
    m_matrix[0][2] = static_cast<blNumberType>(matrix[0][2]);
    m_matrix[1][0] = static_cast<blNumberType>(matrix[1][0]);
    m_matrix[1][1] = static_cast<blNumberType>(matrix[1][1]);
    m_matrix[1][2] = static_cast<blNumberType>(matrix[1][2]);
    m_matrix[2][0] = static_cast<blNumberType>(matrix[2][0]);
    m_matrix[2][1] = static_cast<blNumberType>(matrix[2][1]);
    m_matrix[2][2] = static_cast<blNumberType>(matrix[2][2]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blMatrix3d<blNumberType>::blMatrix3d(const blNumberType2 (&matrixArray)[3][3])
{
    // Copy values from the
    // array into this matrix

    m_matrix[0][0] = static_cast<blNumberType>(matrixArray[0][0]);
    m_matrix[0][1] = static_cast<blNumberType>(matrixArray[0][1]);
    m_matrix[0][2] = static_cast<blNumberType>(matrixArray[0][2]);
    m_matrix[1][0] = static_cast<blNumberType>(matrixArray[1][0]);
    m_matrix[1][1] = static_cast<blNumberType>(matrixArray[1][1]);
    m_matrix[1][2] = static_cast<blNumberType>(matrixArray[1][2]);
    m_matrix[2][0] = static_cast<blNumberType>(matrixArray[2][0]);
    m_matrix[2][1] = static_cast<blNumberType>(matrixArray[2][1]);
    m_matrix[2][2] = static_cast<blNumberType>(matrixArray[2][2]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2,int m,int n>
inline blMatrix3d<blNumberType>::blMatrix3d(const blNumberType2 (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    m_matrix[0][0] = 0;
    m_matrix[0][1] = 0;
    m_matrix[0][2] = 0;
    m_matrix[1][0] = 0;
    m_matrix[1][1] = 0;
    m_matrix[1][2] = 0;
    m_matrix[2][0] = 0;
    m_matrix[2][1] = 0;
    m_matrix[2][2] = 0;

    // Loop and assign
    // the values

    for(int i = 0; i < 2 && i < m; ++i)
    {
        for(int j = 0; j < 2 && j < n; ++j)
        {
            m_matrix[i][j] = static_cast<blNumberType>(matrixArray[i][j]);
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType* blMatrix3d<blNumberType>::operator[](const int& rowIndex)
{
    return &m_matrix[rowIndex][0];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType* blMatrix3d<blNumberType>::operator[](const int& rowIndex)const
{
    return &m_matrix[rowIndex][0];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blMatrix3d<blNumberType>::operator()(const int& dataIndex)
{
    return m_matrix[0][dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blMatrix3d<blNumberType>::operator()(const int& dataIndex)const
{
    return m_matrix[0][dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blMatrix3d<blNumberType>::operator()(const int& rowIndex,const int& colIndex)
{
    return m_matrix[rowIndex][colIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blMatrix3d<blNumberType>::operator()(const int& rowIndex,const int& colIndex)const
{
    return m_matrix[rowIndex][colIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator-()const
{
    return blMatrix3d<blNumberType>(-m_matrix[0][0],-m_matrix[0][1],-m_matrix[0][2],
                                    -m_matrix[1][0],-m_matrix[1][1],-m_matrix[1][2],
                                    -m_matrix[2][0],-m_matrix[2][1],-m_matrix[2][2]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>& blMatrix3d<blNumberType>::operator+=(const blMatrix3d<blNumberType>& matrix)
{
    m_matrix[0][0] += matrix[0][0];
    m_matrix[0][1] += matrix[0][1];
    m_matrix[0][2] += matrix[0][2];
    m_matrix[1][0] += matrix[1][0];
    m_matrix[1][1] += matrix[1][1];
    m_matrix[1][2] += matrix[1][2];
    m_matrix[2][0] += matrix[2][0];
    m_matrix[2][1] += matrix[2][1];
    m_matrix[2][2] += matrix[2][2];

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>& blMatrix3d<blNumberType>::operator-=(const blMatrix3d<blNumberType>& matrix)
{
    m_matrix[0][0] -= matrix[0][0];
    m_matrix[0][1] -= matrix[0][1];
    m_matrix[0][2] -= matrix[0][2];
    m_matrix[1][0] -= matrix[1][0];
    m_matrix[1][1] -= matrix[1][1];
    m_matrix[1][2] -= matrix[1][2];
    m_matrix[2][0] -= matrix[2][0];
    m_matrix[2][1] -= matrix[2][1];
    m_matrix[2][2] -= matrix[2][2];

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>& blMatrix3d<blNumberType>::operator*=(const blNumberType& scalar)
{
    m_matrix[0][0] *= scalar;
    m_matrix[0][1] *= scalar;
    m_matrix[0][2] *= scalar;
    m_matrix[1][0] *= scalar;
    m_matrix[1][1] *= scalar;
    m_matrix[1][2] *= scalar;
    m_matrix[2][0] *= scalar;
    m_matrix[2][1] *= scalar;
    m_matrix[2][2] *= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType>& blMatrix3d<blNumberType>::operator/=(const blNumberType& scalar)
{
    m_matrix[0][0] /= scalar;
    m_matrix[0][1] /= scalar;
    m_matrix[0][2] /= scalar;
    m_matrix[1][0] /= scalar;
    m_matrix[1][1] /= scalar;
    m_matrix[1][2] /= scalar;
    m_matrix[2][0] /= scalar;
    m_matrix[2][1] /= scalar;
    m_matrix[2][2] /= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator*(const blNumberType& scalar)const
{
    return blMatrix3d<blNumberType>(m_matrix[0][0]*scalar,
                                  m_matrix[0][1]*scalar,
                                  m_matrix[0][2]*scalar,
                                  m_matrix[1][0]*scalar,
                                  m_matrix[1][1]*scalar,
                                  m_matrix[1][2]*scalar,
                                  m_matrix[2][0]*scalar,
                                  m_matrix[2][1]*scalar,
                                  m_matrix[2][2]*scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator/(const blNumberType& scalar)const
{
    return blMatrix3d<blNumberType>(m_matrix[0][0]/scalar,
                                  m_matrix[0][1]/scalar,
                                  m_matrix[0][2]/scalar,
                                  m_matrix[1][0]/scalar,
                                  m_matrix[1][1]/scalar,
                                  m_matrix[1][2]/scalar,
                                  m_matrix[2][0]/scalar,
                                  m_matrix[2][1]/scalar,
                                  m_matrix[2][2]/scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator*(const blMatrix3d<blNumberType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix3d<blNumberType> result;

    result[0][0] = m_matrix[0][0]*matrix[0][0] + m_matrix[0][1]*matrix[1][0] + m_matrix[0][2]*matrix[2][0];
    result[0][1] = m_matrix[0][0]*matrix[0][1] + m_matrix[0][1]*matrix[1][1] + m_matrix[0][2]*matrix[2][1];
    result[0][2] = m_matrix[0][0]*matrix[0][2] + m_matrix[0][1]*matrix[1][2] + m_matrix[0][2]*matrix[2][2];
    result[1][0] = m_matrix[1][0]*matrix[0][0] + m_matrix[1][1]*matrix[1][0] + m_matrix[1][2]*matrix[2][0];
    result[1][1] = m_matrix[1][0]*matrix[0][1] + m_matrix[1][1]*matrix[1][1] + m_matrix[1][2]*matrix[2][1];
    result[1][2] = m_matrix[1][0]*matrix[0][2] + m_matrix[1][1]*matrix[1][2] + m_matrix[1][2]*matrix[2][2];
    result[2][0] = m_matrix[2][0]*matrix[0][0] + m_matrix[2][1]*matrix[1][0] + m_matrix[2][2]*matrix[2][0];
    result[2][1] = m_matrix[2][0]*matrix[0][1] + m_matrix[2][1]*matrix[1][1] + m_matrix[2][2]*matrix[2][1];
    result[2][2] = m_matrix[2][0]*matrix[0][2] + m_matrix[2][1]*matrix[1][2] + m_matrix[2][2]*matrix[2][2];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator+(const blMatrix3d<blNumberType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix3d<blNumberType> result;

    result[0][0] = m_matrix[0][0] + matrix[0][0];
    result[0][1] = m_matrix[0][1] + matrix[0][1];
    result[0][2] = m_matrix[0][2] + matrix[0][2];
    result[1][0] = m_matrix[1][0] + matrix[1][0];
    result[1][1] = m_matrix[1][1] + matrix[1][1];
    result[1][2] = m_matrix[1][2] + matrix[1][2];
    result[2][0] = m_matrix[2][0] + matrix[2][0];
    result[2][1] = m_matrix[2][1] + matrix[2][1];
    result[2][2] = m_matrix[2][2] + matrix[2][2];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix3d<blNumberType> blMatrix3d<blNumberType>::operator-(const blMatrix3d<blNumberType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix3d<blNumberType> result;

    result[0][0] = m_matrix[0][0] - matrix[0][0];
    result[0][1] = m_matrix[0][1] - matrix[0][1];
    result[0][2] = m_matrix[0][2] - matrix[0][2];
    result[1][0] = m_matrix[1][0] - matrix[1][0];
    result[1][1] = m_matrix[1][1] - matrix[1][1];
    result[1][2] = m_matrix[1][2] - matrix[1][2];
    result[2][0] = m_matrix[2][0] - matrix[2][0];
    result[2][1] = m_matrix[2][1] - matrix[2][1];
    result[2][2] = m_matrix[2][2] - matrix[2][2];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_MATRIX3D_HPP
