#include "Enums.h"

#ifndef __LIB_MAPS__
#define __LIB_MAPS__

using namespace lib;

namespace Maps {
    class Map {
    public:
        int sz;
        int** Map;
    };

    Map getMap();
}

#endif