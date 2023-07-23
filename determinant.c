#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
void input(double **matrix, int *n);
void output(double det);

int main()
{
    int n;
    double **matrix;
    double determinant;

    input(matrix, &n);
    determinant = det(matrix, n);

    if (determinant == 0) {
        printf("n/a\n");
    } else {
        output(determinant);
    }

    return 0;
}

double det(double **matrix, int n)
{
    int i, j, k;
    double det = 1;
    double temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (matrix[i][i] == 0) {
                int nonzero_row = i + 1;
                while (nonzero_row < n && matrix[nonzero_row][i] == 0) {
                    nonzero_row++;
                }
                if (nonzero_row == n) {
                    return 0;  // Matrix is singular
                }
                for (k = i; k < n; k++) {
                    temp = matrix[i][k];
                    matrix[i][k] = matrix[nonzero_row][k];
                    matrix[nonzero_row][k] = temp;
                }
                det *= -1;  // Swap rows changes determinant sign
            }

            temp = matrix[j][i] / matrix[i][i];
            for (k = i; k < n; k++) {
                matrix[j][k] -= temp * matrix[i][k];
            }
        }
        det *= matrix[i][i];
    }

    return det;
}

void input(double **matrix, int *n)
{
    int i, j;

    printf("Enter the size of the square matrix: ");
    scanf("%d", n);

    matrix = (double **)malloc(*n * sizeof(double *));
    for (i = 0; i < *n; i++) {
        matrix[i] = (double *)malloc(*n * sizeof(double));
        printf("Enter elements for row %d: ", i + 1);
        for (j = 0; j < *n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void output(double det)
{
    printf("Determinant: %.6f\n", det);
}
