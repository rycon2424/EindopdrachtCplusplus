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

	float velocitySpeed = 50;
	float speedY;
	float speedX;

	sf::Vector2f CalculateSpeed();
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Clock deltaClock;
	sf::Time deltaTime;

	void Movement();
	void CollisionDetection(sf::Sprite &playerRef);
};