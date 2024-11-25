#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }

  void setRows(int newRows) {
    if (newRows != rows_) {
      double** newMatrix = new double*[newRows];
      for (int i = 0; i < newRows; i++) {
        newMatrix[i] = new double[cols_]();
        if (i < rows_) {
          for (int j = 0; j < cols_; j++) {
            newMatrix[i][j] = matrix_[i][j];
          }
        }
      }
      delete matrix_;
      matrix_ = newMatrix;
      rows_ = newRows;
    }
  }

  void setCols(int newCols) {
    if (newCols != cols_) {
      for (int i = 0; i < rows_; i++) {
        double* newRows = new double[newCols]();
        for (int j = 0; j < newCols; j++) {
          if (j < cols_) {
            newRows[j] = matrix_[i][j];
          }
        }
        delete[] matrix_[i];
        matrix_[i] = newRows;
      }
      cols_ = newCols;
    }
  }

  double& operator()(int i, int j);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;

  S21Matrix operator*(S21Matrix& other);
  S21Matrix operator+(S21Matrix& other);
  S21Matrix operator-(S21Matrix& other);

  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  bool EqMatrix(const S21Matrix& other) const;
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CreateMinor(int row, int col) const;
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();

  void Print();
};
