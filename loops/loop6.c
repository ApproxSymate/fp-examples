/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int delay_bpl[6];

int delay_dltx[6];

int main(int argc, char **argv) {
  int *bli, *dlti;
  int dec_dh, wd2, wd3;
  int i;

  klee_make_symbolic(&dec_dh, sizeof(int), "dec_dh");
  klee_make_symbolic(delay_bpl, 6 * sizeof(int), "delay_bpl");
  klee_make_symbolic(delay_dltx, 6 * sizeof(int), "delay_dltx");

  bli = delay_bpl;
  dlti = delay_dltx;

  for (i = 0; i < 6; i++) {
    if ((long)dec_dh * dlti[i] >= 0)
      wd2 = 128;
    else
      wd2 = -128;
    wd3 = (int)((255L * bli[i]) >> 8L); /* leak factor of 255/256 */
    bli[i] = wd2 + wd3;
  }

  return 0;
}
