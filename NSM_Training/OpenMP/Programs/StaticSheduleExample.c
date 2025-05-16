#include<stdio.h>
#include<omp.h>
#define Nthreads 5
#define CHUNK_SIZE 3
#define SIZE 17
int main()
{
    omp_set_num_threads(Nthreads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for schedule(static,CHUNK_SIZE)
        for(int i = 0; i < SIZE; i++)
        {
            printf("\n tid = %d, i = %d",tid,i);
            // Lower triangular matrix computations
        }
    }
    return 0;
}