#include "CelestialObject.h"

CelestialObject::CelestialObject(const sf::Vector2f& Coords)
{
	_Shape.setPosition(Coords);
}
void CelestialObject::SetPosition(const sf::Vector2f& Coords)
{
	_Shape.setPosition(Coords);
}
sf::Vector2f CelestialObject::GetPosition() const
{
	return _Shape.getPosition();
}
void CelestialObject::Move(const sf::Vector2f& Offset)
{
	SetPosition(GetPosition() + Offset);
}
void CelestialObject::MoveWithAcceleration(const sf::Vector2f& Acceleration)
{
	_Velocity += Acceleration;
	_Shape.setPosition(_Shape.getPosition() + _Velocity);
}
void CelestialObject::Draw(sf::RenderWindow& window) const {
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
	// �����/��������� = �����
	// ������� ������ ����: ����� = (4/3)*�*r ^ 3
	// ������� ������� ������� ����: ������ = ((�����/���������)/(4/3*�))^(1/3)
	// ������� ��������� ������ ���������������� ����� � ������� ��������������� �������
	float radius = std::cbrtf((_SolarMass * SOLAR_MASS / _Density) / (4.f / 3.f * (float)M_PI)) / 100000 / 50;
	_Shape.setRadius(radius);
	_Shape.setOrigin(radius, radius);
}