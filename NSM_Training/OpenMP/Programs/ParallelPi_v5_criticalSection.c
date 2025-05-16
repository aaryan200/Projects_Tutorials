/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: ParallelPi_v5_criticalSection.c
 *  * Compilation: gcc -fopnemp ParallelPi_v5_criticalSection.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate calculation of PI value using integration method
 *     This is firs attaempt to parallelize the for loop
 *     NThreads defines number of threads to be launched 
 *     Based on number of threads the loop iterations are divided among the threads equally
 *     Each thread gets approximately (num_steps / NThreads) number of iterations
       The race conditions are handled by placing sum variable update int the critical section
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
static long num_steps = 1000000000;
double step;
int main()
{
    int NThreads = 32;
    double pi, sum = 0.0;
    double start_time, run_time;
    step = 1/(double)num_steps;
    omp_set_num_threads(NThreads);
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        double x, partial_sum = 0.0;
        int nthreads = omp_get_num_threads();
        if(tid == 0)
        {
            NThreads = nthreads;
        }
        for(int i = tid; i < num_steps; i+=nthreads)
        {
            x = (i + 0.5)*step;
            partial_sum += 4.0/(1.0 + x * x);
        }   
        #pragma omp critical
         {
           sum +=  partial_sum; 
         }   
    }
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n Pi value = %f  total time = %f ",pi,run_time);
    return 0;
}
