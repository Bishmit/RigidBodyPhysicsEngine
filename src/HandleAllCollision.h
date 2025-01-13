#pragma once
#include <SFML/Graphics.hpp>
#include "CircleCollision.h"
#include "RectangleCollision.h"
#include "RectangleCircleCollision.h"
#include "unordered_map"
#include "Physics.h"

class HandleAllCollision {

public: 
    //void HandleCollision(sf::Shape* shape1, sf::Shape* shape2, PhysicsManger& props1, PhysicsManger& props2, const sf::Vector2f& normal, float depth);
    static void CollisionManager(std::vector<std::unique_ptr<sf::Shape>>& shapes, std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap);

};
