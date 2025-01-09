#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>

class RectangleCollision {
public:
    static bool checkCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB, sf::Vector2f& normal, float& depth);
    static void resolvePolygonCollisions(std::vector<sf::RectangleShape>& rectbodies);

private:
    static float dotProduct(sf::Vector2f& d1, sf::Vector2f& d2);
    static std::pair<float, float> projectRectangleOntoAxis(const sf::RectangleShape& rect, const sf::Vector2f& axis);
    static bool overlapOnAxis(const std::pair<float, float>& projA, const std::pair<float, float>& projB);
    static std::vector<sf::Vector2f> getAxes(const sf::RectangleShape& rect);
    static std::vector<sf::Vector2f> getCorners(const sf::RectangleShape& rect);
    static sf::Vector2f findCenter(const sf::RectangleShape& rect);
};
