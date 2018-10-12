#include <iostream>
#include "map.h"
#include "types.h"


Map::Map() {
  currentArea = -1;
}


bool Map::isWayClear(char dir,int x, int y, int area) {
  getMap(area);
  bool check;
  switch(dir) {
  case 'N': // north
    check = NSCurrentArea[x][y+1];
    break;
  case 'E': // east
    check = EWCurrentArea[x+1][y];
    break;
  case 'S': // south
    check = NSCurrentArea[x][y];
    break;
  case 'W': // west
    check = EWCurrentArea[x][y];
    break;
  default:
    break;

  } // end switch
  return check;
}

void Map::getMap(int area){

  if(currentArea != area) {

    currentArea = area;

    switch(area) {

    case RAVENSWOOD:
      loadRavenswood();
      break;

    case FOREST:
      loadForest();
      break;

    case CAVES:
      loadCaves();
      break;

  default:
    //probably an error to get here
    break;
    }
  }
  return;
}

void Map::loadRavenswood() {

  for(int i=0;i < 17;i++) {
    for(int j=0;j < 18;j++) {
      NSCurrentArea[i][j] = true;
    }
  }

  for(int i=0;i < 18;i++) {
    for(int j=0;j < 17;j++) {
      EWCurrentArea[i][j] = true;
    }
  }
  NSCurrentArea[0][0] = false;
  NSCurrentArea[0][16] = false;

  NSCurrentArea[1][1] = false;
  NSCurrentArea[1][4] = false;
  NSCurrentArea[1][6] = false;
  NSCurrentArea[1][8] = false;
  NSCurrentArea[1][9] = false;
  NSCurrentArea[1][12] = false;
  NSCurrentArea[1][13] = false;
  NSCurrentArea[1][15] = false;
  NSCurrentArea[1][16] = false;

  NSCurrentArea[2][1] = false;
  NSCurrentArea[2][4] = false;
  NSCurrentArea[2][8] = false;
  NSCurrentArea[2][12] = false;
  NSCurrentArea[2][15] = false;
  NSCurrentArea[2][16] = false;

  NSCurrentArea[3][0] = false;
  NSCurrentArea[3][9] = false;
  NSCurrentArea[3][12] = false;
  NSCurrentArea[3][16] = false;

  NSCurrentArea[4][0] = false;
  NSCurrentArea[4][6] = false;
  NSCurrentArea[4][8] = false;
  NSCurrentArea[4][13] = false;
  NSCurrentArea[4][15] = false;
  NSCurrentArea[4][16] = false;

  NSCurrentArea[5][0] = false;
  NSCurrentArea[5][2] = false;
  NSCurrentArea[5][4] = false;
  NSCurrentArea[5][8] = false;
  NSCurrentArea[5][15] = false;
  NSCurrentArea[5][16] = false;

  NSCurrentArea[6][0] = false;
  NSCurrentArea[6][2] = false;
  NSCurrentArea[6][4] = false;
  NSCurrentArea[6][9] = false;
  NSCurrentArea[6][11] = false;
  NSCurrentArea[6][16] = false;

  NSCurrentArea[7][0] = false;
  NSCurrentArea[7][2] = false;
  NSCurrentArea[7][6] = false;
  NSCurrentArea[7][8] = false;
  NSCurrentArea[7][11] = false;
  NSCurrentArea[7][13] = false;
  NSCurrentArea[7][15] = false;
  NSCurrentArea[7][16] = false;

  NSCurrentArea[8][0] = false;
  NSCurrentArea[8][6] = false;
  NSCurrentArea[8][8] = false;
  NSCurrentArea[8][9] = false;
  NSCurrentArea[8][11] = false;
  NSCurrentArea[8][15] = false;
  NSCurrentArea[8][16] = false;

  NSCurrentArea[9][0] = false;
  NSCurrentArea[9][16] = false;

  NSCurrentArea[10][0] = false;
  NSCurrentArea[10][2] = false;
  NSCurrentArea[10][13] = false;
  NSCurrentArea[10][15] = false;
  NSCurrentArea[10][16] = false;

  NSCurrentArea[11][0] = false;
  NSCurrentArea[11][3] = false;
  NSCurrentArea[11][5] = false;
  NSCurrentArea[11][6] = false;
  NSCurrentArea[11][8] = false;
  NSCurrentArea[11][9] = false;
  NSCurrentArea[11][11] = false;
  NSCurrentArea[11][15] = false;
  NSCurrentArea[11][16] = false;

  NSCurrentArea[12][0] = false;
  NSCurrentArea[12][5] = false;
  NSCurrentArea[12][8] = false;
  NSCurrentArea[12][9] = false;
  NSCurrentArea[12][11] = false;
  NSCurrentArea[12][13] = false;
  NSCurrentArea[12][15] = false;
  NSCurrentArea[12][16] = false;

  NSCurrentArea[13][0] = false;
  NSCurrentArea[13][3] = false;
  NSCurrentArea[13][5] = false;
  NSCurrentArea[13][6] = false;
  NSCurrentArea[13][8] = false;
  NSCurrentArea[13][9] = false;
  NSCurrentArea[13][11] = false;
  NSCurrentArea[13][16] = false;

  NSCurrentArea[14][0] = false;
  NSCurrentArea[14][16] = false;

  NSCurrentArea[15][0] = false;
  NSCurrentArea[15][16] = false;

  EWCurrentArea[0][0] = false;
  EWCurrentArea[9][0] = false;
  EWCurrentArea[11][0] = false;
  EWCurrentArea[16][0] = false;

  EWCurrentArea[0][1] = false;
  EWCurrentArea[1][1] = false;
  EWCurrentArea[9][1] = false;
  EWCurrentArea[11][1] = false;
  EWCurrentArea[16][1] = false;

  EWCurrentArea[0][2] = false;
  EWCurrentArea[1][2] = false;
  EWCurrentArea[3][2] = false;
  EWCurrentArea[5][2] = false;
  EWCurrentArea[8][2] = false;
  EWCurrentArea[16][2] = false;

  EWCurrentArea[0][3] = false;
  EWCurrentArea[1][3] = false;
  EWCurrentArea[3][3] = false;
  EWCurrentArea[5][3] = false;
  EWCurrentArea[8][3] = false;
  EWCurrentArea[11][3] = false;
  EWCurrentArea[14][3] = false;
  EWCurrentArea[16][3] = false;

  EWCurrentArea[0][4] = false;
  EWCurrentArea[11][4] = false;
  EWCurrentArea[14][4] = false;
  EWCurrentArea[16][4] = false;

  EWCurrentArea[0][5] = false;
  EWCurrentArea[16][5] = false;

  EWCurrentArea[0][6] = false;
  EWCurrentArea[1][6] = false;
  EWCurrentArea[3][6] = false;
  EWCurrentArea[4][6] = false;
  EWCurrentArea[6][6] = false;
  EWCurrentArea[7][6] = false;
  EWCurrentArea[9][6] = false;
  EWCurrentArea[11][6] = false;
  EWCurrentArea[14][6] = false;
  EWCurrentArea[16][6] = false;

  EWCurrentArea[0][7] = false;
  EWCurrentArea[1][7] = false;
  EWCurrentArea[3][7] = false;
  EWCurrentArea[4][7] = false;
  EWCurrentArea[6][7] = false;
  EWCurrentArea[7][7] = false;
  EWCurrentArea[9][7] = false;
  EWCurrentArea[11][7] = false;
  EWCurrentArea[14][7] = false;
  EWCurrentArea[16][7] = false;

  EWCurrentArea[0][8] = false;
  EWCurrentArea[16][8] = false;

  EWCurrentArea[0][9] = false;
  EWCurrentArea[1][9] = false;
  EWCurrentArea[4][9] = false;
  EWCurrentArea[6][9] = false;
  EWCurrentArea[9][9] = false;
  EWCurrentArea[11][9] = false;
  EWCurrentArea[16][9] = false;

  EWCurrentArea[0][10] = false;
  EWCurrentArea[1][10] = false;
  EWCurrentArea[4][10] = false;
  EWCurrentArea[6][10] = false;
  EWCurrentArea[9][10] = false;
  EWCurrentArea[11][10] = false;
  EWCurrentArea[16][10] = false;

  EWCurrentArea[0][11] = false;
  EWCurrentArea[1][11] = false;
  EWCurrentArea[4][11] = false;
  EWCurrentArea[16][11] = false;

  EWCurrentArea[0][12] = false;
  EWCurrentArea[16][12] = false;

  EWCurrentArea[0][13] = false;
  EWCurrentArea[1][13] = false;
  EWCurrentArea[3][13] = false;
  EWCurrentArea[4][13] = false;
  EWCurrentArea[6][13] = false;
  EWCurrentArea[7][13] = false;
  EWCurrentArea[9][13] = false;
  EWCurrentArea[10][13] = false;
  EWCurrentArea[13][13] = false;
  EWCurrentArea[16][13] = false;

  EWCurrentArea[0][14] = false;
  EWCurrentArea[1][14] = false;
  EWCurrentArea[3][14] = false;
  EWCurrentArea[4][14] = false;
  EWCurrentArea[6][14] = false;
  EWCurrentArea[7][14] = false;
  EWCurrentArea[9][14] = false;
  EWCurrentArea[10][14] = false;
  EWCurrentArea[13][14] = false;
  EWCurrentArea[16][14] = false;

  EWCurrentArea[0][15] = false;
  EWCurrentArea[16][15] = false;
}


