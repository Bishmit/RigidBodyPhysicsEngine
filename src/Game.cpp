#include "Game.h"

namespace Physics {
    Game::Game()
        :WIDTH(1300), HEIGHT(700), window(sf::VideoMode(WIDTH, HEIGHT), "Circle Collision Simulation") {
        window.setFramerateLimit(60);
        shapes.push_back(std::move(createBody(false, physicsMap, "Box", { 600.f, 10.f }, 0.f)));
    }

    void Game::run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    void Game::processEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    shapes.push_back(std::move(createBody(true, physicsMap, "Circle", { 0.f, 0.f }, 25.f)));
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // Create and add a new rectangle at the mouse position
                    shapes.push_back(std::move(createBody(true, physicsMap, "Box", { 25.f, 25.f }, 0.f)));
                }
            }
        }

    }

    void Game::update() {
        
        HandleAllCollision::CollisionManager(shapes, physicsMap);
    }

    void Game::render() {
        window.clear();
        for (const auto& body : shapes) {
            window.draw(*body);
        }
        window.display();
    }

    std::unique_ptr<sf::Shape> Game::createBody(bool isStatic,
        std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap, const std::string& shapeType,
        const sf::Vector2f& size, float radius)
    {
        std::unique_ptr<sf::Shape> shape;

        // Create a shape based on the shape type
        if (shapeType == "Circle") {
            shape = std::make_unique<sf::CircleShape>(radius);
        }
        else if (shapeType == "Box") {
            shape = std::make_unique<sf::RectangleShape>(size);
        }
        else {
            throw std::invalid_argument("Invalid ShapeType!");
        }

        // Set the position to the mouse click position
        
         if (isStatic) {
             shape->setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
             shape->setFillColor(sf::Color::Green); 
         }
         else {
             shape->setPosition(350.f, 500.f);
             shape->setFillColor(sf::Color::Red);
         }

        // Setting up the physics properties
        PhysicsManger props;
        props.shapeType = shapeType;
        props.isStatic = isStatic;
        props.mass = isStatic ? std::numeric_limits<float>::infinity() : 1.0f;
        props.velocity = isStatic ? sf::Vector2f(0.f, 0.f) : sf::Vector2f(0.1f, 0.f);
        props.restitution = 0.5f;
        props.area = (shapeType == "Circle") ? 3.14159f * radius * radius : size.x * size.y;

        // Add the shape to the physics map
        physicsMap[shape.get()] = props;

        return shape;
    }
}


