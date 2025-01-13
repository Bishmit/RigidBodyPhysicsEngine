#include "CircleCollision.h"
#include <iostream>

bool CircleCollision::IntersectCircles(
    const sf::Vector2f& centerA, float radiusA,
    const sf::Vector2f& centerB, float radiusB,
    sf::Vector2f& normal, float& depth
) {
    normal = sf::Vector2f(0.f, 0.f);
    depth = 0.f;

    sf::Vector2f diff = centerB - centerA;
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float radiiSum = radiusA + radiusB;

    if (distance >= radiiSum) {
        return false;
    }

    normal = diff / distance;
    depth = radiiSum - distance;
    return true;
}
