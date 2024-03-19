#include "CelestialObject.h"

CelestialObject::CelestialObject(const sf::Vector2f& Coords, float Density, float Mass)
	: _Id(++_NextId), _Density(Density), _SolarMass(Mass)
{
	_Shape.setPosition(Coords);
}
void CelestialObject::SetShader(std::shared_ptr<sf::Shader> Shader)
{
	_Shader = Shader;
}
void CelestialObject::SetPosition(const sf::Vector2f& Coords)
{
	_Shape.setPosition(Coords);
	NotifyObservers();
}
sf::Vector2f CelestialObject::GetPosition() const
{
	return _Shape.getPosition();
}
void CelestialObject::MoveWithAcceleration(const sf::Vector2f& Acceleration)
{
	_Velocity += Acceleration;
	SetPosition(_Shape.getPosition() + _Velocity);
}
int CelestialObject::GetId() const
{
	return _Id;
}
void CelestialObject::Draw(sf::RenderWindow& window) const
{
	if(_Shader)
		window.draw(_Shape, _Shader.get());
	else
		window.draw(_Shape);
}
std::string CelestialObject::GetName() const
{
	return _Name;
}
void CelestialObject::SetName(const std::string Name)
{
	_Name = Name;
}
void CelestialObject::SetDensity(float Density)
{
	_Density = Density;
	RecalculateRadius();
}
float CelestialObject::GetDensity() const
{
	return _Density;
}
void CelestialObject::SetMass(float SolarMass)
{
	_SolarMass = SolarMass;
	RecalculateRadius();
}
float CelestialObject::GetMass() const
{
	return _SolarMass;
}
float CelestialObject::GetRadius() const
{
	return _Shape.getRadius();
}
void CelestialObject::RecalculateRadius()
{
	// масса/плотность = объем
	// формула объема шара: объем = (4/3)*п*r ^ 3
	// выводим формулу радиуса шара: радиус = ((масса/плотность)/(4/3*п))^(1/3)
	// средн€€ плотность звезды пропорциональна€ массе и обратно пропорциональна радиусу
	float radius = std::cbrtf((_SolarMass * SOLAR_MASS / _Density) / (4.f / 3.f * static_cast<float>(M_PI))) / 100000 / 50;
	_Shape.setRadius(radius);
	_Shape.setOrigin(radius, radius);
}
int CelestialObject::_NextId = 0;