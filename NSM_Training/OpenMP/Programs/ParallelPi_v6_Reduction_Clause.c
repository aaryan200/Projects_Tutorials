/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: ParallelPi_v6_Reduction_Clause.c
 *  * Compilation: gcc -fopnemp ParallelPi_v6_Reduction_Clause.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate calculation of PI value using integration method
 *     This is firs attaempt to parallelize the for loop
 *     NThreads defines number of threads to be launched 
 *     Based on number of threads the loop iterations are divided among the threads equally
 *     Each thread gets approximately (num_steps / NThreads) number of iterations
 *     This version of parallel pi uses parallel reduction clause, hence no need to worry about creating sum array, false sharing, etc.
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define MIN(x,y) ((x<y)?x:y)
static long num_steps = 1000000000;
double step;

int main()
{
    int NThreads = 32;
    double x, pi, sum = 0.0;
    double start_time, run_time;
    step = 1/(double)num_steps;
    //omp_set_num_threads(NThreads);
    start_time = omp_get_wtime();
   
        #pragma omp parallel for private(x) reduction( +: sum)
        for(int i = 0; i < num_steps; i++)
        {

            x = (i + 0.5)*step;
            sum += 4.0/(1.0 + x * x);
        }        
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n Pi value = %f  total time = %f ",pi,run_time);
    return 0;
}
