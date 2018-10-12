#include "event.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>



/* The event class checks to see what is supposed to be happening
at each location in each area. Monsters and NPCs are created The idea
is for none of these to go out of scope until they are "killed."
Also, items are created that serve as treasure.

*/


Event::Event() {
  for(int i=0;i<NUMMONSTERS;i++) {
    monsters[i] = NULL;
  }

  /* monster list
0,1) Vigore,Jarl
2-8) orcs
9,10) Max,Bowie
11-30) kobolds
31-40) goblins
41-50) orcs
51-60) hobgoblins

  */


  weird = false;
  x = 12;
  y = 3;
  area = RAVENSWOOD;

  gameNotOver = true;
  rav2_13 = false;
  rav12_3 = false;
  myMap = new Map();
  rav11_1 = rav14_9 = false;
  havecat = returnedcat = false;
  haveshield = smithfix = false;
  for13_2 = false;
  foundBuffy = foundKelem = false;
  cav1_14 = cav13_8 = cav14_7 = cav9_14 = cav8_14 = cav6_13 = cav0_8 = false;
  cav2_9 = false;
}

bool Event::areaChange(char dir) {

  bool change = false;

  if(area == RAVENSWOOD && x == 0 && y == 7 && dir == 'W') {
    change = true;
    area = FOREST;
    x = 15;
    // y already equals 7
  }

  if(area == FOREST && x == 15 && y == 7 && dir == 'E') {
    change = true;
    area = RAVENSWOOD;
    x = 0;
    // y already equals 7
  }

  if(area == FOREST && x == 0 && (y == 4 || y == 11) && dir == 'W') {
    change = true;
    area = CAVES;
    x = 15;
    // y doesn't need to change  
  }

  if(area == CAVES && x == 15 && (y == 11 || y == 4) && dir == 'E') {
    change = true;
    area = FOREST;
    x = 0;
    // y doesn't need to change
  }

  return change;
}


void Event::Move(char dir) {

  // if area changes, change area, and return else do switch statement


  switch(dir) {
  case 'N': // north
    y++;
    break;
  case 'E': // east
    x++;
    break;
  case 'S': // south
    y--;
    break;
  case 'W': // west
    x--;
    break;
  default:
    cout<<"Error in Event::Move(int dir)"<<endl;
    break;
  }
  return;
}

bool Event::canMove(char move) {
  bool wayClear = myMap->isWayClear(move,x,y,area);
  return wayClear;
}

void Event::displayLocation() {
  cout<<"Area = ";
  switch(area) {
  case RAVENSWOOD:
    cout<<"Ravenswood"<<endl;
    break;
  case FOREST:
    cout<<"Ebon Woods"<<endl;
    break;
  case CAVES:
    cout<<"caves west of Ebon Woods"<<endl;
    break;

  default:
    // should never get here
    break;
  }
  cout<<"x = "<<x<<", y = "<<y<<endl;
  return;
}

Item* Event::createItem(int i) {
  //cout<<"reached createItem()"<<endl;
  Item* item;

  switch(i) {
  case LONGSWORD:
    // cout<<"creating longsword"<<endl;
    item = new Item(WEAPON,"longsword",LONGSWORD,50,false,1,false);
    //cout<<"finished creating longsword"<<endl;
    break;
  case AXE:
    item = new Item(WEAPON,"axe",AXE,50,false,1,false);
    break;
  case DAGGER:
    // cout<<"creating dagger"<<endl;
    item = new Item(WEAPON,"dagger",DAGGER,30,false,1,false);
    //cout<<"finished creating dagger"<<endl;
    break;
  case MACE:
    item = new Item(WEAPON,"mace",MACE,40,false,1,false);
    break;
  case MEDIUMSHIELD:
    item = new Item(SHIELD,"medium shield",MEDIUMSHIELD,20,false,1,false);
    break;
  case LEATHERARMOR:
    item = new Item(ARMOR ,"leather armor",LEATHERARMOR,200,false,1,false);
    break;
  case CHAINMAIL:
    item = new Item(ARMOR ,"chain mail",CHAINMAIL,200,false,1,false);
    break;
  case PLATEMAIL:
    item = new Item(ARMOR ,"plate mail",PLATEMAIL,1000,false,1,false);
    break;
  case FULLPLATEMAIL:
    item = new Item(ARMOR ,"full plate mail",FULLPLATEMAIL,5000,false,1,false);
    break;
  case STAKE:
    item = new Item(WEAPON ,"stake",STAKE,3,false,1,false);
    break;

  default:
    // should never get here
    item = NULL;
    break;
  }
  return item;
}

