/* The creature class represents a creature.

 */
#include <cstdlib>
#include "creature.h"

// should take name, class, array of equipped stuff
// thaco, ac, hps
Creature::Creature(string cname,int cclass, int cthaco, int cac, int chp, int clevel) {
  name = cname;
  myClass = cclass;
  basethaco = cthaco;
  baseac = cac;
  basehp = chp;
  level = clevel;

  currentThaco = cthaco;
  currentac = cac;
  currenthp = chp;
  currentLevel = clevel;


  invisible = false;
  fireproof = false;
  poisoned = false;
  coldproof = false;

  damageModifier = 0;
  xpoints = 0;
  unarmed = 3;

  myPack = new Backpack();

  for(int i=0;i<EQUIPPED;i++) {
    equipped[i] = NULL;
  }

}

// constructor for monsters
Creature::Creature(int cclass,string cname, int cthaco, int cac, int chp,int cxpoints) {
  name = cname;
  currentac = baseac = cac;
  currentThaco = basethaco = cthaco; 
  basehp = currenthp = chp;
  xpoints = cxpoints;
  unarmed = 3;
  damageModifier = 0;
  myClass = cclass;
  thieving = 5;

  myPack = new Backpack();
  
  for(int i=0;i<EQUIPPED;i++) {
    equipped[i] = NULL;
  }
}

// default constructor
Creature::Creature() {
  myPack = new Backpack();
  
  for(int i=0;i<EQUIPPED;i++) {
    equipped[i] = NULL;
  }
}


// int item will be the index of the item 
// in the backpack
// if the item can be equipped, it will be
// if not, an error message is displayed

void Creature::equipItem() {
  // display backpack
  // select item to equip
  // decide if it is equippable
  // if it is, equip it - else cout error

  bool notfinished = true;

  while(notfinished) {

    int choice = -1;
    int loc;

  while(choice < 1) {
    myPack->inventory();
    cout<<"Equip which item? Enter 0 (zero) to quit."<<endl;
    cin>>choice;
    if(choice == 0) {
      return;
    }
    if(myPack->backpack[choice-1] == NULL) {
      cout<<"That is not a valid choice. Don't you know \nhow to play this game? Is it too hard for \nyou? Perhaps tic-tac-toe would be more \nyour speed."<<endl;
      return;
    }
    //if(choice != 0) {
    loc =  myPack->backpack[choice-1]->equipLocation;
  }
  if(loc < 0) {
    cout<<"You can't equip that!"<<endl;
    return;
  }
  if(equipped[loc] != NULL) {
    cout<<"You already have something equipped in that slot."<<endl;
    return;
  }
  else {
    equipped[loc] =  myPack->backpack[choice-1];
    myPack->backpack[choice-1] = NULL;
    myPack->siftPack();
  }
  
  // need to computer armor class, thaco
  computeBonuses();
  }
  return;
}




void Creature::levelUp() {
  Table myTable;
  Dice d5(5);
  int adjust;
  if(xpoints >= myTable.mytable[myClass][level]) {
    cout<<name<<" has gained a level."<<endl;
    // need to adjust level
    level++;

    // need to adjust basethaco, basehp, and currenthp
    switch(myClass) {
    case FIGHTER:
       basethaco--;
       adjust = d5.Roll();
      basehp += (7 + adjust);
      currenthp += (7 + adjust);
      computeBonuses();
      break;
    case CLERIC:
      if(level % 3 == 0) {
	basethaco--;
      }
      adjust = d5.Roll();
      basehp += (5 + adjust);
      currenthp += (5 + adjust);
      break;
    case THIEF:
      thieving += 5;
      if(level % 3 == 0) {
	basethaco--;
      }
      adjust = d5.Roll();
      basehp += (3 + adjust);
      currenthp += (3 + adjust);
      break;
    case MAGE:
      if(level % 4 == 0) {
	basethaco--;
      }
      adjust = d5.Roll();
      basehp += (1 + adjust);
      currenthp += (1 + adjust);
      break;
    default:
      break;
    }
    // computeBonuses();
  }
  return;
}


//enum {HAND, ARMOR, HELMET, WEAPON, SHIELD, BOOTS, GIRDLE, GAUNTLETS, DUMMY};
// EQUIPPED = 8
void Creature::dispEqItems() {
  cout<<" equipped items: "<<endl;      
  for(int i = 0;i<DUMMY;i++) {
    if (equipped[i] != NULL) {

      switch(i) {

      case HAND:
	cout<<i+1<<") hand:\t"<<equipped[i]->getName()<<endl;
	break;

      case ARMOR:
	cout<<i+1<<") armor:\t"<<equipped[i]->getName()<<endl;
	break;

      case HELMET:
	cout<<i+1<<") helmet:\t"<<equipped[i]->getName()<<endl;
	break;

      case WEAPON:
	cout<<i+1<<") weapon:\t"<<equipped[i]->getName()<<endl;
	break;

      case SHIELD:
	cout<<i+1<<") shield:\t"<<equipped[i]->getName()<<endl;
	break;

      case BOOTS:
	cout<<i+1<<") boots:\t"<<equipped[i]->getName()<<endl;
	break;

      case GIRDLE:
	cout<<i+1<<") girdle:\t"<<equipped[i]->getName()<<endl;
	break;

      case GAUNTLETS:
	cout<<i+1<<") gauntlets:\t"<<equipped[i]->getName()<<endl;
	break;

      default:
	break;
      }
    }

  }
  return;
}

