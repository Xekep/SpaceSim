#pragma once
#include "PhysicEngine.h"
#include "CelestialObject.h"
#include "Randomizer.h"
#include "Planet.h"
#include "Star.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Universe
{
public:
	Universe(unsigned int X, unsigned int Y, std::string Title);
	void Run();

private:
	void HandleEvents();
	void CalculatePhysics();
	void DrawUniverse();
	void AddCelestialObject(const sf::Vector2f, CelestialObject::Type Type);
    inline void WindowCloseEvent(const sf::Event& event);
    inline void MouseButtonPressedEvent(const sf::Event& event);
    inline void MouseButtonReleasedEvent(const sf::Event& event);
	inline void WindowResizedEvent(const sf::Event& event);
	inline void MoveObjectsWithMouse();

	PhysicEngine _Engine;
	std::vector < std::unique_ptr<CelestialObject>> _Objects;
	std::unique_ptr<sf::RenderWindow> _Window;
	Randomizer& _rnd = Randomizer::GetInstance();
	bool IsDragging = false;
	sf::Vector2i LastMousePosition;
};

