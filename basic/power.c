
#include <klee/klee.h>

/* From Botella et al.: Symbolic Execution of Floating-Point
 * Computations
 */
float power(float x, float y)
{
  float w = y;
  float z = 1.0;

  if (y < 0.0)
    w = -y;

  while (w > 0.0) {
    z = z * x;
    w = w - 1.0;
  }

  if (y < 0.0)
    z = 1.0 / z;

  return z;
}

int main() {
  float x;

  klee_make_symbolic(&x, sizeof(x), "x");

  power(x, 10);

  return 0;
}
