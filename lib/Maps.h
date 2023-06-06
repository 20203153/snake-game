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
        std::list<std::pair<int, int>> gateLoc;

        // ~Map();
    };
}

#endif