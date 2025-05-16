
/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: ParallelPi_v3_sumArray_CyclicReduction.c
 *  * Compilation: gcc -fopnemp ParallelPi_v3_sumArray_CyclicReduction.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate calculation of PI value using integration method
 *     This is firs attaempt to parallelize the for loop
 *     NThreads defines number of threads to be launched 
 *     Based on number of threads the loop iterations are divided among the threads equally
 *     Each thread gets approximately (num_steps / NThreads) number of iterations
 *     The iterations of for loop are distributed among the available threads in cyclic fashion
 *     Let there are 4 threads in parallel region
 *     Thread 0 is responsible for iteration number 0,  4,  8,  12, ...
 *     Thread 1 is responsible for iteration number 1,  5,  9,  13, ...
 *     Thread 2 is responsible for iteration number 2,  6,  10,  14, ...
 *     Thread 3 is responsible for iteration number 3,  7,  11,  15, ...
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define NTHREADS 128

static long num_steps = 1000000000;
double step;
#define CBLK 8
int main()
{
    int actual_NThreads;
    double pi;
    double sum[NTHREADS][CBLK];
    double start_time, run_time;
    step = 1/(double)num_steps;
    omp_set_num_threads(NTHREADS);
    int chunk_size = num_steps/NTHREADS;
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        double x;
        int tid = omp_get_thread_num();
        int numThreads = omp_get_num_threads();
        if(tid == 0)
        {
            actual_NThreads = numThreads;
        }
        sum[tid][0] = 0.0;
        for(int i = tid; i < num_steps; i+= numThreads)
        {
            x = (i + 0.5)*step;
            sum[tid][0] += 4.0/(1.0 + x * x);
        }        
    }
    pi = 0.0;
    for(int i = 0; i < actual_NThreads; i++)
    {
        pi += sum[i][0];
    }
    pi = step*pi;
    run_time = omp_get_wtime() - start_time;
    printf("\n Pi value = %f  total time = %f ",pi,run_time);
    return 0;
}
