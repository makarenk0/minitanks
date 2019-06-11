#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "TileMap.h"
#include "Widget.h"
#include <vector>

void checkCollisionTiles(TileMap &map, std::vector<Bullet> &vecBullets);
std::vector<Enemy> checkCollisionEntities(std::vector<Bullet> &vecBullets,
                                          std::vector<Enemy> &vecEnt,
                                          sf::Sound &hit, Widget &widget);
void checkCollisionPlayers2(std::vector<Bullet> &vecBullets, Player &pl1,
                            Player &pl2, sf::Sound &hit);
void checkCollisionPlayers1(std::vector<Bullet> &vecBullets, Player &pl1,
                            sf::Sound &hit);
std::vector<Bullet> getVector();
