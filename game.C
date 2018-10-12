#include <iostream>
#include <string>
#include <cstdlib>

//#include "consts.h"
#include "item.h"
#include "backpack.h"
#include "creature.h"
#include "event.h"
#include "party.h"
#include "map.h"
#include "dice.h"

int main() {

  // create main character, party, and event
  string name;
  cout<<"What would you like to name your main character?"<<endl;
  cin>>name;
  Creature* bob = new Creature(name,FIGHTER,18,8,12,1);
  // Party myP(bob);
  // Party* myparty = (&myP);
  Party *myparty = new Party(bob);
  Event* event = new Event();

  // initializing starting point, and needed variables
  int x = 12;
  int y = 3;
  int loc = RAVENSWOOD;
  bool gameNotOver = true;
  bool canmove,changeArea;
  char entry = 'z';
  string choice = "";


  gameNotOver = event->occurance(myparty);
  //cout<<"pre while - rav2_13 = "<<event->rav2_13<<endl;
  while(gameNotOver) {
    entry = '!';
    //cout<<"beginning while - rav2_13 = "<<event->rav2_13<<endl;
    while(entry != '1' && entry != '2' && entry != '3' && entry != '4' && entry != 'm' && entry != 'M' && entry != 'd' && entry != 'D' && entry != 'v' && entry != 'V' && entry != 'r' && entry != 'R') {
      cout<<"You may:"<<endl;
      cout<<" 1) Move "<<endl;
      cout<<" 2) Display current coordinates "<<endl;
      cout<<" 3) View party "<<endl;
      cout<<" 4) Rest "<<endl;

      cin>>choice;

      entry = choice[0];

      if(entry == '1') {entry = 'M';}
      if(entry == '2') {entry = 'D';}
      if(entry == '3') {entry = 'V';}
      if(entry == '4') {entry = 'R';}

      entry = toupper(entry);

    } // end while
    switch(entry) {

    case 'M':
    while(entry != '1' && entry != '2' && entry != '3' && entry != '4' && entry != 'n' && entry != 'N' && entry != 'e' && entry != 'E' && entry != 's' && entry != 'S' && entry != 'w' && entry != 'W') {
      cout<<"Which direction will you go?"<<endl;
      cout<<" 1) North \n 2) East \n 3) South \n 4) West "<<endl;
      // cout<<" while2 - rav2_13 = "<<event->rav2_13<<endl;
      cin>>choice;
      
      entry = choice[0];
      
      if(entry == '1') {entry = 'N';}
      if(entry == '2') {entry = 'E';}
      if(entry == '3') {entry = 'S';}
      if(entry == '4') {entry = 'W';}
      
      entry = toupper(entry);
    }
    
    // if area change, change area - else, canmove

    changeArea = event->areaChange(entry);

    if(changeArea) {
      gameNotOver = event->occurance(myparty);
    }
    else {
      canmove = event->canMove(entry);
      //cout<<" while3 - rav2_13 = "<<event->rav2_13<<endl;
      if(canmove) {
	event->Move(entry);
	gameNotOver = event->occurance(myparty);
      }
      else {
	cout<<"You can't go that way. The path is blocked."<<endl;
      }
    }
    break;

    case 'D':
      event->displayLocation();
      break;

    case 'V':
      myparty->displayPartyHP();
      // void Creature::equipItem() {
      break;

    case 'R':
      myparty->Rest();
      break;

    default:
      cout<<"You really should try entering a valid choice!"<<endl;
      break;

    } // end switch choice
    // cout<<"end of while - rav2_13 = "<<event->rav2_13<<endl;
  } // end while(gameNotOver)

  return 0;
}