#include <list>
#include <utility>
#include "Enums.h"

#ifndef __LIB_MAPS__
#define __LIB_MAPS__

using namespace lib;

namespace lib {
    class Map {
        unsigned int ticks;
    public:
        bool isContinue;
        int sz;
        int** map;
        Map(int (*map)[21], int sz);
        Map(const Map &v);
        Map() {}
        unsigned int getTicks() { return ticks; }
        void addTicks() { ticks++; return; }

        unsigned int lastItemTicks;
        unsigned int lastItemUseTicks;
        std::list<std::pair<int, int>> itemLoc;

        unsigned int lastGateTicks;
        unsigned int gateThrowinCnt;
        bool gateOn;
        bool gateFlag;
        std::list<std::pair<int, int>> gateLoc;
        std::list<std::pair<int, int>> wallLoc;

        std::pair<int, int> nextMove(int x, int y, int dx, int dy) {
            return std::pair<int, int>((x + dx + sz) % sz, (y + dy + sz) % sz);
        }

        // ~Map();
    };
}

#endif