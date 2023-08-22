#include <gtest/gtest.h>

#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

// Тесты для GetRows и GetCols
TEST(S21MatrixTest, GetRows_GetCols) {
  int rows = 4;
  int cols = 5;
  S21Matrix matrix(rows, cols);

  EXPECT_EQ(matrix.GetRows(), rows);
  EXPECT_EQ(matrix.GetCols(), cols);
}
// Тесты для конструкторов
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, SetRowsIncrease) {
  S21Matrix matrix(3, 3);
  matrix.SetRows(5);
  EXPECT_EQ(matrix.GetRows(), 5);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, SetRowsDecrease) {
  S21Matrix matrix(5, 3);
  matrix.SetRows(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, SetColsIncrease) {
  S21Matrix matrix(3, 3);
  matrix.SetCols(5);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 5);
}

TEST(S21MatrixTest, SetColsDecrease) {
  S21Matrix matrix(3, 5);
  matrix.SetCols(3);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, ParameterizedConstructor) {
  int rows = 4;
  int cols = 5;
  S21Matrix matrix(rows, cols);

  EXPECT_EQ(matrix.GetRows(), rows);
  EXPECT_EQ(matrix.GetCols(), cols);
}

TEST(S21MatrixTest, MoveConstructor) {
  // Создание исходной матрицы
  S21Matrix originalMatrix(2, 2);
  originalMatrix(0, 0) = 1.0;
  originalMatrix(0, 1) = 2.0;
  originalMatrix(1, 0) = 3.0;
  originalMatrix(1, 1) = 4.0;
  // Запомним размеры исходной матрицы
  int originalRows = originalMatrix.GetRows();
  int originalCols = originalMatrix.GetCols();
  // Создание матрицы с использованием конструктора перемещения
  S21Matrix movedMatrix(std::move(originalMatrix));
  // Проверка, что размеры перемещенной матрицы совпадают с исходными
  EXPECT_EQ(movedMatrix.GetRows(), originalRows);
  EXPECT_EQ(movedMatrix.GetCols(), originalCols);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix originalMatrix(2, 2);
  originalMatrix(0, 0) = 1.0;
  originalMatrix(0, 1) = 2.0;
  originalMatrix(1, 0) = 3.0;
  originalMatrix(1, 1) = 4.0;

  // Создание копии с использованием конструктора копирования
  S21Matrix copiedMatrix(originalMatrix);
  // Проверка размеров
  EXPECT_EQ(copiedMatrix.GetRows(), originalMatrix.GetRows());
  EXPECT_EQ(copiedMatrix.GetCols(), originalMatrix.GetCols());
  // Проверка значений элементов
  for (int i = 0; i < originalMatrix.GetRows(); ++i) {
    for (int j = 0; j < originalMatrix.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(copiedMatrix(i, j), originalMatrix(i, j));
    }
  }
}

TEST(EqMatrixTest, EqualMatrices) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrixTest, DifferentSizeMatrices) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrixTest, DifferentValueMatrices) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;  // Изменяем значение элемента, чтобы матрицы отличались

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, SumMatrix_SameSize) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(S21MatrixTest, SumMatrix_DifferentSize) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  // Попытка сложить матрицы разного размера должна вызвать исключение
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTest, SubMatrix_SameSize) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 8.0;

  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 4.0);
}

TEST(S21MatrixTest, SubMatrix_DifferentSize) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

// Тесты для MulNumber

TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(S21MatrixTest, MulMatrix_ValidSize) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 154.0);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix originalMatrix(2, 3);
  originalMatrix(0, 0) = 1.0;
  originalMatrix(0, 1) = 2.0;
  originalMatrix(0, 2) = 3.0;
  originalMatrix(1, 0) = 4.0;
  originalMatrix(1, 1) = 5.0;
  originalMatrix(1, 2) = 6.0;

  S21Matrix transposedMatrix = originalMatrix.Transpose();

  // Проверка размеров транспонированной матрицы
  EXPECT_EQ(transposedMatrix.GetRows(), 3);
  EXPECT_EQ(transposedMatrix.GetCols(), 2);

  // Проверка значений транспонированной матрицы
  EXPECT_DOUBLE_EQ(transposedMatrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(transposedMatrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(transposedMatrix(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(transposedMatrix(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(transposedMatrix(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(transposedMatrix(2, 1), 6.0);
}

TEST(S21MatrixTest, Minor) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix minor = matrix.Minor(1, 1);

  EXPECT_DOUBLE_EQ(minor(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(minor(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(minor(1, 0), 7.0);
  EXPECT_DOUBLE_EQ(minor(1, 1), 9.0);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(0, 2) = 3.0;
  matrix2(1, 0) = 4.0;
  matrix2(1, 1) = 5.0;
  matrix2(1, 2) = 6.0;
  matrix2(2, 0) = 7.0;
  matrix2(2, 1) = 8.0;
  matrix2(2, 2) = 9.0;

  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
  EXPECT_DOUBLE_EQ(matrix2.Determinant(), 0.0);
}

TEST(S21MatrixTest, Determinant_NonSquareMatrix_ThrowsException) {
  S21Matrix nonSquareMatrix(2, 3);
  // Проверка, что выбрасывается исключение, если матрица не является квадратной
  EXPECT_THROW(nonSquareMatrix.Determinant(), std::invalid_argument);
}
TEST(S21MatrixTest, Determinant_OneByOneMatrix) {
  S21Matrix oneByOneMatrix(1, 1);
  oneByOneMatrix(0, 0) = 42.0;
  // Проверка, что определитель матрицы 1x1 равен единственному элементу матрицы
  EXPECT_DOUBLE_EQ(oneByOneMatrix.Determinant(), 42.0);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 3.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 2.0;

  S21Matrix inverse = matrix.InverseMatrix();

  // Проверка значений обратной матрицы
  EXPECT_DOUBLE_EQ(inverse(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(inverse(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(inverse(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(inverse(1, 1), -4.0);

  // Тест на выбрасывание исключения для сингулярной матрицы
  S21Matrix singularMatrix(2, 2);
  singularMatrix(0, 0) = 1.0;
  singularMatrix(0, 1) = 2.0;
  singularMatrix(1, 0) = 2.0;
  singularMatrix(1, 1) = 4.0;

  EXPECT_THROW(singularMatrix.InverseMatrix(), std::runtime_error);
}

TEST(S21MatrixTest, CalcComplements) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  // Вычисление матрицы дополнений
  S21Matrix complementsMatrix = matrix.CalcComplements();

  double expectedComplements[2][2] = {{4.0, -3.0}, {-2.0, 1.0}};

  // Проверка значений матрицы дополнений
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      EXPECT_DOUBLE_EQ(complementsMatrix(i, j), expectedComplements[i][j]);
    }
  }
}

TEST(S21MatrixTest, MulMatrix_InvalidSize) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  // Попытка умножить матрицы недопустимого размера должна вызвать исключение
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorAddition) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(S21MatrixTest, OperatorSubtraction) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 8.0;

  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

// Тест для умножения матрицы на число
TEST(S21MatrixTest, MultiplyByNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  double num = 2.0;
  S21Matrix result = matrix * num;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 2);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), 8);
}

// Тест для умножения матриц
TEST(S21MatrixTest, MultiplyMatrices) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.GetRows(), 2);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 19);
  EXPECT_EQ(result(0, 1), 22);
  EXPECT_EQ(result(1, 0), 43);
  EXPECT_EQ(result(1, 1), 50);
}

// Тест для проверки выхода за границы матрицы
TEST(S21MatrixTest, OutOfBoundsAccess) {
  S21Matrix matrix(3, 3);

  // Проверяем, что обращение к элементу за границами матрицы вызывает
  // исключение std::out_of_range
  EXPECT_THROW(matrix(3, 3), std::out_of_range);
}

// Тест для оператора присваивания
TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2;
  matrix2 = matrix1;

  EXPECT_EQ(matrix2.GetRows(), 2);
  EXPECT_EQ(matrix2.GetCols(), 2);
  EXPECT_EQ(matrix2(0, 0), 1);
  EXPECT_EQ(matrix2(0, 1), 2);
  EXPECT_EQ(matrix2(1, 0), 3);
  EXPECT_EQ(matrix2(1, 1), 4);
}

TEST(S21MatrixOperatorTests, AddAssignOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  matrix1 += matrix2;

  EXPECT_EQ(matrix1(0, 0), 6);
  EXPECT_EQ(matrix1(0, 1), 8);
  EXPECT_EQ(matrix1(1, 0), 10);
  EXPECT_EQ(matrix1(1, 1), 12);
}

TEST(S21MatrixOperatorTests, SubtractAssignOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 6;
  matrix1(1, 0) = 7;
  matrix1(1, 1) = 8;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1 -= matrix2;

  EXPECT_EQ(matrix1(0, 0), 4);
  EXPECT_EQ(matrix1(0, 1), 4);
  EXPECT_EQ(matrix1(1, 0), 4);
  EXPECT_EQ(matrix1(1, 1), 4);
}

TEST(S21MatrixOperatorTests, MultiplyAssignMatrixOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1(0, 0), 19);
  EXPECT_EQ(matrix1(0, 1), 22);
  EXPECT_EQ(matrix1(1, 0), 43);
  EXPECT_EQ(matrix1(1, 1), 50);
}

TEST(S21MatrixOperatorTests, MultiplyAssignNumberOperator) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix *= 2.0;

  EXPECT_EQ(matrix(0, 0), 2);
  EXPECT_EQ(matrix(0, 1), 4);
  EXPECT_EQ(matrix(1, 0), 6);
  EXPECT_EQ(matrix(1, 1), 8);
}

TEST(S21MatrixOperatorTests, EqualityOperator) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 5;
  matrix3(0, 1) = 6;
  matrix3(1, 0) = 7;
  matrix3(1, 1) = 8;

  // Проверяем равенство двух идентичных матриц
  EXPECT_TRUE(matrix1 == matrix2);

  // Проверяем неравенство двух разных матриц
  EXPECT_FALSE(matrix1 == matrix3);
}