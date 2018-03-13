#include "all.h"

int getArg(char *s) {
  int ret;
  if (s[0] <= '9' && s[0] >= '0') return stoi(s) - 1;
  ret =  stoi(s, NULL, 18) - 10;
  return ret;
}

void usage(string pname) {
  cout << "Init new game:\n\t" << pname << endl;
  cout << "Get availible moves for chip on c3:\n\t" << pname << " c 3" << endl;
  cout << "Move from c3 to d4:\n\t" << pname << " c 3 e 4" << endl;
}

int dig(){
  Desk desk("dames3-1");
  Solver solver(desk);
  cout << "Dig test command started" << endl;
  solver.Dig(2);
  cout << "Dig test command finished" << endl;
  cout<< solver.SPrint() << endl;
  return 0;
}

int main(int argc, char **argv){
  Desk * desk;

  switch(argc) {
    case 1:
      desk = new Desk();
      desk->Print();
      desk->Save("out.sav");
      delete desk;
      return 0;
    case 2:
      if (string(argv[1]) == "dig") return dig();
      desk = new Desk("out.sav");
      desk->Print();
      printMoveCounts(*desk);
      delete desk;
      return 0;
    case 3:
      desk = new Desk("out.sav");
      printMoveVariants(getArg(argv[2]), getArg(argv[1]), *desk);
      delete desk;
      return 0;
    case 5:
      desk = new Desk("out.sav");
      desk->Move(
        getArg(argv[2]),
        getArg(argv[1]),
        getArg(argv[4]),
        getArg(argv[3])
      );
      desk->Print();
      desk->Save("out.sav");
      delete desk;
      return 0;
    default:
      usage(argv[0]);
      return 1;
  }
}

