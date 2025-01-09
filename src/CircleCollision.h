#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class CircleCollision {
public:
    // Checks if two circles intersect and calculates collision normal and penetration depth
    static bool IntersectCircles(
        const sf::Vector2f& centerA, float radiusA,
        const sf::Vector2f& centerB, float radiusB,
        sf::Vector2f& normal, float& depth
    );

    // Resolves collisions for a vector of circle bodies
    static void ResolveCollisions(std::vector<sf::CircleShape>& bodies);
};
