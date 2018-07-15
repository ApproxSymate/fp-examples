/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int tqmf[24];

int h[24] = { 12,   -44,   -44,  212,   48,    -624, 128,   1448,
              -840, -3220, 3804, 15504, 15504, 3804, -3220, -840,
              1448, 128,   -624, 48,    212,   -44,  -44,   12 };

int main(int argc, char **argv) {
  int *tqmf_ptr, *h_ptr, i;
  long xa = 0, xb = 0;

  klee_make_symbolic(tqmf, 24 * sizeof(int), "tqmf");

  h_ptr = h;
  tqmf_ptr = tqmf;
  xa = (long)(*tqmf_ptr++) * (*h_ptr++);
  xb = (long)(*tqmf_ptr++) * (*h_ptr++);
  for (i = 0; i < 10; i++) {
    xa += (long)(*tqmf_ptr++) * (*h_ptr++);
    xb += (long)(*tqmf_ptr++) * (*h_ptr++);
  }
  xa += (long)(*tqmf_ptr++) * (*h_ptr++);
  xb += (long)(*tqmf_ptr) * (*h_ptr++);

  return 0;
}
