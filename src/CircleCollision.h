#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

bool IntersectCircles(
    const sf::Vector2f& centerA, float radiusA,
    const sf::Vector2f& centerB, float radiusB,
    sf::Vector2f& normal, float& depth
);

void ResolveCollisions(std::vector<sf::CircleShape>& bodies);