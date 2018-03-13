#include "all.h"

Desk::Desk(){
  whiteShouldMove = true;
  for(int i = 0; i < 3; i++) {
    for (int j = i%2; j < 8; j+= 2) {
      Set(i, j, PRESENT | WHITE);
    }
  }

  for(int i = 5; i < 8; i++) {
    for (int j = i%2; j < 8; j+= 2) {
      Set(i, j, PRESENT);
    }
  }
}


Desk& Desk::operator= (const Desk &d) {
  for(int i = 0 ; i < 64; i++) {
    cell[i] = d.cell[i];
  }
  whiteShouldMove = d.whiteShouldMove;
  return *this;
}

bool Desk::operator== (const Desk &d) {
  Desk nd;
  int i;
  if (d.whiteShouldMove == whiteShouldMove) return eqShift(d);
  nd.whiteShouldMove = !d.whiteShouldMove;
  for ( i = 0; i < 64; i++ ) {
    nd.cell[i] = d.cell[i];
    if (d.cell[i].state & PRESENT) nd.cell[i].state ^= WHITE;
  }
  return eqShift(nd);
}

bool Desk::operator!= (const Desk &d) {return !(*this == d);}

bool Desk::eqShift(const Desk &d) {
  bool z, f, s, t;
  int i, u, v;
  if (whiteShouldMove != d.whiteShouldMove) return false;
  for (i = 0, z = f = s = t = true; i < 64 ; i ++ ) {
    u = i / 8;
    v = i % 8;
    z = z && cell[i] == d.cell[i];
    f = f && cell[i] == d.cell[8 * v + u];
    s = s && cell[i] == d.cell[64 - 8 * u - v];
    t = t && cell[i] == d.cell[64 - 8 * v - u];
  }
  return z || f || s || t;
}

Chip Desk::Get(int i, int j) {
  return cell[8 * i + j];
}
void Desk::Set(int i, int j, int state){
  cell[8 * i + j].state = state;
}

