

#ifndef STAGE_MANAGER
#define STAGE_MANAGER


#include "../../overRealms/headers/WakingWorld.h"

#include <string>
#include <vector>

class StageManager {
public:
    StageManager();

    void stageLoop();

private:
    std::string currentOverRealm;
    std::string currentDream;
};

#endif