#pragma once
#include "Entity.h"
#include "TileMap.h"
class Player : public Entity
{
public:
	Player();
	Player(std::string file,  int x, int y, int w, int h, int dir, int speed, int tileSize, TileMap* map);
	void initPlayer(std::string file, int x, int y, int w, int h, int dir, int speed, int tileSize, TileMap* map);
	void updatePlayer();
	void draw(sf::RenderWindow& window);

private:
	
};

