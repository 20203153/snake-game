#include "Snake.h"
#include "Enums.h"
#include "Maps.h"

using namespace lib;

Snake::Snake(int bodies[], int n, int dx, int dy): length(n), dx(dx), dy(dy), SnakeBody(n - 1, {0, 0}) {
    SnakeHead = std::pair<int, int>(bodies[0], bodies[1]);
    for(int i = 1; i < n; i++) {
        SnakeBody[i - 1] = {bodies[2 * i], bodies[2 * i + 1]};
    }
    return;
}

void Snake::draw(Map *map) {
    static int iter = 0;
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::Wall) {
        map->isContinue = false;
        return;
    }
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::SnakeBody) {
        map->isContinue = false;
        return;
    }

    bool growFlag = false;
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::GrowthItem) {
        growFlag = true;
        grow();
    }

    bool smallerFlag = false;
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::PoisonItem) {
        smallerFlag = true;
        smaller();
    }
    if(length<3) {
        map->isContinue = false;
        return;
    }
    
    SnakeBody.insert(SnakeBody.begin(), {SnakeHead.first, SnakeHead.second});
    map->map[SnakeHead.first += dx][SnakeHead.second += dy] = lib::ElementType::SnakeHead;
    auto it = SnakeBody.begin();
    for(int i = 0; i < length - 1; i++, it++) {
        // std::cout << iter << " " << (*it).first << " " << (*it).second << std::endl;
        map->map[(*it).first][(*it).second] = lib::ElementType::SnakeBody;
    }

    if(!growFlag) {
        map->map[SnakeBody[length - 1].first][SnakeBody[length - 1].second] = 0;
        SnakeBody.resize(length - 1);
    }

    if(smallerFlag) {
        map->map[SnakeBody[length].first][SnakeBody[length].second] = 0;
    }

    iter++;

    return;
}

int Snake::grow() {
    length++;
    return length;
}
int Snake::smaller() {
    length--;
    return length;
}

void Snake::move(char dir) {
    switch(dir) {
        case DirectionKey::up:
            dx = 0;
            dy = -1;
            break;
        case DirectionKey::down:
            dx = 0;
            dy = 1;
            break;
        case DirectionKey::left:
            dx = -1;
            dy = 0;
            break;
        case DirectionKey::right:
            dx = 1;
            dy = 0;
            break;
    }

    return;
}