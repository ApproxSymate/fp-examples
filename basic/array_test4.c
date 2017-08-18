/*
 * Copyright 2017 National University of Singapore
 */
#include <klee/klee.h>
#include <stdio.h>

void test_array(short *x);

short arr[5], answer;

int main() {

  klee_make_symbolic(arr, sizeof arr, "__arr16__arr");
  klee_track_error(arr, "__arr16__arr_error");

  test_array(arr);

  klee_bound_error(arr[0], 1.3);
  return 0;
}

void test_array(short *x) {
  // x[0] = (x[1] + x[2]) * (x[3] - x[4]);
  x[0] = x[1] + x[2];
}
