#include "Player.h"

void Player::Update(sf::RenderWindow &window, sf::Event event)
{
	SpriteHandler::Update(window);
	Move(event);
}

Player::~Player() {}

void Player::Move(sf::Event event)
{
	const sf::Vector2f& currentPosition = _sprite.getPosition();
	if (currentPosition.x < 650)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			acceleration.x = 2;
		}
	}
	if (currentPosition.x > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			acceleration.x = -2;
		}
	}
	if (currentPosition.y > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			acceleration.y = -1;
		}
	}
	if (currentPosition.y < 580)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			acceleration.y = 3;
		}
	}
	if (currentPosition.y > 580 || currentPosition.y < 0 || currentPosition.x < 0 || currentPosition.x > 650)
	{
		velocity *= 0.0f;
	}
	
	_sprite.move(CalculateSpeed());
}
