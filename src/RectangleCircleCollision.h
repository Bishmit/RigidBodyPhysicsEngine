#pragma once
#include <SFML/Graphics.hpp>
#include <limits>
#include <cmath>

class RectangleCircleCollision {
public:
    static bool resolveRectangleCircleCollision(sf::RectangleShape& rect, sf::CircleShape& circle, sf::Vector2f &normal, float &depth);

private:
    static float dotProduct(const sf::Vector2f& d1, const sf::Vector2f& d2);
    static sf::Vector2f findCenter(const sf::RectangleShape& rect);
    static std::pair<float, float> projectRectangleOntoAxis(const sf::RectangleShape& rect, const sf::Vector2f& axis);
    static std::pair<float, float> projectCircleOntoAxis(const sf::CircleShape& circle, const sf::Vector2f& axis);
    static std::vector<sf::Vector2f> getAxes(const sf::RectangleShape& rect);
    static std::vector<sf::Vector2f> getAxesCircle(const sf::RectangleShape& rect, const sf::Vector2f& circleCenter);
    static std::vector<sf::Vector2f> getCorners(const sf::RectangleShape& rect);
}; 
