#ifndef BL_MATRIX2D_HPP
#define BL_MATRIX2D_HPP



///-------------------------------------------------------------------
///
///
///
/// PURPOSE:        A simple 2x2 matrix class
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
#include "blVector3dOperations.hpp"
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blMathAPI namespace
//-------------------------------------------------------------------
namespace blMathAPI
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
class blMatrix2d
{
public: // Default constructor and destructor



    // Default constructor

    blMatrix2d(const blNumberType& initialValue = blNumberType(0));



    // Copy constructor

    template<typename blNumberType2>
    blMatrix2d(const blMatrix2d<blNumberType2>& matrix);



    // Constructor using
    // 4 distinct values

    blMatrix2d(const blNumberType& M00,const blNumberType& M01,
               const blNumberType& M10,const blNumberType& M11);



    // Constructor builds
    // matrix from a 2x2
    // two-dimensional array
    // of different type

    template<typename blNumberType2>
    blMatrix2d(const blNumberType2 (&matrixArray)[2][2]);



    // Constructor builds
    // matrix from a
    // two-dimensional
    // array of different
    // type and different
    // dimensions

    template<typename blNumberType2,int m,int n>
    blMatrix2d(const blNumberType2 (&matrixArray)[m][n]);



    // Destructor

    ~blMatrix2d()
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

    blMatrix2d<blNumberType>                operator-()const;
    blMatrix2d<blNumberType>&               operator+=(const blMatrix2d<blNumberType>& matrix);
    blMatrix2d<blNumberType>&               operator-=(const blMatrix2d<blNumberType>& matrix);
    blMatrix2d<blNumberType>&               operator*=(const blNumberType& scalar);
    blMatrix2d<blNumberType>&               operator/=(const blNumberType& scalar);

    blMatrix2d<blNumberType>                operator+(const blMatrix2d<blNumberType>& matrix)const;
    blMatrix2d<blNumberType>                operator-(const blMatrix2d<blNumberType>& matrix)const;
    blMatrix2d<blNumberType>                operator*(const blNumberType& scalar)const;
    blMatrix2d<blNumberType>                operator/(const blNumberType& scalar)const;

    blMatrix2d<blNumberType>                operator*(const blMatrix2d<blNumberType>& matrix)const;



private: // Private variables



    // 3x3 matrix components

