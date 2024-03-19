#pragma once
#include "Planet.h"
#include "Star.h"
#include "Randomizer.h"
#include <memory>

class CelestialObjectFactory {
public:
    static std::unique_ptr<CelestialObject> CreateObject(CelestialObject::Type Type, const sf::Vector2f& ObjCoords);
    static std::unique_ptr<CelestialObject> CreateStar(const sf::Vector2f& ObjCoords);
    static std::unique_ptr<CelestialObject> CreatePlanet(const sf::Vector2f& ObjCoords);
};