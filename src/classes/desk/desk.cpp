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
  return *this;
}
Chip Desk::Get(int i, int j) {
  return cell[8 * i + j];
}
void Desk::Set(int i, int j, int state){
  cell[8 * i + j].state = state;
}

