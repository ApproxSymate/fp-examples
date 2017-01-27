/*
 * From Figure 4 of An et al.: FPInst: Floating-Point Error Analysis
 * Using Dyninst (2008)
 */

float ffunc() {
  float a = 42.7f;
  float b = 3.14f;
  return a + b;
}

float ffunc2() {
  float a = 42.7f;
  float b = 3.14f;
  float c = 2.5f;
  return (a + b) * c;
}

float ffunc3() {
  float a = 42.7f;
  float b = 3.14f;
  return a * b;
}

double dfunc() {
  double a = 42.7;
  double b = 3.14;
  return a + b;
}

double mfunc() {
  float a = 42.7f;
  double b = 42.7;
  return a + b;
}

int main() {
  ffunc();
  dfunc();
  ffunc2();
  for (i = 0; i < 3; i++)
    ffunc3();
  mfunc();
}

