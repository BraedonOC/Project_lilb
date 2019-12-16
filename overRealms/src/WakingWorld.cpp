#include "../headers/WakingWorld.h"

WakingWorld::WakingWorld() {
    
}


void WakingWorld::enter() {
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "lilb");
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    while (window.isOpen()) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = now - lastUpdate;
        if (elapsed.count() > 50) {

            // ******** movement ********
            
            bool verticalMoved = false;
            bool horizontalMoved = false;

            speedX *= .9;
            
            speedY *= .9;
            
            double speedMagnitude = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                verticalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speedY += 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                verticalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speedY -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                horizontalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speedX -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                horizontalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speedX += 1;
                }
            }
      
            if (abs(speedX) < .4) speedX = 0;
            if (abs(speedY) < .4) speedY = 0;

            // *************************

            lastUpdate = std::chrono::high_resolution_clock::now();
            updateWorld(window);
        } 
    }
}


void WakingWorld::updateWorld(sf::RenderWindow &window) {
    double originX = windowX / 2;
    double originY = windowY / 2;

    window.clear(sf::Color(150, 150, 150));
    playerX += speedX;
    playerY -= speedY;

    sf::CircleShape player;
    player.setRadius(20);
    player.setFillColor(sf::Color(20, 20, 20));
    player.setPosition(sf::Vector2f(originX + speedX - 20, originY + speedY - 20));
    window.draw(player);

    sf::RectangleShape test;
    test.setSize(sf::Vector2f(50, 50));
    test.setFillColor(sf::Color(20, 20, 20));
    test.setPosition(sf::Vector2f(500 - playerX, 500 - playerY));
    window.draw(test);
    

    window.display();
}