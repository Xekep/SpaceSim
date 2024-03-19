#pragma once
#include "CelestialObject.h"
#include "Randomizer.h"
#include <SFML/Graphics/Color.hpp>
class Planet :
    public CelestialObject
{
public:
    Planet(const sf::Vector2f& Coords, float Density, float Mass);
    sf::Color GetColor() const override;
    CelestialObject::Type GetType() const override;
private:
    void SetRandomName();

    const sf::Color SOARING_EAGLE_COLOR = sf::Color(149, 175, 192, 255);
    Randomizer& _Rnd = Randomizer::GetInstance();
};