void Event::combat(Party* p, int start, int end) {

  int numAllies = p->sizeOfParty;
  int numEnemies = (end - start) + 1;
  int numAll = numAllies + numEnemies;
  int counter = 0;
  Dice d20(20);
  int expPts = 0;

  //  cout<<"numAllies = "<<numAllies<<endl;
  //  cout<<"numEnemies = "<<numEnemies<<endl;
  //  cout<<"numAll = "<<numAll<<endl;

  Creature* participants[numAll];
  int AQ[numAll];
  int TQ[numAllies];

  bool battleover = false;
  int roll,damage,result,sum;
  int enemyIndex;
  int needToHit;
  Dice d3(3);


  // need to initialize arrays - friendlies first
  // cout<<"init arrays"<<endl;
  for(int i = 0;i < p->sizeOfParty;i++) {
    AQ[i] = p->myParty[i]->AttackQ();
    TQ[i] = p->myParty[i]->TargetQ();
    participants[i] = p->myParty[i];
  }
 
  // now bad guys - start index = sizeOfParty  end index = numAllies + numEnemies - 1
  //cout<<"setting Q"<<endl;
  for(int i = numAllies;i < numAll;i++) {
    int j = (i - numAllies) + start;
    AQ[i] = monsters[j]->AttackQ();
    //TQ[i] = monsters[j]->AttackQ(); // do monsters need this?
    participants[i] = monsters[j];
  }


  /* cout<<"This battle is brought to you by:"<<endl;
  for(int q = 0;q < numAll;q++) {
    cout<<q<<" "<<participants[q]->name<<endl;
    }*/
  // ok, arrays are set - let's boogie...

  while(!battleover) {
    //    string bob;
    //    cin>>bob;
    /* for(int q = 0;q < numAll;q++) {
    cout<<q<<" "<<participants[q]->name<<" AQ "<<AQ[q];
    if(q < numAllies) {
      cout<<"   TQ "<<TQ[q];
    }
    cout<<endl;
    }*/
    // cout<<"while 1"<<endl;
    cout<<"party's current status"<<endl;
    p->displayPartyNames();
    // need to add up all attack quotients
    int sumAQ = 0;
    //cout<<"while 2"<<endl;
    for(int i = 0;i < numAll;i++) {
      if(participants[i]->currenthp > 0) {
	if(AQ[i] < 0) {
	  AQ[i] = 0;
	}
	sumAQ += AQ[i];
      }
      else {
	AQ[i] = 0;  // dead are not attackers nor targets
	if(i < numAllies) {
	  TQ[i] = 0;
	}
      } // end else
    } // end for

    // ok, let's see who attacks
    //cout<<"while 3"<<endl;
    Dice d(sumAQ);
    result = d.Roll();


    // now, need to find out who that represents
    //cout<<"while 4"<<endl;
    int i = 0;
    sum = 0;
    bool foundAttacker = false;

    while((!foundAttacker) && i < numAll) {
      sum += AQ[i];
      if(result <= sum) { // if this is true, we have found the attacker - participants[i]
	foundAttacker = true;
      } // end if(result < sum)
      else {
	i++;
      } // end else
    } // end while(!foundAttacker...

    if(i >= numAll) {
      cout<<"Adjusting index..."<<endl;
      i--;
    }

    //cout<<"while 5"<<endl;
    // ok, attacker = participants[i] - now who gets attacked?
    // if i < numAllies, good guys attack - otherwise bad guys

    //cout<<" i = "<<i<<"  die roll = "<<result<<"  sumaq = "<<sumAQ<<endl;
    // cin>>bob;

    if(i < numAllies) { // good guys attack
      TQ[i]++;  // increase target quotient for attacker
      AQ[i] -= 3; // decrease attack quotient for attacker
      // need to increase attack quotient for everyone else
      for(int j=0;j<numAll;j++) {
	if(j != i && (participants[j]->currenthp > 0)) {
	  //  cout<<"increasing allies attack Q"<<endl;
	  AQ[j]++;
	}
      }
      // need to pick a target
      //cout<<"while 6"<<endl;
      int choice = -1;
      while(choice < 1 || choice > numEnemies) {
	cout<<"Who will "<<participants[i]->name<<" attack?"<<endl;
	cout<<"Enter the number in front of the enemy."<<endl;
	displayEnemies(start,end);
	cin>>choice;
	enemyIndex = start + choice - 1;
	if(monsters[enemyIndex] != NULL) {
	  if(monsters[enemyIndex]->currenthp < 1) {
	    choice = -1;
	  }
	}
      } // end while
      // need to see if character hits opponent, and calculate damage

      roll = d20.Roll();
      needToHit = (participants[i]->currentThaco) - (monsters[enemyIndex]->currentac);
      //cout<<"while 7"<<endl;
      if(roll >= needToHit) {	// calculate damage
	//cout<<"while 8"<<endl;
	if(participants[i]->equipped[WEAPON] == NULL) {
	  Dice dd(participants[i]->unarmed);
	  damage = dd.Roll();
	}
	else {
	  //cout<<"while 9"<<endl;
	  damage = damageDone(participants[i]->equipped[WEAPON]->type);
	}
	//cout<<"reached calculate damage2"<<endl;
	damage += participants[i]->damageModifier;
	//cout<<"reached calculate damage3"<<endl;
	monsters[enemyIndex]->currenthp -= damage;
	if(monsters[enemyIndex]->currenthp < 1) {
	  expPts += monsters[enemyIndex]->xpoints;  // calc xpoints for kill
	}
	cout<<p->myParty[i]->name<<" rolled a "<<roll<<" and did "<<damage<<" damage to "<<monsters[enemyIndex]->name<<"."<<endl;
	
      } // end if(roll > needToHit
      else {
	cout<<p->myParty[i]->name<<" rolled a "<<roll<<" and missed."<<endl;
      }
      
    } // end if(i < numAllies
    else { // bad guys attack
      //cout<<"while 10"<<endl;
      AQ[i] -= 3; // decrease attack quotient for attacker
      // first other enemy's attack Q
      for(int j=0;j<numAll;j++) {
	if(j != i && (participants[j]->currenthp > 0)) {
	  AQ[j]++;
	}
      }
      // ok, need to pick a target using the target quotient
      // cout<<"while 11"<<endl;
      //summing up target quotients
      int sumTQ = 0;
      for(int k=0;k < numAllies;k++) {
	if(participants[k]->currenthp > 0) {
	  sumTQ += TQ[k];
	}
	else { // dead are not attackers nor targets
	  AQ[k] = 0;
	  TQ[k] = 0;
	} // end else
      } // end for k

      // let's see who gets attacked
      Dice kgg(sumTQ);     // kgg = kill good guys
      result = kgg.Roll();
      //cout<<"while 12"<<endl;
   // now, need to find out who that represents
      int m = 0; // m will be index of attackee
      sum = 0;
      bool foundTarget = false;
      while(!foundTarget && (m < numAllies)) {
	sum += TQ[m];
	if(result <= sum) { // if true, have found target
	  foundTarget = true;
	} // end if
	else {
	  m++;
	}
      } // end while attacker is participants[i], target is participants[m]
      roll = d20.Roll();
      needToHit = (participants[i]->currentThaco) - (participants[m]->currentac);
      // cout<<"while 13"<<endl;
      if(roll >= needToHit) {
	//cout<<"while 14"<<endl;
	  //calculate damage
	  if(participants[i]->equipped[WEAPON] == NULL) {
	    Dice dd(participants[i]->unarmed);
	    damage = dd.Roll();
	  }
	  else {
	    // cout<<"while 15"<<endl;
	  damage = damageDone(participants[i]->equipped[WEAPON]->type);
	  damage += participants[i]->damageModifier;
	  participants[m]->currenthp -=damage;

	  cout<<participants[i]->name<<" rolled a "<<roll<<" and did "<<damage<<" damage to "<<participants[m]->name<<"."<<endl;
	  }
      }
      else {
	//cout<<"while 16"<<endl;
	//cout<<"i = "<<i<<", m = "<<m<<endl;
	cout<<participants[i]->name<<" attacked "<<participants[m]->name<<"."<<participants[i]->name<<" rolled a "<<roll<<" and missed."<<endl;
      }
    } // end else enemies attack
    // need to see if either side is victorious

    bool partyToast = true;
    bool monstersToast = true;

    for(int n = 0;(n < p->sizeOfParty) && (partyToast);n++) {
      if(participants[n]->currenthp > 0) {
	partyToast = false;
      }
    }
    for(int q = start;(q <= end) && monstersToast;q++) {
      if(monsters[q]->currenthp > 0) {
	monstersToast = false;
      }
    }

    if(monstersToast) {
      cout<<"Your party is victorious!"<<endl;
      p->addExp(expPts);
      battleover = true;
      for(int z = start;z <= end;z++) {
	if(monsters[z]->currenthp < 1) {
	  delete monsters[z];
	}
	else {
	  monsters[z]->currenthp = monsters[z]->basehp;
	}
      }
    }
    if(partyToast) {
      cout<<"Your party was defeated. "<<endl;
      gameNotOver = false;
      battleover = true;
      for(int z = 0;z < NUMMONSTERS;z++) {
	delete monsters[z];
      }
      for(int z = 0;z < numAllies;z++) {
	delete participants[z];
      }

    }


  } // ends while !battleover
  // ok, battle over, cleaning up


}


