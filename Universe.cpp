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
        if (event.type == sf::Event::Closed)
            _Window->close();
        else if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            auto mousePosition = sf::Mouse::getPosition(*_Window);
            auto type = _rnd.Generate<int>(0, 99) <= 90 ? CelestialObject::Type::Planet : CelestialObject::Type::Star;
            AddCelestialObject(sf::Vector2f(mousePosition), type);
        }
        else if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            _Window->setView(sf::View(visibleArea));
        }
    }
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