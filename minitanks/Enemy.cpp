#include "Enemy.h"

Enemy::Enemy() {}
Enemy::Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
             int tileSize, TileMap *map, int maxHealth)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth) {}

void Enemy::initEnemy(std::string file, int x, int y, int w, int h, int dir,
                      int speed, int tileSize, TileMap *map, int maxHealth) {
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
}

void Enemy::updateEnemy() {
	if (this->frontBlocked) {
		if (dir >= 3)
			dir = 0;
		else
			dir++;
	}
  if (map->getEditMode()) {
    delete this;
  }
  if (dir == 3) {

    speed = 3;
    entitySprite.setRotation(270);
  }

  if (dir == 1) {

    speed = 3;
    entitySprite.setRotation(90);
    //	std::cout << x << "," << y << std::endl;
  }

  if (dir == 0) {

    speed = 3;
    entitySprite.setRotation(0);
    //	std::cout << x << "," << y << std::endl;
  }

  if (dir == 2) {

    speed = 3;
    entitySprite.setRotation(180);
    //	std::cout << x << "," << y << std::endl;
  }
  update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }

void Enemy::changeMoveDirection(int newDir) { dir = newDir; }
