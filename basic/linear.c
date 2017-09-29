// Linear controller (Figure 6) of Ramachandran, Pasareanu, and Wahl:
// Symbolic Execution for Checking the Accuracy of Floating-Point
// Programs

#include <klee/klee.h>

void test(int r, float in0) {
  float x0, x1, x2, x3, x4;
  
  if((in0 >= -1.0f) && (in0 <= 1.0f)){
    if (r) {
      x0=1.0f; x1=1.0f; x2=1.0f; x3=1.0f; x4=1.0f;
    } else {
      x0=0.4250f * x0 + 0.8131f * in0;

      // The following replaces
      // assert(Debug.checkAccuracy(x0,0.01f,"a"));
      klee_bound_error(x0, "x0", 0.01);

      x1=0.3167f * x0 + 0.1016f * x1 - 0.4444f *x2 + 0.1807f * in0;

      // The following replaces
      // assert(Debug.checkAccuracy(x1,0.01f,"a"));
      klee_bound_error(x1, "x1", 0.01);

      x2=0.1278f * x0 + 0.4444f * x1 + 0.8207f * x2 + 0.0729f * in0;

      // The following replaces
      // assert(Debug.checkAccuracy(x2,0.01f,"a"));
      klee_bound_error(x2, "x2", 0.01);

      x3 = 0.0365f * x0 + 0.1270f * x1 + 0.5202f * x2 + 0.4163f * x3 - 0.5714f * x4 + 0.0208f * in0;
      
      // The following replaces
      // assert(Debug.checkAccuracy(x3,0.01f,"a"));
      klee_bound_error(x3, "x3", 0.01);

      x4 = 0.0147f * x0 + 0.0512f * x1 + 0.2099f * x2 + 0.57104f * x3 + 0.7694f * x4 + 0.0084f * in0;

      // The following replaces
      // assert(Debug.checkAccuracy(x4,0.01f,"a"));
      klee_bound_error(x4, "x4", 0.01);
    }
  }
}

int main(int argc, char **argv) {
  float input;
  int r;
  
  klee_make_symbolic(&input, sizeof(input), "input");
  klee_make_symbolic(&r, sizeof(r), "r");
  
  test(r, input);
  return 0;
}
