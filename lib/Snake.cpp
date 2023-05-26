#include "Snake.h"
#include "Enums.h"

Snake::Snake(int bodies[], int n, int dx, int dy): length(n), dx(dx), dy(dy) {
    SnakeHead = std::pair<int, int>(bodies[0], bodies[1]);
    for(int i = 1; i < n; i++) {
        SnakeBody.push_back({bodies[2 * i], bodies[2 * i + 1]});
    }
    return;
}

void Snake::draw(int **game) {
    game[SnakeHead.first][SnakeHead.second] = lib::ElementType::SnakeHead;
    for(int i = 0; i < length - 1; i++) {
        game[SnakeBody[i].first][SnakeBody[i].second] = lib::ElementType::SnakeBody;
    }

    return;
}

int Snake::grow() {
    return length;
}
int Snake::samller() {
    return length;
}