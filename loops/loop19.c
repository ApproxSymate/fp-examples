/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/fdct/fdct.c
 */

#include <klee/klee.h>

// Other FDCT Parameters
#define CONST_BITS 13
#define PASS1_BITS 2

int main(int argc, char **argv) {
  int lx = 8;
  short int b[64], *block;
  int i;
  int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  int tmp10, tmp11, tmp12, tmp13;
  int z1, z2, z3, z4, z5;
  int constant;

  klee_make_symbolic(b, 64 * sizeof(short), "b");

  block = b;

  for (i = 0; i < 8; i++) {
    tmp0 = block[0] + block[7 * lx];
    tmp7 = block[0] - block[7 * lx];
    tmp1 = block[lx] + block[6 * lx];
    tmp6 = block[lx] - block[6 * lx];
    tmp2 = block[2 * lx] + block[5 * lx];
    tmp5 = block[2 * lx] - block[5 * lx];
    tmp3 = block[3 * lx] + block[4 * lx];
    tmp4 = block[3 * lx] - block[4 * lx];

    /* Even part per LL&M figure 1 --- note that published figure is faulty;
     * rotator "sqrt(2)*c1" should be "sqrt(2)*c6".
     */

    tmp10 = tmp0 + tmp3;
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    block[0] = (tmp10 + tmp11) >> (PASS1_BITS + 3);
    block[4 * lx] = (tmp10 - tmp11) >> (PASS1_BITS + 3);

    constant = 4433;
    z1 = ((tmp12 + tmp13) * constant);
    constant = 6270;
    block[2 * lx] = (z1 + (tmp13 * constant)) >> (CONST_BITS + PASS1_BITS + 3);
    constant = -15137;
    block[6 * lx] = (z1 + (tmp12 * constant)) >> (CONST_BITS + PASS1_BITS + 3);

    /* Odd part per figure 8 --- note paper omits factor of sqrt(2).
     * cK represents cos(K*pi/16).
     * i0..i3 in the paper are tmp4..tmp7 here.
     */

    z1 = tmp4 + tmp7;
    z2 = tmp5 + tmp6;
    z3 = tmp4 + tmp6;
    z4 = tmp5 + tmp7;
    constant = 9633;
    z5 = ((z3 + z4) * constant); /* sqrt(2) * c3 */

    constant = 2446;
    tmp4 = (tmp4 * constant); /* sqrt(2) * (-c1+c3+c5-c7) */
    constant = 16819;
    tmp5 = (tmp5 * constant); /* sqrt(2) * ( c1+c3-c5+c7) */
    constant = 25172;
    tmp6 = (tmp6 * constant); /* sqrt(2) * ( c1+c3+c5-c7) */
    constant = 12299;
    tmp7 = (tmp7 * constant); /* sqrt(2) * ( c1+c3-c5-c7) */
    constant = -7373;
    z1 = (z1 * constant); /* sqrt(2) * (c7-c3) */
    constant = -20995;
    z2 = (z2 * constant); /* sqrt(2) * (-c1-c3) */
    constant = -16069;
    z3 = (z3 * constant); /* sqrt(2) * (-c3-c5) */
    constant = -3196;
    z4 = (z4 * constant); /* sqrt(2) * (c5-c3) */

    z3 += z5;
    z4 += z5;

    block[7 * lx] = (tmp4 + z1 + z3) >> (CONST_BITS + PASS1_BITS + 3);
    block[5 * lx] = (tmp5 + z2 + z4) >> (CONST_BITS + PASS1_BITS + 3);
    block[3 * lx] = (tmp6 + z2 + z3) >> (CONST_BITS + PASS1_BITS + 3);
    block[lx] = (tmp7 + z1 + z4) >> (CONST_BITS + PASS1_BITS + 3);

    /* advance to next column */
    block++;
  }

  return 0;
}
