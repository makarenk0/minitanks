#pragma once
#include "Entity.h"
#include "TileMap.h"
class Player : public Entity {
public:
  Player();
  Player(std::string file, int x, int y, int w, int h, int dir, int speed,
         int tileSize, TileMap *map);
  void initPlayer(std::string file, int x, int y, int w, int h, int dir,
                  int speed, int tileSize, TileMap *map, int maxHealth);
  void updatePlayer(sf::Clock &clock);
  int getAmmoCount();
  void minusAmmo();

private:
  int ammoCount = 2;
};
