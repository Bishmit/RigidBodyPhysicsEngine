#pragma once
#include <SFML/Graphics.hpp>
#include "CircleCollision.h"
#include "RectangleCollision.h"
#include "RectangleCircleCollision.h"

class HandleAllCollision {

public: 
    static void CollisionManager(std::vector<std::unique_ptr<sf::Shape>>& shapes);

};
