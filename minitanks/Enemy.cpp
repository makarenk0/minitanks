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


void Enemy::updateEnemy(float time, int pl1X, int pl1Y) {
   frame += 0.001 * time;
   if (int(frame) == 4) {
	   frame = 0;
   }
  if (int(frame) > 1) {
    if (rand() % 2) {
	 
      if (frontBlocked) {
        randomizer = rand() % 3;
        if (randomizer == 0) {
			direction++;
        } else if (randomizer == 1) {
			direction+=3;
        } else if (randomizer == 2) {
			direction += 2;
        }
		direction = direction % 4;
      }	  
    }
  }
  if ((x / tileSize) == int(pl1X / tileSize) || int(y / tileSize) == int(pl1Y / tileSize)) { //focus on player when enemies see player on the line
	
	  
	  if (int(x / tileSize) > int(pl1X / tileSize)) {
		  if (!map->checkCollisionOfPoint(x-tileSize, y, false)) {
			  direction = 3;
		  }
		  
	  }
	  else if (int(x / tileSize) < int(pl1X / tileSize)) {
		  if (!map->checkCollisionOfPoint(x + tileSize, y, false)) {
			  direction = 1;
		  }
		  
	  }
	  else if (int(y / tileSize) < int(pl1Y / tileSize)) {
		  if (!map->checkCollisionOfPoint(x, y+tileSize, false)) {
			  direction = 2;
		  }
		  
	  }
	  else if (int(y / tileSize) > int(pl1Y / tileSize)) {
		  if (!map->checkCollisionOfPoint(x, y-tileSize, false)) {
			  direction = 0;
		  }
		  
	  }
  }
  else if (frame > 3&& frame < 3.1) {  // random rotate of enemies sometimes
  if (rand() % 5==0) {
	  randomizer = rand() % 3;
	  if (randomizer == 0) {
		  direction++;
	  }
	  else if (randomizer == 1) {
		  direction += 3;
	  }
	  else if (randomizer == 2) {
		  direction += 2;
	  }
	  direction = direction % 4;
  }
  }

  
  
  
  
  if (this->direction == 3) {
	 
    speed = 2;
    entitySprite.setRotation(270);
	dir = 3;
  }

  if (this->direction == 1) {

    speed = 2;
    entitySprite.setRotation(90);
	dir = 1;
  }

  if (this->direction == 0) {
	
    speed = 2;
    entitySprite.setRotation(0);
	dir = 0;
  }

if (this->direction == 2) {
	speed = 2;
	entitySprite.setRotation(180);
	dir = 2;
}
speed = enemySpeed;
this->update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }
