// From Ramachandran, Pasareanu, and Wahl: Symbolic Execution for
// Checking the Accuracy of Floating-Point Programs

void test(int N,float[] x){
  float c=0.0f, sum=0.0f, y=0.0f, t=0.0f;
  y=x[0]; t=y; c=t-y; sum=t;
  for (int i = 1; i < N; i++){
    y = x[i] - c; t = sum + y;
    c = (t - sum) - y; sum = t;
    assert(Debug.checkAccuracy(sum,0.01f,"a"));
  }
}
