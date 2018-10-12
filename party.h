#ifndef PARTY_H
#define PARTY_H


#include <iostream>
#include <cstdlib>
#include "backpack.h"
#include "creature.h"


class Party {


 private:
  //int MAXSIZEOFPARTY;
  int reputation; // whether party is good or evil - can go from 0 to 100
  int notoriety;  // how well known party is
  int gold;


 public:
  Party(Creature* cre);
  int sizeOfParty;
  Creature* myParty[MAXSIZEOFPARTY];
  void addPartyMember(Creature* cre);
  void remove(int i); // removes party member i
  int returnGold();
  void addToGold(int i);
  int getRep();
  void addToRep(int i);
  int getNotoriety();
  void addToNot(int i);
  void displayPartyNames();
  void displayPartyHP();
  void Rest();
  void addExp(int exp);
  bool findThief(int diff);
};

#endif