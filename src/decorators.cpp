#include "all.h"

void printVec(vector <int> x) {
  for (int n : x) {
    cout << n/8 << "," << n%8 << "\t";
  }
  cout << endl;
}

void printMovVec(vector <int> x) {
  if (x.size()) {
    cout << "Availible moves:" << endl;
    return printVec(x);
  }
  cout << "Cannot move" << endl;
}


string printMoveVariant(string from, string to) {
  stringstream ss_from(from), ss_to(to);
  ostringstream oss;
  string s_from, s_to;
  const string empty = "         ";
  const string witharrow = "    \u2192    ";
  int i;
  for (i=0; i<9; i++) {
    getline(ss_from, s_from, '\n');
    getline(ss_to, s_to, '\n');
    oss << s_from << (i==4 ? witharrow : empty) << s_to << endl;
  }
  return oss.str();
}

string prettyCoords(int i, int j) {
  stringstream ss;
  ss <<(char)(((char)(j)) + 'a') << i+1;
  return ss.str();
}

void printMoveVariants(int i, int j, Desk& d) {
  Desk d1;
  vector <MovesC> movesV;
  MovesC moves;
  int I, J;
  unsigned int k;
  movesV = d.Moves();
  for (k = 0; k < movesV.size(); k++) {
    if (movesV[k].i == i && movesV[k].j == j) {
      moves = movesV[k];
      break;
    }
  }
  cout << "Current state:" << endl;
  if (moves.moves.size() == 0) cout << "Cannot move" << endl;
  for( int move : moves.moves) {
    I = move / 8;
    J = move % 8;
    cout << "                 Move to "
         << prettyCoords(I, J) << ":" << endl;
    d1 = d;
    d1.Move(i, j, I, J);
    cout << printMoveVariant(d.SPrint(), d1.SPrint());
  }
}

void printMoveCounts(Desk &d) {
  vector <MovesC> movesV;
  MovesC moves;
  unsigned int i;
  movesV = d.Moves();
  for (i = 0; i < movesV.size(); i++) {
    moves = movesV[i];
    cout << prettyCoords(moves.i, moves.j) << ": " << moves.moves.size() << endl;
  }
}
