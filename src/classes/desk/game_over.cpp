#include "all.h"

int Desk::GameOver() {
  int blacks = 0, whites = 0;
  for(Chip c : cell) {
    if (c.state & WHITE) whites++;
    else if (c.state & PRESENT) blacks++;
  }
  return blacks == 0 ? 1 : (whites==0 ? WHITE & 1 : 0);
}
