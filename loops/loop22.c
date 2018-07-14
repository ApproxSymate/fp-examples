/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/matmult/matmult.c
 */

/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */

#include <klee/klee.h>

#define UPPERLIMIT 20

typedef int matrix[UPPERLIMIT][UPPERLIMIT];

matrix ArrayA, ArrayB, ResultArray;

void Multiply(matrix A, matrix B, matrix Res);

int main(int argc, char **argv) {
  klee_make_symbolic(ArrayA, UPPERLIMIT * UPPERLIMIT * sizeof(int), "ArrayA");
  klee_make_symbolic(ArrayB, UPPERLIMIT * UPPERLIMIT * sizeof(int), "ArrayB");

  Multiply(ArrayA, ArrayB, ResultArray);
}

void Multiply(matrix A, matrix B, matrix Res) {
  register int Outer, Inner, Index;

  for (Outer = 0; Outer < UPPERLIMIT; Outer++)
    for (Inner = 0; Inner < UPPERLIMIT; Inner++) {
      Res[Outer][Inner] = 0;
      for (Index = 0; Index < UPPERLIMIT; Index++)
        Res[Outer][Inner] += A[Outer][Index] * B[Index][Inner];
    }
}
