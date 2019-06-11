#include "Player.h"

Player::Player() {}
Player::Player(std::string file, int x, int y, int w, int h, int dir, int speed,
	int tileSize, TileMap* map, int maxHealth, bool playerOne)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth) {}

void Player::initPlayer(std::string file, int x, int y, int w, int h, int dir,
                        int speed, int tileSize, TileMap *map, int maxHealth, bool playerOne) {
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
  this->playerOne = playerOne;
}

void Player::updatePlayer(sf::Clock& clock) {
	sf::Time elapsed1 = clock.getElapsedTime();
	if (ammoCount < 2 && elapsed1.asMilliseconds() > 1000) {
		ammoCount++;
		clock.restart();
	}


	if (map->getEditMode()) {
		delete this;
	}
	if (playerOne) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			dir = 3;
			speed = 3;
			entitySprite.setRotation(270);
			//	std::cout << x << "," << y<<std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			dir = 1;
			speed = 3;
			entitySprite.setRotation(90);
			//	std::cout << x << "," << y << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			dir = 0;
			speed = 3;
			entitySprite.setRotation(0);
			//	std::cout << x << "," << y << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			dir = 2;
			speed = 3;
			entitySprite.setRotation(180);
			//	std::cout << x << "," << y << std::endl;
		}
	}
	else if (!playerOne){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			dir = 3;
			speed = 3;
			entitySprite.setRotation(270);
			//	std::cout << x << "," << y<<std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			dir = 1;
			speed = 3;
			entitySprite.setRotation(90);
			//	std::cout << x << "," << y << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			dir = 0;
			speed = 3;
			entitySprite.setRotation(0);
			//	std::cout << x << "," << y << std::endl;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			dir = 2;
			speed = 3;
			entitySprite.setRotation(180);
			//	std::cout << x << "," << y << std::endl;
		}
		}
	update();
}
int Player::getAmmoCount() { return ammoCount; }

void Player::minusAmmo() { ammoCount--; }

void Player::setPosition(sf::Vector2f position) {
	entitySprite.setPosition(position + sf::Vector2f(widgetWidth,0));
	x = position.x + widgetWidth;
	y = position.y;
}
