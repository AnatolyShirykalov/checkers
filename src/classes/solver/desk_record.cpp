#include "all.h"

Solver::DeskRecord::DeskRecord(Desk d) {
  desk = d;
}

bool Solver::DeskRecord::operator== (const DeskRecord &dr) {
  return desk == dr.desk;
}

bool Solver::DeskRecord::operator!= (const DeskRecord &dr) {
  return desk != dr.desk;
}
