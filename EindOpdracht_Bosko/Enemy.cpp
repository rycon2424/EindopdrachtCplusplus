#include "Enemy.h"
#include "GameManager.h"

void Enemy::Update(sf::RenderWindow &window, sf::Sprite &playerRef)
{
	SpriteHandler::Update(window);
	Movement();
	CollisionDetection(playerRef);
}

void Enemy::SetGameManager(GameManager* gameManager)
{
	gm = gameManager;
}

void Enemy::CollisionDetection(sf::Sprite &playerRef)
{
	if (playerRef.getGlobalBounds().intersects(_sprite.getGlobalBounds()))
	{
		gm->DestroyEnemy(*this);
		//std::cout << "Collision with enemy ID " << ID << std::endl;
	}
}

void Enemy::Movement()
{
	const sf::Vector2f& currentPosition = _sprite.getPosition();
	//std::cout << currentPosition << std::endl;
	if (movingLeft)
	{
		if (currentPosition.x < 75)
		{
			movingLeft = !movingLeft;
			_sprite.setScale((float)0.3, (float)0.3);
			_sprite.move(-100, 0);
		}
		_sprite.move(-0.05f, 0);
	}
	else
	{
		if (currentPosition.x > 625)
		{
			movingLeft = !movingLeft;
			_sprite.setScale(-(float)0.3, (float)0.3);
			_sprite.move(100, 0);
		}
		_sprite.move(0.05f, 0);
	}
	_sprite.move(0, 0.025f);
}