#include "Star.h"
Star::Star(const sf::Vector2f& Coords, float Density, float Mass)
	: CelestialObject(Coords, Density, Mass)
{
	RecalculateRadius();
	_Shape.setFillColor(GetColor());
	SetName("Red dwarf");
}
sf::Color Star::GetColor() const
{
	// Определение спектрального класса
	// https://en.wikipedia.org/wiki/Stellar_classification
	// https://en.wikipedia.org/wiki/Spectral_type
	// O - гиганты (масса > 10 M⊙)
	// B - супергиганты (8 <= mass <= 100 M⊙)
	// A - гиганты (2 <= mass <= 8 M⊙)
	// F - субгиганты (1.4 <= mass <= 2 M⊙)
	// G - главная последовательность (0.8 <= mass <= 1.4 M⊙)
	// K - красные гиганты (0.4 <= mass <= 0.8 M⊙)
	// M - красные субгиганты (0.08 <= mass <= 0.4 M⊙)
	// L - белые карлики (0.08 <= mass <= 0.08 M⊙)
	// T - белые карлики (0.0001 <= mass <= 0.08 M⊙)
	// Y - белые карлики (0.000001 <= mass <= 0.0001 M⊙)

	if (_SolarMass >= CLASS_O)
		return MIDDLE_BLUE_COLOR;
	else if (_SolarMass >= CLASS_B)
		return COASTAL_BREEZE_COLOR;
	else if (_SolarMass >= CLASS_A)
		return sf::Color::White;
	else if (_SolarMass >= CLASS_F)
		return BEEKEEPER_COLOR;
	else if (_SolarMass >= CLASS_G)
		return TURBO_COLOR;
	else if (_SolarMass >= CLASS_K)
		return QUINCE_JELLY_COLOR;
	else
		return CARMINE_PINK_COLOR;
}
CelestialObject::Type Star::GetType() const
{
	return Type::Star;
}