/*
 * A simple example with infeasible path for testing -no-branch-check
 * option.
 *
 * Copyright 2018 National University of Singapore
 */
#include <klee/klee.h>

int main(int argc, char **argv) {

  int x;
  int y = 0;

  klee_make_symbolic(&x, sizeof(x), "x");

  if (x > 10) {
    y += 10;
  } else {
    y += 20;
  }

  if (x < 5) {
    y += 30;
  } else {
    y += 40;
  }

  return y;
}
