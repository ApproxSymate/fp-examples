/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#include <klee/klee.h>

typedef struct IMMENSE {
  unsigned long l, r;
} immense;
typedef struct GREAT {
  unsigned long l, c, r;
} great;

static immense icd;

static char ipc2[49] = { 0,  14, 17, 11, 24, 1,  5,  3,  28, 15, 6,  21, 10,
                         23, 19, 12, 4,  26, 8,  16, 7,  27, 20, 13, 2,  41,
                         52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49,
                         39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };

unsigned long bit[33];

unsigned long getbit(immense source, int bitno, int nbits) {
  if (bitno <= nbits)
    return bit[bitno] & source.r ? 1L : 0L;
  else
    return bit[bitno - nbits] & source.l ? 1L : 0L;
}

int main(int argc, char **argv) {
  int i, j, k, l;
  great kn1, *kn;
  kn = &kn1;

  klee_make_symbolic(&icd, sizeof(immense), "icd");
  klee_make_symbolic(bit, sizeof(unsigned long) * 33, "bit");

  for (j = 16, k = 32, l = 48; j >= 1; j--, k--, l--) {
    (*kn).r = ((*kn).r <<= 1) | (unsigned short)getbit(icd, ipc2[j], 28);
    (*kn).c = ((*kn).c <<= 1) | (unsigned short)getbit(icd, ipc2[k], 28);
    (*kn).l = ((*kn).l <<= 1) | (unsigned short)getbit(icd, ipc2[l], 28);
  }

  return 0;
}
