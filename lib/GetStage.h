#include "Maps.h"
#include "Snake.h"
#include "AdditionalWindow.h"
#include <vector>

#ifndef __GETMAP__
#define __GETMAP__

namespace lib {
    struct StageData {
        int (*map)[21];
        int sz;
        int *snake;
        std::vector<MissionData> mission;
    };
    void getStage(int stage, Map &map, Snake &snake, std::vector<MissionData> &missionData);
}

#endif