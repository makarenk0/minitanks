#include "Player.h"



Player::Player(std::string file, int x, int y, int w, int h,int dir, int speed, int tileSize, TileMap* map) : Entity(x, y, w, h, dir, file, speed, tileSize, map)
{
}

void Player::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dir = 1;
		speed = 2;
		entitySprite.setRotation(180);
	//	std::cout << x << "," << y<<std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir = 0;
		speed = 2;
		entitySprite.setRotation(0);
	//	std::cout << x << "," << y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dir = 3;
		speed = 2;
		entitySprite.setRotation(270);
	//	std::cout << x << "," << y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dir = 2;
		speed = 2;
		entitySprite.setRotation(90);
	//	std::cout << x << "," << y << std::endl;
	}
	update();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(entitySprite);
}
