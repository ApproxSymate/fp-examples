/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int tqmf[24];

int main(int argc, char **argv) {
  int *tqmf_ptr, *tqmf_ptr1;
  int i;

  klee_make_symbolic(tqmf, 24 * sizeof(int), "tqmf");

  tqmf_ptr = &(tqmf[23]);

  tqmf_ptr1 = tqmf_ptr - 2;
  for (i = 0; i < 22; i++)
    *tqmf_ptr-- = *tqmf_ptr1--;
  return 0;
}
