#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
  } else {
    result->matrix = NULL;
    ret = 1;
  }

  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = 0;
  int check_eq = 0;
  if (error_matrix(A) == 1 || error_matrix(B) == 1)
    ret = 0;
  else {
    if (A->columns == B->columns && A->rows == B->rows) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) <= EPS) check_eq++;
        }
      }
      if (check_eq == A->columns * A->rows) ret = SUCCESS;
    }
  }
  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (error_matrix(A) == 1 || error_matrix(B) == 1)
    ret = 1;
  else if (A->rows != B->rows || A->columns != B->columns)
    ret = 2;
  if (ret == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    if (result->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    } else {
      ret = 1;
    }
  } else
    result->matrix = NULL;
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (error_matrix(A) == 1 || error_matrix(B) == 1)
    ret = 1;
  else if (A->rows != B->rows || A->columns != B->columns)
    ret = 2;
  if (ret == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    if (result->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    } else {
      ret = 1;
    }
  } else
    result->matrix = NULL;
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 0;
  if (error_matrix(A) == 1) ret = 1;
  if (ret == 0) {
    if (s21_create_matrix(A->rows, A->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] * number;
      }
    } else {
      ret = 1;
    }
  } else
    result->matrix = NULL;
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (error_matrix(A) == 1 || error_matrix(B) == 1)
    ret = 1;
  else if (A->columns != B->rows)
    ret = 2;
  if (ret == 0) {
    if (s21_create_matrix(A->rows, B->columns, result) == 0) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  } else
    result->matrix = NULL;
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (error_matrix(A) == 1) ret = 1;
  if (ret == 0) {
    if (s21_create_matrix(A->columns, A->rows, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else
    result->matrix = NULL;
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  matrix_t temp = {0};

  if (error_matrix(A) == 1)
    ret = 1;
  else if (A->columns == 1 && A->rows == 1 && ret == 0) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = A->matrix[0][0];
  } else if (A->columns == A->rows && A->rows > 1) {
    if (s21_create_matrix(A->rows, A->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          copy_matrix_for_minor(A, &temp, i, j);
          result->matrix[i][j] = pow(-1, i + j) * minM(&temp);
          s21_remove_matrix(&temp);
        }
      }
    }
  } else {
    result->matrix = NULL;
    ret = 2;
  }
  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = 0;
  double det = 0;
  *result = 0;
  matrix_t temp = {0};
  if (error_matrix(A) == 1)
    ret = 1;
  else if (A->columns == A->rows && ret == 0) {
    if (A->columns == 1 && A->rows == 1)
      *result = A->matrix[0][0];
    else {
      s21_calc_complements(A, &temp);
      for (int i = 0; i < A->rows; i++)
        det += A->matrix[0][i] * temp.matrix[0][i];
      *result = det;
      s21_remove_matrix(&temp);
    }

  } else
    ret = 2;
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double det = 0;
  int ret = 0;
  matrix_t trans = {0};
  matrix_t compl = {0};
  if (error_matrix(A) == 1)
    ret = 1;
  else if (A->columns == A->rows && ret == 0) {
    ret = s21_determinant(A, &det);
    if (det == 0)
      ret = 2;
    else if (ret == 0) {
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        s21_transpose(A, &trans);
        s21_calc_complements(&trans, &compl );
        for (int i = 0; i < compl .rows; i++) {
          for (int j = 0; j < compl .columns; j++) {
            result->matrix[i][j] = compl .matrix[i][j] / det;
          }
        }
      }
    }
  } else {
    ret = 2;
    result->matrix = NULL;
  }
  s21_remove_matrix(&trans);
  s21_remove_matrix(&compl );
  return ret;
}

void copy_matrix_for_minor(matrix_t *A, matrix_t *temp, int r, int c) {
  s21_create_matrix(A->rows - 1, A->columns - 1, temp);
  int s = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != r) {
      int t = 0;
      for (int j = 0; j < A->rows; j++) {
        if (j != c) {
          temp->matrix[s][t] = A->matrix[i][j];
          t++;
        }
      }
      s++;
    }
  }
}

double minM(matrix_t *A) {
  double ret = 0;
  matrix_t temp = {0};
  if (A->columns == 1 && A->rows == 1)
    ret = A->matrix[0][0];
  else if (A->columns == 2 && A->rows == 2)
    ret = det_2_A(*A);
  else if (A->columns > 2 && A->rows > 2) {
    for (int k = 0; k < A->columns; k++) {
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &temp) == 0) {
        for (int i = 1; i < A->rows; i++) {
          int t = 0;
          for (int j = 0; j < A->rows; j++) {
            if (j != k) {
              temp.matrix[i - 1][t] = A->matrix[i][j];
              t++;
            }
          }
        }
        ret += pow(-1, k + 2) * A->matrix[0][k] * minM(&temp);
        s21_remove_matrix(&temp);
      }
    }
  }

  return ret;
}

double det_2_A(matrix_t a) {
  double ret = 0;
  if (a.columns == 2 && a.rows == 2) {
    ret = a.matrix[0][0] * a.matrix[1][1] - a.matrix[0][1] * a.matrix[1][0];
  }
  return ret;
}

int error_matrix(matrix_t *a) {
  int ret = 0;
  if (a == NULL || a->matrix == NULL || a->columns < 1 || a->rows < 1) ret = 1;
  return ret;
}
