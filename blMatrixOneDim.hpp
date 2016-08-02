//---------------------------------------------------------------------------------------
// CLASS:			vbMatrix<vbType>
// BASE CLASS:		None
// PURPOSE:			Matrix container with various algorithms
// AUTHOR:			Vincenzo Barbato
//					(713)402-8451
//					navyenzo@gmail.com
// DATE CREATED:	Aug/27/2009
// DATE UPDATED:
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
// Make sure we only load this file once
#ifndef _VBMATRIX_
#define _VBMATRIX_
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
class vbMatrix
{
public: // Default constructors and destructors

	// Default constructor builds an mxn matrix with an initialize value
	vbMatrix(const int& NumOfRows = 0,
			 const int& NumOfCols = 0,
			 const vbType& InitialValue = vbType(0));

	// Copy constructor
	vbMatrix(const vbMatrix<vbType>& Matrix);

	// Constructor builds matrix from a two dimensional array
	template<int m,int n>
	vbMatrix(const vbType (&MatrixArray)[m][n]);

	// Constructor builds matrix from augmenting two matrices
	vbMatrix(const vbMatrix<vbType>& M1,
			 const vbMatrix<vbType>& M2,
			 const bool& AreMatricesToBeAugmentedHorizontally);

	// Default destructor
	~vbMatrix(void);

public: // Overloaded operators

	// Used to access an individual value of the matrix in matrix format (i,j)
	vbType&									operator()(const int& i,const int& j);
	const vbType&							operator()(const int& i,const int& j)const;

	// Used to access an individual value of the matrix in array format (i) or [i]
	vbType&									operator()(const int& i);
	const vbType&							operator()(const int& i)const;
	vbType&									operator[](const int& i);
	const vbType&							operator[](const int& i)const;

	// Used for basic matrix operations
	vbMatrix<vbType>&						operator+=(const vbMatrix<vbType>& M);
	vbMatrix<vbType>&						operator-=(const vbMatrix<vbType>& M);
	vbMatrix<vbType>&						operator*=(const vbType& x);
	vbMatrix<vbType>&						operator*=(const vbMatrix<vbType>& M);
	vbMatrix<vbType>&						operator/=(const vbType& x);
	vbMatrix<vbType>&						operator/=(const vbMatrix<vbType>& M);
	void									operator++(int);
	vbMatrix<vbType>&						operator++();
	void									operator--(int);
	vbMatrix<vbType>&						operator--();

public: // Public variables

public: // Public functions

	// Used to get the matrix array
	vector<vbType>&							GetMatrixArray();
	const vector<vbType>&					GetMatrixArray()const;

	// Used to save the matrix to an xml file
	void									SaveToXml(CkXml* XmlFile,
													  const string& Name = "");
	bool									LoadFromXml(CkXml* XmlFile);

	// Used to re-zero the matrix
	void									ReZero();

	// Functions derived from std::vector
	void									clear();
	const int&								size()const;
	vbType&									front();
	const vbType&							front()const;

	// Used to round-off all values in the matrix
	void									RoundOff(const int& Precision);

	// Used to make a matrix square (if it's not already square)
	// by adding zero rows or columns as needed
	void									MakeSquare();

	// Used to set a block of the matrix using another matrix
	void									SetMatrixBlock(const int& i,
														   const int& j,
														   const vbMatrix<vbType>& M);

	// Used to get block-matrices from this matrix
	vbMatrix<vbType>						GetMatrixBlock(const int& i1,
														   const int& j1,
														   const int& i2,
														   const int& j2);
	void									GetMatrixBlock(const int& i1,
														   const int& j1,
														   const int& i2,
														   const int& j2,
														   vbMatrix<vbType>& M);

	void									GetMatrixBlocks(vbMatrix<vbType>& A,vbMatrix<vbType>& B,
															vbMatrix<vbType>& C,vbMatrix<vbType>& D);
	void									GetMatrixBlocks2(vbMatrix<vbType>& A,vbMatrix<vbType>& B,
															 vbMatrix<vbType>& C,vbMatrix<vbType>& D);

	// Used to define a zero (where anything smaller than this number
	// might as well be considered zero due to the finite machine precision)
	vbType									DefineZero();

	// Static functions used to create unit row or column vectors
	static vbMatrix<vbType>					CreateUnitRowVector(const int& NumOfCols,
																const int& WhichComponentToMakeUnity);
	static vbMatrix<vbType>					CreateUnitColVector(const int& NumOfRows,
																const int& WhichComponentToMakeUnity);

	// Used to zero out all the very small values in the matrix
	void									CleanZeroes(const vbType& Zero);

	// Used to get row/column vectors from this matrix
	const vbMatrix<vbType>					GetRowVector(const int& i)const;
	const vbMatrix<vbType>					GetColVector(const int& i)const;

	// Used to get the magnitude of a row or column vector
	vbType									GetRowVectorMagnitude(const int& WhichRow);
	vbType									GetColVectorMagnitude(const int& WhichColumn);

	// Used to get non-zero column vector(s) from this matrix
	vbMatrix<vbType>						GetNonZeroColVectors(const vbType& Zero,
																 const int& NumOfNonZeroVectorsToGet);

	// Functions used to randomize the matrix
	void									Mutate(const vbType& MutationAmountPercentage);
	void									RandomizeMatrix(const vbType& MinValue,
															const vbType& MaxValue);
	void									RandomizeMatrixIntelligently(const vbType& MinValue,
																		 const vbType& MaxValue,
																		 const vbType& SmoothnessConstant);

	void									RowSwap(const int& Row1,const int& Row2);
	void									ColSwap(const int& Col1,const int& Col2);

	void									Normalize();
	void									OrthoNormalizeMatrix();
	const vbMatrix<vbType>					GetNormalizedMatrix()const;
	const vbMatrix<vbType>					GetOrthonormalizedMatrix()const;

	const int&								GetNumOfRows()const;
	const int&								GetNumOfCols()const;

	void									SetRowVector(const int& i,const vbMatrix<vbType>& Vector);
	void									SetColVector(const int& i,const vbMatrix<vbType>& Vector);

	void									AddZeroRowVectors(const int& NumOfRowVectorsToAdd);
	void									AddZeroColVectors(const int& NumOfColVectorsToAdd);
	void									AddRowVector(const vbMatrix<vbType>& RowVector);
	void									AddColVector(const vbMatrix<vbType>& ColVector);
	
private: // Private variables

	// Matrix array (holds the matrix values)
	vector<vbType>							m_Matrix;

