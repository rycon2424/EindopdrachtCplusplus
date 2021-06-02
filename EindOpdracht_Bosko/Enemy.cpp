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
	}
}

void Enemy::SetSpeed(float xSpeed, float ySpeed)
{
	speedX = xSpeed;
	speedY = ySpeed;
}

void Enemy::Movement()
{
	const sf::Vector2f& currentPosition = _sprite.getPosition();
	//std::cout << currentPosition.x << " =X Y= " << currentPosition.y << std::endl;
	if (movingLeft)
	{
		if (currentPosition.x < 125)
		{
			movingLeft = !movingLeft;
		}
		_sprite.move(-speedX, 0);
	}
	else
	{
		if (currentPosition.x > 600)
		{
			movingLeft = !movingLeft;
		}
		_sprite.move(speedX, 0);
	}
	_sprite.move(0, speedY);
	if (currentPosition.y > 700)
	{
		gm->DestroyEnemy(*this);
	}
}