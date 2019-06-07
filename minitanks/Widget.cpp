#include "Widget.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Widget::Widget(sf::Vector2f position, int width, int height, bool firstPlayer) {
  // creating widget bounds (box containter)
  widgetBounds = {0, 0, width, height};
  // loading background sprite from REPEATED texture
  if (!background.loadFromFile("assets\\brickgray.png"))
    std::cout << "error loading background" << std::endl;
  background.setRepeated(true);
  backgroundSprite.setTexture(background);
  backgroundSprite.setPosition(0, 0);
  backgroundSprite.setTextureRect(widgetBounds);
  // background for heartSprites
  heartRect.setSize(sf::Vector2f(172, 60));
  heartRect.setOutlineThickness(6);
  heartRect.setFillColor(sf::Color(95, 95, 95, 255));
  heartRect.setOutlineColor(sf::Color::Black);
  heartRect.setPosition((width - 172) / 2, height * 4 / 5);
  // loading hearts textures
  if (!fullHeart.loadFromFile("assets\\fullheart.png"))
    std::cout << "error loading background" << std::endl;
  if (!emptyHeart.loadFromFile("assets\\emptyheart.png"))
    std::cout << "error loading background" << std::endl;
  heart1.setPosition(heartRect.getPosition().x +4,
                     heartRect.getPosition().y+4);
  heart2.setPosition(heartRect.getPosition().x + heartRect.getSize().x * 9 / 28 + 4,
                     heartRect.getPosition().y+4);
  heart3.setPosition(heartRect.getPosition().x + heartRect.getSize().x * 9 / 14+4,
                     heartRect.getPosition().y+4);
  // main render texture as canvas.
  widgetCanvas.create(width, height);
  mainSprite.setTexture(widgetCanvas.getTexture(), false);
  mainSprite.setPosition(position);
  // initialising text on widget
  initText(width, height, firstPlayer);
}

void Widget::draw(sf::RenderWindow &window) {
  widgetCanvas.draw(backgroundSprite);
  widgetCanvas.draw(heartRect);
  widgetCanvas.draw(heart1);
  widgetCanvas.draw(heart2);
  widgetCanvas.draw(heart3);
  widgetCanvas.draw(playerId);
  widgetCanvas.display();

  window.draw(mainSprite);
}

void Widget::setPosition(sf::Vector2f position) {
  backgroundSprite.setPosition(position);
}

void Widget::initText(int width, int height, bool firstPlayer) {
  // loading text for player1 | player 2
  if (!font.loadFromFile("assets\\ARCADECLASSIC.TTF"))
    std::cout << "error loading font" << std::endl;
  playerId.setFont(font);
  playerId.setCharacterSize(40);
  playerId.setPosition(width / 10, height / 2);
  playerId.setFillColor(sf::Color(242, 242, 242, 255));
  if (firstPlayer)
    playerId.setString("PLAYER 1");
  else
    playerId.setString("PLAYER 2");
}

void Widget::updateHealth(int currentHealth) {
  switch (currentHealth) {
  case 3: {
    heart1.setTexture(fullHeart);
    heart2.setTexture(fullHeart);
    heart3.setTexture(fullHeart);
    break;
  }
  case 2: {
    heart1.setTexture(fullHeart);
    heart2.setTexture(fullHeart);
    heart3.setTexture(emptyHeart);
    break;
  }
  case 1: {
    heart1.setTexture(fullHeart);
    heart2.setTexture(emptyHeart);
    heart3.setTexture(emptyHeart);
    break;
  }
  case 0: {
    heart1.setTexture(emptyHeart);
    heart2.setTexture(emptyHeart);
    heart3.setTexture(emptyHeart);
    break;
  }
  }
}
