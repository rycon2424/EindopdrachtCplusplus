#pragma once
#include "SpriteHandler.h"

class BackGround : public SpriteHandler
{
public:
	BackGround(float spawnX, float spawnY, std::string pathToImage) :SpriteHandler(spawnX, spawnY, pathToImage) {};
	~BackGround();
	void Update(sf::RenderWindow &window);
private:
	float movingSpeed = 10;
};