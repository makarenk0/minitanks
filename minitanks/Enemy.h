#pragma once
#include "Entity.h"
#include "TileMap.h"
#include <cstdlib>
#include <ctime>

class Enemy : public Entity {
private:
  float enemySpeed;
  int direction;
  float frame=0;
public:
  Enemy();
  ~Enemy();
  Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
        int tileSize, TileMap *map, int maxHealth);
  void initEnemy(std::string file, int x, int y, int w, int h, int dir,
                 int speed, int tileSize, TileMap *map, int maxHealth);
  void draw(sf::RenderWindow &window);
  void updateEnemy(float time, int pl1X, int pl1Y);

};
