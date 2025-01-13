#pragma once
#include <SFML/Graphics.hpp>	
#include <unordered_map>
#include <iostream>

    struct PhysicsManger {
        sf::Vector2f velocity{ 0.f, 0.f };
        float mass = 1.f;
        float restitution = 0.5f;
        bool isStatic = false;
        float density = 1.f;
        float area = 0.f;
        std::string shapeType;
    };

