#pragma once
#include <SFML/Graphics/Color.hpp>
#include "CelestialObject.h"
class Star :
    public CelestialObject
{
public:
    Star(const sf::Vector2f& Coords);
    sf::Color GetColor() const override;
    CelestialObject::Type GetType() const override;

private:
    const float CLASS_O = 10.0f;
    const float CLASS_B = 8.0f;
    const float CLASS_A = 2.0f;
    const float CLASS_F = 1.4f;
    const float CLASS_G = 0.8f;
    const float CLASS_K = 0.4f;
    const float CLASS_M = 0.08f;
    const sf::Color MIDDLE_BLUE_COLOR = sf::Color(126, 214, 223, 255);      //Голубой
    const sf::Color COASTAL_BREEZE_COLOR = sf::Color(223, 249, 251, 255);   // Голубовато-белый
    const sf::Color TURBO_COLOR = sf::Color(249, 202, 36, 255);             // Желтый
    const sf::Color BEEKEEPER_COLOR = sf::Color(246, 229, 141, 255);        // Желтоватый
    const sf::Color CARMINE_PINK_COLOR = sf::Color(235, 77, 75, 255);       // Красный
    const sf::Color QUINCE_JELLY_COLOR = sf::Color(240, 147, 43, 255);      // Оранжевый
};

