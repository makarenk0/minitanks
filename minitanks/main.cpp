
#include "Player.h"
#include "TileMap.h"
#include "Widget.h"
#include "toolbox.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define FPS 60
#define mapHeight 768
#define mapWidth 864
#define widgetWidth 192
#define FPS 60
#define cellWidth 48
#define playerSize 40

//DEBUG
int score = 0;

int main() {
  sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                           "Main window",
                           sf::Style::Close | sf::Style::Titlebar);
  mWindow.setFramerateLimit(FPS);

   TileMap map("example_map", cellWidth, mapWidth, mapHeight, widgetWidth, false, true);
   Player pl("Player.png", 200, 200, playerSize, playerSize, 2, 1, cellWidth,
             &map);
  
  Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
  Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth,
                  mapHeight, false);
  p1Widget.updateHealth(2);
  p2Widget.updateHealth(0);
  p1Widget.updateBullet(2);
  p2Widget.updateBullet(1);
  p1Widget.speedActive(true);
  p2Widget.speedActive(false);


  while (mWindow.isOpen()) {

    sf::Event event;
    while (mWindow.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed: {
        mWindow.close();
        break;
      }
      }
    }

    // DEBUG
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
      p1Widget.updateScore(score += 10);
    }
    mWindow.clear();

    //for map
     if (sf::Keyboard::isKeyPressed(
           sf::Keyboard::I)) { // this event is when user press "editor" to
                               // create own map
      map.initMap("example_map", cellWidth, mapWidth, mapHeight, false, true);
    }
     if (map.getEditMode()) { // checking if user switched to editor mod
      map.editMap(mWindow);
      if (sf::Keyboard::isKeyPressed(
              sf::Keyboard::O)) { // this event is when user press "exit" from
                                  // editor
        map.setExitEditMode(true);
      }
    }
    // for map

    pl.updatePlayer();

	map.setFirstLayer(true);  //draw first layer
	map.draw(mWindow);

    mWindow.draw(pl);    //player between ground and some overlays

	map.setFirstLayer(false); //draw overlay
	map.draw(mWindow);

    p1Widget.draw(mWindow);
    p2Widget.draw(mWindow);

    mWindow.display();
  }

  return 0;
}
