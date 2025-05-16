#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 100000

void vectorAdditionSequential(int a[], int b[], int c[], int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

void vectorAdditionParallel(int a[], int b[], int c[], int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];
    double startTime, endTime;
    
    // Initialize the arrays
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = i;
        b[i] = i;
    }
    
    // Sequential vector addition
    startTime = omp_get_wtime();
    vectorAdditionSequential(a, b, c, ARRAY_SIZE);
    endTime = omp_get_wtime();
    printf("Sequential execution time: %.6f seconds\n", endTime - startTime);
    
    // Parallel vector addition
    startTime = omp_get_wtime();
    vectorAdditionParallel(a, b, c, ARRAY_SIZE);
    endTime = omp_get_wtime();
    printf("Parallel execution time: %.6f seconds\n", endTime - startTime);
    
    return 0;
}
