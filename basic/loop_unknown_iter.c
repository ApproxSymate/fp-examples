/*
 * Simple loop example with unknown iteration for numerical precision
 * analysis. Loop breaking analysis (activated with -loop-breaking
 * option) should simply unroll the loop when trip count is unknown.
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>

int loop(int c, int bound) {
  for (int i = 0; i < bound; ++i) {
    c++;
  }
  return c;
}

int main(int argc, char **argv) {
  int c = 0;
  int bound = 5;
  
  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  c = loop(c, bound);

  klee_bound_error(c, 1.3);

  return 0;
}
