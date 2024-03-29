﻿#pragma once
#define _USE_MATH_DEFINES
#include "Randomizer.h"
#include "Observable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <array>
#include <string>
#include <iostream>
#include <memory>

#define SOLAR_MASS static_cast<float>(1.98847e+30)
#define SOLAR_DENSITY 1.41f * 1000

class CelestialObject : public Observable
{
public:
	enum Type : int {
		Planet,
		Star
	};

	virtual ~CelestialObject() {}
	void SetShader(std::shared_ptr<sf::Shader> Shader);
	CelestialObject(const sf::Vector2f& Coords, float Density, float Mass);
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
	void MoveWithAcceleration(const sf::Vector2f& Acceleration);
	int GetId() const;

protected:
	void RecalculateRadius();

	std::string _Name;
	int _Id = 0;
	float _SolarMass = 1.f; // солнечная масса M⊙
	float _Density = 0.f;	// плотность кг/м^3
	sf::Vector2f _Velocity;
	sf::CircleShape _Shape;

private:
	std::shared_ptr<sf::Shader> _Shader;
	static int _NextId;
};