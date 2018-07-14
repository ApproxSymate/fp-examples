/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/insertsort/insertsort.c
 */

#include <klee/klee.h>

unsigned int a[11];

int main() {
  int i, j, temp;

  klee_make_symbolic(a, 11 * sizeof(unsigned int), "a");

  i = 2;
  while (i <= 10) {
    j = i;
    while (a[j] < a[j - 1]) {
      temp = a[j];
      a[j] = a[j - 1];
      a[j - 1] = temp;
      j--;
    }
    i++;
  }

  return 1;
}
