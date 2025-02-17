#include "RectangleCircleCollision.h"



std::pair<float, float> RectangleCircleCollision::projectRectangleOntoAxis(const sf::RectangleShape& rect, const sf::Vector2f& axis) {
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();

    auto corners = getCorners(rect);
    for (const auto& corner : corners) {
        float projection = dotProduct(corner, axis);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return { min, max };
}

std::pair<float, float> RectangleCircleCollision::projectCircleOntoAxis(const sf::CircleShape& circle, const sf::Vector2f& axis) {
    float radius = circle.getRadius();
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float projectionCenter = dotProduct(circleCenter, axis);
    return { projectionCenter - radius, projectionCenter + radius };
}

std::vector<sf::Vector2f> RectangleCircleCollision::getAxes(const sf::RectangleShape& rect) {
    auto corners = getCorners(rect);
    std::vector<sf::Vector2f> axes;

    for (size_t i = 0; i < corners.size(); ++i) {
        sf::Vector2f edge = corners[(i + 1) % corners.size()] - corners[i];
        sf::Vector2f axis(-edge.y, edge.x); // Perpendicular axis (normal)
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (length > 0.000001f) {
            axis /= length; // Normalize
            axes.push_back(axis);
        }
    }
    return axes;
}

std::vector<sf::Vector2f> RectangleCircleCollision::getAxesCircle(const sf::RectangleShape& rect, const sf::Vector2f& circleCenter) {
    auto corners = getCorners(rect);
    std::vector<sf::Vector2f> axes;

    for (const auto& corner : corners) {
        sf::Vector2f axis = corner - circleCenter; // Axis from circle to rectangle corner
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (length > 0.000001f) {
            axis /= length; // Normalize
            axes.push_back(axis);
        }
    }
    return axes;
}

std::vector<sf::Vector2f> RectangleCircleCollision::getCorners(const sf::RectangleShape& rect) {
    sf::Transform transform = rect.getTransform();
    std::vector<sf::Vector2f> corners(4);

    for (size_t i = 0; i < 4; ++i) {
        corners[i] = transform.transformPoint(rect.getPoint(i)); // Get each transformed corner
    }
    return corners;
}


bool RectangleCircleCollision::resolveRectangleCircleCollision(sf::RectangleShape& rect, sf::CircleShape& circle, sf::Vector2f &normal, float &depth) {
    sf::Vector2f circleCenter = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());// Correct center
    auto rectAxes = getAxes(rect);
    auto circleAxes = getAxesCircle(rect, circleCenter);

    // Combine rectangle and circle axes
    std::vector<sf::Vector2f> axes = rectAxes;
    axes.insert(axes.end(), circleAxes.begin(), circleAxes.end());

    depth = std::numeric_limits<float>::max();

    // SAT Test: Check all axes
    for (const auto& axis : axes) {
        auto [minRect, maxRect] = projectRectangleOntoAxis(rect, axis);
        auto [minCircle, maxCircle] = projectCircleOntoAxis(circle, axis);

        if (maxRect < minCircle || maxCircle < minRect) {
            // No overlapno,  collision
            rect.setOutlineColor(sf::Color::White); 
            circle.setOutlineColor(sf::Color::White); 
            return false; 
        }
        rect.setOutlineColor(sf::Color::Red);  // Border color
        rect.setOutlineThickness(0.1f);
        circle.setOutlineColor(sf::Color::Red);  // Border color
        circle.setOutlineThickness(0.1f);

        // Calculate depth i.e overlap
        float axisDepth = std::min(maxRect, maxCircle) - std::max(minRect, minCircle);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    // Normalize normal
    if (std::sqrt(dotProduct(normal, normal) > 0.000001f)){
        normal /= std::sqrt(dotProduct(normal, normal));
    }

    // Ensure normal points from rectangle to circle
    sf::Vector2f directionToCircle = circleCenter - findCenter(rect);
    if (dotProduct(normal, directionToCircle) < 0.f) {
        normal = -normal;
    }
    return true; 
}


float RectangleCircleCollision::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f RectangleCircleCollision::findCenter(const sf::RectangleShape& rect) {
    auto corners = getCorners(rect);
    float sumX = 0.f;
    float sumY = 0.f;
    for (const auto& corner : corners) {
        sumX += corner.x;
        sumY += corner.y;
    }
    return { sumX / corners.size(), sumY / corners.size() };
}