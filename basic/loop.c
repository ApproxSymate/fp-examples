/*
 * Simple loop example for numerical precision analysis.
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>

int main(int argc, char **argv) {
  int c = 0;
  int d = 0;

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  for (int i = 0; i < 3; ++i) {
    c++;
    d++;
  }

  // Anything modified within the loop should be made symbolic, when
  // the loop is prematurely exited.
  klee_assert(klee_is_symbolic(d));

  // Bound the error
  klee_bound_error(c, "c", 1.3);

  return 0;
}
