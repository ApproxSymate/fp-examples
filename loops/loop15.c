/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/edn/edn.c
 */

#include <klee/klee.h>

void iir1(const short *coefs, const short *input, long int *optr,
          long int *state) {
  long int x;
  long int t;
  long int n;

  x = input[0];
  for (n = 0; n < 50; n++) {
    t = x + ((coefs[2] * state[0] + coefs[3] * state[1]) >> 15);
    x = t + ((coefs[0] * state[0] + coefs[1] * state[1]) >> 15);
    state[1] = state[0];
    state[0] = t;
    coefs += 4; /* point to next filter coefs  */
    state += 2; /* point to next filter states */
  }
  *optr++ = x;
}

int main(int argc, char **argv) {
  short a[200];
  short b[200];
  long int output[200];

  klee_make_symbolic(a, 200 * sizeof(short), "a");
  klee_make_symbolic(b, 200 * sizeof(short), "b");

  iir1(a, b, &output[100], output);
  return 0;
}
