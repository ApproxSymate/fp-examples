/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#include <klee/klee.h>

int main(int argc, char **argv) {
  int j, m;
  unsigned long ietmp1, ietmp2;
  char iec[9];

  klee_make_symbolic(iec, 9 * sizeof(char), "iec");

  for (j = 1, m = 5; j <= 4; j++, m++) {
    iec[j] = ietmp1 & 0x3fL;
    iec[m] = ietmp2 & 0x3fL;
    ietmp1 >>= 6;
    ietmp2 >>= 6;
  }

  return 0;
}
