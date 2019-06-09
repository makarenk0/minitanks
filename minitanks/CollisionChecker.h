#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "TileMap.h"
#include <vector>

void checkCollisionTiles(TileMap &map, std::vector<Bullet> &vecBullets);
std::vector<Entity> checkCollisionEntities(std::vector<Bullet> &vecBullets,
                                           std::vector<Entity> &vecEnt,
                                           sf::Sound &hit);
std::vector<Bullet> getVector();
