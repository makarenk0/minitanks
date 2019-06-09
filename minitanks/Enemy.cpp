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

  if (map->getEditMode()) {
    delete this;
  }

  update();
}

void Enemy::draw(sf::RenderWindow &window) { window.draw(entitySprite); }
