#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Entity {
private:
  int randomizer;

public:
  Enemy();
  Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
        int tileSize, TileMap *map, int maxHealth);
  void initEnemy(std::string file, int x, int y, int w, int h, int dir,
                 int speed, int tileSize, TileMap *map, int maxHealth);
  void updateEnemy(unsigned long int er);
  void draw(sf::RenderWindow &window);
  void changeMoveDirection(int newDir);
};
