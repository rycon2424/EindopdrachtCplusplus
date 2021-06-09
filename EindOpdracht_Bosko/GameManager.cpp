#include "GameManager.h"

//PUBLIC vvv

GameManager::GameManager()
{
	sf::Font uiFont;
	uiFont.loadFromFile("Freshman.ttf");

	font = uiFont;

	healthTexture.loadFromFile("HealthIcon.png");

	//First Screen
	sf::Color color(0, 0, 0);
	InitialiseText(mainMenuText, 40, color, 225, 50, "Racing Game");
	InitialiseText(credits, 20, color, 235, 100, "Made by: Bosko Ivkovic");
	InitialiseText(pressEnterToStart, 24, color, 220, 350, "Press Enter To start");

	//Ingame Screen
	InitialiseText(currentScore, 24, color, 5, 0, "Score: " + std::to_string(highscore));
	InitialiseText(pointsModifier, 24, color, 570, 0, "Points x" + std::to_string(playerCurrentY));

	//End Screen
	color = sf::Color(255, 255, 255);
	InitialiseText(GameOver, 40, color, 225, 50, "Game Over");
	InitialiseText(yourScore, 24, color, 260, 100, "Score: " + std::to_string(highscore));
	InitialiseText(exitGame, 24, color, 220, 350, "Press Enter to exit");

}

GameManager::~GameManager() {}

//The Update loop
void GameManager::GameLoop(sf::RenderWindow &window, sf::Sprite &playerRef, sf::Event event)
{
	switch (currentGameState)
	{
	case GameState::startScreen:
		StartGame(window, event);
		break;
	case GameState::playing:
		Playing(window, playerRef);
		break;
	case GameState::endScreen:
		EndScreen(window);
		break;
	default:
		break;
	}
}

void GameManager::PlayerLoseHealth()
{
	playerHealth -= 1;
	if (playerHealth == 0)
	{
		yourScore.setString("Score: " + std::to_string(highscore));
		currentGameState = GameState::endScreen;
	}
}

//PUBLIC ^^^^

//PRIVATE vvvv

void GameManager::StartGame(sf::RenderWindow &window, sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		currentGameState = GameState::playing;
	}
	window.draw(mainMenuText);
	window.draw(credits);
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

void GameManager::Playing(sf::RenderWindow &window, sf::Sprite &playerRef)
{
	playerCurrentY = playerRef.getPosition().y;
	frameRate++;
	if (frameRate > enemySpawnInterval)
	{
		SpawnEnemy();
		frameRate = 0;
	}
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
	sf::RectangleShape rec(sf::Vector2f(700, 30));
	rec.setFillColor(sf::Color(255, 255, 0));
	window.draw(rec);
	DrawUI(window);
}

void GameManager::EndScreen(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		exit(0);
	}

	sf::RectangleShape rec(sf::Vector2f(700, 700));
	rec.setFillColor(sf::Color(0, 0, 0));

	window.draw(rec);

	window.draw(GameOver);
	window.draw(yourScore);
	window.draw(exitGame);
}

void GameManager::SpawnEnemy()
{
	if (enemySpawnInterval > 31)
	{
		enemySpawnInterval--;
	}

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
			highscore += 50 * pointsMultiplier;
			currentScore.setString("Score: " + std::to_string(highscore));
		}
	}
}

Enemy GameManager::SelectEnemyType()
{
	int randomInt = rand() % 101 + 1; // Chance from 1 to 100
	int fiftyfifty = rand() % 3 + 1;
	if (randomInt < 70) // 70% chance to spawn driving vehicle
	{
		std::string imagePath = "";
		int spawnLocation = 0;
		if (fiftyfifty == 1)
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
		if (fiftyfifty == 1)
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
		int spawnPos;
		if (fiftyfifty == 1)
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
		int spawnPos;
		if (fiftyfifty == 1)
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
	pointsMultiplier = int((playerCurrentY - 600) * -1 / 100 + 1);

	pointsModifier.setString("Points x" + std::to_string(pointsMultiplier));

	for (int i = 0; i < playerHealth; i++)
	{
		sf::Sprite healthIcon;
		healthIcon.scale(0.15f, 0.15f);
		healthIcon.setTexture(healthTexture);
		healthIcon.setPosition(60 * i, 600);

		window.draw(healthIcon);
	}
	window.draw(currentScore);
	window.draw(pointsModifier);
}

void GameManager::InitialiseText(sf::Text &text, int fontSize, sf::Color color, float posX, float posY, std::string content)
{
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(color);
	text.setString(content);
	text.setPosition(posX, posY);
}

//PRIVATE ^^^^