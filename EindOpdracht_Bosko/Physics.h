#pragma once
#include <SFML/Graphics.hpp>

class Physics
{
public:
	float velocitySpeed = 50;
	float friction = -0.01f;
	sf::Vector2f CalculateSpeed();
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Clock deltaClock;
	sf::Time deltaTime;
};

