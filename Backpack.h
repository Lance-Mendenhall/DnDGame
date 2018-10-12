#ifndef BACKPACK_H
#define BACKPACK_H

#include <string>
#include <cstdlib>
#include "item.h"


/* The backpack class will hold various item the person will
carry. The item is represented by a string.

possible methods needed:

1) look in backpack - inventory()
2) drop item
3) remove item from backpack
4) place item in backpack - insert(string item)

*/

class Backpack {

  private:
  //  int STORAGESIZE;
  //string backpack[STORAGESIZE];

 public:
  Backpack();
  void inventory();
  bool insert(Item* item);
  void drop();
  void use(Item* item);
  void siftPack();
  Item* backpack[STORAGESIZE];
  int howMany();
  bool isFull(); // returns true if pack is full, false otherwise
  void dropItem(int i);
};


#endif
