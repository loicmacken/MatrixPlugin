#include "FloatMatrixTest.h"

#include "../Plugins/MatrixCalculus/Source/MatrixCalculus/Public/FloatMatrix.h" 
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFloatMatrixTest, "FloatMatrixTests", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FFloatMatrixTest::RunTest(const FString& Parameters)
{
	// Base Constructor tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix(3, 3);
		FFloatMatrix Mat2 = FFloatMatrix(3);
		FFloatMatrix Mat3 = FFloatMatrix({{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}});
		FFloatMatrix Mat4 = FFloatMatrix(Mat3);

		// Tests
		// Constructor with Rows and Cols
		TestEqual(TEXT("Testing Constructor with Rows and Columns: Num"), Mat1.Num(), 9);
		TestEqual(TEXT("Testing Constructor with Rows and Columns: Rows"), Mat1.Rows(), 3);
		TestEqual(TEXT("Testing Constructor with Rows and Columns: Cols"), Mat1.Cols(), 3);
		// Constructor with Size
		TestEqual(TEXT("Testing Constructor with Size: Num"), Mat2.Num(), 9);
		TestEqual(TEXT("Testing Constructor with Size: Rows"), Mat2.Rows(), 3);
		TestEqual(TEXT("Testing Constructor with Size: Cols"), Mat2.Cols(), 3);
		// Constructor with InitList
		TestEqual(TEXT("Testing Constructor with InitList: Num"), Mat3.Num(), 9);
		TestEqual(TEXT("Testing Constructor with InitList: Rows"), Mat3.Rows(), 3);
		TestEqual(TEXT("Testing Constructor with InitList: Cols"), Mat3.Cols(), 3);
		// Copy Constructor
		TestEqual(TEXT("Testing Copy Constructor: Num"), Mat4.Num(), 9);
		TestEqual(TEXT("Testing Copy Constructor: Rows"), Mat4.Rows(), 3);
		TestEqual(TEXT("Testing Copy Constructor: Cols"), Mat4.Cols(), 3);
	}
	
	// Static Constructor tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix::Zeros(3, 3);
		FFloatMatrix Mat2 = FFloatMatrix::Ones(3, 3);
		FFloatMatrix Mat3 = FFloatMatrix::Identity(3);
		FFloatMatrix Mat4 = FFloatMatrix::Transposed(FFloatMatrix({{1.f, 2.f}, {3.f, 4.f}}));
		FFloatMatrix Mat5 = FFloatMatrix::RowFromArray(TArray<float>({1.f, 2.f, 3.f}));
		FFloatMatrix Mat6 = FFloatMatrix::ColFromArray(TArray<float>({1.f, 2.f, 3.f}));

		// Tests
		TestEqual(TEXT("Testing Static Constructor Zeros"), Mat1, FFloatMatrix({{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}}));
		TestEqual(TEXT("Testing Static Constructor Ones"), Mat2, FFloatMatrix({{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}}));
		TestEqual(TEXT("Testing Static Constructor Identity"), Mat3, FFloatMatrix({{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f, 1.f}}));
		TestEqual(TEXT("Testing Static Constructor Transposed"), Mat4, FFloatMatrix({{1.f, 3.f}, {2.f, 4.f}}));
		// Row from array
		TestEqual(TEXT("Testing Static Constructor RowFromArray: Num"), Mat5.Num(), 3);
		TestEqual(TEXT("Testing Static Constructor RowFromArray: Rows"), Mat5.Rows(), 1);
		TestEqual(TEXT("Testing Static Constructor RowFromArray: Cols"), Mat5.Cols(), 3);
		TestEqual(TEXT("Testing Static Constructor RowFromArray: Values"), Mat5, FFloatMatrix({{1.f, 2.f, 3.f}}));
		// Col from array
		TestEqual(TEXT("Testing Static Constructor ColFromArray: Num"), Mat6.Num(), 3);
		TestEqual(TEXT("Testing Static Constructor ColFromArray: Rows"), Mat6.Rows(), 3);
		TestEqual(TEXT("Testing Static Constructor ColFromArray: Cols"), Mat6.Cols(), 1);
		TestEqual(TEXT("Testing Static Constructor ColFromArray: Values"), Mat6, FFloatMatrix({{1.f}, {2.f}, {3.f}}));
	}

	// Comparison Operator tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}});
		FFloatMatrix Mat2 = FFloatMatrix(Mat1);
		FFloatMatrix Mat3 = FFloatMatrix({{1.f, 2.f}});

		// Tests
		TestEqual(TEXT("Testing comparison operator == true case"), Mat1 == Mat2, true);
		TestEqual(TEXT("Testing comparison operator == false case"), Mat1 == Mat3, false);
		TestEqual(TEXT("Testing comparison operator != true case"), Mat1 != Mat3, true);
		TestEqual(TEXT("Testing comparison operator != false case"), Mat1 != Mat2, false);
	}

	// Element Accessor tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}});

		// Tests
		TestEqual(TEXT("Testing element accessor: const"), Mat1(1,0), 4.f);
		Mat1(1, 0) = 7.f;
		TestEqual(TEXT("Testing element accessor: non const"), Mat1(1,0), 7.f);
	}

	// Matrix-Scalar Operation tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}});
		FFloatMatrix Mat2 = FFloatMatrix({{2.f, 2.f, 2.f}, {2.f, 2.f, 2.f}});

		// Tests
		TestEqual(TEXT("Testing Matrix-Scalar operation +"), Mat1 + 1.f, FFloatMatrix({{2.f, 3.f, 4.f}, {5.f, 6.f, 7.f}}));
		FFloatMatrix Mat3 = FFloatMatrix(Mat1);
		Mat3 += 1.f;
		TestEqual(TEXT("Testing Matrix-Scalar operation +="), Mat3, FFloatMatrix({{2.f, 3.f, 4.f}, {5.f, 6.f, 7.f}}));
		
		TestEqual(TEXT("Testing Matrix-Scalar operation -"), Mat1 - 1.f, FFloatMatrix({{0.f, 1.f, 2.f}, {3.f, 4.f, 5.f}}));
		FFloatMatrix Mat4 = FFloatMatrix(Mat1);
		Mat4 -= 1.f;
		TestEqual(TEXT("Testing Matrix-Scalar operation -="), Mat4, FFloatMatrix({{0.f, 1.f, 2.f}, {3.f, 4.f, 5.f}}));
		
		TestEqual(TEXT("Testing Matrix-Scalar operation * (right)"), Mat1 * 2.f, FFloatMatrix({{2.f, 4.f, 6.f}, {8.f, 10.f, 12.f}}));
		TestEqual(TEXT("Testing Matrix-Scalar operation * (left)"), 2.f * Mat1, FFloatMatrix({{2.f, 4.f, 6.f}, {8.f, 10.f, 12.f}}));
		FFloatMatrix Mat5 = FFloatMatrix(Mat1);
		Mat5 *= 2.f;
		TestEqual(TEXT("Testing Matrix-Scalar operation *="), Mat5, FFloatMatrix({{2.f, 4.f, 6.f}, {8.f, 10.f, 12.f}}));
		
		TestEqual(TEXT("Testing Matrix-Scalar operation /"), Mat2 / 2.f, FFloatMatrix({{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}}));
		FFloatMatrix Mat6 = FFloatMatrix(Mat2);
		Mat6 /= 2.f;
		TestEqual(TEXT("Testing Matrix-Scalar operation /="), Mat6, FFloatMatrix({{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}}));
	}

	// Element-wise Operation tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}});
		FFloatMatrix Mat2 = FFloatMatrix({{6.f, 5.f, 4.f}, {3.f, 2.f, 1.f}});
		FFloatMatrix Mat3 = FFloatMatrix({{7.f, 7.f, 7.f}, {7.f, 7.f, 7.f}});
		FFloatMatrix Mat4 = FFloatMatrix({{6.f, 10.f, 12.f}, {12.f, 10.f, 6.f}});
 
		// Tests
		TestEqual(TEXT("Testing Element-wise operation +"), Mat1 + Mat2, Mat3);
		FFloatMatrix Mat5 = FFloatMatrix(Mat1);
		Mat5 += Mat2;
		TestEqual(TEXT("Testing Element-wise operation +="), Mat5, Mat3);
		
		TestEqual(TEXT("Testing Element-wise operation -"), Mat3 - Mat2, Mat1);
		FFloatMatrix Mat6 = FFloatMatrix(Mat3);
		Mat6 -= Mat2;
		TestEqual(TEXT("Testing Element-wise operation -="), Mat6, Mat1);
		
		TestEqual(TEXT("Testing Element-wise operation *"), Mat1 * Mat2, Mat4);
		FFloatMatrix Mat7 = FFloatMatrix(Mat1);
		Mat7 *= Mat2;
		TestEqual(TEXT("Testing Element-wise operation *="), Mat7, Mat4);
		
		TestEqual(TEXT("Testing Element-wise operation /"), Mat4 / Mat2, Mat1);
		FFloatMatrix Mat8 = FFloatMatrix(Mat4);
		Mat8 /= Mat2;
		TestEqual(TEXT("Testing Element-wise operation /="), Mat8, Mat1);
	}

	// Matrix Multiplication tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{6.f, 10.f, 12.f}, {12.f, 10.f, 6.f}});
		FFloatMatrix Mat2 = FFloatMatrix({{3.f, 0.5f}, {2.5f, 0.1f}, {5.f, 100.f}});
		FFloatMatrix ExpectedResult = FFloatMatrix({{103.f, 1204.f}, {91.f, 607.f}});
		
		// Tests
		TestEqual(TEXT("Testing Matrix Multiplication"), Mat1.MatMul(Mat2), ExpectedResult);
	}

	// Transpose tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{6.f, 10.f, 12.f}, {5.f, 4.f, 1.f}});
		FFloatMatrix Mat2 = FFloatMatrix({{3.f, 1.f}, {5.f, 10.f}, {7.f, 2.f}});
		FFloatMatrix ExpectedResult1 = FFloatMatrix({{6.f, 5.f}, {10.f, 4.f}, {12.f, 1.f}});
		FFloatMatrix ExpectedResult2 = FFloatMatrix({{3.f, 5.f, 7.f}, {1.f, 10.f, 2.f}});
		
		// Tests
		TestEqual(TEXT("Testing Transpose 1"), Mat1.T(), ExpectedResult1);
		TestEqual(TEXT("Testing Transpose 2"), Mat2.T(), ExpectedResult2);
	}

	// Sum tests
	{
		// Setup
		FFloatMatrix Mat1 = FFloatMatrix({{6.f, 10.f, 12.f}, {5.f, 4.f, 1.f}});
		FFloatMatrix ExpectedResult1 = FFloatMatrix({{11.f, 14.f, 13.f}});
		FFloatMatrix ExpectedResult2 = FFloatMatrix({{28.f}, {10.f}});
		
		// Tests
		TestEqual(TEXT("Testing Sum"), Mat1.Sum()(0,0), 38.f);
		TestEqual(TEXT("Testing Sum: Axis=-1"), Mat1.Sum(-1)(0,0), 38.f);
		TestEqual(TEXT("Testing Sum: Axis=0"), Mat1.Sum(0), ExpectedResult1);
		TestEqual(TEXT("Testing Sum: Axis=1"), Mat1.Sum(1), ExpectedResult2);
	}
	
	// All tests passed!
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS