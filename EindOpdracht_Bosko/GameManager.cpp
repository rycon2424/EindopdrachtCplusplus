#include "GameManager.h"

GameManager::GameManager()
{
	sf::Font uiFont;
	uiFont.loadFromFile("Freshman.ttf");

	sf::Color color(0, 0, 0);

	font = uiFont;

	InitialiseText(mainMenuText, 40, color, 225, 50, "Racing Game");
	InitialiseText(credits, 20, color, 235, 100, "Made by: Bosko Ivkovic");
	InitialiseText(pressEnterToStart, 24, color, 220, 350, "Press Enter To start");
	InitialiseText(highScoreText, 24, color, 260, 500, "Highscore: " + std::to_string(1000));
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
			//std::cout << "Needs to Remove enemy with ID: " << activeEnemies.at(i).ID << " || position in vector = " << i << std::endl;
			enemyLocation = i;
		}
	}
}

Enemy GameManager::SelectEnemyType()
{
	int randomInt = rand() % 101 + 1; // Chance from 1 to 100
	if (randomInt < 70) // 70% chance to spawn driving vehicle
	{
		int carOrBike = rand() % 3 + 1;
		std::string imagePath = "";
		int spawnLocation = 0;
		if (carOrBike == 1)
		{
			imagePath = "BikerMan.png";
			spawnLocation = rand() % 500 + 150;
		}
		else
		{
			imagePath = "Car.png";
			int lanes = rand() % 5 + 0;
			spawnLocation = 125 + (100 * lanes); // Lane spawn Locations
		}

		Enemy Vehicle(spawnLocation, -200, imagePath);

		sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

		float randomSpeed = rand() % 7 + 3;
		randomSpeed = randomSpeed;
		if (carOrBike == 1)
		{
			if (spawnLocation > 300) // Choose if vehicle starts going in the left or right direction
			{
				Vehicle.movingLeft = true;
			}
			else
			{
				Vehicle.movingLeft = false;
			}
			Vehicle.SetSpeed(2.5f, 2.5f);
			Vehicle.SetScale(0.03f, 0.03f);
		}
		else
		{
			Vehicle.SetSpeed(0.00f, randomSpeed);
			Vehicle.SetScale(0.8f, 0.8f);
		}
		Vehicle._sprite.setColor(color);
		return Vehicle;
	}
	else if (randomInt < 80) // 10% chance to spawn pedestrian
	{
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
		Pedestrian.SetSpeed(0, 15);
		Pedestrian.SetScale(0.4f, 0.5f);
		return Pedestrian;
	}
	else if (randomInt < 100) // 20% chance to spawn Parked Car
	{
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
		EmergencyCar.SetSpeed(0, 15);
		EmergencyCar.SetScale(0.8f, 0.8f);
		EmergencyCar._sprite.setColor(color);
		return EmergencyCar;
	}
}

void GameManager::GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef)
{
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
	DrawUI(window);
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

}

void GameManager::StartGame(sf::RenderWindow &window, sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		gameInProgress = true;
	}
	window.draw(mainMenuText);
	window.draw(credits);
	window.draw(highScoreText);
	mainMenuDisplay++;
	if (mainMenuDisplay > 30)
	{
		window.draw(pressEnterToStart);
	}
	if (mainMenuDisplay > 60)
	{
		mainMenuDisplay = 0;
	}
}

void GameManager::InitialiseText(sf::Text &text, int fontSize, sf::Color color, float posX, float posY, std::string content)
{
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(color);
	text.setString(content);
	text.setPosition(posX, posY);
}