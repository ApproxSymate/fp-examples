// From Ramachandran, Pasareanu, and Wahl: Symbolic Execution for
// Checking the Accuracy of Floating-Point Programs

void test(int N,float[] x){
  float sum = x[0];
  for (int i = 1; i < N; i++){
    sum = sum + x[i];
    assert(Debug.checkAccuracy(sum,0.01f,"a"));
  }
}
