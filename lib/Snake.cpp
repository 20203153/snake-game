#include <cstdlib>
#include <algorithm>

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

bool gate_on = false;

void Snake::draw(Map *map) {
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
        map->itemLoc.remove(std::pair<int, int>(SnakeHead.first + dx, SnakeHead.second + dy));
        map->lastItemUseTicks = map->getTicks();
    }

    bool smallerFlag = false;
    if(map->map[SnakeHead.first + dx][SnakeHead.second + dy] == lib::ElementType::PoisonItem) {
        smallerFlag = true;
        smaller();
        map->itemLoc.remove(std::pair<int, int>(SnakeHead.first + dx, SnakeHead.second + dy));
        map->lastItemUseTicks = map->getTicks();
    }
    if(length < 3) {
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

    if((map->getTicks() % 20) && map->getTicks() - map->lastItemUseTicks > 15 && map->itemLoc.size() > 0) {
        auto item = map->itemLoc.front();
        map->map[item.first][item.second] = 0;
        map->itemLoc.pop_front();
        map->lastItemUseTicks = map->getTicks();
    }

    

    // create gate
    if((gate_on == false) && (map->getTicks()-map->lastGateTicks)>14){
        int random_1[2] = {0, (map->sz)-1};
        int random_2[19];
        for(int i=1; i<20; i++){
            random_2[i] = i;
        }

        int gate_x, gate_y;
        for(int j=0; j<2; j++){
            bool dec_xy = (rand()%2 ? true : false);
            if(dec_xy){
                gate_x = random_1[rand()%2];
                gate_y = random_2[rand()%19];
            }
            else{
                gate_y = random_1[rand()%2];
                gate_x = random_2[rand()%19];
            }

            std::pair<int, int> gate;
            gate = {gate_x, gate_y};
            if(map->map[gate.first][gate.second] == 2){
                j--;
                continue;
            }

            map->map[gate.first][gate.second] = lib::ElementType::Gate;
            map->gateLoc.push_back(gate);

            if(j==1){
                auto it1 = map->gateLoc.begin();
                auto it2 = map->gateLoc.begin(); it2++;
                if((it1->first == it2->first) && (it1->second == it2->second)){
                    j--;
                    continue;
                }
            }            
        }     

        gate_on = true;
        map->lastGateTicks = map->getTicks();
    }

    // delete gate
    if((gate_on == true) && (map->getTicks() - map->lastGateTicks > 10)){
        auto it = map->gateLoc.begin();
        for(; it != map->gateLoc.end(); it++){;
            map->map[it->first][it->second] = 1;
        }
        for(int i=0; i<2; i++){
            map->gateLoc.pop_front();
        }
        gate_on = false;
    }

    map->addTicks();

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