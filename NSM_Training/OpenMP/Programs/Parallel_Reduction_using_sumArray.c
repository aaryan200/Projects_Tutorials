/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Parallel_Reduction_using_sumArray.c
 *  * Compilation: gcc -fopnemp Parallel_Reduction_using_sumArray.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate computation of reduction using multiple threads
 *     using sum array to avoid race conditions
 *     Note that sum array is defined as 2D to avoid FALSE SHARING IN CACHE
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define MIN(x,y) ((x<y)?x:y)
int sequentialReduction(int *A,int N)
{
    int sum = 0;
    for(int i = 0; i < N; i++)
    {
        sum += A[i];
    }
    return sum;
}
int main()
{
    int N = 1<<24;
    int *A = (int *)malloc(N*sizeof(int));
    if(!A)
    {
        printf("\n Error in memory allocation for A!!!");
    }
    for(int i = 0; i < N; i++)
    {
        A[i] = 1;
    }
    int actual_NThreads, NThreads = 32;
    int chunk_size = N/NThreads;
    omp_set_num_threads(NThreads);
    int sum[NThreads][8];
    double start_sequential; 
    double end_sequential; 
    start_sequential = omp_get_wtime();
    int sequential_sum = sequentialReduction(A,N);
    end_sequential = omp_get_wtime(); 
    printf("\n Sequential Work took %f miliseconds\n", (end_sequential - start_sequential)*1000);
    printf("Sequetial sum = %d \n",sequential_sum);
    
    /************ Parallel reduction WRONG Implementation *********************/
    
    double start_parallel; 
    double end_parallel; 
    start_parallel = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        if(tid == 0)
        {
            actual_NThreads = numThreads;
        }
        sum[tid][0] = 0.0;
        int lower = tid * chunk_size;
        int upper = (tid + 1) * chunk_size;
    for(int i = lower; i < MIN(upper,N); i++)
    {
        sum[tid][0] += A[i];
    }
    }
    int parallel_sum = 0;
    for(int i = 0; i < actual_NThreads; i++)
    {
      parallel_sum += sum[i][0];
    }
    end_parallel = omp_get_wtime(); 
    printf("Parallel Work took %f miliseconds\n", (end_parallel - start_parallel)*1000);
    printf("Parallel sum = %d \n",parallel_sum);
    if(parallel_sum != N)
    {
        printf("****************Results are wrong!!!******************* \n\n");
    }
    return 0;
}