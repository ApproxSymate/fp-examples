/*
 * Run with: klee --write-kqueries --math-calls --precision test.bc
 *
 * Author: Himeshi De Silva <himeshidslv@gmail.com>
 */
#include "klee/klee.h"
#include <math.h>

int main() {
  int a, b, c;
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_track_error(&a, "a_err");

  a = sin(a);
  return 0;
}
