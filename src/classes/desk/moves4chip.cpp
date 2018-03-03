#include "all.h"

MovesC Desk::Moves(int i, int j) {
  MovesC ret(i, j, false), withKills(i, j, true);
  Chip c = Get(i, j);
  int s = c.state, ss, idir, jdir, I, J, last, killed, ii, jj, k;
  switch(s & (PRESENT | DAME)) {
    case PRESENT | DAME:
      for (idir = 1; idir > -2; idir -= 2) {
        for (jdir = 1; jdir > -2; jdir -= 2) {
          last = killed = 0; // чтобы ходить была дальше нельзя, нужно две фишки подряд, первая из которых чужая
          for (k = 1; k < 7; k++) {
            J = j + jdir * k;
            I = i + idir * k;
            if (I < 0 || J < 0 || I > 7 || J > 7) break;
            c = Get(I, J);
            if (!(c.state & PRESENT)) {
              ret.moves.push_back(8*I+J);
              if (last || killed) {
                withKills.moves.push_back(8*I+J);
                killed = PRESENT;
              }
              last = 0;
              continue;
            }
            if ((c.state & WHITE) == (s & WHITE)) break;
            if (last == 0) {
              last = PRESENT;
              continue;
            }
            // здесь last == PRESENT и там была не наша фишка,
            // но тут стоит фишка и не наша.
            // Значит, две подряд чужие
            break;
          }
        }
      }
      break;
    case PRESENT:
      I = -30;
      if (i < 7 && (s & WHITE)) {
        I = i+1;
      } else if (i > 0){
        I = i - 1;
      }
      if (I != -30) {
        for (J = j - 1; J < j + 2; J+=2) {
          if (J < 0 || J > 7) continue;
          c = Get(I, J);
          if (!(c.state & PRESENT)) ret.moves.push_back(8*I + J);
        }
      }
      for (I = i - 2; I < i + 3; I += 4) {
        for (J = j - 2; J < j + 3; J += 4) {
          if (I<0 || J <0 || I > 7 || J > 7) continue;
          ii = (i + I)/2; jj = (j+J)/2;
          ss = Get(ii, jj).state;
          if (!(ss & PRESENT) || (ss & WHITE) == (s & WHITE)) continue;
          if (Get(I, J).state & PRESENT) continue;
          withKills.moves.push_back(8*I+J);
        }
      }
      break;
    default: break;
  }
  if (withKills.moves.size()) return withKills;
  return ret;
}
