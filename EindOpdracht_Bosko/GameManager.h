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
	void StartGame(sf::RenderWindow &window, sf::Event event);
	void SpawnEnemy();
	void DestroyEnemy(Enemy &enemyToRemove);
	void GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef);
	void ReDefineTextures();
	void DrawUI(sf::RenderWindow &window);
	Enemy SelectEnemyType();

	bool gameInProgress;

private:
	void InitialiseText(sf::Text &text, int fontSize, sf::Color color, float posX, float posY, std::string content);

	//Main menu texts
	sf::Text mainMenuText;
	sf::Text highScoreText;
	sf::Text pressEnterToStart;
	sf::Text credits;

	sf::Font font;

	int enemyID = 0;
	int enemyLocation = -1;

	int mainMenuDisplay;
};