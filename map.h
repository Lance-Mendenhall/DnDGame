#ifndef MAP_H
#define MAP_H

class Map {

 private:

  bool NSCurrentArea[16][17];
  bool EWCurrentArea[17][16];
  int currentArea;

 public:
  Map();
  void getMap(int area);

  void loadRavenswood();
  void loadForest();
  void loadCaves();
  bool isWayClear(char dir,int x, int y, int area);


};

#endif