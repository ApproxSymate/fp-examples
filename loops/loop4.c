/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int delay_bpl[6];

int delay_dltx[6];

int filtez(int *bpl, int *dlt) {
  int i;
  long int zl;
  zl = (long)(*bpl++) * (*dlt++);

  for (i = 1; i < 6; i++)
    zl += (long)(*bpl++) * (*dlt++);

  return ((int)(zl >> 14)); /* x2 here */
}

int main(int argc, char **argv) {
  int szl;

  klee_make_symbolic(delay_bpl, sizeof(int) * 6, "delay_bpl");
  klee_make_symbolic(delay_dltx, sizeof(int) * 6, "delay_dltx");

  szl = filtez(delay_bpl, delay_dltx);
  return 0;
}
