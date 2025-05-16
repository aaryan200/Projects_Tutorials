/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: VecAdd.c
 * Compilation: gcc -fopnemp VecAdd.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate vector addition using OpenMP
 *     Input: Three vectors A, B, C of size N
 *     Output: C = A + B 
*/
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void initVectors(double *A,double *B,double *CS,double *CP, int N)
{
    for(int i = 0; i < N; i++)
    {
        A[i] = 3.0;
        B[i] = 4.0;
        CS[i] = 0.0;
        CP[i] = 0.0;
    }
}
void vecAddSequential(double *A,double *B,double *C, int N)
{
 for(int i = 0; i < N; i++)
 {
    C[i] = A[i] + B[i];
 }
}
int min(int a, int b)
{
    if(a > b)
    { 
        return a;
    }else{
        return b;
    }
}
void verifyResults(double *CS,double *CP, int N)
{
    for(int i = 0; i < N; i++)
    {
        if(CS[i] != CP[i])
        {
            printf("Results are incorrect!!! \n");
            printf("CS[%d] = %f and CP[%d] = %f \n",i,CS[i],i,CP[i]);
            break;
        }
    }
}
int main()
{
  int i,N = 1024*1024*10;

  double *A = (double *)malloc(N*sizeof(double));
  double *B = (double *)malloc(N*sizeof(double));
  double *CS = (double *)malloc(N*sizeof(double)); // Output vector to store sequential results
  double *CP = (double *)malloc(N*sizeof(double)); // Output vector to store Parallel results

  if(!A)
  {
    printf("\n Error in allocating memory to vector A");
  }
  if(!B)
  {
    printf("\n Error in allocating memory to vector B");
  }
  if(!CS)
  {
    printf("\n Error in allocating memory to vector C");
  }
  if(!CP)
  {
    printf("\n Error in allocating memory to vector C");
  }
  /*Initialize vectors*/
  initVectors(A,B,CS,CP,N);

  double start_sequential; 
  double end_sequential; 
  start_sequential = omp_get_wtime();

  /*Sequential execution of vector addition*/
  vecAddSequential(A,B,CS,N);

  end_sequential = omp_get_wtime(); 
  printf("Sequential Work took %f miliseconds\n", (end_sequential - start_sequential)*1000);
  

  /***************** Parallel Execution ****************************/
  int nThreads = 8;
  omp_set_num_threads(nThreads);
  int chunkSize = N/nThreads;
  double start_parallel; 
  double end_parallel; 
  start_parallel = omp_get_wtime();
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    int lower = tid*chunkSize;
    int upper = (tid + 1)*chunkSize;
    
    for(int i = tid; i < min(upper,N); i++)
    {
        CP[i] = A[i] + B[i];
    }
  }
  end_parallel = omp_get_wtime(); 
  printf("Parallel Work took %f miliseconds\n", (end_parallel - start_parallel)*1000);
  
  verifyResults(CS,CP, N);

  free(A);
  free(B);
  free(CS);
  free(CP);
  return 0;
}