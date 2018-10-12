#ifndef CREATURE_H
#define CREATURE_H


#include <string>
#include <cstdlib>
#include "dice.h"
#include "consts.h"
#include "item.h"
#include "backpack.h"
#include "table.h"

class Creature {

 private:

 
 public:
  // this constuctor creates party members
  Creature(string cname,int cclass, int cthaco, int cac, int chp, int clevel);
  // this constructor creates enemies
  Creature(int cclass,string cname, int cthaco, int cac, int chp,int cxpoints);
  Creature();

  string name;
  int myClass;
  int basethaco;
  int baseac;
  int basehp;
  int level;
  int currentThaco;
  int currentac;
  int currenthp;
  int currentLevel;
  int damageModifier;
  int xpoints;

  int thaco;
  int ac;
  int unarmed;

  bool invisible;
  bool fireproof;
  bool poisoned;
  bool blessed;
  bool alive;
  bool coldproof;
  bool acidproof;

  int thieving;

  Backpack* myPack;
  Item* equipped[EQUIPPED];
  void equipItem();
  void levelUp();
  void dispEqItems();
  void unequip();
  void computeBonuses();
  int ACBonus(int temp);
  int thacoBonus(int temp);
  int AttackQ();
  int TargetQ();
  void equip(Item* item);
  bool thiefCan(int difficulty);
};


#endif