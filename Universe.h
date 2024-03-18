#pragma once
#include "PhysicEngine.h"
#include "CelestialObject.h"
#include "Randomizer.h"
#include "Planet.h"
#include "Star.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include <functional>


class Universe
{
public:
	Universe(unsigned int X, unsigned int Y, std::string Title);
	void Run();

private:
	void InitializeEventHandlers();
	void HandleEvents();
	void CalculatePhysics();
	void DrawUniverse();
	void AddCelestialObject(const sf::Vector2i CursorCoords, CelestialObject::Type Type);
	void HandleWindowCloseEvent(const sf::Event& Event);
	void HandleMouseButtonPressedEvent(const sf::Event& Event);
	void HandleMouseButtonReleasedEvent(const sf::Event& Event);
	void HandleWindowResizedEvent(const sf::Event& Event);
	void HandleKeyPressedEvent(const sf::Event& Event);
	void HandleMouseWheelMovedEvent(const sf::Event& Event);
	void MoveCamera();
	void ProcessCameraAndMouse();
	void Zoom(float Factor);

	std::map<sf::Event::EventType, std::function<void(const sf::Event&)>> EventHandlers;
	PhysicEngine _Engine;
	std::vector < std::unique_ptr<CelestialObject>> _Objects;
	std::unique_ptr<sf::RenderWindow> _Window;
	Randomizer& _rnd = Randomizer::GetInstance();
	bool IsDragging = false;
	sf::Vector2i LastMousePosition;
};

