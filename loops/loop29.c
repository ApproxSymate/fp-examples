/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#include <klee/klee.h>

typedef struct IMMENSE {
  unsigned long l, r;
} immense;

static immense icd;

int main(int argc, char **argv) {
  int i;

  klee_make_symbolic(&icd, sizeof(immense), "icd");

  for (i = 1; i <= 2; i++) {
    icd.r = (icd.r | ((icd.r & 1L) << 28)) >> 1;
    icd.l = (icd.l | ((icd.l & 1L) << 28)) >> 1;
  }

  return 0;
}
