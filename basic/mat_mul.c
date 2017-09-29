/*
 * A modified version of the first KLEE tutorial: testing a small
 * function.
 */

#include <klee/klee.h>

int main() {
    int row, col, inner;
    int aMatrix[3][2];
    int bMatrix[2][3];
    int product[3][3];

    for (row = 0; row < 3; row++) {
      klee_track_error(&aMatrix[row][0], "aError0");
      klee_track_error(&aMatrix[row][1], "aError1");
      klee_track_error(&aMatrix[row][2], "aError2");
      for (col = 0; col < 3; col++) {
	klee_track_error(&bMatrix[0][col], "bError0");
	klee_track_error(&bMatrix[1][col], "bError1");
	klee_track_error(&bMatrix[2][col], "bError2");
	for (inner = 0; inner < 2; inner++) {
	  product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];
	}
        klee_bound_error(product[row][col], "product[row][col]", 0.01);
      }
    }
    
    return 0;
}

