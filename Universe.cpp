#include "Universe.h"
Universe::Universe(unsigned int X, unsigned int Y, std::string Title)
{
    _Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(X, Y), Title);
    _Window->setFramerateLimit(60);
}

void Universe::Run()
{
    while (_Window->isOpen())
    {
        HandleEvents();
        CalculatePhysics();
        DrawUniverse();
    }
}

void Universe::CalculatePhysics()
{
    /*дохера математики*/
}

void Universe::HandleEvents()
{
    sf::Event event;

    while (_Window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            WindowCloseEvent(event);
            break;
        case sf::Event::MouseButtonPressed:
            MouseButtonPressedEvent(event);
            break;
        case sf::Event::MouseButtonReleased:
            MouseButtonReleasedEvent(event);
            break;
        case sf::Event::Resized:
            WindowResizedEvent(event);
            break;
        default:
            break;
        }

        if (IsDragging)
            MoveObjectsWithMouse();
    }
}

inline void Universe::WindowCloseEvent(const sf::Event& event)
{
    _Window->close();
}

inline void Universe::MouseButtonPressedEvent(const sf::Event& event)
{
    auto mousePosition = sf::Mouse::getPosition(*_Window);
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        auto type = _rnd.Generate<int>(0, 99) <= 90 ? CelestialObject::Type::Planet : CelestialObject::Type::Star;
        AddCelestialObject(sf::Vector2f(mousePosition), type);
    }
    if (event.mouseButton.button == sf::Mouse::Right)
    {
        IsDragging = true;
        LastMousePosition = mousePosition;
    }
}

inline void Universe::MouseButtonReleasedEvent(const sf::Event& event)
{
    if (event.mouseButton.button == sf::Mouse::Right)
        IsDragging = false;
}

inline void Universe::WindowResizedEvent(const sf::Event& event)
{
    sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
    _Window->setView(sf::View(visibleArea));
}

inline void Universe::MoveObjectsWithMouse()
{
    auto offset = sf::Vector2f(LastMousePosition - sf::Mouse::getPosition(*_Window));
    for (auto& object : _Objects)
        object->Move(offset);
}

void Universe::DrawUniverse()
{
    _Window->clear(sf::Color::Black);
    for (auto& object : _Objects)
        object->Draw(*_Window);
    _Window->display();
}

void Universe::AddCelestialObject(const sf::Vector2f Coords, CelestialObject::Type Type)
{
    if (Type == CelestialObject::Type::Planet)
        _Objects.push_back(std::make_unique<Planet>(Coords));
    else
        _Objects.push_back(std::make_unique<Star>(Coords));
}