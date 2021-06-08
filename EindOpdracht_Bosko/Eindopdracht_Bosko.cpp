#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "GameManager.h"
#include "Enemy.h"
#include "BackGround.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Eindopdracht Kernmodule Bosko Ivkovic");
	window.setFramerateLimit(60);

	srand(time(NULL)); // Set Random seed

	//Create and initiate Player
	Player* player = new Player(325, 550, "PlayerCar.png");

	//Create and initiate GameManager
	GameManager* gm = new GameManager();

	//Create and initiate BackGround
	BackGround* bg = new BackGround(0, -700, "BackGround.jpg");

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

		bg->Update(window);

		if (gm->gameInProgress)
		{
			player->Update(window, event);

			gm->GameLoop(window, player->_sprite);
		}
		else
		{
			gm->StartGame(window, event);
			window.draw(player->_sprite);
		}

		window.display(); // Draw code ^^
	}

	delete gm;
	delete player;
	delete bg;

	return 0;
}