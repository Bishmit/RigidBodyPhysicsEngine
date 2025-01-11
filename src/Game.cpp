#include "Game.h"

namespace Physics {
    Game::Game()
        :WIDTH(1300), HEIGHT(700), window(sf::VideoMode(WIDTH, HEIGHT), "Circle Collision Simulation") {
        window.setFramerateLimit(60);
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
                    // Create and add a new circle at the mouse position
                    auto circle = std::make_unique<sf::CircleShape>(20.f);
                    circle->setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    circle->setFillColor(sf::Color::Green);
                    shapes.push_back(std::move(circle));
                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    // Create and add a new rectangle at the mouse position
                    auto rectangle = std::make_unique<sf::RectangleShape>(sf::Vector2f(50.f, 50.f));
                    rectangle->setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                    rectangle->setFillColor(sf::Color::Green);
                    shapes.push_back(std::move(rectangle));
                }
            }
        }

    }

    void Game::update() {
       
        HandleAllCollision::CollisionManager(shapes);
    }

    void Game::render() {
        window.clear();
        for (const auto &body : shapes) {
            window.draw(*body);
        }
        window.display();
    }
}


