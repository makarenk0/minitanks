#pragma once
#include "Bullet.h"
#include "CollisionChecker.h"
#include "Endscreen.h"
#include "Enemy.h"
#include "MainMenu.h"
#include "Player.h"
#include "SFML/Window.hpp"
#include "TileMap.h"
#include "Widget.h"
#include "toolbox.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>
#define FPS 60
#define mapHeight 768
#define mapWidth 960
#define widgetWidth 192
#define FPS 60
#define cellWidth 48
#define playerSize 40

sf::Sound hit;
sf::Sound ost, shoot;
sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
	"Main window", sf::Style::Close | sf::Style::Titlebar);