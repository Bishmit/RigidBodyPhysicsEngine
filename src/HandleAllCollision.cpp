#include "HandleAllCollision.h"

void HandleAllCollision::CollisionManager(
    std::vector<std::unique_ptr<sf::Shape>>& shapes,
    std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap
) {

    const sf::Vector2f gravity(0.0f, 9.8f);

    for (auto& shape : shapes) {
        sf::Shape* currentShape = shape.get();
        PhysicsManger& props = physicsMap[currentShape];

        if (!props.isStatic) {
            continue;
        }
        currentShape->move(gravity);
    }

        for (size_t i = 0; i < shapes.size(); ++i) {
            for (size_t j = i + 1; j < shapes.size(); ++j) {
                sf::Shape* shapeA = shapes[i].get();
                sf::Shape* shapeB = shapes[j].get();

                PhysicsManger& props1 = physicsMap[shapeA];
                PhysicsManger& props2 = physicsMap[shapeB];

                if (!props1.isStatic && !props2.isStatic) {
                    continue;
                }

                sf::Vector2f normal;
                float depth;
                sf::Vector2f displacement;

                if (props1.shapeType == "Circle" && props2.shapeType == "Circle") {
                    auto* circle1 = dynamic_cast<sf::CircleShape*>(shapeA);
                    auto* circle2 = dynamic_cast<sf::CircleShape*>(shapeB);

                    if (circle1 && circle2 && CircleCollision::IntersectCircles(
                        circle1->getPosition(), circle1->getRadius(),
                        circle2->getPosition(), circle2->getRadius(),
                        normal, depth)) {
                        displacement = normal * (depth / 2.f);
                        circle1->move(-displacement);
                        circle2->move(displacement);
                    }
                }
                if (props1.shapeType == "Box" && props2.shapeType == "Box") {
                    auto* rect1 = dynamic_cast<sf::RectangleShape*>(shapeA);
                    auto* rect2 = dynamic_cast<sf::RectangleShape*>(shapeB);

                    if (RectangleCollision::checkCollision(*rect1, *rect2, normal, depth)) {
                        displacement = normal * (depth / 2.f);
                        rect1->move(-displacement);
                        rect2->move(displacement);
                    }
                }
                if ((props1.shapeType == "Circle" && props2.shapeType == "Box") ||
                    (props1.shapeType == "Box" && props2.shapeType == "Circle")) {
                    sf::CircleShape* circle = (props1.shapeType == "Circle") ? dynamic_cast<sf::CircleShape*>(shapeA)
                        : dynamic_cast<sf::CircleShape*>(shapeB);
                    sf::RectangleShape* rect = (props1.shapeType == "Box") ? dynamic_cast<sf::RectangleShape*>(shapeA)
                        : dynamic_cast<sf::RectangleShape*>(shapeB);

                    if (circle && rect && RectangleCircleCollision::resolveRectangleCircleCollision(*rect, *circle, normal, depth)) {
                        displacement = normal * (depth / 2.f);
                        rect->move(-displacement);
                        circle->move(displacement);
                    }
                }
         
        }
    }
}