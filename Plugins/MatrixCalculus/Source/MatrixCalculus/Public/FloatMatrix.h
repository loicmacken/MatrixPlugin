#pragma once

class FFloatMatrix
{
private:
	TArray<float> M;
	int32 M_Size;
	int32 M_Rows;
	int32 M_Cols;
	
public:
	// Base Constructors
	explicit FFloatMatrix(int32 NumRows, int32 NumCols); // Base
	explicit FFloatMatrix(int32 Size); // Square matrix (Size x Size)
	FFloatMatrix(std::initializer_list<std::initializer_list<float>> InitList); 
	FFloatMatrix(const FFloatMatrix& Source); // Copy
	FFloatMatrix(FFloatMatrix&& Source) noexcept; // Move

	// Assignment operators
	FFloatMatrix& operator=(const FFloatMatrix& Source); // Copy
	FFloatMatrix& operator=(FFloatMatrix&& Source) noexcept; // Move

	// Destructor
	~FFloatMatrix(); 
	
	// Constructors from vectors
	// NOTE: converts to float! loss of precision!
	FFloatMatrix(FVector2D InVector2D); // FVector2D: becomes (2 * 1) matrix = column vector
	FFloatMatrix(FVector InVector); // FVector: becomes (3 * 1) matrix = column vector
	FFloatMatrix(FVector4 InVector4); // FVector4: becomes (4 * 1) matrix = column vector
	
	// Static Constructors
	static FFloatMatrix Zeros(int32 NumRows, int32 NumCols);
	static FFloatMatrix Ones(int32 NumRows, int32 NumCols);
	static FFloatMatrix Identity(int32 Size); // Only square matrices
	static FFloatMatrix Transposed(const FFloatMatrix& Source); // Returns a new, transposed copy. For copy in-place use T()
	static FFloatMatrix RowFromArray(const TArray<float>& Source); // Returns (1xn) matrix with values from Source
	static FFloatMatrix ColFromArray(const TArray<float>& Source); // Returns (mx1) matrix with values from Source

	// Comparison operators
	bool operator==(const FFloatMatrix& RHS) const;
	bool operator!=(const FFloatMatrix& RHS) const;
	
	// Element accessors
	float& operator()(int32 RowIndex, int32 ColIndex);
	const float& operator()(int32 RowIndex, int32 ColIndex) const;

	// Matrix-Scalar operations
	FFloatMatrix& operator+=(float Val);
	FFloatMatrix operator+(float Val) const;
	FFloatMatrix& operator-=(float Val);
	FFloatMatrix operator-(float Val) const;
	FFloatMatrix& operator*=(float Val);
	FFloatMatrix operator*(float Val) const;
	FFloatMatrix& operator/=(float Val);
	FFloatMatrix operator/(float Val) const;

	// ELEMENT-WISE(!) Matrix operations
	FFloatMatrix& operator+=(const FFloatMatrix& RHS);
	FFloatMatrix operator+(const FFloatMatrix& RHS) const;
	FFloatMatrix& operator-=(const FFloatMatrix& RHS);
	FFloatMatrix operator-(const FFloatMatrix& RHS) const;
	FFloatMatrix& operator*=(const FFloatMatrix& RHS);
	FFloatMatrix operator*(const FFloatMatrix& RHS) const;
	FFloatMatrix& operator/=(const FFloatMatrix& RHS);
	FFloatMatrix operator/(const FFloatMatrix& RHS) const;

	// Matrix multiplication
	FFloatMatrix MatMul(const FFloatMatrix& RHS) const;
	FFloatMatrix MatMul(const FVector2D& RHS) const;
	FFloatMatrix MatMul(const FVector& RHS) const;
	FFloatMatrix MatMul(const FVector4& RHS) const;
	
	// Transpose (in-place)
	FFloatMatrix& T();
	
	// Sum
	FFloatMatrix Sum(int32 Axis = -1);
	
	int32 Num() const { return M_Size; }
	int32 Rows() const { return M_Rows; }
	int32 Cols() const { return M_Cols; }

#if WITH_EDITOR
	// Editor-only functions
	void Show() const
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ToString())
	}
	FString ToString() const
	{
		FString Result = FString(TEXT("["));
		for (int32 Row = 0; Row < M_Rows; Row++)
		{
			Result.Append(TEXT("\n[ "));
			for (int32 Col = 0; Col < M_Cols; Col++)
			{
				Result.Append(FString::Printf(TEXT("%f "), (*this)(Row, Col)));
			}
			Result.Append(TEXT("]"));
		}
		Result.Append(TEXT("\n]"));
		return Result;
	}
#endif

private:
	bool EqualShape(const FFloatMatrix& Other) const
	{
		return (M_Size == Other.M_Size) && (M_Rows == Other.M_Rows) && (M_Cols == Other.M_Cols);
	}
	static FFloatMatrix CreateAndFill(int32 NumRows, int32 NumCols, float FillValue)
	{
		auto Mat = FFloatMatrix(NumRows, NumCols);
		Mat.M.Init(FillValue, Mat.M_Size);
		return Mat;
	}

};

// Non-member operators
FFloatMatrix operator*(float LHS, const FFloatMatrix& RHS);