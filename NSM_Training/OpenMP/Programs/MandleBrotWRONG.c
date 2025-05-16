/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: MandleBrotWRONG.c
 *  * Compilation: gcc -fopnemp MandleBrotWRONG.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrates a program that computes the area of a Mandelbrot set. 
 *     The Mandelbrot set is the set of complex numbers c for which the function z2 + c does not diverge when iterated from z= 0. 
 *     The area of the Mandelbrot set is known to be around 1.506
 *     NOTE: This version of the program has multiple bugs. Your job is to inspect the code and find the bugs.
 *     
 *     Problems in this code
 *     1. The first problem we notice is that eps is specified as private. Therefore, it has not been initialized
 *     Solution: Notice that eps is read-only. It is not updated inside the parallel region.
 *               Therefore, another solution is to let it be shared (shared(eps)) or
 *               not specify eps in a data environment clause and let its default, shared behavior be used.
 *     2. The function testpoint() works with a file scope variable for c, but this same variable is specified 
 *        as a private variable in the parallel worksharing-loop region.
 *     Solution: To fix this problem, we modify the argument list to testpoint() so we pass c into the function as an argument. 
 *               We then remove the file scope copy of the variable since it is no longer used.
 *     3. the increment of the shared variable numoutside, it is happening from multiple threads without any constructs 
 *        to enforce mutual exclusion.
 *     Solution: That increment operation needs to be protected with a critical section; thereby eliminating the data race.
 **/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#define NPOINTS 1000
#define MAXITER 1000

struct d_complex{
    double r;
    double i;
};

struct d_complex c;
int numoutside = 0;
void testpoint(void)
{
  struct d_complex z;
  int iter;
  double temp;
   
   z = c;
   for(iter = 0; iter < MAXITER; iter++)
   {
    temp = (z.r*z.r) - (z.i*z.i) + c.r;
    z.i = z.r*z.i*2 +c.i;
    z.r = temp;
    if((z.r*z.r+z.i*z.i)> 4.0)
    {
        numoutside++;
        break;
    }
   }
}
int main()
{
    int i,j;
    double area, error, eps = 1.0e-5;
    #pragma omp parallel for private(c,eps)
    for(i = 0; i < NPOINTS; i++)
    {
        for(j = 0; j < NPOINTS; j++)
        {
            c.r = -2.0 + 2.5*(double)(i)/(double)(NPOINTS)+eps;
            c.i = 1.125*(double)(j)/(double)(NPOINTS)+eps;
            testpoint();
        }
    }

   area = 2.0 * 2.5*1.125*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
   error = area/(double)NPOINTS;

   printf("\n Area of Mandlebrot set = %12.8f +/- %12.8f",area,error);
   printf("\n Correct answer should be around 1.506\n");
    return 0;
}



