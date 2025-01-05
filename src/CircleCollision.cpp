#include "CircleCollision.h"
#include <cmath>

bool IntersectCircles(
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

void ResolveCollisions(std::vector<sf::CircleShape>& bodies) {
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            sf::Vector2f normal;
            float depth;
            if (IntersectCircles(bodies[i].getPosition(), bodies[i].getRadius(), bodies[j].getPosition(), bodies[j].getRadius(), normal, depth)) {
                sf::Vector2f displacement = normal * (depth / 2.f);
                bodies[i].move(-displacement);
                bodies[j].move(displacement);
            }
        }
    }
}