#pragma once
#define _USE_MATH_DEFINES
#include "Randomizer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <array>
#include <string>
#include <iostream>

class CelestialObject
{
public:
	enum Type : int {
		Planet,
		Star
	};
	const float SOLAR_MASS = (float)1.98847e+30;
	const float SOLAR_DENSITY = 1.41 * 1000;

	CelestialObject(const sf::Vector2f& Coords);
	std::string GetName() const;
	void SetName(const std::string Name);
	void SetDensity(float Density);
	float GetDensity() const;
	void SetMass(float SolarMass);
	float GetMass() const;
	float GetRadius() const;
	virtual sf::Color GetColor() const = 0;
	virtual Type GetType() const = 0;
	void Draw(sf::RenderWindow& window) const;
	void SetPosition(const sf::Vector2f& Coords);
	sf::Vector2f GetPosition() const;
	void Move(const sf::Vector2f& Offset);
	void MoveWithAcceleration(const sf::Vector2f& Acceleration);


protected:
	void RecalculateRadius();

	std::string _Name;
	float _SolarMass = 0.f; // солнечная масса M⊙
	float _Density = 0.f;	// плотность кг/м^3
	sf::Vector2f _Velocity;
	sf::CircleShape _Shape;
};

