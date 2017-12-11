/*
 * Copyright 2017 National University of Singapore
 */
#include <klee/klee.h>
#include <stdio.h>

#define SIZE 5

int main() {
  char arr[SIZE];
  int i;

  klee_make_symbolic(&i, sizeof(i), "i");
  klee_track_error(&i, "error_i");
  
  klee_assume(0 <= i);
  klee_assume(i < 5);
  
  char n = arr[i];
  
  return n;
}

