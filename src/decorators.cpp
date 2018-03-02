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


void printMoveVariant(string from, string to) {
  stringstream ss_from(from), ss_to(to);
  string s_from, s_to;
  const string empty = "         ";
  const string witharrow = "    \u2192    ";
  int i;
  for (i=0; i<9; i++) {
    getline(ss_from, s_from, '\n');
    getline(ss_to, s_to, '\n');
    cout << s_from << (i==4 ? witharrow : empty) << s_to << endl;
  }
}

void printMoveVariants(int i, int j, Desk& d) {
  Desk d1;
  MovesC moves;
  int I, J;
  moves = d.Moves(i, j);
  cout << "Current state:" << endl;
  if (moves.moves.size() == 0) cout << "Cannot move" << endl;
  for( int move : moves.moves) {
    I = move / 8;
    J = move % 8;
    cout << "                 Move to "
         <<(char)(((char)(J)) + 'a') << I+1<< ":" << endl;
    d1 = d;
    d1.Move(i, j, I, J);
    printMoveVariant(d.SPrint(), d1.SPrint());
  }
}
