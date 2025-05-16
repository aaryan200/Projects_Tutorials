/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: ParallelPi_v2_SumArray_BlockDistribution.c
 *  * Compilation: gcc -fopnemp ParallelPi_v2_SumArray_BlockDistribution.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate calculation of PI value using integration method
 *     This is firs attaempt to parallelize the for loop
 *     NThreads defines number of threads to be launched 
 *     Based on number of threads the loop iterations are divided among the threads equally
 *     Each thread gets approximately (num_steps / NThreads) number of iterations
 *     For this implementation we declare lower and upper variables in parallel region to get start and end iteration number for each thread
 *     lower = tid *  (num_steps / NThreads)
 *     upper = (tid + 1) *  (num_steps / NThreads)
 *     If num_steps are not iteger multiple of NThreads then last thread may get less number of iterations
 *     To handle this situation a MIN() function is defined to get upper limit of iteration number for last thread
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <time.h>
#define MIN(x,y) ((x<y)?x:y)
static long num_steps = 1000000000;
double step;
#define NTHREADS 256

int main()
{
    int actual_NThreads;
    double pi;
    double sum[NTHREADS];
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
        sum[tid] = 0.0;
        int lower = tid * chunk_size;
        int upper = (tid + 1) * chunk_size;
        for(int i = lower; i < MIN(upper,num_steps); i++)
        {
            x = (i + 0.5)*step;
            sum[tid] += 4.0/(1.0 + x * x);
        }        
    }
    pi = 0.0;
    for(int i = 0; i < actual_NThreads; i++)
    {
        pi += sum[i];
    }
    pi = step*pi;
    run_time = omp_get_wtime() - start_time;
    printf("\n Pi value = %f  total time = %f ",pi,run_time);
    return 0;
}
