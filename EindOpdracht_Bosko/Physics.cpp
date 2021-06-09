#include "Physics.h"

sf::Vector2f Physics::CalculateSpeed()
{
	deltaTime = deltaClock.restart(); // Set deltatime

	acceleration += friction * velocity; // Friction

	sf::Vector2f calcSpeed = sf::Vector2f(deltaTime.asSeconds() * velocity + acceleration); // Calculate acceleration

	velocity += deltaTime.asSeconds() * acceleration * velocitySpeed; // Set velocity
	acceleration = sf::Vector2f(0, 0);

	return calcSpeed;
}