#pragma once
#include "Entity.h"
#include "TileMap.h"
class Player : public Entity, public sf::Drawable
{
public:
	Player(std::string file,  int x, int y, int w, int h, int dir, int speed, int tileSize, TileMap* map);
	void updatePlayer();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

