#include "all.h"

vector<Desk> Solver::Level(unsigned int level){
  unsigned int i;
  vector <Desk> ret;
  vector <SolverNode*> parents;
  parents = LevelNodes(level);
  for (i = 0; i < parents.size(); i++ ) {
    ret.push_back(parents[i]->deskRecord().desk);
  }
  return ret;
}

/*
 * Конструктор принимает доску
 * хранилище состояний доски инициализируется принятой доской
 * дерево ходов инициализируется принятой доской
 */

Solver::Solver(Desk desk) {
  deskRecords.push_back(DeskRecord(desk));
  root = SolverNode(this, 0);
  levels = 1;
}


/*
 * Solver::LevelNodes(level)
 * Возвращает узлы уровня level
 * Если level == 0, вернётся [root]
 * если level == 1, вернётся root.children
 * если level == 2, вернётся root.children[0].children, ... , root.children[n].children
 *
 * Метод нужен для того, чтобы сделать следующий шаг в анализе ходов,
 * и для того, чтобы печатать текущее состояния дерева на экран
 */
vector <Solver::SolverNode*> Solver::LevelNodes(unsigned int level) {
  unsigned int i, j;
  vector <SolverNode*> parents, children;
  parents.push_back(&root);
  for (i = 0 ; i < level ; i++ ){
    children.clear();
    for (j = 0; j < parents.size(); j++) {
      children.insert(
        children.end(),
        parents[j]->children.begin(),
        parents[j]->children.end()
      );
    }
    parents = children;
  }
  return parents;
}

/*
 * Безопасное добавление записи о состоянии доски
 * в deskRecords. Какие дубликаты не допускаются
 * зависит от реализации Desk::operator==(Desk &);
 */
unsigned int Solver::findOrCreateDeskRecord(Desk &desk) {
  unsigned int i;
  for (i = 0; i < deskRecords.size(); i++)
    if (deskRecords[i].desk == desk) return i;
  deskRecords.push_back(DeskRecord(desk));
  return i;
}
/*
 * Добавить доступные ходы для узла parent в качестве
 * его children в дерево. Если есть новые состояния (deskRecords), то
 * сохранить их.
 */
void Solver::AddMove(MovesC moves, SolverNode *parent) {
  Desk desk;
  SolverNode *sn;
  unsigned int dri;
  LOG_WHERE_AM_I;
  cout << moves.i << ' ' << moves.j << endl;
  for (int m : moves.moves) {
    desk = parent->deskRecord().desk;
    desk.Move(moves.i, moves.j, m / 8, m % 8);
    dri = findOrCreateDeskRecord(desk);
    sn = new SolverNode(this, dri);
    sn->parent = parent;
    parent->children.push_back(sn);
  }
}

void Solver::Dig(unsigned int level) {
  unsigned int i, j;
  Desk desk;
  vector <SolverNode*> parents;
  vector <MovesC> moves;
  if (levels != 1) throw "Cannot dig two times yet";
  parents.push_back(&root);
  for (i = 0; i < level; i++) {
    for (j = 0; j < parents.size(); j++) {
      desk = parents[j]->deskRecord().desk;
      moves = desk.Moves();
      for (MovesC move : moves) {
        cout << endl;
        LOG_WHERE_AM_I;
        cout << move.i << ' ' << move.j << endl;
        AddMove(move, parents[j]);
      }
    }
    levels++;
    parents = LevelNodes(i+1);
  }
}

/*
 * Мотивацию использоваться ostringstream см в Desk::SPrint
 */
string Solver::SPrint() {
  ostringstream oss;
  unsigned int i;
  vector<SolverNode*> nodes;
  for(i = 0; i < levels; i++) {
    oss << "Level " << i << endl;
    nodes = LevelNodes(i);
    for (SolverNode* solverNode : nodes) oss << solverNode->SPrint();
  }
  return oss.str();
}

string Solver::Stats() {
  ostringstream oss;
  oss << "Stats:" << endl;
  oss << deskRecords.size() << " desk records" << endl;
  return oss.str();
}
