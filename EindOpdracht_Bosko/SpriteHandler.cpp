#include "SpriteHandler.h"
#include <iostream>

SpriteHandler::SpriteHandler(float spawnX, float spawnY, std::string pathToImage)
{
	sf::Texture texture;
	texture.loadFromFile(pathToImage);

	_texture = texture;

	sf::Sprite sprite;

	_sprite = sprite;
	_sprite.setTexture(_texture);
	_sprite.setPosition(spawnX, spawnY);
}

void SpriteHandler::Update(sf::RenderWindow &window)
{
	window.draw(_sprite);
}