void Map::loadForest() {

  for(int i=0;i < 17;i++) {
    for(int j=0;j < 18;j++) {
      NSCurrentArea[i][j] = true;
    }
  }

  for(int i=0;i < 18;i++) {
    for(int j=0;j < 17;j++) {
      EWCurrentArea[i][j] = true;
    }
  }
  NSCurrentArea[0][0] = false;
  NSCurrentArea[0][4] = false;
  NSCurrentArea[0][5] = false;
  NSCurrentArea[0][11] = false;
  NSCurrentArea[0][12] = false;
  NSCurrentArea[0][16] = false;

  NSCurrentArea[1][0] = false;
  NSCurrentArea[1][4] = false;
  NSCurrentArea[1][7] = false;
  NSCurrentArea[1][11] = false;
  NSCurrentArea[1][14] = false;
  NSCurrentArea[1][16] = false;

  NSCurrentArea[2][0] = false;
  NSCurrentArea[2][6] = false;
  NSCurrentArea[2][7] = false;
  NSCurrentArea[2][13] = false;
  NSCurrentArea[2][14] = false;
  NSCurrentArea[2][16] = false;

  NSCurrentArea[3][0] = false;
  NSCurrentArea[3][2] = false;
  NSCurrentArea[3][4] = false;
  NSCurrentArea[3][6] = false;
  NSCurrentArea[3][7] = false;
  NSCurrentArea[3][9] = false;
  NSCurrentArea[3][12] = false;
  NSCurrentArea[3][13] = false;
  NSCurrentArea[3][14] = false;
  NSCurrentArea[3][16] = false;

  NSCurrentArea[4][0] = false;
  NSCurrentArea[4][4] = false;
  NSCurrentArea[4][6] = false;
  NSCurrentArea[4][7] = false;
  NSCurrentArea[4][9] = false;
  NSCurrentArea[4][12] = false;
  NSCurrentArea[4][13] = false;
  NSCurrentArea[4][14] = false;
  NSCurrentArea[4][16] = false;

  NSCurrentArea[5][0] = false;
  NSCurrentArea[5][1] = false;
  NSCurrentArea[5][2] = false;
  NSCurrentArea[5][4] = false;
  NSCurrentArea[5][6] = false;
  NSCurrentArea[5][7] = false;
  NSCurrentArea[5][9] = false;
  NSCurrentArea[5][12] = false;
  NSCurrentArea[5][13] = false;
  NSCurrentArea[5][14] = false;
  NSCurrentArea[5][16] = false;

  NSCurrentArea[6][0] = false;
  NSCurrentArea[6][1] = false;
  NSCurrentArea[6][2] = false;
  NSCurrentArea[6][5] = false;
  NSCurrentArea[6][14] = false;
  NSCurrentArea[6][16] = false;

  NSCurrentArea[7][0] = false;
  NSCurrentArea[7][1] = false;
  NSCurrentArea[7][2] = false;
  NSCurrentArea[7][5] = false;
  NSCurrentArea[7][6] = false;
  NSCurrentArea[7][8] = false;
  NSCurrentArea[7][9] = false;
  NSCurrentArea[7][12] = false;
  NSCurrentArea[7][13] = false;
  NSCurrentArea[7][16] = false;

  NSCurrentArea[8][0] = false;
  NSCurrentArea[8][1] = false;
  NSCurrentArea[8][2] = false;
  NSCurrentArea[8][5] = false;
  NSCurrentArea[8][6] = false;
  NSCurrentArea[8][8] = false;
  NSCurrentArea[8][9] = false;
  NSCurrentArea[8][12] = false;
  NSCurrentArea[8][13] = false;
  NSCurrentArea[8][16] = false;

  NSCurrentArea[9][0] = false;
  NSCurrentArea[9][1] = false;
  NSCurrentArea[9][2] = false;
  NSCurrentArea[9][5] = false;
  NSCurrentArea[9][6] = false;
  NSCurrentArea[9][8] = false;
  NSCurrentArea[9][11] = false;
  NSCurrentArea[9][12] = false;
  NSCurrentArea[9][13] = false;
  NSCurrentArea[9][16] = false;

  NSCurrentArea[10][0] = false;
  NSCurrentArea[10][1] = false;
  NSCurrentArea[10][8] = false;
  NSCurrentArea[10][10] = false;
  NSCurrentArea[10][11] = false;
  NSCurrentArea[10][12] = false;
  NSCurrentArea[10][13] = false;
  NSCurrentArea[10][16] = false;

  NSCurrentArea[11][0] = false;
  NSCurrentArea[11][4] = false;
  NSCurrentArea[11][5] = false;
  NSCurrentArea[11][7] = false;
  NSCurrentArea[11][8] = false;
  NSCurrentArea[11][10] = false;
  NSCurrentArea[11][11] = false;
  NSCurrentArea[11][12] = false;
  NSCurrentArea[11][14] = false;
  NSCurrentArea[11][16] = false;

  NSCurrentArea[12][0] = false;
  NSCurrentArea[12][1] = false;
  NSCurrentArea[12][2] = false;
  NSCurrentArea[12][4] = false;
  NSCurrentArea[12][5] = false;
  NSCurrentArea[12][7] = false;
  NSCurrentArea[12][8] = false;
  NSCurrentArea[12][13] = false;
  NSCurrentArea[12][14] = false;
  NSCurrentArea[12][16] = false;

  NSCurrentArea[13][0] = false;
  NSCurrentArea[13][1] = false;
  NSCurrentArea[13][5] = false;
  NSCurrentArea[13][7] = false;
  NSCurrentArea[13][8] = false;
  NSCurrentArea[13][13] = false;
  NSCurrentArea[13][14] = false;
  NSCurrentArea[13][16] = false;

  NSCurrentArea[14][0] = false;
  NSCurrentArea[14][1] = false;
  NSCurrentArea[14][2] = false;
  NSCurrentArea[14][7] = false;
  NSCurrentArea[14][8] = false;
  NSCurrentArea[14][16] = false;

  NSCurrentArea[15][0] = false;
  NSCurrentArea[15][7] = false;
  NSCurrentArea[15][8] = false;
  NSCurrentArea[15][16] = false;

  EWCurrentArea[0][0] = false;
  EWCurrentArea[16][0] = false;

  EWCurrentArea[0][1] = false;
  EWCurrentArea[4][1] = false;
  EWCurrentArea[11][1] = false;
  EWCurrentArea[12][1] = false;
  EWCurrentArea[15][1] = false;
  EWCurrentArea[16][1] = false;

  EWCurrentArea[0][2] = false;
  EWCurrentArea[3][2] = false;
  EWCurrentArea[6][2] = false;
  EWCurrentArea[10][2] = false;
  EWCurrentArea[11][2] = false;
  EWCurrentArea[13][2] = false;
  EWCurrentArea[14][2] = false;
  EWCurrentArea[16][2] = false;

  EWCurrentArea[0][3] = false;
  EWCurrentArea[3][3] = false;
  EWCurrentArea[6][3] = false;
  EWCurrentArea[10][3] = false;
  EWCurrentArea[11][3] = false;
  EWCurrentArea[13][3] = false;
  EWCurrentArea[14][3] = false;
  EWCurrentArea[16][3] = false;

  EWCurrentArea[0][4] = false;
  EWCurrentArea[2][4] = false;
  EWCurrentArea[10][4] = false;
  EWCurrentArea[14][4] = false;
  EWCurrentArea[16][4] = false;

  EWCurrentArea[0][5] = false;
  EWCurrentArea[1][5] = false;
  EWCurrentArea[2][5] = false;
  EWCurrentArea[6][5] = false;
  EWCurrentArea[11][5] = false;
  EWCurrentArea[16][5] = false;

  EWCurrentArea[0][6] = false;
  EWCurrentArea[1][6] = false;
  EWCurrentArea[7][6] = false;
  EWCurrentArea[10][6] = false;
  EWCurrentArea[11][6] = false;
  EWCurrentArea[16][6] = false;

  EWCurrentArea[0][7] = false;
  EWCurrentArea[6][7] = false;
  EWCurrentArea[7][7] = false;
  EWCurrentArea[10][7] = false;
  EWCurrentArea[16][7] = false;

  EWCurrentArea[0][8] = false;
  EWCurrentArea[6][8] = false;
  EWCurrentArea[10][8] = false;
  EWCurrentArea[16][8] = false;

  EWCurrentArea[0][9] = false;
  EWCurrentArea[3][9] = false;
  EWCurrentArea[6][9] = false;
  EWCurrentArea[7][9] = false;
  EWCurrentArea[9][9] = false;
  EWCurrentArea[10][9] = false;
  EWCurrentArea[16][9] = false;

  EWCurrentArea[0][10] = false;
  EWCurrentArea[3][10] = false;
  EWCurrentArea[6][10] = false;
  EWCurrentArea[7][10] = false;
  EWCurrentArea[9][10] = false;
  EWCurrentArea[12][10] = false;
  EWCurrentArea[16][10] = false;

  EWCurrentArea[0][11] = false;
  EWCurrentArea[2][11] = false;
  EWCurrentArea[3][11] = false;
  EWCurrentArea[6][11] = false;
  EWCurrentArea[7][11] = false;
  EWCurrentArea[16][11] = false;

  EWCurrentArea[0][12] = false;
  EWCurrentArea[1][12] = false;
  EWCurrentArea[2][12] = false;
  EWCurrentArea[6][12] = false;
  EWCurrentArea[12][12] = false;
  EWCurrentArea[16][12] = false;

  EWCurrentArea[0][13] = false;
  EWCurrentArea[1][13] = false;
  EWCurrentArea[7][13] = false;
  EWCurrentArea[11][13] = false;
  EWCurrentArea[14][13] = false;
  EWCurrentArea[16][13] = false;

  EWCurrentArea[0][14] = false;
  EWCurrentArea[16][14] = false;

  EWCurrentArea[0][15] = false;
  EWCurrentArea[16][15] = false;
}

