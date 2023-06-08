#include "Maps.h"
#include "Enums.h"
#include <cstring>
#include <memory>

using namespace lib;
using namespace std;

Map::Map(int (*map)[21], int sz): sz(sz), isContinue(true), ticks(0),
    lastItemTicks(0), itemLoc(0), lastGateTicks(0), gateLoc(0), wallLoc(0),
    gateOn(false), gateFlag(false), gateThrowinCnt(0)
{
    this->map = new int*[sz];
    
    for(int i = 0; i < sz; i++) {
        this->map[i] = new int[sz]{};
        memcpy(this->map[i], map[i], sizeof(int) * sz);
        for(int j = 0; j < sz; j++) {
            if(this->map[i][j] == lib::ElementType::Wall) this->wallLoc.push_back({i, j});
        }
    }
}
Map::Map(const Map &v): sz(v.sz), isContinue(v.isContinue), ticks(v.ticks),
    lastItemTicks(v.lastItemTicks), itemLoc(v.itemLoc), lastGateTicks(v.lastGateTicks),
    gateLoc(v.gateLoc), wallLoc(v.wallLoc), gateOn(v.gateOn), gateFlag(v.gateFlag),
    gateThrowinCnt(v.gateThrowinCnt)
{
    this->map = new int*[sz];

    for(int i = 0; i < sz; i++) {
        this->map[i] = new int[sz]{};
        memcpy(this->map[i], v.map[i], sizeof(int) * sz);
    }
}

/* Map::~Map() {
    for(int i = 0; i < sz; i++) {
        delete[] map[i];
    }
    delete[] map;
} */