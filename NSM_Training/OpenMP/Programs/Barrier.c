/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Barrier.c
 * Compilation: gcc -fopnemp Barrier.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate use of barrier synchronization
 *     A barrier defines a point in a program at which all threads must arrive before any thread may proceed past the barrier.
 *     
 *     IMPORTANT: Note that this program is not performing any meaningful computation. It is simply demonstrating the situation where 
 *     barrier synchronisation makes sense!
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
double dummyTask(int tid, int NThreads)
{
    double sum = 0.0;
    for(int i = 0; i < (tid + 1)*NThreads; i++)
    {
        sum += sqrt(tid * NThreads);
    }
    return sum;
}
int main()
{  
    double A[8],B[8];
    int nthreads;

    omp_set_num_threads(8);
    #pragma omp parallel
    {
        int tid, NThreads;
        tid = omp_get_thread_num();
        NThreads = omp_get_num_threads();
        if(tid == 0)nthreads = NThreads;
        A[tid] = dummyTask(tid,NThreads);
        // Here all threads must complete dummyTask before proceeding to next computation
        // which requires entire array A[]. Or else the program may end with undefined behaviour.
        #pragma omp barrier 
        for(int i = 0; i < 8; i++)
        {
            B[tid] += A[i];
        }
    }
    return 0;
}