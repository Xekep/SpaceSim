#include "CelestialObjectFactory.h"
std::unique_ptr<CelestialObject> CelestialObjectFactory::CreateObject(CelestialObject::Type Type, const sf::Vector2f& ObjCoords) {
    if (Type == CelestialObject::Star)
        return CreateStar(ObjCoords);
    else
        return CreatePlanet(ObjCoords);
}

std::unique_ptr<CelestialObject> CelestialObjectFactory::CreateStar(const sf::Vector2f& ObjCoords) {
    float mass = 0.09f;
    float density = SOLAR_DENSITY * 50;
    return std::make_unique<Star>(ObjCoords, density, mass);
}

std::unique_ptr<CelestialObject> CelestialObjectFactory::CreatePlanet(const sf::Vector2f& ObjCoords) {
    const float PLANET_MASS_MIN = 0.000003f;
    const float PLANET_MASS_MAX = 0.0013f;
    const float PLANET_DENSITY_MIN = 1330.0f;
    const float PLANET_DENSITY_MAX = 5520.0f;
    auto& rnd = Randomizer::GetInstance();

    float mass = rnd.Generate<float>(PLANET_MASS_MIN, PLANET_MASS_MAX);
    float density = rnd.Generate<float>(PLANET_DENSITY_MIN, PLANET_DENSITY_MAX);
    return std::make_unique<Planet>(ObjCoords, density, mass);
}

