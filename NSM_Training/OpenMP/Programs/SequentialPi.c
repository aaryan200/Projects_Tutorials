/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: SequentialPi.c
 *  * Compilation: gcc -fopnemp SequentialPi.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate calculation of PI value using integration method
*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
static long num_steps = 1000000000;
double step;
int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;
    step = 1/(double)num_steps;
    start_time = omp_get_wtime();
    for(i = 0; i < num_steps; i++)
    {
        x = (i + 0.5)*step;
        sum += 4.0/(1.0 + x * x);
    }
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("\n Pi value = %f  total time = %f ",pi,run_time);
    return 0;
}
