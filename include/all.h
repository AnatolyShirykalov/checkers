#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

#include <vector>
#include <set>


using namespace std;

#ifndef LOG_WHERE_AM_I
#define LOG_WHERE_AM_I cout << __PRETTY_FUNCTION__ << endl << __FILE__ << ":" << __LINE__ << endl
#endif

const int PRESENT = 0x1;
const int WHITE   = 0x2;
const int DAME    = 0x4;
class SimpleDesk;
class Chip {
  public:
    int state;
    Chip();
    Chip(int);
    string Print(void);
    bool operator== (const Chip &c);
    bool operator!= (const Chip &c);
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
    bool whiteShouldMove;

    bool eqShift (const Desk &s);

  public:
    Chip cell[64];
    Desk();
    Desk(string fn);
    Desk(SimpleDesk sd);

    Desk& operator= (const Desk &d);
    bool operator== (const Desk &d);
    bool operator!= (const Desk &d);

    Chip Get(int i, int j);
    void Set(int i, int j, int state);
    void Save(string fn);

    vector<MovesC> Moves(void);
    MovesC Moves(int i, int j);
    void Move(int i0, int j0, int i1, int j1);

    void Print(void);
    string SPrint(void);
};

class Solver {
  class SolverNode;
  class DeskRecord {
    public:
      bool terminate = false;
      Desk desk;
      vector <SolverNode*> recorded;
      DeskRecord(Desk);
      bool operator== (const DeskRecord & dr);
      bool operator!= (const DeskRecord & dr);
  };

  class SolverNode {
    Solver *solver;
    unsigned int deskRecordIndex;
    public:
      DeskRecord& deskRecord();
      SolverNode *same;
      SolverNode *parent;
      vector<SolverNode*> children;
      SolverNode(){};
      SolverNode(Solver *);
      SolverNode(Solver *, unsigned int);
      ~SolverNode();
      string SPrint();
      bool ShouldSkip();
  };
  unsigned int findOrCreateDeskRecord(Desk &desk);
  vector<SolverNode*> nodes;
  public:
    SolverNode root;
    unsigned int levels= 0;

    vector<DeskRecord> deskRecords;
    vector<Desk> Level(unsigned int level);
    Solver(Desk);
    void Dig(unsigned int);
    void AddMove(MovesC, SolverNode*);
    vector<SolverNode*> LevelNodes(unsigned int level);
    string SPrint();
    string Stats();
};


void printVec(vector <int> x);
void printMovVec(vector <int> x);
string printMoveVariant(string from, string to);
void printMoveVariants(int i, int j, Desk& d);
void printMoveCounts(Desk & d);
string prettyCoords(int, int);


