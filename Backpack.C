#include "backpack.h"
#include <string>
#include <iostream>
#include <cstdlib>




Backpack::Backpack() {
  // Item* backpack[STORAGESIZE]; // backpack
  for(int i = 0;i < STORAGESIZE;i++) {
    backpack[i] = NULL;
  }
}
 
void Backpack::inventory() {
  cout<<"Backpack inventory:"<<endl;
  for(int i = 0;i < STORAGESIZE;i++) {
    //cout<<"in for loop"<<endl;
    if(backpack[i] != NULL) {
      //cout<<"in if statement"<<endl;
      cout<<(i+1)<<") "<<backpack[i]->getName()<<endl;
    }
  }
  return;
}

bool Backpack::insert(Item* item) {
  cout<<"started insert function"<<endl;
  cout<<"The item purchased is: :"<<item->getName()<<endl;
  int i = 0;
  bool foundslot = false;
  while(i < STORAGESIZE && !foundslot) {
    cout<<"In while loop, i = "<<i<<endl;
    if(backpack[i] == NULL) {
      cout<<"before assignment"<<endl;
      backpack[i] = item;
      cout<<"after assignment"<<endl;
      foundslot = true;
    }
    i++;
  }
  if(!foundslot) {
    cout<<"Your backpack is full. You need to drop an item first."<<endl;
  }
  cout<<"ended insert function"<<endl;
  return foundslot;
}


void Backpack::drop() {
  int choice = -1;
  int end = howMany();
  while(choice < 1 || choice > end) {
    inventory();
    cout<<"Enter the number of the item you would like to drop. \nWARNING!!! All items in that slot will be dropped!"<<endl;

    cin>>choice;
  }
  choice--;
  delete backpack[choice];
  backpack[choice] = NULL;
  siftPack();
}

void Backpack::use(Item* item) {
  //if item is !usable cout error message
  // else use item
  siftPack();
}

void Backpack::siftPack() {
  bool packsifted = false;
  int i,j;
  i = 0;
  while(!packsifted) {
    // find first NULL
    while(backpack[i] != NULL && i < STORAGESIZE) {
      i++;
    }
    // cout<<"1) i = "<<i<<",j = "<<j<<endl;
    inventory();
    if(i == STORAGESIZE - 1) {
      return;
    }
    //i++;
    // now index I should be first NULL
    // now, start at end and find first item
    
    //cout<<"2) i = "<<i<<",j = "<<j<<endl;
    inventory();

    j = STORAGESIZE - 1;
    while(backpack[j] == NULL && j >= 0) {
      j--;
    }

    //cout<<"3) i = "<<i<<",j = "<<j<<endl;

    if(i < j) {
      backpack[i] = backpack[j];
      backpack[j] = NULL;
    }
    else {
      packsifted = true;
    }
  }
  //cout<<"4) i = "<<i<<",j = "<<j<<endl;
  return;
}

// returns how many slots in pack are occupied
int Backpack::howMany() {
  int i;
  for(i = 0;i < STORAGESIZE;i++) {
    if(backpack[i] != NULL) {
      i++;
    }
  }
  return i;
}

// returns true if pack is full, false otherwise
bool Backpack::isFull(){ 

  bool retVal;
  int i;
  for(i=0;i < STORAGESIZE && backpack[i] != NULL;i++) {
      i++;
  }
  if(i == STORAGESIZE) {
    retVal = true;
  }
  else {
    retVal = false;
  }
  return retVal;
}


void Backpack::dropItem(int i) {
  delete backpack[i];
  backpack[i] = NULL;
  siftPack();
}