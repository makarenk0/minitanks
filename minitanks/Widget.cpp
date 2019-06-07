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
    std::cout << "error loading hearts" << std::endl;
  if (!emptyHeart.loadFromFile("assets\\emptyheart.png"))
    std::cout << "error loading hearts" << std::endl;
  heart1.setPosition(heartRect.getPosition().x + 4,
                     heartRect.getPosition().y + 4);
  heart2.setPosition(heartRect.getPosition().x +
                         heartRect.getSize().x * 9 / 28 + 4,
                     heartRect.getPosition().y + 4);
  heart3.setPosition(heartRect.getPosition().x +
                         heartRect.getSize().x * 9 / 14 + 4,
                     heartRect.getPosition().y + 4);
  // loading bullet textures
  if (!bullet.loadFromFile("assets\\bullet.png"))
    std::cout << "error loading bullets" << std::endl;
  if (!emptyBullet.loadFromFile("assets\\emptyBullet.png"))
    std::cout << "error loading bullets" << std::endl;
  bullet1.setPosition(width * 2 / 10, height * 6 / 10);
  bullet2.setPosition(width * 6 / 10, height * 6 / 10);
  bullet1.scale(2, 2);
  bullet2.scale(2, 2);
  // loading powerups
  speed.loadFromFile("assets\\speed.png");
  emptySpeed.loadFromFile("assets\\emptySpeed.png");
  speedPU.setTexture(speed);
  speedPU.setPosition(0, height / 5);
  speedPU.scale(1.5, 1.5);
  // main render texture as canvas.
  widgetCanvas.create(width, height);
  mainSprite.setTexture(widgetCanvas.getTexture(), false);
  mainSprite.setPosition(position);
  // initialising text on widget
  initText(width, height, firstPlayer);
}

void Widget::draw(sf::RenderWindow &window) {
  widgetCanvas.clear();
  widgetCanvas.draw(backgroundSprite);
  widgetCanvas.draw(heartRect);
  widgetCanvas.draw(heart1);
  widgetCanvas.draw(heart2);
  widgetCanvas.draw(heart3);
  widgetCanvas.draw(bullet1);
  widgetCanvas.draw(bullet2);
  widgetCanvas.draw(speedPU);
  widgetCanvas.draw(playerId);
  widgetCanvas.draw(score);
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
  score.setFont(font);
  score.setCharacterSize(30);
  score.setPosition(width / 16, height / 3);
  score.setFillColor(sf::Color(242, 242, 242, 255));
  if (firstPlayer)
    playerId.setString("PLAYER 1");
  else
    playerId.setString("PLAYER 2");
  score.setString("SCORE 0");
}

void Widget::updateHealth(int currentHealth) {
  if (currentHealth >= 3) {
    heart1.setTexture(fullHeart);
    heart2.setTexture(fullHeart);
    heart3.setTexture(fullHeart);
  } else if (currentHealth == 2) {
    heart1.setTexture(fullHeart);
    heart2.setTexture(fullHeart);
    heart3.setTexture(emptyHeart);
  } else if (currentHealth == 1) {
    heart1.setTexture(fullHeart);
    heart2.setTexture(emptyHeart);
    heart3.setTexture(emptyHeart);
  } else {
    heart1.setTexture(emptyHeart);
    heart2.setTexture(emptyHeart);
    heart3.setTexture(emptyHeart);
  }
}
void Widget::updateScore(int newScore) {
  score.setString("SCORE " + std::to_string(newScore));
}

void Widget::updateBullet(int currentBullets) {
  if (currentBullets >= 2) {
    bullet1.setTexture(bullet);
    bullet2.setTexture(bullet);
  } else if (currentBullets == 1) {
    bullet1.setTexture(bullet);
    bullet2.setTexture(emptyBullet);
  } else {
    bullet1.setTexture(emptyBullet);
    bullet2.setTexture(emptyBullet);
  }
}

void Widget::speedActive(bool isActive) {
	if (isActive)
		speedPU.setTexture(speed);
	else
		speedPU.setTexture(emptySpeed);
}

Widget::~Widget() {}
