/* 
 * Figure 1 of Benz et al.: A Dynamic Program Analysis to Find
 * Floating-Point Accuracy Problems
 *
 * C program with an error due to insufficient precision
 */

/* float unit roundoff is 0.00000006f */

int main() {
  float e = 0.00000005f;
  float sum = 1.0f;
  int i;
  for (i = 0; i < 5; i++) {
    sum += e;
  }
  /* sum is still 1.0f */
  return 0;  
}

