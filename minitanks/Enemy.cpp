#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

Enemy::Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
             int tileSize, TileMap *map, int maxHealth)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth) {}

void Enemy::initEnemy(std::string file, int x, int y, int w, int h, int dir,
                      int speed, int tileSize, TileMap *map, int maxHealth) {
  this->enemySpeed = speed;
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
  srand(time(0));
}

void Enemy::updateEnemy(unsigned long int BehaviourCounter) {
	if (BehaviourCounter % 50 == 0 && frontBlocked && rand() % 2) {

		int getRand = rand() % 3;
		if (getRand == 0) {
			dir++;
		}
		else if (getRand == 1) {
			dir--;
		}
		else if (getRand == 2) {
			dir += 2;
		}
		dir = dir % 4;
	}


if (this->dir == 3) {
  entitySprite.setRotation(270);
}

if (this->dir == 1) {
  entitySprite.setRotation(90);
}

if (this->dir == 0) {

  entitySprite.setRotation(0);
}

if (this->dir == 2) {
  entitySprite.setRotation(180);
}

speed = enemySpeed;
this->update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }
