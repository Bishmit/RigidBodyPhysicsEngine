#pragma once
#include "HandleAllCollision.h"
#include "Physics.h"

namespace Physics {

    class Game {
    public:
        Game();
        void run();

    private:
        int WIDTH, HEIGHT; 
        void processEvents();
        void update();
        void render();
        sf::RenderWindow window;
        sf::Clock clock;
        std::unique_ptr<sf::RectangleShape> rect;
        const float radius = 30.f;
        float movespeed = 300.f;
        std::vector<std::unique_ptr<sf::Shape>> shapes;
        std::unordered_map<sf::Shape*, PhysicsManger> physicsMap;

        int maxRectangles = 5; 
        sf::Event event{};
        bool lockClick = false;
        sf::Clock spawnClock;       
        sf::Time spawnInterval;  
        std::unique_ptr<sf::Shape> createBody(bool isStatic,
            std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap,
            const std::string& shapeType, const sf::Vector2f& size, float radius);
    };
}