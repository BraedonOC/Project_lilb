#include "../headers/WakingWorld.h"

WakingWorld::WakingWorld() {
    
}

void WakingWorld::enter() {
    sf::RenderWindow window(sf::VideoMode(_windowX, _windowY), "lilb");
    int time = std::time(nullptr);
    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            
        }
        drawWindow();
    }
}

void WakingWorld::drawWindow() {

}