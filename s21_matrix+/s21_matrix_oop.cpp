#include "s21_matrix_oop.h"

#include <iostream>
#include <stdexcept>

// S21Matrix A;

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
};

// Создание матрицы
//  S21Matrix A (5, 5);
S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];

    std::fill(matrix_[i], matrix_[i] + cols_, 0.0);
  }
};

// Удаление матрицы
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
};

// Копирование матрицы
S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  // Копирование данных из другой матрицы в текущую
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

// Перенос матрицы
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = other.matrix_;

  // Удаляем старую матрицу, теперь она принадлежит новому объекту
  other.matrix_ = nullptr;

  // Сбрасываем размеры исходного объекта
  other.rows_ = 0;
  other.cols_ = 0;
};

// Индексация по элементам матрицы
double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("out of range");
  }

  return matrix_[i][j];
};

// Сложение
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("invalid argument");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
};

// Вычитание
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("invalid argument");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
};

// Умножение матрицы на матрицу
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("invalid argument");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
};

// Умножение матрицы на число
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
};

// Сравнение матриц
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) return false;
    }
  }
  return 1;
};

// Транспонирование матриц
S21Matrix S21Matrix::Transpose() {
  S21Matrix matr(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matr.matrix_[j][i] = matrix_[i][j];
    }
  }
  return matr;
};

// Минор
S21Matrix S21Matrix::CreateMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  int m_row = 0, m_col = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    m_col = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;
      minor.matrix_[m_row][m_col] = matrix_[i][j];
      m_col++;
    }
    m_row++;
  }
  return minor;
};

// Детерминант
double S21Matrix::Determinant() {
  double result = 0.0;
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не квадртаная");
  }
  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  for (int j = 0; j < cols_; j++) {
    S21Matrix minor = CreateMinor(0, j);
    double minor_det = minor.Determinant();
    result += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * minor_det;
  }
  return result;
};

// Вычислительные дополнения
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица не квадратная");
  }
  S21Matrix res(rows_, cols_);
  double minor_det = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = CreateMinor(i, j);
      minor_det = minor.Determinant();
      res.matrix_[i][j] = (i + j) % 2 == 0 ? minor_det : -minor_det;
    }
  }
  return res;
}

// Обратная матрица
S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0) {
    throw std::invalid_argument("Определитель матрицы равен нулю");
  }
  S21Matrix complements = this->CalcComplements();
  S21Matrix adjugate = complements.Transpose();

  S21Matrix res = adjugate;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] /= det;
    }
  }
  return res;
};

//=
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete matrix_;

    cols_ = other.cols_;
    rows_ = other.rows_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
};

//+=
void S21Matrix::operator+=(const S21Matrix& other) { this->SumMatrix(other); }

//-=
void S21Matrix::operator-=(const S21Matrix& other) { this->SubMatrix(other); };

//*=
void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); };

//==
bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
};

//*
S21Matrix S21Matrix::operator*(S21Matrix& other) {
  S21Matrix temp = *this;

  temp.MulMatrix(other);

  return temp;
};

//+
S21Matrix S21Matrix::operator+(S21Matrix& other) {
  S21Matrix temp = *this;

  temp.SumMatrix(other);

  return temp;
};

//-
S21Matrix S21Matrix::operator-(S21Matrix& other) {
  S21Matrix temp = *this;

  temp.SubMatrix(other);

  return temp;
};