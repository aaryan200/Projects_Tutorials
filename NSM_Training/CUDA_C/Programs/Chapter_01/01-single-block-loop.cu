#include <stdio.h>

/*
 * Refactor `loop` to be a CUDA Kernel. The new kernel should
 * only do the work of 1 iteration of the original loop.
 */

__global__ void loop(int N)
{
  int tid = threadIdx.x;
  int bid = blockIdx.x;
  int bdim = blockIdx.x;
  int global_id = bid * bdim + tid;
  printf("Block %d, Thread %d, Global: %d\n", tid, bid, global_id);
}

int main()
{
  /*
   * When refactoring `loop` to launch as a kernel, be sure
   * to use the execution configuration to control how many
   * "iterations" to perform.
   *
   * For this exercise, only use 1 block of threads.
   */

  int N = 10;
  loop<<<1, N>>>(N);
  cudaDeviceSynchronize();
}
