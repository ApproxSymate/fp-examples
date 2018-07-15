/* Simplified from
 * http://www.mrtc.mdh.se/projects/wcet/wcet_bench/cover/cover.c
 */

int swi50(int c) {
  int i;
  for (i = 0; i < 50; i++) {
    switch (i) {
    case 0:
      c++;
      break;
    case 1:
      c++;
      break;
    case 2:
      c++;
      break;
    case 3:
      c++;
      break;
    case 4:
      c++;
      break;
    case 5:
      c++;
      break;
    case 6:
      c++;
      break;
    case 7:
      c++;
      break;
    case 8:
      c++;
      break;
    case 9:
      c++;
      break;
    case 10:
      c++;
      break;
    case 11:
      c++;
      break;
    case 12:
      c++;
      break;
    case 13:
      c++;
      break;
    case 14:
      c++;
      break;
    case 15:
      c++;
      break;
    case 16:
      c++;
      break;
    case 17:
      c++;
      break;
    case 18:
      c++;
      break;
    case 19:
      c++;
      break;
    case 20:
      c++;
      break;
    case 21:
      c++;
      break;
    case 22:
      c++;
      break;
    case 23:
      c++;
      break;
    case 24:
      c++;
      break;
    case 25:
      c++;
      break;
    case 26:
      c++;
      break;
    case 27:
      c++;
      break;
    case 28:
      c++;
      break;
    case 29:
      c++;
      break;
    case 30:
      c++;
      break;
    case 31:
      c++;
      break;
    case 32:
      c++;
      break;
    case 33:
      c++;
      break;
    case 34:
      c++;
      break;
    case 35:
      c++;
      break;
    case 36:
      c++;
      break;
    case 37:
      c++;
      break;
    case 38:
      c++;
      break;
    case 39:
      c++;
      break;
    case 40:
      c++;
      break;
    case 41:
      c++;
      break;
    case 42:
      c++;
      break;
    case 43:
      c++;
      break;
    case 44:
      c++;
      break;
    case 45:
      c++;
      break;
    case 46:
      c++;
      break;
    case 47:
      c++;
      break;
    case 48:
      c++;
      break;
    case 49:
      c++;
      break;
    case 50:
      c++;
      break;
    case 51:
      c++;
      break;
    case 52:
      c++;
      break;
    case 53:
      c++;
      break;
    case 54:
      c++;
      break;
    case 55:
      c++;
      break;
    case 56:
      c++;
      break;
    case 57:
      c++;
      break;
    case 58:
      c++;
      break;
    case 59:
      c++;
      break;
    default:
      c--;
      break;
    }
  }
  return c;
}

int main() {
  volatile int cnt = 0;
  cnt = swi50(cnt);
  return cnt;
}
