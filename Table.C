#include "table.h"


Table::Table() {

  mytable[0][0] = FIGHTER;
  mytable[0][1] = 2000;
  mytable[0][2] = 4000;
  mytable[0][3] = 8000;
  mytable[0][4] = 16000;
  mytable[0][5] = 32000;
  mytable[0][6] = 64000;
  mytable[0][7] = 128000;

  mytable[1][0] = CLERIC;
  mytable[1][1] = 1500;
  mytable[1][2] = 3000;
  mytable[1][3] = 6000;
  mytable[1][4] = 13000;
  mytable[1][5] = 27500;
  mytable[1][6] = 55000;
  mytable[1][7] = 110000;

  mytable[2][0] = MAGE;
  mytable[2][1] = 2500;
  mytable[2][2] = 5000;
  mytable[2][3] = 10000;
  mytable[2][4] = 20000;
  mytable[2][5] = 40000;
  mytable[2][6] = 60000;
  mytable[2][7] = 90000;

  mytable[3][0] = THIEF;
  mytable[3][1] = 1250;
  mytable[3][2] = 2500;
  mytable[3][3] = 5000;
  mytable[3][4] = 10000;
  mytable[3][5] = 20000;
  mytable[3][6] = 40000;
  mytable[3][7] = 70000;
}

