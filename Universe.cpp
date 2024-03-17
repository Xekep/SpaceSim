#include "Universe.h"
Universe::Universe(unsigned int X, unsigned int Y, std::string Title)
    : _Window(std::make_unique<sf::RenderWindow>(sf::VideoMode(X, Y), Title))
{
    _Window->setFramerateLimit(60);
    InitializeEventHandlers();
}

void Universe::InitializeEventHandlers()
{
    using namespace std::placeholders;

    EventHandlers.insert({
        {sf::Event::Closed, std::bind(&Universe::HandleWindowCloseEvent, this, _1)},
        {sf::Event::MouseButtonPressed, std::bind(&Universe::HandleMouseButtonPressedEvent, this, _1)},
        {sf::Event::MouseButtonReleased, std::bind(&Universe::HandleMouseButtonReleasedEvent, this, _1)},
        {sf::Event::Resized, std::bind(&Universe::HandleWindowResizedEvent, this, _1)},
        {sf::Event::KeyPressed, std::bind(&Universe::HandleKeyPressedEvent, this, _1)}
    });
}

void Universe::Run()
{
    while (_Window->isOpen())
    {
        HandleEvents();
        ProcessCameraAndMouse();
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
        if (EventHandlers.find(event.type) != EventHandlers.end())
            EventHandlers[event.type](event);
    }
}

void Universe::ProcessCameraAndMouse()
{
    if (IsDragging)
        MoveCamera();

    LastMousePosition = sf::Mouse::getPosition(*_Window);
}

inline void Universe::HandleWindowCloseEvent(const sf::Event& Event)
{
    _Window->close();
}

inline void Universe::HandleMouseButtonPressedEvent(const sf::Event& Event)
{
    auto mousePosition = sf::Mouse::getPosition(*_Window);
    if (Event.mouseButton.button == sf::Mouse::Left)
    {
        auto type = _rnd.Generate<int>(0, 99) <= 90 ? CelestialObject::Type::Planet : CelestialObject::Type::Star;
        AddCelestialObject(mousePosition, type);
    }
    else if (Event.mouseButton.button == sf::Mouse::Right)
    {
        IsDragging = true;
    }

}

inline void Universe::HandleKeyPressedEvent(const sf::Event& Event)
{
    if (Event.key.code == sf::Keyboard::Escape)
        _Window->close();
}

inline void Universe::HandleMouseButtonReleasedEvent(const sf::Event& Event)
{
    if (Event.mouseButton.button == sf::Mouse::Right)
        IsDragging = false;
}

inline void Universe::HandleWindowResizedEvent(const sf::Event& Event)
{
    auto resolution = sf::Vector2i(Event.size.width, Event.size.height);
    auto center = _Window->mapPixelToCoords(resolution / 2);
    sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(resolution));
    sf::View view(visibleArea);
    view.setCenter(center);
    _Window->setView(view);
}

inline void Universe::MoveCamera()
{
    sf::View view = _Window->getView();
    auto mousePosition = sf::Mouse::getPosition(*_Window);
    // Вычисляем насколько сместился курсор и задаем нвоый центр
    sf::Vector2f center = view.getCenter() + sf::Vector2f(LastMousePosition - mousePosition);
    view.setCenter(center);
    _Window->setView(view);
    
}

void Universe::DrawUniverse()
{
    _Window->clear(sf::Color::Black);
    for (auto& object : _Objects)
        object->Draw(*_Window);
    _Window->display();
}

void Universe::AddCelestialObject(const sf::Vector2i CursorCoords, CelestialObject::Type Type)
{
    auto objCoords = _Window->mapPixelToCoords(CursorCoords);
    if (Type == CelestialObject::Type::Planet)
        _Objects.push_back(std::make_unique<Planet>(objCoords));
    else
        _Objects.push_back(std::make_unique<Star>(objCoords));
}