	// Variables used to hold the size of the matrix
	int										m_NumOfRows;
	int										m_NumOfCols;

private: // Private functions
};
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>::~vbMatrix(void)
{
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>::vbMatrix(const int& NumOfRows,
								  const int& NumOfCols,
								  const vbType& InitialValue)
{
	// Store the number of rows and columns
	m_NumOfRows = NumOfRows;
	m_NumOfCols = NumOfCols;

	// The matrix will have m_NumOfRows*m_NumOfCols values in it
	m_Matrix = vector<vbType>((m_NumOfRows*m_NumOfCols),InitialValue);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>::vbMatrix(const vbMatrix<vbType>& Matrix)
{
	// Copy the matrix size
	m_NumOfRows = Matrix.GetNumOfRows();
	m_NumOfCols = Matrix.GetNumOfCols();

	// Copy the matrix
	m_Matrix = Matrix.GetMatrixArray();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>::vbMatrix(const vbMatrix<vbType>& M1,const vbMatrix<vbType>& M2,
								  const bool& AreMatricesToBeAugmentedHorizontally)
{
	// Let's get the number of rows and columns of the two matrices
	int m1 = M1.GetNumOfRows();
	int n1 = M1.GetNumOfCols();
	int m2 = M2.GetNumOfRows();
	int n2 = M2.GetNumOfCols();

	// Let's check which way we have to augment the matrices,
	// where we either stack the matrices side to side or
	// stack them vertically
	if(AreMatricesToBeAugmentedHorizontally)
	{
		// Check which matrix has more rows and reserve the
		// necessary memory size of the new matrix accordingly
		if(m1 >= m2)
			(*this) = vbMatrix(m1,n1+n2,0);
		else
			(*this) = vbMatrix(m2,n1+n2,0);

		// Use the two matrices to fill the new matrix values
		SetMatrixBlock(0,0,M1);
		SetMatrixBlock(0,n1,M2);
	}
	else
	{
		// Check which matrix has more columns and reserve the
		// necessary memory size of the new matrix accordingly
		if(n1 >= n2)
			(*this) = vbMatrix(m1+m2,n1,0);
		else
			(*this) = vbMatrix(m1+m2,n2,0);

		// Use the two matrices to fill the new matrix values
		SetMatrixBlock(0,0,M1);
		SetMatrixBlock(m1,0,M2);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
template<int m,int n>
inline vbMatrix<vbType>::vbMatrix(const vbType (&a)[m][n])
{
	// Store the number of rows and columns
	m_NumOfRows = m;
	m_NumOfCols = n;

	// Create the matrix array
	m_Matrix = vector<vbType>((m_NumOfRows*m_NumOfCols),0);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			for(int j = 0; j < m_NumOfColumns; ++j)
				(*this)(i,j) = a[i][j];
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vector<vbType>& vbMatrix<vbType>::GetMatrixArray()
{
	return m_Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vector<vbType>& vbMatrix<vbType>::GetMatrixArray()const
{
	return m_Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::clear()
{
	// Reset the number of rows and columns to zero
	m_NumOfRows = 0;
	m_NumOfCols = 0;

	// Clear the entire matrix array
	m_Matrix.clear();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const int& vbMatrix<vbType>::size()const
{
	return m_Matrix.size();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType& vbMatrix<vbType>::front()
{
	return m_Matrix.front();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbType& vbMatrix<vbType>::front()const
{
	return m_Matrix.front();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::ReZero()
{
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			for(int j = 0; j < m_NumOfColumns; ++j)
				(*this)(i,j) = vbType(0);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::RoundOff(const int& Precision)
{
	// Step through all the values and round-off each value to
	// the desired precision
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			for(int j = 0; j < m_NumOfColumns; ++j)
				(*this)(i,j) = vbMath::RoundOff((*this)(i,j),Precision);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::MakeSquare()
{
	// Check the matrix size and do the following
	if(m_NumOfRows == m_NumOfCols)
	{
		// The matrix is already square, so we just return
		return;
	}
	
	if(m_NumOfRows > m_NumOfCols)
	{
		// There are more rows than columns, so we add zero columns
		AddZeroColVectors(m_NumOfRows - m_NumOfCols);
		return;
	}
	
	if(m_NumOfRows < m_NumOfCols)
	{
		// There are more columns than rows, so we add zero rows
		AddZeroRowVectors(m_NumOfCols - m_NumOfRows);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType vbMatrix<vbType>::DefineZero()
{
	// Define what it means to be zero
	if(m_NumOfRows >= m_NumOfCols)
		return (numeric_limits<vbType>::epsilon() * m_NumOfRows * vbType(10) * Norm1(*this));
	else
		return (numeric_limits<vbType>::epsilon() * m_NumOfCols * vbType(10) * NormInf(*this));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
static inline vbMatrix<vbType> vbMatrix<vbType>::CreateUnitRowVector(const int& NumOfCols,
																	 const int& WhichComponentToMakeUnity)
{
	// Check index validity
	if(WhichComponentToMakeUnity < 0 || WhichComponentToMakeUnity >= NumOfCols)
		return CreateUnitRowVector<vbType>(NumOfCols,0);

	vbMatrix<vbType> Matrix(1,NumOfCols,0);
	Matrix(0,WhichComponentToMakeUnity) = vbType(1);

	return Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
static inline vbMatrix<vbType> vbMatrix<vbType>::CreateUnitColVector(const int& NumOfRows,
																	 const int& WhichComponentToMakeUnity)
{
	// Check index validity
	if(WhichComponentToMakeUnity < 0 || WhichComponentToMakeUnity >= NumOfRows)
		return CreateUnitColVector<vbType>(NumOfRows,0);

	vbMatrix<vbType> Matrix(NumOfRows,1,0);
	Matrix(WhichComponentToMakeUnity,0) = vbType(1);

	return Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbMatrix<vbType> vbMatrix<vbType>::GetRowVector(const int& i)const
{
	if(i >= m_NumOfRows)
	{
		GlobalErrorLog += "\nTried to access row vector outside of matrix range";
		return vbMatrix<vbType> EmptyMatrix;
	}
	else
	{
		vbMatrix<vbType> RowVector(1,m_NumOfCols,0);
		for(int j = 0; j < m_NumOfCols; ++j)
			RowVector(0,j) = (*this)(i,j);

		return RowVector;
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbMatrix<vbType> vbMatrix<vbType>::GetColVector(const int& i)const
{
	if(i >= m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to access col vector outside of matrix range";
		return vbMatrix<vbType>(0,0,vbType(0));
	}
	else
	{
		vbMatrix<vbType> ColVector(m_NumOfRows,1,0);
		for(int j = 0; j < m_NumOfRows; ++j)
			ColVector(j,0) = (*this)(j,i);
			
		return ColVector;
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType vbMatrix<vbType>::GetRowVectorMagnitude(const int& WhichRow)
{
	// Check index validity
	if(i < 0 || i >= m_NumOfRows)
	{
		GlobalErrorLog += "\nTried to calculate the magnitude of a row vector using the wrong index";
		return vbType(0);
	}

	vbType Mag = 0;

	for(int j = 0; j < m_NumOfCols; ++j)
		Mag += ((*this)(WhichRow,j) * (*this)(WhichRow,j));

	return std::sqrt(Mag);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType vbMatrix<vbType>::GetColVectorMagnitude(const int& WhichColumn)
{
	// Check index validity
	if(i < 0 || i >= m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to calculate the magnitude of a col vector with out of bounds index";
		return vbType(0);
	}

	vbType Mag = 0;

	for(int j = 0; j < m_NumOfRows; ++j)
		Mag += ((*this)(j,WhichColumn) * (*this)(j,WhichColumn));

	return std::sqrt(Mag);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> vbMatrix<vbType>::GetNonZeroColVectors(const vbType& Zero,
															   const int& NumOfNonZeroVectorsToGet)
{
	// Check for input validity
	if(NumOfNonZeroVectorsToGet > m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to get more non-zero column vectors from matrix than there are column in this matrix";
		return GetNonZeroColVectors(Zero,m_NumOfCols);
	}

	if(NumOfNonZeroVectorsToGet <= 0)
	{
		GlobalErrorLog += "\nTried to get a \"negative\" number of non-zero column vectors from matrix, which doesn't make any sense";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Prepare the NonZeroColVectors matrix
	vbMatrix<vbType> NonZeroColVectors(0,0,0);

	// Index used to keep track of non zero vectors
	int Index;

	// Get the first non zero col vector from the matrix
	for(int i = 0; i < m_NumOfRows; ++i)
	{
		for(int j = 0; j < m_NumOfCols; ++j)
		{
			if(!(EqualsZero(at(i,j),Zero)))
			{
				NonZeroColVectors.AddColVector(GetColVector(j));
				Index = j;

				// break from both for loops
				i = m_NumOfRows;
				j = m_NumOfCols;
			}
		}
	}

	// If only one vector is needed then return
	if(NumOfNonZeroVectorsToGet == 1)
		return NonZeroColVectors;

	// Go through all the vectors until we have found
	// the needed independent non-zero vectors
	for(int i = Index+1; i < m_NumOfCols; ++i)
	{
		// Add the next vector to the NonZeroColVectors matrix and check the rank
		// If it has full rank, then keep it, otherwise discard it and move on to the next
		// col vector
		vbMatrix<vbType> CCC = vbMatrix<vbType>(NonZeroColVectors,GetColVector(i),true);
		if(rank(CCC,Zero) == (NonZeroColVectors.GetNumOfCols() + 1))
			NonZeroColVectors.AddColVector(GetColVector(i));

		// Check if it found all the needed independent vectors
		if(NonZeroColVectors.GetNumOfCols() >= NumOfNonZeroVectorsToGet)
			return NonZeroColVectors;
	}

	return NonZeroColVectors;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::GetMatrixBlock(const int& i1,
											 const int& j1,
											 const int& i2,
											 const int& j2,
											 vbMatrix<vbType>& M)
{
	// Check for index validity
	if((i1 < 0) || (j1 < 0) || (i2 < 0) || (j2 < 0) ||
	   (i1 > m_NumOfRows) || (j1 > m_NumOfCols) || (i2 > m_NumOfRows) || (j2> m_NumOfCols))
	{
		GlobalErrorLog += "\nUsed wrong indeces when trying to access a matrix sub-block";
		return;
	}

	// Sort the indeces
	if(i1 > i2)
		std::swap(i1,i2);
	if(j1 > j2)
		std::swap(j1,j2);

	// Initialize the matrix
	M = vbMatrix<vbType>(i2-i1+1,j2-j1+1,0);

	for(int i = i1; i <= i2; ++i)
		for(int j = j1; j <= j2; ++j)
			M(i-i1,j-j1) = m_Matrix[i][j];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> vbMatrix<vbType>::GetMatrixBlock(const int& i1,
														 const int& j1,
														 const int& i2,
														 const int& j2)
{
	// Check for index validity
	if((i1 < 0) || (j1 < 0) || (i2 < 0) || (j2 < 0) ||
	   (i1 >= m_NumOfRows) || (j1 >= m_NumOfCols) || (i2 >= m_NumOfRows) || (j2>= m_NumOfCols))
	{
		GlobalErrorLog += "\nUsed wrong indeces when trying to access a matrix sub-block";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Sort the indeces
	if(i1 > i2)
		std::swap(i1,i2);
	if(j1 > j2)
		std::swap(j1,j2);

	// Initialize the matrix
	vbMatrix<vbType> M = vbMatrix<vbType>(i2-i1+1,j2-j1+1,0);

	for(int i = i1; i <= i2; ++i)
		for(int j = j1; j <= j2; ++j)
			M(i-i1,j-j1) = m_Matrix[i][j];

	return M;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::GetMatrixBlocks(vbMatrix<vbType> &A,vbMatrix<vbType> &B,
											  vbMatrix<vbType> &C,vbMatrix<vbType> &D)
{
	// Divide the matrix into blocks as follows: M = [A,B;C,D]
	// A -- (m-1)x(m-1)
	// B -- (m-1)x1
	// C -- 1x(m-1)
	// D -- 1x1
	A = GetMatrixBlock(0,0,m_NumOfRows-2,m_NumOfRows-2);
	B = GetMatrixBlock(0,m_NumOfRows-1,m_NumOfRows-2,m_NumOfRows-1);
	C = GetMatrixBlock(m_NumOfRows-1,0,m_NumOfRows-1,m_NumOfRows-2);
	D = GetMatrixBlock(m_NumOfRows-1,m_NumOfRows-1,m_NumOfRows-1,m_NumOfRows-1);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::GetMatrixBlocks2(vbMatrix<vbType> &A,vbMatrix<vbType> &B,
											   vbMatrix<vbType> &C,vbMatrix<vbType> &D)
{
	// Divide the matrix into blocks as follows: M = [A,B;C,D]
	// A -- 1x1
	// B -- 1x(m-1)
	// C -- m(-1)x1
	// D -- (m-1)x(m-1)
	A = GetMatrixBlock(0,0,0,0);
	B = GetMatrixBlock(0,1,0,m_NumOfRows-1);
	C = GetMatrixBlock(1,0,m_NumOfRows-1,0);
	D = GetMatrixBlock(1,1,m_NumOfRows-1,m_NumOfRows-1);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::SetMatrixBlock(const int& i1,
											 const int& j1,
											 const vbMath::vbMatrix<vbType> &M)
{
	// Check for index validity
	if((i1 < 0) || (j1 < 0) || (i1 >= m_NumOfRows) || (j1 >= m_NumOfCols))
	{
		GlobalErrorLog += "\nUsed wrong indeces when trying to set a matrix sub-block";
		return;
	}

	int m,n;

	// Check to see if the matrix M is bigger than this matrix
	if((i1 + M.GetNumOfRows()) > m_NumOfRows)
		m = m_NumOfRows - i1;
	else
		m = M.GetNumOfRows();

	if((j1 + M.GetNumOfCols()) > m_NumOfCols)
		n = m_NumOfCols - j1;
	else
		n = M.GetNumOfCols();

	// Assign the elements of M to this matrix
	for(int i = i1; i < i1+m; ++i)
		for(int j = j1; j < j1+n; ++j)
			(*this)(i,j) = M(i-i1,j-j1);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::SaveToXml(CkXml *XmlFile,const string& Name)
{
	// Create the matrix tag
	XmlFile = XmlFile->NewChild("Matrix","");

	// Add name attribute
	XmlFile->AddAttribute("Name",Name.c_str());

	// Add size attribute
	XmlFile->AddAttribute("NumOfRows",ConvertNumber(m_NumOfRows).c_str());
	XmlFile->AddAttribute("NumOfCols",ConvertNumber(m_NumOfCols).c_str());

	// Write the actual values
	for(int i = 0; i < m_NumOfRows; ++i)
	{
		// Create the row tag
		XmlFile = XmlFile->NewChild("Row","");

		// Add the row number attribute
		XmlFile->AddAttribute("RowNumber",ConvertNumber(i).c_str());

		// Add the columns tabs for each row tab
		for(int j = 0; j < m_NumOfCols; ++j)
		{
			// Create the column tab
			XmlFile = XmlFile->NewChild("Col","");

			// Add the column number attribute
			XmlFile->AddAttribute("ColNumber",ConvertNumber(j).c_str());

			// Add the value attribute
			XmlFile->AddAttribute("Value",ConvertNumber(at(i,j)).c_str());

			// Get back to the row level
			XmlFile = XmlFile->GetParent();
		}

		// Get back to the matrix level
		XmlFile = XmlFile->GetParent();
	}

	// Get back to the parent level
	XmlFile = XmlFile->GetParent();
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool vbMatrix<vbType>::LoadFromXml(CkXml* XmlFile)
{
	// Enter the matrix tag
	if(!(XmlFile = XmlFile->FindChild("Matrix")))
		return false;

	CkString Value;

	// Get the number of rows
	if(!(XmlFile->GetAttrValue("NumOfRows",Value)))
		return false;

	int NumOfRows = Value.intValue();

	// Get the number of cols
	if(!(XmlFile->GetAttrValue("NumOfCols",Value)))
		return false;

	int NumOfCols = Value.intValue();

	Create(NumOfRows,NumOfCols,0);

	// Enter the row tag
	if(!(XmlFile = XmlFile->FirstChild()))
		return false;

	// Read the individual values from the xml file
	for(int i = 0; i < NumOfRows; ++i)
	{
		// Enter the first col tag
		if(!(XmlFile = XmlFile->FirstChild()))
			return false;

		// Go through the columns
		for(int j = 0; j < NumOfCols; ++j)
		{
			// Get the value
			if(!(XmlFile->GetAttrValue("Value",Value)))
				return false;

			// Write the value to the matrix
			at(i,j) = Value.doubleValue();

			// Go to the next col tag
			if(j < (NumOfCols-1))
				if(!(XmlFile = XmlFile->NextSibling()))
					return false;
		}

		// Get back to the row tag
		if(!(XmlFile = XmlFile->GetParent()))
			return false;

		// Go to the next row tag
		if(i < (NumOfRows-1))
			if(!(XmlFile = XmlFile->NextSibling()))
				return false;
	}

	// Get back to the matrix tag
	if(!(XmlFile = XmlFile->GetParent()))
		return false;

	// Get back to the parent level
	if(!(XmlFile = XmlFile->GetParent()))
		return false;

	return true;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline ostream& operator<<(ostream& os,const vbMatrix<vbType>& A)
{
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	// Get the maximum length of all the entries so as to set the format
	// of the matrix output text
	vbMatrix<int> Widths(1,n,0);
	string TempString;
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			TempString = ConvertNumber(A(i,j));
			if(TempString.length() > std::real(Widths(0,j)))
				Widths(0,j) = TempString.length();
		}
	}

	// Write the matrix to the output stream formatting it
	// using the calculated maximum string length
	for(int i = 0; i < m; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			// Write the ith,jth value to the string
			os << setw(std::real(Widths(0,j))) << std::left << ConvertNumber(A(i,j));

			if(j == (n-1) && i != (m-1))
				os << "\n";
			else if(j != (n-1))
				os << "   ";
		}
	}

	return os;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbType& vbMatrix<vbType>::operator()(const int& i,const int& j)const
{
	return m_Matrix[i*m_NumOfCols + j];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType& vbMatrix<vbType>::operator()(const int& i,const int& j)
{
	return m_Matrix[i*m_NumOfCols + j];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbType& vbMatrix<vbType>::operator()(const int& i)const
{
	return m_Matrix[i];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType& vbMatrix<vbType>::operator()(const int& i)
{
	return m_Matrix[i];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbType& vbMatrix<vbType>::operator[](const int& i)const
{
	return m_Matrix[i];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType& vbMatrix<vbType>::operator[](const int& i)
{
	return m_Matrix[i];
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator*=(const vbType& x)
{
	(*this) = (*this)*x;
	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator*=(const vbMatrix<vbType>& M)
{
	(*this) = (*this)*M;
	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator/=(const vbType& x)
{
	(*this) = (*this)*(vbType(1)/x);
	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator/=(const vbMatrix<vbType>& M)
{
	(*this) = (*this)*inv(M);
	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator*(const vbType& x,const vbMatrix<vbType>& M)
{
	vbMatrix<vbType> Result(M);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M.GetNumOfRows(); ++i)
			for(int j = 0; j < M.GetNumOfCols(); ++j)
				Result(i,j) *= x;
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator*(const vbMatrix<vbType>& M,const vbType& x)
{
	return (x*M);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator /(const vbMatrix<vbType>& M,const vbType& x)
{
	return (M*(vbType(1)/x));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator /(const vbType& x,const vbMatrix<vbType>& M)
{
	return (x*inv(M));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator*(const vbMatrix<vbType>& M1,const vbMatrix<vbType>& M2)
{
	// Check to see if one of the matrices is a scalar
	if(M1.GetNumOfRows() == 1 && M1.GetNumOfCols() == 1)
		return M1(0,0)*M2;
	else if(M2.GetNumOfRows() == 1 && M2.GetNumOfCols() == 1)
		return M2(0,0)*M1;
				
	// Check the size of the matrices to see if multiplication is possible
	if(M1.GetNumOfCols() != M2.GetNumOfRows())
	{
		GlobalErrorLog += "\nTried to multiply two matrices of non-matching sizes";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Each component of the new matrix is:  Cij = Aik*Bkj;
	vbMatrix<vbType> Result(M1.GetNumOfRows(),M2.GetNumOfCols(),0);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M1.GetNumOfRows(); ++i)
			for(int j = 0; j < M2.GetNumOfCols(); ++j)
				for(int k = 0; k < M1.GetNumOfCols(); ++k)
					Result(i,j) += M1(i,k)*M2(k,j);
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator/(const vbMatrix<vbType>& M1,const vbMatrix<vbType>& M2)
{
	return (M1*inv(M2));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::operator++(int)
{
	// Check to see if the matrix is a square matrix
	if(m_NumOfRows != m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to add an identity matrix to a non square matrix";
		return;
	}

	// Add this matrix to an identity matrix
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			(*this)(i,j) += vbType(1);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator++()
{
	// Check to see if the matrix is a square matrix
	if(m_NumOfRows != m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to add an identity matrix to a non square matrix";
		return (*this);
	}

	// Add this matrix to an identity matrix
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			(*this)(i,j) += vbType(1);
	}

	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::operator--(int)
{
	// Check to see if the matrix is a square matrix
	if(m_NumOfRows != m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to subtract an identity matrix from a non square matrix";
		return;
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			(*this)(i,j) -= vbType(1);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator--()
{
	// Check to see if the matrix is a square matrix
	if(m_NumOfRows != m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to subtract an identity matrix from a non square matrix";
		return (*this);
	}

	// Subtract an identity matrix from this matrix
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			(*this)(i,j) -= vbType(1);
	}

	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator-(const vbMatrix<vbType>& M)
{
	vbMatrix<vbType> Result(M);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M.GetNumOfRows(); ++i)
			#pragma omp for
			for(int j = 0; j < M.GetNumOfCols(); ++j)
				Result(i,j) = -Result(i,j);
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator+(const vbMatrix<vbType>& M1,const vbMatrix<vbType>& M2)
{				
	// Check the size of the matrices to see if addition is possible
	if((M1.GetNumOfRows() != M2.GetNumOfRows()) && (M1.GetNumOfCols() != M2.GetNumOfCols()))
	{
		GlobalErrorLog += "\nTried to add two matrices of unequal dimensions";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Each component of the new matrix is:  Cij = Aij+Bij;
	vbMatrix<vbType> Result(M1);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M1.GetNumOfRows(); ++i)
			for(int j = 0; j < M1.GetNumOfCols(); ++j)
				Result(i,j) += M2(i,j);
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> operator-(const vbMatrix<vbType>& M1,const vbMatrix<vbType>& M2)
{				
	// Check the size of the matrices to see if addition is possible
	if((M1.GetNumOfRows() != M2.GetNumOfRows()) && (M1.GetNumOfCols() != M2.GetNumOfCols()))
		{
		GlobalErrorLog += "\nTried to subtract two matrices of unequal dimensions";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Each component of the new matrix is:  Cij = Aik-Bik;
	vbMatrix<vbType> Result(M1);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M1.GetNumOfRows(); ++i)
			for(int j = 0; j < M1.GetNumOfCols(); ++j)
				Result(i,j) -= M2(i,j);
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator+=(const vbMatrix<vbType> &M)
{
	// Check the size of the matrices to see if addition is possible
	if((m_NumOfRows != M.GetNumOfRows()) && (m_NumOfCols != M.GetNumOfCols()))
	{
		GlobalErrorLog += "\nTried to add two matrices of unequal dimensions";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			#pragma omp for
			for(int j = 0; j < m_NumOfCols; ++j)
				m_Matrix[i][j] += M(i,j);
	}

	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType>& vbMatrix<vbType>::operator-=(const vbMatrix<vbType> &M)
{
	// Check the size of the matrices to see if addition is possible
	if((m_NumOfRows != M.GetNumOfRows()) && (m_NumOfCols != M.GetNumOfCols()))
	{
		GlobalErrorLog += "\nTried to subtract two matrices of unequal dimensions";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < m_NumOfRows; ++i)
			for(int j = 0; j < m_NumOfCols; ++j)
				m_Matrix[i][j] -= M(i,j);
	}

	return (*this);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> OrthogonalProjection(const vbMatrix<vbType>& M,const vbMatrix<vbType>& Mtranspose)
{
	// Orthogonal projection of M = (II - (M*inv(Mt*M)*Mt))
	return vbMatrix<vbType>(eye<vbType>(M.GetNumOfRows()) - (M * inv(Mtranspose * M) * Mtranspose));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> Transpose(const vbMatrix<vbType>& M)
{
	int m = M.GetNumOfRows();
	int n = M.GetNumOfCols();

	vbMatrix<vbType> TransposedMatrix(n,m,vbType(0));

	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < M.GetNumOfRows(); ++i)
			#pragma omp for
			for(int j = 0; j < M.GetNumOfCols(); ++j)
				TransposedMatrix(j,i) = M(i,j);
	}

	return TransposedMatrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::OrthoNormalizeMatrix()
{
	vbMatrix<vbType> vi,vii,vj;

	for(int i = 0; i < m_NumOfCols; ++i)
	{
		vi = GetColVector(i);
		vii = GetColVector(i);
		
		for(int j = i-1; j >= 0; --j)
		{
			vj = GetColVector(j);
			vj.Normalize();
			vi = vi - ((Transpose(vj)*vii)/(Transpose(vj)*vj))*vj;
		}
		vi.Normalize();

		SetColVector(i,vi);
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbMatrix<vbType> vbMatrix<vbType>::GetOrthonormalizedMatrix()const
{
	vbMatrix<vbType> OrthogonalMatrix(m_NumOfRows,m_NumOfCols,0);
	vbMatrix<vbType> vi,vii,vj;

	for(int i = 0; i < m_NumOfCols; ++i)
	{
		vi = GetColVector(i);
		vii = GetColVector(i);
		
		for(int j = i-1; j >= 0; --j)
		{
			vj = OrthogonalMatrix.GetColVector(j);
			vj.Normalize();
			vi = vi - ((Transpose(vj)*vii)/(Transpose(vj)*vj))*vj;
		}
		vi.Normalize();

		OrthogonalMatrix.SetColVector(i,vi);
	}

	return OrthogonalMatrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void QRdecomposition(const vbMatrix<vbType>& M,
							vbMatrix<vbType>& Q,
							vbMatrix<vbType>& R,
							const vbType& Zero = 0.00000001)
{
	int m = M.GetNumOfRows();
	int n = M.GetNumOfCols();

	R = M;
	vbMatrix<vbType> x,u,v,Qk;
	vbType xMag;
	vbType uMag;
	complex<vbType> a;
	complex<vbType> j(0,1);
	vbMatrix<vbType> II;
	Q = eye<vbType>(m);

	int NumOfIterations = min(m-1,n-1);

	for(int i = 0; i < NumOfIterations; ++i)
	{
		R = R.GetMatrixBlock(i,i,m-1,n-1);

		x = R.GetColVector(0);
		xMag = GetColVectorMagnitude(x,0);
		a = -std::exp(j*x(0,0))*xMag;

		u = x - xMag*CreateUnitColVector<vbType>(R.GetNumOfRows(),0);

		// Check if u is a zero vector
		uMag = GetColVectorMagnitude(u,0);
		if(EqualsZero(uMag,Zero))
		{
			R = Transpose(Q)*M;
			return;
		}

		v = u/uMag;

		Qk = eye<vbType>(R.GetNumOfRows()) - vbType(2)*v*Transpose(v);

		II = eye<vbType>(m);
		II.SetMatrixBlock(i,i,Qk);

		Q = Q*II;

		R = Transpose(Q)*M;
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline int rank(const vbMatrix<vbType>& A)
{
	// Define a zero
	vbType Zero = DefineZero(A);

	// Carry out a QR decomposition
	vbMatrix<vbType> Q,R;
	QRdecomposition(A,Q,R,Zero);

	int NumOfIterations = min(R.GetNumOfRows(),R.GetNumOfCols());

	int Rank = 0;
	for(int i = 0; i < NumOfIterations; ++i)
		if(!EqualsZero(R(i,i),Zero))
			++Rank;

	return Rank;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline int rank(const vbMatrix<vbType>& A,const vbType& Zero)
{
	// Carry out a QR decomposition
	vbMatrix<vbType> Q,R;
	QRdecomposition(A,Q,R,Zero);

	int NumOfIterations = min(R.GetNumOfRows(),R.GetNumOfCols());

	int Rank = 0;
	for(int i = 0; i < NumOfIterations; ++i)
		if(!EqualsZero(R(i,i),Zero))
			++Rank;

	return Rank;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline int rank_triangular(const vbMatrix<vbType>& A)
{
	// Define a zero
	vbType Zero = DefineZero(A);

	// Calculate the rank of a triangular matrix blindly (does not check whether
	// the matrix is really triangular
	int NumOfIterations = min(A.GetNumOfRows(),A.GetNumOfCols());
	int Rank = 0;
	for(int i = 0; i < NumOfIterations; ++i)
		if(!EqualsZero(A(i,i),Zero))
			++Rank;

	return Rank;	
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline int rank_triangular(const vbMatrix<vbType>& A,const vbType& Zero)
{
	// Calculate the rank of a triangular matrix blindly (does not check whether
	// the matrix is really triangular
	int NumOfIterations = min(A.GetNumOfRows(),A.GetNumOfCols());
	int Rank = 0;
	for(int i = 0; i < NumOfIterations; ++i)
		if(!EqualsZero(A(i,i),Zero))
			++Rank;

	return Rank;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline complex<vbType> det(const vbMatrix<vbType>& A,const vbType& Zero)
{
	// Check to make sure matrix A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
		return 0;

	if(m == 1)
		return A(0,0);

	if(m == 2)
		return (A(0,0)*A(1,1) - A(1,0)*A(0,1));

	if(m == 3)
	{
		return (A(0,0)*(A(1,1)*A(2,2) - A(2,1)*A(1,2)) -
				A(0,1)*(A(1,0)*A(2,2) - A(2,0)*A(1,2)) +
				A(0,2)*(A(1,0)*A(2,1) - A(2,0)*A(1,1)));
	}

	vbMatrix<vbType> Q,R;
	QRdecomposition(A,Q,R,Zero);

	complex<vbType> Det = 1;
	
	for(int i = 0; i < R.GetNumOfRows(); ++i)
		Det *= R(i,i);
	
	return Det;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType det_triangular(const vbMatrix<vbType>& A)
{
	// Calculate the determinant of a triangular matrix blindly (does
	// not check whether the matrix is really triangular
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
		return 0;

	complex<vbType> Det = 1;
	for(int i = 0; i < m; ++i)
		Det *=A(i,i);

	return Det;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void LUdecomposition(const vbMatrix<vbType>& M,vbMatrix<vbType>& L,vbMatrix<vbType>& U)
{
	// Check to see if matrix A is square
	if(M.GetNumOfRows() != M.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to do a LU decomposition on non-square matrix";
		return;
	}

	// Check to see if A is scalar
	if(M.GetNumOfRows() == 1 && M.GetNumOfCols() == 1)
	{
		L = vbMatrix<vbType>(1);
		U = M;
	}

	// Check to see if A is a 2x2 matrix
	if(M.GetNumOfRows() == 2 && M.GetNumOfCols())
	{
		L = eye<vbType>(2);
		U = eye<vbType>(2);

		if(M(0,0) != 0) // The first element of A is not zero
		{
			L(1,0) = -M(1,0)/M(0,0);
			U(0,1) = -M(0,1)/M(0,0);
		}
		else if(M(1,1) != 0) // The last element of A is not zero
		{
			L(1,0) = M(1,0)/M(1,1);
			U(0,1) = M(0,1)/M(1,1);
		}
		else if(M(1,0) != 0)
		{
			L(1,0) = M(0,0)/M(0,1);
			U(0,1) = M(1,1)/M(0,1);
		}
		else
			GlobalErrorLog += "\nNo LU decomposition is possible on this matrix";
	}

	// Get and store the number of rows of matrix M
	int m = M.GetNumOfRows();

	// Initialize the L and U matrices as eye matrices
	L = eye<vbType>(m);
	U = eye<vbType>(m);

	// Divide the matrix into blocks
	vbMatrix<vbType> A,B,C,D;
	M.GetMatrixBlocks(A,B,C,D);

	// Check if D is singular:
	// D is not singular then use Sd to find LU decomposition
	// D is singular then use Sa to find LU decomposition
	if(D(0,0) != vbType(0))
	{
		vbMatrix<vbType> Dinv = inv(D);
		vbMatrix<vbType> Sd = A - B*Dinv*C;
		vbMatrix<vbType> Sdinv = inv(Sd);


	}
	else
	{
		vbMatrix<vbType> Ainv = inv(A);
		vbMatrix<vbType> Sa = D - C*Ainv*B;
		vbMatrix<vbType> Sainv = inv(Sa);

	}	
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> inv(const vbMatrix<vbType>& A)
{
	// Make sure that A is a square matrix
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to take the inverse of a non-square matrix";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// First do a QR decomposition on A:  A = QR
	vbMatrix<vbType> Q,R;
	QRdecomposition(A,Q,R);

	// Check if A is singular
	if(rank_triangular(R) != m)
	{
		GlobalErrorLog += "\nTried to take the inverse of a singular matrix";
		return A;
	}

	// The inverse of A = inv(R)*Transpose(Q) where R is upper triangular
	// Calculate the inverse of R using backsubstitution with unit vectors
	vbMatrix<vbType> Rinv(m,m,0);

	for(int i = m-1; i >= 0; --i) // Loop over cols
	{
		for(int j = m-1; j >= 0; --j) // Loop over rows
		{
			if(j == i)
				Rinv(j,i) = vbType(1)/R(j,j);
			else if(j < i)
			{
				Rinv(j,i) = 0;
				for(int k = j+1; k < m; ++k)
					Rinv(j,i) -= R(j,k)*Rinv(k,i);
				Rinv(j,i) /= R(j,j);
			}
		}
	}

	// The inverse of the original matrix A = inv(R)*Transpose(Q)
	return (Rinv*Transpose(Q));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbSet<vbType>> inv(const vbMatrix<vbSet<vbType>>& Ai,const int& sums = 1)
{
	// Use Hansen's Inverse Method to calculate the inverse of
	// an interval matrix Ai

	// Get the size of the interval matrix Ai and make sure it is square
	int m = Ai.GetNumOfRows();
	if(m != Ai.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to take the inverse of a non-square matrix";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Define an eye matrix
	vbMatrix<vbType> II = eye<vbType>(m);

	// Form a nominal matrix Ao = (Amax + Amin)/2
	vbMatrix<vbType> Ao = Ai;

	// Get the inverse of the nominal matrix Ao
	vbMatrix<vbType> Aoinv = inv(Ao);

	// Calculate an interval error matrix
	vbMatrix<vbSet<vbType>> Ei = II - Ai*Aoinv;

	// Calculate the infinity norm
	vbType EiNormInf = NormInf(Ei);

	// Check to see if the inverse of the interval matrix can be taken
	// It is calculated using a geometric series with Ei, if EiNormInf is
	// greater then or equal to 1, then it cannot be taken
	if(EiNormInf >= 1)
	{
		GlobalErrorLog += "\nInverse of the interval matrix does not exist";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	// Calculate the remainder of the error matrix
	vbType r = (std::pow(EiNormInf,sums+1))/(vbType(1) - EiNormInf);

	// Construct the Sm and Pm to m sums, where Sm is
	// constructed using a geometric series
	vbMatrix<vbSet<vbType>> Pm(m,m,vbSet<vbType>(-r,r));
	vbMatrix<vbSet<vbType>> Sm = II;
	for(int i = 0; i < sums; ++i)
	{
		Sm *= Ei;
		Sm += II;
	}

	return (Aoinv*(Sm + Pm));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> invBLOCK(const vbMatrix<vbType>& M)
{
	// Define a Zero
	vbType Zero = DefineZero(M);

	if(M.GetNumOfRows() != M.GetNumOfCols())
	{
		GlobalErrorLog += "\nCannot take inverse of non-square matrix";
		return vbMatrix<vbType>(0,0,vbType(0));
	}

	if(M.GetNumOfRows() == 1 && M.GetNumOfCols() == 1)
		if(EqualsZero(M(0,0),Zero))
			return vbType(0);
		else
			return vbType(1)/M(0,0);

	if(M.GetNumOfRows() == 2 && M.GetNumOfCols() == 2)
	{
		// Calculate the determinant
		vbType Det = M(0,0)*M(1,1) - M(1,0)*M(0,1);
		vbType Inverse[2][2] = {{M(1,1)/Det,-M(0,1)/Det},
								{-M(1,0)/Det,M(0,0)/Det}};
		return CreateMatrix(Inverse);
	}
	
	// Get and store the number of rows of matrix M
	int m = M.GetNumOfRows();

	// Divide the matrix into blocks as follows: M = [A,B;C,D]
	// A -- (m-1)x(m-1)
	// B -- (m-1)x1
	// C -- 1x(m-1)
	// D -- 1x1
	vbMatrix<vbType> A,B,C,D;
	M.GetMatrixBlocks(A,B,C,D);

	// Resulting inverse matrix
	vbMatrix<vbType> Result = vbMatrix<vbType>(m,m,0);

	// Check if D is singular:
	// D is not singular then use Sd to find inverse
	// D is singular then use Sa to find inverse
	if(!(EqualsZero(D(0,0),Zero)))
	{
		vbMatrix<vbType> Dinv = inv(D);
		vbMatrix<vbType> Sd = A - B*Dinv*C;
		vbMatrix<vbType> Sdinv = inv(Sd);

			// Set the blocks of the resulting inverse matrix
			Result.SetMatrixBlock(0,0,Sdinv);
			Result.SetMatrixBlock(0,m-1,-Sdinv*B*Dinv);
			Result.SetMatrixBlock(m-1,0,-Dinv*C*Sdinv);
			Result.SetMatrixBlock(m-1,m-1,Dinv + Dinv*C*Sdinv*B*Dinv);
	}
	else
	{
		vbMatrix<vbType> Ainv = inv(A);
		vbMatrix<vbType> Sa = D - C*Ainv*B;
		vbMatrix<vbType> Sainv = inv(Sa);

			// Set the blocks of the resulting inverse matrix
			Result.SetMatrixBlock(0,0,Ainv + Ainv*B*Sainv*C*Ainv);
			Result.SetMatrixBlock(0,m-1,-Ainv*B*Sainv);
			Result.SetMatrixBlock(m-1,0,-Sainv*C*Ainv);
			Result.SetMatrixBlock(m-1,m-1,Sainv);
	}
	
	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> pinv(const vbMatrix<vbType>& M)
{
	// Define a zero
	vbType Zero = DefineZero(M);

	// Get the number of rows and cols and store them
	int m = M.GetNumOfRows();
	int n = M.GetNumOfCols();
	
	// Check to see if the matrix M is a scalar
	if(m == 1 && n == 1)
		if(EqualsZero(M(0,0),Zero))
			return vbType(0);
		else
			return vbType(1)/M(0,0);

	// Check if the matrix M is a row or column vector
	if(m == 1)
	{
		// Get the magnitude of the vector
		vbType Mag = GetRowVectorMagnitude(M,0);
		if(EqualsZero(Mag,Zero))
			return (vbMatrix<vbType>(n,m,0));
		else
			return (Transpose(M)/Mag);
	}
	else if(n == 1)
	{
		// Get the magnitude of the vector
		vbType Mag = GetColVectorMagnitude(M,0);
		if(EqualsZero(Mag,Zero))
			return(vbMatrix<vbType>(n,m,0));
		else
			return(Transpose(M)/Mag);
	}

	vbMatrix<vbType> A;
	vbMatrix<vbType> B;
	vbMatrix<vbType> ProjA;
	vbMatrix<vbType> ProjB;

	// m > n:
	// M -- mxn
	// A -- mx1
	// B -- mx(n-1)
	// ProjA -- mxm
	// ProjB -- mxm
	// Result -- nxm
	if(m >= n)
	{
		A = M.GetMatrixBlock(0,0,m-1,0);
		B = M.GetMatrixBlock(0,1,m-1,n-1);

		ProjA = OrthogonalProjection(A,Transpose(A));
		ProjB = OrthogonalProjection(B,Transpose(B));

		return vbMatrix<vbType>(Transpose(vbMatrix<vbType>(ProjB * A * inv(Transpose(A) * ProjB * A))),
								Transpose(vbMatrix<vbType>(ProjA * B * inv(Transpose(B) * ProjA * B))),false);
	}
	else
		return Transpose(pinv(Transpose(M)));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::Normalize()
{
	for(int i = 0; i < m_NumOfCols; ++i)
	{
		complex<vbType> Mag = 0;

		for(int j = 0; j < m_NumOfRows; ++j)
			Mag += at(j,i)*std::conj(at(j,i));

		Mag = std::sqrt(Mag);

		if(Mag != complex<vbType>(0))
			for(int j = 0; j < m_NumOfRows; ++j)
				at(j,i) /= Mag;
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType Norm1(const vbMatrix<vbType>& A)
{
	// Get the size of A
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	vbType Norm = 0;
	vbType ColSum = 0;

	// The norm1 of a matrix A is the maximum absolute column sum
	for(int j = 0; j < n; ++j)
	{
		ColSum = 0;
		for(int i = 0; i < m; ++i)
			ColSum += std::abs(A(i,j));

		if (ColSum > Norm)
			Norm = ColSum;
	}

	return Norm;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType NormInf(const vbMatrix<vbType>& A)
{
	// Get the size of A
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	vbType Norm = 0;
	vbType RowSum = 0;

	// The NormInf of a matrix A is the maximum absolute row sum
	for(int i = 0; i < m; ++i)
	{
		RowSum = 0;
		for(int j = 0; j < n; ++j)
			RowSum += std::abs(A(i,j));

		if (RowSum > Norm)
			Norm = RowSum;
	}

	return Norm;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType NormFrobenius(const vbMatrix<vbType>& A)
{
	// Get the size of A
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	vbType Result = 0;

	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			Result += A(i,j)*std::conj(A(i,j));

	return std::sqrt(Result);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType Norm1(const vbMatrix<vbSet<vbType>>& A)
{
	// Get the size of A
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	vbType Norm = 0;
	vbType ColSum = 0;

	// The norm1 of a matrix A is the maximum absolute column sum
	for(int j = 0; j < n; ++j)
	{
		ColSum = 0;
		for(int i = 0; i < m; ++i)
			ColSum += (A(i,j)).GetAbsMax();

		if (ColSum > Norm)
			Norm = ColSum;
	}

	return Norm;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType NormInf(const vbMatrix<vbSet<vbType>>& A)
{
	// Get the size of A
	int m = A.GetNumOfRows();
	int n = A.GetNumOfCols();

	vbType Norm = 0;
	vbType RowSum = 0;

	// The NormInf of a matrix A is the maximum absolute row sum
	for(int i = 0; i < m; ++i)
	{
		RowSum = 0;
		for(int j = 0; j < n; ++j)
			RowSum += (A(i,j)).GetAbsMax();

		if (RowSum > Norm)
			Norm = RowSum;
	}

	return Norm;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline complex<vbType> trace(const vbMatrix<vbType>& M)
{
	// The trace -- addition of all the diagonal elements
	// equals to the sum of the eigenvalues of the matrix M
	complex<vbType> Result = 0;
	int m = M.GetNumOfRows();

	// Check to make sure the matrix M is square
	if(m != M.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to take the trace of a non square matrix";
		return Result;
	}

	for(int i = 0; i < m; ++i)
		Result += M(i,i);

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> MatrixSign(const vbMatrix<vbType>& M,const int& ConvergentRate = 3,const vbType& Zero = 0.00000001)
{
	vbType NewErr = 1;
	int m = M.GetNumOfRows();

	// Check to make sure that the matrix M is square
	if(m != M.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to apply the matrix sign function to a non square matrix";
		return M;
	}

	// r -- Convergent rate
	// Make sure convergent rate is equal/greater than 2
	int r = ConvergentRate;
	if(r < 2)
		r = 2;

	vbMatrix<vbType> Pr = eye<vbType>(m);
	vbMatrix<vbType> Qr = eye<vbType>(m);
	vbMatrix<vbType> Pold,Qold;
	vbMatrix<vbType> S = M;
	vbMatrix<vbType> Sinvsquared = power(inv(S),2);

	while(!(EqualsZero(NewErr,Zero)))
	{
		Pr = eye<vbType>(m);
		Qr = eye<vbType>(m);
		Sinvsquared = power(inv(S),2);
		for(int i = 0; i < r; ++i)
		{
			Pold = Pr;
			Qold = Qr;
			Pr = Pold + Sinvsquared*Qold;
			Qr = Pold + Qold;
		}

		S = S*inv(Qr)*Pr;

		NewErr = std::abs(std::real(trace(S*S)) - vbType(m))/vbType(m);
	}

	return S;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void eigs(const vbMatrix<vbType>& A,vbMatrix<vbType>& EigenValues,vbMatrix<vbType>& EigenVectors)
{
	// Define a zero
	vbType Zero = DefineZero(A);

	// Check if matrix A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nCannot calculate eigenvalues/eigenvectors of non-square matrix";
		return;
	}
	
	// Check for 1x1 case (scalar case)
	if(m == 1)
	{
		EigenValues(0,0) = A(0,0);
		EigenVectors(0,0) = 1;
		return;
	}

	// Check for 2x2 case
	if(m == 2)
	{
		// Prepare the eigen value and eigen vector matrices
		EigenVectors = vbMatrix<vbType>(m,m,0);
		EigenValues = EigenVectors;

		// Calculate the eigen values using the determinant of the 2x2 matrix
		EigenValues(0,0) = ((A(0,0) + A(1,1))/vbType(2)) + std::sqrt(std::pow(A(0,0) + A(1,1),2)/vbType(4) + A(0,1)*A(1,0) - A(0,0)*A(1,1));
		EigenValues(1,1) = ((A(0,0) + A(1,1))/vbType(2)) - std::sqrt(std::pow(A(0,0) + A(1,1),2)/vbType(4) + A(0,1)*A(1,0) - A(0,0)*A(1,1));

		// Calculate the eigen vectors
		if(!(EqualsZero(A(1,0),Zero)))
		{
			EigenVectors(0,0) = EigenValues(0,0) - A(1,1);
			EigenVectors(1,0) = A(1,0);
			EigenVectors(0,1) = EigenValues(1,1) - A(1,1);
			EigenVectors(1,1) = A(1,0);
		}
		else if(!(EqualsZero(A(0,1),Zero)))
		{
			EigenVectors(0,0) = A(0,1);
			EigenVectors(1,0) = EigenValues(0,0) - A(0,0);
			EigenVectors(0,1) = A(0,1);
			EigenVectors(1,1) = EigenValues(1,1) - A(0,0);
		}
		else
		{
			EigenVectors(0,0) = 1;
			EigenVectors(1,1) = 1;
		}
		EigenVectors.Normalize();

		return;
	}

	// Case for when A > 2x2
	// Prepare the eigen vector and eigen value matrices
	EigenVectors = vbMatrix<vbType>(m,m,0);
	EigenValues = EigenVectors;
	vbMatrix<vbType> SPlusEigenVectors;
	vbMatrix<vbType> SMinusEigenVectors;

	// Matrices used for the algorithm
	vbMatrix<vbType> II = eye<vbType>(m);
	vbMatrix<vbType> SPlus,SMinus;
	int SPlusTrace = 0;
	int SMinusTrace = 0;

	// Average eigenvalue
	vbType EigAvg = std::real(trace(A))/vbType(m);

	// Calculate the Sign+ and the Sign- of the shifted A (A is shifted by the EigAvg amount)
	SPlus = vbType(0.5)*(II + MatrixSign(A - EigAvg*II));
	SMinus = II - SPlus;

	// Calculate the traces of the Sign+ and Sign- matrices
	SPlusTrace = int(RoundOff(std::real(trace(SPlus)),0));
	SMinusTrace = int(RoundOff(std::real(trace(SMinus)),0));

	// Get "SPlusTrace" independent vectors from Sign+ and
	// "SMinusTrace" independent vectors from Sign- and
	// store them in the eigen vector matrix
	SPlusEigenVectors = SPlus.GetNonZeroColVectors(Zero,SPlusTrace);
	SMinusEigenVectors = SMinus.GetNonZeroColVectors(Zero,SMinusTrace);
	SPlusEigenVectors.Normalize();
	SMinusEigenVectors.Normalize();
	EigenVectors.SetMatrixBlock(0,0,SMinusEigenVectors);
	EigenVectors.SetMatrixBlock(0,SMinusTrace,SPlusEigenVectors);

	// Recursively call the eigs function until the individual eigenvalues are calculated
	vbMatrix<vbType> RecursiveEigenValues1 = pinv(SMinusEigenVectors)*A*SMinusEigenVectors;
	vbMatrix<vbType> RecursiveEigenValues2 = pinv(SPlusEigenVectors)*A*SPlusEigenVectors;

	// Calculate the eigen value block matrix
	EigenValues.SetMatrixBlock(0,0,RecursiveEigenValues1);
	EigenValues.SetMatrixBlock(SMinusTrace,SMinusTrace,RecursiveEigenValues2);

	eigs(EigenValues.GetMatrixBlock(0,0,SMinusTrace-1,SMinusTrace-1),RecursiveEigenValues1,SMinusEigenVectors);
	eigs(EigenValues.GetMatrixBlock(SMinusTrace,SMinusTrace,m-1,m-1),RecursiveEigenValues2,SPlusEigenVectors);
	EigenValues.SetMatrixBlock(0,0,RecursiveEigenValues1);
	EigenValues.SetMatrixBlock(SMinusTrace,SMinusTrace,RecursiveEigenValues2);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool DoesMatrixHavePurelyImaginaryEigenValues(const vbMatrix<vbType>& A,const vbType& Zero)
{
	// Make sure A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to calculate eigen values of non-square matrix";
		return false;
	}

	// Calculate the eigen values of A
	vbMatrix<vbType> EIGS,EIGENVECTORS;
	eigs(A,EIGS,EIGENVECTORS);

	// Go through the eigen values and check for pure imaginary ones
	for(int i = 0; i < A.GetNumOfRows();  ++i)
	{
		if(EqualsZero(EIGS(i,i),Zero))
			return true;
	}

	// If we made it this far, then there are no purely imaginary eigen values
	return false;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> BlockDiagonalize(const vbMatrix<vbType>& M)
{
	// Get and store the number of rows of matrix M
	int m = M.GetNumOfRows();

	// Check to see if matrix is square
	if(m != M.GetNumOfCols())
	{
		GlobalErrorLog += "\nTried to block diagonalize a non-square matrix";
		return M;
	}

	// Check if matrix is a scalar
	if(m == 1)
		return M;

	// Create the resulting block diagonalized matrix
	vbMatrix<vbType> Result(m,m,0);

	// Divide the matrix into blocks as follows: M = [A,B;C,D]
	// A -- (m-1)x(m-1)
	// B -- (m-1)x1
	// C -- 1x(m-1)
	// D -- 1x1
	vbMatrix<vbType> A,B,C,D;
	M.GetMatrixBlocks(A,B,C,D);

	vbMatrix<vbType> Sa = D - C*inv(A)*B;

	// Set the blocks of the resulting block diagonalized matrix
	Result.SetMatrixBlock(0,0,BlockDiagonalize(A));
	Result.SetMatrixBlock(m-1,m-1,Sa);

	return Result;	
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::Mutate(const vbType& MutationAmountPercentage)
{
	for(int i = 0; i < m_NumOfRows; ++i)
		for(int j = 0; j < m_NumOfCols; ++j)
			(*this)(i,j) += (Random1() - 0.5) * 2.0 * MutationAmountPercentage * (*this)(i,j);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const vbMatrix<vbType> vbMatrix<vbType>::GetNormalizedMatrix()const
{
	vbMatrix<vbType> Result(*this);
	for(int i = 0; i < m_NumOfCols; ++i)
	{
		complex<vbType> Mag = 0;

		for(int j = 0; j < m_NumOfRows; ++j)
			Mag += std::real(at(j,i)*std::conj(at(j,i)));

		Mag = std::sqrt(Mag);

		if(Mag != complex<vbType>(0))
			for(int j = 0; j < m_NumOfRows; ++j)
				Result.at(j,i) /= Mag;
	}

	return Result;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::SetColVector(const int& i,const vbMatrix<vbType>& Vector)
{
	if(i >= m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to set a vector outside the size of the matrix";
		return;
	}

	if(Vector.GetNumOfRows() != m_NumOfRows)
	{
		GlobalErrorLog += "\nTried to set a vector of unequal number of rows to the matrix";
		return;
	}

	for(int j = 0; j < m_NumOfRows; ++j)
		at(j,i) = Vector(j,0);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::AddZeroRowVectors(const int& NumOfRowVectorsToAdd)
{
	for(int i = 0; i < NumOfRowVectorsToAdd; ++i)
		m_Matrix.push_back(RowVectorToAdd);

	m_NumOfRows += NumOfRowVectorsToAdd;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::AddZeroColVectors(const int& NumOfColVectorsToAdd)
{
	for(int i = 0; i < NumOfColVectorsToAdd; ++i)
		for(int j = 0; j < m_NumOfRows; ++j)
			m_Matrix.push_back(vbType(0));

	m_NumOfCols += NumOfColVectorsToAdd;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::AddRowVector(const vbMatrix<vbType>& RowVector)
{
	// Check if matrix is has been initialized
	if(m_NumOfRows == 0 || m_NumOfCols == 0)
	{
		(*this) = RowVector;
		return;
	}

	int m = RowVector.GetNumOfRows();
	int n = RowVector.GetNumOfCols();

	// Add zero rows to the current matrix
	AddZeroRowVectors(m);

	// Add additional columns to the current matrix if needed
	if(n > m_NumOfCols)
		this->AddZeroColVectors(n-m_NumOfCols);

	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			at(m_NumOfRows - m + i,j) = RowVector(i,j);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::AddColVector(const vbMatrix<vbType>& ColVector)
{
	// Check if matrix has been initialized
	if(m_NumOfRows == 0 || m_NumOfCols == 0)
	{
		(*this) = ColVector;
		return;
	}

	// Get the number of rows and columns of the passed vector
	int m = ColVector.GetNumOfRows();
	int n = ColVector.GetNumOfCols();

	// Add zero columns to the current matrix
	AddZeroColVectors(n);

	// Add additional columns to the current matrix if needed
	if(m > m_NumOfRows)
		this->AddZeroRowVectors(n-m_NumOfRows);

	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			(*this)(i,j) = ColVector(i,j);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::SetRowVector(const int& i,const vbMatrix<vbType>& Vector)
{
	if(i >= m_NumOfRows)
	{
		GlobalErrorLog += "\nTried to set a vector outside the size of the matrix";
		return;
	}

	if(Vector.GetNumOfCols() != m_NumOfCols)
	{
		GlobalErrorLog += "\nTried to set a vector of unequal number of rows to the matrix";
		return;
	}

	for(int j = 0; j < m_NumOfCols; ++j)
		at(i,j) = Vector(0,j);
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::RandomizeMatrix(const vbType& MinValue,const vbType& MaxValue)
{
	vbType ValueDiff = MaxValue - MinValue;

	for(int i = 0; i < m_NumOfRows; ++i)
		for(int j = 0; j < m_NumOfCols; ++j)
			(*this)(i,j) = ((Random1()) * ValueDiff) + MinValue;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::RandomizeMatrixIntelligently(const vbType& MinValue,
														   const vbType& MaxValue,
														   const vbType& SmoothnessConstant)
{
	// Variable representing the numeric range of the random values
	vbType ValueRange = std::abs(MaxValue - MinValue);

	// Variables used to calculate the new value of each matrix component
	vbType Value = 0;

	// Variable used to know how many matrix components were
	// used in averaging the new value during each step
	// of the algorithm, so that we know what to divide the
	// calculated value by to get the average
	int HowManyValuesWereUsedForTheAverage = 0;

	// Used to calculate the convergence of the algorithm
	vbType ValueVariation = 1;

	while(ValueVariation > 0.001)
	{
		for(int i = 0; i < m_NumOfRows; ++i)
		{
			for(int j = 0; j < m_NumOfCols; ++j)
			{
				// Reset the value variable
				Value = 0;

				// Reset the averaging variable
				HowManyValuesWereUsedForTheAverage = 0;

				// Average the value of the four components
				// surrounding this current component:
				// (i-1,j),(i+1,j),(i,j+1),(i,j-1)
				if(i > 0)
				{
					Value += (*this)(i-1,j);
					++HowManyValuesWereUsedForTheAverage;
				}
				if(i < (m_NumOfRows - 1))
				{
					Value += (*this)(i+1,j);
					++HowManyValuesWereUsedForTheAverage;
				}
				if(j > 0)
				{
					Value += (*this)(i,j-1);
					++HowManyValuesWereUsedForTheAverage;
				}
				if(j < (m_NumOfCols - 1))
				{
					Value += (*this)(i,j+1);
					++HowManyValuesWereUsedForTheAverage;
				}

				Value /= HowManyValuesWereUsedForTheAverage;

				Value += (Random1() - 0.5)*2.0*(Random1()*ValueRange + MinValue)*ValueVariation;

				// Set the value of (i,j)
				(*this)(i,j) = Value;
			}
		}

		ValueVariation *= SmoothnessConstant;
	}
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> eye(const int& NumOfRows)
{
	vbMatrix<vbType> Matrix(NumOfRows,NumOfRows,0);

	for(int i = 0; i < NumOfRows; ++i)
		Matrix(i,i) = 1;

	return Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbMatrix<vbType> zeroes(const int& NumOfRows,const int& NumOfCols)
{
	vbMatrix<vbType> Matrix(NumOfRows,NumOfRows,0);
	return Matrix;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const int& vbMatrix<vbType>::GetNumOfRows()const
{
	return m_NumOfRows;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline const int& vbMatrix<vbType>::GetNumOfCols()const
{
	return m_NumOfCols;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline void vbMatrix<vbType>::RowSwap(const int &Row1, const int &Row2)
{
	// Check to see if indeces are valid or if they're the same
	if((Row1 == Row2) || (Row1 < 0) || (Row1 > (m_NumOfRows - 1)) || (Row2 < 0) || (Row2 > (m_NumOfRows - 1)))
		return;

	// Swap the rows
	for(int i = 0; i < m_NumOfCols; ++i)
		std::swap(at(Row1,i),at(Row2,i));
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool riccati(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
					const vbMatrix<vbType>& Q,const vbMatrix<vbType>& R,
					vbMatrix<vbType>& P)
{
	// Get the number of rows and columns of A and
	// check if A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nA is non-square";
		return false;
	}

	// Check if A,B,Q and R are the correct sizes
	if(m != B.GetNumOfRows())
	{
		GlobalErrorLog += "\nB is the wrong size";
		return false;
	}
	if(m != Q.GetNumOfRows() || m != Q.GetNumOfCols())
	{
		GlobalErrorLog += "\nQ is the wrong size";
		return false;
	}
	if(R.GetNumOfRows() != R.GetNumOfCols() || R.GetNumOfRows() != B.GetNumOfCols())
	{
		GlobalErrorLog+= "\nR is the wrong size";
		return false;
	}

	vbMatrix<vbType> D = B*inv(R)*Transpose(B);

	// Construct the hamiltonian matrix: H = [A,-D;-Q,-Transpose(A)];
	vbMatrix<vbType> H(2*m,2*m,0);
	H.SetMatrixBlock(0,0,A);
	H.SetMatrixBlock(0,m,-D);
	H.SetMatrixBlock(m,0,-Q);
	H.SetMatrixBlock(m,m,-Transpose(A));

	// Calculate the matrix sign of H: S = [S11,S12;S21,S22]
	vbMatrix<vbType> S = MatrixSign(H);
	
	//S11 = S.GetMatrixBlock(0,0,m-1,m-1);
	//S12 = S.GetMatrixBlock(0,m,m-1,2*m-1);
	//S21 = S.GetMatrixBlock(m,0,2*m-1,m-1);
	//S22 = S.GetMatrixBlock(m,m,2*m-1,2*m-1);

	// P is given by: P = -inv(S12)*(S11 + II)
	P = -inv(S.GetMatrixBlock(0,m,m-1,2*m-1))*(S.GetMatrixBlock(0,0,m-1,m-1) + eye<vbType>(m));

	return true;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool riccati(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
					const vbMatrix<vbType>& Q,const vbMatrix<vbType>& R,
					vbMatrix<vbType>& P,vbMatrix<vbType>& K)
{
	// Solve the riccati equation
	if(!(riccati(A,B,Q,R,P)))
		return false;

	// The gain matrix K is given by: K = inv(R)*Transpose(B)*P
	K = inv(R)*Transpose(B)*P;

	return true;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool riccati(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
					const vbMatrix<vbType>& Q,const vbMatrix<vbType>& R,
					vbMatrix<vbType>& P,vbMatrix<vbType>& K,vbMatrix<vbType>& Ac,
					vbMatrix<vbType>& AcEIGS,vbMatrix<vbType>& AcEIGENVECTORS)
{
	// Solve the riccati equation
	if(!(riccati(A,B,Q,R,P,K)))
		return false;

	// The closed loop Ac is given by: Ac = A - B*K
	Ac = A - B*K;

	// Check the eigenvalues of the closed loop Ac to prove it is stable
	eigs(Ac,AcEIGS,AcEIGENVECTORS);

	return true;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline bool riccati(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
					const vbMatrix<vbType>& Q,const vbMatrix<vbType>& R,
					vbMatrix<vbType>& P,vbMatrix<vbType>& K,vbMatrix<vbType>& Ac,
					vbMatrix<vbType>& AcEIGS,vbMatrix<vbType>& AcEIGENVECTORS,
					string& ResultsString)
{
	// Solve the riccati equation and calculate K,Ac,AcEIGS,AcEIGENVECTORS
	if(!(riccati(A,B,Q,R,P,K,Ac,AcEIGS,AcEIGENVECTORS)))
		return false;

	// Save the results to the ResultsString
	stringstream Result;
	Result << "\n\nGiven:\n\n\nA =\n\n" << A << "\n\n\nB =\n\n" << B << "\n\n\nQ =\n\n" << Q << "\n\n\nR =\n\n" << R
		   << "\n\n\n\nSolved for P,K and Ac\n\n\nP =\n\n" << P << "\n\n\nK = inv(R)*Transpose(B)*P =\n\n" << K
		   << "\n\n\nAc = A - B*K =\n\n" << Ac << "\n\n\nEigenValues of Ac are:\n\n\nEIGS =\n\n" << AcEIGS;

	ResultsString += Result.str();

	return true;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType hinf(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
				   const vbMatrix<vbType>& C,const vbMatrix<vbType>& D,
				   const vbType& Zero,const vbType& MinError,int& NumOfIterations,
				   vbType& Error)
{
	// Get the number of rows and columns of A and
	// check if A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nA is non-square";
		return false;
	}

	// Check if A,B,Q and R are the correct sizes
	if(m != B.GetNumOfRows())
	{
		GlobalErrorLog += "\nB is the wrong size";
		return false;
	}

	// Calculate all the transposes of the system matrices that will be used in the bisection algorithm
	vbMatrix<vbType> At = Transpose(A);
	vbMatrix<vbType> Bt = Transpose(B);
	vbMatrix<vbType> Ct = Transpose(C);
	vbMatrix<vbType> Dt = Transpose(D);

	// Define a matrix Hgamma that will be used to calculate the infinity norm of the system
	vbMatrix<vbType> HgammaMin(2*m,2*m,0);
	vbMatrix<vbType> HgammaMax(2*m,2*m,0);
	vbMatrix<vbType> HgammaNew(2*m,2*m,0);

	// Define matrices S and R which will be used to create the Hgamma matrix
	vbMatrix<vbType> S;
	vbMatrix<vbType> R;

	// Form an eye matrix of the dimensions the same as the number of rows of D
	vbMatrix<vbType> II = eye<vbType>(D.GetNumOfRows());

	// Find guess for the initial gamma values
	vbType GammaMin = 1;
	vbType GammaMax = 5;
	vbType Gamma = GammaMax;
	vbType GammaOld = Gamma;

	// Loop until one GammaMin has purely imaginary eigen values
	while(1)
	{
		// Form the R matrix: R = Dt*D - GammaMin^2*II
		R = Dt*D - GammaMin*GammaMin*II;

		// Form the S matrix: S = D*Dt - GammaMin^2*II
		S = D*Dt - GammaMin*GammaMin*II;

		// Form the HgammaMin matrix:
		// Hgamma = [A-B*inv(R)*Dt*C, -B*inv(R)*Bt;
		//			 Gamma^2*Ct*inv(S)*C, -At+Ct*D*inv(R)*Bt]
		HgammaMin.SetMatrixBlock(0,0,(A - B*inv(R)*Dt*C));
		HgammaMin.SetMatrixBlock(0,m,(-B*inv(R)*Bt));
		HgammaMin.SetMatrixBlock(m,0,(GammaMin*GammaMin*Ct*inv(S)*C));
		HgammaMin.SetMatrixBlock(m,m,(-At + Ct*D*inv(R)*Bt));

		if(DoesMatrixHavePurelyImaginaryEigenValues(HgammaMin,Zero))
			break;

		// Update the GammaMin initial guess
		GammaMin /= 2;
	}

	// Loop until one GammaMax has no purely imaginary eigen values
	while(1)
	{
		// Form the R matrix: R = Dt*D - GammaMax^2*II
		R = Dt*D - GammaMax*GammaMax*II;

		// Form the S matrix: S = D*Dt - GammaMax^2*II
		S = D*Dt - GammaMax*GammaMax*II;

		// Form the HgammaMax matrix:
		// Hgamma = [A-B*inv(R)*Dt*C, -B*inv(R)*Bt;
		//			 Gamma^2*Ct*inv(S)*C, -At+Ct*D*inv(R)*Bt]
		HgammaMax.SetMatrixBlock(0,0,(A - B*inv(R)*Dt*C));
		HgammaMax.SetMatrixBlock(0,m,(-B*inv(R)*Bt));
		HgammaMax.SetMatrixBlock(m,0,(GammaMax*GammaMax*Ct*inv(S)*C));
		HgammaMax.SetMatrixBlock(m,m,(-At + Ct*D*inv(R)*Bt));

		if(!(DoesMatrixHavePurelyImaginaryEigenValues(HgammaMax,Zero)))
			break;

		// Update the GammaMax initial guess
		GammaMax *= 2;
	}

	// Error variable used in the bisection method
	Error = MinError*2;

	// To calculate the infinity norm of the system, we loop through
	// the bisection method until the desired error has been achieved
	NumOfIterations = 0;
	while(Error > MinError)
	{
		// Store the old gamma value
		GammaOld = Gamma;

		// Find the mid-point gamma value
		Gamma = vbType(0.5)*(GammaMin + GammaMax);

		// Calculate the convergence error
		Error = std::abs((Gamma - GammaOld)/GammaOld) * 100;

		// Form the R matrix: R = Dt*D - Gamma^2*II
		R = Dt*D - Gamma*Gamma*II;

		// Form the S matrix: S = D*Dt - Gamma^2*II
		S = D*Dt - Gamma*II;

		// Form the HgammaNew matrix:
		// Hgamma = [A-B*inv(R)*Dt*C, -B*inv(R)*Bt;
		//			 Gamma^2*Ct*inv(S)*C, -At+Ct*D*inv(R)*Bt]
		HgammaNew.SetMatrixBlock(0,0,(A - B*inv(R)*Dt*C));
		HgammaNew.SetMatrixBlock(0,m,(-B*inv(R)*Bt));
		HgammaNew.SetMatrixBlock(m,0,(Gamma*Gamma*Ct*inv(S)*C));
		HgammaNew.SetMatrixBlock(m,m,(-At + Ct*D*inv(R)*Bt));

		if(DoesMatrixHavePurelyImaginaryEigenValues(HgammaNew,Zero))
			GammaMin = Gamma;
		else
			GammaMax = Gamma;

		++NumOfIterations;
	}

	return Gamma;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename vbType>
inline vbType riccatiMIMO(const vbMatrix<vbType>& A,const vbMatrix<vbType>& B,
						  const vbMatrix<vbType>& C,const vbMatrix<vbType>& D,
						  const vbType& Zero,const vbType& MinError,
						  vbMatrix<vbType>& P,vbMatrix<vbType>& K,vbMatrix<vbType>& Ac,
						  vbMatrix<vbType>& AcEIGS,vbMatrix<vbType>& AcEIGENVECTORS,
						  string& ResultsString)
{
	// Get the number of rows and columns of A and
	// check if A is square
	int m = A.GetNumOfRows();
	if(m != A.GetNumOfCols())
	{
		GlobalErrorLog += "\nA is non-square";
		return false;
	}

	// Check if A,B,Q and R are the correct sizes
	if(m != B.GetNumOfRows())
	{
		GlobalErrorLog += "\nB is the wrong size";
		return false;
	}

	// Variables used for hinf norm calculation
	vbType Error;
	int NumOfIterations;

	// Calculate the hinf norm of the system
	vbType Gamma = hinf(A,B,C,D,Zero,MinError,NumOfIterations,Error);

	// Calculate Q = Transpose(C)*C
	vbMatrix<vbType> Q = Transpose(C)*C;

	// Calculate R = Gamma*II
	vbMatrix<vbType> R = Gamma*Gamma * eye<vbType>(B.GetNumOfCols());

	// Call the riccati equation
	if(!(riccati(A,B,Q,R,P,K,Ac,AcEIGS,AcEIGENVECTORS)))
		return vbType(0);

	// Save the results to the ResultsString
	stringstream Result;
	Result << "\n\nGiven:\n\n\nA =\n\n" << A << "\n\n\nB =\n\n" << B << "\n\n\nC =\n\n" << C << "\n\n\nD =\n\n" << D
		   << "\n\n\n\nSolved for a minimal Gamma = GammaMin = \n\n" << Gamma
		   << "\n\nThe bisection method went through " << NumOfIterations << " loops to find Gamma and the"
		   << " convergence error is:\n\nError = " << Error
		   << "\n\n\nCalculated a Q = Ct*C =\n\n" << Q << "\n\n\nCalculated an R = Gamma^2*II =\n\n" << R
		   << "\n\n\n\nSolved for P,K and Ac\n\n\nP =\n\n" << P << "\n\n\nK = inv(R)*Transpose(B)*P =\n\n" << K
		   << "\n\n\nAc = A - B*K =\n\n" << Ac << "\n\n\nEigenValues of Ac are:\n\n\nEIGS =\n\n" << AcEIGS;

	ResultsString += Result.str();

	return Gamma;
}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
#endif // _VBMATRIX_
//---------------------------------------------------------------------------------------