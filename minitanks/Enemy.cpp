#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {

}

Enemy::Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
             int tileSize, TileMap *map, int maxHealth)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth) {}

void Enemy::initEnemy(std::string file, int x, int y, int w, int h, int dir,
                      int speed, int tileSize, TileMap *map, int maxHealth) {
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
  srand(time(0));
}

void Enemy::updateEnemy(unsigned long int BehaviourCounter) {
  if (BehaviourCounter % 50 == 0) {
	  if (rand() % 2) {
		  if (frontBlocked) {
			  randomizer = rand() % 3;
			  if (randomizer == 0) {
				  dir++;
			  }
			  else if (randomizer == 1) {
				  dir--;
			  }
			  else if (randomizer == 2) {
				  dir += 2;
			  }
			  dir = dir % 4;
		  }
	  }
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
  this->update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }

void Enemy::changeMoveDirection(int newDir) { dir = newDir; }