void Event::useItem(Creature* cre, Item* item) {
  Dice d5(5);
  int healAmount = 7 + d5.Roll();
  int mhp;

  switch(item->type) {
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

}

int Event::damageDone(int weapon) {
  int damage;
  Dice d8(8);
  Dice d6(6);
  Dice d4(4);

  switch(weapon) {

  case LONGSWORD: // 1d8
    damage = d8.Roll();
    break;

  case AXE:  // 1d8
    damage = d8.Roll();
    break;

  case MACE:  // 1d6+1
    damage = d6.Roll() + 1;
    break;

  case DAGGER: //1d4
    damage = d4.Roll();
    break;

  case STAKE: //1d4
    damage = d4.Roll();
    break;




  default:
    cout<<"Error in damage function."<<endl;
    cout<<"Weapon used was of type "<<weapon<<endl;
    damage = 1;
    break;
  }
  return damage;
}

void Event::displayEnemies(int start, int end) {

  // should be from 1 to end - start + 1
  int numMonsters = end - start + 1;

  for(int i=start;i <= end; i++) {
    if(monsters[i]->currenthp > 0) {
      cout<<" "<<(i - start + 1)<<") "<<monsters[i]->name<<"\t"<<monsters[i]->currenthp<<"/"<<monsters[i]->basehp;

      if(monsters[i]->equipped[WEAPON] != NULL) {
	cout<<"\t"<<monsters[i]->equipped[WEAPON]->getName();
      }

      if(monsters[i]->equipped[ARMOR] != NULL) {
	cout<<"\t"<<monsters[i]->equipped[ARMOR]->getName();
      }


      cout<<"\t"<<monsters[i]->currentac<<endl;
    }
  }
}


// first, we find who is selling an item
// then, we view their backpack - NOT their equipped items
// we compute the selling price, which should not exceed the purchase price.
// after giving the price, we give the option of selling or not
// selling price = price 

void Event::sellItem(Party* p) {

  cout<<"party gold: "<<p->returnGold();
  cout<<"Who wants to sell something? Enter a number."<<endl;
  p->displayPartyNames();
  int seller,itemnum;
  cin>>seller;
  if(seller < 0 || seller > p->sizeOfParty) {
    cout<<"Get out of here, you imbecile!"<<endl;
    return;
  }
  cout<<"Enter the number of the item you want to sell."<<endl;
  //p->myPacks[seller-1]->inventory();
  p->myParty[seller-1]->myPack->inventory(); // displays inventory of party member
  cin>>itemnum;
  //int price = p->myPacks[seller-1]->backpack[itemnum-1]->getCost();
  int price = p->myParty[seller-1]->myPack->backpack[itemnum-1]->getCost();

  int rep = p->getRep();
  int noto = p->getNotoriety();

  int sellingprice = (price/4) + (((noto * (rep-50))/1000) * price);
  if(sellingprice > price) {
    sellingprice = price;
  }
  cout<<"I will give you "<<sellingprice<<" gold for that. Deal?"<<endl;
  char answer;
  cin>>answer;
  answer = toupper(answer);
  switch(answer) {
  case 'N':
    cout<<"Too bad. Anything else?"<<endl;
    break;
  case 'Y':
    cout<<"OK then! Anything else?"<<endl;
    p->addToGold(sellingprice);
    //p->myPacks[seller-1]->drop(itemnum-1);
    p->myParty[seller-1]->myPack->dropItem(itemnum-1);
    break;
  default:
    cout<<"Huh???"<<endl;
    break;
  }
  return;
}

void Event::buy(Party* p,Item* item) {
  // need to check if enough gold
  // need to ask who is buying the item
  // need to make sure their pack is not full
  // need to insert item in their pack

  bool canbuy = true;
  int whobuys;
  int gold = p->returnGold();
  int cost = item->getCost();
  if(cost <= gold) {
    cout<<"Who will buy the "<<item->getName()<<"?"<<endl;
    p->displayPartyNames();
  }
  else {
    cout<<"You don't have enough money for that!"<<endl;
    delete item;
    return;
  }
  cin>>whobuys;
  if((whobuys < 0) || (whobuys > p->sizeOfParty)) {
    cout<<"Try hitting the button sober next time..."<<endl;
    delete item;
  }
  else {
    //canbuy = p->myPacks[whobuys+1]->insert(item);
    cout<<"reached insert item"<<endl;
    canbuy = p->myParty[whobuys-1]->myPack->insert(item);
    cout<<"passed insert item"<<endl;
    p->addToGold(-1*cost);
  }
  if(!canbuy) {
    delete item;
  }
  return;
}


void Event::cureLightWounds(Party* p) {
  // need to check if enough gold
  // need to ask who is buying healing

  Dice d5(5);
  int healAmount = 7 + d5.Roll();
  bool canbuy = true;
  int whobuys;
  int gold = p->returnGold();
  if (gold > CLWCOST) {
    cout<<"Who will purchase the healing?"<<endl;
    p->displayPartyNames();
  }
  else {
    cout<<"May you be blessed with more material comforts. Goodbye."<<endl;
    return;
  }
  cin>>whobuys;
  if((whobuys < 0) || (whobuys > p->sizeOfParty)) {
    cout<<"May the mentally challenged be blessed as well. "<<endl;
    return;
  }
  else {
     p->addToGold(-1*CLWCOST);
    // need to heal someone

     int mhp = p->myParty[whobuys - 1]->basehp;
    //new code

    if(healAmount > mhp - p->myParty[whobuys-1]->currenthp) {
      healAmount = mhp - p->myParty[whobuys-1]->currenthp;
    }
    cout<<p->myParty[whobuys-1]->name<<" was healed for "<<healAmount<<" hit points."<<endl;
    if(healAmount == 0) {
      cout<<"You know, you are wasting your money. However, \nwe thank you for the donation..."<<endl;
    }
  }
  return;
}



void Event::bobsShop(Party* p) {
  // want to sell mirror, bell, and healing salves
  cout<<"Hello! I'm Bob!"<<endl;

  char choice;

  // need to make sure party has enough gold
  // need to make sure party member has room to carry item

  do {
    cout<<"What can I get for you?"<<endl;
    // displaying wares
    cout<<"1) mirror             10gp"<<endl;
    cout<<"2) bell               10gp"<<endl;
    cout<<"3) salve of healing   10gp"<<endl;
    cout<<"4) sell item from inventory"<<endl;
    cout<<"5) leave the store"<<endl;
    cout<<"Gold: "<<p->returnGold()<<endl;

    cin>>choice;

    Item* myItem = new Item();

    switch(choice) {


    case '1':
      delete myItem;
      myItem = new Item(-1, "mirror", MIRROR, 10, false,1,false);
      // need to check if enough gold
      // need to ask who is buying the item
      // need to make sure their pack is not full
      // need to insert item in their pack

      buy(p,myItem);

      break;
    case '2':
      myItem = new Item(-1, "bell", BELL, 10, false,1,false);
      buy(p,myItem);
      break;
    case '3':
      myItem = new Item(-1, "healing salve", HEALINGSALVE, 10, true,1,true);
      buy(p,myItem);
      break;
    case '4':
      sellItem(p);
      break;
    case '5':
      cout<<"Come back real soon!"<<endl;
      break;

    default:
      cout<<"I'm sorry; I'm all out of those..."<<endl;
    }

  } while(choice != '5');
}

void Event::ArestesArmory(Party* p) {

  // want to sell weapons, armor, and shields
  cout<<"Hello! I'm Arestes! Don't touch anything unless you mean to buy!"<<endl;

  int choice;

  // need to make sure party has enough gold
  // need to make sure party member has room to carry item

  do {
    cout<<"Are you interested in anything, or just wasting your time and mine?"<<endl;
    // displaying wares
    cout<<"1) long sword         50gp"<<endl;
    cout<<"2) axe                50gp"<<endl;
    cout<<"3) dagger             30gp"<<endl;
    cout<<"4) mace               40gp"<<endl;
    cout<<"5) medium shield      20gp"<<endl;
    cout<<"6) leather armor      30gp"<<endl;
    cout<<"7) chain mail         50gp"<<endl;
    cout<<"8) plate mail        100gp"<<endl;
    cout<<"9) full plate mail   150gp"<<endl;
    cout<<"10) sell item from inventory"<<endl;
    cout<<"11) leave the store"<<endl;
    cout<<"Gold: "<<p->returnGold()<<endl;

    cin>>choice;

    Item* myItem = new Item();

    switch(choice) {


    case 1:
      myItem = new Item(WEAPON, "long sword", LONGSWORD, 50, false,1,false);

      // need to check if enough gold
      // need to ask who is buying the item
      // need to make sure their pack is not full
      // need to insert item in their pack

      buy(p,myItem);

      break;
    case 2:
      myItem = new Item(WEAPON, "axe", AXE, 50, false,1,false);
      buy(p,myItem);
      break;
    case 3:
      myItem = new Item(WEAPON, "dagger", DAGGER, 30, false,1,false);
      buy(p,myItem);
      break;
    case 4:
      myItem = new Item(WEAPON, "mace", MACE, 40, false,1,false);
      buy(p,myItem);
      break;
    case 5:
      myItem = new Item(SHIELD, "medium shield", MEDIUMSHIELD, 20, false,1,false);
      buy(p,myItem);
      break;
    case 6:
      myItem = new Item(ARMOR, "leather armor",LEATHERARMOR, 30, false,1,false);
      buy(p,myItem);
      break;
    case 7:
      myItem = new Item(ARMOR, "chain mail",CHAINMAIL, 50, false,1,false);
      buy(p,myItem);
      break;
    case 8:
      myItem = new Item(ARMOR, "plate mail",PLATEMAIL, 100, false,1,false);
      buy(p,myItem);
      break;
    case 9:
      myItem = new Item(ARMOR, "full plate mail",FULLPLATEMAIL, 150, false,1,false);
      buy(p,myItem);
      break;
    case 10:
      sellItem(p);
      break;
    case 11:
      cout<<"Come back real soon!"<<endl;
      break;

    default:
      cout<<"I'm sorry; I'm all out of those..."<<endl;
    }

  } while(choice != 11);
}

void Event::templeSune(Party* p) {
  // want to sell healing
  cout<<"Good day to you, travelers. I am Priestess Novicia."<<endl;

  int choice;

  // need to make sure party has enough gold
  // need to make sure party member has room to carry item

  do {
    cout<<"How may I be of assistance?"<<endl;
    // displaying wares
    cout<<"1) cure light wounds     10gp"<<endl;
    cout<<"2) leave the store"<<endl;
    cout<<"Gold: "<<p->returnGold()<<endl;

    cin>>choice;

    switch(choice) {
      Item* myItem;

    case 1:
      cureLightWounds(p);
      break;
    case 2:
      cout<<"May Sune smile upon you this day. Go in peace."<<endl;
      break;

    default:
      cout<<"I'm sorry; Perhaps you should seek elsewhere..."<<endl;
    }

  } while(choice != 2);
}

char Event::yesNo() {
  string entry = "";
  char option = 'z';
  while(option != '1' && option !='2' && option != 'Y' && option != 'N') {
    cout<<" 1) Yes."<<endl;
    cout<<" 2) No. "<<endl;
    cin>>entry;
    option = entry[0];
    option = toupper(option);
    if(option == '1') {
      option = 'Y';
    }
    if(option == '2') {
      option = 'N';
    }
  } // end while
  return option;
}

bool Event::occurance(Party* p) {
  Item* myitem = new Item();
  string entry = " ";
  char option = 'f';
  Creature* ppm = new Creature(); // potential party member
  // first dealing with the x coordinate
  Dice d100(100);
  int dieroll;
  bool success;


  switch(x) {
  case 0:
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	cout<<"You notice an entrance to a cave in the hills to the west."<<endl;
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You are standing at the far east border of Ravenswood."<<endl;
	cout<<"To the west lie the Ebon Woods."<<endl;

	break;
      case FOREST:
	break;
      case CAVES:
	cout<<"There is a glow to the north. It appears to be
a small band of hobgoblins."<<endl;
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav0_8) {
	  cav0_8 = true;
	  cout<<"The hobgoblins attacks!"<<endl;
	  
	  for(int i=0;i < 10;i++) {
	    monsters[i+51] = new Creature(FIGHTER,"hobgoblin ",19,10,10,300);
	    
	    myitem = createItem(LONGSWORD);
	    monsters[i+51]->equip(myitem);
	    myitem = createItem(CHAINMAIL);
	    monsters[i+51]->equip(myitem);
	  }
	  combat(p,51,60);
	  if(gameNotOver) {
	    dieroll = d100.Roll();
	    dieroll *= 5;
	    p->addToGold(dieroll);
	  }
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	cout<<"You notice an entrance to a cave in the hills to the west."<<endl;
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 1:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:

	if(!cav1_14) {
	  cav1_14 = true;
	  dieroll = d100.Roll();
	  cout<<"As you enter this chamber, two men rise from their chairs and 
draw their weapons. One glares at you in amazement. \"You can't have
found us. We were promised protection!\"
     \"Shut up you fool!\" retorts the other. They obviously did
find us!\" At that, both men draw weapons and start maneuvering for
position..."<<endl;


	  monsters[9] = new Creature(FIGHTER,"Bowie",15,8,20,600);
	  monsters[10] = new Creature(FIGHTER,"Max",14,8,20,600);
	  
	  myitem = createItem(LONGSWORD);
	  monsters[9]->equip(myitem);
	  myitem = createItem(CHAINMAIL);
	  monsters[9]->equip(myitem);

	  myitem = createItem(AXE);
	  monsters[10]->equip(myitem);
	  myitem = createItem(CHAINMAIL);
	  monsters[10]->equip(myitem);

	  combat(p,9,10);

	  if(gameNotOver) {

	    cout<<"Both men are dead - and with them, some of your questions
remain unanswered. Who was behind this plot? One of the men spoke
of promised protection - what did he mean? Answers will have to wait,
however."<<endl;

	    if(dieroll < 75) {
	      girlalive = true;
	      cout<<"You see a half-starved girl peeking at you from
around the corner. The men were apparently using a nearby
undergound stream as a privy. You tell the girl you are taking
her to her father and she begins to cry.
     \"Thank you,\" she whispers, as you start the journey
back to Ravenswood."<<endl;
	    }
	    else {
	      girlalive = false;
	      cout<<"You look around for the girl. Did she escape?
As you search, you smell a pungent odor from a nearby
tunnel. Your worst fears come to pass as you discover
the body of a small blonde girl, obviously dead for days,
still clutching a stuffed unicorn. You wrap up the body as best you 
can, and start the journey back to Ravenswood. "<<endl;

	    }
	  } // if gameNotOver
	  area = RAVENSWOOD;
	  x = 0;
	  y = 7;

	} // if cav1_14
     
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
            
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 2:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	cout<<"You have entered Arestes Armory."<<endl;
	ArestesArmory(p);
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	cout<< "To the north is Bob's Hock Shop and Transmission Repair."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You have entered Bob's Hock Shop."<<endl;
	bobsShop(p);
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"To the north is the Temple of Sune. "<<endl;
	cout<<"Healing can be purchased there."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You have entered the Temple of Sune."<<endl;
	templeSune(p);
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav2_9) {
	  cav2_9 = true;
	  cout<<"The hobgoblins were guarding a small chest. It is locked - perhaps
a thief could open it."<<endl;
	  // need to check for thief
	  // then get thieving
	  // see if can be opened

	  success = p->findThief(50);
	  if(success) {
	    cout<<"Your thief opened the chest. It contains some gold, and
one useful item. The item might be created later."<<endl;
	    p->addExp(800);
	    p->addToGold(2000);
	  }
	  else {
	    cout<<"You cannot open it."<<endl;
	  }
	}

	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	if(!rav2_13) {
	  cout<<"To the north is an abandoned building. However, you see a faint light through the window, and you thing you hear voices as well."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	if(!rav2_13) {
	  rav2_13 = true;
	  cout<<"You barge in and find 2 men arguing. They quickly draw weapons and attack you!"<<endl;
	  //need to create monsters here
	  //cout<<"Creating bad guys"<<endl;
	  monsters[0] = new Creature(FIGHTER,"Vigore",19,8,8,200);
	  monsters[1] = new Creature(FIGHTER,"Jarl",19,8,8,200);
	  
	  // cout<<"Creating equipment"<<endl;
	  myitem = createItem(LONGSWORD);
	  //cout<<"created longsword"<<endl;
	  monsters[0]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[0]->equip(myitem);
	  
	  myitem = createItem(DAGGER);
	  monsters[1]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[1]->equip(myitem);

	  // cout<<"calling combat"<<endl;
	  combat(p,0,1);

	  // finishing up...
cout<<"Vigore is dead and Jarl is dying. Jarl whispers, \"...knew 
it was a bad idea to get involved with those guys.\"
     \"What guys?\" you ask. \"Come on, you don't have anything
to gain by holding back...\"
     \"Two men...took girl...to cave...west...\" He stops breathing."<<endl;
	}
	else {
	  cout<<"This building is abandoned. You see no trace of Vigore and Jarl. Someone has removed the bodies."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav1_14) {
	  cout<<"You see a light flickering in a chamber to the west."<<endl;
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 3:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	cout<<"Directly to the west is a doorway. Over the door \na sign read \"Arestes Weapon Emporium.\""<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	if(!foundBuffy) {
	  foundBuffy = true;
cout<<"     You encounter a small blonde woman holding what appears to be
a tent stake. 
     \"Hello,\" you say, as she eyes you suspiciously. 
     \"Let me guess,\" she says, examining your attire. \"There's a big
SCA convention going on here, right?\"
     \"SCA...?\"
     \"Never mind...just seen a lot of people in funny costumes 
around here lately.\"
     \"Funny...costumes...?\"
     \"Never mind. I'm B...I'm Anne. What are you doing out here anyway?\"
     \"The mayor's daughter has been kidnapped. We're looking for her - and
for the people who did this.\"
     \"I don't like mayors much. They tend to be real snakes...but, you're
here to get the bad guys, right? You can tag along, but don't get in my
way, ok?\""<<endl;
 cout<<"Will you let Anne join the party?"<<endl;
 option = yesNo();
 if(option == 'Y') {
   ppm = new Creature("Anne",FIGHTER,10,-3,30,4);
   ppm->damageModifier = 10;

   myitem = createItem(STAKE);
   ppm->equip(myitem);
   p->addPartyMember(ppm);
   cout<<"Anne has joined your party."<<endl;
 }
 else {
   cout<<"\"Ok,\" she says as she walks away. "<<endl;
 }
	}
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;

      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;    

  case 4:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;    


  case 5:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:

	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"To the north you hear clanging, such as a blacksmith at work."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
if(haveshield && !smithfix) {
	  cout<<"You explain to the smith about the old man and \nthe shield. He smiles and takes the shield - apparently \nhe is aware of the old man's eccentricity. As \nhe hammers the shield into its original shape, \nhe explains. \"His name is Nate Gunderson. He claims he used to be \nsome sort of adventurer. He spends a lot of time \nmooning over some beat-up old weapons, and he \nlikes to tell stories about horrible monsters he almost \nslew, and fantastic treasures he almost gained. He's a little \ntouched in the head, but he's harmless.\""<<endl;
	  cout<<"    You ask, if he's just crazy, why are you repairing his shield for free?"<<endl;
	  cout<<"The smith hands you the repaired shield and says, \"I'll be \nold some day.\"\n    With that, he goes back to work."<<endl;
	  smithfix = true; 
	}
	else {
	  cout<<"You enter a smithy and see a well-muscled man forging a shield. He looks up at you, smiles, then goes back to work."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	if(!returnedcat) {
	  cout<<"A residence lies to the north. You hear crying from inside."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	if(!havecat && !returnedcat) {
	  cout<<"The door is ajar. Inside, a small girl is crying. \nShe is holding a ball of yarn, and continues \nweeping, occasionally muttering 'poor kitty.'"<<endl;
	}
	else if(havecat && !returnedcat) {
	  cout<<"You dump the cat out of the sack. The feline \nsprings into the girl's lap and scowls at you - at \nleast, as much as a cat can scowl through a faceful of fur. \nThe girl smiles, \"Oh, thank you so much for bringing back Princess!\""<<endl;
	  returnedcat = true;
	  p->addExp(100);
	  // need to give xpoints
	}
	else if(returnedcat) {
	  cout<<"The little girls smiles at you. The cat is \nstill scowling."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;    

  case 6:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav6_13) {
	  cav6_13 = true;
	  cout<<"A small contingent of orcs attacks!"<<endl;
	  
	  for(int i=0;i < 10;i++) {
	    monsters[i+41] = new Creature(FIGHTER,"orc ",18,8,10,300);
	    
	    myitem = createItem(LONGSWORD);
	    monsters[i+41]->equip(myitem);
	    myitem = createItem(CHAINMAIL);
	    monsters[i+41]->equip(myitem);
	  }
	  combat(p,41,50);
	  if(gameNotOver) {
	    dieroll = d100.Roll();
	    dieroll *= 5;
	    p->addToGold(dieroll);
	  }
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;    

  case 7: // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	if(cav1_14) {
	  if(girlalive) {
cout<<"As you march into city hall, everyone stops their business
and gasps as they witness you returning the missing girl. A man dashes
down a hallway, and a moment later, a door slams open and a tall, balding 
man dashes down the hallway towards Evelyn Homphrey. The man's eyes begin
to tear as he embraces his new-found daughter.
     \"Quickly!\" he exclaims, in a voice obviously accustomed to 
  command, \"bring this child some water and some food. Nothing heavy - 
broth and some bread to start!\" At least three public employees
scatter to obey.
     He commands the girl to be taken to his office to lie down and
wait for the food to arrive. He thanks you profusely, and you relate
the tale of how you found the girl, and you explain that there are
clearly mysteries yet to be solved. The mayor nods as he listens intently,
and he asks you to return if you discover any answers.
     \"For now, however, you have given my child back to me, and you
well deserve the promised reward. First, I insist that you join my family
for dinner tonight. There is much cause for celebration. Secondly,
it is my privilege to present you with the promised reward.\""<<endl;
 p->addToGold(5000);
 p->addExp(5000);
cout<<"     You leave city hall to toast your comrades, and celebrate your
successful mission. There are still mysteries to be solved - but those will
have to wait for another day. "<<endl;

	  } // end if girlalive
	  else { // if girl is dead
	    cout<<"     You enter city hall, while the rest of your party
waits outside with the girl's body. You tell a clerk you have news of Evelyn
Homphrey, and ask where to find the mayor. You are soon escorted to Mayor 
Homphrey's office, where you disclose the sad fate of his child. The mayor
breaks into tears, and you try to answer as many of his questions as you can.
Some answers you simply don't have, and finding them will have to wait for
another day. The mayor asks you to return if you can shed light on the
unanswered questions. Why was there no ransom note? What there a motive
other than ransom? Who was really behind this foul scheme? 
     He explains that the reward was for the safe return of his daughter, 
but he does give you a lesser reward for discovering her fate. Officials
have arrived to care for the remains of the child, and you leave city hall,
swearing someone is going to pay for this atrocity."<<endl;
 p->addToGold(2000);
 p->addExp(2000);
	  }
	  gameNotOver = false;
	} // end if cav1_14
	else { // if girl not found
	  cout<<"You have entered city hall. People glance up from their work, 
likely to wonder what business you have here."<<endl;
	} // end else
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"The entrance to City Hall lies just to the south."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"To the north lies Farthrop's Inn."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
cout<<"You have entedred Farthrop's Inn. A fire smolders \nin the fireplace, and a tempting aroma wafts \nfrom the kitchen. The clerk at the desk smiles and \nasks, \"What can I do for you?\""<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 8:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
cout<<"     As you walk through this area, a voice from the dark 
whispers, \"Psst! Hey! Are you guys crazy!? Don't you know this
cave is full of nasties that would love to have you for dinner!?\"
A thin woman leaps from an overhang above you, somersaults in midair
and lands on her feet.
     \"They haven't posed us too much of a problem so far. I suppose 
you're after the reward for the mayor's kid?\"
     \"I was. I'll still get her out if I find her. But I found other reasons
to stay here.\"
     \"Other reasons?\"
     \"Have you noticed how organized the demi-humans are here? And where
there's organization, there's money. Somebody is paying these creeps to be
here.\" She jingles a small purse for you to hear. \"I'm taking my cut from
the less-attentive residents.\" She grins as she makes the pouch of gold
disappear. "<<endl;
 cout<<"Do you invite Felicia to join?"<<endl;
 option = yesNo();
 if(option == 'Y') {
   cout<<    " \"Hmmm...we could use somebody sneaky. Care to join us?\"
     \"As long as there's gold in it, I'm your girl.\""<<endl;

   ppm = new Creature("Felicia",THIEF,19,6,8,1);

   myitem = createItem(LEATHERARMOR);
   ppm->equip(myitem);
   myitem = createItem(DAGGER);
   ppm->equip(myitem);

   p->addPartyMember(ppm);
   cout<<"Felicia has joined your party."<<endl;


 }
 else {
   cout<<"     \"Well, try not to get killed.\" You bid her farewell."<<endl;
 }


	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	if(!haveshield && !smithfix) {
	  cout<<"There is a residence to the north. You hear \na mixture of hammering and curses."<<endl;
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	if(!haveshield && !smithfix) {
	  cout<<"You enter the home. You see an old man trying to \nhammer dents out of what must have been an ornate shield \nthat apparently has seen quite a bit of use. \nHe looks up from his work. \"Any of you happen to be a blacksmith?\""<<endl;
	  cout<<"    \"No, but we could take the shield to the smith in town. \nYou don't seem to be having much luck fixing it yourself.\""<<endl;
	  cout<<"    The old man looks at the shield and slides it across the table \nto you. \"Take care of her - she was a good friend to me once.\""<<endl;
	  cout<<"You take the shield, promising to return it shortly."<<endl;
	  haveshield = true;
	}
	if(haveshield && smithfix) {
	  haveshield = false;
	  cout<<"    You enter Gunderson's home only to find he is not alone. \nWith him is a slim girl with golden hair. \"This is my Granddaughter Dinah.\" His eyes start to tear \nas he sees the shield you have returned. You present the \nshield to him, and he runs his wrinkled hand over \nthe now-smooth surface of the shield. \"Thank you,\" he \nwhispers. \"You've made an old man very happy.\"    He looks at you \nagain. \"You're going after whoever took the mayor's daughter, \naren't you?\" You nod. \"I'm going too!\" he says \nas he tries to stand."<<endl;
	  cout<<"<press enter>"<<endl;
	  cin>>entry;
	  cout<<"You start to explain to the old man that he's too old,
but the girl interrupts. \"You can't go, grandfather. But I can.
I will represent our family's honor.\" 
    He starts to protest - then sits back down. \"Very well. If they
will take you, you may go. Perhaps you will succeed where I failed.\""<<endl;
	  cout<<"The girl notices your reluctance, and states, \"I can fight, and 
  I know the area. You can use a guide, can't you?\""<<endl;
	  cout<<"Will you take the girl?"<<endl;

	  option = yesNo();
	  switch(option) {
	  case 'Y':
	    cout<<"We could use a guide, you admit. The girl says goodbye
to her grandfother and promises to return. With that, you bid
the old man farewell and take your leave."<<endl;
	    ppm = new Creature("Dinah",FIGHTER,19,7,11,1);
	    p->addPartyMember(ppm);
	    cout<<"Dinah has joined your party."<<endl;
	    break;

	  case 'N':
	    cout<<"You explain that can't take the girl, and walk out
of the home before they have a chance to argue."<<endl;
	    break;

	  default:
	    break;


	  }
	}
      

	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav8_14) {
	  cav8_14 = true;
	  cout<<"You find a small stash of gold. "<<endl;
	  dieroll = d100.Roll();
	  dieroll *= 3;
	  p->addToGold(dieroll);
	  p->addExp(dieroll);
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 9:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	cout<<"A wizened old man looks up from unpacking his crates. \n\"Sorry - this store is not open yet. \nPlease come see me later.\""<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch are
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:

	if(!cav9_14) {
	  cav9_14 = true;
	  cout<<"A squad of goblins leaps from the darkness and attacks!"<<endl;
	  
	  for(int i=0;i < 10;i++) {
	    monsters[i+31] = new Creature(FIGHTER,"kobold",18,9,10,70);
	    
	    myitem = createItem(DAGGER);
	    monsters[i+31]->equip(myitem);
	    myitem = createItem(LEATHERARMOR);
	    monsters[i+31]->equip(myitem);
	  }
	  combat(p,31,40);
	}

	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;


  case 10:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
	break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
	break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You see a cat nosing through the garbage outside \n the Frisky Wyvern. You quickly grab the cat \nand stuff it in a gunnysack."<<endl;
	havecat = true;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
	break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 11: // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	if(!rav11_1) {
	  rav11_1 = true;
	  cout<<"You see a man sharpening his sword. \n\"Hey Buddy, you goin' after the reward \nfor the mayor's brat?\""<<endl;
	  while(option != '1' && option != 'Y' && option != 'N') {
	    cout<<" 1) Yes."<<endl;
	    cout<<" 2) No. "<<endl;
	    cin>>entry;
	    option = entry[0];
	    option = toupper(option);
	    if(option == '1') {
	      option = 'Y';
	    }
	    if(option == '2') {
	      option = 'N';
	    }	  
	  }


	  switch(option) {
	  case 'Y':
	    cout<<"\"You look like you can handle yourself. What say \nwe team up and split the reward?\""<<endl;
	    option = 'z';
	    while(option != '1' && option != 'Y' && option != 'N') {
	      cout<<" 1) Yes."<<endl;
	      cout<<" 2) No. "<<endl;
	      cin>>entry;
	      option = entry[0];
	      option = toupper(option);
	      if(option == '1') {
		option = 'Y';
	      }
	      if(option == '2') {
		option = 'N';
	      }
	    }

	    switch(option) {
	    case 'Y':
	      cout<<"\"Time's a wastin'. Let's get going!\""<<endl;
	      ppm = new Creature("Enlar",FIGHTER,18,8,11,1);
	      p->addPartyMember(ppm);
	      cout<<"Enlar has joined your party."<<endl;
	      break;
	    case 'N':
	      cout<<"\"More reward money for me then.\"\nHe sheathes his sword and leaves."<<endl;
	      break;
	      
	    default:
	      break;
	    } 
	    break;
	  case 'N':
	    cout<<"\"More reward money for me then.\"\nHe sheathes his sword and leaves."<<endl;
	    break;
	    
	  default:
	    break;
	  } 
	}
	  break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      
    }   // end of switch y
    break;

  case 12:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You are just south of the Horny Unicorn. From the outside, it appears to cater to clientele who are less than wealthy."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	//cout<<"rav12_3 = "<<rav12_3<<endl;
	 if(!rav12_3) {
	   rav12_3 = true;
cout<<"You are having a quiet drink in the Horny Unicorn, a tavern frequented chiefly by workers from the docks as well as sailors and merchants currently in port. A tall, redfaced man stands on a table and begins to speak in very loud tones. His bearing and raiment suggest he is an official of some import in Ravenswood.
     \"Attention everyone! The Mayor's daughter has been kidnapped! His Honor Mayor Reginald Homphrey III is offering a reward of 5000 gold pieces for her return!\"
He then nails a reward poster to the far wall. You approach and read the flyer it reads:

\"Reward! 5000 gold pieces for the safe return of Evelyn Homphrey!

Any information leading to the return of Evelyn Homphrey, and/or the
capture of her abductors, will also be rewarded. Evelyn is 8 years
old, has blond hair and green eyes, and was playing with a white
stuffed unicorn when last seen.

The reward can be collected at City Hall\""<<endl;

	 }
      
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      break;
      
    }   // end of switch y
    break;

  case 13:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	// Ok, need to create & equip orcs
	// indices in monster array are 2-8

	if(!for13_2) {
	  for13_2 = true;
	  cout<<"The orcs look up from their dinner and quickly
decide you have more meat on you than squirrels. They draw
weapons and attack!"<<endl;

	  // creating orcs
	  monsters[2] = new Creature(FIGHTER,"orc1",19,8,10,300);
	  myitem = createItem(LONGSWORD);
	  monsters[2]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[2]->equip(myitem);

	  monsters[3] = new Creature(FIGHTER,"orc2",19,8,10,300);
	  myitem = createItem(AXE);
	  monsters[3]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[3]->equip(myitem);

	  monsters[4] = new Creature(FIGHTER,"orc3",19,8,10,300);
	  myitem = createItem(MACE);
	  monsters[4]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[4]->equip(myitem);

	  monsters[5] = new Creature(FIGHTER,"orc4",19,8,10,300);
	  myitem = createItem(LONGSWORD);
	  monsters[5]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[5]->equip(myitem);

	  monsters[6] = new Creature(FIGHTER,"orc5",19,8,10,300);
	  myitem = createItem(DAGGER);
	  monsters[6]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[6]->equip(myitem);

	  monsters[7] = new Creature(FIGHTER,"orc6",19,8,10,300);
	  myitem = createItem(MACE);
	  monsters[7]->equip(myitem);
	  myitem = createItem(LEATHERARMOR);
	  monsters[7]->equip(myitem);

	  monsters[8] = new Creature(FIGHTER,"orcleader7",15,8,15,500);
	  myitem = createItem(LONGSWORD);
	  monsters[8]->equip(myitem);
	  myitem = createItem(CHAINMAIL);
	  monsters[8]->equip(myitem);

	  combat(p,2,8);

	}
	else {
	  cout<<"You find the remains of what was once an orc camp."<<endl;
	}

	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	if(!for13_2) {
	  cout<<"You see 7 orcs to the south. They are roasting
some small animals - apparently squirrels - over the
fire. They don't have a guard posted, so your presence
is still unnoticed."<<endl;
	}
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	if(!for13_2) {
	  cout<<"To the south you see a small fire burning.
Around the fire is a small collection of orcs.
Thet don't seem to have noticed you yet."<<endl;
	}
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav13_8) {
	  cav13_8 = true;
	  cout<<"From the dark, a group of kobolds attack!"<<endl;
	  
	  for(int i=0;i < 20;i++) {
	    monsters[i+11] = new Creature(FIGHTER,"kobold",19,7,6,50);
	    
	    myitem = createItem(DAGGER);
	    monsters[i+11]->equip(myitem);
	    myitem = createItem(LEATHERARMOR);
	    monsters[i+11]->equip(myitem);
	  }
	  combat(p,11,30);
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"You walk into the Frisky Wyvern - a rather rowdy drinking \nestablishment close to the docks. "<<endl;
	if(!rav14_9) {
	  rav14_9 = true;
	  cout<<"A sailor eyes your party and \napproaches you. \n\"Say, you guys wouldn't be goin' after the mayor's daughter, wouldja?\""<<endl;

	  option = 'z';
	  while(option != '1' && option !='2' && option != 'Y' && option != 'N') {
	    cout<<" 1) Yes."<<endl;
	    cout<<" 2) No. "<<endl;
	    cin>>entry;
	    option = entry[0];
	    option = toupper(option);
	    if(option == '1') {
	      option = 'Y';
	    }
	    if(option == '2') {
	      option = 'N';
	    }
	  } // end while
	  switch(option) {
	  case 'Y':
	    cout<<"\"Look, I got an idea about who snatched the kid. \nFor 20 gold pieces, I'll tell what I know.\""<<endl;

	    option = yesNo();
	    switch(option) {
	    case 'Y':
	      if(p->returnGold() < 20) {
		cout<<"\"Too bad ya ain't got the coin. He swaggers away.\""<<endl;
		//return;
	      }
	      else {
		cout<<"\"Look, I got in on the Summer Breeze a few days ago. \nWe usually carry just freight, but this time we had a couple \npassengers. Captain Balsam don't like passengers, so they \nmusta paid a mayor's ransom to book passage, if you \nget my meanin'. I saw 'em in here the day after we made \nport - nosin' around, askin' a lotta questions. Mostly, \n they seemed interested in who ran the town, and what \n lay west of the town.\""<<endl;

		cout<<"You pay him off, wondering if the two new men in \ntown have anything to do with the kidnapping."<<endl;
		p->addToGold(-20);
		p->addExp(100);
	      }
	      break;
	    case 'N':
	      cout<<"\"Your loss. He staggers away.\""<<endl;
	      break;
	    default:
	      break;
	    }


	    break;
	  case 'N':
	    cout<<"\"Your loss. He staggers away.\""<<endl;
	    break;
	  } // end if
	}
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	if(!foundKelem) {
	  foundKelem = true;
cout<<"A man emerges from some trees to your left. You introduce yourself
and he relates that he is also after the reward. 
     \"I'm Kelem. I was heading for the caves to the west,\" he explains. \"but
the monsters are too much for one man. I don't suppose you could use
an extra sword arm?\""<<endl;
 option = yesNo();
 if(option == 'Y') {
   ppm = new Creature("Kelem",FIGHTER,18,8,12,1);

   myitem = createItem(LONGSWORD);
   ppm->equip(myitem);
   
   myitem = createItem(MEDIUMSHIELD);
   ppm->equip(myitem);

   myitem = createItem(CHAINMAIL);
   ppm->equip(myitem);

   p->addPartyMember(ppm);
   cout<<"Kelem has joined your party."<<endl;
 }
 else {
cout<<"\"Ok, then, good luck to you...\" He fades back into
the forest."<<endl;
 }
	}
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {

	break;    
      }
      break;
      
    }   // end of switch y
    break;

  case 14:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	if(!cav14_7) {
	  cav14_7 = true;
	  cout<<"The party has found a small treasure trove. Apparently this is 
what the kobolds were guarding - but they won't be needing it now."<<endl;
	  dieroll = d100.Roll();
	  dieroll *= 5;
	  p->addToGold(dieroll);
	}
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:

	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	cout<<"Just to the west lies the Frisky Wyvern, a lower class \ndrinking establishment."<<endl;
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      
      break;
    }   // end of switch y
    break;

  case 15:  // x coordinate
      
    switch(y) {
    case 0:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
      } 	// end of switch area
      break;
	
	
    case 1:
	  
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } //end of switch area
      break;
	    
    case 2:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 3:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 4:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	cout<<"You are at the cave's mouth. To the east lies the Ebon Woods."<<endl;
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 5:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 6:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 7:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 8:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 9:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 10:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 11:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	cout<<"You are at the cave's mouth. To the east lies the Ebon Woods."<<endl;
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 12:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 13:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 14:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      break;
      
    case 15:
      
      switch(area) {
      case RAVENSWOOD:
	break;
      case FOREST:
	break;
      case CAVES:
	break;
	
      default:
	break;
	
      } // end of switch area
      
      
      
    default: // for switch y 
      {
	break;    
      }
      break;
      
    }   // end of switch y


  default: // for switch x
    {
      break;    
    }
    
    
  }  // end of switch x
  return gameNotOver;
} // end of function
