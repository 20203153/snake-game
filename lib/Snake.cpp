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
bool gateFlag = false;

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

    
    // gate pass
    if(map->map[SnakeHead.first+dx][SnakeHead.second+dy] == lib::ElementType::Gate) {
        gateFlag = true; // gate passing start
        auto gate1 = map->gateLoc.begin();
        auto gate2 = map->gateLoc.begin(); gate2++;

        std::pair<int, int> clockwise[12] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        int pattern_gate[4] = {0, 1, -1, 2};

        
        // When Gate1 is input gate
        if((SnakeHead.first+dx == gate1->first) && (SnakeHead.second+dy == gate1->second)){
                // 벽(가장자리)에 Gate가 있을 때
            if(gate2->first == 0){
                map->map[(gate2->first)+1][gate2->second] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate2->first+1;
                SnakeHead.second = gate2->second;
                dx = 1; dy = 0;
            }
            else if(gate2->first == map->sz-1){
                map->map[(gate2->first)-1][gate2->second] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate2->first-1;
                SnakeHead.second = gate2->second;
                dx = -1; dy = 0;
            }
            else if(gate2->second == 0){
                map->map[gate2->first][gate2->second+1] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate2->first;
                SnakeHead.second = gate2->second+1;
                dx = 0; dy = 1;
            }
            else if(gate2->second == map->sz-1){
                map->map[gate2->first][gate2->second-1] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate2->first;
                SnakeHead.second = gate2->second-1;
                dx = 0; dy = -1;
            }
            else{
                // Choose Direction (ClockWise)
                int i;
                for(i=0; i<4; i++){
                    if((clockwise[i].first == dx) && (clockwise[i].second == dy)) break;
                }
                for(int j=0; j<4; j++, i++){
                    dx = clockwise[i+pattern_gate[j]].first; dy = clockwise[i+pattern_gate[j]].second;
                    if((map->map[gate2->first+dx][gate2->second+dy] == 0) && ((gate2->first+dx)>=0) && ((gate2->second+dy)>=0) && ((gate2->first+dx)<=20) && ((gate2->second+dy)<=20)){
                        map->map[gate2->first+dx][gate2->second+dy] = lib::ElementType::SnakeHead;
                        SnakeHead.first = gate2->first+dx;
                        SnakeHead.second = gate2->second+dy;
                        break;
                    }
                }
            }
        }
        else{

            if(gate1->first == 0){
                map->map[(gate1->first)+1][gate1->second] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate1->first+1;
                SnakeHead.second = gate1->second;
                dx = 1; dy = 0;
            }
            else if(gate1->first == map->sz-1){
                map->map[(gate1->first)-1][gate1->second] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate1->first-1;
                SnakeHead.second = gate1->second;
                dx = -1; dy = 0;
            }
            else if(gate1->second == 0){
                map->map[gate1->first][gate1->second+1] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate1->first;
                SnakeHead.second = gate1->second+1;
                dx = 0; dy = 1;
            }
            else if(gate1->second == map->sz-1){
                map->map[gate1->first][gate1->second-1] = lib::ElementType::SnakeHead;
                SnakeHead.first = gate1->first;
                SnakeHead.second = gate1->second-1;
                dx = 0; dy = -1;
            }
            else{
                // Choose Direction (ClockWise)
                int i;
                for(i=0; i<4; i++){
                    if((clockwise[i].first == dx) && (clockwise[i].second == dy)) break;
                }
                for(int j=0; j<4; j++, i++){
                    dx = clockwise[i].first; dy = clockwise[i].second;
                    if((map->map[gate1->first+dx][gate1->second+dy] == 0) && ((gate1->first+dx)>=0) && ((gate1->second+dy)>=0) && ((gate1->first+dx)<=20) && ((gate1->second+dy)<=20)){
                        map->map[gate1->first+dx][gate1->second+dy] = lib::ElementType::SnakeHead;
                        SnakeHead.first = gate1->first+dx;
                        SnakeHead.second = gate1->second+dy;
                        break;
                    }
                }
            }
        }

    }
    else{
        map->map[SnakeHead.first += dx][SnakeHead.second += dy] = lib::ElementType::SnakeHead;
    }
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
    
    
    // gate passing time count
    static int gate_throwin_count = 0;
    if(gateFlag){
        gate_throwin_count++;
        map->addGateTicks();
    }

    if(gate_throwin_count>getLength()){
        gateFlag = false;
        gate_throwin_count = 0;
    }

    // create gate
    if((gate_on == false) && (map->getTicks()-map->lastGateTicks)>25){
        int random_1[2] = {0, map->sz - 1};
        int random_2[19] = {0};
        for(int i=0; i<19; i++){
            random_2[i] = i+1;
        }

        bool dec_xy = rand()%2 ? true : false;

        int gate_x, gate_y;
        for(int j=0; j<2; j++){
            if(dec_xy){
                gate_x = random_1[rand()%2];
                gate_y = random_2[rand()%19];
            }
            else{
                gate_x = random_2[rand()%19];
                gate_y = random_1[rand()%2];
            }
            
            if(map->map[gate_x][gate_y] == lib::ElementType::ImmuneWall){
                j--;
                continue;
            }

            std::pair<int, int> gate;
            gate = {gate_x, gate_y};

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
    if((gate_on == true) && (map->getTicks() - map->lastGateTicks > 20)){
        auto it = map->gateLoc.begin();
        for(; it != map->gateLoc.end(); it++){;
            if((it->first >= 1) && (it->first <= 19) && (it->second >= 1) && (it->second <= 19)){
                map->map[it->first][it->second] = 0;
            }
            else{
                map->map[it->first][it->second] = 1;
            }
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