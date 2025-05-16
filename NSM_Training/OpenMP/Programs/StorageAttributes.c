/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: StorageAttributes.c
 *  * Compilation: gcc -fopnemp StorageAttributes.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrates the storage attributes such as private, firstprivate, lastprivate,default
 *     private
 *           The private clause changes the default behavior when mapping variables into the new data environment. 
 *           The private clause tells the compiler to create a new variable of the same type and name for each thread. 
 *           This new variable is private to each thread; that is each thread has a copy of the variable that the other threads cannot access.
 *           The value of the private variable is uninitialized.
 *    firstprivate
 *           The firstprivate variable also masks the original variable inside the parallel region, and the value of the original 
 *           variable is unchanged after the region.The difference between firstprivate and private is that with firstprivate, 
 *           the new private variable is initialized by copying the value of the corresponding original variable.
 *   Default
 *          If default(none)is used on a construct, then all variables passing from the encountering thread into a region must be 
 *          explicitly listed in a private, firstprivate, reduction, or shared clause.

 * */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main()
{
    int val = 10;
    omp_set_num_threads(2);
    #pragma omp parallel private(val)
    {
        int tid = omp_get_thread_num();
        val += tid;// Here val is uninitialized
        printf("\n Inside 'private' parallel region private val = %d",val);
    }
    printf("\n Outside 'private' parallel region val = %d",val);// Here val is considered outiside the parallel scope

    val = 10;
    #pragma omp parallel firstprivate(val)
    {
        int tid = omp_get_thread_num();
        val += tid;// Here valinitialized to 10
        printf("\n Inside 'firstprivate' parallel region private val = %d",val);
    }
    printf("\n Outside 'firstprivate' parallel region val = %d",val);// Here val is considered outiside the parallel scope


   /*
   #pragma omp parallel lastprivate(val)
    {
        int tid = omp_get_thread_num();
        val += tid;// Here val is uninitialized
        printf("\n Inside 'lastprivate' parallel region private val = %d",val);
    }
    printf("\n Outside 'lastprivate' parallel region val = %d",val);// Here val is considered outiside the parallel scope
    
    The meaning of lastprivate, is to assign "the sequentially last iteration of the associated loops, or 
    the lexically last section construct [...] to the original list item."Hence, there it no meaning for a pure parallel construct. 
    It would not be a good idea to use a meaning like "the last thread to exit the parallel construct" - that would be a race condition.
   */
    
}