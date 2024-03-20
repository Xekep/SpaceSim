#include "Universe.h"
using namespace std::placeholders;

Universe::Universe(unsigned int X, unsigned int Y, std::string Title)
    : _Window(std::make_unique<sf::RenderWindow>(sf::VideoMode(X, Y), Title)),
    _Camera(std::make_unique<Camera>(sf::Vector2f( static_cast<float>(X), static_cast<float>(Y)))),
    EventHandlers({
        { sf::Event::Closed, std::bind(&Universe::HandleWindowCloseEvent, this, _1) },
        { sf::Event::MouseButtonPressed, std::bind(&Universe::HandleMouseButtonPressedEvent, this, _1) },
        { sf::Event::MouseButtonReleased, std::bind(&Universe::HandleMouseButtonReleasedEvent, this, _1) },
        { sf::Event::Resized, std::bind(&Universe::HandleWindowResizedEvent, this, _1) },
        { sf::Event::KeyPressed, std::bind(&Universe::HandleKeyPressedEvent, this, _1) },
        { sf::Event::MouseWheelMoved, std::bind(&Universe::HandleMouseWheelMovedEvent, this, _1)}
        })
{
    _Window->setFramerateLimit(60);
}

int Universe::Run()
{
    while (_Window->isOpen())
    {
        HandleEvents();
        ProcessCameraAndMouse();
        CalculatePhysics();
        DrawUniverse();
    }
    return 0;
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

inline sf::Vector2f Universe::GetMousePosition()
{
    return _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
}

void Universe::ProcessCameraAndMouse()
{
    if(IsDragging && !FollowingObjectId)
        CameraFollowMouse();

    _PrevMousePosition = GetMousePosition();
}

void Universe::HandleWindowCloseEvent(const sf::Event& Event)
{
    _Window->close();
}

void Universe::HandleMouseButtonPressedEvent(const sf::Event& Event)
{
    if (Event.mouseButton.button == sf::Mouse::Left)
    {
        auto type = _rnd.Generate<int>(0, 99) <= 90 ? CelestialObject::Type::Planet : CelestialObject::Type::Star;
        AddCelestialObject(GetMousePosition(), type);
    }
    else if (Event.mouseButton.button == sf::Mouse::Right)
    {
        IsDragging = true;
    }
    else if (Event.mouseButton.button == sf::Mouse::Middle)
    {
        FollowingObjectId = FindCelestialObject(GetMousePosition());
    }
}

void Universe::HandleKeyPressedEvent(const sf::Event& Event)
{
    if (Event.key.code == sf::Keyboard::Escape)
        _Window->close();
}

void Universe::HandleMouseButtonReleasedEvent(const sf::Event& Event)
{
    if (Event.mouseButton.button == sf::Mouse::Right)
        IsDragging = false;
}

void Universe::HandleWindowResizedEvent(const sf::Event& Event)
{
    int x = Event.size.width, y = Event.size.height;
    _Camera->reset(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(x), static_cast<float>(y) }));
    _Camera->setCenter(_Window->mapPixelToCoords(sf::Vector2i(x, y) / 2));
    _Window->setView(*_Camera);
}

void Universe::HandleMouseWheelMovedEvent(const sf::Event& Event)
{
    auto delta = Event.mouseWheel.delta;
    Zoom(delta < 0 ? 1.f + ZOOM_FACTOR : 1.f - ZOOM_FACTOR);
}

void Universe::Zoom(float Factor)
{
    _Camera->modifyZoom(Factor, _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window)));
    _Window->setView(*_Camera);
}

int Universe::FindCelestialObject(const sf::Vector2f& Coords)
{
    for (auto& object : _Objects)
    {
        auto delta = object->GetPosition() - Coords;
        float distance = std::hypot(delta.x, delta.y);
        if (distance <= object->GetRadius())
            return object->GetId();
    }
    return 0;
}

void Universe::CameraFollowMouse()
{
    // Вычисляем насколько сместился курсор и задаем нвоый центр
    auto center = _Camera->getCenter() + _PrevMousePosition - GetMousePosition();
    MoveCamera(center);
}


void Universe::MoveCamera(const sf::Vector2f Coords)
{
    _Camera->setCenter(Coords);
    _Window->setView(*_Camera);
}

void Universe::DrawUniverse()
{
    _Window->clear(sf::Color::Black);
    for (auto& object : _Objects)
        object->Draw(*_Window);
    _Window->display();
}

void Universe::AddCelestialObject(const sf::Vector2f ObjCoords, CelestialObject::Type Type)
{
    auto object = CelestialObjectFactory::CreateObject(Type, ObjCoords);
    object->AddObserver(*this);
    _Objects.push_back(std::move(object));
}

void Universe::HandleEvent(const Observable& Observable)
{
    if (typeid(Observable) != typeid(CelestialObject))
        return;
    auto& object = dynamic_cast<const CelestialObject&>(Observable);
    if (object.GetId() == FollowingObjectId)
    {
        MoveCamera(object.GetPosition());
    }
}