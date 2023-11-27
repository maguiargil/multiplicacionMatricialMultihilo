#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 1500
#define NUM_THREADS 20

int **A, **B, **C;

typedef struct {
    int start_row;
    int end_row;
} ThreadParam;

void *multiply(void *arg) {
    ThreadParam *param = (ThreadParam *)arg;
    int start = param->start_row;
    int end = param->end_row;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(0);
}

int main() {
    // Allocate memory
    A = (int **)malloc(SIZE * sizeof(int *));
    B = (int **)malloc(SIZE * sizeof(int *));
    C = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        A[i] = (int *)malloc(SIZE * sizeof(int));
        B[i] = (int *)malloc(SIZE * sizeof(int));
        C[i] = (int *)malloc(SIZE * sizeof(int));
    }

    // Initialize matrices with values
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = 1; // or any other initialization
            B[i][j] = 1; // or any other initialization
        }
    }

    pthread_t threads[NUM_THREADS];
    ThreadParam params[NUM_THREADS];

    // Start timing
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Create threads to multiply matrices in chunks
    int chunk_size = SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        params[i].start_row = i * chunk_size;
        params[i].end_row = (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, multiply, &params[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // End timing
    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - start.tv_sec) * 1000.0; // segundos a milisegundos
    elapsed += (end.tv_usec - start.tv_usec) / 1000.0; // microsegundos a milisegundos

    printf("Tiempo de ejecucion promedio: %f milisegundos\n", elapsed);

    // Cleanup
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