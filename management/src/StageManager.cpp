#include "../headers/StageManager.h"

StageManager::StageManager() {
    // system("includeDreams.sh");
    // system("includeRealms.sh");
    currentOverRealm = "wakingWorld";  // will hopefully be used in future
}

void StageManager::stageLoop() {
    WakingWorld test;
    while (true) {
        test.enter();
        break;
    }
}