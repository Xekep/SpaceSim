#pragma once
#include "PhysicEngine.h"
#include "CelestialObject.h"
#include "CelestialObjectFactory.h"
#include "Randomizer.h"
#include "Planet.h"
#include "Star.h"
#include "Observer.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include <functional>


class Universe : public Observer
{
public:
	Universe(unsigned int X, unsigned int Y, std::string Title);
	int Run();

private:
	void HandleEvents();
	void CalculatePhysics();
	void DrawUniverse();
	void AddCelestialObject(const sf::Vector2f ObjCoords, CelestialObject::Type Type);
	void HandleWindowCloseEvent(const sf::Event& Event);
	void HandleMouseButtonPressedEvent(const sf::Event& Event);
	void HandleMouseButtonReleasedEvent(const sf::Event& Event);
	void HandleWindowResizedEvent(const sf::Event& Event);
	void HandleKeyPressedEvent(const sf::Event& Event);
	void HandleMouseWheelMovedEvent(const sf::Event& Event);
	void ProcessCameraAndMouse();
	void Zoom(float Factor);
	inline sf::Vector2f GetMousePosition();
	int FindCelestialObject(const sf::Vector2f& Coords);
	void HandleEvent(const Observable& observable) override;
	void MoveCamera(const sf::Vector2f Coords);
	void CameraFollowMouse();

	std::map<sf::Event::EventType, std::function<void(const sf::Event&)>> EventHandlers;
	PhysicEngine _Engine;
	std::vector<std::unique_ptr<CelestialObject>> _Objects;
	std::unique_ptr<sf::RenderWindow> _Window;
	std::unique_ptr<Camera> _Camera;
	Randomizer& _rnd = Randomizer::GetInstance();
	bool IsDragging = false;
	int FollowingObjectId = 0;
	sf::Vector2f _PrevMousePosition;

	const float ZOOM_FACTOR = 0.05f;
};

