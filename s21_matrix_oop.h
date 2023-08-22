#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  // Копирование
  S21Matrix(const S21Matrix& other);
  // Перенос
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // Сеттеры и Геттеры
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // Основные операции
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix Minor(int row, int col) const;
  S21Matrix InverseMatrix() const;
  S21Matrix Transpose();

  // Перегрузка методов
  double& operator()(int row, int col) const;
  double& operator()(int row, int col);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(double num);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  friend S21Matrix operator*(int scalar, const S21Matrix& matrix);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void CreateMatrix();
  void RemoveMatrix();
};

#endif
