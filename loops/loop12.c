/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/edn/edn.c
 */

#include <klee/klee.h>

long int mac(const short *a, const short *b, long int sqr, long int *sum) {
  long int i;
  long int dotp = *sum;

  for (i = 0; i < 150; i++) {
    dotp += b[i] * a[i];
    sqr += b[i] * b[i];
  }

  *sum = dotp;
  return sqr;
}

int main(int argc, char **argv) {
  short a[200];
  short b[200];
  short c = 0x3;
  long int output[200];

  klee_make_symbolic(a, 200 * sizeof(short), "a");
  klee_make_symbolic(b, 200 * sizeof(short), "b");

  c = mac(a, b, (long int)c, (long int *)output);
  return 0;
}
