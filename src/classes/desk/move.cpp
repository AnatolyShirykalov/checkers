#include "all.h"

void Desk::Move(int i0, int j0, int i1, int j1) {
  int idir, jdir, I, J;
  int s = Get(i0, j0).state;
  Set(i0, j0, 0);
  if (i0 - i1 > 1 || i1 - i0 > 1) {
    idir = i1 - i0 > 0 ? 1 : -1;
    jdir = j1 - j0 > 0 ? 1 : -1;
    for (I = i0, J = j0; I != i1; I += idir, J += jdir) Set(I, J, 0);
  }
  Set(i1, j1, s);
  if (i1 == 0 && !(s & WHITE)) Set(i1, j1, s | DAME);
  if (i1 == 7 && (s & WHITE)) Set(i1, j1, s | DAME);
}
