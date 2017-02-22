/* From the article Barr et al. "Automatic Detection of Floating-Point
 * Exceptions", POPL '13, citing Sterbenz as the original
 * source. Computes floating-point average, provably without overflow.
 * The tool reported in Barr et al., however, discovered underflows.
 */
#include <klee/klee.h>

double av1(double x, double y) {
  return (x + y) / 2.0;
}

double av2(double x, double y) {
  return x / 2.0 + y / 2.0;
}

double av3(double x, double y) {
  return x + (y - x) / 2.0;
}

double av4(double x, double y) {
  return y + (x - y) / 2.0;
}

double average(double x, double y) {
  int samesign;

  if (x >= 0) {
    if (y >= 0)
      samesign = 1;
    else
      samesign = 0;
  } else {
    if (y >= 0)
      samesign = 0;
    else
      samesign = 1;
  }
  if (samesign) {
    if (y >= x)
      return av3(x, y);
    else
      return av4(x, y);
  } else 
  return av1(x, y);
}

int main(int argc, char **argv) {
  double in1, in2;

  klee_make_symbolic(&in1, sizeof(in1), "in1");
  klee_make_symbolic(&in2, sizeof(in2), "in2");

  klee_output_error(average(in1, in2));
  
  return 0;
}


