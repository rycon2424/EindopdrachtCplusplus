#include "BackGround.h"

void BackGround::Update(sf::RenderWindow & window)
{
	_sprite.move(0, movingSpeed);
	if (_sprite.getPosition().y > 0)
	{
		_sprite.setPosition(0, -700);
	}
	SpriteHandler::Update(window);
}
