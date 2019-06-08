#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
class Entity
{
public:
	Entity(int x, int y, int w, int h, int dir, std::string file, int speed, int tileSize, TileMap* map);
	int x, y, speed, w, h, dx, dy, dir;
	int tileSize;
	void update();
	void setSpeed(int speed);
protected:
	const int rangeBetweenTiles = 2;
	int widgetWidth;
	int health;
	sf::Texture entityTexture;
	sf::Sprite entitySprite;
	TileMap* map;
	void interactMap();

};

