#include "Planet.h"
Planet::Planet(const sf::Vector2f& Coords)
	: CelestialObject(Coords)
{
	_SolarMass = _rnd.Generate<float>(0.000003f, 0.0013f);
	_Density = _rnd.Generate<float>(1330, 5520);
	RecalculateRadius();
	_Shape.setFillColor(GetColor());
	SetRandomName();
}
sf::Color Planet::GetColor() const
{
	return SOARING_EAGLE_COLOR;
}
CelestialObject::Type Planet::GetType() const
{
	return Type::Planet;
}
void Planet::SetRandomName() {

	const std::array<std::string, 10> prefixes = { "Ast", "Cos", "Gal", "Hel", "Nep", "Ori", "Per", "Tau", "Ura", "Zet" };
	const std::array<std::string, 10> suffixes = { "on", "os", "er", "onos", "astron", "ite", "onium", "ium", "osm", "on" };
	const std::array<std::string, 7> minorSuffixes = { "ula", "ulae", "ulus", "ule", "ulo", "ulum", "uloa" };

	int prefixIndex = _rnd.Generate() % prefixes.size();
	int suffixIndex = _rnd.Generate() % suffixes.size();
	int minorSuffixIndex = _rnd.Generate() % minorSuffixes.size();

	_Name = prefixes[prefixIndex] + suffixes[suffixIndex] + minorSuffixes[minorSuffixIndex];
}