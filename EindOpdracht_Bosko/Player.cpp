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
			_sprite.move(5, 0);
		}
	}
	if (currentPosition.x > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			_sprite.move(-5, 0);
		}
	}
	if (currentPosition.y > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			_sprite.move(0, -2.5f);
		}
	}
	if (currentPosition.y < 580)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			_sprite.move(0, 5);
		}
	}
}