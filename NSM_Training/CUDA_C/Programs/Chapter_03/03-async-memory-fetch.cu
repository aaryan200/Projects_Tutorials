#include <stdio.h>

__global__
void initWith(float num, float *a, int N)
{

  int index = threadIdx.x + blockIdx.x * blockDim.x;
  int stride = blockDim.x * gridDim.x;

  for(int i = index; i < N; i += stride)
  {
    a[i] = num;
  }
}

__global__
void addVectorsInto(float *result, float *a, float *b, int N)
{
  int index = threadIdx.x + blockIdx.x * blockDim.x;
  int stride = blockDim.x * gridDim.x;

  for(int i = index; i < N; i += stride)
  {
    result[i] = a[i] + b[i];
  }
}

void checkElementsAre(float target, float *vector, int N)
{
  for(int i = 0; i < N; i++)
  {
    if(vector[i] != target)
    {
      printf("FAIL: vector[%d] - %0.0f does not equal %0.0f\n", i, vector[i], target);
      exit(1);
    }
  }
  printf("Success! All values calculated correctly.\n");
}

int main()
{
  int deviceId;
  int numberOfSMs;

  cudaGetDevice(&deviceId);
  cudaDeviceGetAttribute(&numberOfSMs, cudaDevAttrMultiProcessorCount, deviceId);

  const int N = 2<<24;
  size_t size = N * sizeof(float);

  float *a;
  float *b;
  float *c;
  float *h_c;

  cudaMalloc(&a, size);
  cudaMalloc(&b, size);
  cudaMalloc(&c, size);
  cudaMallocHost(&h_c, size);

  size_t threadsPerBlock;
  size_t numberOfBlocks;

  threadsPerBlock = 256;
  numberOfBlocks = 32 * numberOfSMs;

  cudaError_t addVectorsErr;
  cudaError_t asyncErr;

  /*
   * Create 3 streams to run initialize the 3 data vectors in parallel.
   */

  cudaStream_t stream1, stream2, stream3;
  cudaStreamCreate(&stream1);
  cudaStreamCreate(&stream2);
  cudaStreamCreate(&stream3);

  /*
   * Give each `initWith` launch its own non-standard stream.
   */

  initWith<<<numberOfBlocks, threadsPerBlock, 0, stream1>>>(3, a, N);
  initWith<<<numberOfBlocks, threadsPerBlock, 0, stream2>>>(4, b, N);
  initWith<<<numberOfBlocks, threadsPerBlock, 0, stream3>>>(0, c, N);
    
  /*
   * Synchronize - we are using different non-standard streams for initialisation
   * and calcs, so we need to explicitly synchronize to ensure all data has been
   * initialised before starting the calculations 
   */
  cudaError_t asyncErrInit = cudaDeviceSynchronize();
  if(asyncErrInit != cudaSuccess) printf("Error init: %s\n", cudaGetErrorString(asyncErrInit));
  
  int segmentSize = size / 4;
  int segLen = N / 4;
    
  for (int i = 0; i < 4; i++) {
      cudaStream_t stream;
      cudaStreamCreate(&stream);
      
      int segOffset = i * segLen;
      
      // Execute the add vectors kernel on this non-default stream
      addVectorsInto<<<numberOfBlocks, threadsPerBlock, 0, stream>>>(&c[segOffset], // provide the pointer to this location
                                                                     &a[segOffset],
                                                                     &b[segOffset],
                                                                     segLen);
      
      // Use cudaMemcpyAsync to copy this segment to host over the same non-default stream
      cudaMemcpyAsync(&h_c[segOffset],
                      &c[segOffset],
                      segmentSize,
                      cudaMemcpyDeviceToHost,
                      stream);
      
      cudaStreamDestroy(stream);
  }

  addVectorsErr = cudaGetLastError();
  if(addVectorsErr != cudaSuccess) printf("Error: %s\n", cudaGetErrorString(addVectorsErr));

  asyncErr = cudaDeviceSynchronize();
  if(asyncErr != cudaSuccess) printf("Error: %s\n", cudaGetErrorString(asyncErr));

  checkElementsAre(7, h_c, N);

  /*
   * Destroy streams when they are no longer needed.
   */

  cudaStreamDestroy(stream1);
  cudaStreamDestroy(stream2);
  cudaStreamDestroy(stream3);

  cudaFree(a);
  cudaFree(b);
  cudaFree(c);
  cudaFreeHost(h_c);
}
