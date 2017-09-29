/*
 * Simple single-iteration loop example for numerical precision
 * analysis. Loop breaking analysis (activated with -loop-breaking
 * option) requires two iterations, but it has to do proper cleaning
 * up when less than two iterations were executed.
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>

int main(int argc, char **argv) {
  int c = 0;

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  for (int i = 0; i < 1; ++i) {
    c++;
  }

  klee_bound_error(c, "c", 1.3);

  return 0;
}
