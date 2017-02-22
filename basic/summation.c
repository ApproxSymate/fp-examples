// From Ramachandran, Pasareanu, and Wahl: Symbolic Execution for
// Checking the Accuracy of Floating-Point Programs

#include <klee/klee.h>

#define INPUT_SIZE 10

void test(int N, float* x) {
  float sum = x[0];
  for (int i = 1; i < N; i++){
    sum = sum + x[i];
    
    // The following replaces
    // assert(Debug.checkAccuracy(sum,0.01f,"a"));
    klee_output_error(sum);
  }
}

int main(int argc, char **argv) {
  float input[INPUT_SIZE];

  klee_make_symbolic(input, INPUT_SIZE * sizeof(float), "input");

  test(INPUT_SIZE, input);
  return 0;
}
