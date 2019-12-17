#include "../headers/WakingWorld.h"

WakingWorld::WakingWorld() {
    
}



// enter method is called by the stage manager whenever the Waking World is entered
void WakingWorld::enter() {
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "lilb");
    auto lastUpdate = std::chrono::high_resolution_clock::now();
    
    // main gameplay loop
    while (window.isOpen()) {  
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = now - lastUpdate;

        // game updates every 50 milliseconds
        if (elapsed.count() > 50) {

            // ******** movement ********
            
            bool verticalMoved = false;
            bool horizontalMoved = false;


            // there's probably a better way to do this
            // the speed deteriorates at the beginning of the loop
            // to avoid the case of speed being equal to 10
            // and making it so that the player can't turn around

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
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
            }
        }
            updateWorld(window);
        } 
    }
}


// something is probably wrong with the generate function
void WakingWorld::generate() {
    int objectsToGenerate = 1;
    if (playerX > maxXReached) {
        
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = rand() % 20 + windowX + playerX;
            newObject.y = rand() % windowY + playerY;
            newObject.type = rand() % numberOfObjectTypes;
            worldVector.push_back(newObject);
        }
        maxXReached = playerX;
    }
    if (playerX < minXReached) {
        
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = playerX - rand() % 20 ;
            newObject.y = rand() % windowY + playerY;
            newObject.type = rand() % numberOfObjectTypes;
            worldVector.push_back(newObject);
        }
        minXReached = playerX;
    }
    if (playerY > maxYReached) {

        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = rand() % windowX + playerX ;
            newObject.y = rand() % 20 + windowY + playerY;
            newObject.type = rand() % numberOfObjectTypes;
            worldVector.push_back(newObject);
        }
        maxYReached = playerY;
    }
    if (playerY < minYReached) {
      
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = rand() % windowX + playerX ;
            newObject.y = playerY - rand() % 20 ;
            newObject.type = rand() % numberOfObjectTypes;
            worldVector.push_back(newObject);
        }
        minYReached = playerY;
    }
}


// update world function is called by the gameplay loop and 
// updates graphics and generates the world around the player
void WakingWorld::updateWorld(sf::RenderWindow &window) {
    window.clear(sf::Color(242, 124, 85));

    double originX = windowX / 2;
    double originY = windowY / 2;

    // update player position
    playerX += speedX;
    playerY -= speedY;

    // std::cout << "player x: " << playerX << " max x: " << maxXReached << " min x: " << minXReached << std::endl;
    // std::cout << "player y: " << playerY << " max y: " << maxYReached << " min y: " << minYReached << std::endl;

    // world generation
    generate();

    // draw objects in world
    // this is the loop that draws the objects in the world that have been generated so far
    // at the moment it goes through all objects and sees which ones are within range
    // this could probably be improved greatly so that it doesn't have to sort through all
    // objects in the world
    for(int i = 0; i < worldVector.size(); i++) {
        // in this case origin is used as the distance to the edge of the screen
        int relativeToPlayerX = worldVector.at(i).x - playerX;
        int relativeToPlayerY = worldVector.at(i).y - playerY;
        if (relativeToPlayerX < windowX && relativeToPlayerX > 0 
            && relativeToPlayerY < windowY && relativeToPlayerY > 0) {

            int screenPositionX = worldVector.at(i).x - playerX;
            int screenPositionY = worldVector.at(i).y - playerY;

            // type 0 = grass
            if (worldVector.at(i).type == 0) {
                sf::RectangleShape line(sf::Vector2f(2, 30));
            
                line.setPosition(sf::Vector2f(screenPositionX, screenPositionY));

                line.rotate(180 - speedX);
                line.setFillColor(sf::Color(255, 75, 15));
                window.draw(line);
            }

            if (worldVector.at(i).type == 1) {
                int x = worldVector.at(i).x;
                int y = worldVector.at(i).y;
                // create an empty shape
                sf::ConvexShape convex;

                // resize it to 5 points
                convex.setPointCount(5);

                // define the points
                convex.setPoint(0, sf::Vector2f(0, 0));
                convex.setPoint(1, sf::Vector2f(5, -7));
                convex.setPoint(2, sf::Vector2f(10 ,  -10));
                convex.setPoint(3, sf::Vector2f(15 , -7));
                convex.setPoint(4, sf::Vector2f(20, 0));

                convex.setFillColor(sf::Color(100, 100, 100));
                convex.setPosition(sf::Vector2f(screenPositionX, screenPositionY));
                
                window.draw(convex);
            }
        }
    }

    // draw player, this will hopefully be more advanced at some point
    sf::CircleShape player;
    player.setRadius(20);
    player.setFillColor(sf::Color(251, 255, 23));
    player.setPosition(sf::Vector2f(originX + speedX - 20, originY + speedY - 20));
    window.draw(player);

    // this is just a test shape to show the movement of the player
    sf::RectangleShape test;
    test.setSize(sf::Vector2f(50, 50));
    test.setFillColor(sf::Color(242, 52, 39));
    test.setPosition(sf::Vector2f(500 - playerX, 500 - playerY));
    window.draw(test);

    

    
    window.display();
}
