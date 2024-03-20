#pragma once
#include <SFML/Graphics.hpp>
class Camera : public sf::View
{
public:
	Camera(const sf::Vector2f Resolution)
	{
        reset(sf::FloatRect({ 0.f, 0.f }, Resolution));
	}

    void modifyZoom(float Factor, const sf::Vector2f MousePosition)
    {
        sf::Vector2f center = getCenter();
        sf::Vector2f newCenter = center;
        if (Factor > 1.f)
            newCenter += (center - MousePosition) / 20.f;
        else
            newCenter -= (center - MousePosition) / 20.f;
        setCenter(newCenter);
        zoom(Factor);
    }
};

