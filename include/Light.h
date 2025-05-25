#pragma once
#include "Common.h"

class Light {
public:
    sf::CircleShape shape; // Forma de luz
    float intensity;       // Intensidad de la luz

    Light(float radius, float intensity): intensity(intensity) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(intensity))); // Color blanco
        shape.setOrigin(radius, radius); // Para centrar la luz
    }
    ~Light() = default;

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};