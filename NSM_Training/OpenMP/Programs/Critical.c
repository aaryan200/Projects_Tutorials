/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Critical.c
 *  * Compilation: gcc -fopnemp Critical.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate critical contrunct in OpenMP
 *     #pragma omp critical
 *     {
 *        // code snippet
 *      }
 *      Critical section is a region in the code which can be executed by a thread at a time
 * */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

float big_job(int i)
{
  float s = 0.0; 
  for(int j = 0; j < i * 2; j++)
  {
   s += sin(i); 
  }
  return s;
}
float consumeB(float B)
{
    return B/10.0;
}

float executeSequentially(int niters)
{
    float result = 0.0;
    float B = 0.0;
    for(int i = 0; i < niters; i++)
        {
            B = big_job(i);
            result += consumeB(B);
        }
    return result;
}

int main()
{
    float result = 0.0;
    int niters = 10000;
    double S_start_time, S_run_time;
    S_start_time = omp_get_wtime();
    result = executeSequentially(niters);
    S_run_time = omp_get_wtime() - S_start_time;
    printf("\n final value after sequential execution is %f and Time: %f",result,S_run_time);
    result = 0.0;

    double P_start_time, P_run_time;
    P_start_time = omp_get_wtime();
    #pragma omp parallel
    {
        float B;
        int i, id, Nthreads;
        id = omp_get_thread_num();
        Nthreads = omp_get_num_threads();
        for(i = id; i < niters; i += Nthreads)
        {
            B = big_job(i);
            #pragma omp critical
               result += consumeB(B);
        }
    }
     P_run_time = omp_get_wtime() - P_start_time;
    printf("\n final value after Parallel execution is %f and Time: %f",result,P_run_time);
    return 0;
}