#include "all.h"

Solver::DeskRecord Solver::SolverNode::deskRecord(){
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