// removes equipped item and puts it in pack
void Creature::unequip() {
  bool packIsFull = myPack->isFull();
  bool dummy;
  if(packIsFull) {
    cout<<"You have no room in your pack to put this item!"<<endl;
  }
  else {
    // need to display equipped items
    // need to allow selection, them put item in pack
    dispEqItems();
  
    //enum {HAND, ARMOR, HELMET, WEAPON, SHIELD, BOOTS, GIRDLE, GAUNTLETS, DUMMY};
  
    cout<<"Enter the number of the slot of the /nitem you wish to unequip. "<<endl;
    cout<<"Enter 0 to exit."<<endl;
    int choice = -1;

    cin>>choice;
    choice--;
    switch(choice) {

    case ARMOR:
      dummy = myPack->insert(equipped[ARMOR]);
      equipped[ARMOR] = NULL;
      break;

    case HAND:
      dummy = myPack->insert(equipped[HAND]);
      equipped[HAND] = NULL;
      break;

    case HELMET:
      dummy = myPack->insert(equipped[HELMET]);
      equipped[HELMET] = NULL;
      break;

    case WEAPON:
      dummy = myPack->insert(equipped[WEAPON]);
      equipped[WEAPON] = NULL;
      break;

    case SHIELD:
      dummy = myPack->insert(equipped[SHIELD]);
      equipped[SHIELD] = NULL;
      break;

    case BOOTS:
      dummy = myPack->insert(equipped[BOOTS]);
      equipped[BOOTS] = NULL;
      break;

    case GIRDLE:
      dummy = myPack->insert(equipped[GIRDLE]);
      equipped[GIRDLE] = NULL;
      break;

    case GAUNTLETS:
      dummy = myPack->insert(equipped[GAUNTLETS]);
      equipped[GAUNTLETS] = NULL;
      break;

    default:
      cout<<"That is not a valid choice."<<endl;
    }
  }
  // need to compute armor class, thaco
}


void Creature::computeBonuses() {
  int acbonus = 0;
  //int hpbonus = 0;
  int thacobonus = 0;
  currentThaco = basethaco;
  currentac = baseac;

  for(int i=0;i < DUMMY;i++) {
    if(equipped[i] != NULL) {
      int temp = equipped[i]->type;
      acbonus += ACBonus(temp);
      thacobonus += thacoBonus(temp);
    }
  }
  currentThaco += thacobonus;
  currentac += acbonus;
}

// AC bonuses are returned as negative numbers
int Creature::ACBonus(int temp) {

  int bonus = 0;
  switch(temp) {

  case MEDIUMSHIELD:
    bonus--;
    break;

  case LEATHERARMOR:
    bonus -= 2;
    break;

  case CHAINMAIL:
    bonus -= 5;
    break;

  case PLATEMAIL:
    bonus -= 7;
    break;

  case FULLPLATEMAIL:
    bonus -= 9;
    break;

  default:
    bonus += 0;
    break;


  }
  return bonus;
}

int Creature::thacoBonus(int temp) {
  return 0;
}

int Creature::AttackQ() {
  int retVal = 5;
  switch(myClass) {
  case FIGHTER:
    retVal = 10;
    break;
  case MAGE:
  case CLERIC:
  case THIEF:
    retVal = 5;
    break;

  default:
    retVal = 5;
    break;
  }
  return retVal;
}


int Creature::TargetQ() {
  int retVal = 5;
  switch(myClass) {
  case FIGHTER:
    retVal = 10;
    break;
  case MAGE:
  case CLERIC:
  case THIEF:
    retVal = 5;
    break;

  default:
    retVal = 5;
    break;
  }
  return retVal;
}


// This function is used to equip enemies
void Creature::equip(Item* item) {

  // need to make sure nothing else is equipped in same slot first
  // need to equip item

  Item* check;
  int slot;
  slot = item->equipLocation;
  //cout<<"slot = "<<slot<<endl;
  check = equipped[slot];
  if(check != NULL) {
    cout<<"You already have something equipped in that slot."<<endl;
  }
  else {
    //cout<<"reached else statement"<<endl;
    equipped[slot] = item;
    item = NULL;
  }
  computeBonuses();
  return;
}

// returns true if thief can accomplish task
bool Creature::thiefCan(int difficulty) {
  bool retVal = false;
  Dice dt(100 - thieving);
  int roll = dt.Roll();
  roll = thieving + roll;
  if(difficulty > roll) {
    retVal = true;
  }
  return retVal;
}