#include "Game.h"
#include "HandleAllCollision.h"

namespace Physics {
    Game::Game()
        : WIDTH(1300), HEIGHT(700), window(sf::VideoMode(WIDTH, HEIGHT), "Circle Collision Simulation") {
        window.setFramerateLimit(60);

        // Create a static platform at the bottom of the screen
        shapes.push_back(std::move(createBody(true, physicsMap, "Box", { 600.f, 10.f }, 0.f, { 350.f, 650.f }, { 0.f, 0.f })));

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
                    // Create a dynamic rectangle at a predefined position
                    auto rect = createBody(false, physicsMap, "Box", { 100.f, 50.f }, 0.f, { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) }, {0.f, 0.f});
                    shapes.push_back(std::move(rect));
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // Create a dynamic circle at a predefined position
                    auto circle = createBody(false, physicsMap, "Circle", {}, 25.f, { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) }, { 0.5f, 0.f });
                    shapes.push_back(std::move(circle));
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

    std::unique_ptr<sf::Shape> Game::createBody(
        bool isStatic,
        std::unordered_map<sf::Shape*, PhysicsManger>& physicsMap,
        const std::string& shapeType,
        const sf::Vector2f& size,
        float radius,
        const sf::Vector2f& position,
        const sf::Vector2f& initialVelocity
    ) {
        std::unique_ptr<sf::Shape> shape;

        if (shapeType == "Circle") {
            shape = std::make_unique<sf::CircleShape>(radius);
        }
        else if (shapeType == "Box") {
            shape = std::make_unique<sf::RectangleShape>(size);
        }
        else {
            throw std::invalid_argument("Invalid ShapeType! Must be 'Circle' or 'Box'.");
        }
        shape->setPosition(position);
        shape->setFillColor(isStatic ? sf::Color::Cyan : sf::Color::White);

        PhysicsManger props;
        props.shapeType = shapeType;
        props.isStatic = isStatic;
        props.mass = isStatic ? 0.0f : 1.0f;
        props.velocity = isStatic ? sf::Vector2f(0.f, 0.f) : initialVelocity;
        props.restitution = 0.5f;
        props.area = (shapeType == "Circle") ? 3.14159f * radius * radius : size.x * size.y;

        physicsMap[shape.get()] = props;
        return shape;
    }
}
