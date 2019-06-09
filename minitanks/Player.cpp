#include "Player.h"

Player::Player() {}
Player::Player(std::string file, int x, int y, int w, int h, int dir, int speed,
               int tileSize, TileMap *map)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, 3) {}

void Player::initPlayer(std::string file, int x, int y, int w, int h, int dir,
                        int speed, int tileSize, TileMap *map, int maxHealth) {
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dir = 3;
		speed = 2;
		entitySprite.setRotation(270);
		//	std::cout << x << "," << y<<std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir = 1;
		speed = 2;
		entitySprite.setRotation(90);
		//	std::cout << x << "," << y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dir = 0;
		speed = 2;
		entitySprite.setRotation(0);
		//	std::cout << x << "," << y << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dir = 2;
		speed = 2;
		entitySprite.setRotation(180);
		//	std::cout << x << "," << y << std::endl;
	}
	update();
}
int Player::getAmmoCount() { return ammoCount; }

void Player::minusAmmo() { ammoCount--; }
