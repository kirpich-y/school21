#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, SumMatrix1) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix.SumMatrix(matrix1);
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, SumMatrix2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix += matrix1;
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, SumMatrix3) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  S21Matrix m = matrix + matrix1;
  EXPECT_EQ(m, matrix2);
}

TEST(S21MatrixTest, SumMatrix4) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 2.0;

  EXPECT_THROW(matrix.SumMatrix(matrix1), std::invalid_argument);
}

TEST(S21MatrixTest, SubMatrix1) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 5.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 7.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix.SubMatrix(matrix1);
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, SubMatrix2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 5.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 7.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix -= matrix1;
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, SubMatrix3) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 5.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 7.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 1.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 3.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  S21Matrix m = matrix - matrix1;
  EXPECT_EQ(m, matrix2);
}

TEST(S21MatrixTest, SubMatrix4) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 2.0;

  EXPECT_THROW(matrix.SubMatrix(matrix1), std::invalid_argument);
}

TEST(S21MatrixTest, MulMatrix1) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 11.0;
  matrix2(1, 1) = 10.0;

  matrix.MulMatrix(matrix1);
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, MulMatrix2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 11.0;
  matrix2(1, 1) = 10.0;

  matrix *= matrix1;
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, MulMatrix3) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 11.0;
  matrix2(1, 1) = 10.0;

  S21Matrix m = matrix * matrix1;
  EXPECT_EQ(m, matrix2);
}

TEST(S21MatrixTest, MulMatrix4) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 2.0;

  EXPECT_THROW(matrix.MulMatrix(matrix1), std::invalid_argument);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 10.0;
  matrix2(0, 1) = 5.0;
  matrix2(1, 0) = 10.0;
  matrix2(1, 1) = 15.0;

  matrix.MulNumber(5.0);
  EXPECT_EQ(matrix, matrix2);
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 3.0;

  matrix1 = matrix.Transpose();
  EXPECT_EQ(matrix1, matrix2);
}

TEST(S21MatrixTest, CreateMinor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1;

  S21Matrix matrix2(1, 1);
  matrix2(0, 0) = 3.0;

  matrix1 = matrix.CreateMinor(0, 0);
  EXPECT_EQ(matrix1, matrix2);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  double det = 4;

  double chislo = matrix.Determinant();
  EXPECT_EQ(chislo, det);
}

TEST(S21MatrixTest, Determinant2) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(0, 2) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 1.0;
  matrix(2, 0) = 1.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = 3.0;

  double det = 10;

  double chislo = matrix.Determinant();
  EXPECT_EQ(chislo, det);
}

TEST(S21MatrixTest, Determinant3) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(0, 2) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 1.0;

  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

TEST(S21MatrixTest, InverseMatrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 3.0;
  matrix(0, 1) = 4.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = -4.0;
  matrix2(1, 0) = -2.0;
  matrix2(1, 1) = 3.0;

  matrix1 = matrix.InverseMatrix();
  EXPECT_EQ(matrix1, matrix2);
}

TEST(S21MatrixTest, Move) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 3.0;
  matrix(0, 1) = 4.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1 = std::move(matrix);

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 3.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 3.0;

  EXPECT_EQ(matrix1, matrix2);
}

TEST(S21MatrixTest, InverseMatrix2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1;

  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, CalcComplements) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 2.0;
  matrix1(2, 0) = 3.0;
  matrix1(2, 1) = 2.0;

  EXPECT_THROW(matrix1.CalcComplements(), std::invalid_argument);
}

TEST(S21MatrixTest, override_op) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 1.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 3.0;

  EXPECT_THROW(matrix(3, 5), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}