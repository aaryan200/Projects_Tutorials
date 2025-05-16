/*
  Write an OpenMP program to perform following computation
   D = A*B + C
   Where A, B, C, D are matrices of size N*N (square matrix)
   1. Write sequential program first to perform above computation
   2. Assume N = 1024 (You may increase the size based on memory available in your system)
   3. Record the sequential time Ts
   4. Apply parallelization strategy
   5. Valdiate the output by writing validate_function()
   6. Record the parallel runtime for number of threads = 2, 4, 8, 16, 32
   7. Calculate speedup for each of the above multi-threaded version.
*/