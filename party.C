#include "party.h"


Party::Party(Creature* cre) {
  for(int i = 0;i < MAXSIZEOFPARTY;i++) {
    myParty[i] = NULL;
  }
  myParty[0] = cre;
  sizeOfParty = 1;
  gold = 500;
  reputation = 50;
  notoriety = 0;
}

void Party::Rest() {
  for(int i=0;i < sizeOfParty;i++) {
    myParty[i]->currenthp = myParty[i]->basehp;
  }
}


void Party::addPartyMember(Creature* cre) {
  if(sizeOfParty < MAXSIZEOFPARTY) {
    myParty[sizeOfParty] = cre;
    sizeOfParty++;
  }
  else
    {
      cout<<"Your party is full!"<<endl;
    }
}

void Party::remove(int i) { // removes party member i
  myParty[i-1] = NULL;
    sizeOfParty--;

    // making sure active members are first in array

    int k,j;
    bool partyNotSifted = true;

    while(partyNotSifted) {
      k = 0;
      // looking for contiguous party members
      while((myParty[k] != NULL) && (k<MAXSIZEOFPARTY)) {
	k++;
      }
      j = k + 1;
      // looking for contiguous NULLs
      while((myParty[j] == NULL) && (j<MAXSIZEOFPARTY)) {
	j++;
      }
      if(j != (MAXSIZEOFPARTY-1)) {
	myParty[k] = myParty[j];
	myParty[j] = NULL;
      }
      else { 
	if(myParty[j] != NULL) {
	  myParty[k] = myParty[j];
	  myParty[j] = NULL;
	}
	partyNotSifted = false; 
      }
    } // end sift party
}

int Party::returnGold() {
  return gold;
}


void Party::addToGold(int i) { // i can be negative (buying stuff, money stolen)
  if(i > 0) {
    cout<<"The party has gained "<<i<<" gold."<<endl;
  }
  gold += i;
  if(gold < 0) {
    gold = 0;
  }
}


int Party::getRep() {
  return reputation;
}


void Party::addToRep(int i) {
  reputation += i;
  if(reputation < 0) {
    reputation = 0;
  }
  if(reputation >100) {
    reputation = 100;
  }
}

//notoriety

int Party::getNotoriety() {
  return notoriety;
}


void Party::addToNot(int i) {
  notoriety += i;
  if(notoriety < 0) {
    notoriety = 0;
  }
  if(notoriety >100) {
    notoriety = 100;
  }
}

void Party::displayPartyNames() {
  int i = 0;
  while(i < sizeOfParty) {
    //cout<<"sizeOfParty = "<<sizeOfParty<<endl;
    if(myParty[i] == NULL) {
      cout<<"index "<<i<<" is NULL."<<endl;
    }
    cout<<(i+1)<<")   "<<myParty[i]->name<<"\t\t"<<myParty[i]->currenthp<<"/"<<myParty[i]->basehp<<endl;
    i++;
  }
  return;
}


// this function display party hps, and also accesses inventory
void Party::displayPartyHP() {
  //cout<<"displaying hp"<<endl;
  int i = 0;
  char entry = '!';
  cout<<"     name\tHP\tAC\tthaco\tlevel\txpoints"<<endl;
  while(i < sizeOfParty) {
    //   cout<<"i = "<<i<<endl;
    // cout<<"sizeOfParty = "<<sizeOfParty<<endl;
    if(myParty[i] == NULL) {
      cout<<"I am about to dereference the NULL pointer."<<endl;
    }

    cout<<(i+1)<<")   "<<myParty[i]->name<<"\t"<<myParty[i]->currenthp<<"/"<<myParty[i]->basehp<<"\t"<<myParty[i]->currentac<<"\t"<<myParty[i]->currentThaco<<"\t"<<myParty[i]->level<<"\t"<<myParty[i]->xpoints<<endl;
    i++;
  }
  // now, need to display inventory
  // Would you like to view the inventory of a party member?
  int choice = -1;
  while(choice < 0 || choice > sizeOfParty) {
    cout<<"Enter the number in front of a party \nmember to view their inventory."<<endl;
    cout<<"Enter 0 (zero) to exit."<<endl;
    cin>>choice;
  }
  if(choice != 0 && choice <= sizeOfParty) {
    myParty[choice-1]->myPack->inventory();
    myParty[choice-1]->dispEqItems();
    
    while(entry != '1' && entry != '2' && entry != '3' && entry != '4' && entry != 'e' && entry != 'E' && entry != 'r' && entry != 'R' && entry != 'd' && entry != 'D' && entry != 'q' && entry != 'Q') {
    
    cout<<"You may: \n1) equip an item \n2) remove an equipped item \n3) drop an item from inventory \n4) quit this menu"<<endl;

    string newchoice = "";
    cin>>newchoice;

    entry = newchoice[0];
      if(entry == '1') {entry = 'E';}
      if(entry == '2') {entry = 'R';}
      if(entry == '3') {entry = 'D';}
      if(entry == '4') {entry = 'Q';}

      entry = toupper(entry);
    }

    switch(entry) {


    case 'E': // equip an item
      myParty[choice-1]->equipItem();
      break;

    case 'R': // remove an equipped item
      myParty[choice-1]->unequip();
      break;

    case 'D': // drop an item
      myParty[choice-1]->myPack->drop();
      break;

    case 'Q': // quit
      break;

    default:
      cout<<"Error in dispPartHP"<<endl;
      break;
    }


  }
  else {
  }
  return;
}

void Party::addExp(int exp) {
  int ppm = exp/sizeOfParty; // ppm = points per member

  cout<<"The party has gained "<<exp<<" experience points."<<endl;

  for(int i=0;i < sizeOfParty;i++) {
    myParty[i]->xpoints += ppm;
    myParty[i]->levelUp();
  }
}


// this finds the first thief in the party, and sees if the
// thief can accomplish the set task.

bool Party::findThief(int diff) {
  int thiefIndex = -1;
  bool foundthief = false;
  bool success = false;
  for(int i = 0;i < sizeOfParty && !foundthief;i++) {
    if(myParty[i]->myClass == THIEF) {
      thiefIndex = i;
      foundthief = true;
    }
  }
  if(thiefIndex != -1) {
    success = myParty[thiefIndex]->thiefCan(diff);
  }
  else {
    cout<<"You do not have a thief."<<endl;
    success = false;
  }
  return success;
}