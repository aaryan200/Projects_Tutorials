/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: Dynamic_schedule.c
 *  * Compilation: gcc -fopnemp Dynamic_schedule.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate the concept of Dynamic schedule
 * The static schedule runs into trouble, however, in two different situations.
 * 1. The amount of work per iteration of the loop may vary widely
 * 2. If the processors in a system run at different speeds, the scheduler has no way to take such differences into account
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<stdbool.h>
#define ITER 10000000
#define CHUNK_SIZE 2
#define NTHREADS 8

bool checkPrime(int num)
{
  for(int i = 2; i < sqrt(num); i++)
  {
    if(num%i == 0)
    {
        return false;
    }
  }
  return true;
}
int main()
{
   int sum = 0;
   double start_time, end_time, total_time;
   int chunk_size,num_threads;
   for( chunk_size = 1; chunk_size < 50; chunk_size+=10)
   {
     for(num_threads = 1; num_threads < 33; num_threads *= 2)
     {
        omp_set_num_threads(num_threads);
        start_time = omp_get_wtime();
        #pragma omp parallel
        {
          int i;
          int tid = omp_get_thread_num();
          #pragma omp for schedule(static,chunk_size) reduction(+ : sum)
          for(i = 2; i <= ITER; i++)
          {
             if(checkPrime(i)) sum++;
          }
        }
        end_time = omp_get_wtime();
        total_time = end_time - start_time;
         printf("\n Total time using dynamic scheduling with chunk size %d and num Threads %d is %f",chunk_size, num_threads,(end_time-start_time));
      }
    }
    return 0;
}