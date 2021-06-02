#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"

class GameManager
{
public:
	GameManager();
	std::vector<Enemy> activeEnemies;
	void SpawnEnemy();
	void DestroyEnemy(Enemy &enemyToRemove);
	void GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef);
	void ReDefineTextures();
	void DrawUI(sf::RenderWindow &window);
	Enemy SelectEnemyType();

	sf::Font font;

private:
	int enemyID = 0;
	int enemyLocation = -1;
};