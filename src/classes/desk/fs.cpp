#include "all.h"

void Desk::Save(string fn) {
  ofstream f;
  f.open(fn);
  for (int i = 0; i< 64; i++){
    f << cell[i].state << ' ';
  }
  f.close();
}

Desk::Desk(string fn) {
  ifstream f;
  f.open(fn);
  for (int i = 0; i< 64; i++) {
    f >> cell[i].state;
  }
  f.close();
}


