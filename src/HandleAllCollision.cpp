#include "HandleAllCollision.h"

void HandleAllCollision::CollisionManager(std::vector<std::unique_ptr<sf::Shape>>& shapes) {
    for (size_t i = 0; i < shapes.size(); ++i) {
        for (size_t j = i + 1; j < shapes.size(); ++j) {
            sf::CircleShape* circle1 = dynamic_cast<sf::CircleShape*>(shapes[i].get());
            sf::CircleShape* circle2 = dynamic_cast<sf::CircleShape*>(shapes[j].get());
            sf::RectangleShape* rect1 = dynamic_cast<sf::RectangleShape*>(shapes[i].get());
            sf::RectangleShape* rect2 = dynamic_cast<sf::RectangleShape*>(shapes[j].get());

            sf::Vector2f normal;
            float depth;
            sf::Vector2f displacement;
            if (circle1 && circle2) {
                if (CircleCollision::IntersectCircles(circle1->getPosition(), circle1->getRadius(),
                    circle2->getPosition(), circle2->getRadius(),
                    normal, depth)) {
                    displacement = normal * (depth / 2.f);
                    circle1->move(-displacement);
                    circle2->move(displacement);
                }
            }

            if (rect1 && rect2) {
                if (RectangleCollision::checkCollision(*rect1, *rect2, normal, depth)) {
                    displacement = normal * (depth / 2.f);
                    rect1->move(-displacement);
                    rect2->move(displacement);
                }
            }

            if ((rect1 && circle2) || (rect2 && circle1)) {
                sf::RectangleShape* rect = rect1 ? rect1 : rect2;
                sf::CircleShape* circle = circle1 ? circle1 : circle2;

                if (rect && circle && RectangleCircleCollision::resolveRectangleCircleCollision(*rect, *circle, normal, depth)) {
                    displacement = normal * (depth / 2.f);
                    rect->move(-displacement);
                    circle->move(displacement);
                }
            }
        }
    }
}
