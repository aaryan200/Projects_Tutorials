/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Static_schedule.c
 *  * Compilation: gcc -fopnemp Static_schedule.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate the concept of static schedule
 * The static schedule on a worksharing-loop constructs directs the compiler to define the schedule for mapping loop 
 * iterations onto threads at “compile time”. 
 * When a chunk size is not provided, the compiler will break the loop iterations into number of chunks equal to the 
 * number of threads, and assign one chunk to each thread. 
 * The chunks are assigned to each thread in a round robin fashion. Since the decisions such as chunk size, 
 * compute distribution are fixed at compile time, the scheduling overhead is reduced and the program could potentially run faster.

*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#define ITER 10
#define CHUNK_SIZE 2
#define NTHREADS 4
int main()
{
    int i;
    double *A = (double *)malloc(ITER*sizeof(double));
    if(!A)
    {
        printf("\n Memory allocation error to A !!!");
    }
    for(i = 0; i < ITER; i++)
    {
        A[i] = 2.0 * i;
    }
    omp_set_num_threads(NTHREADS);
   double total_time, end_time, start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int i;
        int tid = omp_get_thread_num();
        #pragma omp for schedule(static,CHUNK_SIZE)
        for(i = 1; i < ITER; i++)
        {
          A[i] = A[i] * sqrt(i)/pow(sin(i), tan(i));
          //printf("\n tid = %d i = %d",tid,i);
        }
    }
    end_time = omp_get_wtime();
    total_time = end_time-start_time;
    printf("\n chunk size = %d total time = %f  seconds",CHUNK_SIZE,total_time);

    return 0;
}