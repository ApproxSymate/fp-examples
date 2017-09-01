/*
 * Copyright 2017 National University of Singapore
 *
 * This example adds more rigorous testing for array element error
 * expression handling, that it tests loading of element 0, which has
 * the same address as its base array.
 */
#include <klee/klee.h>
#include <stdio.h>

#define SIZE 5

void test_array(char *x);

char arr[SIZE], answer;

int main() {

  /*
     Here we add __arr8__ prefix to declare that this was an array of
     8 bits. This causes array indirection to be used in the output
     error expression.
  */
  klee_make_symbolic(arr, SIZE * sizeof(char), "__arr8__arr");
  klee_track_error(arr, "__arr8__arr_error");

  test_array(arr);
  
  klee_bound_error(arr[2], "arr[2]", 1.3);
  return 0;
}

void test_array(char *x) {
  x[2] = x[0] + x[1];
}
