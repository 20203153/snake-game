#include "Enums.h"
#include "Snake.h"

#ifndef __LIB_MAPS__
#define __LIB_MAPS__

using namespace lib;

namespace Maps {
    class Map {
    public:
        int sz;
        int** map;
        Map(int (*map)[21], int sz);
        Map() {}
    };

    void getMap(Map &map, Snake &snake);
}

#endif