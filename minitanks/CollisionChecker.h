#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "TileMap.h"
#include "Widget.h"
#include <vector>


bool checkCollisionTiles(TileMap &map, Bullet bullet);
bool checkCollisionEnemies(Bullet bullet, std::vector<Enemy> &vecEnemies,
                            sf::Sound &hit, Widget &pl1, Widget &pl2);
bool checkCollisionPlayer(Bullet bullet, Player& player, sf::Sound& hit);
std::vector<Enemy> getEnemies();
void setEnemies(std::vector<Enemy> &newVector);


