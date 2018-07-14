/* Extracted from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/adpcm/adpcm.c
 */

#include <klee/klee.h>

int delay_bpl[6];

int main(int argc, char **argv) {
  int *bli;
  int i;

  klee_make_symbolic(delay_bpl, 6 * sizeof(int), "delay_bpl");

  bli = delay_bpl;
  for (i = 0; i < 6; i++) {
    bli[i] = (int)((255L * bli[i]) >> 8L);
  }
  return 0;
}
