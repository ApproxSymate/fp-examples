/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/crc/crc.c
 */

unsigned short icrc1(unsigned short crc, unsigned char onech) {
  int i;
  unsigned short ans = (crc ^ onech << 8);

  for (i = 0; i < 8; i++) {
    if (ans & 0x8000)
      ans = (ans <<= 1) ^ 4129;
    else
      ans <<= 1;
  }
  return ans;
}

int main(int argc, char **argv) {
  icrc1(255 << 8, (unsigned char)0);
  return 0;
}
