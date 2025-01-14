#pragma once
#include <SFML/Graphics.hpp>
#include "CircleCollision.h"
#include "RectangleCollision.h"
#include "RectangleCircleCollision.h"
#include "unordered_map"
#include "Physics.h"

class HandleAllCollision {

public: 
    static float dotProduct(const sf::Vector2f& d1, const sf::Vector2f& d2);
    static void ResolveCollision(const sf::Vector2f& normal, float depth, PhysicsManger& props1, PhysicsManger& props2, sf::Shape& shape1, sf::Shape& shape2);
    //void HandleCollision(sf::Shape* shape1, sf::Shape* shape2, PhysicsManger& props1, PhysicsManger& props2, const sf::Vector2f& normal, float depth);
    static void CollisionManager(std::vector<std::unique_ptr<sf::Shape>>& shapes, std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap);
    //static void ResolveCollisionVelocity(std::vector<std::unique_ptr<sf::Shape>>& shapes, std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap);
      
};
