
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
int score = 0;
int main() {
  sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                           "Main window",
                           sf::Style::Close | sf::Style::Titlebar);

  //TileMap map("example_map", cellWidth, mapWidth, mapHeight, false, false);
 // Player pl("Player.png", 13, 13, playerSize, playerSize, 2, 1, cellWidth,
 //           &map);
//
  Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
  Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth,
                  mapHeight, false);
  p1Widget.updateHealth(2);
  p2Widget.updateHealth(0);
  p1Widget.updateBullet(2);
  p2Widget.updateBullet(1);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
		p1Widget.updateScore(score+=10);
	}
    mWindow.clear();

    //// for map
    //if (sf::Keyboard::isKeyPressed(
    //        sf::Keyboard::I)) { // this event is when user press "editor" to
    //                            // create own map
    //  map.initMap("example_map", cellWidth, mapWidth, mapHeight, false, true);
    //}
    //if (map.getEditMode()) { // checking if user switched to editor mod
    //  map.editMap(mWindow);
    //  if (sf::Keyboard::isKeyPressed(
    //          sf::Keyboard::O)) { // this event is when user press "exit" from
    //                              // editor
    //    map.setExitEditMode(true);
    //  }
    //}
    //// for map

   // pl.updatePlayer();
   // mWindow.draw(map);
   // mWindow.draw(pl);
    p1Widget.draw(mWindow);
    p2Widget.draw(mWindow);

    mWindow.display();
  }

  return 0;
}
