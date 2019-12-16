#ifndef WAKING_WORLD
#define WAKING_WORLD

#include <SFML/Graphics.hpp>
#include <math.h>
#include <chrono>
#include <vector>
#include <iostream>


class WakingWorld {
public:
    WakingWorld();
    void enter();

private:
    void mainLoop();
    void updateWorld(sf::RenderWindow &window);

    std::vector<std::vector<int>> worldVector;

    int maxSpeed = 15;

    int playerX = 0;
    int playerY = 250;

    int windowX = 500;
    int windowY = 500;

    double speedX = 0;
    double speedY = 0;
};


#endif
