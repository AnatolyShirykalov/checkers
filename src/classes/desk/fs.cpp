#include "all.h"

void Desk::Save(string fn) {
  ofstream f;
  f.open(fn);
  f << whiteShouldMove << ' ';
  for (int i = 0; i< 64; i++){
    f << cell[i].state << ' ';
  }
  f.close();
}

Desk::Desk(string fn) {
  ifstream f;

  if (fn == "dames3-1") {
    whiteShouldMove = true;
    cell[0] = cell[2] = cell[4] = PRESENT | WHITE | DAME;
    cell[43] = PRESENT | DAME;
    return;
  }
  f.open(fn);
  f >> whiteShouldMove;
  for (int i = 0; i< 64; i++) {
    f >> cell[i].state;
  }
  f.close();
}


