// Linear controller (Figure 6) of Ramachandran, Pasareanu, and Wahl:
// Symbolic Execution for Checking the Accuracy of Floating-Point
// Programs

public void test(boolean r, float in0){
  if((in0 >= -1.0f) && (in0 <= 1.0f)){
    if(Verify.randomBool()){
      x0=1.0f; x1=1.0f; x2=1.0f; x3=1.0f; x4=1.0f;
    } else{
      x0=0.4250f * x0 + 0.8131f * in0;
      assert(Debug.checkAccuracy(x0,0.01f,"a"));
      x1=0.3167f * x0 + 0.1016f * x1 - 0.4444f *x2 + 0.1807f * in0;
      assert(Debug.checkAccuracy(x1,0.01f,"a"));
      x2=0.1278f * x0 + 0.4444f * x1 + 0.8207f * x2 + 0.0729f * in0;
      assert(Debug.checkAccuracy(x2,0.01f,"a"));
      x3 = 0.0365f * x0 + 0.1270f * x1 + 0.5202f * x2 + 0.4163f * x3 - 0.5714f * x4 + 0.0208f * in0;
      assert(Debug.checkAccuracy(x3,0.01f,"a"));
      x4 = 0.0147f * x0 + 0.0512f * x1 + 0.2099f * x2 + 0.57104f * x3 + 0.7694f * x4 + 0.0084f * in0;
      assert(Debug.checkAccuracy(x4,0.01f,"a"));
    }
  }
}

