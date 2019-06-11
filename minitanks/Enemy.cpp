#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

Enemy::Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
             int tileSize, TileMap *map, int maxHealth)
    : Entity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth) {}

void Enemy::initEnemy(std::string file, int x, int y, int w, int h, int dir,
                      int speed, int tileSize, TileMap *map, int maxHealth) {
  this->enemySpeed = speed;
  this->direction = dir;
  initEntity(x, y, w, h, dir, file, speed, tileSize, map, maxHealth);
  srand(time(0));
}

void Enemy::updateEnemy(unsigned long int BehaviourCounter) {
  if (BehaviourCounter % 50 == 0) {
    if (rand() % 2) {
      if (frontBlocked) {
        randomizer = rand() % 3;
        if (randomizer == 0) {
			direction++;
        } else if (randomizer == 1) {
			direction--;
        } else if (randomizer == 2) {
			direction += 2;
        }
		direction = direction % 4;
      }
    }
  }

  if (this->direction == 3) {

    speed = enemySpeed;
    entitySprite.setRotation(270);
  }

  if (this->direction == 1) {

    speed = enemySpeed;
    entitySprite.setRotation(90);
  }

  if (this->direction == 0) {

    speed = enemySpeed;
    entitySprite.setRotation(0);
  }

  if (this->direction == 2) {

    speed = enemySpeed;
    entitySprite.setRotation(180);
  }
  this->update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }

void Enemy::changeMoveDirection(int newDir) { dir = newDir; }
