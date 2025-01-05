#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "CircleCollision.h"
#include "RectangleCollision.h"
#include "RectangleCircleCollision.h"

namespace Physics {

    class Game {
    public:
        Game();
        void run();
        void initCircles();
        void initRectangles();

    private:
        void processEvents();
        void update();
        void render();
        sf::RenderWindow window;
        sf::Clock clock;
        std::vector<sf::CircleShape> bodies;
        sf::CircleShape controllableCircle;
        /*std::vector<sf::RectangleShape> rectBodies;*/
        sf::RectangleShape rectangle; 
        //sf::RectangleShape rect;
        const float radius = 30.f;
        float movespeed = 300.f;
        bool isEnterPressed = false;

        int maxRectangles = 5; // Cap the number of rectangles
        sf::Event event{};
        bool lockClick = false;
        sf::Clock spawnClock;         // Clock to track time for spawning rectangles
        sf::Time spawnInterval;       // Time interval for spawning rectangles

    };
}