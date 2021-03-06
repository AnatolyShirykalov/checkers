#include "all.h"

void Desk::Print(void){
  cout << SPrint();
}

/*
 * Мотивация использовать ostringstream в том,
 * чтобы легче было добавлять к итоговой строке
 * числа, не указывая явно в каком формате их добавить.
 * Вместо sprintf(s, "%i", i) пишем oss << i
 */
string Desk::SPrint(void) {
  ostringstream oss;
  oss << "  a b c d e f g h " << endl;
  for(int i = 0; i < 8; i++ ) {
    oss << i+1;
    for (int j = 0; j < 8; j++ ) {
      Chip c = Get(i, j);
      if((i+j)%2) {
        oss << "| ";
      } else  {
        if (c.state & PRESENT) {
          oss << "|" << c.Print();
        } else {
          oss << "|*";
        }
      }
    }
    oss << "|" << endl;
  }
  return oss.str();
}
