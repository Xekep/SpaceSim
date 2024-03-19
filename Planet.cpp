#include "Planet.h"
Planet::Planet(const sf::Vector2f& Coords, float Density, float Mass)
	: CelestialObject(Coords, Density, Mass)
{
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

	const std::vector<std::string> prefixes = { "Ast", "Cos", "Gal", "Hel", "Nep", "Ori", "Per", "Tau", "Ura", "Zet" };
	const std::vector<std::string> suffixes = { "on", "os", "er", "onos", "astron", "ite", "onium", "ium", "osm", "on" };
	const std::vector<std::string> minorSuffixes = { "ula", "ulae", "ulus", "ule", "ulo", "ulum", "uloa" };

	auto rand = [=](const auto& array) {
		int index = _Rnd.Generate(static_cast<int>(array.size()) - 1);
		return array[index];
	};

	_Name = rand(prefixes) + rand(suffixes) + rand(minorSuffixes);
}