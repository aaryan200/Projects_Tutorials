/**
 * Author: Dr. Nileshchandra Pikle
 * Email: nilesh.pikle@gmail.com
 * Contact No: 7276834418
 * Program Name: arrayNpointers.c
 *  * Compilation: gcc -fopnemp arrayNpointers.c
 *         Run: .\a.exe (on windows) or ./a.out (on Linux)
 * Program details:
 *     This program demonstrate use of arrays and pointers in the data environment
 *     Static Array: Arrays that are declared at compile time with a known size are allocated on the stack.
 *                   The compiler knows the size of this array and can manage it for you.
 *     In parallel region: The compiler knows the type and size of the array. 
 *     It can create a private copy of the array for each thread. 
 *     If we used firstprivate instead, it would have copied the values into the new private array.
 * 
 *    Dynamic Array: Arrays whose size known at run time and memory allocated on heap.
 * */
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void initArray(int *array, int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}
int main()
{
    /************************** STATIC ARRAY ******************************************/
    int array[10];
    initArray(array,10);
    printf("\n Static Array before parallel region: ");
    for(int i = 0; i < 10; i++)
    {
        printf("\n array[%d] = %d",i,array[i]);
    }
    /*
      We will create a private region and consider array as private    
    */
   printf("\n Static Array inside parallel region with array as 'private': ");
   omp_set_num_threads(1);
   #pragma omp parallel private(array) 
   {
    // Here array of size 10 created as a private copy to each thread\
    // Note that array is uninitialized!
    for(int i = 0; i < 10; i++)
    {
        printf("\n Static array[%d] = %d",i,array[i]);
    }
   }

   /*
      We will create a private region and consider array as firstprivate    
    */
   printf("\n Static Array inside parallel region with array as 'firstprivate': ");
   omp_set_num_threads(1);
   #pragma omp parallel firstprivate(array) 
   {
    // Here array of size 10 created as a private copy to each thread
    // Note that array is initialized with global values
    for(int i = 0; i < 10; i++)
    {
        printf("\n Static array[%d] = %d",i,array[i]);
    }
   }
   /************************** DYNAMIC ARRAY ******************************************/
   int *darray = (int *)malloc(10*sizeof(int));
   initArray(darray,10);
   printf("\n Dynamic Array before parallel region: ");
    for(int i = 0; i < 10; i++)
    {
        printf("\n Dynamic array[%d] = %d",i,darray[i]);
    }
    /*
      We will create a private region and consider darray as private    
    */
   printf("\n Dynamic Array inside parallel region with array as 'private': ");
   omp_set_num_threads(1);
   #pragma omp parallel private(darray) 
   {
    // Here dynamic array of size 10 created as a private copy to each thread
    // Note that array pointer is uninitialized!
    // Hence you may get segmentation fault or invalid memory access
    for(int i = 0; i < 10; i++)
    {
        //printf("\n Dynamic darray[%d] = %d",i,darray[i]);
    }
   }

   //Note: before executing the code to understand next part of the code comment the printf statement from previous parallel region
   printf("\n Dynamic Array inside parallel region with array as 'firstprivate': ");
   omp_set_num_threads(2);
   #pragma omp parallel firstprivate(darray) 
   {
    // Here pointer to dynamic array of size 10 created as a private copy to each thread
    // Note that array pointer is initialized to the base address of original array!
    // Each thread gets same base address of array so each thread refer to the same array
    for(int i = 0; i < 10; i++)
    {
        printf("\n Dynamic darray[%d] = %d",i,darray[i]);
    }
   }
    return 0;
}