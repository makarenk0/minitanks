
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
#define mapWidth 864
#define widgetWidth 192
#define FPS 60
#define cellWidth 48
#define playerSize 40

// render mode, 0 for mainMenu, 1 for editor 2 for game with 1 P,3 for 2 P, 4
// for endscreen
int renderMode = 0;
const float bulletSpeed = 5.f;
int buf;
long unsigned int BehaviourCounter = 0;

std::vector<Bullet> vecBullet;
std::vector<Enemy> vecEntities;

Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth, mapHeight,
                false);
MainMenu menu(sf::Vector2f(widgetWidth, 0), sf::Vector2i(mapWidth, mapHeight));
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
void setRenderMode(int newMode);
void pause();
void initEnemies();
int main() {
  srand(time(0));
  initSound();
  sf::Clock clock1, clock2, clock3;
  mWindow.setFramerateLimit(FPS);


  if (!bulletTex.loadFromFile("assets\\bullet.png"))
    std::cout << "error loading bullet" << std::endl;
  if (!enemyTex.loadFromFile("assets\\Enemy.png"))
    std::cout << "error loading bullet" << std::endl;

  mWindow.setFramerateLimit(FPS);

  // ost.play();
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
          else if (event.key.code == sf::Keyboard::Return) {
            if (menu.getCurrentOption() == 0) {
              if (!map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                               widgetWidth, false, false, 1))
                break;
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, 3, true);
			  initEnemies();
              renderMode = 2;
              ost.stop();
            } else if (menu.getCurrentOption() == 1) {
              if (!map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                               widgetWidth, false, false, 2))
                break;
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, 3, true);
              pl2.initPlayer("Player2.png", map.pl2X, map.pl2Y, playerSize,
                             playerSize, 0, 2, cellWidth, &map, 3, false);
			  initEnemies();
              renderMode = 3;
              ost.stop();
            } else {
              map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                          widgetWidth, false, true, 0);
              renderMode = 1;
              ost.stop();
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
    } else if (renderMode == 2) { // game
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
                             bulletSpeed, false);
            newBullet.setTexture(bulletTex);
            vecBullet.push_back(newBullet);
            pl1.minusAmmo();
          } else if (event.key.code == sf::Keyboard::Escape) {
            ost.play();
            renderMode = 0;
            vecEntities.clear();
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
      map.draw(mWindow);
      pl1.updatePlayer(
          clock1); // player between ground and some(bushes) overlays
      pl1.draw(mWindow);

      checkCollisionPlayers1(vecBullet, pl1, hit);

      vecEntities =
          checkCollisionEntities(vecBullet, vecEntities, hit, p1Widget);
      vecBullet = getVector();
      checkCollisionTiles(map, vecBullet);

      vecBullet = getVector();
      for (auto &i : vecEntities) {
        i.updateEnemy(BehaviourCounter);
        i.draw(mWindow);
      }

      for (auto &i : vecBullet) {
        i.updateBullet();
        i.draw(mWindow);
      }

      map.setFirstLayer(false); // draw overlay
      map.draw(mWindow);
      p1Widget.updateBullet(pl1.getAmmoCount());
      p1Widget.updateHealth(pl1.getCurrentHealth());
      p1Widget.draw(mWindow);
      mWindow.display();
      if (map.fail) {
        vecBullet.clear();
        map.fail = false;
        map.win = false;
        ost.play();
        renderMode = 5;
      } else if (map.win) {
        vecBullet.clear();
        map.win = false;
        map.fail = false;
        ost.play();
        renderMode = 4;
      }
      if (BehaviourCounter % 240 == 0) {

        for (auto &i : vecEntities) {

          if (rand() % 2) {
            Bullet newBullet(i.getFacePosition(), i.getDirection(), bulletSpeed,
                             false);
            newBullet.setTexture(bulletTex);
            vecBullet.push_back(newBullet);
          }
        }
      }

      BehaviourCounter++;
      if (BehaviourCounter > 429496729)
        BehaviourCounter = 0;
    } else if (renderMode == 3) { // game(2 players)
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
            Bullet newBullet(pl1.getFacePosition(), pl1.getDirection(),
                             bulletSpeed, false);
            newBullet.setTexture(bulletTex);
            vecBullet.push_back(newBullet);
            pl1.minusAmmo();
          } else if (event.key.code == sf::Keyboard::RControl &&
                     pl2.getAmmoCount() > 0) {
            clock2.restart();
            Bullet newBullet(pl2.getFacePosition(), pl2.getDirection(),
                             bulletSpeed, false);
            newBullet.setTexture(bulletTex);
            vecBullet.push_back(newBullet);
            pl2.minusAmmo();
          } else if (event.key.code == sf::Keyboard::Escape) {
            p1Widget.updateScore(0);
            p2Widget.updateScore(0);
            ost.play();
            renderMode = 0;
            vecEntities.clear();
            continue;
          } else if (event.key.code == sf::Keyboard::P)
            pause();
          break;
        }
        }
      }

      mWindow.clear();

      map.setFirstLayer(true); // draw first layer
      map.draw(mWindow);

      pl1.updatePlayer(
          clock1); // player between ground and some(bushes) overlays
      pl2.updatePlayer(clock2);
      pl1.draw(mWindow);
      pl2.draw(mWindow);

      checkCollisionPlayers2(vecBullet, pl1, pl2, hit);

      vecEntities =
          checkCollisionEntities(vecBullet, vecEntities, hit, p1Widget);
      vecBullet = getVector();
      checkCollisionTiles(map, vecBullet);

      vecBullet = getVector();
      for (auto &i : vecEntities) {
        i.updateEnemy(BehaviourCounter);
        i.draw(mWindow);
      }
      for (auto &i : vecBullet) {
        i.updateBullet();
        i.draw(mWindow);
      }

      map.setFirstLayer(false); // draw first layer
      map.draw(mWindow);
      p1Widget.updateBullet(pl1.getAmmoCount());
      p1Widget.updateHealth(pl1.getCurrentHealth());
      p1Widget.draw(mWindow);
      p2Widget.updateBullet(pl2.getAmmoCount());
      p2Widget.updateHealth(pl2.getCurrentHealth());
      p2Widget.draw(mWindow);
      mWindow.display();
      if (map.fail) {
        vecBullet.clear();
        map.fail = false;
        map.win = false;
        ost.play();
        renderMode = 5;
      } else if (map.win) {
        vecBullet.clear();
        map.win = false;
        map.fail = false;
        ost.play();
        renderMode = 4;
      }
      if (BehaviourCounter % 240 == 0) {

        for (auto &i : vecEntities) {

          if (rand() % 2) {
            Bullet newBullet(i.getFacePosition(), i.getDirection(), bulletSpeed,
                             false);
            newBullet.setTexture(bulletTex);
            vecBullet.push_back(newBullet);
          }
        }
      }

      BehaviourCounter++;
      if (BehaviourCounter > 429496729)
        BehaviourCounter = 0;
    } else if (renderMode == 1) { // editor is active
      map.editMap(mWindow);
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
      map.draw(mWindow);
      map.setFirstLayer(false); // draw overlay
      map.draw(mWindow);
      mWindow.display();
    } else if (renderMode == 4) { // endscreen win
      mWindow.clear();
      win.draw(mWindow);
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
            ost.play();
            renderMode = 0;
          }
        }
        }
      }
    } else if (renderMode == 5) { // endscreen loose
      mWindow.clear();
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
  hit.setVolume(70);
  buffer1.loadFromFile("assets\\mainOST.ogg");
  buffer2.loadFromFile("assets\\flaunch.wav");
  shoot.setBuffer(buffer2);
  ost.setBuffer(buffer1);
  ost.setLoop(true);
  ost.setVolume(70);
}

void pause() {
  while (true) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
      break;
    }
  }
}

void initEnemies() {

	for (auto& i : map.getEnemiesCords()) {
		Enemy newEnemy;
		newEnemy.initEnemy("Enemy.png", i.x, i.y, playerSize, playerSize, rand()%4,
			2, cellWidth, &map, 2);
		newEnemy.setEnemyTexture(enemyTex);
		vecEntities.push_back(newEnemy);
	}
}
