#include "Entity.h"



Entity::Entity(int x, int y, int w, int h,int dir, std::string file, int speed, int tileSize, TileMap* map)
{

	widgetWidth = map->widgetWidth;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
	this->tileSize = tileSize;
	this->dir = dir;
	this->map = map;

	entityTexture.loadFromFile("assets/" + file);
	entitySprite.setTexture(entityTexture);
	entitySprite.setOrigin((w/2), (h/2));
	entitySprite.setPosition(x+widgetWidth, y);
}

void Entity::update()
{
	
	switch (dir)
	{
	case 0: dx = speed; dy = 0; break;
	case 1: dx = -speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	}
	entitySprite.move(dx, dy);
	x += dx;
	y += dy;
	speed = 0;
	interactMap();
}

void Entity::setSpeed(int speed)
{
	this->speed = speed;
}

void Entity::interactMap()
{
	for (int i = (y-(h/2)+ rangeBetweenTiles) / tileSize; i <= ((y+(h/2)- rangeBetweenTiles)/tileSize); i++) {
		for (int j = (x-(w/2)+ rangeBetweenTiles) / tileSize; j <= ((x+(w/2)- rangeBetweenTiles) / tileSize); j++) {
			if (map->checkCollisionOfPoint(j * tileSize, i * tileSize)) {
				if (dy > 0) {
					y = i * tileSize - h/2-1 + rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth+x, y);
				}
				if (dy < 0) {
					y = (i * tileSize) + tileSize+h/2 - rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth+x, y);
				}
				if (dx > 0) {
					x = j * tileSize - w/2-1 + rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth+x, y);
				}
				if (dx < 0) {
					x = j * tileSize + tileSize+w/2 - rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth+x, y);
				}
			}
		}
	}
}
