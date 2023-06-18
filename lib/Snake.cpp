#include <cstdlib>
#include <algorithm>

#include "Snake.h"
#include "Enums.h"
#include "Maps.h"

using namespace lib;

const std::pair<int, int> clockwise[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
const int clockwise_2[3] = {1, 3, 2}; // (1) clockwise (2) reverse-clockwise (3) reverse direction

Snake::Snake(int bodies[], int n, int dx, int dy): length(n), dx(dx), dy(dy), SnakeBody(n - 1), growthItemCount(0), poisonItemCount(0), gateCount(0) {
    SnakeHead = std::pair<int, int>(bodies[0], bodies[1]);
    for(int i = 1; i < n; i++) {
        SnakeBody[i - 1] = {bodies[2 * i], bodies[2 * i + 1]};
    }
    return;
}

void Snake::draw(Map *map) {
    auto next = map->nextMove(SnakeHead.first, SnakeHead.second, dx, dy);
    if(map->map[next.first][next.second] == lib::ElementType::Wall) {
        map->isContinue = false;
        return;
    }
    if(map->map[next.first][next.second] == lib::ElementType::ImmuneWall) {
        map->isContinue = false;
        return;
    }
    if(map->map[next.first][next.second] == lib::ElementType::SnakeBody) {
        map->isContinue = false;
        return;
    }

    bool growFlag = false;
    if(map->map[next.first][next.second] == lib::ElementType::GrowthItem) {
        growFlag = true;
        grow();
        map->itemLoc.remove(next);
        map->lastItemUseTicks = map->getTicks();
    }

    bool smallerFlag = false;
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::PoisonItem) {
        smallerFlag = true;
        smaller();
        map->itemLoc.remove(next);
        map->lastItemUseTicks = map->getTicks();
    }
    if(length < 3) {
        map->isContinue = false;
        return;
    }
    
    SnakeBody.insert(SnakeBody.begin(), SnakeHead);
    
    // gate pass
    if(map->map[next.first][next.second] == lib::ElementType::Gate) {
        map->gateFlag = true; // gate passing start
        gateCount++;
        auto gate1 = map->gateLoc.begin();
        auto gate2 = map->gateLoc.begin();
        gate2++;

        bool flag = true;
        int i = 0, j = 0;

        if(!dx) {
            i = (dy > 0 ? 2 : 0);
        } else {
            i = (dx > 0 ? 1 : 3); // Error fixed { i = (dx >0 ? 3 : 1) }
        }

        std::pair<int, int>nextPred;
        std::pair<int, int>gate;

        // When Gate1 is input gate
        if(next.first == gate1->first && next.second == gate1->second){
            gate = *gate2;
        } else {
        // When Gate2 is input gate
            gate = *gate1;
        }
        // Choose Direction (ClockWise)
        int dir_count = 0;
        while(flag) {
            nextPred = map->nextMove(gate.first, gate.second, clockwise[i].first, clockwise[i].second);
            if(map->map[nextPred.first][nextPred.second] == 0 ||
                map->map[nextPred.first][nextPred.second] == lib::ElementType::GrowthItem ||
                map->map[nextPred.first][nextPred.second] == lib::ElementType::PoisonItem
            ) {
                flag = false;
                dx = clockwise[i].first;
                dy = clockwise[i].second;
                next = nextPred;
            } else {
                i = (i + clockwise_2[dir_count]) % 4;
                dir_count++;
            }
        }
    }
    map->map[next.first][next.second] = lib::ElementType::SnakeHead;
    SnakeHead = next;

    auto it = SnakeBody.begin();
    for(int i = 0; i < length - 1; i++, it++) {
        map->map[(*it).first][(*it).second] = lib::ElementType::SnakeBody;
    }

    if(!growFlag) {
        map->map[SnakeBody[length - 1].first][SnakeBody[length - 1].second] = 0;
        SnakeBody.resize(length - 1);
    }

    if(smallerFlag) {
        map->map[SnakeBody[length].first][SnakeBody[length].second] = 0;
    }
    
    // add item on field
    if(map->getTicks() - map->lastItemTicks > 10 && map->itemLoc.size() < 3) {
        std::pair<int, int> item = { rand() % map->sz, rand() % map->sz };

        int i = map->getTicks() % 2;
        while(map->map[item.first][item.second]) {
            if (i++ % 2) item.first = (item.first + rand()) % map->sz;
            else item.second = (item.second + rand()) % map->sz;
        }

        map->itemLoc.push_back(item);
        map->map[item.first][item.second] = (rand() % 2 ? lib::ElementType::GrowthItem : lib::ElementType::PoisonItem);
        map->lastItemTicks = map->getTicks();
        if (!map->lastItemUseTicks) map->lastItemUseTicks = map->lastItemTicks;
    }

    // remove item on field
    if((map->getTicks() % 20) && map->getTicks() - map->lastItemUseTicks > 15 && map->itemLoc.size() > 0) {
        auto item = map->itemLoc.front();
        map->map[item.first][item.second] = 0;
        map->itemLoc.pop_front();
        map->lastItemUseTicks = map->getTicks();
    }
    
    // gate passing time count
    if(map->gateFlag) {
        map->gateThrowinCnt++;
        map->lastGateTicks++;
    }

    if(map->gateThrowinCnt > getLength()){
        map->gateFlag = false;
        map->gateThrowinCnt = 0;
    }

    // create gate
    if(!map->gateOn && (map->getTicks() - map->lastGateTicks) > 25) {
        auto gate1 = map->wallLoc.begin();
        auto gate2 = map->wallLoc.begin();
        
        std::advance(gate1, rand() % map->wallLoc.size());
        std::advance(gate2, rand() % map->wallLoc.size());

        int i = map->getTicks() % 2;
        while(gate1 == gate2) {
            if(i % 2) std::advance(gate1, rand() % map->wallLoc.size());
            else std::advance(gate2, rand() % map->wallLoc.size());
        }

        map->map[(*gate1).first][(*gate1).second] = lib::ElementType::Gate;
        map->map[(*gate2).first][(*gate2).second] = lib::ElementType::Gate;

        map->gateLoc.push_back((*gate1));
        map->gateLoc.push_back((*gate2));

        map->gateOn = true;
        map->lastGateTicks = map->getTicks();
    }

    // delete gate
    if(map->gateOn && (map->getTicks() - map->lastGateTicks > 20)) {
        for(auto it = map->gateLoc.begin(); it != map->gateLoc.end(); it++){;
            map->map[(*it).first][(*it).second] = lib::ElementType::Wall;
        }
        map->gateLoc.clear();
        map->gateOn = false;
    }

    map->addTicks();

    return;
}

int Snake::grow() {
    length++;
    growthItemCount++;
    return length;
}
int Snake::smaller() {
    length--;
    poisonItemCount++;
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