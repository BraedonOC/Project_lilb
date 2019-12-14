#ifndef WAKING_WORLD
#define WAKING_WORLD

#include <SFML/Graphics.hpp>
#include <time.h>


class WakingWorld {
public:
    WakingWorld();
    void enter();

private:
    void mainLoop();
    void drawWindow();
    
    int _windowX = 500;
    int _windowY = 500;
};


#endif
