#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500  

void matrixMultiplyParallel(double A[N][N], double B[N][N], double C[N][N]) {
    int i, j, k;

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0.0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    static double A[N][N], B[N][N], C[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    double start = omp_get_wtime();

    matrixMultiplyParallel(A, B, C);

    double end = omp_get_wtime();
    printf("Time taken: %f seconds\n", end - start);
    /*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }
    */

    return 0;
}



// gcc -fopenmp matrix_mult.c -o matrix_mult
./matrix_mult