    blNumberType                            m_matrix[2][2];
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>::blMatrix2d(const blNumberType& initialValue)
{
    // Initialize all values to
    // the passed value

    m_matrix[0][0] = initialValue;
    m_matrix[0][1] = initialValue;
    m_matrix[1][0] = initialValue;
    m_matrix[1][1] = initialValue;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>::blMatrix2d(const blNumberType& M00,
                                            const blNumberType& M01,
                                            const blNumberType& M10,
                                            const blNumberType& M11)
{
    // Initialize all values to their
    // specified initial value

    m_matrix[0][0] = M00;
    m_matrix[0][1] = M01;
    m_matrix[1][0] = M10;
    m_matrix[1][1] = M11;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>
inline blMatrix2d<blNumberType>::blMatrix2d(const blMatrix2d<blNumberType2>& matrix)
{
    // Copy the inidividual
    // values to this matrix

    m_matrix[0][0] = static_cast<blNumberType>(matrix[0][0]);
    m_matrix[0][1] = static_cast<blNumberType>(matrix[0][1]);
    m_matrix[1][0] = static_cast<blNumberType>(matrix[1][0]);
    m_matrix[1][1] = static_cast<blNumberType>(matrix[1][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2>

inline blMatrix2d<blNumberType>::blMatrix2d(const blNumberType2 (&matrixArray)[2][2])
{
    // Copy values from the
    // array into this matrix

    m_matrix[0][0] = static_cast<blNumberType>(matrixArray[0][0]);
    m_matrix[0][1] = static_cast<blNumberType>(matrixArray[0][1]);
    m_matrix[1][0] = static_cast<blNumberType>(matrixArray[1][0]);
    m_matrix[1][1] = static_cast<blNumberType>(matrixArray[1][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
template<typename blNumberType2,int m,int n>

inline blMatrix2d<blNumberType>::blMatrix2d(const blNumberType2 (&matrixArray)[m][n])
{
    // Initialize the
    // values to zero

    m_matrix[0][0] = 0;
    m_matrix[0][1] = 0;
    m_matrix[1][0] = 0;
    m_matrix[1][1] = 0;

    // Loop and assign
    // the values

    for(int i = 0; i < 2 && i < m; ++i)
    {
        for(int j = 0; j < 2 && j < n; ++j)
        {
            m_matrix[i][j] = static_cast<blNumberType>( matrixArray[i][j] );
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType* blMatrix2d<blNumberType>::operator[](const int& rowIndex)
{
    return &m_matrix[rowIndex][0];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType* blMatrix2d<blNumberType>::operator[](const int& rowIndex)const
{
    return &m_matrix[rowIndex][0];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blMatrix2d<blNumberType>::operator()(const int& dataIndex)
{
    return m_matrix[0][dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blMatrix2d<blNumberType>::operator()(const int& dataIndex)const
{
    return m_matrix[0][dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blNumberType& blMatrix2d<blNumberType>::operator()(const int& rowIndex,const int& colIndex)
{
    return m_matrix[rowIndex][colIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline const blNumberType& blMatrix2d<blNumberType>::operator()(const int& rowIndex,const int& colIndex)const
{
    return m_matrix[rowIndex][colIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator-()const
{
    return blMatrix2d<blNumberType>(-m_matrix[0][0],-m_matrix[0][1],-m_matrix[1][0],-m_matrix[1][1]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>& blMatrix2d<blNumberType>::operator+=(const blMatrix2d<blNumberType>& matrix)
{
    m_matrix[0][0] += matrix[0][0];
    m_matrix[0][1] += matrix[0][1];
    m_matrix[1][0] += matrix[1][0];
    m_matrix[1][1] += matrix[1][1];

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>& blMatrix2d<blNumberType>::operator-=(const blMatrix2d<blNumberType>& matrix)
{
    m_matrix[0][0] -= matrix[0][0];
    m_matrix[0][1] -= matrix[0][1];
    m_matrix[1][0] -= matrix[1][0];
    m_matrix[1][1] -= matrix[1][1];

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>& blMatrix2d<blNumberType>::operator*=(const blNumberType& scalar)
{
    m_matrix[0][0] *= scalar;
    m_matrix[0][1] *= scalar;
    m_matrix[1][0] *= scalar;
    m_matrix[1][1] *= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType>& blMatrix2d<blNumberType>::operator/=(const blNumberType& scalar)
{
    m_matrix[0][0] /= scalar;
    m_matrix[0][1] /= scalar;
    m_matrix[1][0] /= scalar;
    m_matrix[1][1] /= scalar;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator*(const blNumberType& scalar)const
{
    return blMatrix2d<blNumberType>(m_matrix[0][0]*scalar,
                                    m_matrix[0][1]*scalar,
                                    m_matrix[1][0]*scalar,
                                    m_matrix[1][1]*scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator/(const blNumberType& scalar)const
{
    return blMatrix2d<blNumberType>(m_matrix[0][0]/scalar,
                                    m_matrix[0][1]/scalar,
                                    m_matrix[1][0]/scalar,
                                    m_matrix[1][1]/scalar);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator*(const blMatrix2d<blNumberType>& matrix)const
{
    // C[i][j] = Sum(A[i][k]*B[k][j])

    blMatrix2d<blNumberType> result;

    result[0][0] = m_matrix[0][0]*matrix[0][0] + m_matrix[0][1]*matrix[1][0];
    result[0][1] = m_matrix[0][0]*matrix[0][1] + m_matrix[0][1]*matrix[1][1];
    result[1][0] = m_matrix[1][0]*matrix[0][0] + m_matrix[1][1]*matrix[1][0];
    result[1][1] = m_matrix[1][0]*matrix[0][1] + m_matrix[1][1]*matrix[1][1];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator+(const blMatrix2d<blNumberType>& matrix)const
{
    // C[i][j] = A[i][j] + B[i][j])

    blMatrix2d<blNumberType> result;

    result[0][0] = m_matrix[0][0] + matrix[0][0];
    result[0][1] = m_matrix[0][1] + matrix[0][1];
    result[1][0] = m_matrix[1][0] + matrix[1][0];
    result[1][1] = m_matrix[1][1] + matrix[1][1];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blNumberType>
inline blMatrix2d<blNumberType> blMatrix2d<blNumberType>::operator-(const blMatrix2d<blNumberType>& matrix)const
{
    // C[i][j] = A[i][j] - B[i][j])

    blMatrix2d<blNumberType> result;

    result[0][0] = m_matrix[0][0] - matrix[0][0];
    result[0][1] = m_matrix[0][1] - matrix[0][1];
    result[1][0] = m_matrix[1][0] - matrix[1][0];
    result[1][1] = m_matrix[1][1] - matrix[1][1];

    return result;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of the blMathAPI namespace
}
//-------------------------------------------------------------------



#endif // BL_MATRIX2D_HPP
