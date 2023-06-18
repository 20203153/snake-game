#include <iostream>
#include <utility>
#include <vector>
#include "Maps.h"

using namespace lib;

#ifndef __SNAKE__
#define __SNAKE__

class Snake {
    std::pair<int, int> SnakeHead;
    std::vector<std::pair<int, int>> SnakeBody;
    int length;
    int dx, dy;
    int growthItemCount;
    int poisonItemCount;
    int gateCount;
public:
    Snake(int bodies[], int n, int dx = -1, int dy = 0);
    Snake() {}
    void draw(Map *map);
    int getLength() { return length; }
    int getGrowthItemCount() {return growthItemCount;}
    int getPoisonItemCount() {return poisonItemCount;}
    int getGateCount() {return gateCount;}
    int grow();
    int smaller();
    void move(char dir);
};

#endif