/* Simplified from:
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/ndes/ndes.c
 */

#define KNOWN_VALUE 1

typedef struct IMMENSE {
  unsigned long l, r;
} immense;
typedef struct GREAT {
  unsigned long l, c, r;
} great;

unsigned long bit[33];

static char ip[65] = { 0,  58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36,
                       28, 20, 12, 4,  62, 54, 46, 38, 30, 22, 14, 6,  64,
                       56, 48, 40, 32, 24, 16, 8,  57, 49, 41, 33, 25, 17,
                       9,  1,  59, 51, 43, 35, 27, 19, 11, 3,  61, 53, 45,
                       37, 29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7 };

unsigned long getbit(immense source, int bitno, int nbits) {
  if (bitno <= nbits)
    return bit[bitno] & source.r ? 1L : 0L;
  else
    return bit[bitno - nbits] & source.l ? 1L : 0L;
}

int main(int argc, char **argv) {
  immense itmp, inp;
  int j, k;

  inp.l = KNOWN_VALUE * 35;
  inp.r = KNOWN_VALUE * 26;

  itmp.r = itmp.l = 0L;
  for (j = 32, k = 64; j >= 1; j--, k--) {
    itmp.r = (itmp.r <<= 1) | getbit(inp, ip[j], 32);
    itmp.l = (itmp.l <<= 1) | getbit(inp, ip[k], 32);
  }

  return 0;
}
