#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "CircleCollision.h"
#include "RectangleCollision.h"
#include "RectangleCircleCollision.h"
#include "unordered_map"
#include "Physics.h"

class HandleAllCollision {
private: 
    static sf::Time timeInterval; 
    static sf::Clock spawnClock; 
public: 
    static float dotProduct(const sf::Vector2f& d1, const sf::Vector2f& d2);
    static void CollisionManager(std::vector<std::unique_ptr<sf::Shape>>& shapes, std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap);
    static void removeOffScreenShapes(std::vector<std::unique_ptr<sf::Shape>>& shapes, const sf::RenderWindow& window);
};
