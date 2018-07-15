/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

typedef struct IMMENSE {
  unsigned long l, r;
} immense;
typedef struct GREAT {
  unsigned long l, c, r;
} great;

unsigned long bit[33];

static char ipm[65] = { 0,  40, 8,  48, 16, 56, 24, 64, 32, 39, 7,  47, 15,
                        55, 23, 63, 31, 38, 6,  46, 14, 54, 22, 62, 30, 37,
                        5,  45, 13, 53, 21, 61, 29, 36, 4,  44, 12, 52, 20,
                        60, 28, 35, 3,  43, 11, 51, 19, 59, 27, 34, 2,  42,
                        10, 50, 18, 58, 26, 33, 1,  41, 9,  49, 17, 57, 25 };

unsigned long getbit(immense source, int bitno, int nbits) {
  if (bitno <= nbits)
    return bit[bitno] & source.r ? 1L : 0L;
  else
    return bit[bitno - nbits] & source.l ? 1L : 0L;
}

int main(int argc, char **argv) {
  immense itmp, out1;
  immense *out;
  int j, k;

  out = &out1;

  (*out).r = (*out).l = 0L;
  for (j = 32, k = 64; j >= 1; j--, k--) {
    (*out).r = ((*out).r <<= 1) | getbit(itmp, ipm[j], 32);
    (*out).l = ((*out).l <<= 1) | getbit(itmp, ipm[k], 32);
  }

  return 0;
}
