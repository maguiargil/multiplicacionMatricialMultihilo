#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1500

void multiplyMatrices(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int **A, **B, **C;

    // Dynamic allocation of matrices
    A = (int **)malloc(SIZE * sizeof(int *));
    B = (int **)malloc(SIZE * sizeof(int *));
    C = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        A[i] = (int *)malloc(SIZE * sizeof(int));
        B[i] = (int *)malloc(SIZE * sizeof(int));
        C[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Initialize matrices A and B with some values (for example, 1)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    multiplyMatrices(A, B, C, SIZE);

    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - start.tv_sec) * 1000.0; // segundos a milisegundos
    elapsed += (end.tv_usec - start.tv_usec) / 1000.0; // microsegundos a milisegundos

    printf("Tiempo de ejecucion promedio: %f milisegundos\n", elapsed);

    // Clean up
    for (int i = 0; i < SIZE; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}