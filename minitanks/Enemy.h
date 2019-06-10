#pragma once
#include "Entity.h"
#include "TileMap.h"
class Enemy : public Entity {
private:
	
public:
  Enemy();
  Enemy(std::string file, int x, int y, int w, int h, int dir, int speed,
        int tileSize, TileMap *map, int maxHealth);
  void initEnemy(std::string file, int x, int y, int w, int h, int dir,
                 int speed, int tileSize, TileMap *map, int maxHealth);
  void updateEnemy(sf::Clock& clock);
  void draw(sf::RenderWindow &window);
  void changeMoveDirection(int newDir);
};
