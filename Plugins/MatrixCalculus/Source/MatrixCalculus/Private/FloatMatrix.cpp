#include "FloatMatrix.h"

FFloatMatrix::FFloatMatrix(int32 NumRows, int32 NumCols) : M_Rows(NumRows), M_Cols(NumCols)
{
	M_Size = M_Rows * M_Cols;
	M.Empty(M_Size);
}

FFloatMatrix::FFloatMatrix(int32 Size) : FFloatMatrix(Size, Size)
{
}

FFloatMatrix::FFloatMatrix(FVector2D InVector2D)
{
	M = { (float)InVector2D.X, (float)InVector2D.Y };
	M_Rows = 2;
	M_Cols = 1;
	M_Size = M_Rows * M_Cols;
}

FFloatMatrix::FFloatMatrix(FVector InVector)
{
	M = { (float)InVector.X, (float)InVector.Y, (float)InVector.Z };
	M_Rows = 3;
	M_Cols = 1;
	M_Size = M_Rows * M_Cols;
}

FFloatMatrix::FFloatMatrix(FVector4 InVector4)
{
	M = { (float)InVector4.X, (float)InVector4.Y, (float)InVector4.Z, (float)InVector4.W };
	M_Rows = 4;
	M_Cols = 1;
	M_Size = M_Rows * M_Cols;
}

FFloatMatrix::FFloatMatrix(const FFloatMatrix& Source) : M_Rows(Source.M_Rows), M_Cols(Source.M_Cols)
{
	M_Size = Source.M_Size;
	// call copy ctor
	M = TArray(Source.M);
}

FFloatMatrix::FFloatMatrix(FFloatMatrix&& Source) noexcept
{
	M_Size = Source.M_Size;
	M_Rows = Source.M_Rows;
	M_Cols = Source.M_Cols;
	M = Source.M;
	Source.M.Empty();
}

FFloatMatrix::FFloatMatrix(std::initializer_list<std::initializer_list<float>> InitList)
{
	M_Rows = InitList.size();
	M_Cols = InitList.begin()->size();
	M_Size = M_Rows * M_Cols;
	M.Empty(M_Size);
	for (auto& Row : InitList)
	{
		M.Append(Row);
	}
}

FFloatMatrix FFloatMatrix::Zeros(int32 NumRows, int32 NumCols)
{
	return CreateAndFill(NumRows, NumCols, 0.f);
}

FFloatMatrix FFloatMatrix::Ones(int32 NumRows, int32 NumCols)
{
	return CreateAndFill(NumRows, NumCols, 1.f);
}

FFloatMatrix FFloatMatrix::Identity(int32 Size)
{
	auto Mat = Zeros(Size, Size);
	for (int32 i = 0; i < Size; i++)
	{
		Mat(i,i) = 1.f;
	}
	return Mat;
}

FFloatMatrix FFloatMatrix::Transposed(const FFloatMatrix& Source)
{
	FFloatMatrix Result = FFloatMatrix(Source);
	Result.T();
	return Result;
}

FFloatMatrix FFloatMatrix::RowFromArray(const TArray<float>& Source)
{
	FFloatMatrix Result = FFloatMatrix(1, Source.Num());
	Result.M = Source;
	return Result;
}

FFloatMatrix FFloatMatrix::ColFromArray(const TArray<float>& Source)
{
	FFloatMatrix Result = FFloatMatrix(Source.Num(), 1);
	Result.M = Source;
	return Result;
}

FFloatMatrix& FFloatMatrix::operator=(const FFloatMatrix& Source)
{
	if (&Source == this)
	{
		return *this;
	}

	M_Size = Source.M_Size;
	M = Source.M;
	M_Rows = Source.M_Rows;
	M_Cols = Source.M_Cols;
	return *this;
}

FFloatMatrix& FFloatMatrix::operator=(FFloatMatrix&& Source) noexcept
{
	if (this != &Source)
	{
		M.Empty();

		M_Size = Source.M_Size;
		M_Rows = Source.M_Rows;
		M_Cols = Source.M_Cols;
		M = Source.M;
		Source.M.Empty();
	}
	return *this;
}

FFloatMatrix::~FFloatMatrix()
{
	M.Empty();
}

bool FFloatMatrix::operator==(const FFloatMatrix& RHS) const
{
	if (!EqualShape(RHS))
	{
		return false;
	}
	for (int32 Row = 0; Row < M_Rows; Row++)
	{
		for (int32 Col = 0; Col < M_Cols; Col++)
		{
			if (!FMath::IsNearlyEqual((*this)(Row, Col), RHS(Row, Col), KINDA_SMALL_NUMBER))
			{
				return false;
			}
		}
	}

	return true;
}

bool FFloatMatrix::operator!=(const FFloatMatrix& RHS) const
{
	return !operator==(RHS);
}

float& FFloatMatrix::operator()(int32 RowIndex, int32 ColIndex)
{
	check(RowIndex <= M_Rows)
	check(ColIndex <= M_Cols)
	return M[RowIndex * M_Cols + ColIndex];
}

const float& FFloatMatrix::operator()(int32 RowIndex, int32 ColIndex) const
{
	check(RowIndex <= M_Rows)
	check(ColIndex <= M_Cols)
	return M[RowIndex * M_Cols + ColIndex];
}

