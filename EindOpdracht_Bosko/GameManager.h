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
	void GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef, sf::Event event);
	void DestroyEnemy(Enemy &enemyToRemove);
	void PlayerLoseHealth();

	int highscore;
	int enemySpawnInterval = 80;

private:
	enum GameState { startScreen, playing, endScreen };
	GameState currentGameState;

	void StartGame(sf::RenderWindow &window, sf::Event event);
	void Playing(sf::RenderWindow &window, sf::Sprite &playerRef);
	void EndScreen(sf::RenderWindow &window);

	void InitialiseText(sf::Text &text, int fontSize, sf::Color color, float posX, float posY, std::string content);
	void DrawUI(sf::RenderWindow &window);

	void SpawnEnemy();
	void ReDefineTextures();

	int playerHealth = 3;

	//Main menu text
	sf::Text mainMenuText;
	sf::Text pressEnterToStart;
	sf::Text credits;

	//Ingame text
	sf::Text currentScore;
	sf::Text pointsModifier;
	sf::Font font;

	//EndScreen text
	sf::Text GameOver;
	sf::Text yourScore;
	sf::Text exitGame;

	sf::Texture healthTexture;

	float playerCurrentY;
	int pointsMultiplier = 1;

	int enemyID = 0;
	int enemyLocation = -1;

	int mainMenuDisplay;
	int frameRate;

	Enemy SelectEnemyType();
};