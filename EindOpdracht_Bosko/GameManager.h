#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include <iomanip>

class GameManager
{
public:
	GameManager();
	~GameManager();
	std::vector<Enemy> activeEnemies;
	void StartGame(sf::RenderWindow &window, sf::Event event);
	void GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef);
	void DestroyEnemy(Enemy &enemyToRemove);

	int highscore;
	bool gameInProgress;
	int enemySpawnInterval = 80;

private:
	void InitialiseText(sf::Text &text, int fontSize, sf::Color color, float posX, float posY, std::string content);
	void DrawUI(sf::RenderWindow &window);

	void SpawnEnemy();
	void ReDefineTextures();

	//Main menu text
	sf::Text mainMenuText;
	sf::Text highscoreText;
	sf::Text pressEnterToStart;
	sf::Text credits;

	//Ingame text
	sf::Text currentHighscore;
	sf::Text pointsModifier;
	sf::Font font;

	float playerCurrentY;
	int pointsMultiplier = 1;

	int enemyID = 0;
	int enemyLocation = -1;

	int mainMenuDisplay;
	int frameRate;

	Enemy SelectEnemyType();
};