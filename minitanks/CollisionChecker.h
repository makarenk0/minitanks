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
//void checkCollisionPlayers2(std::vector<Bullet> &vecBullets, Player &pl1,
//                            Player &pl2, sf::Sound &hit);
bool checkCollisionPlayers1(Bullet bullet, Player& pl1, sf::Sound& hit);
std::vector<Enemy> getEnemies();
void setEnemies(std::vector<Enemy> &newVector);
