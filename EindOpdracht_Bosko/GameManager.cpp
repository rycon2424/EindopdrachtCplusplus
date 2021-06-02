#include "GameManager.h"

GameManager::GameManager()
{
	sf::Font uiFont;
	uiFont.loadFromFile("Freshman.ttf");

	font = uiFont;
}

void GameManager::SpawnEnemy()
{
	Enemy enemy = SelectEnemyType();
	enemy.SetGameManager(this);

	enemyID++;
	enemy.ID = enemyID;
	
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

Enemy GameManager::SelectEnemyType()
{
	srand(time(NULL));
	int randomInt = rand() % 100 + 1;
	int spawnLocation = rand() % 500 + 150;
	if (randomInt < 70) // 50% chance to spawn driving vehicle
	{
		int carOrBike = rand() % 3 + 1;
		std::string imagePath = "";
		if (carOrBike == 1)
		{
			imagePath = "BikerMan.png";
			//std::cout << "Spawn Biker" << std::endl;
		}
		else
		{
			imagePath = "Car.png";
			//std::cout << "Spawn Car" << std::endl;
		}
		Enemy Vehicle(spawnLocation, -200, imagePath);
		Vehicle.SetSpeed(0.05f, 0.05f);
		sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		if (carOrBike == 1)
		{
			Vehicle.SetScale(0.03f, 0.03f);
		}
		else
		{
			Vehicle.SetScale(0.8f, 0.8f);
		}
		Vehicle._sprite.setColor(color);
		return Vehicle;
	}
	else if (randomInt < 80) // 10% chance to spawn pedestrian
	{
		std::cout << "Spawn Pedestrian" << std::endl;
		int leftOrRight = rand() % 3 + 1;
		int spawnPos;
		if (leftOrRight == 1)
		{
			spawnPos = 10;
		}
		else
		{
			spawnPos = 660;
		}
		Enemy Pedestrian(spawnPos, -200, "Pedestrian.png");
		Pedestrian.SetSpeed(0, 0.2f);
		Pedestrian.SetScale(0.4f, 0.5f);
		return Pedestrian;
	}
	else if (randomInt < 100) // 20% chance to spawn Parked Car
	{
		std::cout << "Spawn Parked Car" << std::endl;
		int leftOrRight = rand() % 3 + 1;
		int spawnPos;
		if (leftOrRight == 1)
		{
			spawnPos = 50;
		}
		else
		{
			spawnPos = 600;
		}
		sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		Enemy EmergencyCar(spawnPos, -200, "Car.png");
		EmergencyCar.SetSpeed(0, 0.25f);
		EmergencyCar.SetScale(0.8f, 0.8f);
		EmergencyCar._sprite.setColor(color);
		return EmergencyCar;
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