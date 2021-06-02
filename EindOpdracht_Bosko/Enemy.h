#pragma once
#include <iostream>
#include "SpriteHandler.h"

class GameManager;

class Enemy : public SpriteHandler
{
public:
	int ID;
	Enemy(float spawnX, float spawnY, std::string pathToImage) :SpriteHandler(spawnX, spawnY, pathToImage) {};
	void Update(sf::RenderWindow &window, sf::Sprite &playerRef);
	void SetGameManager(GameManager* gameManager);
	void SetSpeed(float xSpeed, float ySpeed);
	void SetScale(float xScale, float yScale);

	bool movingLeft = true;

private: 
	GameManager* gm;
	float speedY;
	float speedX;

	void Movement();
	void CollisionDetection(sf::Sprite &playerRef);
};