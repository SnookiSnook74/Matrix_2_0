#ifndef S21_MATRIX_EXCEPTION_H
#define S21_MATRIX_EXCEPTION_H

#include <stdexcept>

#include "s21_matrix_oop.h"
class S21MatrixException {
 public:
  static void CheckRange(int row, int col, int maxRow, int maxCol) {
    if (row < 0 || row >= maxRow || col < 0 || col >= maxCol) {
      throw std::out_of_range("Index out of range");
    }
  }

  static void CheckDimensions(const S21Matrix& a, const S21Matrix& b) {
    if (a.GetRows() != b.GetRows() || a.GetCols() != b.GetCols()) {
      throw std::invalid_argument("Matrix sizes do not match");
    }
  }

  static void CheckMultiplication(const S21Matrix& a, const S21Matrix& b) {
    if (a.GetCols() != b.GetRows()) {
      throw std::invalid_argument(
          "Number of columns of the first matrix must equal the number of rows "
          "of the second matrix for multiplication.");
    }
  }

  static void CheckSquare(int rows, int cols) {
    if (rows != cols) {
      throw std::invalid_argument(
          "Matrix must be square to compute the determinant.");
    }
  }

  static void CheckSingular(double det) {
    if (std::abs(det) < 1e-6) {
      throw std::runtime_error("Matrix is singular, inverse does not exist.");
    }
  }

  static void CheckRows(int rows) {
    if (rows <= 0) {
      throw std::invalid_argument("Number of rows must be greater than zero");
    }
  }

  static void CheckCols(int cols) {
    if (cols <= 0) {
      throw std::invalid_argument(
          "Number of columns must be greater than zero");
    }
  }
};

#endif
