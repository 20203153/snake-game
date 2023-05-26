#include <iostream>
#include <utility>
#include <vector>

#ifndef __SNAKE__
#define __SNAKE__

class Snake {
    std::pair<int, int> SnakeHead;
    std::vector<std::pair<int, int>> SnakeBody;
    int length;
    int dx, dy;
public:
    Snake(int bodies[], int n, int dx = -1, int dy = 0);
    Snake() {}
    void draw(int **game);
    int getLength() { return length; }
    int grow();
    int samller();
};

#endif