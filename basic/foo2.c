/* From Botella et al.: Symbolic Execution of Floating-Point
 * Computations
 */
#include <klee/klee.h>

float foo2(float x)
{
  float y = 1.0e12, z ;
  
  if (x < 10000.0)
    /* A */
    z = x + y;
  
  if (z > y)
    /* If the execution visited A, then
       there is no solution over real
       of rational, but there is none over
       floating point */
    return x;

  return y;
}

int main(int argc, char **argv) {
  float input;

  klee_make_symbolic(&input, sizeof(input), "input");

  klee_bound_error(foo2(input), "foo2(input)", 0.01);

  return 0;
}
