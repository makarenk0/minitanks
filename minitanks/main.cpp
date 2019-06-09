
#include "Bullet.h"
#include "MainMenu.h"
#include "Player.h"
#include "TileMap.h"
#include "Widget.h"
#include "toolbox.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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

// render mode, 0 for mainMenu, 1 for editor 2 for game with 1 P,3 for 2 P
int renderMode = 0;
const float bulletSpeed = 10.f;
std::vector<Bullet> vecBullet;

Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth, mapHeight,
                false);
MainMenu menu(sf::Vector2f(widgetWidth, 0), sf::Vector2i(mapWidth, mapHeight));
sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                         "Main window", sf::Style::Close | sf::Style::Titlebar);
TileMap map;
Player pl1;
Player pl2;

std::map<std::string, int> myFirstMap = {
    {"0", 3}, // 0 - bricks, 1 - metal, 2 - bush
    {"1", 10},
    {"2", 1}};

int main() {
  mWindow.setFramerateLimit(FPS);

  sf::Texture bulletTex;
  if (!bulletTex.loadFromFile("assets\\bullet.png"))
    std::cout << "error loading bullet" << std::endl;

  mWindow.setFramerateLimit(FPS);
  p1Widget.updateHealth(2);
  p2Widget.updateHealth(0);
  p1Widget.updateBullet(2);
  p2Widget.updateBullet(1);
  p1Widget.speedActive(true);
  p2Widget.speedActive(false);

  sf::SoundBuffer buffer;
  if (!buffer.loadFromFile("assets\\mainOST.ogg"))
    return -1;
  sf::Sound sound;
  sound.setBuffer(buffer);
  sound.setLoop(true);
  sound.setVolume(70);
  // sound.play();				// UNCOMMENT BEFORE RELEASE

  while (mWindow.isOpen()) {

    if (renderMode == 0) {
      sf::Event event;
      while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed: {
          mWindow.close();
          break;
        }
        case sf::Event::KeyPressed: {
          if (event.key.code == sf::Keyboard::Equal)
            sound.setVolume(sound.getVolume() + 10.f);
          else if (event.key.code == sf::Keyboard::Hyphen)
            sound.setVolume(sound.getVolume() - 10.f);
          else if (event.key.code == sf::Keyboard::Up)
            menu.previousOption();
          else if (event.key.code == sf::Keyboard::Down)
            menu.nextOption();
          else if (event.key.code == sf::Keyboard::Return) {
            if (menu.getCurrentOption() == 0) {
              map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                          widgetWidth, false, false, 1);
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 2, 1, cellWidth, &map);
              renderMode = 2;

            } else if (menu.getCurrentOption() == 1) {
              map.initMap("example_map", cellWidth, mapWidth, mapHeight,
                          widgetWidth, false, false, 2);
              pl1.initPlayer("Player.png", map.pl1X, map.pl1Y, playerSize,
                             playerSize, 2, 1, cellWidth, &map);
              pl2.initPlayer("Player2.png", map.pl2X, map.pl2Y, playerSize,
                             playerSize, 2, 1, cellWidth, &map);
              renderMode = 3;

            } else {
              map.initMap("empty_map", cellWidth, mapWidth, mapHeight,
                          widgetWidth, false, true, 0);
              renderMode = 1;
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
	}
	else if (renderMode == 2) { // game(one player)
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Space) {
					Bullet newBullet(pl1.getFacePosition(), pl1.getDirection(),
						bulletSpeed, false);
					newBullet.setTexture(bulletTex);
					vecBullet.push_back(newBullet);
				}
			}
			}
		}

		mWindow.clear();

		map.setFirstLayer(true); // draw first layer
		map.draw(mWindow);
		pl1.updatePlayer(); // player between ground and some(bushes) overlays
		pl1.draw(mWindow);
		map.setFirstLayer(false); // draw overlay
		map.draw(mWindow);
		for (auto& i : vecBullet) {
			i.updateBullet();
			i.draw(mWindow);
		}
		p1Widget.draw(mWindow);
		p2Widget.draw(mWindow);
		mWindow.display();
	}
	else if (renderMode == 3) { // game(2 players)
		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				break;
			}
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Space) {
					Bullet newBullet(pl1.getFacePosition(), pl1.getDirection(),
						bulletSpeed, false);
					newBullet.setTexture(bulletTex);
					vecBullet.push_back(newBullet);
				}
			}
			}
		}

		mWindow.clear();

		map.setFirstLayer(true); // draw first layer
		map.draw(mWindow);
		pl1.updatePlayer(); // player between ground and some(bushes) overlays
		pl2.updatePlayer();
		pl1.draw(mWindow);
		pl2.draw(mWindow);
		map.setFirstLayer(false); // draw overlay
		map.draw(mWindow);
		for (auto& i : vecBullet) {
			i.updateBullet();
			i.draw(mWindow);
		}
		p1Widget.draw(mWindow);
		p2Widget.draw(mWindow);
		mWindow.display();
	}
     else if (renderMode == 1) { // editor is active

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
          break;
        }
        }
      }
      mWindow.clear();
      map.setFirstLayer(true); // draw first layer
      map.draw(mWindow);
      map.setFirstLayer(false); // draw overlay
      map.draw(mWindow);
      mWindow.display();
    }
  }
  return 0;
}
