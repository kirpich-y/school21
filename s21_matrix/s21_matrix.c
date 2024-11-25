
#include "s21_matrix.h"
// int rows; строки
// int columns; столбцы
// первый индекс - номер строки, второй - номер столбца

//Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;

  if (rows >= 1 &&
      columns >=
          1) {  // избежать создания матрицы нулевого или отрицательного размера
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  } else {
    error = INCORRENTLY;  // некорректная матрица
  }

  return error;
}

// Очистка матриц
void s21_remove_matrix(matrix_t *const A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

//  сравнение матриц

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (!A->matrix || !B->matrix || A->columns != B->columns ||
      A->rows != B->rows) {
    error = FAILURE;
  } else {
    float tmp1 = 0, tmp2 = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp1 = A->matrix[i][j];
        tmp2 = B->matrix[i][j];  // i - номер строки результата, j - номер
                                 // столбца результата
        if (tmp1 != tmp2) {
          i = A->rows;
          j = A->columns;
          error = FAILURE;  // ошибка вычисления
        }
      }
    }
  }

  return error;
}
// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!A->matrix || !B->matrix) {
    error = INCORRENTLY;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    error = CALC_ERROR;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] =
            A->matrix[i][j] + B->matrix[i][j];  // i - номер строки результата,
                                                // j - номер столбца результата
      }
    }
  }
  return error;  // гуд
}
// вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!A->matrix || !B->matrix) {
    error = INCORRENTLY;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    error = CALC_ERROR;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] =
            A->matrix[i][j] - B->matrix[i][j];  // i - номер строки результата,
                                                // j - номер столбца результата
      }
    }
  }
  return error;
}
// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (!A->matrix) {
    error = INCORRENTLY;  // некорректнаяя матрица
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (!result->matrix) {
      error = INCORRENTLY;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return error;
}
// Умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  error = s21_create_matrix(A->rows, B->columns, result);
  if (!A->matrix || !B->matrix || !result->matrix) {
    error = INCORRENTLY;
  } else if (A->columns != B->rows) {  // количество столбцов матрицы A равно
                                       // количеству строк матрицы B
    error = CALC_ERROR;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns;
             k++) {  // k - номер столбца матрицы A (соответствует номеру строки
                     // матрицы B)
          result->matrix[i][j] +=
              A->matrix[i][k] *
              B->matrix[k][j];  // i - номер строки результата, j - номер
                                // столбца результата,
        }
      }
    }
  }
  return error;
}
// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!A->matrix) {
    error = INCORRENTLY;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);
    if (!result->matrix) {
      error = INCORRENTLY;
    } else {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return error;
}
// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = s21_create_matrix(A->rows, A->columns, result);

  if (!A->matrix || !result->matrix) {
    error = INCORRENTLY;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else if (A->rows == 1) {
    result->matrix[0][0] = A->matrix[0][0];
  } else {
    matrix_t minor_matrix = {0};
    double determinant = 0.0;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        create_minor(A, &minor_matrix, i, j);
        error = s21_determinant(&minor_matrix, &determinant);
        result->matrix[i][j] = pow(-1, i + j) * determinant;
      }
    }
    s21_remove_matrix(&minor_matrix);
  }

  return error;
}

//  exception_row ряд, в котором стоит данный элемент.
//  exception_column столбец, в котором стоит данный элемент.

// создание минор матрицы, исключая выбранные строки и столбцы
void create_minor(matrix_t *A, matrix_t *result, int exception_row,
                  int exception_column) {
  for (int i = 0, m = 0, k = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i != exception_row && j != exception_column) {
        result->matrix[m][k] = A->matrix[i][j];
        if (k == result->columns - 1) {
          m++;
          k = 0;
        } else {
          k++;  // обеспечивает правильное заполнение матрицы миноров в виде
                // прямоугольника
        }
      }
    }
  }
}
// Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int error = OK;

  if (!A->matrix)
    error = INCORRENTLY;
  else if (A->rows != A->columns)
    error = CALC_ERROR;
  else if (A->rows == 1)
    *result = A->matrix[0][0];
  else {
    *result = 1;
    matrix_t triangle = {0};
    error = s21_create_matrix(A->rows, A->columns, &triangle);

    for (int i = 0; i < triangle.rows && error == OK;
         i++)  // переносим матрицу в треугольную матрицу
      for (int j = 0; j < triangle.columns; j++)
        triangle.matrix[i][j] = A->matrix[i][j];

    for (int i = 0; i < triangle.rows && error == OK; i++) {  //
      int hook = i;
      for (int j = i + 1; j < triangle.rows; j++)
        if (triangle.matrix[j][i] > triangle.matrix[hook][i]) hook = j;
      if (hook != i) {  // если элемент не самый большой в столбике, то ищем
                        // самый большой элемент столбика до главной диагоняли и
                        // домножаем на -1
        *result *= -1;
        for (int j = i; j < triangle.rows; j++) {
          double temp = triangle.matrix[i][j];
          triangle.matrix[i][j] = triangle.matrix[hook][j];
          triangle.matrix[hook][j] = temp;
        }
      }
      if (!triangle.matrix[i][i]) {
        *result = 0;
        i = triangle.rows;
      } else
        *result *= triangle.matrix[i][i];
      for (int j = i + 1; j < triangle.rows; j++) {
        double ratio = triangle.matrix[j][i] / triangle.matrix[i][i];
        for (int k = i; k < triangle.rows; k++) {
          triangle.matrix[j][k] -= ratio * triangle.matrix[i][k];
        }
      }
    }
    s21_remove_matrix(&triangle);
  }

  return error;
}
// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  // начилие матрицы
  if (A->matrix && A->rows == A->columns) {
    double determinant = 0;

    if (s21_determinant(A, &determinant) == OK &&
        determinant != 0) {  // получение определителя
      matrix_t temp_calc = {0}, temp_transpose = {0};

      s21_calc_complements(A, &temp_calc);  // генерация матрицы
      s21_transpose(&temp_calc, &temp_transpose);  // транспонирование матрицы
      error = s21_mult_number(
          &temp_transpose, 1 / determinant,
          result);  // умножение трансп матрицы на обратный определитель
      s21_remove_matrix(&temp_calc);
      s21_remove_matrix(&temp_transpose);
    } else
      error = CALC_ERROR;
  } else if (A->rows != A->columns)
    error = CALC_ERROR;
  else
    error = INCORRENTLY;

  return error;  // 0 правильно
}
