#pragma once
#include <SFML\Graphics.hpp>
class Circles
{
private:
	float radius{ 100.f };
public:
	sf::CircleShape circle{ 100.f };
	sf::Vector2f position;
	sf::Vector2f velocity;
	void setVelocity(sf::Vector2f v);
};

