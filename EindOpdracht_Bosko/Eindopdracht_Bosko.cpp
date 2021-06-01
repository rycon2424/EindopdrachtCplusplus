#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "GameManager.h"
#include "Enemy.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Eindopdracht Kernmodule Bosko Ivkovic");

	//Create and initiate Player
	Player* player = new Player(350, 550, "PlayerCar.png");

	//Create and initiate GameManager
	GameManager* gm = new GameManager();
	gm->SpawnEnemy();

	int FrameRate = 60;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear(); // Draw code vv

		player->Update(window, event);

		gm->GameLoop(window, player->_sprite);

		FrameRate++;
		if (FrameRate > 6000) // Tries to get called every 60 frames + spawn then an enemy
		{
			gm->SpawnEnemy();
			//std::cout << "Frame" << std::endl;
			FrameRate = 0;
		}

		window.display(); // Draw code ^^
	}

	delete player;
	delete gm;

	return 0;
}