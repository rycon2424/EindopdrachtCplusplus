#pragma once

#include "SpriteHandler.h"

class Player : public SpriteHandler
{
public:
	Player(float spawnX, float spawnY, std::string pathToImage) :SpriteHandler(spawnX, spawnY, pathToImage) 
	{
		_sprite.setScale((float)0.225, (float)0.225);
	};
	~Player();
	void Update(sf::RenderWindow &window, sf::Event event);

private:
	void Move(sf::Event event);
};

