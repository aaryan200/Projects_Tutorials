/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Threads.c
 * Compilation: gcc -fopnemp Threads.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate some openMP library routines such as 
 *     1. omp_get_num_procs() - This gives total number of logocal cores (with hyperthreading) present in the system
 *     2. omp_get_num_threads() - This gives total number of threads created in the current team
 *     3. omp_set_num_threads() - This defines the number of threads to be created in the current team 
 *     4. omp_get_thread_num() - This gives id of each thread in the current team 
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
    /*
      TODO:
           1. Set different number of threads using omp_set_num_threads(N);  
           2. Observe the sequence in which thread Ids are printed in the parallel region by running multiple times
           3. print number of threads before setting number of threads by omp_set_num_threads(4);
           4. What is the maximum number of threads can be launched?
    */

  
    int numProcs = omp_get_num_procs();
    printf("\n The number of logical cores present in the system are: %d",numProcs);
    
    omp_set_num_threads(numProcs);

    int nThreads = omp_get_num_threads();
    printf("\n The number of threads present before parallel region: %d",nThreads);
        
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("\n tid = %d",tid);
        
        int nThreads = omp_get_num_threads();
        if(tid == 0)
        {
            printf("\n The number of threads present in the parallel region are: %d",nThreads);
        }
    }
    return 0;
}