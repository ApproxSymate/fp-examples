/*
 * Copyright 2017 National University of Singapore
 *
 * Author: Himeshi De Silva <himeshidslv@gmail.com>
 */
#include <klee/klee.h>
#include <stdio.h>

int add(int x, int y);

int main() {
  int a, b, answer;
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");
  klee_track_error(&a, "error_a");
  klee_track_error(&b, "error_b");

  answer = add(a, b);

  klee_bound_error(answer, 1.3);
  return 0;
}

int add(int x, int y) { return (x + y); }
