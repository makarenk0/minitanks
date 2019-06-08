
#include "MainMenu.h"
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

// render mode, 0 for mainMenu, 1 for game, 2 for editor
int renderMode = 0;
int main() {
  sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                           "Main window",
                           sf::Style::Close | sf::Style::Titlebar);

  TileMap map("example_map", cellWidth, mapWidth, mapHeight, false, false);
  Player pl("Player.png", 20, 20, playerSize, playerSize, 2, 1, cellWidth,
            &map);

  Widget p1Widget(sf::Vector2f(0, 0), widgetWidth, mapHeight, true);
  Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth,
                  mapHeight, false);
  MainMenu menu(sf::Vector2f(widgetWidth, 0),
                sf::Vector2i(mapWidth, mapHeight));
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
	  // for map
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
	  mWindow.clear();
	  pl.updatePlayer();
	  map.setFirstLayer(true); // draw first layer
	  map.draw(mWindow);
	  mWindow.draw(pl);         // player between ground and some(bushes) overlays
	  map.setFirstLayer(false); // draw overlay
	  map.draw(mWindow);
	  p1Widget.draw(mWindow);
	  p2Widget.draw(mWindow);
	  mWindow.display();
  }

return 0;
}
