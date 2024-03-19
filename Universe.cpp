#include "Universe.h"
using namespace std::placeholders;

Universe::Universe(unsigned int X, unsigned int Y, std::string Title)
    : _Window(std::make_unique<sf::RenderWindow>(sf::VideoMode(X, Y), Title)),
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
    if (IsDragging)
        MoveCamera();

    PrevMousePosition = GetMousePosition();
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
    {
        IsDragging = false;
    }
}

void Universe::HandleWindowResizedEvent(const sf::Event& Event)
{
    auto resolution = sf::Vector2i(Event.size.width, Event.size.height);
    auto center = _Window->mapPixelToCoords(resolution / 2);
    sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(resolution));
    sf::View view(visibleArea);
    view.setCenter(center);
    _Window->setView(view);
}

void Universe::HandleMouseWheelMovedEvent(const sf::Event& Event)
{
    auto delta = Event.mouseWheel.delta;
    Zoom(delta < 0 ? 1.f + ZOOM_FACTOR : 1.f - ZOOM_FACTOR);
}

void Universe::Zoom(float Factor)
{
    sf::View view = _Window->getView();
    auto& center = view.getCenter();
    auto mouseWorldPosition = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
    auto newCenter = center;
    if(Factor > 1.f)
        newCenter += (center - mouseWorldPosition) / 20.f;
    else
        newCenter -= (center - mouseWorldPosition) / 20.f;
    view.setCenter(newCenter);
    view.zoom(Factor);
    _Window->setView(view);
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

void Universe::MoveCamera()
{
    sf::View view = _Window->getView();
    // Вычисляем насколько сместился курсор и задаем нвоый центр
    auto center = view.getCenter() + PrevMousePosition - GetMousePosition();
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

void Universe::AddCelestialObject(const sf::Vector2f ObjCoords, CelestialObject::Type Type)
{
    auto object = CelestialObjectFactory::CreateObject(Type, ObjCoords);
    object->AddObserver(this);
    _Objects.push_back(std::move(object));
}

void Universe::HandleEvent(Observable* observable)
{
    if (typeid(observable) != typeid(CelestialObject))
        return;
    CelestialObject* object = dynamic_cast<CelestialObject*>(observable);
    //if(object->GetId() == FollowingObjectId)
        //
}