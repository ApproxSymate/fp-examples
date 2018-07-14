/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/expint/expint.c
 */

#include <klee/klee.h>

long int foo(long int x) { return (x * x + (8 * x)) << (4 - x); }

int main(int argc, char **argv) {
  int i, ii, nm1;
  long int del, fact, psi, ans;
  long int x;

  klee_make_symbolic(&x, sizeof(long int), "x");

  ans = nm1 != 0 ? 2 : 1000;
  fact = 1;
  for (i = 1; i <= 100; i++) {
    fact *= -x / i;
    if (i != nm1)
      del = -fact / (i - nm1);
    else {
      psi = 0x00FF;
      for (ii = 1; ii <= nm1; ii++)
        psi += ii + nm1;
      del = psi + fact * foo(x);
    }
    ans += del;
  }

  return 0;
}
