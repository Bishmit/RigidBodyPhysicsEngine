#include "RectangleCollision.h"

std::pair<float, float> RectangleCollision::projectRectangleOntoAxis(const sf::RectangleShape& rect, const sf::Vector2f& axis) {
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();

    auto corners = getCorners(rect);
    for (const auto& corner : corners) {
        float projection = corner.x * axis.x + corner.y * axis.y;
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return {min, max};
}

bool RectangleCollision::overlapOnAxis(const std::pair<float, float>& projA, const std::pair<float, float>& projB) {
    return !(projA.second < projB.first || projB.second < projA.first);
}

std::vector<sf::Vector2f> RectangleCollision::getAxes(const sf::RectangleShape& rect) {
    auto corners = getCorners(rect);
    std::vector<sf::Vector2f> axes;

    for (size_t i = 0; i < corners.size(); ++i) {
        sf::Vector2f edge = corners[(i + 1) % corners.size()] - corners[i];
        sf::Vector2f axis(-edge.y, edge.x);
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (length > 0.00001f) {
            axis /= length;
            axes.push_back(axis);
        }
    }
    return axes;
}

std::vector<sf::Vector2f> RectangleCollision::getCorners(const sf::RectangleShape& rect) {
    sf::Transform transform = rect.getTransform();
    std::vector<sf::Vector2f> corners(4);
    for (size_t i = 0; i < 4; ++i) {
        corners[i] = transform.transformPoint(rect.getPoint(i));
    }
    return corners;
}

sf::Vector2f RectangleCollision::findCenter(const sf::RectangleShape& rect) {
    auto corners = getCorners(rect);
    float sumX = 0.f;
    float sumY = 0.f;
    for (const auto& corner : corners) {
        sumX += corner.x;
        sumY += corner.y;
    }
    return {sumX / corners.size(), sumY / corners.size()};
}

bool RectangleCollision::checkCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB, sf::Vector2f& normal, float& depth) {
    normal = sf::Vector2f(0.f, 0.f);
    depth = std::numeric_limits<float>::max();

    auto axesA = getAxes(rectA);
    auto axesB = getAxes(rectB);

    for (const auto& axis : axesA) {
        auto projA = projectRectangleOntoAxis(rectA, axis);
        auto projB = projectRectangleOntoAxis(rectB, axis);
        if (!overlapOnAxis(projA, projB)) {
            return false;
        }
        float axisDepth = std::min(projB.second - projA.first, projA.second - projB.first);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    for (const auto& axis : axesB) {
        auto projA = projectRectangleOntoAxis(rectA, axis);
        auto projB = projectRectangleOntoAxis(rectB, axis);
        if (!overlapOnAxis(projA, projB)) {
            return false;
        }
        float axisDepth = std::min(projB.second - projA.first, projA.second - projB.first);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }
    sf::Vector2f centerA = findCenter(rectA);
    sf::Vector2f centerB = findCenter(rectB);
    sf::Vector2f directionToB = centerB - centerA;
    if (dotProduct(directionToB, normal) < 0.f) {
        normal = -normal;
    }
    return true;
}

void RectangleCollision::resolvePolygonCollisions(std::vector<sf::RectangleShape>& bodies) {
    for (size_t i = 0; i < bodies.size(); ++i) {
        bodies[i].setFillColor(sf::Color::White);

        for (size_t j = i + 1; j < bodies.size(); ++j) {
            sf::Vector2f normal;
            float depth;
            if (checkCollision(bodies[i], bodies[j], normal, depth)) {
                sf::Vector2f displacement = normal * (depth / 2.f);
                bodies[i].move(-displacement);
                bodies[j].move(displacement);
                bodies[j].setOutlineColor(sf::Color::Yellow);
                bodies[i].setFillColor(sf::Color::Yellow);
            }
        }
    }
    //std::cout<<deltaTime<<std::endl;
}

float RectangleCollision::dotProduct(sf::Vector2f &d1, sf::Vector2f &d2) {
    return d1.x * d2.x + d1.y * d2.y;
}