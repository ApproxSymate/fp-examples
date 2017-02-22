/* From the article Barr et al. "Automatic Detection of Floating-Point
 * Exceptions", POPL '13, citing GNU Scientific Library (GSL) as the
 * original source. Barr et al. reported that it is possible for the
 * function to thrown division by zero and invalid value exceptions.
 */

#include <math.h>
#include <stdlib.h>
#include <klee/klee.h>

#define GSL_SUCCESS 0;
#define GSL_DBL_EPSILON 2.2204460492503131e-16

typedef struct {
  double val;
  double err;
} gsl_sf_result;

int gsl_sf_bessel_Knu_scaled_asympx_e(const double nu, const double x, gsl_sf_result *result) {
  double mu = 4.0 * nu * nu;
  double mum1 = mu - 1.0;
  double mum9 = mu - 9.0;
  double pre = sqrt(M_PI / (2.0 * x));
  double r = nu / x;
  result->val = pre * (1.0 + mum1 / (8.0 * x) + mum1 * mum9 / (128.0 * x * x));
  result->err = 2.0 * GSL_DBL_EPSILON * fabs(result->val) + pre * fabs(0.1 * r * r * r);
  return GSL_SUCCESS;
}

int main(int argc, char **argv) {
  double nu, x;
  gsl_sf_result *r = malloc(sizeof(gsl_sf_result));
  
  klee_make_symbolic(&nu, sizeof(nu), "nu");
  klee_make_symbolic(&x, sizeof(x), "x");

  gsl_sf_bessel_Knu_scaled_asympx_e(nu, x, r);

  klee_output_error(r->val);
  klee_output_error(r->err);
  
  return 0;
}
