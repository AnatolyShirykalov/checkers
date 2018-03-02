#include "all.h"

MovesC::MovesC(){;}

MovesC::MovesC(bool wk) {
  withKills = wk;
}

MovesC::MovesC(int I, int J, bool wk) {
  withKills = wk;
  i = I;
  j = J;
}

