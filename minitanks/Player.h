#pragma once
#include "Entity.h"
#include "TileMap.h"
class Player : public Entity {
public:
  Player();
  Player(std::string file, int x, int y, int w, int h, int dir, int speed,
         int tileSize, TileMap *map, int maxHealth, bool playerOne);
  void initPlayer(std::string file, int x, int y, int w, int h, int dir,
                  int speed, int tileSize, TileMap *map, int maxHealth,
                  bool playerOne);
  void updatePlayer(sf::Clock &clock);
  int getAmmoCount();
  void minusAmmo();
  void setPosition(sf::Vector2f position);

private:
  int ammoCount = 2;
  bool playerOne;
};
