#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include "windows.h"
#include <vector>

using namespace std;

bool isGameOver = false;

const int blocksCount = 7;
const int blocksSprites[blocksCount] {'0', '1', '2', '3', '4', '5', '6'};

const char wallSprite = '#';

int score = 0;

vector< vector< vector<int> > > blocksShapes = {
  {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 1, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},
  },
  {
    {0, 0, 0, 1},
    {0, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  }
};

int generateBlock() {
  srand( time(NULL) );
  return rand() % blocksCount;
}

vector<string> map{
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*                 *"),
 string("*******************"),
};


class block {
  public:
    vector <vector<int> > shape;
    int type;
    int positionX;
    int positionY;
    char sprite;

    
    block(int positionX = 9, int positionY = 0) {
      this->type = generateBlock();
      this->shape = blocksShapes[type];
      this->positionX = positionX;
      this->positionY = positionY;
      this->sprite = blocksSprites[type];
    }
};

block realBlock;

bool canMoveBlockRight() {
  for (int x = realBlock.positionX + 1; x <= realBlock.positionX + 4; ++x) {
    for (int y = realBlock.positionY; y <= realBlock.positionY + 3; ++y) {
      if (map[y].size() <= x) {
        continue;
      }
      if (map[y][x] != ' ' && realBlock.shape[y - (realBlock.positionY)][x - (realBlock.positionX + 1)] == 1) {
        return false;
      }
    }
  }
  return true;
};

bool canMoveBlockLeft() {
  for (int x = realBlock.positionX -1; x <= realBlock.positionX + 2; ++x) {
    for (int y = realBlock.positionY; y <= realBlock.positionY + 3; ++y) {
      if (x < 0) {
        continue;
      }
      if (map[y][x] != ' ' && realBlock.shape[y - (realBlock.positionY)][x - (realBlock.positionX - 1)] == 1) {
        return false;
      }
    }
  }
  return true;
};

bool canFall() {
  for (int y = realBlock.positionY; y <= realBlock.positionY + 3; ++y){
    for (int x = realBlock.positionX; x <= realBlock.positionX + 3; ++x) {
      if (realBlock.shape[y - realBlock.positionY][x - realBlock.positionX] == 1 && map[y + 1][x] != ' ') {
        return false;
      }
    }
  }
  return true;
};

void doFall() {
  ++realBlock.positionY;
}

void doMoveBlockLeft() {
  --realBlock.positionX;
}

void doMoveBlockRight() {
  ++realBlock.positionX;
}

/*void doRotate() {
  vector <vector <int> > rotatedOne = realBlock.shape;
  for (intdddddddddddddddddddadawdsadawd x = 0; x < realBlock.shape.size(); ++x) {
    for (int y = realBlock.shape[x].size() - 1; y >= 0; --y) {
      rotatedOne[x][y] = realBlock.shape[3 - y][x];
    }
  }
  realBlock.shape = rotatedOne;
}*/

void clearMap() {
  for (int examRowIndex = 0; examRowIndex < map.size() - 1; ++examRowIndex) {
    int rowLength = map[examRowIndex].size() - 2;
    int blocksSum = 0;
    for (int columnIndex = 0; columnIndex < map[examRowIndex].size(); ++columnIndex) {
      if (map[examRowIndex][columnIndex] != ' ' && map[examRowIndex][columnIndex] != '*') {
        --rowLength;
        blocksSum += map[examRowIndex][columnIndex] - '0';
      }
    }

    if (rowLength == 0) {
      score += blocksSum;
      for (int toClerrRowIndex = examRowIndex; toClerrRowIndex > 0; --toClerrRowIndex) {
        map[toClerrRowIndex] = map[toClerrRowIndex - 1];
      }

    }

  }
}

void logic() {
  if ( canFall() ) {
    doFall();
  } else {
    for (int rowIndex = 0; rowIndex < map.size(); ++rowIndex) {

      for (int columnIndex = 0; columnIndex < map[rowIndex].size(); ++columnIndex) {
        
        if (columnIndex >= realBlock.positionX && columnIndex <= realBlock.positionX + 3 && rowIndex >= realBlock.positionY && rowIndex <= realBlock.positionY + 3) {
          
          if (realBlock.shape[rowIndex - realBlock.positionY][columnIndex - realBlock.positionX] == 1) {
            map[rowIndex][columnIndex] = realBlock.sprite;
          }
        }

      }
    }
    
    clearMap();

    block a;
    realBlock = a;
    
    if ( !canFall() ) {
      isGameOver = true;
    }
  }

}

void drawMap() {
  system("cls");

  for (int rowIndex = 0; rowIndex < map.size(); ++rowIndex) {

    for (int columnIndex = 0; columnIndex < map[rowIndex].size(); ++columnIndex) {
      //map[realBlock.positionY + rowIndex][realBlock.positionX + columnIndex] = realBlock.shape[rowIndex][columnIndex] == 1 ? realBlock.sprite : ' ';
      
      if (columnIndex >= realBlock.positionX && columnIndex <= realBlock.positionX + 3 && rowIndex >= realBlock.positionY && rowIndex <= realBlock.positionY + 3) {
        
        if (realBlock.shape[rowIndex - realBlock.positionY][columnIndex - realBlock.positionX] == 1) {
          cout << realBlock.sprite;
        } else if (map[rowIndex][columnIndex] == '*') {
          cout << wallSprite;
        } else {
          cout << map[rowIndex][columnIndex];
        }

      } else if (map[rowIndex][columnIndex] == '*') {
        cout << wallSprite;
      } else {
        cout << map[rowIndex][columnIndex];
      }

    }
    cout << endl;

  }

  cout << "score: " << score;
};

void tryRotate() {
  vector <vector <int> > rotatedOne = realBlock.shape;
  for (int x = 0; x < realBlock.shape.size(); ++x) {
    for (int y = realBlock.shape[x].size() - 1; y >= 0; --y) {
      rotatedOne[x][y] = realBlock.shape[3 - y][x];
    }
  }

  for (int y = realBlock.positionY; y <= realBlock.positionY + 3; ++y){
    for (int x = realBlock.positionX; x <= realBlock.positionX + 3; ++x) {
      if (rotatedOne[y - realBlock.positionY][x - realBlock.positionX] == 1 && map[y][x] != ' ') {
        return;
      }
    }
  }
  realBlock.shape = rotatedOne;
  drawMap();
};

void controls() {
  if ( _kbhit() ) {
    switch ( _getch() ) {
      case 'A':
      case 'a':
        if ( canMoveBlockLeft() ) {
          doMoveBlockLeft();
          drawMap();
        }
        break;
      case 'd':
      case 'D':
        if ( canMoveBlockRight() ) {
          doMoveBlockRight();
          drawMap();
        }
        break;
      case 's':
      case 'S':
        if ( canFall() ) {
          doFall();
          drawMap();
        }
        break;
      case 'W':
      case 'w':
        /*if ( canRotate() ) {
          doRotate();
        }*/
        tryRotate();
        break;
    }
  }
}

int main() {
  int timer = time(NULL);
  int tick = 1;
  
  while(!isGameOver) {
    controls();

    if (time(NULL) - timer >= tick) {
      logic();
      drawMap();

      timer = time(NULL);
    }

  }
  
  //cout << "score: " << score << endl;
  system("pause");

  return 0;
};
