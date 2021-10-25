#include <math.h>
#include <stdio.h>
#define MATRIX_SIZE 32

float determinant(float[][MATRIX_SIZE], float);
void cofactor(float[][MATRIX_SIZE], float);
void transpose(float[][MATRIX_SIZE], float[][MATRIX_SIZE], float);
int main() {
  float a[MATRIX_SIZE][MATRIX_SIZE], k, d;
  int i, j;
  printf("Enter the order of the Matrix : ");
  scanf("%f", &k);
  printf("Enter the elements of %.0fX%.0f Matrix : \n", k, k);
  for (i = 0; i < k; i++) {
    for (j = 0; j < k; j++) {
      scanf("%f", &a[i][j]);
    }
  }
  d = determinant(a, k);
  if (d == 0)
    printf("\nInverse of Entered Matrix is not possible\n");
  else
    cofactor(a, k);
}

/*For calculating Determinant of the Matrix */
float determinant(float a[MATRIX_SIZE][MATRIX_SIZE], float k) {
  float s = 1, det = 0, b[MATRIX_SIZE][MATRIX_SIZE];
  int i, j, m, n, c;
  if (k == 1) {
    return (a[0][0]);
  } else {
    det = 0;
    for (c = 0; c < k; c++) {
      m = 0;
      n = 0;
      for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
          b[i][j] = 0;
          if (i != 0 && j != c) {
            b[m][n] = a[i][j];
            if (n < (k - 2))
              n++;
            else {
              n = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (a[0][c] * determinant(b, k - 1));
      s = -1 * s;
    }
  }

  return (det);
}

void cofactor(float num[MATRIX_SIZE][MATRIX_SIZE], float f) {
  float b[MATRIX_SIZE][MATRIX_SIZE], fac[MATRIX_SIZE][MATRIX_SIZE];
  int p, q, m, n, i, j;
  for (q = 0; q < f; q++) {
    for (p = 0; p < f; p++) {
      m = 0;
      n = 0;
      for (i = 0; i < f; i++) {
        for (j = 0; j < f; j++) {
          if (i != q && j != p) {
            b[m][n] = num[i][j];
            if (n < (f - 2))
              n++;
            else {
              n = 0;
              m++;
            }
          }
        }
      }
      int t = -1;
      if ((q + p) % 2 == 0)
        t = 1;
      fac[q][p] = t * determinant(b, f - 1);
    }
  }
  transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[MATRIX_SIZE][MATRIX_SIZE],
               float fac[MATRIX_SIZE][MATRIX_SIZE], float r) {
  int i, j;
  float b[MATRIX_SIZE][MATRIX_SIZE], inverse[MATRIX_SIZE][MATRIX_SIZE], d;

  for (i = 0; i < r; i++) {
    for (j = 0; j < r; j++) {
      b[i][j] = fac[j][i];
    }
  }
  d = determinant(num, r);
  for (i = 0; i < r; i++) {
    for (j = 0; j < r; j++) {
      inverse[i][j] = b[i][j] / d;
    }
  }
  printf("\n\n\nThe inverse of matrix is : \n");

  for (i = 0; i < r; i++) {
    for (j = 0; j < r; j++) {
      printf("\t%f", inverse[i][j]);
    }
    printf("\n");
  }
}