#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>

class SpriteHandler
{
public:
	sf::Sprite _sprite;
	sf::Texture _texture;

	SpriteHandler(float spawnX, float spawnY, std::string pathToImage);
	void Update(sf::RenderWindow &window);

};

