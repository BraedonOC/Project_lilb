#include "../headers/WakingWorld.h"

WakingWorld::WakingWorld() {
    player.x = 0;
    player.y = 0;
    speed.x = 0;
    speed.y = 0;
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

            speed.x *= .9;
            speed.y *= .9;
            
            double speedMagnitude = std::sqrt(std::pow(speed.x, 2) + std::pow(speed.y, 2));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                verticalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speed.y += 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                verticalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speed.y -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                horizontalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speed.x -= 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                horizontalMoved = true;
                if (speedMagnitude < maxSpeed) {
                    speed.x += 1;
                }
            }
      
            if (abs(speed.x) < .4) speed.x = 0;
            if (abs(speed.y) < .4) speed.y = 0;

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


void WakingWorld::generateObject(Object &newObject) {
    newObject.type = rand() % numberOfObjectTypes;
    if (newObject.type == 0) {  // grass 
        newObject.colorOffsetR = rand() % 40 - 20;
        newObject.shapeOffset = rand() % 30;  // changes length
    }
    else if (newObject.type == 1) { // rock
                
        if (rand() % 100 > 30) return; // cahnce to spawn = 10%
    
        newObject.colorOffsetR = rand() % 100 - 15;
        newObject.colorOffsetG = rand() % 100 - 15;
        newObject.colorOffsetB = rand() % 100 - 15;
        newObject.shapeOffset = rand() % 2 + 1;  // changes size
    }

    worldVector.push_back(newObject);
}



// something is wrong with the generate function
void WakingWorld::generateWorld() {
    int objectsToGenerate = 5;
    int gridSize = 10;

    // format for generation:
    // if the player coord is past the max reached plus the grid size
    // then for however many objects are being generated:
    // create a new object
    // set its coords
    // call generateObject on the object


    // maxs
    if (player.x > maxXReached + gridSize) {
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;         
            newObject.x = renderDistance + windowX + player.x + rand() % 20;
            newObject.y = rand() % windowY + player.y;
            generateObject(newObject);
        }
        maxXReached = player.x;
    }
    if (player.y > maxYReached + gridSize) {
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = rand() % windowX + player.x ;
            newObject.y = renderDistance + windowY + player.y + rand() % 20;
            generateObject(newObject);
        }
        maxYReached = player.y;
    }

    // mins
    if (player.x < minXReached - gridSize) {
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = player.x - renderDistance - rand() % 20;
            newObject.y = rand() % windowY + player.y;
            generateObject(newObject);
        }
        minXReached = player.x;
    }
    if (player.y < minYReached - gridSize) {
        for (int i = 0; i < objectsToGenerate; i++) {
            Object newObject;
            newObject.x = rand() % windowX + player.x;
            newObject.y = player.y - renderDistance - rand() % 20;
            generateObject(newObject);
        }
        minYReached = player.y;
    }
}


// update world function is called by the gameplay loop and 
// updates graphics and generates the world around the player
void WakingWorld::updateWorld(sf::RenderWindow &window) {
    window.clear(sf::Color(217, 151, 240));
    double originX = windowX / 2;
    double originY = windowY / 2;

    // update player position
    player.x += speed.x;
    player.y -= speed.y;

  

    if (abs(wind) > 5) {
        windSpeed *= -1;
    }
    
    wind += windSpeed;

    // world generation
    generateWorld();

    // draw objects in world
    // this is the loop that draws the objects in the world that have been generated so far
    // at the moment it goes through all objects and sees which ones are within range
    // this could probably be improved greatly so that it doesn't have to sort through all
    // objects in the world

    for(int i = 0; i < worldVector.size(); i++) {
        // in this case origin is used as the distance to the edge of the screen
        int screenPositionX = worldVector.at(i).x - player.x;
        int screenPositionY = worldVector.at(i).y - player.y;
        
        if (screenPositionX < windowX + renderDistance  && screenPositionX > -1 * renderDistance 
            && screenPositionY < windowY + renderDistance && screenPositionY > -1 * renderDistance) {
            

            // type 0 = grass
            if (worldVector.at(i).type == 0) {
                sf::RectangleShape line(sf::Vector2f(3, 30 + worldVector.at(i).shapeOffset));
            
                line.setPosition(sf::Vector2f(screenPositionX, screenPositionY));

                line.rotate(180 - speed.x - wind);
                line.setFillColor(sf::Color(235 + worldVector.at(i).colorOffsetR, 75, 15));
                window.draw(line);
            }

            // type 1 = rock thing
            else if (worldVector.at(i).type == 1) {  
 
                int x = worldVector.at(i).x;
                int y = worldVector.at(i).y;
                double size = worldVector.at(i).shapeOffset;
                // create an empty shape
                sf::ConvexShape rock;

                // resize it to 5 points
                rock.setPointCount(3);

                // define the points
                rock.setPoint(0, sf::Vector2f(0, 0));
                rock.setPoint(1, sf::Vector2f(10 * size, (-10 - 10 * size)));
                rock.setPoint(2, sf::Vector2f(20 * size, 0));

                int rOffset = worldVector.at(i).colorOffsetR;
                int gOffset = worldVector.at(i).colorOffsetG;
                int bOffset = worldVector.at(i).colorOffsetB;

                rock.setFillColor(sf::Color(100 + rOffset, 100 + gOffset, 100 + bOffset));
                rock.setPosition(sf::Vector2f(screenPositionX, screenPositionY));
                
                window.draw(rock);
                
            }
        }
    }

    // draw player, this will hopefully be more advanced at some point
    sf::CircleShape playerSprite;
    playerSprite.setRadius(20);
    playerSprite.setFillColor(sf::Color(251, 255, 23));
    playerSprite.setPosition(sf::Vector2f(originX + speed.x - 20, originY + speed.y - 20));
    window.draw(playerSprite);

    // this is just a test shape to show the movement of the player
    sf::RectangleShape test;
    test.setSize(sf::Vector2f(50, 50));
    test.setFillColor(sf::Color(242, 52, 39));
    test.setPosition(sf::Vector2f(500 - player.x, 500 - player.y));
    window.draw(test);

    

    
    window.display();
}
