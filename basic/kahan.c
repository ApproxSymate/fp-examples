// From Ramachandran, Pasareanu, and Wahl: Symbolic Execution for
// Checking the Accuracy of Floating-Point Programs

#include <klee/klee.h>

#define ARRAY_SIZE 10

void test(int N,float* x) {
  float c=0.0f, sum=0.0f, y=0.0f, t=0.0f;
  y=x[0]; t=y; c=t-y; sum=t;
  for (int i = 1; i < N; i++){
    y = x[i] - c; t = sum + y;
    c = (t - sum) - y; sum = t;

    // The klee_output_error below is a replacement of:
    // assert(Debug.checkAccuracy(sum,0.01f,"a"));
    klee_output_error(sum);
  }
}

int main(int argc, char **argv) {
  float input[ARRAY_SIZE];

  klee_make_symbolic(input, sizeof(float) * ARRAY_SIZE, "input");
  
  test(ARRAY_SIZE, input);
}
