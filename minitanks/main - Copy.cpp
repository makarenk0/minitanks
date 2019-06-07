#include "toolbox.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Widget.h"
#define FPS 60
#define mapHeight 768
#define mapWidth 864
#define widgetWidth 192

int main() {
  sf::RenderWindow mWindow(sf::VideoMode(mapWidth + 2 * widgetWidth, mapHeight),
                           "Main window",
                           sf::Style::Close | sf::Style::Titlebar);
  sf::Sprite testSprite;
  testSprite.setPosition(widgetWidth, 0);
  sf::Texture testTexture;
  sf::Image testImage;
  testImage.create(mapWidth, mapHeight, sf::Color::Red);
  testTexture.loadFromImage(testImage);
  testSprite.setTexture(testTexture);
  testSprite.setPosition(widgetWidth,0);
  Widget p1Widget(sf::Vector2f(0, 0),widgetWidth, mapHeight, true);
  Widget p2Widget(sf::Vector2f(mapWidth + widgetWidth, 0), widgetWidth, mapHeight, false);
  p1Widget.updateHealth(3);
  p2Widget.updateHealth(3);
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

    mWindow.clear();
    mWindow.draw(testSprite);
	p1Widget.draw(mWindow);
	p2Widget.draw(mWindow);
    mWindow.display();
  }

  return 0;
}
