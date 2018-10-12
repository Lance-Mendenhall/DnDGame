#ifndef ITEM_H
#define ITEM_H

#include <cstdlib>
#include "consts.h"
#include "dice.h"
#include "types.h"


class Item {

 private:

  string name;
  int cost;
  bool stackable;
  int quantity;

  //enum {HAND, ARMOR, HELMET, WEAPON, SHIELD, BOOTS, GIRDLE, GAUNTLETS, DUMMY};

 public:
  // constructor for Item class

  Item(int Iequip,             // enumerated type of where can be equipped ,-1 if non-equippable
       string Iname,          // name of item - for display purposes
       int Itype,             // enumerated type of item (LONGSWORD, MIRROR,etc.)
       int Icost,             // cost of item
       bool Istackable,       // if item can stack
       int Iquantity,         // quantity
       bool Iusable);         // is item usable
  // int Iequipable);       
  Item();
  int equipLocation;
  int type;  // enum type of weapon, item, etc.
  bool usable;
  string getName();
  int getCost();
  //string getDescription();
  bool isStackable();
  int getQuantity();
  void displayFull();
  // void useItem(Creature* cre);
};

#endif#ifndef ITEM_H
#define ITEM_H

#include <cstdlib>
#include "consts.h"
#include "dice.h"
#include "types.h"


class Item {

 private:

  string name;
  int cost;
  bool stackable;
  int quantity;

  //enum {HAND, ARMOR, HELMET, WEAPON, SHIELD, BOOTS, GIRDLE, GAUNTLETS, DUMMY};

 public:
  // constructor for Item class

  Item(int Iequip,             // enumerated type of where can be equipped ,-1 if non-equippable
       string Iname,          // name of item - for display purposes
       int Itype,             // enumerated type of item (LONGSWORD, MIRROR,etc.)
       int Icost,             // cost of item
       bool Istackable,       // if item can stack
       int Iquantity,         // quantity
       bool Iusable);         // is item usable
  // int Iequipable);       
  Item();
  int equipLocation;
  int type;  // enum type of weapon, item, etc.
  bool usable;
  string getName();
  int getCost();
  //string getDescription();
  bool isStackable();
  int getQuantity();
  void displayFull();
  // void useItem(Creature* cre);
};

#endif