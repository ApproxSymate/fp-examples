/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/edn/edn.c
 */

#include <klee/klee.h>

#define N 100
#define ORDER 50

void fir(const short array1[], const short coeff[], long int output[]) {
  long int i, j, sum;

  for (i = 0; i < N - ORDER; i++) {
    sum = 0;
    for (j = 0; j < ORDER; j++) {
      sum += array1[i + j] * coeff[j];
    }
    output[i] = sum >> 15;
  }
}

int main(int argc, char **argv) {
  short a[200];
  short b[200];
  long int output[200];

  klee_make_symbolic(a, 200 * sizeof(short), "a");
  klee_make_symbolic(b, 200 * sizeof(short), "b");

  fir(a, b, output);
  return 0;
}
