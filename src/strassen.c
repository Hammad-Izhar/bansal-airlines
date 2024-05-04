#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

void initalize_matrix(int *A, size_t matrix_dim)
{
    for (size_t i = 0; i < matrix_dim; i++)
        for (size_t j = 0; j < matrix_dim; j++)
            A[i + j * matrix_dim] = rand() % 100;
}

void print_matrix(int *A, size_t matrix_dim)
{
    for (size_t j = 0; j < matrix_dim; j++)
    {
        for (size_t i = 0; i < matrix_dim; i++)
        {
            printf("%d ", A[i + j * matrix_dim]);
        }
        printf("\n");
    }
    printf("\n");
}

int *matrix_add(int *A, int *B, size_t matrix_dim, size_t row_start_A, size_t col_start_A, size_t row_start_B, size_t col_start_B, bool subtract)
{
    int *C = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));

    for (size_t i = 0; i < matrix_dim; i++)
    {
        for (size_t j = 0; j < matrix_dim; j++)
        {
            int iA = col_start_A + i;
            int jA = row_start_A + j;
            int iB = col_start_B + i;
            int jB = row_start_B + j;

            C[i + j * matrix_dim] = A[iA + jA * matrix_dim * 2] + B[iB + jB * matrix_dim * 2] * (subtract ? -1 : 1);
        }
    }

    return C;
}

int *matrix_multiply(int *A, int *B, size_t dimOut)
{
    if (dimOut == 2)
    {
        int *C = (int *)malloc(4 * sizeof(int));
        C[0] = A[0] * B[0] + A[1] * B[2];
        C[1] = A[0] * B[1] + A[1] * B[3];
        C[2] = A[2] * B[0] + A[3] * B[2];
        C[3] = A[2] * B[1] + A[3] * B[3];
        return C;
    }

    int *zeros = (int *)malloc(dimOut * dimOut * sizeof(int));
    memset(zeros, 0, dimOut * dimOut * sizeof(int));

    int *A11 = matrix_add(A, zeros, dimOut / 2, 0, 0, 0, 0, false);
    int *A22 = matrix_add(A, zeros, dimOut / 2, dimOut / 2, dimOut / 2, dimOut / 2, dimOut / 2, false);
    int *B11 = matrix_add(B, zeros, dimOut / 2, 0, 0, 0, 0, false);
    int *B22 = matrix_add(B, zeros, dimOut / 2, dimOut / 2, dimOut / 2, dimOut / 2, dimOut / 2, false);

    int *A11pA22 = matrix_add(A, A, dimOut / 2, 0, 0, dimOut / 2, dimOut / 2, false);
    int *B11pB22 = matrix_add(B, B, dimOut / 2, 0, 0, dimOut / 2, dimOut / 2, false);
    int *A21pA22 = matrix_add(A, A, dimOut / 2, dimOut / 2, 0, dimOut / 2, dimOut / 2, false);
    int *B12sB22 = matrix_add(B, B, dimOut / 2, 0, dimOut / 2, dimOut / 2, dimOut / 2, true);
    int *B21sB11 = matrix_add(B, B, dimOut / 2, dimOut / 2, 0, 0, 0, true);
    int *A11pA12 = matrix_add(A, A, dimOut / 2, 0, 0, 0, dimOut / 2, false);
    int *A21sA11 = matrix_add(A, A, dimOut / 2, dimOut / 2, 0, 0, 0, true);
    int *B11pB12 = matrix_add(B, B, dimOut / 2, 0, 0, 0, dimOut / 2, false);
    int *A12sA22 = matrix_add(A, A, dimOut / 2, 0, dimOut / 2, dimOut / 2, dimOut / 2, true);
    int *B21pB22 = matrix_add(B, B, dimOut / 2, dimOut / 2, 0, dimOut / 2, dimOut / 2, false);

    int *M1 = matrix_multiply(A11pA22, B11pB22, dimOut / 2);
    int *M2 = matrix_multiply(A21pA22, B11, dimOut / 2);
    int *M3 = matrix_multiply(A11, B12sB22, dimOut / 2);
    int *M4 = matrix_multiply(A22, B21sB11, dimOut / 2);
    int *M5 = matrix_multiply(A11pA12, B22, dimOut / 2);
    int *M6 = matrix_multiply(A21sA11, B11pB12, dimOut / 2);
    int *M7 = matrix_multiply(A12sA22, B21pB22, dimOut / 2);

    int *C = (int *)malloc(dimOut * dimOut * sizeof(int));

    for (size_t i = 0; i < dimOut / 2; i++)
    {
        for (size_t j = 0; j < dimOut / 2; j++)
        {
            C[i + j * dimOut] = M1[i + j * dimOut / 2] + M4[i + j * dimOut / 2] - M5[i + j * dimOut / 2] + M7[i + j * dimOut / 2];
            C[i + dimOut / 2 + j * dimOut] = M3[i + j * dimOut / 2] + M5[i + j * dimOut / 2];
            C[i + (j + dimOut / 2) * dimOut] = M2[i + j * dimOut / 2] + M4[i + j * dimOut / 2];
            C[i + dimOut / 2 + (j + dimOut / 2) * dimOut] = M1[i + j * dimOut / 2] - M2[i + j * dimOut / 2] + M3[i + j * dimOut / 2] + M6[i + j * dimOut / 2];
        }
    }

    free(A11pA22);
    free(B11pB22);
    free(A21pA22);
    free(B12sB22);
    free(B21sB11);
    free(A11pA12);
    free(A21sA11);
    free(B11pB12);
    free(A12sA22);
    free(B21pB22);
    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);

    return C;
}

int main(int argc, char **argv)
{

    srand(time(NULL));

    if (argc < 2)
    {
        printf("Usage: %s <matrix-dimension>\n", argv[0]);
        return -1;
    }

    size_t matrix_dim = atoi(argv[1]);
    if ((matrix_dim & (matrix_dim - 1)) != 0)
    {
        printf("Matrix dimension must be a power of 2\n");
        return -1;
    }

    int *A = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));
    int *B = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));

    initalize_matrix(A, matrix_dim);
    initalize_matrix(B, matrix_dim);

    matrix_multiply(A, B, matrix_dim);
}