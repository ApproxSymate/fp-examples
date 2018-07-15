/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#include <klee/klee.h>

typedef struct IMMENSE {
  unsigned long l, r;
} immense;
typedef struct GREAT {
  unsigned long l, c, r;
} great;

unsigned long bit[33];

int main(int argc, char **argv) {
  unsigned long ir;

  static int iet[49] = { 0,  32, 1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
                         8,  9,  10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16,
                         17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25,
                         26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

  unsigned long *p;

  great ie;
  int j, l, m;

  klee_make_symbolic(&ir, sizeof(unsigned long), "ir");
  p = bit;
  ie.r = ie.c = ie.l = 0;
  for (j = 16, l = 32, m = 48; j >= 1; j--, l--, m--) {
    ie.r = (ie.r <<= 1) | (p[iet[j]] & ir ? 1 : 0);
    ie.c = (ie.c <<= 1) | (p[iet[l]] & ir ? 1 : 0);
    ie.l = (ie.l <<= 1) | (p[iet[m]] & ir ? 1 : 0);
  }
  return 0;
}
