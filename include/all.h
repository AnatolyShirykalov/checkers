#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

const int PRESENT = 0x1;
const int WHITE   = 0x2;
const int DAME    = 0x4;

void printVec(vector <int>);
void printMovVec(vector <int>);

class Chip {
  public:
    int state;
    Chip();
    Chip(int);
    string Print(void);
};

class MovesC {
  public:
    vector <int> moves;
    bool withKills;
    int i, j;
    MovesC();
    MovesC(bool wk);
    MovesC(int I, int J, bool wk);
};

class Desk {
    Chip cell[64];
    bool whiteShouldMove;

  public:
    Desk();
    Desk(string fn);
    Desk& operator= (const Desk &d);

    Chip Get(int i, int j);
    void Set(int i, int j, int state);
    void Save(string fn);

    vector<MovesC> Moves(void);
    MovesC Moves(int i, int j);
    void Move(int i0, int j0, int i1, int j1);

    void Print(void);
    string SPrint(void);
};


void printVec(vector <int> x);
void printMovVec(vector <int> x);
void printMoveVariant(string from, string to);
void printMoveVariants(int i, int j, Desk& d);
