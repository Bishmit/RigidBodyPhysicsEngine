#include "HandleAllCollision.h"
#include <algorithm>

float HandleAllCollision::dotProduct(const sf::Vector2f& d1, const sf::Vector2f& d2) {
    return d1.x * d2.x + d1.y * d2.y;
}

void HandleAllCollision::CollisionManager(
    std::vector<std::unique_ptr<sf::Shape>>& shapes,
    std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap
) {
    const sf::Vector2f gravity(0.0f, 5.0f);
    const int maxIterations = 10;

    // Apply gravity to all dynamic bodies
    for (auto& shape : shapes) {
        sf::Shape* currentShape = shape.get();
        PhysicsManger& props = physicsMap[currentShape];

        if (!props.isStatic) {
            currentShape->move(gravity);  
        }

    }

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        bool resolvedAll = true;

        for (size_t i = 0; i < shapes.size(); ++i) {
            bool collide = false;

            for (size_t j = i + 1; j < shapes.size(); ++j) {
                sf::Shape* shapeA = shapes[i].get();
                sf::Shape* shapeB = shapes[j].get();

                PhysicsManger& props1 = physicsMap[shapeA];
                PhysicsManger& props2 = physicsMap[shapeB];

                sf::Vector2f normal;
                float depth;
                sf::Vector2f displacement;

                // Circle-Circle Collision
                if (props1.shapeType == "Circle" && props2.shapeType == "Circle") {
                    auto* circle1 = dynamic_cast<sf::CircleShape*>(shapeA);
                    auto* circle2 = dynamic_cast<sf::CircleShape*>(shapeB);

                    if (circle1 && circle2 && CircleCollision::IntersectCircles(
                        circle1->getPosition(), circle1->getRadius(),
                        circle2->getPosition(), circle2->getRadius(),
                        normal, depth)) {
                        displacement = normal * depth;
                        resolvedAll = false;
                        collide = true;

                        if (props1.isStatic) {
                            circle2->move(displacement);
                        }
                        else if (props2.isStatic) {
                            circle1->move(-displacement);
                        }
                        else {
                            circle1->move(-displacement * 0.5f);
                            circle2->move(displacement * 0.5f);
                        }
                    }
                }
                // Rectangle-Rectangle Collision
                else if (props1.shapeType == "Box" && props2.shapeType == "Box") {
                    auto* rect1 = dynamic_cast<sf::RectangleShape*>(shapeA);
                    auto* rect2 = dynamic_cast<sf::RectangleShape*>(shapeB);

                    if (rect1 && rect2 && RectangleCollision::checkCollision(*rect1, *rect2, normal, depth)) {
                        displacement = normal * depth;
                        resolvedAll = false;
                        collide = true;

                        if (props1.isStatic) {
                            rect2->move(displacement);
                        }
                        else if (props2.isStatic) {
                            rect1->move(-displacement);
                        }
                        else {
                            rect1->move(-displacement * 0.5f);
                            rect2->move(displacement * 0.5f);
                        }
                    }
                }
                // Circle-Rectangle Collision
                else if ((props1.shapeType == "Circle" && props2.shapeType == "Box") ||
                    (props1.shapeType == "Box" && props2.shapeType == "Circle")) {
                    sf::CircleShape* circle = (props1.shapeType == "Circle") ? dynamic_cast<sf::CircleShape*>(shapeA)
                        : dynamic_cast<sf::CircleShape*>(shapeB);
                    sf::RectangleShape* rect = (props1.shapeType == "Box") ? dynamic_cast<sf::RectangleShape*>(shapeA)
                        : dynamic_cast<sf::RectangleShape*>(shapeB);

                    if (circle && rect && RectangleCircleCollision::resolveRectangleCircleCollision(
                        *rect, *circle, normal, depth)) {
                        displacement = normal * depth;
                        resolvedAll = false;
                        collide = true;

                        if (props1.isStatic) {
                            circle->move(displacement);
                        }
                        else if (props2.isStatic) {
                            circle->move(-displacement);
                        }
                        else {
                            rect->move(-displacement * 0.5f);
                            circle->move(displacement * 0.5f);
                        }
                    }
                }

                // Apply collision outline effect if collision occurs
                if (collide) {
                    shapeA->setOutlineThickness(-2.f);
                    shapeA->setOutlineColor(sf::Color::Red);
                    shapeB->setOutlineThickness(-2.f);
                    shapeB->setOutlineColor(sf::Color::Red);
                }
                collide = false; 
            }
        }
        if (resolvedAll) break;
    }

}

void HandleAllCollision::removeOffScreenShapes(std::vector<std::unique_ptr<sf::Shape>>& shapes, const sf::RenderWindow& window) {
    for (auto it = shapes.begin(); it != shapes.end(); ) {
        sf::Shape* shape = it->get(); 

        sf::FloatRect bounds = shape->getGlobalBounds();

        if (bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 || bounds.left > window.getSize().x || bounds.top > window.getSize().y) {
            it = shapes.erase(it);  
        }
        else {
            ++it;  
        }
    }
}
