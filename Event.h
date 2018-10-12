#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>
#include "consts.h"
//#include "types.h"
#include "party.h"
#include "map.h"

class Event {

 private:

  //enum {RAVENSWOOD, FOREST, CAVES};
  //enum {MIRROR, BELL, HEALINGSALVE, LONGSWORD, AXE, DAGGER, MACE, MEDIUMSHIELD, LEATHERARMOR,CHAINMAIL, PLATEMAIL,FULLPLATEMAIL};
  //enum {HAND, ARMOR, HELMET, WEAPON, SHIELD, BOOTS, GIRDLE, GAUNTLETS, DUMMY};
  //enum {FIGHTER, CLERIC, MAGE, THIEF};

  Creature* monsters[NUMMONSTERS];

  int x,y,area;
  Map* myMap;
  bool gameNotOver;
  bool rav11_1,havecat,returnedcat,rav14_9;
  bool haveshield,smithfix;
  bool foundBuffy,foundKelem;
  bool cav1_14,cav13_8,cav14_7,cav9_14,cav8_14,cav6_13,cav0_8;
  bool cav2_9;
 


 public:

  Event();
  Item* createItem(int i);
  void sellItem(Party* p);
  void buy(Party* p,Item* item);
  void bobsShop(Party* p);
  void ArestesArmory(Party* p);
  void cureLightWounds(Party* p);
  void templeSune(Party* p);
  bool occurance(Party* p);
  void combat(Party* p, int start, int end);
  void displayEnemies(int start, int end);
  int damageDone(int weapon);
  void useItem(Creature* cre, Item* item);
  void displayLocation();
  bool canMove(char move);
  void Move(char dir);
  bool weird;
  bool rav2_13;
  bool rav12_3;
  char yesNo();
  bool areaChange(char dir);
  bool for13_2;
  bool girlalive;

};

#endif