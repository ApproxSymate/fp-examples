/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int h[24] = { 12,   -44,   -44,  212,   48,    -624, 128,   1448,
              -840, -3220, 3804, 15504, 15504, 3804, -3220, -840,
              1448, 128,   -624, 48,    212,   -44,  -44,   12 };

int accumc[11], accumd[11];

int main(int argc, char **argv) {
  int *ac_ptr, *ad_ptr;
  int *h_ptr, i;
  long xa1 = 0, xa2 = 0, xd, xs;

  klee_make_symbolic(accumc, 11 * sizeof(int), "accumc");
  klee_make_symbolic(accumd, 11 * sizeof(int), "accumd");
  klee_make_symbolic(&xd, sizeof(long), "xd");
  klee_make_symbolic(&xs, sizeof(long), "xs");

  h_ptr = h;
  ac_ptr = accumc;
  ad_ptr = accumd;
  xa1 = (long)xd * (*h_ptr++);
  xa2 = (long)xs * (*h_ptr++);
  for (i = 0; i < 10; i++) {
    xa1 += (long)(*ac_ptr++) * (*h_ptr++);
    xa2 += (long)(*ad_ptr++) * (*h_ptr++);
  }
  xa1 += (long)(*ac_ptr) * (*h_ptr++);
  xa2 += (long)(*ad_ptr) * (*h_ptr++);

  return 0;
}
