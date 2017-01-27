#include <klee/klee.h>
#include <assert.h>

float my_abs(float input) {
  if (input < 0)
    return -(input);
  return input;
}

int main() {

  float x;

  klee_make_symbolic(&x, sizeof(float), "x");

  x = my_abs(x);

  assert(x >= 0);
  return 0;
}
