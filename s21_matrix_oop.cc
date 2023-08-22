#include "s21_matrix_oop.h"

#include <iostream>
#include <stdexcept>

#include "s21_matrix_exception.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) { CreateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}


S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  S21MatrixException::CheckRows(rows);
  S21Matrix resultMatrix(rows, cols_);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[i][j] = i < rows_ ? matrix_[i][j] : 0.0;
    }
  }
  *this = std::move(resultMatrix);
}

void S21Matrix::SetCols(int cols) {
  S21MatrixException::CheckCols(cols);
  S21Matrix resultMatrix(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      resultMatrix.matrix_[i][j] = j < cols_ ? matrix_[i][j] : 0.0;
    }
  }
  *this = std::move(resultMatrix);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool areEqual = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    areEqual = false;
  } else {
    for (int i = 0; areEqual && i < rows_; ++i) {
      for (int j = 0; areEqual && j < cols_; ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          areEqual = false;
        }
      }
    }
  }
  return areEqual;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  S21MatrixException::CheckDimensions(*this, other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  S21MatrixException::CheckDimensions(*this, other);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  S21MatrixException::CheckMultiplication(*this, other);
  S21Matrix resultMatrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      resultMatrix.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; ++k) {
        resultMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(resultMatrix);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix resultMatrix(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return resultMatrix;
}

S21Matrix S21Matrix::Minor(int row, int col) const {
  S21Matrix minorMatrix(rows_ - 1, cols_ - 1);
  int minorRow = 0;
  for (int i = 0; i < rows_; ++i) {
    if (i == row) continue;
    int minorCol = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) continue;
      minorMatrix.matrix_[minorRow][minorCol] = matrix_[i][j];
      minorCol++;
    }
    minorRow++;
  }
  return minorMatrix;
}

double S21Matrix::Determinant() const {
  S21MatrixException::CheckSquare(rows_, cols_);
  double result = 0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; ++i) {
      double sign = (i % 2 == 0) ? 1 : -1;
      result += sign * matrix_[0][i] * Minor(0, i).Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21MatrixException::CheckSquare(rows_, cols_);
  S21Matrix complementsMatrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      double sign = ((i + j) % 2 == 0) ? 1 : -1;
      complementsMatrix.matrix_[i][j] = sign * Minor(i, j).Determinant();
    }
  }
  return complementsMatrix;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  S21MatrixException::CheckSingular(det);
  S21Matrix complementsMatrix = CalcComplements();
  S21Matrix transposedComplements = complementsMatrix.Transpose();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transposedComplements.matrix_[i][j] /= det;
    }
  }
  return transposedComplements;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmpMatirx(*this);
  tmpMatirx.SumMatrix(other);
  return tmpMatirx;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmpMatirx(*this);
  tmpMatirx.SubMatrix(other);
  return tmpMatirx;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tmpMatrix(*this);
  tmpMatrix.MulNumber(num);
  return tmpMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmpMatrix(*this);
  tmpMatrix.MulMatrix(other);
  return tmpMatrix;
}

S21Matrix operator*(int scalar, const S21Matrix& matrix) {
    S21Matrix result(matrix.GetRows(), matrix.GetCols());
    for (int i = 0; i < matrix.GetRows(); ++i) {
        for (int j = 0; j < matrix.GetCols(); ++j) {
            result(i, j) = scalar * matrix(i, j);
        }
    }
    return result;
}


double& S21Matrix::operator()(int row, int col) const {
  S21MatrixException::CheckRange(row, col, rows_, cols_);
  return matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col){
  S21MatrixException::CheckRange(row, col, rows_, cols_);
  return matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

// Перемещение
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    RemoveMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
// Копирование
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix tmpMatrix(other);
    *this = std::move(tmpMatrix);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

void S21Matrix::CreateMatrix() {
  S21MatrixException::CheckCols(cols_);
  S21MatrixException::CheckRows(rows_);
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 2.0;
    }
  }
}

void S21Matrix::RemoveMatrix() {
  // Проверка, что указатель не равен nullptr
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

