#include "Entity.h"

Entity::Entity(int x, int y, int w, int h, int dir, std::string file, int speed,
               int tileSize, TileMap *map) {

  widgetWidth = map->widgetWidth;
  this->x = x;
  this->y = y;
  this->w = w * 0.8f;
  this->h = h * 0.8f;
  this->speed = speed;
  this->tileSize = tileSize;
  this->dir = dir;
  this->map = map;

  entityTexture.loadFromFile("assets/" + file);
  entitySprite.setTexture(entityTexture);
  entitySprite.setOrigin((w / 2), (h / 2));
  entitySprite.setPosition(x + widgetWidth, y);
  entitySprite.scale(0.8f, 0.8f);
}

void Entity::update() {

  switch (dir) {
  case 0:
    dx = 0;
    dy = -speed;
    break;
  case 1:
    dx = speed;
    dy = 0;
    break;
  case 2:
    dx = 0;
    dy = speed;
    break;
  case 3:
    dx = -speed;
    dy = 0;
    break;
  }
  entitySprite.move(dx, dy);
  x += dx;
  y += dy;
  speed = 0;
  interactMap();
}

void Entity::setSpeed(int speed) { this->speed = speed; }

void Entity::interactMap() {
  for (int i = (y - (h / 2) + rangeBetweenTiles) / tileSize;
       i <= ((y + (h / 2) - rangeBetweenTiles) / tileSize); i++) {
    for (int j = (x - (w / 2) + rangeBetweenTiles) / tileSize;
         j <= ((x + (w / 2) - rangeBetweenTiles) / tileSize); j++) {
      if (map->checkCollisionOfPoint(j * tileSize, i * tileSize)) {
        if (dy > 0) {
          y = i * tileSize - h / 2 - 1 + rangeBetweenTiles;
          entitySprite.setPosition(widgetWidth + x, y);
        }
        if (dy < 0) {
          y = (i * tileSize) + tileSize + h / 2 - rangeBetweenTiles;
          entitySprite.setPosition(widgetWidth + x, y);
        }
        if (dx > 0) {
          x = j * tileSize - w / 2 - 1 + rangeBetweenTiles;
          entitySprite.setPosition(widgetWidth + x, y);
        }
        if (dx < 0) {
          x = j * tileSize + tileSize + w / 2 - rangeBetweenTiles;
          entitySprite.setPosition(widgetWidth + x, y);
        }
      }
    }
  }
}

sf::Vector2f Entity::getFacePosition() {
  switch (dir) {
  case 0: {
    return sf::Vector2f(entitySprite.getPosition().x -7
                            ,
                        entitySprite.getPosition().y-40);
    break;
  }
  case 1: {
    return sf::Vector2f(entitySprite.getPosition().x +
                            entitySprite.getGlobalBounds().width+8,
                        entitySprite.getPosition().y -7);
    break;
  }
  case 2: {
    return sf::Vector2f(
        entitySprite.getPosition().x + 7,
        entitySprite.getPosition().y + entitySprite.getGlobalBounds().height+8);
    break;
  }
  case 3: {
    return sf::Vector2f(entitySprite.getPosition().x-40,
                        entitySprite.getPosition().y +
                            7);
    break;
  }
  }
}

int Entity::getDirection() { return dir; }
