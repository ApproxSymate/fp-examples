/*
 * Simple loop example for numerical precision analysis, with
 * branching within the loop body. This example tests the loop error
 * semantics: Assignment to constant results in error 0. In two
 * iterations before loop is broken:
 *
 * 1. In case both the first and the second stored errors were
 *    non-constant symbolic expressions, then the error amount is: the
 *    first stored error + (trip count - 1) * (second stored error -
 *    first stored error).
 *
 * 2. In case the first stored error was a constant and the second
 *    stored error was a non-constant symbolic expression, then the
 *    resulting error was the symbolic expression.
 *
 * 3. In case the second stored error was a constant, then the
 *    resulting error is the constant.
 *
 * This example would result in four test cases, three of which has 0
 * as the error, as this was the error amount of the constant
 * assignment c = 2, and one of them would be a symbolic expression
 * corresponding to case 1 above. Here, case 2 was not encountered as
 * when c was assigned constant 2 in the first iteration, then the
 * dependent error computation for the second iteration becomes 0 as
 * well.
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>

#define INPUT_SIZE 10

int main(int argc, char **argv) {
  int c = 0;

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_track_error(&c, "c_error");

  for (int i = 0; i < INPUT_SIZE; ++i) {
    char d;

    klee_make_symbolic(&d, sizeof(char), "d");
    
    if (d) {
      c++;
    } else {
      c = 2;
    }
  }

  // Bound the error
  klee_bound_error(c, "c", 1.3);

  return 0;
}
