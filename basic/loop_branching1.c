/*
 * Simple loop example for numerical precision analysis, with
 * branching within the loop body.
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>

#define INPUT_SIZE 10

int main(int argc, char **argv) {
  int c = 0;
  char a[INPUT_SIZE];

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  klee_make_symbolic(a, INPUT_SIZE * sizeof(char), "a");
		     
  for (int i = 0; i < INPUT_SIZE; ++i) {
    if (a[i]) {
      c++;
    } else {
      c += 2;
    }
  }

  // Bound the error
  klee_bound_error(c, 1.3);

  return 0;
}
