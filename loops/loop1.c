/* Simplified version of
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/bsort100/bsort100.c
 */

#include <klee/klee.h>

#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define NUMELEMS 100
#define MAXDIM (NUMELEMS + 1)

/* BUBBLESORT BENCHMARK PROGRAM:
 * This program tests the basic loop constructs, integer comparisons,
 * and simple array handling of compilers by sorting 10 arrays of
 * randomly generated integers.
 */

int Array[MAXDIM];

void BubbleSort(int Array[]);

int main() {
  klee_make_symbolic(Array, MAXDIM * sizeof(int), "Array");
  BubbleSort(Array);
}

void BubbleSort(Array) int Array[];
/*
 * Sorts an array of integers of size NUMELEMS in ascending order.
 */
{
  int Sorted = FALSE;
  int Temp, LastIndex, Index, i;

  for (i = 1; i <= NUMELEMS - 1; /* apsim_loop 1 0 */
       i++) {
    Sorted = TRUE;
    for (Index = 1; Index <= NUMELEMS - 1; /* apsim_loop 10 1 */
         Index++) {
      if (Index > NUMELEMS - i)
        break;
      if (Array[Index] > Array[Index + 1]) {
        Temp = Array[Index];
        Array[Index] = Array[Index + 1];
        Array[Index + 1] = Temp;
        Sorted = FALSE;
      }
    }

    if (Sorted)
      break;
  }
}
