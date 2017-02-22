/*
 * First KLEE tutorial: testing a small function
 */

#include <klee/klee.h>

int main() {
    int row, col, inner;
    int aMatrix[3][2] = {{1, 4}, {2, 5}, {3, 6}};
    int bMatrix[2][3] = {{7, 8, 9}, {10, 11, 12}};
    int product[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    klee_make_symbolic(&aMatrix, sizeof(aMatrix), "aMatrix");
    klee_make_symbolic(&bMatrix, sizeof(bMatrix), "bMatrix");

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            for (inner = 0; inner < 2; inner++) {
                product[row][col] += aMatrix[row][inner] * bMatrix[inner][col];
            }
	    klee_output_error(product[row][col]);
        }
    }
    
    return 0;
}

