#include <string>
#include "item.h"


Item::Item(int Iequip,string Iname,int Itype,int Icost,bool Istackable, int Iquantity, bool Iusable) {
  equipLocation = Iequip;
  type = Itype;
  name = Iname;
  cost = Icost;
  stackable = Istackable;
  quantity = Iquantity;
  usable = Iusable;
}


Item::Item() {
  type = -1;
  name = "";
  cost = 0;
}

string Item::getName() {
  return name;
}

int Item::getCost() {
  return cost;
}

/*string Item::getDescription() {
  return description;
}
*/

bool Item::isStackable() {
  return stackable;
}

int Item::getQuantity() {
  return quantity;
}

void Item::displayFull() {

  switch(type) {
  case MIRROR:
    cout<<"This is a small mirror."<<endl;
    break;
  case BELL:
    cout<<"This is a small silver bell."<<endl;
    break;
  case HEALINGSALVE:
    cout<<"This is a vial of healing salve. It will heal 8-12 hit points."<<endl;
    break;
  case LONGSWORD:
    cout<<"This is a longsword."<<endl;
    break;
  case AXE:
    cout<<"This is an axe."<<endl;
    break;
  case DAGGER:
    cout<<"This is a dagger."<<endl;
    break;
  case MACE:
    cout<<"This is a mace."<<endl;
    break;
  case MEDIUMSHIELD:
    cout<<"This is a medium-sized shield. It adds one to armor class."<<endl;
    break;
  case LEATHERARMOR:
    cout<<"This is a suit of leather armor. It adds 2 to armor class."<<endl;
    break;
  case CHAINMAIL:
    cout<<"This is a suit of chain mail. It adds 5 to armor class."<<endl;
    break;
  case PLATEMAIL:
    cout<<"This is a suit of plate mail. It adds 7 to armor class."<<endl;
    break;
  case FULLPLATEMAIL:
    cout<<"This is a suit of full plate mail. It adds 9 to armor class."<<endl;
    break;
  case STAKE:
    cout<<"This is a wooden stake about 10 inches long"<<endl;
    break;

  default:
    // should never get here
    cout<<"Error in displayFull()"<<endl;
    break;
  }
}




/*
need to pass in party, enemies
void Item::useItem() {

  if(usable) {
    Dice d5(5);
    int healAmount = 7 + d5.Roll();
    int mhp;
    switch(type) {

    case HEALINGSALVE:
      mhp = cre->basehp;

      if(healAmount > (mhp - cre->currenthp)) {
	healAmount = (mhp - cre->currenthp);
      }

      cre->currenthp += healAmount;
      cout<<cre->name<<" was healed for "<<healAmount<<" hit points."<<endl;
      break;

    default:
      break;

    } // end switch
  } // end if

  else {
    cout<<"You can't use that!"<<endl;
  }
}
*/
