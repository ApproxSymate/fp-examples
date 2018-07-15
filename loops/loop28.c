/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#include <klee/klee.h>

unsigned long bit[33];

int main(int argc, char **argv) {
  int j;
  char iec[9];
  unsigned long itmp, ic, *iout;
  unsigned long *p;
  static int ipp[33] = { 0,  16, 7, 20, 21, 29, 12, 28, 17, 1,  15,
                         23, 26, 5, 18, 31, 10, 2,  8,  24, 14, 32,
                         27, 3,  9, 19, 13, 30, 6,  22, 11, 4,  25 };

  iout = &ic;

  klee_make_symbolic(bit, 33 * sizeof(unsigned long), "bit");

  p = bit;
  for (j = 32; j >= 1; j--)
    *iout = (*iout <<= 1) | (p[ipp[j]] & itmp ? 1 : 0);

  return 0;
}
