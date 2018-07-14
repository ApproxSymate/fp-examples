/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/cnt/cnt.c
 */

#include <klee/klee.h>

#define MAXSIZE 10

typedef int matrix[MAXSIZE][MAXSIZE];

// Forwards declarations
void Sum(matrix);

// Globals
matrix Array;
int Postotal, Negtotal, Poscnt, Negcnt;

// The main function
int main(int argc, char **argv) {
  klee_make_symbolic(Array, sizeof(int) * MAXSIZE * MAXSIZE, "Array");

  Sum(Array);
  return 0;
}

void Sum(matrix Array) {
  register int Outer, Inner;

  int Ptotal = 0; /* changed these to locals in order to drive worst case */
  int Ntotal = 0;
  int Pcnt = 0;
  int Ncnt = 0;

  for (Outer = 0; Outer < MAXSIZE; Outer++) // Maxsize = 100
    for (Inner = 0; Inner < MAXSIZE; Inner++)
#ifdef WORSTCASE
      if (Array[Outer][Inner] >= 0) {
#else
      if (Array[Outer][Inner] < 0) {
#endif
        Ptotal += Array[Outer][Inner];
        Pcnt++;
      } else {
        Ntotal += Array[Outer][Inner];
        Ncnt++;
      }

  Postotal = Ptotal;
  Poscnt = Pcnt;
  Negtotal = Ntotal;
  Negcnt = Ncnt;
}
