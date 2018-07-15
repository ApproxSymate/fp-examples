/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/edn/edn.c
 */

#include <klee/klee.h>

void fir_no_red_ld(const short x[], const short h[], long int y[]) {
  long int i, j;
  long int sum0, sum1;
  short x0, x1, h0, h1;
  for (j = 0; j < 100; j += 2) {
    sum0 = 0;
    sum1 = 0;
    x0 = x[j];
    for (i = 0; i < 32; i += 2) {
      x1 = x[j + i + 1];
      h0 = h[i];
      sum0 += x0 * h0;
      sum1 += x1 * h0;
      x0 = x[j + i + 2];
      h1 = h[i + 1];
      sum0 += x1 * h1;
      sum1 += x0 * h1;
    }
    y[j] = sum0 >> 15;
    y[j + 1] = sum1 >> 15;
  }
}

int main(int argc, char **argv) {
  short a[200];
  short b[200];
  long int output[200];

  klee_make_symbolic(a, 200 * sizeof(short), "a");
  klee_make_symbolic(b, 200 * sizeof(short), "b");

  fir_no_red_ld(a, b, output);
  return 0;
}
