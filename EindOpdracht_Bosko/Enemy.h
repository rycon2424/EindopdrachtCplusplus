#pragma once
#include <iostream>
#include "SpriteHandler.h"

class GameManager;

class Enemy : public SpriteHandler
{
public:
	int ID;
	Enemy(float spawnX, float spawnY, std::string pathToImage) :SpriteHandler(spawnX, spawnY, pathToImage)
	{
		_sprite.setScale(-(float)0.3, (float)0.3);
	};
	void Update(sf::RenderWindow &window, sf::Sprite &playerRef);
	void SetGameManager(GameManager* gameManager);

private: 
	GameManager* gm;
	bool movingLeft = true;
	void Movement();
	void CollisionDetection(sf::Sprite &playerRef);
};