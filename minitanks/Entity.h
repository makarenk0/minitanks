#pragma once
#include "TileMap.h"
#include <SFML/Graphics.hpp>
class Entity {
public:
  Entity();
  ~Entity();
  Entity(int x, int y, int w, int h, int dir, std::string file, int speed,
         int tileSize, TileMap *map, int maxHealth);
  int x, y, speed, w, h, dx, dy, dir;
  int tileSize;
  void update();
  void setSpeed(int speed);
  sf::Vector2f getFacePosition();
  int getDirection();
  void initEntity(int x, int y, int w, int h, int dir, std::string file,
                  int speed, int tileSize, TileMap *map, int maxHealth);
  sf::FloatRect getGlobalBounds();
  void draw(sf::RenderWindow &window);
  int getCurrentHealth();
  void setCurrentHealth(int newHealth);

protected:
  int rangeBetweenTiles = 2;
  int widgetWidth;
  int currentHealth;
  sf::Texture entityTexture;
  sf::Sprite entitySprite;
  TileMap *map;
  void interactMap();
};
