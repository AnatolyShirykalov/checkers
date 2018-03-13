#include "all.h"

Chip::Chip(){
  state = 0;
}

Chip::Chip(int newState){
  state = newState;
}

bool Chip::operator==(const Chip &c) {
  return state == c.state;
}

bool Chip::operator!=(const Chip &c) {
  return state != c.state;
}

string Chip::Print() {
  switch(state) {
    case PRESENT | WHITE | DAME: return "\u26c1";
    case PRESENT | WHITE: return "\u26c0";
    case PRESENT | DAME: return "\u26c3";
    case PRESENT: return "\u26c2";
    default: return "";
  }
  return "";
}

