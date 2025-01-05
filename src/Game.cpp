#include "Game.h"
#include <ctime>
#include <cstdlib>
#include<iostream>


#include "RectangleCircleCollision.h"

namespace Physics {
    Game::Game()
        : window(sf::VideoMode(800, 600), "Circle Collision Simulation"),
        controllableCircle(radius), spawnInterval(sf::seconds(2.f)) {

        window.setFramerateLimit(60);
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        initCircles(); 
        initRectangles(); 
    }

    void Game::run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

    void Game::initCircles()
    {
        // Initialize 8 circles with random positions
        for (int i = 0; i < 2; ++i) {

            sf::CircleShape circle(radius);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(
                static_cast<float>(std::rand() % (800 - static_cast<int>(2 * radius))),
                static_cast<float>(std::rand() % (600 - static_cast<int>(2 * radius)))
            );
            bodies.push_back(circle);
        }

        // Initialize controllable circle
        controllableCircle.setRadius(radius);
        controllableCircle.setFillColor(sf::Color::Red);
        controllableCircle.setPosition(400.f, 300.f);
        bodies.push_back(controllableCircle);
    }

    void Game::initRectangles()
    {
        const float width = 150.f;
        const float height = 150.f;

        // Initialize 8 rectangles with random positions
        /*for (int i = 0; i < 2; ++i) {
            sf::RectangleShape rectangle(sf::Vector2f(width, height));
            rectangle.setFillColor(sf::Color::Green);
            rectangle.setPosition(
                static_cast<float>(std::rand() % (800 - static_cast<int>(width))),
                static_cast<float>(std::rand() % (600 - static_cast<int>(height)))
            );
            rectBodies.push_back(rectangle);
        }*/

        rectangle.setFillColor(sf::Color::Green);
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(450.f, 150.f); 

        // Initialize controllable rectangle
       /* rect.setSize(sf::Vector2f(width, height));
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(400.f, 300.f);*/
       // rectBodies.push_back(rect);
    }

    void Game::processEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //if (event.type == sf::Event::MouseButtonPressed) {
            //    if (event.mouseButton.button == sf::Mouse::Left) {
            //        sf::RectangleShape remRect(sf::Vector2f(50.f, 50.f));
            //        remRect.setFillColor(sf::Color::Green);
            //        remRect.setPosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            //        //rectBodies.push_back(remRect);
            //    }
            //}
        }

        // Control the red circle with arrow keys
        const float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && controllableCircle.getPosition().y > 0) {
            controllableCircle.move(0.f, -movespeed*deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && controllableCircle.getPosition().y < 540) {
            controllableCircle.move(0.f, movespeed*deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && controllableCircle.getPosition().x > 0) {
            controllableCircle.move(-movespeed*deltaTime, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && controllableCircle.getPosition().x < 740) {
            controllableCircle.move(movespeed*deltaTime, 0.f);
        }

        // control the one rectangle
      /*  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rect.getPosition().y > 0) {
            rect.move(0.f, -movespeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rect.getPosition().y < 540) {
            rect.move(0.f, movespeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rect.getPosition().x > 0) {
            rect.move(-movespeed * deltaTime, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rect.getPosition().x < 740) {
            rect.move(movespeed * deltaTime, 0.f);
        }*/


    }

    void Game::update() {
        //bodies.back() = controllableCircle;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !isEnterPressed) {
           // rect.rotate(45.f);
            isEnterPressed = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            isEnterPressed = false;
        }

          //rectBodies.back() = rect;
          //ResolveCollisions(bodies);
         //RectangleCollision::resolvePolygonCollisions(rectBodies);
        RectangleCircleCollision::resolveRectangleCircleCollision(rectangle, controllableCircle);
        //std::cout << "Position: " << controllableCircle.getPosition().x << ", " << controllableCircle.getPosition().y << std::endl;
    }

    void Game::render() {
        window.clear();
       /* for (const auto& body : bodies) {
            window.draw(body);
        }
       for (const auto& r : rectBodies) {
           window.draw(r);
       }*/
        window.draw(rectangle); 
        window.draw(controllableCircle); 

        window.display();
    }
}
