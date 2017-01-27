/* 
 * Figure 1 of Benz et al.: A Dynamic Program Analysis to Find
 * Floating-Point Accuracy Problems
 *
 * C program with large error accumulation (the relative error
 * of 0.1 is close the the unit roundoff).
 */
int main() {
  float time = 0.0f;
  int i;
  for (i = 0; i < 20000; i++) {
    time += 0.1f;
  }
  return 0;
}
