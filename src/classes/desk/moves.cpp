#include "all.h"

vector<MovesC> Desk::Moves(void) {
  vector <MovesC> ret, withKills;
  MovesC moves;
  int i, j, my;
  bool mustKill = false;
  my = whiteShouldMove ? WHITE : 0;
  for (i = 0; i < 8; i++) {
    for (j = i%2; j < 8; j+=2 ){
      if ((Get(i, j).state & WHITE) != my) continue;
      moves = Moves(i, j);
      mustKill = mustKill || moves.withKills;
      if (mustKill && moves.withKills) withKills.push_back(moves);
      if (!mustKill && !moves.withKills) ret.push_back(moves);
    }
  }
  if (mustKill) return withKills;
  return ret;
}
