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

// render mode, 0 for mainMenu, 1 for editor 2 for game with 1 P,3 for 2 P, 4
// for end screen
int renderMode = 0;
const float bulletSpeed = 5.f;
long unsigned int BehaviourCounter = 0;

int difficulty = 1;
const int playerMaxHealth = 3;
int enemyMaxHealth = 2;
const float enemySpeed = 2.f;
bool won;
int frameRandom;
float mainTime;


std::vector<Bullet> vecBullets;
std::vector<Bullet> vecBulletBuffer;
std::vector<Enemy> vecEnemies;

Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth, mapHeight,
                false);
MainMenu menu(sf::Vector2f(widgetWidth, 0), sf::Vector2i(mapWidth, mapHeight), 2);
MainMenu subMenu(sf::Vector2f(widgetWidth, 0), sf::Vector2i(mapWidth, mapHeight),1, true);

sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                         "Main window", sf::Style::Close | sf::Style::Titlebar);
Endscreen win(true, mapHeight, mapWidth);
Endscreen lose(false, mapHeight, mapWidth);
TileMap map;
Player pl1;
Player pl2;

sf::SoundBuffer buffer1, buffer2;
sf::Sound ost, shoot;
sf::SoundBuffer hitBuffer;
sf::Sound hit;
sf::Texture bulletTex, enemyTex;

