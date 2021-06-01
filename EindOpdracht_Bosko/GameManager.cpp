#include "GameManager.h"

GameManager::GameManager()
{
	sf::Font uiFont;
	uiFont.loadFromFile("Freshman.ttf");

	font = uiFont;
}

void GameManager::SpawnEnemy()
{
	Enemy enemy(350, 0, "BikerMan.png");
	enemy.SetGameManager(this);

	enemyID++;
	enemy.ID = enemyID;
	
	//std::cout << "Created Enemy " << enemyID << std::endl;

	activeEnemies.push_back(enemy);
	ReDefineTextures();
}

void GameManager::DestroyEnemy(Enemy &enemyToRemove)
{
	for (int i = 0; i < activeEnemies.size(); i++)
	{
		if (activeEnemies.at(i).ID == enemyToRemove.ID)
		{
			std::cout << "Needs to Remove enemy with ID: " << activeEnemies.at(i).ID << " || position in vector = " << i << std::endl;
			enemyLocation = i;
		}
	}
}

void GameManager::GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef)
{
	DrawUI(window);
	if (activeEnemies.size() > 0)
	{
		for (Enemy& e : activeEnemies) // & so that i am modifiying the original and NOT the copy
		{
			e.Update(window, playerRef);
		}
	}
	if (enemyLocation != -1) // Check if there is an enemy to be deleted after the foreach-loop for no nullreferences
	{
		activeEnemies.erase(activeEnemies.begin() + enemyLocation);
		enemyLocation = -1;
		ReDefineTextures();
	}
}

//Re-Reference texture each time because of whiteBox issue
void GameManager::ReDefineTextures()
{
	for (int i = 0; i < activeEnemies.size(); i++)
	{
		activeEnemies[i]._sprite.setTexture(activeEnemies[i]._texture);
	}
}

void GameManager::DrawUI(sf::RenderWindow &window)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(500, 0);
	text.setString("Test 123456789");
	window.draw(text);
}