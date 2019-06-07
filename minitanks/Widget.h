#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Widget {
private:
  sf::RectangleShape heartRect;
  sf::RenderTexture widgetCanvas;
  sf::Texture background, fullHeart, emptyHeart,bullet,emptyBullet;
  sf::Sprite backgroundSprite, mainSprite, heart1, heart2, heart3,bullet1,bullet2;
  sf::IntRect widgetBounds;
  sf::Text playerId,score;
  sf::Font font;
  void initText(int width, int height, bool firstPlayer);

public:
  Widget(sf::Vector2f position, int width, int height, bool firstPlayer);
  void draw(sf::RenderWindow &window);
  void setPosition(sf::Vector2f position);
  void updateHealth(int currentHealth);
  void updateScore(int score);
  void updateBullet(int currentBullets);
  ~Widget();
};
