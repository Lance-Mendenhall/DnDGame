#ifndef TABLE_H
#define TABLE_H

#include <cstdlib>
#include "consts.h"
//#include "types.h"


class Table {

 private:
  enum {FIGHTER, CLERIC, MAGE, THIEF};

 public:
  Table();
  int mytable[4][10];
};

#endif