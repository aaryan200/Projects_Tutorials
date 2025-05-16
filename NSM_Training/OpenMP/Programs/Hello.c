/*
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Hello.c
 * Compilation: gcc -fopnemp Hello.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main()
{
    int procs = omp_get_num_procs();
    printf("\n number of logical cores: %d",procs);
    omp_set_num_threads(procs);
    #pragma omp parallel // This parallel directive start the parallel region by creating (forking) threads
    {
        int tid = omp_get_thread_num();
        int nThreads = omp_get_num_threads();
        if(tid == 0)
        {
            printf("\n Total Number of threads in parallel region: %d",nThreads);
        }else{
              printf("\n Hello world %d",tid);
        }
         // This statement gets executed by number of threads available in the parallel region
    }// Parallel region termibates here and threads get destroyed (Joining)
    return 0;
}