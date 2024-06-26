#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>

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
            std::cout << A[i + j * matrix_dim] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void matrix_multiply(int *A, int *B, int *C, size_t matrix_dim)
{
    for (size_t i = 0; i < matrix_dim; i++)
    {
        for (size_t j = 0; j < matrix_dim; j++)
        {
            for (size_t k = 0; k < matrix_dim; k++)
            {
                C[i + j * matrix_dim] += B[i + k * matrix_dim] * A[k + j * matrix_dim];
            }
        }
    }
}

int main(int argc, char **argv)
{

    srand(time(NULL));

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <matrix-dimension>" << std::endl;
        return -1;
    }

    size_t matrix_dim = atoi(argv[1]);
    if ((matrix_dim & (matrix_dim - 1)) != 0)
    {
        std::cout << "Matrix dimension must be a power of 2" << std::endl;
        return -1;
    }

    int *A = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));
    int *B = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));
    int *C = (int *)malloc(matrix_dim * matrix_dim * sizeof(int));

    initalize_matrix(A, matrix_dim);
    initalize_matrix(B, matrix_dim);
    memset(C, 0, matrix_dim * matrix_dim * sizeof(int));

    matrix_multiply(A, B, C, matrix_dim);
}