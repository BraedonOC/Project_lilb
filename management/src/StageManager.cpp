#include "../headers/StageManager.h"
// #include "../../overRealms/headers/*"


// from OverRealm import *



// class StageManager:
//     outerZone = 0  # outer zone is the zone shown when not in a sub zone
//     dreams = [] 
//     def __init__(self):
//         self.outerZone = OverRealm()  # maybe there could be multiple outer zones
//     def stageLoop (self):
//         while True:
//             self.outerZone.enter()
//            # self.dreams[dreamName].enter()


StageManager::StageManager() {
    // system("includeDreams.sh");
    // system("includeRealms.sh");
    currentOverRealm = "wakingWorld";  // will hopefully be used in future
}

void StageManager::stageLoop() {
    while (true) {
        
    }
}