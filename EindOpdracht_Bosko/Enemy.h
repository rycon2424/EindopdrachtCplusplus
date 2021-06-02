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
		_sprite.setScale(-(float)0.03, (float)0.03);
	};
	void Update(sf::RenderWindow &window, sf::Sprite &playerRef);
	void SetGameManager(GameManager* gameManager);
	void SetSpeed(float xSpeed, float ySpeed);

private: 
	GameManager* gm;
	float speedY;
	float speedX;
	bool movingLeft = true;

	void Movement();
	void CollisionDetection(sf::Sprite &playerRef);
};