FFloatMatrix& FFloatMatrix::operator+=(float Val)
{
	for (auto& Elem : M)
	{
		Elem += Val; 
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator+(float Val) const
{
	auto Result = *this;
	return Result += Val;
}

FFloatMatrix& FFloatMatrix::operator-=(float Val)
{
	for (auto& Elem : M)
	{
		Elem -= Val; 
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator-(float Val) const
{
	auto Result = *this;
	return Result -= Val;
}

FFloatMatrix& FFloatMatrix::operator*=(float Val)
{
	for (auto& Elem : M)
	{
		Elem *= Val; 
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator*(float Val) const
{
	auto Result = *this;
	return Result *= Val;
}

FFloatMatrix& FFloatMatrix::operator/=(float Val)
{
	for (auto& Elem : M)
	{
		Elem /= Val; 
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator/(float Val) const
{
	auto Result = *this;
	return Result /= Val;
}

FFloatMatrix& FFloatMatrix::operator+=(const FFloatMatrix& RHS)
{
	check(EqualShape(RHS))
	for (int32 i = 0; i < M_Size; i++)
	{
		M[i] += RHS.M[i];
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator+(const FFloatMatrix& RHS) const
{
	auto Result = *this;
	return Result += RHS;
}

FFloatMatrix& FFloatMatrix::operator-=(const FFloatMatrix& RHS)
{
	check(EqualShape(RHS))
	for (int32 i = 0; i < M_Size; i++)
	{
		M[i] -= RHS.M[i];
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator-(const FFloatMatrix& RHS) const
{
	auto Result = *this;
	return Result -= RHS;
}

FFloatMatrix& FFloatMatrix::operator*=(const FFloatMatrix& RHS)
{
	check(EqualShape(RHS))
	for (int32 i = 0; i < M_Size; i++)
	{
		M[i] *= RHS.M[i];
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator*(const FFloatMatrix& RHS) const
{
	auto Result = *this;
	return Result *= RHS;
}

FFloatMatrix& FFloatMatrix::operator/=(const FFloatMatrix& RHS)
{
	check(EqualShape(RHS))
	for (int32 i = 0; i < M_Size; i++)
	{
		M[i] /= RHS.M[i];
	}
	return *this;
}

FFloatMatrix FFloatMatrix::operator/(const FFloatMatrix& RHS) const
{
	auto Result = *this;
	return Result /= RHS;
}

FFloatMatrix FFloatMatrix::MatMul(const FFloatMatrix& RHS) const
{
	check(M_Cols == RHS.M_Rows)
	FFloatMatrix Result = Zeros(M_Rows, RHS.M_Cols);
	/*
	 *	Multiply (n x m) by (m x o) matrix
	 */
	for (int32 n = 0; n < M_Rows; n++)
	{
		for (int32 o = 0; o < RHS.M_Cols; o++)
		{
			for (int32 m = 0; m < M_Cols; m++)
			{
				Result(n,o) += (*this)(n,m) * RHS(m,o);
			}
		}
	}

	return Result;
}

FFloatMatrix FFloatMatrix::MatMul(const FVector2D& RHS) const
{
	const FFloatMatrix Mat = FFloatMatrix(RHS);
	return MatMul(Mat);
}

FFloatMatrix FFloatMatrix::MatMul(const FVector& RHS) const
{
	const FFloatMatrix Mat = FFloatMatrix(RHS);
	return MatMul(Mat);
}

FFloatMatrix FFloatMatrix::MatMul(const FVector4& RHS) const
{
	const FFloatMatrix Mat = FFloatMatrix(RHS);
	return MatMul(Mat);
}

FFloatMatrix& FFloatMatrix::T()
{
	auto PrevMat = FFloatMatrix(*this);
	int32 Temp = M_Rows;
	M_Rows = M_Cols;
	M_Cols = Temp;
	for (int32 Col = 0; Col < M_Cols; Col++)
	{
		for (int32 Row = 0; Row < M_Rows; Row++)
		{
			(*this)(Row, Col) = PrevMat(Col, Row);
		}
	}
	return *this;
}

FFloatMatrix FFloatMatrix::Sum(int32 Axis)
{
	/*
	 *	Axis = -1 (default): sums all elements; returns a (1x1) matrix
	 *	Axis = 0: sums the values along columns; returns a (1xn) matrix
	 *	Axis = 1: sums the values along rows; returns a (mx1) matrix
	 */
	if (Axis == 0)
	{
		FFloatMatrix Result = Zeros(1, M_Cols);
		for (int32 Row = 0; Row < M_Rows; Row++)
		{
			for (int32 Col = 0; Col < M_Cols; Col++)
			{
				Result(0, Col) += (*this)(Row, Col);
			}
		}
		return Result;
	}
	
	if (Axis == 1)
	{
		FFloatMatrix Result = Zeros(M_Rows, 1);
		for (int32 Row = 0; Row < M_Rows; Row++)
		{
			for (int32 Col = 0; Col < M_Cols; Col++)
			{
				Result(Row, 0) += (*this)(Row, Col);
			}
		}
		return Result;
	}

	FFloatMatrix Result = Zeros(1, 1);
	for (int32 Row = 0; Row < M_Rows; Row++)
	{
		for (int32 Col = 0; Col < M_Cols; Col++)
		{
			Result(0, 0) += (*this)(Row, Col);
		}
	}
	return Result;
}

FFloatMatrix operator*(float LHS, const FFloatMatrix& RHS)
{
	return RHS * LHS;
}
