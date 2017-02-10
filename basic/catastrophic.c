/******************************************************************************
 *  catastrophic.c
 *
 *  Plot fl(x) = (1 - cos x) / x^2 in the interval from
 *  -4 * 10^-8 to 4 * 10^-8. Catastrophic cancellation
 *  leads to extremely inaccurate values in this range.
 *  The true answer is approximately 0.5 for all x values
 *  in this range.
 *
 *  Compile with libm (-lm).
 *
 *  From the original Java version in:
 *  http://introcs.cs.princeton.edu/java/91float/Catastrophic.java.html
 *  Copyright © 2000–2016 Robert Sedgewick and Kevin Wayne.  All
 *  rights reserved.
 *
 *  The issue is also described in the article "Dynamic
 *  Floating-Point Cancellation Detection" by Lam, 
 *  Hollingsworth, and Stewart, Section 4.1.
 *
 ******************************************************************************/

#include <math.h>
#include <stdio.h>

// compute f(x)  = (1 - cos x) / x^2 in floating point
double fl(double x) {
  double a = cos(x);
  double b = 1.0 - a;
  double c = b / (x*x);
  return c;
}

// compute f(x)  = (1 - cos x) / x^2 in floating point
// compiler may produce more accurate results by using more precision than
// IEEE requires
double fl2(double x) {
  return (1.0 - cos(x)) / (x*x);
}

double f(double x) {
  return 2 * sin(x/2) * sin(x/2) / (x*x);
}

int main(int argc, char **argv) { 
  // number of line segments to plot
  int N = 10000;
  
  // x-interval to plot
  double x0 = -4.0e-8;
  double x1 = +4.0e-8;
  
  double vals1[N+1];
  double vals2[N+1];
  double vals3[N+1];
  
  for (int i = 0; i <= N; i++) {
    vals1[i] = fl(x0 + (x1 - x0) * i / N);
    vals2[i] = fl2(x0 + (x1 - x0) * i / N);
    vals3[i] = f(x0 + (x1 - x0) * i / N);
    printf("%d %e17 %e17\n", i, vals1[i], vals3[i]);
  }
}
