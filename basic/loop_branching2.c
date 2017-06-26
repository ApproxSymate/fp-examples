/*
 * Simple loop example for numerical precision analysis, with
 * branching within the loop body. In some paths, in two iterations:
 *
 * 1. There is only one store to c (either in the first or second
 *    iteration). In this case, we assume we do not add more errors to
 *    c after the first store.  
 * 2. There is no store to c. In this case, the error value should be
 *    the same as before entering the loop, that is, equals "c_error".
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>

#define INPUT_SIZE 10

int main(int argc, char **argv) {
  int c = 0, e = 0;

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  for (int i = 0; i < INPUT_SIZE; ++i) {
    char d;

    klee_make_symbolic(&d, sizeof(char), "d");
    
    if (d) {
      c++;
    } else {
      e++;
    }
  }

  // Bound the error
  klee_bound_error(c, 1.3);

  return 0;
}