void initSound();
void pause();
void initEnemies();
int main() {
  srand(time(0));
  initSound();
  sf::Clock clock1, clock2, clock3, clockMain;
  mWindow.setFramerateLimit(FPS);

  if (!bulletTex.loadFromFile("assets\\bullet.png"))
    std::cout << "error loading bullet" << std::endl;
  if (!enemyTex.loadFromFile("assets\\Enemy.png"))
    std::cout << "error loading bullet" << std::endl;
  ost.play();
  while (mWindow.isOpen()) {
    if (renderMode == 0) {
      sf::Event event;
      while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
          mWindow.close();
          mWindow.~RenderWindow();
          return 0;
        }
        case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Equal)
				ost.setVolume(ost.getVolume() + 10.f);
			else if (event.key.code == sf::Keyboard::Hyphen)
				ost.setVolume(ost.getVolume() - 10.f);
			else if (event.key.code == sf::Keyboard::Up)
				menu.previousOption();
			else if (event.key.code == sf::Keyboard::Down)
				menu.nextOption();
			else if (event.key.code == sf::Keyboard::M) {
					 ost.pause();
			}
          else if (event.key.code == sf::Keyboard::Return) {
            if (menu.getCurrentOption() == 0) {
              vecBullets.clear();
              if (!map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                               widgetWidth, false, 1))
                break;
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, playerMaxHealth,
                             true);
              initEnemies();
              setEnemies(vecEnemies);
              renderMode = 2;
              ost.stop();

            } else if (menu.getCurrentOption() == 1) {
              vecBullets.clear();
              if (!map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                               widgetWidth, false, 2))
                break;
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, playerMaxHealth,
                             true);
              pl2.initPlayer("Player2.png", map.pl2X, map.pl2Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, playerMaxHealth,
                             false);
              initEnemies();
			  setEnemies(vecEnemies);
              renderMode = 3;
              ost.stop();
            } else {
				
				renderMode = 5;
            }
          }
          break;
        }
        }
      }
      mWindow.clear();
      p1Widget.draw(mWindow);
      p2Widget.draw(mWindow);
      menu.draw(mWindow);
      mWindow.display();
    } else if (renderMode == 2) { // game 1 player
		frameRandom = rand();

		mainTime = clockMain.getElapsedTime().asMicroseconds(); //for animation
		mainTime = mainTime / 1000;
		clockMain.restart();
		

      sf::Event event;
      while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
          mWindow.close();
          mWindow.~RenderWindow();
          return 0;
        }
        case sf::Event::KeyPressed: {
          if (event.key.code == sf::Keyboard::Space && pl1.getAmmoCount() > 0) {
            clock1.restart();
            shoot.play();
            Bullet newBullet(pl1.getFacePosition(), pl1.getDirection(),
                             bulletSpeed, 1);
            newBullet.setTexture(bulletTex);
            vecBullets.push_back(newBullet);
            pl1.minusAmmo();
          } else if (event.key.code == sf::Keyboard::Escape) {
            ost.play();
            renderMode = 0;
            vecEnemies.clear();
            p1Widget.updateScore(0);
            continue;
          } else if (event.key.code == sf::Keyboard::P)
            pause();
          break;
        }
        }
      }

      mWindow.clear();

      map.setFirstLayer(true); // draw first layer
      map.draw(mWindow, mainTime);

      pl1.updatePlayer(
          clock1); // player between ground and some(bushes) overlays
      pl1.draw(mWindow);

      for (auto &i : vecEnemies) {
        i.updateEnemy(BehaviourCounter, pl1.x, pl1.y);
        i.draw(mWindow);
      }


      if (BehaviourCounter % (100 / difficulty) == 0) {
        for (auto &i : vecEnemies) {
          if (rand() % 2) {
            Bullet newBullet(i.getFacePosition(), i.getDirection(), bulletSpeed,
                             0);
            newBullet.setTexture(bulletTex);
            vecBullets.push_back(newBullet);
          }
        }
      }
      // TUT ESHE NORMALNO, PERVAYA ITERACIYA PASHET
      vecBulletBuffer.clear();
      for (auto &i : vecBullets) {
        i.updateBullet();
        i.draw(mWindow);

        int shouldDestroy = 0;
        if (checkCollisionTiles(map, i))
          shouldDestroy++;
        if (checkCollisionEnemies(i, vecEnemies, hit, p1Widget, p2Widget))
          shouldDestroy++;
        if (checkCollisionPlayer(i, pl1, hit))
          shouldDestroy++;
        if (shouldDestroy == 0)
          vecBulletBuffer.push_back(i);
		vecEnemies = getEnemies();

      }
	//  std::cout << m << std::endl;

      
      vecBullets = vecBulletBuffer;

      map.setFirstLayer(false); // draw overlay
      map.draw(mWindow, mainTime);
      p1Widget.update(pl1.getAmmoCount(), pl1.getCurrentHealth(), mWindow);
      mWindow.display();
      if (map.fail) {
        won = false;
        vecBullets.clear();
        map.fail = false;
        map.win = false;
        ost.play();
        renderMode = 4;
        difficulty = 1;
      } else if (map.win) {
        won = true;
        vecBullets.clear();
        map.win = false;
        map.fail = false;
        ost.play();
        renderMode = 4;
        difficulty++;
      }
      BehaviourCounter++;

    } else if (renderMode == 3) { // game(2 players)
		frameRandom = rand();
      sf::Event event;

	  mainTime = clockMain.getElapsedTime().asMicroseconds(); //for animation
	  mainTime = mainTime / 1000;
	  clockMain.restart();

      while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
          mWindow.close();
          mWindow.~RenderWindow();
          return 0;
        }
        case sf::Event::KeyPressed: {
          if (event.key.code == sf::Keyboard::Space && pl1.getAmmoCount() > 0) {
            shoot.play();
            clock1.restart();
            Bullet newBullet(pl1.getFacePosition(), pl1.getDirection(),
                             bulletSpeed, 1);
            newBullet.setTexture(bulletTex);
            vecBullets.push_back(newBullet);
            pl1.minusAmmo();
          } else if (event.key.code == sf::Keyboard::RControl &&
                     pl2.getAmmoCount() > 0) {
            shoot.play();
            clock2.restart();
            Bullet newBullet(pl2.getFacePosition(), pl2.getDirection(),
                             bulletSpeed, 2);
            newBullet.setTexture(bulletTex);
            vecBullets.push_back(newBullet);
            pl2.minusAmmo();
          } else if (event.key.code == sf::Keyboard::Escape) {
            p1Widget.updateScore(0);
            p2Widget.updateScore(0);
            ost.play();
            renderMode = 0;
            vecEnemies.clear();
            continue;
          } else if (event.key.code == sf::Keyboard::P)
            pause();
          break;
        }
        }
      }

      mWindow.clear();

      map.setFirstLayer(true); // draw first layer
      map.draw(mWindow, mainTime);

      pl1.updatePlayer(
          clock1); // player between ground and some(bushes) overlays
      pl2.updatePlayer(clock2);
      pl1.draw(mWindow);
      pl2.draw(mWindow);

      for (auto &i : vecEnemies) {
        i.updateEnemy(mainTime, pl1.x, pl1.y);
        i.draw(mWindow);
		
      }

      if (BehaviourCounter % (100 / difficulty) == 0) {
		  BehaviourCounter = 0;
        for (auto &i : vecEnemies) {
          if (rand() % 2) {
            Bullet newBullet(i.getFacePosition(), i.getDirection(), bulletSpeed,
                             0);
            newBullet.setTexture(bulletTex);
            vecBullets.push_back(newBullet);
          }
        }
      }

	  
      // TUT ESHE NORMALNO, PERVAYA ITERACIYA PASHET
      vecBulletBuffer.clear();
      for (auto &i : vecBullets) {
		 
        i.updateBullet();
        i.draw(mWindow);

        int shouldDestroy = 0;
       
		if (checkCollisionTiles(map, i))
			shouldDestroy++;
        if (checkCollisionEnemies(i, vecEnemies, hit, p1Widget, p2Widget))
          shouldDestroy++;
        if (checkCollisionPlayer(i, pl1, hit))
          shouldDestroy++;
        if (checkCollisionPlayer(i, pl2, hit))
          shouldDestroy++;
        if (shouldDestroy == 0)
          vecBulletBuffer.push_back(i);
		vecEnemies = getEnemies();
		
      } 
	  vecBullets = vecBulletBuffer;
     

      map.setFirstLayer(false); // draw first layer
      map.draw(mWindow, mainTime);
	  p1Widget.update(pl1.getAmmoCount(), pl1.getCurrentHealth(), mWindow);
	  p2Widget.update(pl2.getAmmoCount(), pl2.getCurrentHealth(), mWindow);
      mWindow.display();

	  if (map.fail) {
		  won = false;
		  vecBullets.clear();
		  map.fail = false;
		  map.win = false;
		  ost.play();
		  renderMode = 4;
		  difficulty = 1;
	  }
	  else if (map.win) {
		  won = true;
		  vecBullets.clear();
		  map.win = false;
		  map.fail = false;
		  ost.play();
		  renderMode = 4;
		  difficulty++;
	  }

      BehaviourCounter++;
	}
	else if (renderMode == 1) { // editor is active
		map.editMap(mWindow);

		mainTime = clockMain.getElapsedTime().asMicroseconds(); //for animation
		mainTime = mainTime / 1000;
		clockMain.restart();

		if (sf::Keyboard::isKeyPressed(
			sf::Keyboard::Escape)) { // this event is when user press "exit"
									 // from
			renderMode = 0;
			map.setExitEditMode(true);
			map.editMap(mWindow);
		}
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				mWindow.~RenderWindow();
				return 0;
			}
			}
		}
		mWindow.clear();
		map.setFirstLayer(true); // draw first layer
		map.draw(mWindow, mainTime);
		map.setFirstLayer(false); // draw overlay
		map.draw(mWindow, mainTime);
		mWindow.display();
	}
	else if(renderMode == 5){
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: {
			mWindow.close();
			mWindow.~RenderWindow();
			return 0;
		}
		case sf::Event::KeyPressed: {
			if (event.key.code == sf::Keyboard::Equal)
				ost.setVolume(ost.getVolume() + 10.f);
			else if (event.key.code == sf::Keyboard::Escape)
				renderMode = 0;
			else if (event.key.code == sf::Keyboard::Hyphen)
				ost.setVolume(ost.getVolume() - 10.f);
			else if (event.key.code == sf::Keyboard::Up)
				subMenu.previousOption();
			else if (event.key.code == sf::Keyboard::Down)
				subMenu.nextOption();
			else if (event.key.code == sf::Keyboard::M) {
				ost.pause();
			}
			else if (event.key.code == sf::Keyboard::Return) {
				if (subMenu.getCurrentOption() == 0) {
					map.setNemMap(true);
					map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
						widgetWidth, true, 0);
					renderMode = 1;
					ost.stop();
				}
				else if (subMenu.getCurrentOption() == 1) {
					map.setNemMap(false);
					map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
						widgetWidth, true, 0);
					renderMode = 1;
					ost.stop();
				}
				else {
					
				}
			}
			break;
		}
		}
	}
	mWindow.clear();
	p1Widget.draw(mWindow);
	p2Widget.draw(mWindow);
	subMenu.draw(mWindow);
	mWindow.display();
    } else if (renderMode == 4) { // end screen win
      mWindow.clear();
      if (won)
        win.draw(mWindow);
      else
        lose.draw(mWindow);
      mWindow.display();
      sf::Event event;
      while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
          mWindow.close();
          mWindow.~RenderWindow();
          return 0;
        }
        case sf::Event::KeyPressed: {
          if (event.key.code == sf::Keyboard::Escape) {
            vecEnemies.clear();
            ost.play();
            renderMode = 0;
          }
        }
        }
      }
    }
  }
  return 0;
}

void setRenderMode(int newMode) { renderMode = newMode; }

void initSound() { 
 hitBuffer.loadFromFile("assets\\broke_armor.wav");
  hit.setBuffer(hitBuffer);
  hit.setVolume(70.f);
  buffer1.loadFromFile("assets\\mainOST.ogg");
  buffer2.loadFromFile("assets\\flaunch.wav");
  shoot.setBuffer(buffer2);
  ost.setBuffer(buffer1);
  ost.setLoop(true);
  ost.setVolume(70.f);

}

void pause() {
  while (true) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
      break;
    }
  }
}

void initEnemies() {
	srand(time(0));
	int numerizer = 0;
  for (auto &i : map.getEnemiesCords()) {
	  numerizer++;
    Enemy newEnemy;
	std::cout << i.x << std::endl;
	newEnemy.initEnemy("ENEMY", i.x, i.y, playerSize, playerSize,
		0, enemySpeed, cellWidth, &map, enemyMaxHealth);
    newEnemy.setEnemyTexture(enemyTex);
    vecEnemies.push_back(newEnemy);
  }
}
