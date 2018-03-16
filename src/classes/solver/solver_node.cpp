#include "all.h"

bool Solver::SolverNode::ShouldSkip(){
  Desk desk = deskRecord().desk;
  int cs = 0;
  for (Chip chip : desk.cell) {
    if(chip.state & PRESENT) cs++;
  }
  return same != NULL || cs < 4;
}

Solver::DeskRecord& Solver::SolverNode::deskRecord(){
  if(solver == NULL) throw "solver null";
  if(deskRecordIndex>= solver->deskRecords.size()) throw "kaka";
  return solver->deskRecords[deskRecordIndex];
}

Solver::SolverNode::SolverNode(Solver*s){
  solver = s;
  same = NULL;
  parent = NULL;
}

Solver::SolverNode::SolverNode(Solver *s, unsigned int dri) {
  solver = s;
  deskRecordIndex = dri;
  same = NULL;
  parent = NULL;
}

Solver::SolverNode::~SolverNode() {
  unsigned int i;
  for (i = 0; i < children.size(); i++ ){
    delete children[i];
  }
}

string Solver::SolverNode::SPrint() {
  ostringstream oss;
  oss << "SolverNode" << endl;
  oss << children.size() << " children" << endl;
  if (parent != NULL) {
    oss << printMoveVariant(parent->deskRecord().desk.SPrint(), deskRecord().desk.SPrint()) << endl;
  }
  else oss << deskRecord().desk.SPrint() << endl;
  return oss.str();
}

void Solver::SolverNode::Save(string fn) {
  ofstream f;
  f.open(fn);
  Save(f);
  f.close();
}

void Solver::SolverNode::Save(ofstream &f) {
  f << this << " " << parent << " " << deskRecord().desk.GaveOver() << " " << deskRecord().desk.whiteShouldMove;
  for (int i = 0; i< 64; i++) {
    f << " " << deskRecord().desk.cell[i].state;
  }
  f << endl;
  for (SolverNode* snp : children) {
    snp->Save(f);
  }
}