void Map::loadCaves() {

  for(int i=0;i < 17;i++) {
    for(int j=0;j < 18;j++) {
      NSCurrentArea[i][j] = true;
    }
  }

  for(int i=0;i < 18;i++) {
    for(int j=0;j < 17;j++) {
      EWCurrentArea[i][j] = true;
    }
  }
  NSCurrentArea[0][0] = false;
  NSCurrentArea[0][10] = false;
  NSCurrentArea[0][14] = false;
  NSCurrentArea[0][16] = false;

  NSCurrentArea[1][0] = false;
  NSCurrentArea[1][1] = false;
  NSCurrentArea[1][8] = false;
  NSCurrentArea[1][10] = false;
  NSCurrentArea[1][14] = false;
  NSCurrentArea[1][16] = false;

  NSCurrentArea[2][0] = false;
  NSCurrentArea[2][1] = false;
  NSCurrentArea[2][3] = false;
  NSCurrentArea[2][5] = false;
  NSCurrentArea[2][8] = false;
  NSCurrentArea[2][10] = false;
  NSCurrentArea[2][11] = false;
  NSCurrentArea[2][15] = false;
  NSCurrentArea[2][16] = false;

  NSCurrentArea[3][0] = false;
  NSCurrentArea[3][1] = false;
  NSCurrentArea[3][3] = false;
  NSCurrentArea[3][4] = false;
  NSCurrentArea[3][7] = false;
  NSCurrentArea[3][8] = false;
  NSCurrentArea[3][11] = false;
  NSCurrentArea[3][12] = false;
  NSCurrentArea[3][16] = false;

  NSCurrentArea[4][0] = false;
  NSCurrentArea[4][4] = false;
  NSCurrentArea[4][6] = false;
  NSCurrentArea[4][7] = false;
  NSCurrentArea[4][8] = false;
  NSCurrentArea[4][16] = false;

  NSCurrentArea[5][0] = false;
  NSCurrentArea[5][2] = false;
  NSCurrentArea[5][5] = false;
  NSCurrentArea[5][6] = false;
  NSCurrentArea[5][9] = false;
  NSCurrentArea[5][14] = false;
  NSCurrentArea[5][16] = false;

  NSCurrentArea[6][0] = false;
  NSCurrentArea[6][7] = false;
  NSCurrentArea[6][8] = false;
  NSCurrentArea[6][9] = false;
  NSCurrentArea[6][16] = false;

  NSCurrentArea[7][0] = false;
  NSCurrentArea[7][1] = false;
  NSCurrentArea[7][2] = false;
  NSCurrentArea[7][5] = false;
  NSCurrentArea[7][8] = false;
  NSCurrentArea[7][9] = false;
  NSCurrentArea[7][16] = false;

  NSCurrentArea[8][0] = false;
  NSCurrentArea[8][1] = false;
  NSCurrentArea[8][8] = false;
  NSCurrentArea[8][12] = false;
  NSCurrentArea[8][13] = false;
  NSCurrentArea[8][15] = false;
  NSCurrentArea[8][16] = false;

  NSCurrentArea[9][0] = false;
  NSCurrentArea[9][1] = false;
  NSCurrentArea[9][2] = false;
  NSCurrentArea[9][7] = false;
  NSCurrentArea[9][8] = false;
  NSCurrentArea[9][12] = false;
  NSCurrentArea[9][13] = false;
  NSCurrentArea[9][15] = false;
  NSCurrentArea[9][16] = false;

  NSCurrentArea[10][0] = false;
  NSCurrentArea[10][1] = false;
  NSCurrentArea[10][2] = false;
  NSCurrentArea[10][3] = false;
  NSCurrentArea[10][4] = false;
  NSCurrentArea[10][7] = false;
  NSCurrentArea[10][11] = false;
  NSCurrentArea[10][12] = false;
  NSCurrentArea[10][14] = false;
  NSCurrentArea[10][15] = false;
  NSCurrentArea[10][16] = false;

  NSCurrentArea[11][0] = false;
  NSCurrentArea[11][3] = false;
  NSCurrentArea[11][6] = false;
  NSCurrentArea[11][7] = false;
  NSCurrentArea[11][11] = false;
  NSCurrentArea[11][12] = false;
  NSCurrentArea[11][14] = false;
  NSCurrentArea[11][15] = false;
  NSCurrentArea[11][16] = false;

  NSCurrentArea[12][0] = false;
  NSCurrentArea[12][4] = false;
  NSCurrentArea[12][7] = false;
  NSCurrentArea[12][8] = false;
  NSCurrentArea[12][15] = false;
  NSCurrentArea[12][16] = false;

  NSCurrentArea[13][0] = false;
  NSCurrentArea[13][4] = false;
  NSCurrentArea[13][5] = false;
  NSCurrentArea[13][7] = false;
  NSCurrentArea[13][9] = false;
  NSCurrentArea[13][11] = false;
  NSCurrentArea[13][12] = false;
  NSCurrentArea[13][16] = false;

  NSCurrentArea[14][0] = false;
  NSCurrentArea[14][4] = false;
  NSCurrentArea[14][5] = false;
  NSCurrentArea[14][7] = false;
  NSCurrentArea[14][9] = false;
  NSCurrentArea[14][11] = false;
  NSCurrentArea[14][12] = false;
  NSCurrentArea[14][16] = false;

  NSCurrentArea[15][0] = false;
  NSCurrentArea[15][4] = false;
  NSCurrentArea[15][5] = false;
  NSCurrentArea[15][11] = false;
  NSCurrentArea[15][12] = false;
  NSCurrentArea[15][16] = false;

  EWCurrentArea[0][0] = false;
  EWCurrentArea[6][0] = false;
  EWCurrentArea[12][0] = false;
  EWCurrentArea[16][0] = false;

  EWCurrentArea[0][1] = false;
  EWCurrentArea[1][1] = false;
  EWCurrentArea[4][1] = false;
  EWCurrentArea[6][1] = false;
  EWCurrentArea[7][1] = false;
  EWCurrentArea[11][1] = false;
  EWCurrentArea[12][1] = false;
  EWCurrentArea[16][1] = false;

  EWCurrentArea[0][2] = false;
  EWCurrentArea[1][2] = false;
  EWCurrentArea[4][2] = false;
  EWCurrentArea[5][2] = false;
  EWCurrentArea[8][2] = false;
  EWCurrentArea[9][2] = false;
  EWCurrentArea[12][2] = false;
  EWCurrentArea[16][2] = false;

  EWCurrentArea[0][3] = false;
  EWCurrentArea[1][3] = false;
  EWCurrentArea[2][3] = false;
  EWCurrentArea[5][3] = false;
  EWCurrentArea[8][3] = false;
  EWCurrentArea[9][3] = false;
  EWCurrentArea[10][3] = false;
  EWCurrentArea[16][3] = false;

  EWCurrentArea[0][4] = false;
  EWCurrentArea[1][4] = false;
  EWCurrentArea[2][4] = false;
  EWCurrentArea[4][4] = false;
  EWCurrentArea[5][4] = false;
  EWCurrentArea[8][4] = false;
  EWCurrentArea[9][4] = false;
  EWCurrentArea[11][4] = false;
  EWCurrentArea[12][4] = false;
  EWCurrentArea[16][4] = false;

  EWCurrentArea[0][5] = false;
  EWCurrentArea[1][5] = false;
  EWCurrentArea[3][5] = false;
  EWCurrentArea[4][5] = false;
  EWCurrentArea[6][5] = false;
  EWCurrentArea[7][5] = false;
  EWCurrentArea[9][5] = false;
  EWCurrentArea[11][5] = false;
  EWCurrentArea[12][5] = false;
  EWCurrentArea[13][5] = false;
  EWCurrentArea[16][5] = false;

  EWCurrentArea[0][6] = false;
  EWCurrentArea[1][6] = false;
  EWCurrentArea[3][6] = false;
  EWCurrentArea[7][6] = false;
  EWCurrentArea[9][6] = false;
  EWCurrentArea[13][6] = false;
  EWCurrentArea[16][6] = false;

  EWCurrentArea[0][7] = false;
  EWCurrentArea[1][7] = false;
  EWCurrentArea[5][7] = false;
  EWCurrentArea[6][7] = false;
  EWCurrentArea[13][7] = false;
  EWCurrentArea[15][7] = false;
  EWCurrentArea[16][7] = false;

  EWCurrentArea[0][8] = false;
  EWCurrentArea[3][8] = false;
  EWCurrentArea[4][8] = false;
  EWCurrentArea[10][8] = false;
  EWCurrentArea[12][8] = false;
  EWCurrentArea[15][8] = false;
  EWCurrentArea[16][8] = false;

  EWCurrentArea[0][9] = false;
  EWCurrentArea[3][9] = false;
  EWCurrentArea[4][9] = false;
  EWCurrentArea[5][9] = false;
  EWCurrentArea[8][9] = false;
  EWCurrentArea[10][9] = false;
  EWCurrentArea[12][9] = false;
  EWCurrentArea[13][9] = false;
  EWCurrentArea[16][9] = false;

  EWCurrentArea[0][10] = false;
  EWCurrentArea[4][10] = false;
  EWCurrentArea[5][10] = false;
  EWCurrentArea[8][10] = false;
  EWCurrentArea[10][10] = false;
  EWCurrentArea[12][10] = false;
  EWCurrentArea[13][10] = false;
  EWCurrentArea[16][10] = false;

  EWCurrentArea[0][11] = false;
  EWCurrentArea[2][11] = false;
  EWCurrentArea[5][11] = false;
  EWCurrentArea[8][11] = false;
  EWCurrentArea[16][11] = false;

  EWCurrentArea[0][12] = false;
  EWCurrentArea[2][12] = false;
  EWCurrentArea[3][12] = false;
  EWCurrentArea[4][12] = false;
  EWCurrentArea[5][12] = false;
  EWCurrentArea[12][12] = false;
  EWCurrentArea[13][12] = false;
  EWCurrentArea[16][12] = false;

  EWCurrentArea[0][13] = false;
  EWCurrentArea[2][13] = false;
  EWCurrentArea[3][13] = false;
  EWCurrentArea[4][13] = false;
  EWCurrentArea[5][13] = false;
  EWCurrentArea[8][13] = false;
  EWCurrentArea[10][13] = false;
  EWCurrentArea[12][13] = false;
  EWCurrentArea[13][13] = false;
  EWCurrentArea[16][13] = false;

  EWCurrentArea[0][14] = false;
  EWCurrentArea[3][14] = false;
  EWCurrentArea[4][14] = false;
  EWCurrentArea[6][14] = false;
  EWCurrentArea[8][14] = false;
  EWCurrentArea[13][14] = false;
  EWCurrentArea[16][14] = false;

  EWCurrentArea[0][15] = false;
  EWCurrentArea[2][15] = false;
  EWCurrentArea[4][15] = false;
  EWCurrentArea[6][15] = false;
  EWCurrentArea[16][15] = false;
}
