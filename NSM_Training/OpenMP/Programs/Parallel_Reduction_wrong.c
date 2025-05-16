/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Parallel_Reduction_wrong.c
 *  * Compilation: gcc -fopnemp Parallel_Reduction_wrong.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate computation of reduction using multiple threads
 *     NOTE THAT THIS IS THE WRONG IMPLEMENTATION OF REDUCTION OPERATION
 * 
 *     reduction stands for sum/mulyiplication/min/max etc. of all elements of an array
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
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
    int sum = 0;
    double start_sequential; 
    double end_sequential; 
    start_sequential = omp_get_wtime();
    sum = sequentialReduction(A,N);
    end_sequential = omp_get_wtime(); 
    printf("\n Sequential Work took %f miliseconds\n", (end_sequential - start_sequential)*1000);
    printf("Sequetial sum = %d \n",sum);
    
    /************ Parallel reduction WRONG Implementation *********************/
    sum = 0;
    double start_parallel; 
    double end_parallel; 
    start_parallel = omp_get_wtime();
    #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
        sum += A[i];
    }
    end_parallel = omp_get_wtime(); 
    printf("Parallel Work took %f miliseconds\n", (end_parallel - start_parallel)*1000);
    printf("Parallel sum = %d \n",sum);
    if(sum != N)
    {
        printf("****************Results are wrong!!!******************* \n\n");
    }
    return 0;
}